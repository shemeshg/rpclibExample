
# movavg - moving average cpp utility

C++ utility, Adds colomn of the moving average

```bash
 ./movavg -h                              
Allowed options:
  -h [ --help ]         produce help message
  -e [ --showErr ]      show errors
  -l [ --len ] arg      set moving avg len, 0 for none moving, default 7
  -d [ --coldelim ] arg set column delimiter, default ',' 
  -n [ --colnum ] arg   set column number, default 0
  --nullstr arg         set null string, default 'null' 
```

## Building

1. install boot with `apt-get install boost` or on mac `brew install boost`
2. you might want also to install `apt-get install googletest` or on mac `brew install googletest`
or just remark the `add_subdirectory(test)` in the `CMakeLists.txt`

3. cmake the project

```bash
git clone https://github.com/shemeshg/movavg.git
cd movavg
mkdir build
cd build
cmake ..
make

cd main
./movavg -h
```

it is linked staticlly, so just copy the file `movavg` anywhere youd like.

## Example of usage

```bash
# curl https://covid.ourworldindata.org/data/owid-covid-data.json --output data.json
curl https://raw.githubusercontent.com/owid/covid-19-data/master/public/data/owid-covid-data.json --output data.json
cat data.json| jq '.["ISR"].data'  | jq -r '.[] | {date, hosp_patients, icu_patients_per_million, new_deaths_per_million} |join(",") '  > list.txt
cat list.txt|./movavg -l 7 -n 1|./movavg -l 10 -n 2|./movavg -l 10 -n 3
```

# See also

* Refer to [this blog post](http://kaizou.org/2014/11/gtest-cmake/) for a detailed explaination of how it works.
* Licence MIT.
