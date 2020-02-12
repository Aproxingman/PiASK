#!/bin/bash -l
#SBATCH -J first_gpu_job


## Get one node, one CPU-GPU pair
#SBATCH -N 1
#SBATCH --ntasks-per-node=1
#SBATCH --gres=gpu:1


## Specify exec time, queue and output
#SBATCH --time=00:10:00
#SBATCH --partition=plgrid-gpu
#SBATCH --output=out_fir_gpu

## Select module and run task


./fir_gpu_app
