#!/bin/bash -l
#SBATCH -q defq
#SBATCH -N 1
#SBATCH -n 1
#SBATCH -t 01:00:00
#SBATCH -J blockedmul
#SBATCH -o blockedmul.%j.out
#SBATCH -e blockedmul.%j.error
#SBATCH --exclude=gpu01

mpirun ./proj2 2048 1
mpirun ./proj2 2048 10
mpirun ./proj2 2048 16
mpirun ./proj2 2048 32
mpirun ./proj2 2048 64
mpirun ./proj2 2048 128
