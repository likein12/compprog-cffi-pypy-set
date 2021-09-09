//lf=lf

typedef lf hq_data_t_lf;
#define HQ_CAP_DEFAULT 4

typedef struct {
    int cap;
    int n;
    hq_data_t_lf* q;
} cheapq_lf;

cheapq_lf* hq_init_lf(){
    cheapq_lf* hq = (cheapq_lf*)malloc(sizeof(cheapq_lf));
    hq->cap = HQ_CAP_DEFAULT;
    hq->n = 0;
    hq->q = (hq_data_t_lf*)malloc(hq->cap*sizeof(hq_data_t_lf));
    return hq;
}

int hq_get_size_lf(cheapq_lf* hq){
    return hq->n;
}

hq_data_t_lf* hq_extention_lf(cheapq_lf* hq){
    hq->cap *= 2;
    hq_data_t_lf* ptr = (hq_data_t_lf*)realloc(hq->q, (hq->cap)*sizeof(hq_data_t_lf));
    if (ptr==NULL) return NULL;
    hq->q = ptr;
    return hq->q;
}

hq_data_t_lf* hq_reduction_lf(cheapq_lf* hq){
    hq->cap /= 4;
    hq_data_t_lf* ptr = (hq_data_t_lf*)realloc(hq->q, (hq->cap)*sizeof(hq_data_t_lf));
    if (ptr==NULL) return NULL;
    hq->q = ptr;
    return hq->q;
}

hq_data_t_lf hq_pop_lf(cheapq_lf* hq){
    if ((hq->n)-1<=(hq->cap)/16 && (hq->n)>HQ_CAP_DEFAULT) hq_reduction_lf(hq);
    hq_data_t_lf* q = hq->q;
    int res = q[0];
    q[0] = q[hq->n-1]; 
    (hq->n)--;
    int n = hq->n;
    int now = 0;
    hq_data_t_lf tmp;
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

hq_data_t_lf hq_top_lf(cheapq_lf* hq){
    return hq->q[0];
}

void hq_push_lf(cheapq_lf* hq, hq_data_t_lf x){
    (hq->n)++;
    if ((hq->n)>(hq->cap)) hq_extention_lf(hq);
    hq_data_t_lf* q = hq->q;
    int now = hq->n-1;
    q[now] = x;
    hq_data_t_lf tmp;
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