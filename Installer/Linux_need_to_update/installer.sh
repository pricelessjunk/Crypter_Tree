#!/bin/bash

set -v
set -e

if [ ! -d /opt/crypter/ ]; then
    sudo cp -r crypter /opt/
    sudo chmod 755 -R /opt/crypter
    sudo chmod +x /opt/crypter/Crypter.sh
fi

if [ ! -f /usr/bin/crypter ]; then
    sudo ln -s /opt/crypter/Crypter.sh /usr/bin/crypter
fi

cp crypter.desktop /home/$(whoami)/.local/share/applications
mkdir -p /home/$(whoami)/.local/crypter/
cp crypter.cfg /home/$(whoami)/.config/crypter/crypter.cfg
