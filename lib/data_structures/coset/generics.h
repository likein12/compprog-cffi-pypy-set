// AVL tree
typedef struct cs_node_TAG {
    cs_data_t_TAG key;
    struct cs_node_TAG* left;
    struct cs_node_TAG* right;
    int rank;
    int size;
    int isR;    // L: -1, E: 0, R: 1
} cs_node_TAG;

cs_node_TAG* cs_new_node_TAG(cs_data_t_TAG key){
    cs_node_TAG* nd = (cs_node_TAG*)malloc(sizeof(cs_node_TAG));
    nd->key = key;
    nd->left = NULL;
    nd->right = NULL;
    nd->rank = 0;
    nd->size = 1;
    nd->isR = 0;
    return nd;
}

void cs_node_update_TAG(cs_node_TAG* nd){
    cs_node_TAG* left = nd->left;
    cs_node_TAG* right = nd->right;
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
    cs_node_TAG* root;
    int size;
} coset_TAG;

coset_TAG* coset_init_TAG(){
    coset_TAG* cs = (coset_TAG*)malloc(sizeof(coset_TAG));
    cs->root = NULL;
    cs->size = 0;
    return cs;
}

void _cs_clear_TAG(cs_node_TAG* nd){
    if (nd->left!=NULL) _cs_clear_TAG(nd->left);
    if (nd->right!=NULL) _cs_clear_TAG(nd->right);
    free(nd);
    return;
}

void cs_clear_TAG(coset_TAG* cs){
    if (cs->root==NULL) return;
    _cs_clear_TAG(cs->root);
    cs->root = NULL;
    cs->size = 0;
}

int cs_get_size_TAG(coset_TAG* cs){
    return cs->size;
}

cs_node_TAG* _cs_max_TAG(cs_node_TAG* nd){
    if (nd->right==NULL) return nd;
    return _cs_max_TAG(nd->right);
}

cs_node_TAG* cs_max_TAG(coset_TAG* cs){
    if (cs->root==NULL) return NULL;
    return _cs_max_TAG(cs->root);
}

cs_node_TAG* _cs_min_TAG(cs_node_TAG* nd){
    if (nd->left==NULL) return nd;
    return _cs_min_TAG(nd->left);
}

cs_node_TAG* cs_min_TAG(coset_TAG* cs){
    if (cs->root==NULL) return NULL;
    return _cs_min_TAG(cs->root);
}

cs_node_TAG* _cs_lower_bound_TAG(cs_node_TAG* nd, cs_data_t_TAG k){
	if (nd==NULL) return NULL;
	if (nd->key < k) return _cs_lower_bound_TAG(nd->right, k);
	return _cs_lower_bound_TAG(nd->left, k)?:nd;
}

cs_node_TAG* cs_lower_bound_TAG(coset_TAG* cs, cs_data_t_TAG k){
    return _cs_lower_bound_TAG(cs->root, k);
}

cs_node_TAG* _cs_rlower_bound_TAG(cs_node_TAG* nd, cs_data_t_TAG k){
	if (nd==NULL) return NULL;
	if (nd->key > k) return _cs_rlower_bound_TAG(nd->left, k);
	return _cs_rlower_bound_TAG(nd->right, k)?:nd;
}

cs_node_TAG* cs_rlower_bound_TAG(coset_TAG* cs, cs_data_t_TAG k){
    return _cs_rlower_bound_TAG(cs->root, k);
}

cs_node_TAG* _cs_upper_bound_TAG(cs_node_TAG* nd, cs_data_t_TAG k){
	if(nd==NULL) return NULL;
	if(nd->key <= k) return _cs_upper_bound_TAG(nd->right, k);
	return _cs_upper_bound_TAG(nd->left, k)?:nd;
}

cs_node_TAG* cs_upper_bound_TAG(coset_TAG* cs, cs_data_t_TAG k){
    return _cs_upper_bound_TAG(cs->root, k);
}

cs_node_TAG* _cs_rupper_bound_TAG(cs_node_TAG* nd, cs_data_t_TAG k){
	if(nd==NULL) return NULL;
	if(nd->key >= k) return _cs_rupper_bound_TAG(nd->left, k);
	return _cs_rupper_bound_TAG(nd->right, k)?:nd;
}

cs_node_TAG* cs_rupper_bound_TAG(coset_TAG* cs, cs_data_t_TAG k){
    return _cs_rupper_bound_TAG(cs->root, k);
}

cs_node_TAG* _cs_find_TAG(cs_node_TAG* nd, cs_data_t_TAG k){
    if(nd==NULL) return NULL;
    if(nd->key==k) return nd;
    if(nd->key<k) return _cs_find_TAG(nd->right, k);
    if(nd->key>k) return _cs_find_TAG(nd->left, k);
}

cs_node_TAG* cs_find_TAG(coset_TAG* cs, cs_data_t_TAG k){
    return _cs_find_TAG(cs->root, k);
}

cs_node_TAG* cs_rotate_sl_TAG(cs_node_TAG* nd, cs_node_TAG* ch){
    cs_node_TAG* beta = ch->left;
    ch->left = nd;
    nd->right = beta;
    cs_node_update_TAG(nd);
    cs_node_update_TAG(ch);
    return ch;
}

cs_node_TAG* cs_rotate_dr_TAG(cs_node_TAG* nd, cs_node_TAG* ch){
    cs_node_TAG *chch, *beta, *gamma;
    chch = ch->left;
    beta = chch->left;
    gamma = chch->right;
    chch->left = nd;
    chch->right = ch;
    nd->right = beta;
    ch->left = gamma;
    cs_node_update_TAG(nd);
    cs_node_update_TAG(ch);
    cs_node_update_TAG(chch);
    return chch;
}

cs_node_TAG* cs_rotate_sr_TAG(cs_node_TAG* nd, cs_node_TAG* ch){
    cs_node_TAG* beta = ch->right;
    ch->right = nd;
    nd->left = beta;
    cs_node_update_TAG(nd);
    cs_node_update_TAG(ch);
    return ch;
}

cs_node_TAG* cs_rotate_dl_TAG(cs_node_TAG* nd, cs_node_TAG* ch){
    cs_node_TAG *chch, *beta, *gamma;
    chch = ch->right;
    beta = chch->right;
    gamma = chch->left;
    chch->right = nd;
    chch->left = ch;
    nd->left = beta;
    ch->right = gamma;
    cs_node_update_TAG(nd);
    cs_node_update_TAG(ch);
    cs_node_update_TAG(chch);
    return chch;
}

cs_node_TAG* _cs_insert_TAG(cs_node_TAG* nd, cs_data_t_TAG k){
    if(nd->key==k) return NULL;
    cs_node_TAG* ch;
    if(nd->key<k) {
        if (nd->right==NULL) {
            ch = cs_new_node_TAG(k); 
            nd->right = ch;
        } else {
            ch = _cs_insert_TAG(nd->right, k);
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
        if (ch->isR==1) return cs_rotate_sl_TAG(nd, ch);
        if (ch->isR==-1) return cs_rotate_dr_TAG(nd, ch);
    }
    else {
        if (nd->left==NULL) {
            ch = cs_new_node_TAG(k); 
            nd->left = ch;
        } else {
            ch = _cs_insert_TAG(nd->left, k);
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
        if (ch->isR==-1) return cs_rotate_sr_TAG(nd, ch);
        if (ch->isR==1) return cs_rotate_dl_TAG(nd, ch);
    }
    exit(1);
    return NULL;
}

void cs_insert_TAG(coset_TAG* cs, cs_data_t_TAG k){
    if (cs->root==NULL){
        cs->root = cs_new_node_TAG(k);
        cs->size = (cs->root)->size;
        return;
    }
    cs_node_TAG* ptr = _cs_insert_TAG(cs->root, k);
    if (ptr!=NULL) cs->root = ptr;
    cs->size = (cs->root)->size;
}

//これから
//削除したnodeの子が一つ→それをそのまま上げる
//二つ→左側の子孫の最大値を持ってくる
cs_node_TAG* _cs_remove_max_TAG(cs_node_TAG* nd, cs_node_TAG* targ){
    if (nd->right==NULL) {
        targ->key = nd->key;
        cs_node_TAG* ch = nd->left;
        free(nd);
        return ch;
    }
    cs_node_TAG *ch, *cha; 
    ch = _cs_remove_max_TAG(nd->right, targ);
    nd->right = ch;
    
    cs_node_update_TAG(nd);
    if (nd->isR==-2) {
        cha = nd->left;
        if (cha->isR<=0) return cs_rotate_sr_TAG(nd, cha);
        if (cha->isR==1) return cs_rotate_dl_TAG(nd, cha);
    }
    return nd;
}

cs_node_TAG* _cs_remove_from_targ_TAG(cs_node_TAG* nd){
    cs_node_TAG* left = nd->left;
    cs_node_TAG* right = nd->right;
    if (left==NULL && right==NULL) {
        free(nd);
        return NULL;
    }
    if (left!=NULL && right!=NULL) {
        cs_node_TAG* ch = _cs_remove_max_TAG(left, nd);
        nd->left = ch;
        cs_node_update_TAG(nd);
        if (nd->isR==2) {
            cs_node_TAG* cha = nd->right;
            if (cha->isR>=0) return cs_rotate_sl_TAG(nd, cha);
            if (cha->isR==-1) return cs_rotate_dr_TAG(nd, cha);
        }
        return nd;
        
    }
    free(nd);
    if (left!=NULL) return left;
    else return right;
}


cs_node_TAG* _cs_remove_TAG(cs_node_TAG* nd, cs_data_t_TAG k){
    if(nd->key==k) return _cs_remove_from_targ_TAG(nd);
    cs_node_TAG *ch, *cha;
    if(nd->key<k) {
        if (nd->right==NULL) {
            return nd;
        } else {
            ch = _cs_remove_TAG(nd->right, k);
            nd->right = ch;
        }
        cs_node_update_TAG(nd);
        if (nd->isR==-2) {
            cha = nd->left;
            if (cha->isR<=0) return cs_rotate_sr_TAG(nd, cha);
            if (cha->isR==1) return cs_rotate_dl_TAG(nd, cha);
        }
        return nd;
    }
    else {
        if (nd->left==NULL) {
            return nd;
        } else {
            ch = _cs_remove_TAG(nd->left, k);
            nd->left = ch;
        }
        cs_node_update_TAG(nd);
        if (nd->isR==2) {
            cha = nd->right;
            if (cha->isR>=0) return cs_rotate_sl_TAG(nd, cha);
            if (cha->isR==-1) return cs_rotate_dr_TAG(nd, cha);
        }
        return nd;
    }
}

void cs_remove_TAG(coset_TAG* cs, cs_data_t_TAG k){
    cs->root = _cs_remove_TAG(cs->root, k);
    if (cs->root==NULL) cs->size = 0;
    else cs->size = (cs->root)->size;
}

cs_node_TAG* _cs_get_k_TAG(cs_node_TAG* nd, int k, int l){
    int ls;
    if (nd->left!=NULL) ls = (nd->left)->size;
    else ls = 0;
    if (l+ls+1==k) return nd;
    if (l+ls+1>k) return _cs_get_k_TAG(nd->left, k, l);
    if (l+ls+1<k) return _cs_get_k_TAG(nd->right, k, l+ls+1);
}

cs_node_TAG* cs_get_k_TAG(coset_TAG* cs, int k){
    //assert (cs->root!=NULL);
    //assert ((cs->root)->size>k);
    return _cs_get_k_TAG(cs->root, k+1, 0);
}