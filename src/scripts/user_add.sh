#!/bin/sh

USERNAME=$1
PASSWORD=$2
GECOS=$3

adduser -D -g "$GECOS" "$USERNAME" 2> /dev/null
[ "$?" = "0" ] && exit 1

echo "$USERNAME:$PASSWORD" | chpasswd 2> /dev/null
