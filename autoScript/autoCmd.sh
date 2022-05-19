#!/bin/bash

echo "hello"
pwd
cd /home/x/code/HPGeSimulation/build || exit

# shellcheck disable=SC2129
./sim /home/x/code/HPGeSimulation/autoScript/2022-05-15/1_0_0_.mac >> /home/x/code/HPGeSimulation/autoScript/log.txt
./sim /home/x/code/HPGeSimulation/autoScript/2022-05-15/2_0_0_.mac >> /home/x/code/HPGeSimulation/autoScript/log.txt
./sim /home/x/code/HPGeSimulation/autoScript/2022-05-15/3_0_0_.mac >> /home/x/code/HPGeSimulation/autoScript/log.txt
./sim /home/x/code/HPGeSimulation/autoScript/2022-05-15/1_0_1_.mac >> /home/x/code/HPGeSimulation/autoScript/log.txt
./sim /home/x/code/HPGeSimulation/autoScript/2022-05-15/2_0_1_.mac >> /home/x/code/HPGeSimulation/autoScript/log.txt
./sim /home/x/code/HPGeSimulation/autoScript/2022-05-15/3_0_1_.mac >> /home/x/code/HPGeSimulation/autoScript/log.txt
#./sim /home/x/code/HPGeSimulation/autoScript/2022-05-14/2_0_2_.mac >> /home/x/code/HPGeSimulation/autoScript/log.txt
#./sim /home/x/code/HPGeSimulation/autoScript/2022-05-14/3_0_2_.mac >> /home/x/code/HPGeSimulation/autoScript/log.txt
echo "Finished"
