#!/bin/bash
target=build/test/test_input
makefile_path=../makefile
m_token="file1.m file2.m"

echo "input test start"
cd ..
echo "compile start"
make
echo "compile done!"

echo "file paths are: ${m_token}"

${target} -m "${m_token}"
echo "input test done!"