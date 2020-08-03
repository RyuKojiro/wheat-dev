#!/bin/sh

source relay.sh

echo "a00101a2" | xxd -r -p > $RELAYDEV
sleep .2
echo "a00100a1" | xxd -r -p > $RELAYDEV
