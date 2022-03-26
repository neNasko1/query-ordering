# query-ordering
An examination of query ordering methods.

The query-ordering methods are implemented in C++ for pure efficiency. 
The benchmarks are conducted with a python script, which uses [perf](https://man7.org/linux/man-pages/man1/perf.1.html) to measure running-times, cache-misses and branch-mispredictions. 

## Requirements
* Python3.9 or newer 
* C++ compiler, which supports C++ 20
* perf(1)
