#!/bin/sh

username=$1
password=$2
gecos=$3

adduser -D -g "$gecos" "$username" 2> /dev/null
[ "$?" = "0" ] && exit 1

echo "$username:$password" | chpasswd 2> /dev/null
