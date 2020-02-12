#!/bin/bash -l
#SBATCH -J first_gpu_job


## Get one node, one CPU-GPU pair
#SBATCH -N 1
#SBATCH --ntasks-per-node=1
#SBATCH --gres=gpu:1


## Specify exec time, queue and output
#SBATCH --time=00:10:00
#SBATCH --partition=plgrid-gpu
#SBATCH --output=out_hello_gpu

## Select module and run task

cd $HOME/labwork4/gpu
./hello_gpu_app
