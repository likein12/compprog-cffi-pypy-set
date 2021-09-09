typedef struct cms_node_TAG{
    cms_data_t_TAG key;
    int count;
    struct cms_node_TAG* left;
    struct cms_node_TAG* right;
    int rank;
    int size;
    int isR;
} cms_node_TAG;

typedef struct {
    cms_node_TAG* root;
    int size;
} comultiset_TAG;

comultiset_TAG* comultiset_init_TAG();
void cms_clear_TAG(comultiset_TAG* cms);
int cms_get_size_TAG(comultiset_TAG* cms);
cms_node_TAG* cms_max_TAG(comultiset_TAG* cms);
cms_node_TAG* cms_min_TAG(comultiset_TAG* cms);
cms_node_TAG* cms_lower_bound_TAG(comultiset_TAG* cms, cms_data_t_TAG k);
cms_node_TAG* cms_rlower_bound_TAG(comultiset_TAG* cms, cms_data_t_TAG k);
cms_node_TAG* cms_upper_bound_TAG(comultiset_TAG* cms, cms_data_t_TAG k);
cms_node_TAG* cms_rupper_bound_TAG(comultiset_TAG* cms, cms_data_t_TAG k);
cms_node_TAG* cms_find_TAG(comultiset_TAG* cms, cms_data_t_TAG k);
int cms_count_TAG(cms_node_TAG* cms, cms_data_t_TAG k);
void cms_insert_TAG(comultiset_TAG* cms, cms_data_t_TAG k, int count);
void cms_remove_TAG(comultiset_TAG* cms, cms_data_t_TAG k, Boolean remove_all);
cms_node_TAG* cms_get_k_TAG(comultiset_TAG* cms, int k);
