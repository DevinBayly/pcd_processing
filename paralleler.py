import multiprocessing as mp
import zipfile as zf

from pathlib import Path
import subprocess as sp
import os

ncpus = os.environ.get("SLURM_NTASKS")
print(ncpus)
def process_pcd(pcd):
  print(pcd)
  if not os.path.exists(pcd + "all_scans.bin"):
    print("would re run ")
    ##sp.run(f"./main '{pcd}'",shell=True)
  else :
      print("already run")

pcds = os.listdir("../finished")
print(pcds)

with mp.Pool(int(ncpus)) as pool:
  pool.map(process_pcd,["../finished/"+pcd for pcd in pcds if os.path.isdir("../finished"+pcd)])


all_scans = Path("../finished/").rglob("all_scans")
with zf.ZipFile("all_scans.zip","w") as ophile:
    for scan in all_scans:
        ophile.write(scan)