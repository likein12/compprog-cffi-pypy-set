typedef struct cs_node_TAG{
    cs_data_t_TAG key;
    struct cs_node_TAG* left;
    struct cs_node_TAG* right;
    int rank;
    int size;
    int isR;
} cs_node_TAG;

typedef struct {
    cs_node_TAG* root;
    int size;
} coset_TAG;

coset_TAG* coset_init_TAG();
void cs_clear_TAG(coset_TAG* cs);
int cs_get_size_TAG(coset_TAG* cs);
cs_node_TAG* cs_max_TAG(coset_TAG* cs);
cs_node_TAG* cs_min_TAG(coset_TAG* cs);
cs_node_TAG* cs_lower_bound_TAG(coset_TAG* cs, cs_data_t_TAG k);
cs_node_TAG* cs_rlower_bound_TAG(coset_TAG* cs, cs_data_t_TAG k);
cs_node_TAG* cs_upper_bound_TAG(coset_TAG* cs, cs_data_t_TAG k);
cs_node_TAG* cs_rupper_bound_TAG(coset_TAG* cs, cs_data_t_TAG k);
cs_node_TAG* cs_find_TAG(coset_TAG* cs, cs_data_t_TAG k);
void cs_insert_TAG(coset_TAG* cs, cs_data_t_TAG k);
void cs_remove_TAG(coset_TAG* cs, cs_data_t_TAG k);
cs_node_TAG* cs_get_k_TAG(coset_TAG* cs, int k);
