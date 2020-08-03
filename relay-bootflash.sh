#!/bin/sh

source relay.sh

echo "a00201a3" | xxd -r -p > $RELAYDEV
