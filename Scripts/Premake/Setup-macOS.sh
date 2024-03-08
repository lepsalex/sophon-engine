#!/bin/bash

pushd %~dp0/../../
Vendor/Binaries/Premake/Linux/premake5 --file=Build.lua xcode4
popd
