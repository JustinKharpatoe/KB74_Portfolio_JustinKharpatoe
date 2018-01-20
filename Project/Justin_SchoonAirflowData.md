

```python
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
```


```python
dfo = pd.read_csv(("~/notebooks/AlleAirflowData.csv"), sep=";")#, header=None)
```

### Split de data in 18 delen, zodat het bewerkt kan worden


```python
aantal = int(len(dfo)/18) #12 18 27
df = pd.DataFrame()
print(len(dfo), aantal)
```

    131375844 7298658


#### Bewerken van data
Slice de data in de vooraf bepaalde aantal regels, pivot daarna de data waardoor de field_id's kolomnamen worden in plaats van waardes. Converteer dan de tijd waardes naar pandas datetime format en verwijder alle kolommen met meer dan 100 lege velden. Mochten er NaN waardes zijn, vul deze dan volgens de methode "ffil" (laatst waargenomen waarden doortrekken tot de volgende NIET NaN). Mocht de data nog niet per uur zijn, resample deze dan door het gemiddelde te nemen van alle tussengelegen waardes. 
Maak daarna een nieuw dataframe aan met gesorteerde kolommen.


```python
df = dfo.iloc[:aantal]
df = df.pivot(index="timestamp", columns="field_id", values="value")
df = df.set_index(pd.to_datetime(df.index, unit='D', origin=pd.Timestamp('1899-12-31')))
df = df.dropna(axis=1, thresh=100)
df = df.fillna(method='ffill')
df = df.resample("H").mean()
df1 = df.dropna().reindex_axis(sorted(df.columns), axis=1)
df1.describe()
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
      <th>field_id</th>
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
      <th>361330</th>
      <th>361356</th>
      <th>382668</th>
      <th>382830</th>
      <th>466464</th>
      <th>470074</th>
      <th>471495</th>
      <th>482953</th>
      <th>483052</th>
      <th>506760</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>count</th>
      <td>2928.000000</td>
      <td>2928.000000</td>
      <td>2928.000000</td>
      <td>2928.000000</td>
      <td>2928.000000</td>
      <td>2928.000000</td>
      <td>2928.000000</td>
      <td>2928.000000</td>
      <td>2928.000000</td>
      <td>2928.000000</td>
      <td>...</td>
      <td>2928.000000</td>
      <td>2928.000000</td>
      <td>2928.000000</td>
      <td>2928.000000</td>
      <td>2928.000000</td>
      <td>2928.000000</td>
      <td>2928.000000</td>
      <td>2928.000000</td>
      <td>2928.000000</td>
      <td>2928.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>78.302440</td>
      <td>43.197976</td>
      <td>540.047152</td>
      <td>21.708335</td>
      <td>181.364827</td>
      <td>92.849722</td>
      <td>130.377629</td>
      <td>20.585702</td>
      <td>37.964040</td>
      <td>32.616083</td>
      <td>...</td>
      <td>5379.279519</td>
      <td>2071.025438</td>
      <td>1814.310302</td>
      <td>662.506394</td>
      <td>59.292453</td>
      <td>74.738060</td>
      <td>96.612636</td>
      <td>24.793312</td>
      <td>29.072973</td>
      <td>52.294855</td>
    </tr>
    <tr>
      <th>std</th>
      <td>131.250509</td>
      <td>88.142787</td>
      <td>880.323463</td>
      <td>39.207314</td>
      <td>252.467058</td>
      <td>180.274172</td>
      <td>274.803933</td>
      <td>42.353172</td>
      <td>63.935012</td>
      <td>62.948824</td>
      <td>...</td>
      <td>7072.272960</td>
      <td>3324.945279</td>
      <td>2604.351608</td>
      <td>918.898340</td>
      <td>143.864133</td>
      <td>90.348634</td>
      <td>182.286415</td>
      <td>24.919492</td>
      <td>163.854773</td>
      <td>72.153864</td>
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
      <td>13.727409</td>
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
      <td>68.781631</td>
      <td>4.797898</td>
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
      <td>638.717812</td>
      <td>7.359758</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>2.168762</td>
      <td>0.000000</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>75%</th>
      <td>80.330690</td>
      <td>3.254793</td>
      <td>1059.665644</td>
      <td>18.866758</td>
      <td>424.049358</td>
      <td>47.827189</td>
      <td>0.000000</td>
      <td>1.605927</td>
      <td>73.841711</td>
      <td>6.321878</td>
      <td>...</td>
      <td>12355.300706</td>
      <td>4016.262372</td>
      <td>5120.052786</td>
      <td>1977.938896</td>
      <td>0.000000</td>
      <td>173.528494</td>
      <td>6.401435</td>
      <td>49.882771</td>
      <td>0.000000</td>
      <td>98.418025</td>
    </tr>
    <tr>
      <th>max</th>
      <td>438.631673</td>
      <td>319.407154</td>
      <td>2839.864185</td>
      <td>158.055121</td>
      <td>718.742253</td>
      <td>619.141527</td>
      <td>871.012616</td>
      <td>164.695578</td>
      <td>177.785789</td>
      <td>215.022552</td>
      <td>...</td>
      <td>20351.450514</td>
      <td>12272.801394</td>
      <td>6414.599036</td>
      <td>2069.079070</td>
      <td>768.095481</td>
      <td>256.088041</td>
      <td>550.793995</td>
      <td>55.244837</td>
      <td>1002.982215</td>
      <td>277.062597</td>
    </tr>
  </tbody>
</table>
<p>8 rows × 253 columns</p>
</div>




```python
df = dfo.iloc[aantal:(aantal*2)]
df = df.pivot(index="timestamp", columns="field_id", values="value")
df = df.set_index(pd.to_datetime(df.index, unit='D', origin=pd.Timestamp('1899-12-31')))
df = df.dropna(axis=1, thresh=100)
df = df.fillna(method='ffill')
df = df.resample("H").mean()
df2 = df.dropna().reindex_axis(sorted(df.columns), axis=1)
df2.describe()
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
      <th>field_id</th>
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
      <th>382830</th>
      <th>466464</th>
      <th>470074</th>
      <th>471495</th>
      <th>482953</th>
      <th>483052</th>
      <th>506760</th>
      <th>526315</th>
      <th>526713</th>
      <th>526795</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>count</th>
      <td>81.000000</td>
      <td>81.000000</td>
      <td>81.000000</td>
      <td>81.000000</td>
      <td>81.000000</td>
      <td>81.000000</td>
      <td>81.000000</td>
      <td>81.000000</td>
      <td>81.000000</td>
      <td>81.000000</td>
      <td>...</td>
      <td>81.000000</td>
      <td>81.000000</td>
      <td>81.000000</td>
      <td>81.000000</td>
      <td>81.0</td>
      <td>81.0</td>
      <td>81.000000</td>
      <td>81.000000</td>
      <td>81.000000</td>
      <td>81.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>41.907875</td>
      <td>41.534086</td>
      <td>231.430521</td>
      <td>18.392663</td>
      <td>170.414501</td>
      <td>32.207628</td>
      <td>8.390762</td>
      <td>4.956807</td>
      <td>13.700272</td>
      <td>1.958281</td>
      <td>...</td>
      <td>1106.837377</td>
      <td>6.935730</td>
      <td>77.705674</td>
      <td>138.249924</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>39.164990</td>
      <td>16.654873</td>
      <td>113.962818</td>
      <td>123.608559</td>
    </tr>
    <tr>
      <th>std</th>
      <td>74.425850</td>
      <td>82.298251</td>
      <td>387.775446</td>
      <td>27.550068</td>
      <td>197.419553</td>
      <td>43.309785</td>
      <td>44.274410</td>
      <td>16.029279</td>
      <td>31.792068</td>
      <td>9.749791</td>
      <td>...</td>
      <td>978.794732</td>
      <td>37.845826</td>
      <td>83.872487</td>
      <td>204.551755</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>43.751807</td>
      <td>43.646926</td>
      <td>160.018601</td>
      <td>237.072956</td>
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
      <td>0.0</td>
      <td>0.0</td>
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
      <td>0.0</td>
      <td>0.0</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>50%</th>
      <td>9.544397</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>12.149881</td>
      <td>12.742553</td>
      <td>34.649469</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>...</td>
      <td>1837.830914</td>
      <td>0.000000</td>
      <td>31.718158</td>
      <td>0.000000</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>7.618262</td>
      <td>0.000000</td>
      <td>81.177795</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>75%</th>
      <td>38.215630</td>
      <td>3.281736</td>
      <td>396.388590</td>
      <td>20.253337</td>
      <td>352.176895</td>
      <td>40.838447</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>...</td>
      <td>2026.415021</td>
      <td>0.000000</td>
      <td>182.258302</td>
      <td>440.542646</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>93.853435</td>
      <td>0.000000</td>
      <td>106.337872</td>
      <td>57.292120</td>
    </tr>
    <tr>
      <th>max</th>
      <td>253.038376</td>
      <td>288.525850</td>
      <td>1780.740680</td>
      <td>122.950494</td>
      <td>547.265951</td>
      <td>213.412986</td>
      <td>287.599223</td>
      <td>86.865241</td>
      <td>136.917035</td>
      <td>61.321206</td>
      <td>...</td>
      <td>2084.802888</td>
      <td>261.731764</td>
      <td>193.883845</td>
      <td>478.023212</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>100.103093</td>
      <td>206.821108</td>
      <td>541.462003</td>
      <td>722.779904</td>
    </tr>
  </tbody>
</table>
<p>8 rows × 256 columns</p>
</div>




```python
df = dfo.iloc[(aantal*2):(aantal*3)]
df = df.pivot(index="timestamp", columns="field_id", values="value")
df = df.set_index(pd.to_datetime(df.index, unit='D', origin=pd.Timestamp('1899-12-31')))
df = df.dropna(axis=1, thresh=100)
df = df.fillna(method='ffill')
df = df.resample("H").mean()
df3 = df.dropna().reindex_axis(sorted(df.columns), axis=1)
df3.describe()
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
      <th>field_id</th>
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
      <th>382830</th>
      <th>466464</th>
      <th>470074</th>
      <th>471495</th>
      <th>482953</th>
      <th>483052</th>
      <th>506760</th>
      <th>526315</th>
      <th>526713</th>
      <th>526795</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>count</th>
      <td>900.000000</td>
      <td>900.000000</td>
      <td>900.000000</td>
      <td>900.000000</td>
      <td>900.000000</td>
      <td>900.000000</td>
      <td>900.000000</td>
      <td>900.000000</td>
      <td>900.000000</td>
      <td>900.000000</td>
      <td>...</td>
      <td>900.000000</td>
      <td>900.000000</td>
      <td>900.000000</td>
      <td>900.000000</td>
      <td>900.000000</td>
      <td>900.000000</td>
      <td>900.000000</td>
      <td>900.000000</td>
      <td>900.000000</td>
      <td>900.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>87.090755</td>
      <td>58.694568</td>
      <td>559.007431</td>
      <td>33.903231</td>
      <td>245.244147</td>
      <td>106.109809</td>
      <td>155.774781</td>
      <td>24.478119</td>
      <td>43.395109</td>
      <td>34.959499</td>
      <td>...</td>
      <td>919.001922</td>
      <td>150.573724</td>
      <td>88.896078</td>
      <td>122.626171</td>
      <td>0.167719</td>
      <td>3.543782</td>
      <td>62.075022</td>
      <td>43.438541</td>
      <td>302.820458</td>
      <td>236.743001</td>
    </tr>
    <tr>
      <th>std</th>
      <td>122.326285</td>
      <td>107.554788</td>
      <td>861.971462</td>
      <td>46.284995</td>
      <td>292.548786</td>
      <td>188.093688</td>
      <td>310.681029</td>
      <td>46.969675</td>
      <td>69.525650</td>
      <td>64.852467</td>
      <td>...</td>
      <td>969.601137</td>
      <td>479.691812</td>
      <td>94.039761</td>
      <td>200.965158</td>
      <td>2.634001</td>
      <td>55.943411</td>
      <td>77.089194</td>
      <td>90.677210</td>
      <td>532.911933</td>
      <td>466.814831</td>
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
      <td>33.298345</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>18.232108</td>
      <td>56.777893</td>
      <td>5.750640</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>...</td>
      <td>145.268432</td>
      <td>0.000000</td>
      <td>36.163214</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>8.244885</td>
      <td>0.000000</td>
      <td>9.236730</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>75%</th>
      <td>156.423777</td>
      <td>51.147795</td>
      <td>1011.940880</td>
      <td>45.559005</td>
      <td>529.581468</td>
      <td>57.145000</td>
      <td>0.000000</td>
      <td>10.034246</td>
      <td>101.976611</td>
      <td>20.563701</td>
      <td>...</td>
      <td>1990.188482</td>
      <td>0.000000</td>
      <td>190.523891</td>
      <td>270.397063</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>115.595090</td>
      <td>0.000000</td>
      <td>173.369400</td>
      <td>27.851624</td>
    </tr>
    <tr>
      <th>max</th>
      <td>378.230599</td>
      <td>386.452955</td>
      <td>2815.421841</td>
      <td>171.298984</td>
      <td>958.124880</td>
      <td>640.538185</td>
      <td>1170.504946</td>
      <td>193.242912</td>
      <td>229.020372</td>
      <td>225.732142</td>
      <td>...</td>
      <td>2080.532743</td>
      <td>2585.489729</td>
      <td>245.972242</td>
      <td>567.165455</td>
      <td>45.584781</td>
      <td>955.512790</td>
      <td>222.590685</td>
      <td>332.408469</td>
      <td>1863.629566</td>
      <td>1536.139601</td>
    </tr>
  </tbody>
</table>
<p>8 rows × 256 columns</p>
</div>




```python
df = dfo.iloc[(aantal*3):(aantal*4)]
df = df.pivot(index="timestamp", columns="field_id", values="value")
df = df.set_index(pd.to_datetime(df.index, unit='D', origin=pd.Timestamp('1899-12-31')))
df = df.dropna(axis=1, thresh=100)
df = df.fillna(method='ffill')
df = df.resample("H").mean()
df4 = df.dropna().reindex_axis(sorted(df.columns), axis=1)
df4.describe()
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
      <th>field_id</th>
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
      <th>382830</th>
      <th>466464</th>
      <th>470074</th>
      <th>471495</th>
      <th>482953</th>
      <th>483052</th>
      <th>506760</th>
      <th>526315</th>
      <th>526713</th>
      <th>526795</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>count</th>
      <td>2309.000000</td>
      <td>2309.000000</td>
      <td>2309.000000</td>
      <td>2309.000000</td>
      <td>2309.000000</td>
      <td>2309.000000</td>
      <td>2309.000000</td>
      <td>2309.000000</td>
      <td>2309.000000</td>
      <td>2309.000000</td>
      <td>...</td>
      <td>2309.000000</td>
      <td>2309.000000</td>
      <td>2309.000000</td>
      <td>2309.000000</td>
      <td>2309.000000</td>
      <td>2309.000000</td>
      <td>2309.000000</td>
      <td>2309.000000</td>
      <td>2309.000000</td>
      <td>2309.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>76.617118</td>
      <td>55.611656</td>
      <td>568.125470</td>
      <td>35.699802</td>
      <td>259.844285</td>
      <td>106.891081</td>
      <td>145.307283</td>
      <td>20.304257</td>
      <td>34.266386</td>
      <td>28.879084</td>
      <td>...</td>
      <td>823.198051</td>
      <td>218.011285</td>
      <td>76.016170</td>
      <td>105.383856</td>
      <td>2.192427</td>
      <td>30.254921</td>
      <td>48.732687</td>
      <td>36.154222</td>
      <td>266.338865</td>
      <td>216.514920</td>
    </tr>
    <tr>
      <th>std</th>
      <td>125.530689</td>
      <td>109.847741</td>
      <td>953.450768</td>
      <td>52.523819</td>
      <td>322.695390</td>
      <td>195.053444</td>
      <td>319.274416</td>
      <td>46.820709</td>
      <td>66.848437</td>
      <td>60.894052</td>
      <td>...</td>
      <td>955.401092</td>
      <td>562.753038</td>
      <td>90.840732</td>
      <td>196.659400</td>
      <td>9.979763</td>
      <td>166.690849</td>
      <td>67.453233</td>
      <td>84.146452</td>
      <td>531.715451</td>
      <td>458.721177</td>
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
      <td>1.722260</td>
      <td>1.687014</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>...</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>9.038720</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>75%</th>
      <td>58.771371</td>
      <td>2.515383</td>
      <td>880.528676</td>
      <td>63.523861</td>
      <td>626.049075</td>
      <td>56.966375</td>
      <td>0.000000</td>
      <td>3.229232</td>
      <td>0.000000</td>
      <td>1.467212</td>
      <td>...</td>
      <td>1974.071765</td>
      <td>74.130991</td>
      <td>186.151347</td>
      <td>7.135407</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>98.326444</td>
      <td>0.000000</td>
      <td>81.143513</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>max</th>
      <td>388.520252</td>
      <td>379.295846</td>
      <td>2823.822176</td>
      <td>191.995813</td>
      <td>1028.234646</td>
      <td>637.728302</td>
      <td>1118.091513</td>
      <td>240.764148</td>
      <td>226.947888</td>
      <td>227.704337</td>
      <td>...</td>
      <td>2065.104123</td>
      <td>3479.404893</td>
      <td>241.015075</td>
      <td>532.685671</td>
      <td>56.353525</td>
      <td>969.877356</td>
      <td>224.135720</td>
      <td>388.693620</td>
      <td>1849.775035</td>
      <td>1616.684157</td>
    </tr>
  </tbody>
</table>
<p>8 rows × 256 columns</p>
</div>




```python
df = dfo.iloc[(aantal*4):(aantal*5)]
df = df.pivot(index="timestamp", columns="field_id", values="value")
df = df.set_index(pd.to_datetime(df.index, unit='D', origin=pd.Timestamp('1899-12-31')))
df = df.dropna(axis=1, thresh=100)
df = df.fillna(method='ffill')
df = df.resample("H").mean()
df5 = df.dropna().reindex_axis(sorted(df.columns), axis=1)
df5.describe()
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
      <th>field_id</th>
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
      <th>382830</th>
      <th>466464</th>
      <th>470074</th>
      <th>471495</th>
      <th>482953</th>
      <th>483052</th>
      <th>506760</th>
      <th>526315</th>
      <th>526713</th>
      <th>526795</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>count</th>
      <td>2322.000000</td>
      <td>2322.000000</td>
      <td>2322.000000</td>
      <td>2322.000000</td>
      <td>2322.000000</td>
      <td>2322.000000</td>
      <td>2322.000000</td>
      <td>2322.000000</td>
      <td>2322.000000</td>
      <td>2322.000000</td>
      <td>...</td>
      <td>2322.000000</td>
      <td>2322.000000</td>
      <td>2322.000000</td>
      <td>2322.000000</td>
      <td>2322.000000</td>
      <td>2322.000000</td>
      <td>2322.000000</td>
      <td>2322.000000</td>
      <td>2322.000000</td>
      <td>2322.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>80.860473</td>
      <td>63.992299</td>
      <td>601.183380</td>
      <td>27.100752</td>
      <td>276.541424</td>
      <td>106.597887</td>
      <td>137.531494</td>
      <td>27.784334</td>
      <td>38.748393</td>
      <td>37.871985</td>
      <td>...</td>
      <td>693.319463</td>
      <td>275.525045</td>
      <td>67.375807</td>
      <td>166.364556</td>
      <td>21.775392</td>
      <td>1.771040</td>
      <td>40.336248</td>
      <td>46.145701</td>
      <td>239.198642</td>
      <td>200.556869</td>
    </tr>
    <tr>
      <th>std</th>
      <td>131.661753</td>
      <td>113.085523</td>
      <td>943.843875</td>
      <td>44.419523</td>
      <td>323.092390</td>
      <td>198.184509</td>
      <td>305.208103</td>
      <td>55.837406</td>
      <td>69.153681</td>
      <td>69.968023</td>
      <td>...</td>
      <td>928.925020</td>
      <td>682.471067</td>
      <td>89.097569</td>
      <td>211.704196</td>
      <td>24.207000</td>
      <td>38.468434</td>
      <td>59.574662</td>
      <td>95.245835</td>
      <td>484.193138</td>
      <td>423.598398</td>
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
      <td>4.234867</td>
      <td>135.807121</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>...</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>16.488964</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>75%</th>
      <td>107.257917</td>
      <td>90.838263</td>
      <td>1090.234094</td>
      <td>22.595077</td>
      <td>619.374529</td>
      <td>56.252333</td>
      <td>0.000000</td>
      <td>7.240331</td>
      <td>46.886253</td>
      <td>16.363440</td>
      <td>...</td>
      <td>1972.043251</td>
      <td>117.821549</td>
      <td>175.952494</td>
      <td>421.286693</td>
      <td>48.618968</td>
      <td>0.000000</td>
      <td>93.481774</td>
      <td>0.000000</td>
      <td>114.119540</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>max</th>
      <td>386.809637</td>
      <td>415.285826</td>
      <td>2848.014418</td>
      <td>160.953674</td>
      <td>1017.877582</td>
      <td>622.304938</td>
      <td>1107.594460</td>
      <td>234.587231</td>
      <td>219.932650</td>
      <td>243.045298</td>
      <td>...</td>
      <td>2056.628012</td>
      <td>4238.386635</td>
      <td>236.294756</td>
      <td>560.092000</td>
      <td>51.817583</td>
      <td>996.646422</td>
      <td>196.083320</td>
      <td>395.083095</td>
      <td>1929.916458</td>
      <td>1662.849404</td>
    </tr>
  </tbody>
</table>
<p>8 rows × 256 columns</p>
</div>




```python
df = dfo.iloc[(aantal*5):(aantal*6)]
df = df.pivot(index="timestamp", columns="field_id", values="value")
df = df.set_index(pd.to_datetime(df.index, unit='D', origin=pd.Timestamp('1899-12-31')))
df = df.dropna(axis=1, thresh=100)
df = df.fillna(method='ffill')
df = df.resample("H").mean()
df6 = df.dropna().reindex_axis(sorted(df.columns), axis=1)
df6.describe()
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
      <th>field_id</th>
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
      <th>595916</th>
      <th>596092</th>
      <th>596245</th>
      <th>596531</th>
      <th>596867</th>
      <th>597011</th>
      <th>597139</th>
      <th>597334</th>
      <th>597487</th>
      <th>597640</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>count</th>
      <td>13.000000</td>
      <td>13.000000</td>
      <td>13.000000</td>
      <td>13.000000</td>
      <td>13.000000</td>
      <td>13.000000</td>
      <td>13.000000</td>
      <td>13.000000</td>
      <td>13.000000</td>
      <td>13.000000</td>
      <td>...</td>
      <td>13.000000</td>
      <td>13.000000</td>
      <td>13.000000</td>
      <td>13.000000</td>
      <td>13.000000</td>
      <td>13.000000</td>
      <td>13.000000</td>
      <td>13.000000</td>
      <td>13.000000</td>
      <td>13.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>39.106806</td>
      <td>55.380373</td>
      <td>309.429136</td>
      <td>18.358327</td>
      <td>225.417930</td>
      <td>155.329035</td>
      <td>217.130449</td>
      <td>8.617397</td>
      <td>29.921328</td>
      <td>29.583142</td>
      <td>...</td>
      <td>39.641763</td>
      <td>258.021307</td>
      <td>6.038717</td>
      <td>3.536059</td>
      <td>14.993101</td>
      <td>15.030772</td>
      <td>10.045564</td>
      <td>65.679991</td>
      <td>512.745572</td>
      <td>772.359541</td>
    </tr>
    <tr>
      <th>std</th>
      <td>73.900220</td>
      <td>74.759107</td>
      <td>580.973454</td>
      <td>38.051260</td>
      <td>302.307002</td>
      <td>218.367297</td>
      <td>293.760770</td>
      <td>30.919580</td>
      <td>40.939425</td>
      <td>55.373936</td>
      <td>...</td>
      <td>48.421786</td>
      <td>293.719035</td>
      <td>7.845562</td>
      <td>6.742514</td>
      <td>19.261053</td>
      <td>20.925244</td>
      <td>15.263050</td>
      <td>126.110529</td>
      <td>980.734701</td>
      <td>1257.090405</td>
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
      <td>5.806000</td>
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
      <td>6.649705</td>
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
      <td>7.356441</td>
      <td>57.432452</td>
      <td>2.335412</td>
      <td>0.000000</td>
      <td>1.673075</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>75%</th>
      <td>15.209196</td>
      <td>155.697063</td>
      <td>256.952082</td>
      <td>9.792079</td>
      <td>501.193162</td>
      <td>266.483012</td>
      <td>589.325462</td>
      <td>0.000000</td>
      <td>82.732165</td>
      <td>4.558501</td>
      <td>...</td>
      <td>94.345524</td>
      <td>476.185400</td>
      <td>8.548460</td>
      <td>0.000000</td>
      <td>36.006621</td>
      <td>30.906537</td>
      <td>14.734000</td>
      <td>5.713205</td>
      <td>0.000000</td>
      <td>1400.117186</td>
    </tr>
    <tr>
      <th>max</th>
      <td>225.150777</td>
      <td>158.296645</td>
      <td>1995.498992</td>
      <td>116.766476</td>
      <td>685.712583</td>
      <td>515.776562</td>
      <td>669.804085</td>
      <td>111.522937</td>
      <td>93.919435</td>
      <td>128.649248</td>
      <td>...</td>
      <td>117.807354</td>
      <td>771.265898</td>
      <td>20.989617</td>
      <td>16.542945</td>
      <td>49.226785</td>
      <td>51.986231</td>
      <td>45.701249</td>
      <td>332.018207</td>
      <td>2434.089810</td>
      <td>3104.028203</td>
    </tr>
  </tbody>
</table>
<p>8 rows × 312 columns</p>
</div>




```python
df = dfo.iloc[(aantal*6):(aantal*7)]
df = df.pivot(index="timestamp", columns="field_id", values="value")
df = df.set_index(pd.to_datetime(df.index, unit='D', origin=pd.Timestamp('1899-12-31')))
df = df.dropna(axis=1, thresh=100)
df = df.fillna(method='ffill')
df = df.resample("H").mean()
df7 = df.dropna().reindex_axis(sorted(df.columns), axis=1)
df7.describe()
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
      <th>field_id</th>
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
      <th>595916</th>
      <th>596092</th>
      <th>596245</th>
      <th>596531</th>
      <th>596867</th>
      <th>597011</th>
      <th>597139</th>
      <th>597334</th>
      <th>597487</th>
      <th>597640</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>count</th>
      <td>1829.000000</td>
      <td>1829.000000</td>
      <td>1829.000000</td>
      <td>1829.000000</td>
      <td>1829.000000</td>
      <td>1829.000000</td>
      <td>1829.000000</td>
      <td>1829.000000</td>
      <td>1829.000000</td>
      <td>1829.000000</td>
      <td>...</td>
      <td>1829.000000</td>
      <td>1829.000000</td>
      <td>1829.000000</td>
      <td>1829.000000</td>
      <td>1829.000000</td>
      <td>1829.000000</td>
      <td>1829.000000</td>
      <td>1829.000000</td>
      <td>1829.000000</td>
      <td>1829.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>72.379157</td>
      <td>40.654097</td>
      <td>566.399884</td>
      <td>22.431324</td>
      <td>298.833881</td>
      <td>106.355222</td>
      <td>194.356332</td>
      <td>23.306492</td>
      <td>37.708626</td>
      <td>31.969178</td>
      <td>...</td>
      <td>28.414254</td>
      <td>178.029092</td>
      <td>9.469437</td>
      <td>17.363299</td>
      <td>15.047917</td>
      <td>14.930993</td>
      <td>15.776519</td>
      <td>98.311179</td>
      <td>660.383384</td>
      <td>747.148793</td>
    </tr>
    <tr>
      <th>std</th>
      <td>120.166216</td>
      <td>78.137730</td>
      <td>916.976981</td>
      <td>40.467118</td>
      <td>389.826789</td>
      <td>195.703391</td>
      <td>331.148264</td>
      <td>48.449643</td>
      <td>65.458276</td>
      <td>60.412115</td>
      <td>...</td>
      <td>39.407301</td>
      <td>298.821665</td>
      <td>15.965532</td>
      <td>28.361229</td>
      <td>24.038121</td>
      <td>22.292111</td>
      <td>23.541341</td>
      <td>160.659799</td>
      <td>1043.652384</td>
      <td>1244.518010</td>
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
      <td>1.003544</td>
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
      <td>5.806000</td>
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
      <td>6.433502</td>
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
      <th>75%</th>
      <td>131.501193</td>
      <td>38.993896</td>
      <td>922.771974</td>
      <td>24.621301</td>
      <td>738.405710</td>
      <td>63.090187</td>
      <td>300.710105</td>
      <td>11.768132</td>
      <td>57.078367</td>
      <td>25.088257</td>
      <td>...</td>
      <td>34.188013</td>
      <td>291.956002</td>
      <td>17.316408</td>
      <td>30.416571</td>
      <td>19.823347</td>
      <td>36.342197</td>
      <td>36.338918</td>
      <td>173.890306</td>
      <td>1642.482896</td>
      <td>1305.775345</td>
    </tr>
    <tr>
      <th>max</th>
      <td>411.831805</td>
      <td>326.983233</td>
      <td>3113.909811</td>
      <td>154.415631</td>
      <td>978.515878</td>
      <td>700.897689</td>
      <td>902.584958</td>
      <td>203.922876</td>
      <td>208.365208</td>
      <td>221.081346</td>
      <td>...</td>
      <td>147.993868</td>
      <td>844.236609</td>
      <td>105.664038</td>
      <td>146.543006</td>
      <td>73.727778</td>
      <td>59.703791</td>
      <td>66.173397</td>
      <td>490.838485</td>
      <td>2634.555898</td>
      <td>3265.853244</td>
    </tr>
  </tbody>
</table>
<p>8 rows × 312 columns</p>
</div>




```python
df = dfo.iloc[(aantal*7):(aantal*8)]
df = df.pivot(index="timestamp", columns="field_id", values="value")
df = df.set_index(pd.to_datetime(df.index, unit='D', origin=pd.Timestamp('1899-12-31')))
df = df.dropna(axis=1, thresh=100)
df = df.fillna(method='ffill')
df = df.resample("H").mean()
df8 = df.dropna().reindex_axis(sorted(df.columns), axis=1)
df8.describe()
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
      <th>field_id</th>
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
      <th>596092</th>
      <th>596245</th>
      <th>596531</th>
      <th>596867</th>
      <th>597011</th>
      <th>597139</th>
      <th>597334</th>
      <th>597487</th>
      <th>597640</th>
      <th>608406</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>count</th>
      <td>1611.000000</td>
      <td>1611.000000</td>
      <td>1611.000000</td>
      <td>1611.000000</td>
      <td>1611.000000</td>
      <td>1611.000000</td>
      <td>1611.000000</td>
      <td>1611.000000</td>
      <td>1611.000000</td>
      <td>1611.000000</td>
      <td>...</td>
      <td>1611.000000</td>
      <td>1611.000000</td>
      <td>1611.000000</td>
      <td>1611.000000</td>
      <td>1611.000000</td>
      <td>1611.000000</td>
      <td>1611.000000</td>
      <td>1611.000000</td>
      <td>1611.000000</td>
      <td>1611.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>53.731104</td>
      <td>23.656240</td>
      <td>423.077776</td>
      <td>14.469564</td>
      <td>207.407424</td>
      <td>92.375946</td>
      <td>129.489587</td>
      <td>16.321463</td>
      <td>27.821081</td>
      <td>22.420260</td>
      <td>...</td>
      <td>152.380005</td>
      <td>6.578557</td>
      <td>9.680982</td>
      <td>11.873542</td>
      <td>11.156453</td>
      <td>11.559259</td>
      <td>79.328237</td>
      <td>453.376456</td>
      <td>567.983017</td>
      <td>105.728245</td>
    </tr>
    <tr>
      <th>std</th>
      <td>104.722361</td>
      <td>59.301692</td>
      <td>819.049425</td>
      <td>32.471056</td>
      <td>345.667695</td>
      <td>186.339173</td>
      <td>285.742794</td>
      <td>40.507207</td>
      <td>57.039869</td>
      <td>52.448771</td>
      <td>...</td>
      <td>286.177354</td>
      <td>13.120953</td>
      <td>19.048374</td>
      <td>22.203709</td>
      <td>20.295375</td>
      <td>21.076251</td>
      <td>153.003157</td>
      <td>913.374221</td>
      <td>1142.333015</td>
      <td>337.699961</td>
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
      <th>75%</th>
      <td>14.191985</td>
      <td>0.000000</td>
      <td>351.369591</td>
      <td>7.857250</td>
      <td>366.989730</td>
      <td>46.367811</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.282658</td>
      <td>...</td>
      <td>71.016548</td>
      <td>11.336222</td>
      <td>5.082636</td>
      <td>10.689706</td>
      <td>10.469122</td>
      <td>10.620945</td>
      <td>9.037252</td>
      <td>0.052148</td>
      <td>19.912275</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>max</th>
      <td>374.622723</td>
      <td>324.956697</td>
      <td>3186.513087</td>
      <td>153.599629</td>
      <td>987.885764</td>
      <td>753.733659</td>
      <td>931.307519</td>
      <td>194.495552</td>
      <td>191.499722</td>
      <td>219.468115</td>
      <td>...</td>
      <td>898.314215</td>
      <td>97.980513</td>
      <td>79.048570</td>
      <td>75.742074</td>
      <td>60.173923</td>
      <td>66.533117</td>
      <td>448.285297</td>
      <td>2612.121271</td>
      <td>3260.437173</td>
      <td>1716.334157</td>
    </tr>
  </tbody>
</table>
<p>8 rows × 313 columns</p>
</div>




```python
df = dfo.iloc[(aantal*8):(aantal*9)]
df = df.pivot(index="timestamp", columns="field_id", values="value")
df = df.set_index(pd.to_datetime(df.index, unit='D', origin=pd.Timestamp('1899-12-31')))
df = df.dropna(axis=1, thresh=100)
df = df.fillna(method='ffill')
df = df.resample("H").mean()
df9 = df.dropna().reindex_axis(sorted(df.columns), axis=1)
df9.describe()
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
      <th>field_id</th>
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
      <th>596092</th>
      <th>596245</th>
      <th>596531</th>
      <th>596867</th>
      <th>597011</th>
      <th>597139</th>
      <th>597334</th>
      <th>597487</th>
      <th>597640</th>
      <th>608406</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>count</th>
      <td>1910.000000</td>
      <td>1910.000000</td>
      <td>1910.000000</td>
      <td>1910.000000</td>
      <td>1910.000000</td>
      <td>1910.000000</td>
      <td>1910.000000</td>
      <td>1910.000000</td>
      <td>1910.000000</td>
      <td>1910.000000</td>
      <td>...</td>
      <td>1910.000000</td>
      <td>1910.000000</td>
      <td>1910.000000</td>
      <td>1910.000000</td>
      <td>1910.000000</td>
      <td>1910.000000</td>
      <td>1910.000000</td>
      <td>1910.000000</td>
      <td>1910.000000</td>
      <td>1910.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>57.776917</td>
      <td>27.865508</td>
      <td>504.355816</td>
      <td>17.519216</td>
      <td>264.886195</td>
      <td>73.046257</td>
      <td>102.963059</td>
      <td>15.273054</td>
      <td>28.207834</td>
      <td>24.954820</td>
      <td>...</td>
      <td>128.751757</td>
      <td>7.758495</td>
      <td>13.044689</td>
      <td>13.756792</td>
      <td>12.051015</td>
      <td>12.430114</td>
      <td>84.384580</td>
      <td>535.641367</td>
      <td>589.146721</td>
      <td>31.807989</td>
    </tr>
    <tr>
      <th>std</th>
      <td>103.894060</td>
      <td>59.009345</td>
      <td>869.936775</td>
      <td>34.319786</td>
      <td>373.523484</td>
      <td>155.293080</td>
      <td>253.001998</td>
      <td>38.587683</td>
      <td>53.773409</td>
      <td>50.237806</td>
      <td>...</td>
      <td>259.050248</td>
      <td>13.406448</td>
      <td>22.377942</td>
      <td>22.065543</td>
      <td>20.259556</td>
      <td>20.902871</td>
      <td>157.282606</td>
      <td>972.016674</td>
      <td>1149.304412</td>
      <td>161.468528</td>
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
      <th>75%</th>
      <td>65.363355</td>
      <td>2.020980</td>
      <td>721.389468</td>
      <td>18.329907</td>
      <td>636.979449</td>
      <td>50.842932</td>
      <td>0.000000</td>
      <td>4.216715</td>
      <td>36.587108</td>
      <td>2.879834</td>
      <td>...</td>
      <td>3.079502</td>
      <td>14.897716</td>
      <td>20.675060</td>
      <td>19.326970</td>
      <td>15.176792</td>
      <td>16.786437</td>
      <td>16.466625</td>
      <td>344.679726</td>
      <td>81.697559</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>max</th>
      <td>388.134915</td>
      <td>309.656136</td>
      <td>3079.301658</td>
      <td>150.829878</td>
      <td>972.810154</td>
      <td>599.886980</td>
      <td>922.870439</td>
      <td>202.337312</td>
      <td>207.152648</td>
      <td>234.095085</td>
      <td>...</td>
      <td>917.508022</td>
      <td>94.258475</td>
      <td>78.806724</td>
      <td>72.419517</td>
      <td>61.691442</td>
      <td>64.070890</td>
      <td>449.505666</td>
      <td>2611.391330</td>
      <td>3267.631798</td>
      <td>1625.718309</td>
    </tr>
  </tbody>
</table>
<p>8 rows × 313 columns</p>
</div>




```python
df = dfo.iloc[(aantal*9):(aantal*10)]
df = df.pivot(index="timestamp", columns="field_id", values="value")
df = df.set_index(pd.to_datetime(df.index, unit='D', origin=pd.Timestamp('1899-12-31')))
df = df.dropna(axis=1, thresh=100)
df = df.fillna(method='ffill')
df = df.resample("H").mean()
df10 = df.dropna().reindex_axis(sorted(df.columns), axis=1)
df10.describe()
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
      <th>field_id</th>
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
      <th>596092</th>
      <th>596245</th>
      <th>596531</th>
      <th>596867</th>
      <th>597011</th>
      <th>597139</th>
      <th>597334</th>
      <th>597487</th>
      <th>597640</th>
      <th>608406</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>count</th>
      <td>1455.000000</td>
      <td>1455.000000</td>
      <td>1455.000000</td>
      <td>1455.000000</td>
      <td>1455.000000</td>
      <td>1455.000000</td>
      <td>1455.000000</td>
      <td>1455.000000</td>
      <td>1455.000000</td>
      <td>1455.000000</td>
      <td>...</td>
      <td>1455.000000</td>
      <td>1455.000000</td>
      <td>1455.000000</td>
      <td>1455.000000</td>
      <td>1455.000000</td>
      <td>1455.000000</td>
      <td>1455.000000</td>
      <td>1455.000000</td>
      <td>1455.000000</td>
      <td>1455.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>36.604375</td>
      <td>17.911368</td>
      <td>230.156760</td>
      <td>10.873546</td>
      <td>185.649841</td>
      <td>35.440518</td>
      <td>25.986868</td>
      <td>12.285800</td>
      <td>16.143552</td>
      <td>14.840817</td>
      <td>...</td>
      <td>45.182063</td>
      <td>4.762997</td>
      <td>7.752638</td>
      <td>7.957704</td>
      <td>6.701930</td>
      <td>7.011517</td>
      <td>52.490548</td>
      <td>376.093733</td>
      <td>452.473896</td>
      <td>32.411153</td>
    </tr>
    <tr>
      <th>std</th>
      <td>79.008230</td>
      <td>48.086434</td>
      <td>520.401535</td>
      <td>25.629485</td>
      <td>321.297999</td>
      <td>105.037651</td>
      <td>121.841641</td>
      <td>34.058975</td>
      <td>37.766426</td>
      <td>34.925618</td>
      <td>...</td>
      <td>155.584845</td>
      <td>7.860974</td>
      <td>17.063577</td>
      <td>16.381255</td>
      <td>15.111961</td>
      <td>15.885869</td>
      <td>126.597707</td>
      <td>837.469445</td>
      <td>1045.398742</td>
      <td>138.852777</td>
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
      <th>75%</th>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>119.490572</td>
      <td>0.000000</td>
      <td>267.845394</td>
      <td>3.087510</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>...</td>
      <td>0.000000</td>
      <td>8.754798</td>
      <td>0.332429</td>
      <td>7.043782</td>
      <td>1.248363</td>
      <td>1.070883</td>
      <td>3.849217</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>max</th>
      <td>316.485238</td>
      <td>299.841658</td>
      <td>3033.160066</td>
      <td>152.639683</td>
      <td>976.721000</td>
      <td>549.780358</td>
      <td>849.873390</td>
      <td>170.804055</td>
      <td>205.227784</td>
      <td>159.541843</td>
      <td>...</td>
      <td>892.473215</td>
      <td>45.748424</td>
      <td>78.480100</td>
      <td>71.726732</td>
      <td>59.578911</td>
      <td>61.714119</td>
      <td>445.299575</td>
      <td>2599.161248</td>
      <td>3258.062569</td>
      <td>1238.325229</td>
    </tr>
  </tbody>
</table>
<p>8 rows × 313 columns</p>
</div>




```python
df = dfo.iloc[(aantal*10):(aantal*11)]
df = df.pivot(index="timestamp", columns="field_id", values="value")
df = df.set_index(pd.to_datetime(df.index, unit='D', origin=pd.Timestamp('1899-12-31')))
df = df.dropna(axis=1, thresh=100)
df = df.fillna(method='ffill')
df = df.resample("H").mean()
df11 = df.dropna().reindex_axis(sorted(df.columns), axis=1)
df11.describe()
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
      <th>field_id</th>
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
      <td>1803.000000</td>
      <td>1803.000000</td>
      <td>1803.000000</td>
      <td>1803.000000</td>
      <td>1803.000000</td>
      <td>1803.000000</td>
      <td>1803.000000</td>
      <td>1803.000000</td>
      <td>1803.000000</td>
      <td>1803.000000</td>
      <td>...</td>
      <td>1803.000000</td>
      <td>1803.000000</td>
      <td>1803.000000</td>
      <td>1803.000000</td>
      <td>1803.000000</td>
      <td>1803.000000</td>
      <td>1803.000000</td>
      <td>1803.000000</td>
      <td>1803.000000</td>
      <td>1803.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>52.157929</td>
      <td>41.623522</td>
      <td>371.611199</td>
      <td>26.702628</td>
      <td>198.022876</td>
      <td>47.598530</td>
      <td>56.178476</td>
      <td>11.006052</td>
      <td>23.704986</td>
      <td>19.231926</td>
      <td>...</td>
      <td>10.765368</td>
      <td>11.503606</td>
      <td>11.019871</td>
      <td>12.413353</td>
      <td>48.203007</td>
      <td>460.251179</td>
      <td>493.497631</td>
      <td>10.389383</td>
      <td>124.084085</td>
      <td>35.709884</td>
    </tr>
    <tr>
      <th>std</th>
      <td>98.538640</td>
      <td>94.879012</td>
      <td>738.331045</td>
      <td>48.122650</td>
      <td>292.018278</td>
      <td>116.928939</td>
      <td>192.664257</td>
      <td>29.943600</td>
      <td>51.979856</td>
      <td>43.100771</td>
      <td>...</td>
      <td>19.889936</td>
      <td>21.604197</td>
      <td>19.118217</td>
      <td>22.466195</td>
      <td>119.053236</td>
      <td>910.239994</td>
      <td>1077.200138</td>
      <td>37.197464</td>
      <td>285.419943</td>
      <td>65.861362</td>
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
      <th>75%</th>
      <td>48.096087</td>
      <td>0.759749</td>
      <td>192.590576</td>
      <td>21.349078</td>
      <td>417.740953</td>
      <td>46.548482</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>...</td>
      <td>13.162958</td>
      <td>10.265276</td>
      <td>12.365212</td>
      <td>11.499143</td>
      <td>11.138191</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>8.612997</td>
    </tr>
    <tr>
      <th>max</th>
      <td>390.215201</td>
      <td>360.966149</td>
      <td>3216.934500</td>
      <td>159.603081</td>
      <td>842.677550</td>
      <td>517.770782</td>
      <td>912.661469</td>
      <td>156.615280</td>
      <td>219.449596</td>
      <td>210.368625</td>
      <td>...</td>
      <td>78.896692</td>
      <td>81.328062</td>
      <td>63.385278</td>
      <td>72.774323</td>
      <td>447.717311</td>
      <td>2594.284288</td>
      <td>3312.880996</td>
      <td>202.615263</td>
      <td>1529.801537</td>
      <td>212.819661</td>
    </tr>
  </tbody>
</table>
<p>8 rows × 315 columns</p>
</div>




```python
df = dfo.iloc[(aantal*11):(aantal*12)]
df = df.pivot(index="timestamp", columns="field_id", values="value")
df = df.set_index(pd.to_datetime(df.index, unit='D', origin=pd.Timestamp('1899-12-31')))
df = df.dropna(axis=1, thresh=100)
df = df.fillna(method='ffill')
df = df.resample("H").mean()
df12 = df.dropna().reindex_axis(sorted(df.columns), axis=1)
df12.describe()
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
      <th>field_id</th>
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
      <td>1030.000000</td>
      <td>1030.000000</td>
      <td>1030.000000</td>
      <td>1030.000000</td>
      <td>1030.000000</td>
      <td>1030.000000</td>
      <td>1030.000000</td>
      <td>1030.000000</td>
      <td>1030.000000</td>
      <td>1030.000000</td>
      <td>...</td>
      <td>1030.000000</td>
      <td>1030.000000</td>
      <td>1030.000000</td>
      <td>1030.000000</td>
      <td>1030.000000</td>
      <td>1030.000000</td>
      <td>1030.000000</td>
      <td>1030.00000</td>
      <td>1030.000000</td>
      <td>1030.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>47.125556</td>
      <td>48.539303</td>
      <td>522.680202</td>
      <td>25.538236</td>
      <td>176.910116</td>
      <td>105.886741</td>
      <td>143.731646</td>
      <td>14.623542</td>
      <td>22.169261</td>
      <td>17.885027</td>
      <td>...</td>
      <td>7.435658</td>
      <td>10.821098</td>
      <td>11.649522</td>
      <td>13.248422</td>
      <td>64.904892</td>
      <td>444.368441</td>
      <td>473.626731</td>
      <td>24.75252</td>
      <td>146.079054</td>
      <td>35.456597</td>
    </tr>
    <tr>
      <th>std</th>
      <td>96.837301</td>
      <td>98.703252</td>
      <td>944.418962</td>
      <td>48.033348</td>
      <td>294.474658</td>
      <td>184.483352</td>
      <td>289.713690</td>
      <td>33.507978</td>
      <td>46.420048</td>
      <td>41.918188</td>
      <td>...</td>
      <td>15.573086</td>
      <td>21.620283</td>
      <td>19.655655</td>
      <td>22.901660</td>
      <td>135.355075</td>
      <td>896.781348</td>
      <td>1034.362096</td>
      <td>54.22364</td>
      <td>322.305812</td>
      <td>65.267845</td>
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
      <td>0.00000</td>
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
      <td>0.00000</td>
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
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.00000</td>
      <td>0.000000</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>75%</th>
      <td>18.554697</td>
      <td>0.812207</td>
      <td>684.943191</td>
      <td>7.518523</td>
      <td>355.291409</td>
      <td>115.540664</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>1.529632</td>
      <td>0.000000</td>
      <td>...</td>
      <td>0.390579</td>
      <td>4.124566</td>
      <td>13.928507</td>
      <td>14.050853</td>
      <td>7.111734</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.00000</td>
      <td>0.000000</td>
      <td>3.635137</td>
    </tr>
    <tr>
      <th>max</th>
      <td>347.894819</td>
      <td>327.615642</td>
      <td>3235.707782</td>
      <td>164.180389</td>
      <td>874.287389</td>
      <td>553.223578</td>
      <td>919.380622</td>
      <td>158.753793</td>
      <td>188.331206</td>
      <td>213.078652</td>
      <td>...</td>
      <td>71.439164</td>
      <td>88.876219</td>
      <td>56.978397</td>
      <td>68.019061</td>
      <td>425.710796</td>
      <td>2589.478430</td>
      <td>3259.947890</td>
      <td>185.49270</td>
      <td>1497.499207</td>
      <td>192.728480</td>
    </tr>
  </tbody>
</table>
<p>8 rows × 315 columns</p>
</div>




```python
df = dfo.iloc[(aantal*12):(aantal*13)]
df = df.pivot(index="timestamp", columns="field_id", values="value")
df = df.set_index(pd.to_datetime(df.index, unit='D', origin=pd.Timestamp('1899-12-31')))
df = df.dropna(axis=1, thresh=100)
df = df.fillna(method='ffill')
df = df.resample("H").mean()
df13 = df.dropna().reindex_axis(sorted(df.columns), axis=1)
df13.describe()
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
      <th>field_id</th>
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
      <td>1874.000000</td>
      <td>1874.000000</td>
      <td>1874.000000</td>
      <td>1874.000000</td>
      <td>1874.000000</td>
      <td>1874.000000</td>
      <td>1874.000000</td>
      <td>1874.000000</td>
      <td>1874.000000</td>
      <td>1874.000000</td>
      <td>...</td>
      <td>1874.000000</td>
      <td>1874.000000</td>
      <td>1874.000000</td>
      <td>1874.000000</td>
      <td>1874.000000</td>
      <td>1874.000000</td>
      <td>1874.000000</td>
      <td>1874.000000</td>
      <td>1874.000000</td>
      <td>1874.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>67.559500</td>
      <td>48.666924</td>
      <td>633.417042</td>
      <td>33.714066</td>
      <td>246.684826</td>
      <td>129.061043</td>
      <td>175.731923</td>
      <td>17.403281</td>
      <td>29.496121</td>
      <td>24.740599</td>
      <td>...</td>
      <td>10.661326</td>
      <td>14.076941</td>
      <td>13.767968</td>
      <td>15.617253</td>
      <td>81.631942</td>
      <td>520.995365</td>
      <td>557.048599</td>
      <td>28.086381</td>
      <td>170.946099</td>
      <td>40.468249</td>
    </tr>
    <tr>
      <th>std</th>
      <td>110.772208</td>
      <td>96.499877</td>
      <td>994.277163</td>
      <td>50.361279</td>
      <td>317.352675</td>
      <td>198.696437</td>
      <td>311.856175</td>
      <td>36.384186</td>
      <td>51.910656</td>
      <td>49.233381</td>
      <td>...</td>
      <td>18.545206</td>
      <td>23.269335</td>
      <td>19.468288</td>
      <td>22.616703</td>
      <td>144.376401</td>
      <td>932.141193</td>
      <td>1079.001061</td>
      <td>55.416928</td>
      <td>309.820682</td>
      <td>65.604998</td>
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
      <th>75%</th>
      <td>88.834537</td>
      <td>3.759831</td>
      <td>1063.744107</td>
      <td>82.030667</td>
      <td>632.030816</td>
      <td>269.690013</td>
      <td>234.636683</td>
      <td>1.198467</td>
      <td>52.140239</td>
      <td>3.078286</td>
      <td>...</td>
      <td>15.107594</td>
      <td>20.419483</td>
      <td>33.664562</td>
      <td>34.642064</td>
      <td>90.318949</td>
      <td>668.050176</td>
      <td>24.575868</td>
      <td>0.000000</td>
      <td>208.247377</td>
      <td>97.317773</td>
    </tr>
    <tr>
      <th>max</th>
      <td>374.097722</td>
      <td>331.802792</td>
      <td>3132.329884</td>
      <td>159.678229</td>
      <td>869.155875</td>
      <td>555.880854</td>
      <td>923.761653</td>
      <td>166.971479</td>
      <td>189.260605</td>
      <td>214.664566</td>
      <td>...</td>
      <td>77.002171</td>
      <td>80.564844</td>
      <td>52.054566</td>
      <td>62.879626</td>
      <td>424.303031</td>
      <td>2591.701594</td>
      <td>3272.975354</td>
      <td>172.533924</td>
      <td>1560.835804</td>
      <td>175.016468</td>
    </tr>
  </tbody>
</table>
<p>8 rows × 315 columns</p>
</div>




```python
df = dfo.iloc[(aantal*13):(aantal*14)]
df = df.pivot(index="timestamp", columns="field_id", values="value")
df = df.set_index(pd.to_datetime(df.index, unit='D', origin=pd.Timestamp('1899-12-31')))
df = df.dropna(axis=1, thresh=100)
df = df.fillna(method='ffill')
df = df.resample("H").mean()
df14 = df.dropna().reindex_axis(sorted(df.columns), axis=1)
df14.describe()
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
      <th>field_id</th>
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
      <td>814.000000</td>
      <td>814.000000</td>
      <td>814.000000</td>
      <td>814.000000</td>
      <td>814.000000</td>
      <td>814.000000</td>
      <td>814.000000</td>
      <td>814.000000</td>
      <td>814.000000</td>
      <td>814.000000</td>
      <td>...</td>
      <td>814.000000</td>
      <td>814.000000</td>
      <td>814.000000</td>
      <td>814.000000</td>
      <td>814.000000</td>
      <td>814.000000</td>
      <td>814.000000</td>
      <td>814.000000</td>
      <td>814.000000</td>
      <td>814.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>69.777531</td>
      <td>54.195149</td>
      <td>679.472696</td>
      <td>34.497806</td>
      <td>261.291094</td>
      <td>84.718574</td>
      <td>241.898632</td>
      <td>18.819363</td>
      <td>29.807249</td>
      <td>28.515972</td>
      <td>...</td>
      <td>13.702796</td>
      <td>19.614346</td>
      <td>15.064206</td>
      <td>17.561773</td>
      <td>100.572510</td>
      <td>616.319169</td>
      <td>620.231678</td>
      <td>33.920863</td>
      <td>230.572569</td>
      <td>41.991397</td>
    </tr>
    <tr>
      <th>std</th>
      <td>110.409963</td>
      <td>101.794988</td>
      <td>1006.911240</td>
      <td>49.483606</td>
      <td>327.730729</td>
      <td>157.060303</td>
      <td>362.537651</td>
      <td>38.392902</td>
      <td>51.919566</td>
      <td>50.580031</td>
      <td>...</td>
      <td>21.482785</td>
      <td>28.981435</td>
      <td>20.213889</td>
      <td>23.875988</td>
      <td>161.492888</td>
      <td>1002.665758</td>
      <td>1144.069625</td>
      <td>60.163975</td>
      <td>368.364488</td>
      <td>64.047884</td>
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
      <th>75%</th>
      <td>112.275290</td>
      <td>28.496896</td>
      <td>1474.235449</td>
      <td>89.856895</td>
      <td>676.342232</td>
      <td>65.938959</td>
      <td>736.896534</td>
      <td>1.205778</td>
      <td>54.464194</td>
      <td>34.810290</td>
      <td>...</td>
      <td>26.008985</td>
      <td>46.649400</td>
      <td>39.372547</td>
      <td>46.292672</td>
      <td>227.860686</td>
      <td>1130.947437</td>
      <td>513.819157</td>
      <td>39.075493</td>
      <td>469.574244</td>
      <td>88.208746</td>
    </tr>
    <tr>
      <th>max</th>
      <td>305.625327</td>
      <td>333.705507</td>
      <td>2988.271027</td>
      <td>155.414466</td>
      <td>861.290506</td>
      <td>558.456180</td>
      <td>908.389146</td>
      <td>174.474213</td>
      <td>186.062653</td>
      <td>210.392828</td>
      <td>...</td>
      <td>78.530426</td>
      <td>87.114540</td>
      <td>52.290778</td>
      <td>63.317829</td>
      <td>414.036876</td>
      <td>2600.976769</td>
      <td>3255.802507</td>
      <td>177.135625</td>
      <td>1335.825800</td>
      <td>173.919972</td>
    </tr>
  </tbody>
</table>
<p>8 rows × 313 columns</p>
</div>




```python
df = dfo.iloc[(aantal*14):(aantal*15)]
df = df.pivot(index="timestamp", columns="field_id", values="value")
df = df.set_index(pd.to_datetime(df.index, unit='D', origin=pd.Timestamp('1899-12-31')))
df = df.dropna(axis=1, thresh=100)
df = df.fillna(method='ffill')
df = df.resample("H").mean()
df15 = df.dropna().reindex_axis(sorted(df.columns), axis=1)
df15.describe()
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
      <th>field_id</th>
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
      <td>611.000000</td>
      <td>611.000000</td>
      <td>611.000000</td>
      <td>611.000000</td>
      <td>611.000000</td>
      <td>611.000000</td>
      <td>611.000000</td>
      <td>611.000000</td>
      <td>611.000000</td>
      <td>611.000000</td>
      <td>...</td>
      <td>611.000000</td>
      <td>611.000000</td>
      <td>611.000000</td>
      <td>611.000000</td>
      <td>611.000000</td>
      <td>611.000000</td>
      <td>611.000000</td>
      <td>611.000000</td>
      <td>611.000000</td>
      <td>611.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>36.659289</td>
      <td>29.092183</td>
      <td>340.434492</td>
      <td>17.044955</td>
      <td>155.453956</td>
      <td>50.555056</td>
      <td>133.612534</td>
      <td>10.724995</td>
      <td>16.537917</td>
      <td>16.421316</td>
      <td>...</td>
      <td>7.754615</td>
      <td>5.934554</td>
      <td>7.046447</td>
      <td>6.978296</td>
      <td>82.280044</td>
      <td>358.458632</td>
      <td>394.387946</td>
      <td>11.699814</td>
      <td>94.065871</td>
      <td>33.801093</td>
    </tr>
    <tr>
      <th>std</th>
      <td>83.512416</td>
      <td>71.479032</td>
      <td>706.618391</td>
      <td>36.009039</td>
      <td>253.423386</td>
      <td>135.132326</td>
      <td>276.050280</td>
      <td>29.331362</td>
      <td>34.917553</td>
      <td>39.185560</td>
      <td>...</td>
      <td>15.439821</td>
      <td>18.755982</td>
      <td>14.459560</td>
      <td>15.366554</td>
      <td>147.892151</td>
      <td>797.507562</td>
      <td>953.548848</td>
      <td>36.230035</td>
      <td>274.846719</td>
      <td>67.405684</td>
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
      <th>75%</th>
      <td>14.017174</td>
      <td>0.000000</td>
      <td>156.568056</td>
      <td>9.483420</td>
      <td>244.586136</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>3.639153</td>
      <td>0.000000</td>
      <td>...</td>
      <td>7.472295</td>
      <td>0.000000</td>
      <td>6.104816</td>
      <td>6.800277</td>
      <td>59.187936</td>
      <td>22.075784</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>max</th>
      <td>357.437491</td>
      <td>330.933927</td>
      <td>3155.632518</td>
      <td>147.711797</td>
      <td>855.827323</td>
      <td>534.322757</td>
      <td>899.346674</td>
      <td>132.531280</td>
      <td>190.016519</td>
      <td>190.615469</td>
      <td>...</td>
      <td>74.170123</td>
      <td>87.133287</td>
      <td>55.673124</td>
      <td>65.267221</td>
      <td>415.063226</td>
      <td>2580.260803</td>
      <td>3232.029744</td>
      <td>184.445050</td>
      <td>1404.950762</td>
      <td>208.390911</td>
    </tr>
  </tbody>
</table>
<p>8 rows × 315 columns</p>
</div>




```python
df = dfo.iloc[(aantal*15):(aantal*16)]
df = df.pivot(index="timestamp", columns="field_id", values="value")
df = df.set_index(pd.to_datetime(df.index, unit='D', origin=pd.Timestamp('1899-12-31')))
df = df.dropna(axis=1, thresh=100)
df = df.fillna(method='ffill')
df = df.resample("H").mean()
df16 = df.dropna().reindex_axis(sorted(df.columns), axis=1)
df16.describe()
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
      <th>field_id</th>
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
      <td>1881.000000</td>
      <td>1881.000000</td>
      <td>1881.000000</td>
      <td>1881.000000</td>
      <td>1881.000000</td>
      <td>1881.000000</td>
      <td>1881.000000</td>
      <td>1881.000000</td>
      <td>1881.000000</td>
      <td>1881.000000</td>
      <td>...</td>
      <td>1881.000000</td>
      <td>1881.000000</td>
      <td>1881.000000</td>
      <td>1881.000000</td>
      <td>1881.000000</td>
      <td>1881.000000</td>
      <td>1881.000000</td>
      <td>1881.000000</td>
      <td>1881.000000</td>
      <td>1881.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>65.968764</td>
      <td>35.901972</td>
      <td>657.008040</td>
      <td>34.576408</td>
      <td>249.881588</td>
      <td>116.690073</td>
      <td>244.503997</td>
      <td>16.838254</td>
      <td>24.593890</td>
      <td>26.912360</td>
      <td>...</td>
      <td>11.555981</td>
      <td>15.675365</td>
      <td>14.575812</td>
      <td>16.662225</td>
      <td>98.021826</td>
      <td>680.781273</td>
      <td>800.607047</td>
      <td>28.581628</td>
      <td>204.100576</td>
      <td>47.292068</td>
    </tr>
    <tr>
      <th>std</th>
      <td>108.970105</td>
      <td>73.349431</td>
      <td>1004.703964</td>
      <td>49.675443</td>
      <td>327.316306</td>
      <td>187.582472</td>
      <td>361.030957</td>
      <td>34.675089</td>
      <td>43.778176</td>
      <td>52.480939</td>
      <td>...</td>
      <td>18.593446</td>
      <td>26.029664</td>
      <td>20.637412</td>
      <td>24.062494</td>
      <td>156.479903</td>
      <td>1037.104034</td>
      <td>1269.832211</td>
      <td>56.997089</td>
      <td>379.219285</td>
      <td>78.525020</td>
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
      <td>0.680989</td>
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
      <th>75%</th>
      <td>80.222687</td>
      <td>2.236858</td>
      <td>1159.552458</td>
      <td>80.269450</td>
      <td>659.549573</td>
      <td>194.080875</td>
      <td>707.399363</td>
      <td>0.718866</td>
      <td>38.741135</td>
      <td>3.171568</td>
      <td>...</td>
      <td>17.291705</td>
      <td>22.046449</td>
      <td>35.810100</td>
      <td>39.421111</td>
      <td>192.294959</td>
      <td>1585.330199</td>
      <td>1643.098888</td>
      <td>9.203550</td>
      <td>253.327075</td>
      <td>92.811597</td>
    </tr>
    <tr>
      <th>max</th>
      <td>376.753491</td>
      <td>351.125207</td>
      <td>3236.514596</td>
      <td>172.982980</td>
      <td>850.876585</td>
      <td>548.468756</td>
      <td>928.669693</td>
      <td>153.560702</td>
      <td>186.287224</td>
      <td>212.442937</td>
      <td>...</td>
      <td>76.279127</td>
      <td>88.405200</td>
      <td>63.008235</td>
      <td>73.483201</td>
      <td>423.404257</td>
      <td>2606.640019</td>
      <td>3293.355730</td>
      <td>203.223827</td>
      <td>1557.584985</td>
      <td>262.793603</td>
    </tr>
  </tbody>
</table>
<p>8 rows × 315 columns</p>
</div>




```python
df = dfo.iloc[(aantal*16):(aantal*17)]
df = df.pivot(index="timestamp", columns="field_id", values="value")
df = df.set_index(pd.to_datetime(df.index, unit='D', origin=pd.Timestamp('1899-12-31')))
df = df.dropna(axis=1, thresh=100)
df = df.fillna(method='ffill')
df = df.resample("H").mean()
df17 = df.dropna().reindex_axis(sorted(df.columns), axis=1)
df17.describe()
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
      <th>field_id</th>
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
      <td>1876.000000</td>
      <td>1876.000000</td>
      <td>1876.000000</td>
      <td>1876.000000</td>
      <td>1876.000000</td>
      <td>1876.000000</td>
      <td>1876.000000</td>
      <td>1876.000000</td>
      <td>1876.000000</td>
      <td>1876.000000</td>
      <td>...</td>
      <td>1876.000000</td>
      <td>1876.000000</td>
      <td>1876.000000</td>
      <td>1876.000000</td>
      <td>1876.000000</td>
      <td>1876.000000</td>
      <td>1876.000000</td>
      <td>1876.000000</td>
      <td>1876.000000</td>
      <td>1876.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>59.145143</td>
      <td>30.126189</td>
      <td>631.561805</td>
      <td>31.890807</td>
      <td>234.029568</td>
      <td>128.588246</td>
      <td>170.180360</td>
      <td>16.651221</td>
      <td>19.956228</td>
      <td>21.925909</td>
      <td>...</td>
      <td>10.437349</td>
      <td>14.463173</td>
      <td>12.866790</td>
      <td>14.733716</td>
      <td>99.394959</td>
      <td>561.313651</td>
      <td>637.559111</td>
      <td>30.087557</td>
      <td>161.999020</td>
      <td>44.140529</td>
    </tr>
    <tr>
      <th>std</th>
      <td>102.521662</td>
      <td>63.340772</td>
      <td>1016.477694</td>
      <td>49.109461</td>
      <td>320.577421</td>
      <td>202.371643</td>
      <td>311.224160</td>
      <td>34.176632</td>
      <td>41.165657</td>
      <td>46.930419</td>
      <td>...</td>
      <td>16.771763</td>
      <td>23.029541</td>
      <td>20.130076</td>
      <td>23.519937</td>
      <td>160.438355</td>
      <td>974.888992</td>
      <td>1162.520340</td>
      <td>59.053662</td>
      <td>310.952570</td>
      <td>77.218066</td>
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
      <th>75%</th>
      <td>62.099537</td>
      <td>2.317952</td>
      <td>1089.456430</td>
      <td>73.733879</td>
      <td>646.797063</td>
      <td>256.370561</td>
      <td>114.824081</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>...</td>
      <td>17.509247</td>
      <td>21.792966</td>
      <td>25.083024</td>
      <td>27.813423</td>
      <td>191.029028</td>
      <td>780.389819</td>
      <td>699.662957</td>
      <td>0.000000</td>
      <td>96.266147</td>
      <td>65.625948</td>
    </tr>
    <tr>
      <th>max</th>
      <td>344.080900</td>
      <td>277.920496</td>
      <td>3243.306403</td>
      <td>169.845170</td>
      <td>881.009704</td>
      <td>546.971585</td>
      <td>916.823022</td>
      <td>141.214924</td>
      <td>198.370613</td>
      <td>194.925385</td>
      <td>...</td>
      <td>77.343651</td>
      <td>74.570822</td>
      <td>65.076100</td>
      <td>74.547350</td>
      <td>435.147549</td>
      <td>2595.183114</td>
      <td>3308.619264</td>
      <td>207.684431</td>
      <td>1527.729538</td>
      <td>275.360363</td>
    </tr>
  </tbody>
</table>
<p>8 rows × 311 columns</p>
</div>




```python
df = dfo.iloc[(aantal*17):]
df = df.pivot(index="timestamp", columns="field_id", values="value")
df = df.set_index(pd.to_datetime(df.index, unit='D', origin=pd.Timestamp('1899-12-31')))
df = df.dropna(axis=1, thresh=100)
df = df.fillna(method='ffill')
df = df.resample("H").mean()
df18 = df.dropna().reindex_axis(sorted(df.columns), axis=1)
df18.describe()
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
      <th>field_id</th>
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
      <td>1085.000000</td>
      <td>1085.000000</td>
      <td>1085.000000</td>
      <td>1085.000000</td>
      <td>1085.000000</td>
      <td>1085.000000</td>
      <td>1085.000000</td>
      <td>1085.000000</td>
      <td>1085.000000</td>
      <td>1085.000000</td>
      <td>...</td>
      <td>1085.000000</td>
      <td>1085.000000</td>
      <td>1085.000000</td>
      <td>1085.000000</td>
      <td>1085.000000</td>
      <td>1085.000000</td>
      <td>1085.000000</td>
      <td>1085.000000</td>
      <td>1085.000000</td>
      <td>1085.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>62.992300</td>
      <td>40.801023</td>
      <td>757.151962</td>
      <td>28.927601</td>
      <td>257.082140</td>
      <td>128.755131</td>
      <td>261.848772</td>
      <td>16.759023</td>
      <td>19.243205</td>
      <td>25.575695</td>
      <td>...</td>
      <td>14.563644</td>
      <td>14.978360</td>
      <td>20.506617</td>
      <td>25.154091</td>
      <td>98.689011</td>
      <td>621.291770</td>
      <td>752.060173</td>
      <td>20.297604</td>
      <td>243.530433</td>
      <td>56.943725</td>
    </tr>
    <tr>
      <th>std</th>
      <td>103.283289</td>
      <td>72.942373</td>
      <td>1104.871417</td>
      <td>44.867711</td>
      <td>324.737837</td>
      <td>202.724382</td>
      <td>372.373248</td>
      <td>33.412116</td>
      <td>38.915043</td>
      <td>47.157522</td>
      <td>...</td>
      <td>20.425152</td>
      <td>23.061228</td>
      <td>29.745667</td>
      <td>36.503641</td>
      <td>158.815743</td>
      <td>1006.555123</td>
      <td>1245.904634</td>
      <td>40.473220</td>
      <td>413.113224</td>
      <td>100.084376</td>
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
      <th>75%</th>
      <td>81.215721</td>
      <td>43.034221</td>
      <td>1502.335682</td>
      <td>56.769806</td>
      <td>673.435308</td>
      <td>256.827557</td>
      <td>773.711628</td>
      <td>0.863362</td>
      <td>25.110101</td>
      <td>16.321316</td>
      <td>...</td>
      <td>28.407329</td>
      <td>28.044847</td>
      <td>55.773641</td>
      <td>69.864179</td>
      <td>207.544415</td>
      <td>1138.514062</td>
      <td>1441.879382</td>
      <td>26.376490</td>
      <td>332.876168</td>
      <td>73.828566</td>
    </tr>
    <tr>
      <th>max</th>
      <td>338.257022</td>
      <td>290.852786</td>
      <td>3233.766384</td>
      <td>143.782050</td>
      <td>785.608990</td>
      <td>551.472685</td>
      <td>912.620547</td>
      <td>159.025977</td>
      <td>201.845075</td>
      <td>171.709724</td>
      <td>...</td>
      <td>73.506287</td>
      <td>72.633895</td>
      <td>81.891210</td>
      <td>98.919953</td>
      <td>425.821735</td>
      <td>2590.259701</td>
      <td>3263.843087</td>
      <td>269.547325</td>
      <td>1729.916912</td>
      <td>335.704242</td>
    </tr>
  </tbody>
</table>
<p>8 rows × 315 columns</p>
</div>



### Voeg alle 18 dataframes samen in 1, sorteer de index hiervan en sla het op als een CSV


```python
df = pd.concat([df1,df2,df3,df4,df5,df6,df7,df8,df9,df10,df11,df12,df13,df14,df15,df16,df17,df18])
df = df.sort_index()
```


```python
df.to_csv(('~/notebooks/AlleAirflowData_bruikbaar.csv'), sep=';')
```


```python
df.describe()
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
      <th>field_id</th>
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
      <td>26332.000000</td>
      <td>26332.000000</td>
      <td>26332.000000</td>
      <td>26332.000000</td>
      <td>26332.000000</td>
      <td>26332.000000</td>
      <td>26332.000000</td>
      <td>26332.000000</td>
      <td>26332.000000</td>
      <td>26332.000000</td>
      <td>...</td>
      <td>17792.000000</td>
      <td>17792.000000</td>
      <td>17792.000000</td>
      <td>17792.000000</td>
      <td>17792.000000</td>
      <td>17792.000000</td>
      <td>17792.000000</td>
      <td>10974.000000</td>
      <td>15950.000000</td>
      <td>10974.000000</td>
    </tr>
    <tr>
      <th>mean</th>
      <td>64.960927</td>
      <td>41.720844</td>
      <td>540.378681</td>
      <td>26.095972</td>
      <td>234.109353</td>
      <td>96.375786</td>
      <td>148.083618</td>
      <td>18.254260</td>
      <td>29.308762</td>
      <td>26.514727</td>
      <td>...</td>
      <td>11.446376</td>
      <td>13.232271</td>
      <td>12.718498</td>
      <td>14.145587</td>
      <td>82.217406</td>
      <td>534.366178</td>
      <td>604.797927</td>
      <td>24.043229</td>
      <td>136.049648</td>
      <td>42.384193</td>
    </tr>
    <tr>
      <th>std</th>
      <td>113.183186</td>
      <td>87.372677</td>
      <td>914.022787</td>
      <td>44.543457</td>
      <td>322.769810</td>
      <td>181.373660</td>
      <td>301.355679</td>
      <td>40.981309</td>
      <td>56.337814</td>
      <td>54.625591</td>
      <td>...</td>
      <td>20.297047</td>
      <td>22.983950</td>
      <td>20.680953</td>
      <td>23.479359</td>
      <td>150.128419</td>
      <td>959.929332</td>
      <td>1150.382165</td>
      <td>52.373362</td>
      <td>312.679246</td>
      <td>74.229546</td>
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
      <th>75%</th>
      <td>59.918319</td>
      <td>2.640592</td>
      <td>856.001959</td>
      <td>25.144295</td>
      <td>557.176077</td>
      <td>57.423945</td>
      <td>0.000000</td>
      <td>1.024165</td>
      <td>27.985481</td>
      <td>1.868576</td>
      <td>...</td>
      <td>15.669204</td>
      <td>15.151632</td>
      <td>19.738244</td>
      <td>19.804559</td>
      <td>48.013372</td>
      <td>496.556058</td>
      <td>115.622427</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>68.191997</td>
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




```python
df.head()
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
      <th>field_id</th>
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
      <th>2012-01-02 00:00:00</th>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
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
      <th>2012-01-02 01:00:00</th>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
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
      <th>2012-01-02 02:00:00</th>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
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
      <th>2012-01-02 03:00:00</th>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
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
      <th>2012-01-02 04:00:00</th>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
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




```python
df.tail()
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
      <th>field_id</th>
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
      <td>278.303077</td>
      <td>80.883988</td>
      <td>2670.651698</td>
      <td>100.070610</td>
      <td>616.703938</td>
      <td>396.123246</td>
      <td>791.745037</td>
      <td>0.000000</td>
      <td>67.808471</td>
      <td>124.848477</td>
      <td>...</td>
      <td>44.985611</td>
      <td>42.368281</td>
      <td>43.957134</td>
      <td>57.955154</td>
      <td>360.393865</td>
      <td>2518.617533</td>
      <td>0.000000</td>
      <td>53.543845</td>
      <td>1205.454855</td>
      <td>193.737564</td>
    </tr>
    <tr>
      <th>2016-04-30 11:00:00</th>
      <td>290.276317</td>
      <td>186.030538</td>
      <td>2691.992891</td>
      <td>102.254257</td>
      <td>693.079792</td>
      <td>531.886006</td>
      <td>818.591279</td>
      <td>79.079892</td>
      <td>72.402791</td>
      <td>132.533827</td>
      <td>...</td>
      <td>47.090122</td>
      <td>64.339045</td>
      <td>68.535954</td>
      <td>81.901524</td>
      <td>378.267075</td>
      <td>2522.945344</td>
      <td>2190.147357</td>
      <td>74.516885</td>
      <td>1282.249385</td>
      <td>177.349022</td>
    </tr>
    <tr>
      <th>2016-04-30 12:00:00</th>
      <td>294.782210</td>
      <td>239.816885</td>
      <td>2919.969381</td>
      <td>103.349679</td>
      <td>729.719584</td>
      <td>501.005546</td>
      <td>850.799723</td>
      <td>95.103667</td>
      <td>78.828923</td>
      <td>137.500557</td>
      <td>...</td>
      <td>23.772590</td>
      <td>62.063745</td>
      <td>74.321518</td>
      <td>87.848202</td>
      <td>373.327631</td>
      <td>2557.268491</td>
      <td>1086.324257</td>
      <td>59.957682</td>
      <td>990.272833</td>
      <td>209.955021</td>
    </tr>
    <tr>
      <th>2016-04-30 13:00:00</th>
      <td>298.003355</td>
      <td>202.689235</td>
      <td>2891.515667</td>
      <td>104.447727</td>
      <td>729.801051</td>
      <td>513.944023</td>
      <td>896.736093</td>
      <td>106.128642</td>
      <td>81.959462</td>
      <td>127.675495</td>
      <td>...</td>
      <td>25.973187</td>
      <td>54.807743</td>
      <td>73.159292</td>
      <td>87.460675</td>
      <td>290.154065</td>
      <td>2093.976234</td>
      <td>1448.531525</td>
      <td>88.003156</td>
      <td>960.392161</td>
      <td>316.398390</td>
    </tr>
    <tr>
      <th>2016-04-30 14:00:00</th>
      <td>287.792295</td>
      <td>182.998488</td>
      <td>2961.333562</td>
      <td>103.388590</td>
      <td>750.118364</td>
      <td>511.400410</td>
      <td>850.674229</td>
      <td>111.597485</td>
      <td>88.149501</td>
      <td>126.255879</td>
      <td>...</td>
      <td>27.279011</td>
      <td>54.123182</td>
      <td>71.451570</td>
      <td>85.497397</td>
      <td>392.278350</td>
      <td>2421.806322</td>
      <td>3121.503636</td>
      <td>81.329656</td>
      <td>1729.916912</td>
      <td>293.164160</td>
    </tr>
  </tbody>
</table>
<p>5 rows × 315 columns</p>
</div>




```python

```
