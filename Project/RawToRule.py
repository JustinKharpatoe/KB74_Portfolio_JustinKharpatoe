# -*- coding: utf-8 -*-
"""
RAW .csv file to Rule .csv file

"""
import time
import pandas as pd

start_time = time.time()
print("Rules aanmaken...")
TempRule = {"Normaal": [19, 23]}
PIRRule = {"Constant": [0.5, 1]}
CO2Rule = {"Normaal": [0, 999], "Hoog": [1000, 1999], "Extreem": [2000], "Constant": 3}
AirRule = {"GoedeErvaring": [0, 0.15]}
#OccRule = {"NietAanwezig": 0, "Aanwezig": 1}

Readfile = "D:\HHS TI\Jaar 4\Minor Data Science\Data\Test4_RuleValues\d2008apr-jun2015 - kopie (3).csv"
Writefile = Readfile[:-4] + "_RULE" + Readfile[-4:]

RAWbestand = pd.read_csv(Readfile, sep=";", index_col=0)

for i in range(0, len(RAWbestand)):
    RAWbestand.iloc[i, 0] = RAWbestand.iloc[i, 0].replace(",", ".")
    RAWbestand.iloc[i, 3] = RAWbestand.iloc[i, 3].replace(",", ".")
    
RAWbestand["Temperature"] = pd.to_numeric(RAWbestand["Temperature"], errors="coerce")
RAWbestand["Air flow"] = pd.to_numeric(RAWbestand["Air flow"], errors="coerce")

#vorigePIRwaarde = 0
temperatuurWaarden = []
CO2Waarden = []

print("Bezig met data bewerken...")    
for column in range(0, len(RAWbestand.columns)):
    print("\tKolom %d..." % (column+1))    
    for row in range(0, len(RAWbestand)):
        if column == 0:     #B
            temperatuurWaarden.append(RAWbestand.iloc[row, column])
            if RAWbestand.iloc[row, column] in range(TempRule["Normaal"][0], TempRule["Normaal"][1]+1):
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
RAWbestand.to_csv(Writefile)

print("\n====== Execution time: %s ======" % (time.time() - start_time))
