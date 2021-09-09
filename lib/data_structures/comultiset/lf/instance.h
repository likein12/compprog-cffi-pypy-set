//lf=lf

typedef lf cms_data_t_lf;

// AVL tree
typedef struct cms_node_lf {
    cms_data_t_lf key;
    int count;
    struct cms_node_lf* left;
    struct cms_node_lf* right;
    int rank;
    int size;
    int isR;    // L: -1, E: 0, R: 1
} cms_node_lf;

cms_node_lf* cms_new_node_lf(cms_data_t_lf key, int count){
    cms_node_lf* nd = (cms_node_lf*)malloc(sizeof(cms_node_lf));
    nd->key = key;
    nd->count = count;
    nd->left = NULL;
    nd->right = NULL;
    nd->rank = 0;
    nd->size = count;
    nd->isR = 0;
    return nd;
}

void cms_node_update_lf(cms_node_lf* nd){
    cms_node_lf* left = nd->left;
    cms_node_lf* right = nd->right;
    int lr, rr, ls, rs;
    if (left==NULL){
        lr = -1;
        ls = 0;
    } else {
        lr = left->rank;
        ls = left->size;
    }
    if (right==NULL){
        rr = -1;
        rs = 0;
    } else {
        rr = right->rank;
        rs = right->size;
    }
    nd->rank = 1+((lr>rr)?lr:rr);
    nd->size = ls+rs+nd->count;
    nd->isR = rr-lr;
}

typedef struct {
    cms_node_lf* root;
    int size;
} comultiset_lf;

comultiset_lf* comultiset_init_lf(){
    comultiset_lf* cms = (comultiset_lf*)malloc(sizeof(comultiset_lf));
    cms->root = NULL;
    cms->size = 0;
    return cms;
}

void _cms_clear_lf(cms_node_lf* nd){
    if (nd->left!=NULL) _cms_clear_lf(nd->left);
    if (nd->right!=NULL) _cms_clear_lf(nd->right);
    free(nd);
    return;
}

void cms_clear_lf(comultiset_lf* cms){
    if (cms->root==NULL) return;
    _cms_clear_lf(cms->root);
    cms->root = NULL;
    cms->size = 0;
}

int cms_get_size_lf(comultiset_lf* cms){
    return cms->size;
}

cms_node_lf* _cms_max_lf(cms_node_lf* nd){
    if (nd->right==NULL) return nd;
    return _cms_max_lf(nd->right);
}

cms_node_lf* cms_max_lf(comultiset_lf* cms){
    if (cms->root==NULL) return NULL;
    return _cms_max_lf(cms->root);
}

cms_node_lf* _cms_min_lf(cms_node_lf* nd){
    if (nd->left==NULL) return nd;
    return _cms_min_lf(nd->left);
}

cms_node_lf* cms_min_lf(comultiset_lf* cms){
    if (cms->root==NULL) return NULL;
    return _cms_min_lf(cms->root);
}

cms_node_lf* _cms_lower_bound_lf(cms_node_lf* nd, cms_data_t_lf k){
	if (nd==NULL) return NULL;
	if (nd->key < k) return _cms_lower_bound_lf(nd->right, k);
	return _cms_lower_bound_lf(nd->left, k)?:nd;
}

cms_node_lf* cms_lower_bound_lf(comultiset_lf* cms, cms_data_t_lf k){
    return _cms_lower_bound_lf(cms->root, k);
}

cms_node_lf* _cms_rlower_bound_lf(cms_node_lf* nd, cms_data_t_lf k){
	if (nd==NULL) return NULL;
	if (nd->key > k) return _cms_rlower_bound_lf(nd->left, k);
	return _cms_rlower_bound_lf(nd->right, k)?:nd;
}

cms_node_lf* cms_rlower_bound_lf(comultiset_lf* cms, cms_data_t_lf k){
    return _cms_rlower_bound_lf(cms->root, k);
}

cms_node_lf* _cms_upper_bound_lf(cms_node_lf* nd, cms_data_t_lf k){
	if(nd==NULL) return NULL;
	if(nd->key <= k) return _cms_upper_bound_lf(nd->right, k);
	return _cms_upper_bound_lf(nd->left, k)?:nd;
}

cms_node_lf* cms_upper_bound_lf(comultiset_lf* cms, cms_data_t_lf k){
    return _cms_upper_bound_lf(cms->root, k);
}

cms_node_lf* _cms_rupper_bound_lf(cms_node_lf* nd, cms_data_t_lf k){
	if(nd==NULL) return NULL;
	if(nd->key >= k) return _cms_rupper_bound_lf(nd->left, k);
	return _cms_rupper_bound_lf(nd->right, k)?:nd;
}

cms_node_lf* cms_rupper_bound_lf(comultiset_lf* cms, cms_data_t_lf k){
    return _cms_rupper_bound_lf(cms->root, k);
}

cms_node_lf* _cms_find_lf(cms_node_lf* nd, cms_data_t_lf k){
    if(nd==NULL) return NULL;
    if(nd->key==k) return nd;
    if(nd->key<k) return _cms_find_lf(nd->right, k);
    if(nd->key>k) return _cms_find_lf(nd->left, k);
}

cms_node_lf* cms_find_lf(comultiset_lf* cms, cms_data_t_lf k){
    return _cms_find_lf(cms->root, k);
}

int cms_count_lf(cms_node_lf* cms, cms_data_t_lf k){
    cms_node_lf* nd = _cms_find_lf(cms, k);
    if (nd==NULL) return 0;
    return nd->count;
}

cms_node_lf* cms_rotate_sl_lf(cms_node_lf* nd, cms_node_lf* ch){
    cms_node_lf* beta = ch->left;
    ch->left = nd;
    nd->right = beta;
    cms_node_update_lf(nd);
    cms_node_update_lf(ch);
    return ch;
}

cms_node_lf* cms_rotate_dr_lf(cms_node_lf* nd, cms_node_lf* ch){
    cms_node_lf *chch, *beta, *gamma;
    chch = ch->left;
    beta = chch->left;
    gamma = chch->right;
    chch->left = nd;
    chch->right = ch;
    nd->right = beta;
    ch->left = gamma;
    cms_node_update_lf(nd);
    cms_node_update_lf(ch);
    cms_node_update_lf(chch);
    return chch;
}

cms_node_lf* cms_rotate_sr_lf(cms_node_lf* nd, cms_node_lf* ch){
    cms_node_lf* beta = ch->right;
    ch->right = nd;
    nd->left = beta;
    cms_node_update_lf(nd);
    cms_node_update_lf(ch);
    return ch;
}

cms_node_lf* cms_rotate_dl_lf(cms_node_lf* nd, cms_node_lf* ch){
    cms_node_lf *chch, *beta, *gamma;
    chch = ch->right;
    beta = chch->right;
    gamma = chch->left;
    chch->right = nd;
    chch->left = ch;
    nd->left = beta;
    ch->right = gamma;
    cms_node_update_lf(nd);
    cms_node_update_lf(ch);
    cms_node_update_lf(chch);
    return chch;
}

cms_node_lf* _cms_insert_lf(cms_node_lf* nd, cms_data_t_lf k, int count){
    if(nd->key==k) {
        (nd->count) += count;
        nd->size += count;
        return nd;
    }
    cms_node_lf* ch;
    if(nd->key<k) {
        if (nd->right==NULL) {
            ch = cms_new_node_lf(k, count); 
            nd->right = ch;
        } else {
            ch = _cms_insert_lf(nd->right, k, count);
            nd->right = ch;
        }
        cms_node_update_lf(nd);
        if (nd->isR==2) {
            if (ch->isR==1) return cms_rotate_sl_lf(nd, ch);
            if (ch->isR==-1) return cms_rotate_dr_lf(nd, ch);
        }
        return nd;
    }
    else {
        if (nd->left==NULL) {
            ch = cms_new_node_lf(k, count); 
            nd->left = ch;
        } else {
            ch = _cms_insert_lf(nd->left, k, count);
            nd->left = ch;
        }
        cms_node_update_lf(nd);
        if (nd->isR==-2) {
            if (ch->isR==-1) return cms_rotate_sr_lf(nd, ch);
            if (ch->isR==1) return cms_rotate_dl_lf(nd, ch);
        }
        return nd;
    }
    exit(1);
    return NULL;
}

void cms_insert_lf(comultiset_lf* cms, cms_data_t_lf k, int count){
    if (cms->root==NULL){
        cms->root = cms_new_node_lf(k, count);
        cms->size = (cms->root)->size;
        return;
    }
    cms_node_lf* ptr = _cms_insert_lf(cms->root, k, count);
    if (ptr!=NULL) cms->root = ptr;
    cms->size = (cms->root)->size;
}

//これから
//削除したnodeの子が一つ→それをそのまま上げる
//二つ→左側の子孫の最大値を持ってくる
cms_node_lf* _cms_remove_max_lf(cms_node_lf* nd, cms_node_lf* targ){
    if (nd->right==NULL) {
        targ->key = nd->key;
        targ->count = nd->count;
        cms_node_lf* ch = nd->left;
        free(nd);
        return ch;
    }
    cms_node_lf *ch, *cha; 
    ch = _cms_remove_max_lf(nd->right, targ);
    nd->right = ch;
    
    cms_node_update_lf(nd);
    if (nd->isR==-2) {
        cha = nd->left;
        if (cha->isR<=0) return cms_rotate_sr_lf(nd, cha);
        if (cha->isR==1) return cms_rotate_dl_lf(nd, cha);
    }
    return nd;
}

cms_node_lf* _cms_remove_from_targ_lf(cms_node_lf* nd, Boolean remove_all){
    if (nd->count>1 && !remove_all){
        --(nd->count);
        --(nd->size);
        return nd;
    }
    cms_node_lf* left = nd->left;
    cms_node_lf* right = nd->right;
    if (left==NULL && right==NULL) {
        free(nd);
        return NULL;
    }
    if (left!=NULL && right!=NULL) {
        cms_node_lf* ch = _cms_remove_max_lf(left, nd);
        nd->left = ch;
        cms_node_update_lf(nd);
        if (nd->isR==2) {
            cms_node_lf* cha = nd->right;
            if (cha->isR>=0) return cms_rotate_sl_lf(nd, cha);
            if (cha->isR==-1) return cms_rotate_dr_lf(nd, cha);
        }
        return nd;
        
    }
    free(nd);
    if (left!=NULL) return left;
    else return right;
}


cms_node_lf* _cms_remove_lf(cms_node_lf* nd, cms_data_t_lf k, Boolean remove_all){
    if(nd->key==k) return _cms_remove_from_targ_lf(nd, remove_all);
    cms_node_lf *ch, *cha;
    if(nd->key<k) {
        if (nd->right==NULL) {
            return nd;
        } else {
            ch = _cms_remove_lf(nd->right, k, remove_all);
            nd->right = ch;
        }
        cms_node_update_lf(nd);
        if (nd->isR==-2) {
            cha = nd->left;
            if (cha->isR<=0) return cms_rotate_sr_lf(nd, cha);
            if (cha->isR==1) return cms_rotate_dl_lf(nd, cha);
        }
        return nd;
    }
    else {
        if (nd->left==NULL) {
            return nd;
        } else {
            ch = _cms_remove_lf(nd->left, k, remove_all);
            nd->left = ch;
        }
        cms_node_update_lf(nd);
        if (nd->isR==2) {
            cha = nd->right;
            if (cha->isR>=0) return cms_rotate_sl_lf(nd, cha);
            if (cha->isR==-1) return cms_rotate_dr_lf(nd, cha);
        }
        return nd;
    }
}

void cms_remove_lf(comultiset_lf* cms, cms_data_t_lf k, Boolean remove_all){
    cms->root = _cms_remove_lf(cms->root, k, remove_all);
    if (cms->root==NULL) cms->size = 0;
    else cms->size = (cms->root)->size;
}

cms_node_lf* _cms_get_k_lf(cms_node_lf* nd, int k, int l){
    int ls;
    if (nd->left!=NULL) ls = (nd->left)->size;
    else ls = 0;
    int count = nd->count;
    if (l+ls<k && k<=l+ls+count) return nd;
    if (l+ls>=k) return _cms_get_k_lf(nd->left, k, l);
    if (l+ls+count<k) return _cms_get_k_lf(nd->right, k, l+ls+1);
}

cms_node_lf* cms_get_k_lf(comultiset_lf* cms, int k){
    //assert (cms->root!=NULL);
    //assert ((cms->root)->size>k);
    return _cms_get_k_lf(cms->root, k+1, 0);
}