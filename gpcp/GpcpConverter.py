import pandas
from pandas import DataFrame
import xarray as xr
import os
import os.path

latitude = 30
longitude = 114

data_dir = os.path.join(os.path.dirname(__file__), "GpcpData")
files = os.listdir(data_dir)
files = [os.path.join(data_dir, f) for f in files if f.endswith(".nc")]
files.sort()

result = DataFrame([], columns=["date", "prec"], dtype="object")

for file in files:
    data_set = xr.open_dataset(file)
    df = data_set.to_dataframe()
    data_set.close()
    df = df.query(
        f"latitude == {latitude} & longitude == {longitude} & nv == 1")
    df = df.reset_index()
    df = df.drop(columns=["latitude", "longitude", "nv",
                 "lat_bounds", "lon_bounds", "time_bounds"])
    df = df.rename(columns={"time": "date", "precip": "prec"})
    result = pandas.concat([result, df], ignore_index=True)

result.to_csv("./out.csv")
