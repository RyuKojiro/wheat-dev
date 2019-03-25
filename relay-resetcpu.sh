#!/bin/sh
echo "a00101a2" | xxd -r -p > /dev/cu.usbserial-40
sleep .2
echo "a00100a1" | xxd -r -p > /dev/cu.usbserial-40
