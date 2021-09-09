//lf=ll

typedef lf cs_data_t_lf;

// AVL tree
typedef struct cs_node_lf {
    cs_data_t_lf key;
    struct cs_node_lf* left;
    struct cs_node_lf* right;
    int rank;
    int size;
    int isR;    // L: -1, E: 0, R: 1
} cs_node_lf;

cs_node_lf* cs_new_node_lf(cs_data_t_lf key){
    cs_node_lf* nd = (cs_node_lf*)malloc(sizeof(cs_node_lf));
    nd->key = key;
    nd->left = NULL;
    nd->right = NULL;
    nd->rank = 0;
    nd->size = 1;
    nd->isR = 0;
    return nd;
}

void cs_node_update_lf(cs_node_lf* nd){
    cs_node_lf* left = nd->left;
    cs_node_lf* right = nd->right;
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
    nd->size = ls+rs+1;
    nd->isR = rr-lr;
}

typedef struct {
    cs_node_lf* root;
    int size;
} coset_lf;

coset_lf* coset_init_lf(){
    coset_lf* cs = (coset_lf*)malloc(sizeof(coset_lf));
    cs->root = NULL;
    cs->size = 0;
    return cs;
}

void _cs_clear_lf(cs_node_lf* nd){
    if (nd->left!=NULL) _cs_clear_lf(nd->left);
    if (nd->right!=NULL) _cs_clear_lf(nd->right);
    free(nd);
    return;
}

void cs_clear_lf(coset_lf* cs){
    if (cs->root==NULL) return;
    _cs_clear_lf(cs->root);
    cs->root = NULL;
    cs->size = 0;
}

int cs_get_size_lf(coset_lf* cs){
    return cs->size;
}

cs_node_lf* _cs_max_lf(cs_node_lf* nd){
    if (nd->right==NULL) return nd;
    return _cs_max_lf(nd->right);
}

cs_node_lf* cs_max_lf(coset_lf* cs){
    if (cs->root==NULL) return NULL;
    return _cs_max_lf(cs->root);
}

cs_node_lf* _cs_min_lf(cs_node_lf* nd){
    if (nd->left==NULL) return nd;
    return _cs_min_lf(nd->left);
}

cs_node_lf* cs_min_lf(coset_lf* cs){
    if (cs->root==NULL) return NULL;
    return _cs_min_lf(cs->root);
}

cs_node_lf* _cs_lower_bound_lf(cs_node_lf* nd, cs_data_t_lf k){
	if (nd==NULL) return NULL;
	if (nd->key < k) return _cs_lower_bound_lf(nd->right, k);
	return _cs_lower_bound_lf(nd->left, k)?:nd;
}

cs_node_lf* cs_lower_bound_lf(coset_lf* cs, cs_data_t_lf k){
    return _cs_lower_bound_lf(cs->root, k);
}

cs_node_lf* _cs_rlower_bound_lf(cs_node_lf* nd, cs_data_t_lf k){
	if (nd==NULL) return NULL;
	if (nd->key > k) return _cs_rlower_bound_lf(nd->left, k);
	return _cs_rlower_bound_lf(nd->right, k)?:nd;
}

cs_node_lf* cs_rlower_bound_lf(coset_lf* cs, cs_data_t_lf k){
    return _cs_rlower_bound_lf(cs->root, k);
}

cs_node_lf* _cs_upper_bound_lf(cs_node_lf* nd, cs_data_t_lf k){
	if(nd==NULL) return NULL;
	if(nd->key <= k) return _cs_upper_bound_lf(nd->right, k);
	return _cs_upper_bound_lf(nd->left, k)?:nd;
}

cs_node_lf* cs_upper_bound_lf(coset_lf* cs, cs_data_t_lf k){
    return _cs_upper_bound_lf(cs->root, k);
}

cs_node_lf* _cs_rupper_bound_lf(cs_node_lf* nd, cs_data_t_lf k){
	if(nd==NULL) return NULL;
	if(nd->key >= k) return _cs_rupper_bound_lf(nd->left, k);
	return _cs_rupper_bound_lf(nd->right, k)?:nd;
}

cs_node_lf* cs_rupper_bound_lf(coset_lf* cs, cs_data_t_lf k){
    return _cs_rupper_bound_lf(cs->root, k);
}

cs_node_lf* _cs_find_lf(cs_node_lf* nd, cs_data_t_lf k){
    if(nd==NULL) return NULL;
    if(nd->key==k) return nd;
    if(nd->key<k) return _cs_find_lf(nd->right, k);
    if(nd->key>k) return _cs_find_lf(nd->left, k);
}

cs_node_lf* cs_find_lf(coset_lf* cs, cs_data_t_lf k){
    return _cs_find_lf(cs->root, k);
}

cs_node_lf* cs_rotate_sl_lf(cs_node_lf* nd, cs_node_lf* ch){
    cs_node_lf* beta = ch->left;
    ch->left = nd;
    nd->right = beta;
    cs_node_update_lf(nd);
    cs_node_update_lf(ch);
    return ch;
}

cs_node_lf* cs_rotate_dr_lf(cs_node_lf* nd, cs_node_lf* ch){
    cs_node_lf *chch, *beta, *gamma;
    chch = ch->left;
    beta = chch->left;
    gamma = chch->right;
    chch->left = nd;
    chch->right = ch;
    nd->right = beta;
    ch->left = gamma;
    cs_node_update_lf(nd);
    cs_node_update_lf(ch);
    cs_node_update_lf(chch);
    return chch;
}

cs_node_lf* cs_rotate_sr_lf(cs_node_lf* nd, cs_node_lf* ch){
    cs_node_lf* beta = ch->right;
    ch->right = nd;
    nd->left = beta;
    cs_node_update_lf(nd);
    cs_node_update_lf(ch);
    return ch;
}

cs_node_lf* cs_rotate_dl_lf(cs_node_lf* nd, cs_node_lf* ch){
    cs_node_lf *chch, *beta, *gamma;
    chch = ch->right;
    beta = chch->right;
    gamma = chch->left;
    chch->right = nd;
    chch->left = ch;
    nd->left = beta;
    ch->right = gamma;
    cs_node_update_lf(nd);
    cs_node_update_lf(ch);
    cs_node_update_lf(chch);
    return chch;
}

cs_node_lf* _cs_insert_lf(cs_node_lf* nd, cs_data_t_lf k){
    if(nd->key==k) return NULL;
    cs_node_lf* ch;
    if(nd->key<k) {
        if (nd->right==NULL) {
            ch = cs_new_node_lf(k); 
            nd->right = ch;
        } else {
            ch = _cs_insert_lf(nd->right, k);
            if (ch==NULL) return NULL;
            nd->right = ch;
        }
        ++(nd->size);
        if (nd->rank==ch->rank+2) return nd;
        if (nd->rank==ch->rank+1) {
            if (nd->isR==-1) nd->isR = 0;
            return nd; 
        }
        if (nd->rank==ch->rank && nd->isR==0) {
            ++(nd->rank);
            nd->isR = 1;
            return nd;
        }
        ++(nd->rank);
        if (ch->isR==1) return cs_rotate_sl_lf(nd, ch);
        if (ch->isR==-1) return cs_rotate_dr_lf(nd, ch);
    }
    else {
        if (nd->left==NULL) {
            ch = cs_new_node_lf(k); 
            nd->left = ch;
        } else {
            ch = _cs_insert_lf(nd->left, k);
            if (ch==NULL) return NULL;
            nd->left = ch;
        }
        ++(nd->size);
        if (nd->rank==ch->rank+2) return nd;
        if (nd->rank==ch->rank+1) {
            if (nd->isR==1) nd->isR = 0;
            return nd;
        } 
        if (nd->rank==ch->rank && nd->isR==0) {
            ++(nd->rank);
            nd->isR = -1;
            return nd;
        }
        ++(nd->rank);
        if (ch->isR==-1) return cs_rotate_sr_lf(nd, ch);
        if (ch->isR==1) return cs_rotate_dl_lf(nd, ch);
    }
    exit(1);
    return NULL;
}

void cs_insert_lf(coset_lf* cs, cs_data_t_lf k){
    if (cs->root==NULL){
        cs->root = cs_new_node_lf(k);
        cs->size = (cs->root)->size;
        return;
    }
    cs_node_lf* ptr = _cs_insert_lf(cs->root, k);
    if (ptr!=NULL) cs->root = ptr;
    cs->size = (cs->root)->size;
}

//これから
//削除したnodeの子が一つ→それをそのまま上げる
//二つ→左側の子孫の最大値を持ってくる
cs_node_lf* _cs_remove_max_lf(cs_node_lf* nd, cs_node_lf* targ){
    if (nd->right==NULL) {
        targ->key = nd->key;
        cs_node_lf* ch = nd->left;
        free(nd);
        return ch;
    }
    cs_node_lf *ch, *cha; 
    ch = _cs_remove_max_lf(nd->right, targ);
    nd->right = ch;
    
    cs_node_update_lf(nd);
    if (nd->isR==-2) {
        cha = nd->left;
        if (cha->isR<=0) return cs_rotate_sr_lf(nd, cha);
        if (cha->isR==1) return cs_rotate_dl_lf(nd, cha);
    }
    return nd;
}

cs_node_lf* _cs_remove_from_targ_lf(cs_node_lf* nd){
    cs_node_lf* left = nd->left;
    cs_node_lf* right = nd->right;
    if (left==NULL && right==NULL) {
        free(nd);
        return NULL;
    }
    if (left!=NULL && right!=NULL) {
        cs_node_lf* ch = _cs_remove_max_lf(left, nd);
        nd->left = ch;
        cs_node_update_lf(nd);
        if (nd->isR==2) {
            cs_node_lf* cha = nd->right;
            if (cha->isR>=0) return cs_rotate_sl_lf(nd, cha);
            if (cha->isR==-1) return cs_rotate_dr_lf(nd, cha);
        }
        return nd;
        
    }
    free(nd);
    if (left!=NULL) return left;
    else return right;
}


cs_node_lf* _cs_remove_lf(cs_node_lf* nd, cs_data_t_lf k){
    if(nd->key==k) return _cs_remove_from_targ_lf(nd);
    cs_node_lf *ch, *cha;
    if(nd->key<k) {
        if (nd->right==NULL) {
            return nd;
        } else {
            ch = _cs_remove_lf(nd->right, k);
            nd->right = ch;
        }
        cs_node_update_lf(nd);
        if (nd->isR==-2) {
            cha = nd->left;
            if (cha->isR<=0) return cs_rotate_sr_lf(nd, cha);
            if (cha->isR==1) return cs_rotate_dl_lf(nd, cha);
        }
        return nd;
    }
    else {
        if (nd->left==NULL) {
            return nd;
        } else {
            ch = _cs_remove_lf(nd->left, k);
            nd->left = ch;
        }
        cs_node_update_lf(nd);
        if (nd->isR==2) {
            cha = nd->right;
            if (cha->isR>=0) return cs_rotate_sl_lf(nd, cha);
            if (cha->isR==-1) return cs_rotate_dr_lf(nd, cha);
        }
        return nd;
    }
}

void cs_remove_lf(coset_lf* cs, cs_data_t_lf k){
    cs->root = _cs_remove_lf(cs->root, k);
    if (cs->root==NULL) cs->size = 0;
    else cs->size = (cs->root)->size;
}

cs_node_lf* _cs_get_k_lf(cs_node_lf* nd, int k, int l){
    int ls;
    if (nd->left!=NULL) ls = (nd->left)->size;
    else ls = 0;
    if (l+ls+1==k) return nd;
    if (l+ls+1>k) return _cs_get_k_lf(nd->left, k, l);
    if (l+ls+1<k) return _cs_get_k_lf(nd->right, k, l+ls+1);
}

cs_node_lf* cs_get_k_lf(coset_lf* cs, int k){
    //assert (cs->root!=NULL);
    //assert ((cs->root)->size>k);
    return _cs_get_k_lf(cs->root, k+1, 0);
}