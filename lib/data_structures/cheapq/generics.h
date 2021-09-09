#define HQ_CAP_DEFAULT 4

typedef struct {
    int cap;
    int n;
    hq_data_t_TAG* q;
} cheapq_TAG;

cheapq_TAG* hq_init_TAG(){
    cheapq_TAG* hq = (cheapq_TAG*)malloc(sizeof(cheapq_TAG));
    hq->cap = HQ_CAP_DEFAULT;
    hq->n = 0;
    hq->q = (hq_data_t_TAG*)malloc(hq->cap*sizeof(hq_data_t_TAG));
    return hq;
}

int hq_get_size_TAG(cheapq_TAG* hq){
    return hq->n;
}

hq_data_t_TAG* hq_extention_TAG(cheapq_TAG* hq){
    hq->cap *= 2;
    hq_data_t_TAG* ptr = (hq_data_t_TAG*)realloc(hq->q, (hq->cap)*sizeof(hq_data_t_TAG));
    if (ptr==NULL) return NULL;
    hq->q = ptr;
    return hq->q;
}

hq_data_t_TAG* hq_reduction_TAG(cheapq_TAG* hq){
    hq->cap /= 4;
    hq_data_t_TAG* ptr = (hq_data_t_TAG*)realloc(hq->q, (hq->cap)*sizeof(hq_data_t_TAG));
    if (ptr==NULL) return NULL;
    hq->q = ptr;
    return hq->q;
}

hq_data_t_TAG hq_pop_TAG(cheapq_TAG* hq){
    if ((hq->n)-1<=(hq->cap)/16 && (hq->n)>HQ_CAP_DEFAULT) hq_reduction_TAG(hq);
    hq_data_t_TAG* q = hq->q;
    int res = q[0];
    q[0] = q[hq->n-1]; 
    (hq->n)--;
    int n = hq->n;
    int now = 0;
    hq_data_t_TAG tmp;
    int ch;
    while (2*now+1<=n-1){
        if (2*now+2<=n-1) {
            if (q[2*now+1]<q[2*now+2]) ch = 2*now+1;
            else ch = 2*now+2;
        } else {
            ch = 2*now+1;
        }
        if (q[now] > q[ch]) {
            tmp = q[now];
            q[now] = q[ch];
            q[ch] = tmp;
            now = ch;
        } else {
            break;
        }             
    }        
    return res;
}

hq_data_t_TAG hq_top_TAG(cheapq_TAG* hq){
    return hq->q[0];
}

void hq_push_TAG(cheapq_TAG* hq, hq_data_t_TAG x){
    (hq->n)++;
    if ((hq->n)>(hq->cap)) hq_extention_TAG(hq);
    hq_data_t_TAG* q = hq->q;
    int now = hq->n-1;
    q[now] = x;
    hq_data_t_TAG tmp;
    int par;
    while (now>0) {
        par = (now-1)/2;
        if (q[par] > q[now]) {
            tmp = q[now];
            q[now] = q[par];
            q[par] = tmp;
            now = par;
        } else {
            break;
        }       
    }
}