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
# Normale temperatuur gaat van 19 t/m 23 graden Celcius
TempRule = {"Normaal": [19, 23]}
# PIR sensor is gitriggerd bij een waarde van 0.5 of 1
PIRRule = {"Constant": [0.5, 1]}
# Normaal CO2 niveau ligt tussen de 0 en 999 ppm, hoog tussen 1000 en 1999 ppm en extreem vanaf 2000 ppm en meer
CO2Rule = {"Normaal": [0, 999], "Hoog": [1000, 1999], "Extreem": [2000], "Constant": 3}
# Comfortabele luchtstroom gaat van 0 t/m 0.15 m/s
AirRule = {"GoedeErvaring": [0, 0.15]}

# Confortabele temperatuur in floating points ipv integers
temperatuurRange = np.arange(TempRule["Normaal"][0], (TempRule["Normaal"][1])+0.001, 0.01)
temperatuurWaarden = []
CO2Waarden = []
#OccRule = {"NietAanwezig": 0, "Aanwezig": 1}
#vorigePIRwaarde = 0

# Zet het aantal cijfers achter de komma op 2
getcontext().prec = 2
temperatuurRange = [float(Decimal("%.2f" % e)) for e in temperatuurRange]

# Naam van het bestand dat ingelezen en later opgeslagen moet worden
Readfile = "D:\HHS TI\Jaar 4\Minor Data Science\Data\Test4_RuleValues\d2008apr-jun2015 - kopie (3).csv"
Writefile = Readfile[:-4] + "_RULE" + Readfile[-4:]

# Lees het bestand in, met als seperator ";", als decimale notatie "," en de datum kolom als index
RAWbestand = pd.read_csv(Readfile, sep=";", decimal=",", index_col=0)

# Converteer de index naar pandas datetime format; 12.04.2015 00:00 --> 2015-12-04 00:00:00
RAWbestand.index = pd.to_datetime(RAWbestand.index)

print("Bezig met data bewerken...")    
for column in range(0, len(RAWbestand.columns)):
    print("\tKolom %d..." % (column+1))    
    for row in range(0, len(RAWbestand)):
        if column == 0:     #B
            temperatuurWaarden.append(RAWbestand.iloc[row, column])
            if bool(np.in1d(RAWbestand.iloc[row, column], temperatuurRange)):
                RAWbestand.iloc[row, column] = 0
            else:
                RAWbestand.iloc[row, column] = 1
        if column == 1:     #C
            if RAWbestand.iloc[row, column]:
                RAWbestand.iloc[row, column] = 1
            else:
                RAWbestand.iloc[row, column] = 0
#==============================================================================
#             if row == 0:
#                 vorigePIRwaarde = RAWbestand.iloc[row, column]
#                 RAWbestand.iloc[row, column] = 1
#             else:
#                 if RAWbestand.iloc[row, column] == vorigePIRwaarde:
#                     vorigePIRwaarde = RAWbestand.iloc[row, column]
#                     RAWbestand.iloc[row, column] = 0
#                 else:
#                     vorigePIRwaarde = RAWbestand.iloc[row, column]
#                     RAWbestand.iloc[row, column] = 1
#==============================================================================
        if column == 2:     #D
            CO2Waarden.append(RAWbestand.iloc[row, column])
            if RAWbestand.iloc[row, column] in range(CO2Rule["Normaal"][0], CO2Rule["Normaal"][1]+1):
                RAWbestand.iloc[row, column] = 0
            elif RAWbestand.iloc[row, column] in range(CO2Rule["Hoog"][0], CO2Rule["Hoog"][1]+1):
                RAWbestand.iloc[row, column] = 1
            else:
                RAWbestand.iloc[row, column] = 2
        if column == 3:     #E
            if RAWbestand.iloc[row, column] > AirRule["GoedeErvaring"][1]:
                RAWbestand.iloc[row, column] = 1
            else:
                RAWbestand.iloc[row, column] = 0
        if column == 4:     #F
            if temperatuurWaarden[row] > TempRule["Normaal"][1] and CO2Waarden[row] >= 700:
                RAWbestand.iloc[row, column] = 0
            else:
                RAWbestand.iloc[row, column] = 1

print("Eerste 3 regels:")
print(RAWbestand.head(3))
print("\nLaatste 3 regels:")
print(RAWbestand.tail(3))

# Sla de nieuwe rule values op in een CSV
RAWbestand.to_csv(Writefile)

# Print het aantal seconden dat het script is uitgevoerd
print("\n\t\t\t====== Execution time: %s ======" % (time.time() - start_time))
