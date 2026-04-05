#!/bin/bash

echo "Compilando server..."
cd server || exit
make
cd ..

echo "Compilando client..."
cd client || exit
make
cd ..

echo "Build completo ✔"
