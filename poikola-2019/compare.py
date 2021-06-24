import subprocess
import os
import sys
from pathlib import Path
from contextlib import contextmanager
from tqdm import tqdm

@contextmanager
def cwd(newdir):
    curdir = os.getcwd()
    os.chdir(newdir)
    try:
        yield
    finally:
        os.chdir(curdir)

subdir = Path(os.getcwd()) / "modified"

def execute(subdir, hash_size):
    with cwd(subdir):
        try:
            os.remove("prog")
        except FileNotFoundError:
            if input(f"{subdir}/prog doesn't exist! Continue? ") not in ("y", "Y", "yes", "Yes"):
                sys.exit(1)

        post = subprocess.run("make".split(), capture_output=True)
        if post.returncode:
            print(subdir, "::", "make failed!")
            print(subdir, "::", post.returncode)
            print(subdir, "::", post.stderr.decode())
            sys.exit(1)

        post = subprocess.run(f"./prog {hash_size * 8} ../compiled_binary".split(), capture_output=True)
        return post.stdout.decode().strip()


for hash_size in tqdm(range(4, 100)):
    original = execute("original", hash_size)
    modified = execute("modified", hash_size)
    assert modified == original, f"\n{modified=}\n{original=}"
