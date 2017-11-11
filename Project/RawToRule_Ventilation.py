# -*- coding: utf-8 -*-
"""
RAW .csv file to Rule .csv file
"""

import time
import pandas as pd

start_time = time.time()

print("Rules en variabelen aanmaken...")
# Normale temperatuur gaat van 19 t/m 23 graden
TempRule = {"Normaal": [19, 23]}
# PIR sensor is gitriggerd bij een waarde van 0.5 of 1
PIRRule = {"Constant": [0.5, 1]}
# Normaal CO2 niveau ligt tussen de 0 en 999, hoog tussen 1000 en 1999 en extreem vanaf 2000 en meer
CO2Rule = {"Normaal": [0, 999], "Hoog": [1000, 1999], "Extreem": [2000], "Constant": 3}
# Comfortabele luchtstroom gaat van 0 t/m 0.15
AirRule = {"GoedeErvaring": [6.04, 26.73]}

# Kolom volgorde voor het nieuwe bestand
KolomVolgorde = ["High_flow", "Low_flow", "Flow_frozen", "Flow_while_PIR_0", "High_CO2", "Low_CO2", "CO2_frozen", "CO2_neighbours_non_identical", "PIR_NaN"]
CO2Waarden = []
dataPer5Minute = False

# Naam van het bestand dat ingelezen en later opgeslagen moet worden
Readfile = "D:\HHS TI\Jaar 4\Minor Data Science\Data\Test4_RuleValues\d2008apr-jun2015_Minimaal.csv"
Writefile = Readfile[:-4] + "_VENTILATIONRULE" + Readfile[-4:]

# Lees het bestand in, met als seperator ";", als decimale notatie "," en de datum kolom als index
RAWbestand = pd.read_csv(Readfile, sep=";", decimal=",", index_col=0)

# Converteer de index naar pandas datetime format; 12.04.2015 00:00 --> 2015-12-04 00:00:00
RAWbestand.index = pd.to_datetime(RAWbestand.index)

# Check of de data per vijf minuten is of per uur
if RAWbestand.index[0].strftime("%M:%S") == RAWbestand.index[1].strftime("%M:%S"):
    dataPer5Minute = True

# Maak een nieuw DataFrame object aan voor het nieuwe bestand
RULEbestand = pd.DataFrame(index=RAWbestand.index, columns=KolomVolgorde)

RAWbestand["CO2 value"] = RAWbestand["CO2 value"].astype(int)

print("Bezig met data bewerken...")
for column in range(1, 4):
    print("\tKolom %s..." % (RAWbestand.columns[column]))    
    for row in range(0, len(RAWbestand)):   
        if column == 1:     #C
            if RAWbestand.iloc[row, column] and RAWbestand.iloc[row, 3]:        # Flow while PIR = 0
                RULEbestand.iloc[row, 3] = 1
            else:
                RULEbestand.iloc[row, 3] = 0
            if RAWbestand.iloc[row, column] in [0, 0.5, 1]:                     # PIR NaN
                RULEbestand.iloc[row, 8] = 1                 
            else:
                RULEbestand.iloc[row, 8] = 0
                
        if column == 2:     #D
            CO2Waarden.append(RAWbestand.iloc[row, column])
            
            if RAWbestand.iloc[row, column] <= 425:                             # Low CO2
                RULEbestand.iloc[row, 4] = 0
                RULEbestand.iloc[row, 5] = 1
            elif RAWbestand.iloc[row, column] >= 1300:                          # High CO2
                RULEbestand.iloc[row, 4] = 1
                RULEbestand.iloc[row, 5] = 0
            else:
                RULEbestand.iloc[row, 4] = 1
                RULEbestand.iloc[row, 5] = 1             
            if row > 3:                                                         # Frozen CO2
                if dataPer5Minute:
                    if RAWbestand.iloc[row, column] == RAWbestand.iloc[row-1, column] and RAWbestand.iloc[row, column] == RAWbestand.iloc[row-2, column] and RAWbestand.iloc[row, column] == RAWbestand.iloc[row-3, column] and RAWbestand.iloc[row, column] == RAWbestand.iloc[row-4, column]:
                        RULEbestand.iloc[row, 6] = 0
                    else:
                        RULEbestand.iloc[row, 6] = 1
                else:
                    if RAWbestand.iloc[row, column] == RAWbestand.iloc[row-1, column]:
                        RULEbestand.iloc[row, 6] = 0
                    else:
                        RULEbestand.iloc[row, 6] = 1                
            else:
                RULEbestand.iloc[row, 6] = 1
            if RAWbestand.iloc[row, column] in range((CO2Waarden[row-1] - int(CO2Waarden[row-1]/100*10)), ((CO2Waarden[row-1] + int(CO2Waarden[row-1]/100*10))+1)):
                RULEbestand.iloc[row, 7] = 1                                    # Non-identical CO2 neighbours
            else:
                RULEbestand.iloc[row, 7] = 0
                
        if column == 3:     #E
            if RAWbestand.iloc[row, column] > AirRule["GoedeErvaring"][1]:      # High flow
                RULEbestand.iloc[row, 0] = 0
                RULEbestand.iloc[row, 1] = 1
            elif RAWbestand.iloc[row, column] < AirRule["GoedeErvaring"][0]:    # Low flow
                RULEbestand.iloc[row, 0] = 1
                RULEbestand.iloc[row, 1] = 0
            else:
                RULEbestand.iloc[row, 0] = 1
                RULEbestand.iloc[row, 1] = 1
            if row > 1:                                                         # Frozen flow
                if not RAWbestand.iloc[row, 2] == RAWbestand.iloc[row-1, 2] and RAWbestand.iloc[row, column] == RAWbestand.iloc[row-1, column]:
                    RULEbestand.iloc[row, 2] = 1            # CO2 veranderd maar flow niet
                else:
                    RULEbestand.iloc[row, 2] = 0
            else:
                RULEbestand.iloc[row, 2] = 0

print("Eerste 3 regels:")
print(RULEbestand.head(3))
print("\nLaatste 3 regels:")
print(RULEbestand.tail(3))

RULEbestand.to_csv(Writefile)

print("\n\t\t\t====== Execution time: %s ======" % (time.time() - start_time))