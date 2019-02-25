#!/bin/bash -l
#SBATCH -q defq
#SBATCH -N 1
#SBATCH -n 1
#SBATCH -t 00:40:00
#SBATCH -J blockedmul
#SBATCH -o blockedmul.%j.out
#SBATCH -e blockedmul.%j.error
#SBATCH --exclude=gpu01

echo "proj2_O0_gcc7:"
mpirun ./proj2_O0_gcc7 2048 64
echo "proj2_O1_gcc7:"
mpirun ./proj2_O1_gcc7 2048 64
echo "proj2_O2_gcc7:"
mpirun ./proj2_O2_gcc7 2048 64
echo "proj2_O3_gcc7:"
mpirun ./proj2_O3_gcc7 2048 64
echo "proj2_O0_gcc5:"
mpirun ./proj2_O0_gcc5 2048 64
echo "proj2_O1_gcc5:"
mpirun ./proj2_O1_gcc5 2048 64
echo "proj2_O2_gcc5:"
mpirun ./proj2_O2_gcc5 2048 64
echo "proj2_O3_gcc5:"
mpirun ./proj2_O3_gcc5 2048 64
