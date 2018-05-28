#!/bin/sh
cd "$( dirname "$0"  )"
#clear
rm -rf ./bin
mkdir ./bin
#compile
cc -flat_namespace -dynamiclib -o ./bin/libhook.dylib hook.c
cc demo.c -o ./bin/app
chmod -R +x ./bin
cd ./bin
#test
export DYLD_FORCE_FLAT_NAMESPACE=1
DYLD_INSERT_LIBRARIES=libhook.dylib ./app