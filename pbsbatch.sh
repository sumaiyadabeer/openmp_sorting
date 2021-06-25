#!/bin/sh
#PBS -N col730A1
#PBS -P cse
#PBS -m bea
#PBS -M $USER@iitd.ac.in
#PBS -l select=1:ncpus=8
#PBS -l walltime=00:15:00
#PBS -o out
#PBS -e err

# After job starts, must goto working directory. 
# $PBS_O_WORKDIR is the directory from where the job is fired. 
echo "==============================="
echo $PBS_JOBID
cat $PBS_NODEFILE
echo "==============================="
cd $PBS_O_WORKDIR
echo $PBS_O_WORKDIR

module () {
        eval `/usr/share/Modules/$MODULE_VERSION/bin/modulecmd bash $*`
}


