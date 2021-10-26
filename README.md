# YGM Tutorial

Tutorial Repostiory for [YGM](https://github.com/LLNL/ygm)

## Run YGM on Binder

To launch Binder, click the button below:

[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/LLNL/ygm-tutorial.git/HEAD)


After Binder is launched, open **Terminal**.
Then,

```
# Setup environmental variables
source setup.sh

# Get YGM and build
git clone https://github.com/LLNL/ygm.git
cd ygm
mkdir build
cd build
cmake ../
make

# OpenMPI is available on the system.
# To launch an example program, for example:
mpirun -np 4 ./examples/howdy_world
```

## NOTICE and Release

[NOTICE](NOTICE)

LLNL-CODE-789122
