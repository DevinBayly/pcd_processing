import multiprocessing as mp
import subprocess as sp
import os

ncpus = os.environ.get("SLURM_NTASKS")
print(ncpus)
def process_pcd(pcd):
  sp.run(f"./main {pcd}",shell=True)

pcds = os.listdir("../finished")


with mp.Pool(int(ncpus)) as pool:
  pool.map(process_pcd,["../finished/"+pcd for pcd in pcds])
