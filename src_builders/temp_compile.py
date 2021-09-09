from cffi import FFI
import os

ffibuilder = FFI()

# cdef() expects a single string declaring the C types, functions and
# globals needed to use the shared object. It must be in valid C syntax.
ffibuilder.cdef("""
typedef int Boolean;
typedef long long ll;
typedef double lf;

typedef ll hq_data_t_ll;
typedef struct {
    int cap;
    int n;
    hq_data_t_ll* q;
} cheapq_ll;

cheapq_ll *hq_init_ll(int _length);
int hq_get_size_ll(cheapq_ll *hq);
hq_data_t_ll hq_pop_ll(cheapq_ll *hq);
hq_data_t_ll hq_top_ll(cheapq_ll *hq);
void hq_push_ll(cheapq_ll *hq, hq_data_t_ll x);

typedef lf hq_data_t_lf;
typedef struct {
    int cap;
    int n;
    hq_data_t_lf* q;
} cheapq_lf;

cheapq_lf *hq_init_lf(int _length);
int hq_get_size_lf(cheapq_lf *hq);
hq_data_t_lf hq_pop_lf(cheapq_lf *hq);
hq_data_t_lf hq_top_lf(cheapq_lf *hq);
void hq_push_lf(cheapq_lf *hq, hq_data_t_lf x);

typedef ll cs_data_t_ll;

typedef struct cs_node_ll{
    cs_data_t_ll key;
    struct cs_node_ll* left;
    struct cs_node_ll* right;
    int rank;
    int size;
    int isR;
} cs_node_ll;

typedef struct {
    cs_node_ll* root;
    int size;
} coset_ll;

coset_ll* coset_init_ll();
void cs_clear_ll(coset_ll* cs);
int cs_get_size_ll(coset_ll* cs);
cs_node_ll* cs_max_ll(coset_ll* cs);
cs_node_ll* cs_min_ll(coset_ll* cs);
cs_node_ll* cs_lower_bound_ll(coset_ll* cs, cs_data_t_ll k);
cs_node_ll* cs_rlower_bound_ll(coset_ll* cs, cs_data_t_ll k);
cs_node_ll* cs_upper_bound_ll(coset_ll* cs, cs_data_t_ll k);
cs_node_ll* cs_rupper_bound_ll(coset_ll* cs, cs_data_t_ll k);
cs_node_ll* cs_find_ll(coset_ll* cs, cs_data_t_ll k);
void cs_insert_ll(coset_ll* cs, cs_data_t_ll k);
void cs_remove_ll(coset_ll* cs, cs_data_t_ll k);
cs_node_ll* cs_get_k_ll(coset_ll* cs, int k);

typedef lf cs_data_t_lf;

typedef struct cs_node_lf{
    cs_data_t_lf key;
    struct cs_node_lf* left;
    struct cs_node_lf* right;
    int rank;
    int size;
    int isR;
} cs_node_lf;

typedef struct {
    cs_node_lf* root;
    int size;
} coset_lf;

coset_lf* coset_init_lf();
void cs_clear_lf(coset_lf* cs);
int cs_get_size_lf(coset_lf* cs);
cs_node_lf* cs_max_lf(coset_lf* cs);
cs_node_lf* cs_min_lf(coset_lf* cs);
cs_node_lf* cs_lower_bound_lf(coset_lf* cs, cs_data_t_lf k);
cs_node_lf* cs_rlower_bound_lf(coset_lf* cs, cs_data_t_lf k);
cs_node_lf* cs_upper_bound_lf(coset_lf* cs, cs_data_t_lf k);
cs_node_lf* cs_rupper_bound_lf(coset_lf* cs, cs_data_t_lf k);
cs_node_lf* cs_find_lf(coset_lf* cs, cs_data_t_lf k);
void cs_insert_lf(coset_lf* cs, cs_data_t_lf k);
void cs_remove_lf(coset_lf* cs, cs_data_t_lf k);
cs_node_lf* cs_get_k_lf(coset_lf* cs, int k);

typedef ll cms_data_t_ll;

typedef struct cms_node_ll{
    cms_data_t_ll key;
    int count;
    struct cms_node_ll* left;
    struct cms_node_ll* right;
    int rank;
    int size;
    int isR;
} cms_node_ll;

typedef struct {
    cms_node_ll* root;
    int size;
} comultiset_ll;

comultiset_ll* comultiset_init_ll();
void cms_clear_ll(comultiset_ll* cms);
int cms_get_size_ll(comultiset_ll* cms);
cms_node_ll* cms_max_ll(comultiset_ll* cms);
cms_node_ll* cms_min_ll(comultiset_ll* cms);
cms_node_ll* cms_lower_bound_ll(comultiset_ll* cms, cms_data_t_ll k);
cms_node_ll* cms_rlower_bound_ll(comultiset_ll* cms, cms_data_t_ll k);
cms_node_ll* cms_upper_bound_ll(comultiset_ll* cms, cms_data_t_ll k);
cms_node_ll* cms_rupper_bound_ll(comultiset_ll* cms, cms_data_t_ll k);
cms_node_ll* cms_find_ll(comultiset_ll* cms, cms_data_t_ll k);
int cms_count_ll(cms_node_ll* cms, cms_data_t_ll k);
void cms_insert_ll(comultiset_ll* cms, cms_data_t_ll k, int count);
void cms_remove_ll(comultiset_ll* cms, cms_data_t_ll k, Boolean remove_all);
cms_node_ll* cms_get_k_ll(comultiset_ll* cms, int k);

typedef lf cms_data_t_lf;

typedef struct cms_node_lf{
    cms_data_t_lf key;
    int count;
    struct cms_node_lf* left;
    struct cms_node_lf* right;
    int rank;
    int size;
    int isR;
} cms_node_lf;

typedef struct {
    cms_node_lf* root;
    int size;
} comultiset_lf;

comultiset_lf* comultiset_init_lf();
void cms_clear_lf(comultiset_lf* cms);
int cms_get_size_lf(comultiset_lf* cms);
cms_node_lf* cms_max_lf(comultiset_lf* cms);
cms_node_lf* cms_min_lf(comultiset_lf* cms);
cms_node_lf* cms_lower_bound_lf(comultiset_lf* cms, cms_data_t_lf k);
cms_node_lf* cms_rlower_bound_lf(comultiset_lf* cms, cms_data_t_lf k);
cms_node_lf* cms_upper_bound_lf(comultiset_lf* cms, cms_data_t_lf k);
cms_node_lf* cms_rupper_bound_lf(comultiset_lf* cms, cms_data_t_lf k);
cms_node_lf* cms_find_lf(comultiset_lf* cms, cms_data_t_lf k);
int cms_count_lf(cms_node_lf* cms, cms_data_t_lf k);
void cms_insert_lf(comultiset_lf* cms, cms_data_t_lf k, int count);
void cms_remove_lf(comultiset_lf* cms, cms_data_t_lf k, Boolean remove_all);
cms_node_lf* cms_get_k_lf(comultiset_lf* cms, int k);


static ll scanner_ll();
static char* scanner_string(int n);
static void printer_ll_one(ll x);
static void printer_ll_array_v(ll* x, int n);
static void printer_ll_array_h(ll* x, int n);

""")

ffibuilder.set_source("_compprog_cffi",
"""
     #include "temp_compprog.h"   // the C header of the library
""")

if __name__ == "__main__":
    os.chdir("lib/")
    ffibuilder.compile(verbose=True)