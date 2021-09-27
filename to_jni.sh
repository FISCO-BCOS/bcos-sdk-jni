#!/bin/bash
dirpath="$(cd "$(dirname "$0")" && pwd)"
cd $dirpath

javah -d src/main/c -cp src/main/java/ org.fisco.bcos.sdk.rpc.Rpc
javah -d src/main/c -cp src/main/java/ org.fisco.bcos.sdk.amop.Amop
javah -d src/main/c -cp src/main/java/ org.fisco.bcos.sdk.subscribe.EventSubscribe
javah -d src/main/c -cp src/main/java/ org.fisco.bcos.sdk.BcosSDK