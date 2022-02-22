#!/bin/sh
git pull
make
./maze
bash check.sh
git add .
git commit -m "testing program"
git push origin master
