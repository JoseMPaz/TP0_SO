#!/bin/bash

echo "Iniciando server..."
gnome-terminal -- bash -c "cd server && ./bin/server; exec bash"

echo "Iniciando client..."
gnome-terminal -- bash -c "cd client && ./bin/client; exec bash"
