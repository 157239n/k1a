# Folder structure

Expected folder location to be `/home/kelvin/repos/labs/k1a`, some have absolute paths inside.

```
compile.sh - script to compile and install everything, for development only
distLinux.py - script to generate source and linux binary distributions
distWin.cmd - script to generate windows binary distribution
docs.py - script to generate docs and upload to https://docs.hdoc.io/157239n/k1a
Doxyfile - docs configuration
logs.txt - text file containing debugging print statements
setup.py - contains setup info of the extension

dist/ - distributions
docs/ - all generated docs, to be synced with NY server
src/ - main source files
  main.cpp - extension definition, contains version number
  utils.cpp - contains bool `debug`. Set to true to print debug statements to logs.txt
  docs/ - folder containing detailed standalone docs file
```

# Development path

- Change cpp files as needed
- Run `./compile.sh` to compile everything and install the package
- Check if everything works
- Run `./docs.py` to generate docs and sync with server
- Commit everything to github
- Generate binary linux distributions by running `./distLinux.py`
- Open Windows VM, do `git pull`
- Generate binary windows distribution by running `distWin.cmd`
- Copy windows wheel to `dist/`. There should be several linux wheels, 1 windows wheel and 1 source distribution here.
- Push new release to PyPI using `twine upload dist/*`
- Bump version number at `src/main.cpp`
