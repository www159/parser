#! /bin/bash
echo "identifier and keyword conginization test"

# compile
echo "compile start"
cd ..
make
echo "compile done!"

work_dir=$(cd $(dirname $0); pwd)
target=${work_dir}/build/bin/wwc
src_file=${work_dir}/run/test_ident_keyword.txt
dest_file=${work_dir}/run/test_ident_keyword.m
debug=${1}

rm -rf ${dest_file}

echo "program start"
echo "src file is ${src_file}"
echo "dest file is ${dest_file}"
if [ "${debug}" == 'd' ]
then
    gdb --args ${target} "-m${dest_file} ${src_file}"
    exit 0
fi

${target} -m "${dest_file} ${src_file}"

echo "program done!"