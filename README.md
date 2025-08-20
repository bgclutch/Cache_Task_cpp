# LFU Cache
This project provides an implementation of LFU (Least Frequently Used) cache and<br>
Belady’s optimal cache algorithm in C++. It includes:

1. An implementation of the LFU cache
2. An implementation of Belady’s optimal cache algorithm
3. Python scripts for automated testing and comparison
   
## Installation:
Clone this repository, then reach the project directory:
```sh
https://github.com/bgclutch/Cache_Task_cpp.git
cd cache
```

## Building:
1. Navigate to ```lfu``` or ```belady``` directory:
```sh
cd lfu
```
Or
```sh
cd belady
```
2. Build the project:
 ```sh
cmake -B build
cmake --build build
```

## Usage: 
1. Navigate to the ```build``` folder inside either ```lfu``` or ```belady```:
```sh
cd build 
```
2. Then run command:
```sh
./cache
```

## Running tests:
1. Navigate to the ```tests``` directory:
```sh
cd tests/EndToEnd
```
2. Run default tests with the Python script:
```sh
python3 testrun.py
```
3. (Optional) Or ```regenerate``` test cases:
```sh
python3 testgen.py
```
And run it as in step 2.
