#!/bin/bash
dirpath="$(cd "$(dirname "$0")" && pwd)"
cd $dirpath

javah -d src/main/c/include -cp src/main/java/ org.fisco.bcos.sdk.jni.rpc.Rpc
echo "transfer org.fisco.bcos.sdk.jni.rpc.Rpc to jni"

javah -d src/main/c/include -cp src/main/java/ org.fisco.bcos.sdk.jni.amop.Amop
echo "transfer org.fisco.bcos.sdk.jni.rpc.Amop to jni"

javah -d src/main/c/include -cp src/main/java/ org.fisco.bcos.sdk.jni.event.EventSubscribe
echo "transfer org.fisco.bcos.sdk.jni.rpc.EventSubscribe to jni"