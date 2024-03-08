#!/bin/bash

pushd %~dp0/../../
Vendor/Binaries/Premake/Linux/premake5 --cc=clang --file=Build.lua gmake2
popd
