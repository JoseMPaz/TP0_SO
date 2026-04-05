#!/bin/bash

set -e

echo "Compilando..."
make -C server
make -C client

echo "Levantando server..."
gnome-terminal -- bash -c "cd server && ./bin/server; exec bash"

sleep 1  # 🔥 importante para que el server arranque primero

echo "Levantando client..."
gnome-terminal -- bash -c "cd client && ./bin/client; exec bash"
