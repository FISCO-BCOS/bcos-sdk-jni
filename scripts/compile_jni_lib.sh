#!/bin/bash
dirpath="$(cd "$(dirname "$0")" && pwd)"
cd ${dirpath}/../

# TODO: check java env

TARGET_LIB_NAME="fisco-bcos-c-jni"
METAINFO_NATIVE_PATH="${dirpath}/../src/main/resources/META-INF/native/"

echo " # Compile JNI dynamic library, Starting ==>> "

cd src/main/c/

[ -d build ] &&  {
    rm -rf build
    echo " == clean build "
}

[ -d bcos-cmake-scripts ] &&  {
    rm -rf bcos-cmake-scripts
    echo " == clean bcos-cmake-scripts "
}

mkdir -p build && cd build
cmake ../
make -j4

ls  | egrep -o ${TARGET_LIB_NAME}
if [ $? -eq 0 ]; then
    echo "Compile JNI dynamic library successfully."
    mkdir -p ${METAINFO_NATIVE_PATH}
    cp *${TARGET_LIB_NAME}* ${METAINFO_NATIVE_PATH}
else
    echo "Compile JNI dynamic library failed."
fi

echo " # Compile JNI dynamic library, Ending   <<== " 