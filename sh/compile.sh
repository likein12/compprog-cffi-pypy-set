pypy3 ./src_builders/temp_compile.py
echo "recompiling with -O3 option..."
gcc -pthread -DNDEBUG -O3 -fPIC -I/opt/pypy3.6-v7.3.0-linux64/include -c ./lib/_compprog_cffi.c -o ./built_files/_compprog_cffi.o
echo "creating a so file..."
gcc -pthread -shared ./built_files/_compprog_cffi.o -o ./built_files/_compprog_cffi.pypy36-pp73-x86_64-linux-gnu.so
rm ./lib/_compprog_cffi.*