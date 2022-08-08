#!/usr/bin/env python3

from distutils.core import setup, Extension

try:
    with open("readme.md") as f:
        md = f.read()
except:
    md = ""

sources = [
    'src/main.cpp',
    'src/utils.cpp',
    'src/funcs.cpp',
    'src/StrIter.cpp',
    'src/StrIterCat.cpp',
    'src/StrIterInter.cpp',
]

module1 = Extension('k1a', sources=sources, language="c++",
                    extra_compile_args=["-O3"])

with open("src/main.cpp") as f:
    version = [l for l in f.readlines(
    ) if "std::string version" in l][0].split("=")[1].strip().strip(" ").strip(";").strip("\"")

setup(name='k1a',
      version=version,
      python_requires=">=3.0",
      description='Accelerated functionalities for k1lib',
      url="https://k1a.k1lib.com",
      author="Quang Ho",
      author_email="157239q@gmail.com",
      long_description=md,
      long_description_content_type="text/markdown",
      license="MIT",
      ext_modules=[module1])
