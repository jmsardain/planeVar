#!/bin/bash

COMPILER=$(root-config --cxx)
FLAGS=$(root-config --cflags --libs)

# FastJet paths (matching ROOT configuration)
FASTJET_DIR="/data/jmsardain/BOOST2025/jetFormation/fastjet-3.5.1/../fastjet-install"
FASTJET_INCLUDE="-I${FASTJET_DIR}/include"
FASTJET_LIBS="-L${FASTJET_DIR}/lib -lfastjettools -lfastjet -lm"

# Set runtime library path
export LD_LIBRARY_PATH="${FASTJET_DIR}/lib:$LD_LIBRARY_PATH"

$COMPILER $FLAGS $FASTJET_INCLUDE $FASTJET_LIBS -Wl,-rpath,${FASTJET_DIR}/lib -g -O3 -Wall -Wextra -Wpedantic -fopenmp ./doAnal.cc ./Analysis.C -I. -o doAnal
