from _compprog_cffi import ffi, lib

comultiset_init = lib.comultiset_init_ll

insert =  lib.cms_insert_ll
remove =  lib.cms_remove_ll
count = lib.cms_count_ll
get_s = lib.cms_get_size_ll
clear = lib.cms_clear_ll
get_min = lib.cms_min_ll
get_max = lib.cms_max_ll
upper_bound = lib.cms_upper_bound_ll
rupper_bound = lib.cms_rupper_bound_ll
get_k = lib.cms_get_k_ll

scan = lib.scanner_ll
prin = lib.printer_ll_one

Q = scan()
 
cms = comultiset_init()
 
for i in range(Q):
    t,x = scan(), scan()
    if t==1:
        insert(cms,x,1)
    else:
        k = get_k(cms,x-1).key
        print(k)
        remove(cms,k,False)
