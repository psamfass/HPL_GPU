#!/bin/bash
# Job Name and Files (also --job-name)
#SBATCH -J hpl
#Output and error (also --output, --error):
#SBATCH -o ./%x.%j.out
#SBATCH -e ./%x.%j.err
#Initial working directory (also --chdir):
#SBATCH -D ./
# Wall clock limit:
#SBATCH --time=00:10:00
#SBATCH --no-requeue
# Setup of execution environment
#SBATCH --get-user-env
#SBATCH --exclusive
#SBATCH --partition=MI250
# Resource configuration
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=8


module load openblas
module load mpi/ompi-4.1.x

hpl_runscript=./run_xhplhip.sh

cp ../scripts/config/HPL_1GPU.dat HPL.dat

filename=HPL.dat

P=$(sed -n "11, 1p" ${filename} | awk '{print $1}')
Q=$(sed -n "12, 1p" ${filename} | awk '{print $1}')
np=$(($P*$Q))
echo ${np}
num_cpu_cores=$(lscpu | grep "Core(s)" | awk '{print $4}')
num_cpu_sockets=$(lscpu | grep Socket | awk '{print $2}')
total_cpu_cores=$(($num_cpu_cores*$num_cpu_sockets))

mpi_args="--map-by slot:PE=${total_cpu_cores} --bind-to core:overload-allowed --mca btl ^openib --mca pml ucx --report-bindings -x LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/rocm/lib ${mpi_args}"

export AMD_LOG_LEVEL=1
# For hybrid MPI+OpenMP jobs, thread affinity settings should be configured (e.g., via OMP_PLACES, OMP_PROC_BIND) 
mpirun -n ${np} ${mpi_args} ${hpl_runscript} # choose appropriate affinity settings for MPI here
