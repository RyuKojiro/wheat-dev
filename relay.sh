RELAYDEV="NOT FOUND"
if [ -e "/dev/cu.usbserial-11210" ]
then
	RELAYDEV="/dev/cu.usbserial-11210"
fi

if [ -e "/dev/cu.usbserial-1210" ]
then
	RELAYDEV="/dev/cu.usbserial-1210"
fi

echo "Relay device is $RELAYDEV"
