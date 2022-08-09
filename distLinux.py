#!/usr/bin/env python

from k1lib.imports import *

base = 'docker run -it --workdir /code --rm --name k1a_build --volume /home/kelvin/repos/labs/k1a:/code --user $(id -u):$(id -g) quay.io/pypa/manylinux_2_24_x86_64'


def build(ver):
    os.system(f"rm -r output")
    os.system(f"mkdir output")
    os.system(f"{base} /opt/python/{ver}/bin/pip wheel /code -w /code/output")
    os.system(f"{base} auditwheel repair /code/{ls('output') | item()} -w /code/dist")


os.system(f"rm -r build dist k1a.egg-info __pycache__")
os.system(f"mkdir dist")

cat("setup.py") | op().replace("sources=sources1", "sources=sources2").all() | deref() | file("setup.py")
os.system("./setup.py sdist")
cat("setup.py") | op().replace("sources=sources2", "sources=sources1").all() | deref() | file("setup.py")

build("cp37-cp37m")
build("cp38-cp38")
build("cp39-cp39")
build("cp310-cp310")

os.system(f"rm -r output")
