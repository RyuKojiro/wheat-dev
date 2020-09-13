#!/bin/sh

./relay-bootrom.sh
./relay-resetcpu.sh
./is-loader-up.exp
exit $?
