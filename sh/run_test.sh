sh ./sh/compile.sh
python3 ./src_builders/source_builder.py COMPILE
echo "testing..."
echo "===input=================="
cat ./input/input.txt
echo "===output================="
pypy3 ./main.py LOCAL_TEST < ./input/input.txt
rm ./_compprog_cffi.*