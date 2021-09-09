import base64
import sys
import re

print("building the source file for submission...")

if sys.argv[1]=="NOT_COMPILE":
    binary_path = "./bin/_compprog_cffi.pypy36-pp73-x86_64-linux-gnu.so"
elif sys.argv[1]=="COMPILE":
    binary_path = "./built_files/_compprog_cffi.pypy36-pp73-x86_64-linux-gnu.so"
else:
    print("argument error")

a = open(binary_path, "rb").read()
binary = base64.b85encode(a)

header = """import base64

binary = BINARY_CODE
open('./_compprog_cffi.pypy36-pp73-x86_64-linux-gnu.so','wb').write(base64.b85decode(binary))

"""

code = "\n".join([line.rstrip() for line in open("./draft/draft.py", "r")])

documents = '\n\n"""\nThis code was created from PyPy CFFI. (https://github.com/likein12/compprog-cffi-pypy-set)\n\n'

docs = []
for line in open("./lib/temp_compprog.h", "r"):
    if re.match(r'#include \".*\"', line):
        l,r = re.match(r'#include \".*\"', line).span()
        docs.append('```' + "./lib/" + line[l:r].split('\"')[1] + "\n")
        docs.append("".join([line1.replace('"', '\\"') for line1 in open("./lib/" + line[l:r].split('\"')[1], "r")]))
        docs.append('\n```\n')

docs.append('```' + "./lib/temp_compprog.h\n")
docs.append("".join([line1.replace('"', '\\"') for line1 in open("./src_builders/temp_compile.py", "r")]))
docs.append('\n```\n')

docs.append('```' + "./src_builders/temp_compile.py\n")
docs.append("".join([line1.replace('"', '\\"') for line1 in open("./src_builders/temp_compile.py", "r")]))
docs.append('\n```\n')
docs.append('\n"""\n')
documents = documents + "\n".join(docs)

src = header.replace("BINARY_CODE", str(binary)) + code + documents

open("./main.py", "w").write(src)

print("you can submit ./main.py")

try:
    import pyperclip
    pyperclip.copy(src)
    print("The source code has already been written in your clipboard! Paste!")
except:
    pass