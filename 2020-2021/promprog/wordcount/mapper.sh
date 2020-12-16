#!/bin/bash

while read line; do
    for word in $line; do
        echo "$word 1"
    done
done
