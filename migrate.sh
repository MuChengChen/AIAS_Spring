#!/bin/bash

cd $(dirname "$0")

ROOT="$PWD"

if [[ ! -d /workspace/projects/Lab07/src/main/scala/aias_lab7/Hw1 ]]; then
    echo clone Lab5 Hw4 to Lab7 Hw1 ......

    cp -r ../Lab05/src/main/scala/aias_lab5/Hw4/. src/main/scala/aias_lab7/Hw1

    cd src/main/scala/aias_lab7/Hw1

    for file in $(ls)
    do
        echo -e $file
        sed -i 's/aias_lab5.Hw4/aias_lab7.Hw1/' $file
    done
fi