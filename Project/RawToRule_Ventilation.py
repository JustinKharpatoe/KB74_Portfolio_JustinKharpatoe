# -*- coding: utf-8 -*-
"""
RAW .csv file to Rule .csv file
"""

import time
import pandas as pd
import numpy as np
from decimal import Decimal, getcontext

start_time = time.time()

print("Rules en variabelen aanmaken...")
# Comfortabele luchtstroom
AirRule = {"GoedeErvaring": [7, 70]}

# Kolom volgorde voor het nieuwe bestand
KolomVolgorde = ["High_flow", "Low_flow", "Flow_frozen", "Flow_while_PIR_0", "High_CO2", "Low_CO2", "CO2_frozen", "CO2_neighbours_non_identical", "PIR_NaN"]
dataPer5Minute = False

# Naam van het bestand dat ingelezen en later opgeslagen moet worden
#Readfile = "D:\HHS TI\Jaar 4\Minor Data Science\Data\Test4_RuleValues\d2008apr-jun2015_Minimaal.csv"
Readfile = "D:\HHS TI\Jaar 4\Minor Data Science\Data\Test5_RuleVentilation\D2008_20142015_hour.csv"
Writefile = Readfile[:-4] + "_VENTILATIONRULE" + Readfile[-4:]

# Lees het data bestand in
RAWbestand = pd.read_csv(Readfile, sep=";", decimal=",", parse_dates={"Datum en tijd (uur)": [0, 1]}, dayfirst=True, index_col=0)

# Check of de data per vijf minuten is of per uur
if not RAWbestand.index[0].strftime("%M:%S") == RAWbestand.index[1].strftime("%M:%S"):
    dataPer5Minute = True
    
#RAWbestand.iloc[:, 3] = round(RAWbestand.iloc[:, 3][RAWbestand.iloc[:, 3].notnull()].astype(int))

# 2 cijfers achter de komma
getcontext().prec = 2
RAWbestand.iloc[:, 0] = [float(Decimal("%.2f" % e)) for e in RAWbestand.iloc[:, 0]]
RAWbestand.iloc[:, 1] = [float(Decimal("%.2f" % e)) for e in RAWbestand.iloc[:, 1]]
RAWbestand.iloc[:, 3] = [float(Decimal("%.2f" % e)) for e in RAWbestand.iloc[:, 3]]
RAWbestand.iloc[:, 4] = [float(Decimal("%.2f" % e)) for e in RAWbestand.iloc[:, 4]]

# Maak een nieuw DataFrame object aan voor het nieuwe bestand
RULEbestand = pd.DataFrame(index=RAWbestand.index, columns=KolomVolgorde)

print("Bezig met data bewerken...")
for column in range(1, 4):
    print("\tKolom %s..." % (RAWbestand.columns[column]))    
    for row in range(0, len(RAWbestand)):   
        if column == 1:     #D
            if RAWbestand.iloc[row, column] > AirRule["GoedeErvaring"][1]:      # High flow
                RULEbestand.iloc[row, 0] = 0
                RULEbestand.iloc[row, 1] = 1
            elif RAWbestand.iloc[row, column] < AirRule["GoedeErvaring"][0]:    # Low flow
                RULEbestand.iloc[row, 0] = 1
                RULEbestand.iloc[row, 1] = 0
            else:
                RULEbestand.iloc[row, 0] = 1
                RULEbestand.iloc[row, 1] = 1
            if row > 0:                                                         # Frozen flow
                CO2Range = np.arange((RAWbestand.iloc[row, 3] - RAWbestand.iloc[row-1, 3]/100*10), ((RAWbestand.iloc[row, 3] + RAWbestand.iloc[row-1, 3]/100*10)+0.001), 0.01)
                #if not RAWbestand.iloc[row, 2] == RAWbestand.iloc[row-1, 2] and RAWbestand.iloc[row, column] == RAWbestand.iloc[row-1, column]:
                if bool(np.in1d(RAWbestand.iloc[row, 3], CO2Range)) and RAWbestand.iloc[row, column] == RAWbestand.iloc[row-1, column]:
                    RULEbestand.iloc[row, 2] = 0            # CO2 veranderd maar flow niet
                else:
                    RULEbestand.iloc[row, 2] = 1
            else:
                RULEbestand.iloc[row, 2] = 1
                
        if column == 2:     #E
            if (RAWbestand.iloc[row, column] and RAWbestand.iloc[row, 1]) or (RAWbestand.iloc[row, column] == 0 and RAWbestand.iloc[row, 1] == 0):        # Flow while PIR = 0
                RULEbestand.iloc[row, 3] = 1
            else:
                RULEbestand.iloc[row, 3] = 0
            if RAWbestand.iloc[row, column] in [0, 0.5, 1]:                     # PIR NaN
                RULEbestand.iloc[row, 8] = 1                 
            else:
                RULEbestand.iloc[row, 8] = 0
                
        if column == 3:     #F
            if RAWbestand.iloc[row, column] <= 418:                             # Low CO2
                RULEbestand.iloc[row, 4] = 1
                RULEbestand.iloc[row, 5] = 0
            elif RAWbestand.iloc[row, column] >= 630:                          # High CO2
                RULEbestand.iloc[row, 4] = 0
                RULEbestand.iloc[row, 5] = 1
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
                
            CO2Range = np.arange((RAWbestand.iloc[row-1, column] - RAWbestand.iloc[row-1, column]/100*10), ((RAWbestand.iloc[row-1, column] + RAWbestand.iloc[row-1, column]/100*10)+0.001), 0.01)
            #if RAWbestand.iloc[row, column] in range((CO2Waarden[row-1] - int(CO2Waarden[row-1]/100*10)), ((CO2Waarden[row-1] + int(CO2Waarden[row-1]/100*10))+1)):
            if bool(np.in1d(RAWbestand.iloc[row, column], CO2Range)):
                RULEbestand.iloc[row, 7] = 1                                    # Non-identical CO2 neighbours
            else:
                RULEbestand.iloc[row, 7] = 0

print("Eerste 3 regels:")
print(RULEbestand.head(3))
print("\nLaatste 3 regels:")
print(RULEbestand.tail(3))

RULEbestand.to_csv(Writefile)

print("\n\t\t\t====== Execution time: %s ======" % (time.time() - start_time))
