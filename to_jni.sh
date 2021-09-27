#!/bin/bash
dirpath="$(cd "$(dirname "$0")" && pwd)"
cd $dirpath

javah -d src/main/c/include -cp src/main/java/ org.fisco.bcos.sdk.rpc.Rpc
javah -d src/main/c/include -cp src/main/java/ org.fisco.bcos.sdk.amop.Amop
javah -d src/main/c/include -cp src/main/java/ org.fisco.bcos.sdk.event.EventSubscribe