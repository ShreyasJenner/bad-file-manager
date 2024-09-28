#!/bin/bash

# wrapper script to ensure that script runs with bash
projdir=$(cat $HOME/.config/sfm/path.txt)
if ! [ $# -gt 0 ]; then
  bash "$projdir/sfm.sh"
else
  bash "$projdir/sfm.sh" $1
fi
