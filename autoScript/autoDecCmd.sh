#!/bin/bash

echo "auto Detection start"
pwd
cd /home/x/code/HPGeSimulation/build || exit

dir=/home/x/code/HPGeSimulation/autoScript/2022-05-18

time=$(date "+ %Y%m%d")
echo "$time"

for file in "$dir"/*.mac
do
  ./sim "$file" >> /home/x/code/HPGeSimulation/autoScript/"$time".txt
  echo  "$file completed"
done