compile_path = "./src_builders/temp_compile.py"
compprog_path = "./lib/temp_compprog.h"

def create_header(lib, tag):
    gen_path = f"{lib}/generics.h"
    if_path = f"{lib}/interface.h"
    param_path = f"{lib}/{tag}/parameter.h"
    declare_path = f"{lib}/{tag}/declare.h"
    orig_snippet_path = f"{lib}/snippet.py"

    gen_code = "".join([line for line in open(gen_path, "r")])
    if_code = "".join([line for line in open(if_path, "r")])
    param_code = "".join([line for line in open(param_path, "r")])
    declare_code = "".join([line for line in open(declare_path, "r")])
    orig_snippet_code = "".join([line for line in open(orig_snippet_path, "r")])
    
    inst_path = f"{lib}/{tag}/instance.h"
    save_snippet_path = f"{lib}/{tag}/snippet.py"
    
    open(inst_path, "w").write((param_code + "\n" + gen_code).replace("TAG",tag))
    open(save_snippet_path, "w").write((orig_snippet_code).replace("TAG",tag))

    compile_code = "".join([line for line in open(compile_path, "r")])
    compile_code = compile_code.replace("//EMBEDPOINT", (declare_code + "\n" + if_code).replace("TAG",tag) + "\n//EMBEDPOINT")
    open(compile_path, "w").write(compile_code)

    include_code = "/".join(inst_path.split("/")[2:])
    include_code = f'#include "{include_code}"'
    compprog_code = "".join([line for line in open(compprog_path, "r")])
    compprog_code = compprog_code.replace("//EMBEDPOINT", include_code + "\n//EMBEDPOINT")
    open(compprog_path, "w").write(compprog_code)

create_header("./lib/data_structures/cheapq", "ll")
create_header("./lib/data_structures/cheapq", "lf")
create_header("./lib/data_structures/coset", "ll")
create_header("./lib/data_structures/coset", "lf")
create_header("./lib/data_structures/comultiset", "ll")
create_header("./lib/data_structures/comultiset", "lf")
