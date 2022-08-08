
# for dev only

rm -r build
rm -r dist
rm -r k1a.egg-info

pip uninstall -y k1a

./setup.py install


