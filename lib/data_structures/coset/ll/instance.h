//ll=ll

typedef ll cs_data_t_ll;

// AVL tree
typedef struct cs_node_ll {
    cs_data_t_ll key;
    struct cs_node_ll* left;
    struct cs_node_ll* right;
    int rank;
    int size;
    int isR;    // L: -1, E: 0, R: 1
} cs_node_ll;

cs_node_ll* cs_new_node_ll(cs_data_t_ll key){
    cs_node_ll* nd = (cs_node_ll*)malloc(sizeof(cs_node_ll));
    nd->key = key;
    nd->left = NULL;
    nd->right = NULL;
    nd->rank = 0;
    nd->size = 1;
    nd->isR = 0;
    return nd;
}

void cs_node_update_ll(cs_node_ll* nd){
    cs_node_ll* left = nd->left;
    cs_node_ll* right = nd->right;
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
    cs_node_ll* root;
    int size;
} coset_ll;

coset_ll* coset_init_ll(){
    coset_ll* cs = (coset_ll*)malloc(sizeof(coset_ll));
    cs->root = NULL;
    cs->size = 0;
    return cs;
}

void _cs_clear_ll(cs_node_ll* nd){
    if (nd->left!=NULL) _cs_clear_ll(nd->left);
    if (nd->right!=NULL) _cs_clear_ll(nd->right);
    free(nd);
    return;
}

void cs_clear_ll(coset_ll* cs){
    if (cs->root==NULL) return;
    _cs_clear_ll(cs->root);
    cs->root = NULL;
    cs->size = 0;
}

int cs_get_size_ll(coset_ll* cs){
    return cs->size;
}

cs_node_ll* _cs_max_ll(cs_node_ll* nd){
    if (nd->right==NULL) return nd;
    return _cs_max_ll(nd->right);
}

cs_node_ll* cs_max_ll(coset_ll* cs){
    if (cs->root==NULL) return NULL;
    return _cs_max_ll(cs->root);
}

cs_node_ll* _cs_min_ll(cs_node_ll* nd){
    if (nd->left==NULL) return nd;
    return _cs_min_ll(nd->left);
}

cs_node_ll* cs_min_ll(coset_ll* cs){
    if (cs->root==NULL) return NULL;
    return _cs_min_ll(cs->root);
}

cs_node_ll* _cs_lower_bound_ll(cs_node_ll* nd, cs_data_t_ll k){
	if (nd==NULL) return NULL;
	if (nd->key < k) return _cs_lower_bound_ll(nd->right, k);
	return _cs_lower_bound_ll(nd->left, k)?:nd;
}

cs_node_ll* cs_lower_bound_ll(coset_ll* cs, cs_data_t_ll k){
    return _cs_lower_bound_ll(cs->root, k);
}

cs_node_ll* _cs_rlower_bound_ll(cs_node_ll* nd, cs_data_t_ll k){
	if (nd==NULL) return NULL;
	if (nd->key > k) return _cs_rlower_bound_ll(nd->left, k);
	return _cs_rlower_bound_ll(nd->right, k)?:nd;
}

cs_node_ll* cs_rlower_bound_ll(coset_ll* cs, cs_data_t_ll k){
    return _cs_rlower_bound_ll(cs->root, k);
}

cs_node_ll* _cs_upper_bound_ll(cs_node_ll* nd, cs_data_t_ll k){
	if(nd==NULL) return NULL;
	if(nd->key <= k) return _cs_upper_bound_ll(nd->right, k);
	return _cs_upper_bound_ll(nd->left, k)?:nd;
}

cs_node_ll* cs_upper_bound_ll(coset_ll* cs, cs_data_t_ll k){
    return _cs_upper_bound_ll(cs->root, k);
}

cs_node_ll* _cs_rupper_bound_ll(cs_node_ll* nd, cs_data_t_ll k){
	if(nd==NULL) return NULL;
	if(nd->key >= k) return _cs_rupper_bound_ll(nd->left, k);
	return _cs_rupper_bound_ll(nd->right, k)?:nd;
}

cs_node_ll* cs_rupper_bound_ll(coset_ll* cs, cs_data_t_ll k){
    return _cs_rupper_bound_ll(cs->root, k);
}

cs_node_ll* _cs_find_ll(cs_node_ll* nd, cs_data_t_ll k){
    if(nd==NULL) return NULL;
    if(nd->key==k) return nd;
    if(nd->key<k) return _cs_find_ll(nd->right, k);
    if(nd->key>k) return _cs_find_ll(nd->left, k);
}

cs_node_ll* cs_find_ll(coset_ll* cs, cs_data_t_ll k){
    return _cs_find_ll(cs->root, k);
}

cs_node_ll* cs_rotate_sl_ll(cs_node_ll* nd, cs_node_ll* ch){
    cs_node_ll* beta = ch->left;
    ch->left = nd;
    nd->right = beta;
    cs_node_update_ll(nd);
    cs_node_update_ll(ch);
    return ch;
}

cs_node_ll* cs_rotate_dr_ll(cs_node_ll* nd, cs_node_ll* ch){
    cs_node_ll *chch, *beta, *gamma;
    chch = ch->left;
    beta = chch->left;
    gamma = chch->right;
    chch->left = nd;
    chch->right = ch;
    nd->right = beta;
    ch->left = gamma;
    cs_node_update_ll(nd);
    cs_node_update_ll(ch);
    cs_node_update_ll(chch);
    return chch;
}

cs_node_ll* cs_rotate_sr_ll(cs_node_ll* nd, cs_node_ll* ch){
    cs_node_ll* beta = ch->right;
    ch->right = nd;
    nd->left = beta;
    cs_node_update_ll(nd);
    cs_node_update_ll(ch);
    return ch;
}

cs_node_ll* cs_rotate_dl_ll(cs_node_ll* nd, cs_node_ll* ch){
    cs_node_ll *chch, *beta, *gamma;
    chch = ch->right;
    beta = chch->right;
    gamma = chch->left;
    chch->right = nd;
    chch->left = ch;
    nd->left = beta;
    ch->right = gamma;
    cs_node_update_ll(nd);
    cs_node_update_ll(ch);
    cs_node_update_ll(chch);
    return chch;
}

cs_node_ll* _cs_insert_ll(cs_node_ll* nd, cs_data_t_ll k){
    if(nd->key==k) return NULL;
    cs_node_ll* ch;
    if(nd->key<k) {
        if (nd->right==NULL) {
            ch = cs_new_node_ll(k); 
            nd->right = ch;
        } else {
            ch = _cs_insert_ll(nd->right, k);
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
        if (ch->isR==1) return cs_rotate_sl_ll(nd, ch);
        if (ch->isR==-1) return cs_rotate_dr_ll(nd, ch);
    }
    else {
        if (nd->left==NULL) {
            ch = cs_new_node_ll(k); 
            nd->left = ch;
        } else {
            ch = _cs_insert_ll(nd->left, k);
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
        if (ch->isR==-1) return cs_rotate_sr_ll(nd, ch);
        if (ch->isR==1) return cs_rotate_dl_ll(nd, ch);
    }
    exit(1);
    return NULL;
}

void cs_insert_ll(coset_ll* cs, cs_data_t_ll k){
    if (cs->root==NULL){
        cs->root = cs_new_node_ll(k);
        cs->size = (cs->root)->size;
        return;
    }
    cs_node_ll* ptr = _cs_insert_ll(cs->root, k);
    if (ptr!=NULL) cs->root = ptr;
    cs->size = (cs->root)->size;
}

//これから
//削除したnodeの子が一つ→それをそのまま上げる
//二つ→左側の子孫の最大値を持ってくる
cs_node_ll* _cs_remove_max_ll(cs_node_ll* nd, cs_node_ll* targ){
    if (nd->right==NULL) {
        targ->key = nd->key;
        cs_node_ll* ch = nd->left;
        free(nd);
        return ch;
    }
    cs_node_ll *ch, *cha; 
    ch = _cs_remove_max_ll(nd->right, targ);
    nd->right = ch;
    
    cs_node_update_ll(nd);
    if (nd->isR==-2) {
        cha = nd->left;
        if (cha->isR<=0) return cs_rotate_sr_ll(nd, cha);
        if (cha->isR==1) return cs_rotate_dl_ll(nd, cha);
    }
    return nd;
}

cs_node_ll* _cs_remove_from_targ_ll(cs_node_ll* nd){
    cs_node_ll* left = nd->left;
    cs_node_ll* right = nd->right;
    if (left==NULL && right==NULL) {
        free(nd);
        return NULL;
    }
    if (left!=NULL && right!=NULL) {
        cs_node_ll* ch = _cs_remove_max_ll(left, nd);
        nd->left = ch;
        cs_node_update_ll(nd);
        if (nd->isR==2) {
            cs_node_ll* cha = nd->right;
            if (cha->isR>=0) return cs_rotate_sl_ll(nd, cha);
            if (cha->isR==-1) return cs_rotate_dr_ll(nd, cha);
        }
        return nd;
        
    }
    free(nd);
    if (left!=NULL) return left;
    else return right;
}


cs_node_ll* _cs_remove_ll(cs_node_ll* nd, cs_data_t_ll k){
    if(nd->key==k) return _cs_remove_from_targ_ll(nd);
    cs_node_ll *ch, *cha;
    if(nd->key<k) {
        if (nd->right==NULL) {
            return nd;
        } else {
            ch = _cs_remove_ll(nd->right, k);
            nd->right = ch;
        }
        cs_node_update_ll(nd);
        if (nd->isR==-2) {
            cha = nd->left;
            if (cha->isR<=0) return cs_rotate_sr_ll(nd, cha);
            if (cha->isR==1) return cs_rotate_dl_ll(nd, cha);
        }
        return nd;
    }
    else {
        if (nd->left==NULL) {
            return nd;
        } else {
            ch = _cs_remove_ll(nd->left, k);
            nd->left = ch;
        }
        cs_node_update_ll(nd);
        if (nd->isR==2) {
            cha = nd->right;
            if (cha->isR>=0) return cs_rotate_sl_ll(nd, cha);
            if (cha->isR==-1) return cs_rotate_dr_ll(nd, cha);
        }
        return nd;
    }
}

void cs_remove_ll(coset_ll* cs, cs_data_t_ll k){
    cs->root = _cs_remove_ll(cs->root, k);
    if (cs->root==NULL) cs->size = 0;
    else cs->size = (cs->root)->size;
}

cs_node_ll* _cs_get_k_ll(cs_node_ll* nd, int k, int l){
    int ls;
    if (nd->left!=NULL) ls = (nd->left)->size;
    else ls = 0;
    if (l+ls+1==k) return nd;
    if (l+ls+1>k) return _cs_get_k_ll(nd->left, k, l);
    if (l+ls+1<k) return _cs_get_k_ll(nd->right, k, l+ls+1);
}

cs_node_ll* cs_get_k_ll(coset_ll* cs, int k){
    //assert (cs->root!=NULL);
    //assert ((cs->root)->size>k);
    return _cs_get_k_ll(cs->root, k+1, 0);
}