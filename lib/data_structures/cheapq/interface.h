typedef struct {
    int cap;
    int n;
    hq_data_t_TAG* q;
} cheapq_TAG;

cheapq_TAG *hq_init_TAG(int _length);
int hq_get_size_TAG(cheapq_TAG *hq);
hq_data_t_TAG hq_pop_TAG(cheapq_TAG *hq);
hq_data_t_TAG hq_top_TAG(cheapq_TAG *hq);
void hq_push_TAG(cheapq_TAG *hq, hq_data_t_TAG x);
