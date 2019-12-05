#!/bin/bash
server=serwerfifo
klient=klientfifo

function createFifo {
	if [[ -e $klient ]]; then
	  rm $klient
	  mkfifo $klient
	  chmod 777 $klient
	else
	  mkfifo $klient
	  chmod 777 $klient
	fi
}

createFifo

echo $klient $2 > $server
read line < $klient
echo $line
