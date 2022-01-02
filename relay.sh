RELAYDEV=`find /dev -name 'cu.usbserial-*210' 2> /dev/null`

if [ $RELAYDEV == "" ]
then
	RELAYDEV="NOT FOUND"
fi

echo "Relay device is $RELAYDEV"
