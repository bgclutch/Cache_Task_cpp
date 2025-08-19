import subprocess
import glob
import os

cache = "../../lfu/build/./cache"
test_dir = "input_files/"

output_file = "e2e_tests.out"

test_files = sorted(glob.glob(test_dir + "test_*.in"))

with open(output_file, 'w') as fout:

    for file in test_files:
        fout.write(f"{os.path.basename(file)} LFU cache result:\n")
        with open(file, 'r') as fin:
            process = subprocess.run(
            [cache],
            stdin=fin,
            text=True,
            capture_output=True)
        if process.returncode != 0:
            fout.write(f"ERROR: {process.stderr}\n")
        else:
            fout.write(process.stdout + "\n")
