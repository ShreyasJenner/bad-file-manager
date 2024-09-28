#!/bin/bash

projdir=$(pwd)

echo "Building shitty file manager"
if [[ "$1" == "clean" ]]; then
  echo "Starting clean build"
  make clean
  make
fi

# remake the code file

# create the sfm directory in .config
echo "Creating sfm directory in .config"
mkdir -p $HOME/.config/sfm

# cd to sfm directory
echo "Changing directory to " $HOME/.config/sfm
cd $HOME/.config/sfm/

# store the proejct path in the directory
echo "Storing project directory path in path.txt"
echo "$projdir" >path.txt

# build sfm.sh in /usr/local/bin/
echo "Need sudo permission"
echo "Sudo permission received"
echo "Building sfm in /usr/local/bin"
sudo rm -f /usr/local/bin/sfm
sudo ln -s -f "$projdir/run.sh" /usr/local/bin/sfm

echo "Done"
