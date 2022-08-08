# Folder structure

Expected folder location to be `/home/kelvin/repos/labs/k1a`, some have absolute paths inside.

```
compile.sh - script to compile and install everything, for development only
docs.py - script to generate docs and upload to https://docs.hdoc.io/157239n/k1a
Doxyfile - docs configuration
logs.txt - text file containing debugging print statements
setup.py - contains setup info of the extension
upload.sh - script to upload extension to PyPI

docs/ - all generated docs, to be synced with NY server
src/ - main source files
  main.cpp - extension definition, contains version number
  utils.cpp - contains bool `debug`. Set to true to print debug statements to logs.txt
  docs/ - folder containing detailed standalone docs file
```

# Development path

- Change cpp files as needed
- Run `./compile.sh` to compile everything and install the package
- Run `./docs.py` to generate docs and sync with server
- Commit everything to github
- Push new release to PyPI using `./upload.sh`
- Bump version number at `src/main.cpp`
