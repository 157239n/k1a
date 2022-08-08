#!/usr/bin/env python3

from k1lib.imports import *
import datetime

# grabbing version from `src/main.cpp`

with open("src/main.cpp") as f:
    version = [l for l in f.readlines(
    ) if "std::string version" in l][0].split("=")[1].strip().strip(" ").strip(";").strip("\"")

# updating version text in `Doxygen` file


def f(e):
    if e.startswith("PROJECT_NUMBER"):
        return f"PROJECT_NUMBER = {version}"
    else:
        return e


cat("Doxyfile") | deref() | apply(f) | deref() | file("Doxyfile")

# actually generate docs

os.system("doxygen")

os.system(f"rm -r docs/latest")
os.system(f"rm -r docs/{version}")
os.system(f"cp -r html docs/latest")
os.system(f"mv html docs/{version}")

# updating LICENSE year

year = datetime.datetime.now().year
cat("LICENSE") | deref() | op().replace(
    f"{year-1}", f"{year}").all() | file("LICENSE")

print("Syncing to NY server...")

os.system(
    """ rsync -a --exclude={'*.ipynb_checkpoints','\.*','*.pth'} --delete --max-size=60m docs/ kelvin@mlexps.com:/production/k1a/code """)
