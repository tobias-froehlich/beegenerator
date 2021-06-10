Installing GTest:

sudo aptitude install libgtest-dev
cd /usr/src/googletest/
sudo cmake .
sudo cmake --build . --target install

Building beegenerator:

Create directory beegenerator/build (if not exists).
In beegenerator/build/
rm -r *
cmake ..
make

Testing:

in beegenerator/bin/
./Test


