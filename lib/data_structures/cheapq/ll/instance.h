//ll=ll

typedef ll hq_data_t_ll;
#define HQ_CAP_DEFAULT 4

typedef struct {
    int cap;
    int n;
    hq_data_t_ll* q;
} cheapq_ll;

cheapq_ll* hq_init_ll(){
    cheapq_ll* hq = (cheapq_ll*)malloc(sizeof(cheapq_ll));
    hq->cap = HQ_CAP_DEFAULT;
    hq->n = 0;
    hq->q = (hq_data_t_ll*)malloc(hq->cap*sizeof(hq_data_t_ll));
    return hq;
}

int hq_get_size_ll(cheapq_ll* hq){
    return hq->n;
}

hq_data_t_ll* hq_extention_ll(cheapq_ll* hq){
    hq->cap *= 2;
    hq_data_t_ll* ptr = (hq_data_t_ll*)realloc(hq->q, (hq->cap)*sizeof(hq_data_t_ll));
    if (ptr==NULL) return NULL;
    hq->q = ptr;
    return hq->q;
}

hq_data_t_ll* hq_reduction_ll(cheapq_ll* hq){
    hq->cap /= 4;
    hq_data_t_ll* ptr = (hq_data_t_ll*)realloc(hq->q, (hq->cap)*sizeof(hq_data_t_ll));
    if (ptr==NULL) return NULL;
    hq->q = ptr;
    return hq->q;
}

hq_data_t_ll hq_pop_ll(cheapq_ll* hq){
    if ((hq->n)-1<=(hq->cap)/16 && (hq->n)>HQ_CAP_DEFAULT) hq_reduction_ll(hq);
    hq_data_t_ll* q = hq->q;
    int res = q[0];
    q[0] = q[hq->n-1]; 
    (hq->n)--;
    int n = hq->n;
    int now = 0;
    hq_data_t_ll tmp;
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

hq_data_t_ll hq_top_ll(cheapq_ll* hq){
    return hq->q[0];
}

void hq_push_ll(cheapq_ll* hq, hq_data_t_ll x){
    (hq->n)++;
    if ((hq->n)>(hq->cap)) hq_extention_ll(hq);
    hq_data_t_ll* q = hq->q;
    int now = hq->n-1;
    q[now] = x;
    hq_data_t_ll tmp;
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