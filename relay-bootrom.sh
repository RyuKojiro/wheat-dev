#!/bin/sh

source relay.sh

echo "a00200a2" | xxd -r -p > $RELAYDEV
