import subprocess
import os
import sys
from pathlib import Path
from contextlib import contextmanager

@contextmanager
def cwd(newdir):
    curdir = os.getcwd()
    os.chdir(newdir)
    try:
        yield
    finally:
        os.chdir(curdir)

subdir = Path(os.getcwd()) / "modified"

def execute(subdir):
    with cwd(subdir):
        try:
            os.remove("prog")
        except FileNotFoundError:
            print(subdir, '::', "prog doesn't exist!")
            sys.exit(1)

        post = subprocess.run('make'.split(), capture_output=True)
        if post.returncode:
            print(subdir, '::', 'make failed!')
            print(subdir, '::', post.returncode)
            print(subdir, '::', post.stderr.decode())
            sys.exit(1)

        post = subprocess.run('./prog 512 ./prog'.split(), capture_output=True)
        return post.stdout.decode().strip()

original = execute('original')
modified = execute('modified')
assert modified == original, f'\n{modified=}\n{original=}'
