# -*- coding: utf-8 -*-
"""
Created on Thu Nov  2 10:23:04 2017

@author: Justin
"""
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
import time

start_time = time.time()

Readfile = "D:\HHS TI\Jaar 4\Minor Data Science\Data\Test3\d2008apr-jun2015.csv"

# Lees het bestand in, met als seperator ; en de datum+tijd kolom als index
RAWbestand = pd.read_csv(Readfile, sep=";", decimal=",", index_col=0)

# Converteer de index naar pandas datetime format; 12.04.2015 00:00 --> 2015-12-04 00:00:00
RAWbestand.index = pd.to_datetime(RAWbestand.index)

ax0 = sns.violinplot(y=RAWbestand.iloc[:, 8])
plt.show()

# Verwijder een rij met data als een nul in één van de air flow kolommen staat
RAWbestand = RAWbestand[RAWbestand.iloc[:,3] != 0]
RAWbestand = RAWbestand[RAWbestand.iloc[:,9] != 0]

# CO2: HIGH 1338 of 636.5 ( (75% - 25%) * 1.5 + 75% ) EN LOW is 450 (gegokt)
ax0 = sns.violinplot(y=RAWbestand.iloc[:, 8])
plt.show()

# MAX flow is 80 M3 per uur, volgens "Foutdetectie in klimaatsystemen"
ax1 = sns.violinplot(y=RAWbestand.iloc[:, 3])
plt.show()
ax2 = sns.violinplot(y=RAWbestand.iloc[:, 9])
plt.show()

# 26,73 & 6,04
print(RAWbestand.iloc[:, 3].describe())
print(RAWbestand.iloc[:, 9].describe())

print("\n\t\t\t====== Execution time: %s ======" % (time.time() - start_time))
