echo "token write test start"

# compile
echo "compile start"
cd ..
make
echo "compile done!"

# define
work_dir=$(cd $(dirname $0); pwd)
target=${work_dir}/build/bin/wwc
src_file=${work_dir}/run/test_scanner.txt
default_dest_file=${src_file}.m
dest_file=${work_dir}/run/token_write.m
debug=${1}

rm -rf ${default_dest_file} ${dest_file}

# start
echo "program start"
echo "test single file"
echo "src file is ${src_file}"

if [ "${debug}" == "d" ]
then
gdb --args  ${target} "-m ${src_file}"
exit 0
fi

echo "write token to file ${default_dest_file}"

echo "test dest and src files"
echo "src file is ${src_file}"
echo "dest file is ${dest_file}"
${target} -m ${src_file}

echo "write token to file ${dest_file}"
# echo ${default_dest_file}
# if [ -e "$default_dest_file" ]; then
#     echo 1
#     exit 0;
# fi

if [ ! -e "${default_dest_file}" ]; then
    echo "error!"
    exit 1
fi
echo "test double files"


${target} -m "${dest_file} ${src_file}"
if [ ! -e ${dest_file} ]
then 
    echo "error!"
    exit 1
fi
echo "program done!"