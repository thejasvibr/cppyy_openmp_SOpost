# Getting OpenMP paralel coding working with cppyy


## Background
Initially I wasn't able to get OpenMP code working. The pragmas were being 
ignored, or unexpected results were being returned. Despite following 
the instructions [here](https://cppyy.readthedocs.io/en/latest/installation.html#precompiled-header)
, I couldn't get the parallelised code to work. 

## What was done
Briefly, the instructions on the ```cppyy``` readthedocs explain that a special 
precompiled header must be created if an OpenMP enabled C++ compiler needs 
to be used. The steps include:

1. Putting the ```EXTRA_CLING_ARGS``` as an 
environmental variable (in this case ```EXTRA_CLING_ARGS=-fopenmp```
1. Running the code (also on the readthedocs page) to generate
the OpenMP enabled precompiled-header (using ```cppyy_backend.loader```
1. Export the second environmental variable ```CLING_STANDARD_PCH``` set to 
the absolute path of the precompiled header just generated. 

Having followed these steps - I had no luck with parallelising code. The error
was the same across three different OS's I tried on: Ubuntu 18, Linux Mint, 
Windows 11:
```
IncrementalExecutor::executeFunction: symbol '__kmpc_for_static_fini' unresolved while linking symbol '__cf_4'!
```

## Cling needs explicit OpenMP enabling
It was while searching around for answers that I found
[this presentation online](https://archive.fosdem.org/2021/schedule/event/interactive_openmp_mpi/attachments/slides/4470/export/events/attachments/interactive_openmp_mpi/slides/4470/presentation_terboven_hahnfeld.pdf).
Explicitly telling Cling where the ```libiomp5.so``` through a pragma
in the C++ code turns on parallellisation - and things work suddenly!

```
// Add this in the C++ code
#include <omp.h>
```

```
import cppyy
# load_libary tells which .dll or .so file to use for the -fopenmp flag
cppyy.load_library(<insert path to .so file in Unis and .dll file in Windows>) 
```

Thus now, run the python code in the command-line with 
```
$python example_pll_cppyy_code.py
```

### Where all this works

Tested on:
* Linux Mint 19.2 Cinnamon
* Windows 11 laptop 
* Ubuntu 18.04



