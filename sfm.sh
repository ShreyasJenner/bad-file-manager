#!/usr/bin/env bash

# get variables
projdir=$(cat $HOME/.config/sfm/path.txt)
logpath="$HOME/.config/sfm/log.txt"
bin="$projdir/bin/shitty-file-manager"

# run the file manager
if ! [ $# -gt 0 ]; then
  # if argument has not been passed, use current directory
  $bin $(pwd) 2>$logpath
else
  $bin $1 2>$logpath
fi

# create an array to check if file or directory has been passed
lines=()

# read the log file
while IFS= read -r line; do
  lines+=("$line")
done <"$logpath"

# check if file or directory has been selected
if [[ "${lines[0]}" == "DIR" ]]; then
  # if directory then open terminal
  cd "${lines[1]}"
  $TERM &
else
  # else open file
  xdg-open "${lines[1]}" &
fi
