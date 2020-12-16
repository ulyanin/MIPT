#!/bin/bash

head -n 1000000 data/LOTR | ./mapper.sh | sort | awk -f ./reducer.awk
