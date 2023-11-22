#!/bin/bash

export _OS_NAME=$1

cat grub.cfg | envsubst > "$2"