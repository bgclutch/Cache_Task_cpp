import subprocess
import glob
import os

lfu = "../../lfu/build/./cache"
belady = "../../belady/build/./cache"
test_dir = "input_files/"

output_file = "e2e_tests.out"

test_files = sorted(glob.glob(test_dir + "test_*.in"))

with open(output_file, 'w') as fout:

    for file in test_files:
        fout.write(f"{os.path.basename(file)}\nLFU cache result:\n")
        with open(file, 'r') as fin:
            input_data = fin.read()
            lfurun = subprocess.run(
            [lfu],
            input=input_data,
            text=True,
            capture_output=True)
            if lfurun.returncode != 0:
                fout.write(f"ERROR: {lfurun.stderr}\n")
            else:
                fout.write(lfurun.stdout)

            fout.write(f"Belady cache result:\n")
            beladyrun = subprocess.run(
            [belady],
            input=input_data,
            text=True,
            capture_output=True)
            if beladyrun.returncode != 0:
                fout.write(f"ERROR: {beladyrun.stderr}\n")
            else:
                fout.write(beladyrun.stdout)
