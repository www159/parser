#!/bin/bash
target=build/bin/wwc
makefile_path=../makefile
m_token="file1.m file2.m"

cd ..
echo "start compiling..."
make
echo "compile done!"
${target} -m "${m_token}"