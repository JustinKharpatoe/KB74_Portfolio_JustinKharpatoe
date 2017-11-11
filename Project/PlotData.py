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

def violinPlot(Dagdata):        
    plt.figure(1)
    sns.violinplot(y=Dagdata.iloc[:, 3])
    plt.show()
    print(Dagdata.iloc[:, 3].describe())
    
    # MAX flow is 80 M3 per uur, volgens "Foutdetectie in klimaatsystemen"
    plt.figure(2)
    # Plot de air flow data van overdag
    sns.violinplot(y=Dagdata.iloc[:, 1])
    plt.show()
    print(Dagdata.iloc[:, 1].describe())
    
    # Filter alle nul waardes weg
    Dagdata = Dagdata[Dagdata.iloc[:,1] != 0]
    plt.figure(3)
    # Plot de air flow data van overdag zonder nullen
    sns.violinplot(y=Dagdata.iloc[:, 1])
    plt.show()
    print(Dagdata.iloc[:, 1].describe())
    
    # Bereken de 75% van een Series
    print(Dagdata.iloc[:, 1].quantile(0.75))
    

def resultGraph(index):
    Readfile = "D:\HHS TI\Jaar 4\Minor Data Science\Data\Results_VENTILATIONRULEv8.csv"
    PlotData = pd.read_csv(Readfile, sep=";", decimal=",", skiprows=[1])
    PlotData = PlotData.loc[:, ~PlotData.columns.str.contains('^Unnamed')]
    PlotData.index = index
    
    plt.figure(1)
    plt.plot(PlotData.index, PlotData.iloc[:, 8], "ro")
    plt.show()
    
    
    data = PlotData[list(i > 0.5 for i in PlotData.iloc[:, 8])]
    
    f, ax = plt.subplots(1)
    ax.plot(data.index, data.iloc[:, 8])
    ax.set_ylim(0, max(data.iloc[:, 8]))
    plt.show(f)



### MAIN ###

#Readfile = "D:\HHS TI\Jaar 4\Minor Data Science\Data\Test3\d2008apr-jun2015.csv"
Readfile = "D:\HHS TI\Jaar 4\Minor Data Science\Data\Test5_RuleVentilation\D2008_20142015_hour.csv"
# Lees het bestand in, met als seperator ";", als decimale notatie "," en de datum kolom als index
RAWbestand = pd.read_csv(Readfile, sep=";", decimal=",", parse_dates={"Datum en tijd (uur)": [0, 1]}, dayfirst=True, index_col=0)
# Filter de nacht uit de data
Dagdata = RAWbestand[list(i in range(7, 24) for i in RAWbestand.index.hour)]

violinPlot(Dagdata)

#resultGraph(RAWbestand.index)

print("\n\t\t\t====== Execution time: %s ======" % (time.time() - start_time))
