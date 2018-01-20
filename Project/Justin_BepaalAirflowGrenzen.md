

```python
import pandas as pd
import numpy as np
from math import floor
```


```python
dfo = pd.read_csv(("~/notebooks/AlleAirflowData_bruikbaar.csv"), sep=";", index_col=0)#, header=None)
```


```python
dfo.index = pd.to_datetime(dfo.index)
```


```python
dfo.index[0]
```




    Timestamp('2012-01-02 00:00:00')



#### Selecteer alleen data tussen de openingstijden van het gebouw


```python
DagData_o = dfo[list(i in range(7, 24) for i in dfo.index.hour)]
```


```python
DagData_o.describe()
```




<div>
<style>
    .dataframe thead tr:only-child th {
        text-align: right;
    }

    .dataframe thead th {
        text-align: left;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>9829</th>
      <th>36752</th>
      <th>37458</th>
      <th>38988</th>
      <th>40229</th>
      <th>41407</th>
      <th>42140</th>
      <th>42726</th>
      <th>44769</th>
      <th>48184</th>
      <th>...</th>
      <th>596531</th>
      <th>596867</th>
      <th>597011</th>
      <th>597139</th>
      <th>597334</th>
      <th>597487</th>
      <th>597640</th>
      <th>598120</th>
      <th>608406</th>
      <th>610715</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>count</th>
      <td>18665.000000</td>
      <td>18665.000000</td>
      <td>18665.000000</td>
      <td>18665.000000</td>
      <td>18665.000000</td>
      <td>18665.000000</td>
      <td>18665.000000</td>
      <td>18665.000000</td>
      <td>18665.000000</td>
      <td>18665.000000</td>
      <td>...</td>
      <td>12609.000000</td>
      <td>12609.000000</td>
      <td>12609.000000</td>
      <td>12609.000000</td>
      <td>12609.000000</td>
      <td>12609.000000</td>
      <td>12609.000000</td>
      <td>7777.000000</td>
      <td>11302.000000</td>
      <td>7777.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>91.364852</td>
      <td>58.858466</td>
      <td>762.349394</td>
      <td>36.519817</td>
      <td>326.795919</td>
      <td>135.963954</td>
      <td>208.911751</td>
      <td>25.752417</td>
      <td>41.347888</td>
      <td>37.404431</td>
      <td>...</td>
      <td>16.126911</td>
      <td>18.671470</td>
      <td>17.917217</td>
      <td>19.927204</td>
      <td>116.013331</td>
      <td>754.019703</td>
      <td>853.403498</td>
      <td>33.927015</td>
      <td>192.000698</td>
      <td>59.807655</td>
    </tr>
    <tr>
      <th>std</th>
      <td>125.179974</td>
      <td>98.798823</td>
      <td>1004.688746</td>
      <td>49.217682</td>
      <td>341.674973</td>
      <td>202.551459</td>
      <td>339.724775</td>
      <td>46.650548</td>
      <td>63.086920</td>
      <td>61.663854</td>
      <td>...</td>
      <td>22.495982</td>
      <td>25.374364</td>
      <td>22.565418</td>
      <td>25.713596</td>
      <td>166.981383</td>
      <td>1065.190861</td>
      <td>1286.556245</td>
      <td>59.458676</td>
      <td>356.701486</td>
      <td>82.056136</td>
    </tr>
    <tr>
      <th>min</th>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>...</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>25%</th>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>...</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>50%</th>
      <td>3.311773</td>
      <td>0.000000</td>
      <td>62.803693</td>
      <td>5.759144</td>
      <td>214.149141</td>
      <td>10.972197</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>...</td>
      <td>0.024340</td>
      <td>0.878932</td>
      <td>1.557624</td>
      <td>1.427935</td>
      <td>0.723667</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>75%</th>
      <td>202.716914</td>
      <td>100.032724</td>
      <td>1531.224531</td>
      <td>76.808986</td>
      <td>685.162268</td>
      <td>240.459373</td>
      <td>389.593065</td>
      <td>30.091979</td>
      <td>71.549765</td>
      <td>71.293613</td>
      <td>...</td>
      <td>31.208066</td>
      <td>44.056661</td>
      <td>43.525143</td>
      <td>48.324825</td>
      <td>269.881277</td>
      <td>1997.510294</td>
      <td>1825.523413</td>
      <td>49.654076</td>
      <td>229.326323</td>
      <td>149.665775</td>
    </tr>
    <tr>
      <th>max</th>
      <td>438.631673</td>
      <td>415.285826</td>
      <td>3243.306403</td>
      <td>191.995813</td>
      <td>1028.234646</td>
      <td>753.733659</td>
      <td>1170.504946</td>
      <td>240.764148</td>
      <td>229.020372</td>
      <td>243.045298</td>
      <td>...</td>
      <td>146.543006</td>
      <td>88.876219</td>
      <td>81.891210</td>
      <td>98.919953</td>
      <td>490.838485</td>
      <td>2634.555898</td>
      <td>3312.880996</td>
      <td>269.547325</td>
      <td>1729.916912</td>
      <td>335.704242</td>
    </tr>
  </tbody>
</table>
<p>8 rows × 315 columns</p>
</div>



#### Sorteer alle waardes zodat de hoogste (mogelijke outliers) onderaan staan


```python
DagData = DagData_o.apply(lambda x: np.sort(x.values))
```


```python
DagData.tail()
```




<div>
<style>
    .dataframe thead tr:only-child th {
        text-align: right;
    }

    .dataframe thead th {
        text-align: left;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>9829</th>
      <th>36752</th>
      <th>37458</th>
      <th>38988</th>
      <th>40229</th>
      <th>41407</th>
      <th>42140</th>
      <th>42726</th>
      <th>44769</th>
      <th>48184</th>
      <th>...</th>
      <th>596531</th>
      <th>596867</th>
      <th>597011</th>
      <th>597139</th>
      <th>597334</th>
      <th>597487</th>
      <th>597640</th>
      <th>598120</th>
      <th>608406</th>
      <th>610715</th>
    </tr>
    <tr>
      <th>timestamp</th>
      <th></th>
      <th></th>
      <th></th>
      <th></th>
      <th></th>
      <th></th>
      <th></th>
      <th></th>
      <th></th>
      <th></th>
      <th></th>
      <th></th>
      <th></th>
      <th></th>
      <th></th>
      <th></th>
      <th></th>
      <th></th>
      <th></th>
      <th></th>
      <th></th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>2016-04-30 10:00:00</th>
      <td>423.940727</td>
      <td>379.295846</td>
      <td>3227.028371</td>
      <td>172.982980</td>
      <td>1009.034785</td>
      <td>700.897689</td>
      <td>1067.532675</td>
      <td>224.780409</td>
      <td>219.932650</td>
      <td>227.704337</td>
      <td>...</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
    </tr>
    <tr>
      <th>2016-04-30 11:00:00</th>
      <td>426.446755</td>
      <td>383.164516</td>
      <td>3233.766384</td>
      <td>173.409385</td>
      <td>1017.213849</td>
      <td>702.894506</td>
      <td>1075.773270</td>
      <td>227.606120</td>
      <td>220.079246</td>
      <td>233.400894</td>
      <td>...</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
    </tr>
    <tr>
      <th>2016-04-30 12:00:00</th>
      <td>429.160027</td>
      <td>386.452955</td>
      <td>3235.707782</td>
      <td>175.386317</td>
      <td>1017.877582</td>
      <td>712.818930</td>
      <td>1107.594460</td>
      <td>234.587231</td>
      <td>226.532299</td>
      <td>234.095085</td>
      <td>...</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
    </tr>
    <tr>
      <th>2016-04-30 13:00:00</th>
      <td>434.739759</td>
      <td>386.725364</td>
      <td>3236.514596</td>
      <td>177.767806</td>
      <td>1020.183188</td>
      <td>719.885982</td>
      <td>1118.091513</td>
      <td>239.812027</td>
      <td>226.947888</td>
      <td>236.654525</td>
      <td>...</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
    </tr>
    <tr>
      <th>2016-04-30 14:00:00</th>
      <td>438.631673</td>
      <td>415.285826</td>
      <td>3243.306403</td>
      <td>191.995813</td>
      <td>1028.234646</td>
      <td>753.733659</td>
      <td>1170.504946</td>
      <td>240.764148</td>
      <td>229.020372</td>
      <td>243.045298</td>
      <td>...</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
      <td>NaN</td>
    </tr>
  </tbody>
</table>
<p>5 rows × 315 columns</p>
</div>



#### Haal de grootste outliers weg door de onderste 25% weg te halen


```python
DagData.reset_index()
DagData75 = DagData.iloc[:round((len(DagData)/100*75)), :]
```


```python
DagData75.describe()
```




<div>
<style>
    .dataframe thead tr:only-child th {
        text-align: right;
    }

    .dataframe thead th {
        text-align: left;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>9829</th>
      <th>36752</th>
      <th>37458</th>
      <th>38988</th>
      <th>40229</th>
      <th>41407</th>
      <th>42140</th>
      <th>42726</th>
      <th>44769</th>
      <th>48184</th>
      <th>...</th>
      <th>596531</th>
      <th>596867</th>
      <th>597011</th>
      <th>597139</th>
      <th>597334</th>
      <th>597487</th>
      <th>597640</th>
      <th>598120</th>
      <th>608406</th>
      <th>610715</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>count</th>
      <td>13999.000000</td>
      <td>13999.000000</td>
      <td>13999.000000</td>
      <td>13999.000000</td>
      <td>13999.000000</td>
      <td>13999.000000</td>
      <td>13999.000000</td>
      <td>13999.000000</td>
      <td>13999.000000</td>
      <td>13999.000000</td>
      <td>...</td>
      <td>12609.000000</td>
      <td>12609.000000</td>
      <td>12609.000000</td>
      <td>12609.000000</td>
      <td>12609.000000</td>
      <td>12609.000000</td>
      <td>12609.000000</td>
      <td>7777.000000</td>
      <td>11302.000000</td>
      <td>7777.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>24.225096</td>
      <td>6.144682</td>
      <td>238.411789</td>
      <td>10.206118</td>
      <td>171.595012</td>
      <td>25.181094</td>
      <td>20.039895</td>
      <td>1.442561</td>
      <td>8.049729</td>
      <td>4.099191</td>
      <td>...</td>
      <td>16.126911</td>
      <td>18.671470</td>
      <td>17.917217</td>
      <td>19.927204</td>
      <td>116.013331</td>
      <td>754.019703</td>
      <td>853.403498</td>
      <td>33.927015</td>
      <td>192.000698</td>
      <td>59.807655</td>
    </tr>
    <tr>
      <th>std</th>
      <td>47.115810</td>
      <td>19.257244</td>
      <td>425.883841</td>
      <td>18.206084</td>
      <td>238.989557</td>
      <td>47.918259</td>
      <td>69.885982</td>
      <td>4.571390</td>
      <td>19.162867</td>
      <td>13.335294</td>
      <td>...</td>
      <td>22.495982</td>
      <td>25.374364</td>
      <td>22.565418</td>
      <td>25.713596</td>
      <td>166.981383</td>
      <td>1065.190861</td>
      <td>1286.556245</td>
      <td>59.458676</td>
      <td>356.701486</td>
      <td>82.056136</td>
    </tr>
    <tr>
      <th>min</th>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>...</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>25%</th>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>...</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>50%</th>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>...</td>
      <td>0.024340</td>
      <td>0.878932</td>
      <td>1.557624</td>
      <td>1.427935</td>
      <td>0.723667</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>75%</th>
      <td>31.811385</td>
      <td>0.000000</td>
      <td>246.311935</td>
      <td>15.987534</td>
      <td>342.241254</td>
      <td>42.962388</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>...</td>
      <td>31.208066</td>
      <td>44.056661</td>
      <td>43.525143</td>
      <td>48.324825</td>
      <td>269.881277</td>
      <td>1997.510294</td>
      <td>1825.523413</td>
      <td>49.654076</td>
      <td>229.326323</td>
      <td>149.665775</td>
    </tr>
    <tr>
      <th>max</th>
      <td>202.716914</td>
      <td>100.032724</td>
      <td>1531.224531</td>
      <td>76.808986</td>
      <td>685.162268</td>
      <td>240.459373</td>
      <td>389.593065</td>
      <td>30.091979</td>
      <td>71.549765</td>
      <td>71.293613</td>
      <td>...</td>
      <td>146.543006</td>
      <td>88.876219</td>
      <td>81.891210</td>
      <td>98.919953</td>
      <td>490.838485</td>
      <td>2634.555898</td>
      <td>3312.880996</td>
      <td>269.547325</td>
      <td>1729.916912</td>
      <td>335.704242</td>
    </tr>
  </tbody>
</table>
<p>8 rows × 315 columns</p>
</div>



#### Pak de maximum waarde van elke sensor zodat er meegerekend kan worden


```python
maxSeries = DagData75.max()
```


```python
maxSeries.head()
```




    9829      202.716914
    36752     100.032724
    37458    1531.224531
    38988      76.808986
    40229     685.162268
    dtype: float64



#### Hoge airflow grens voor elke sensor


```python
highFlow = maxSeries.apply(lambda x: floor(x / 100 * 75))
```


```python
highFlow.head()
```




    9829      152
    36752      75
    37458    1148
    38988      57
    40229     513
    dtype: int64



#### Lage airflow grens voor elke sensor


```python
lowFlow = maxSeries.apply(lambda x: floor(x / 100 * 10))
```


```python
lowFlow.head()
```




    9829      20
    36752     10
    37458    153
    38988      7
    40229     68
    dtype: int64



#### Exporteer de data


```python
d = {"ID": highFlow.index, "Hoge flow": highFlow.values, "Lage flow": lowFlow.values}
exportDF = pd.DataFrame(data=d)
```


```python
exportDF.to_csv("~/notebooks/AirflowGrenzen.csv", sep=";")
```


```python

```
