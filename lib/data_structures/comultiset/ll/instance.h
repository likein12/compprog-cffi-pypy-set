//ll=ll

typedef ll cms_data_t_ll;

// AVL tree
typedef struct cms_node_ll {
    cms_data_t_ll key;
    int count;
    struct cms_node_ll* left;
    struct cms_node_ll* right;
    int rank;
    int size;
    int isR;    // L: -1, E: 0, R: 1
} cms_node_ll;

cms_node_ll* cms_new_node_ll(cms_data_t_ll key, int count){
    cms_node_ll* nd = (cms_node_ll*)malloc(sizeof(cms_node_ll));
    nd->key = key;
    nd->count = count;
    nd->left = NULL;
    nd->right = NULL;
    nd->rank = 0;
    nd->size = count;
    nd->isR = 0;
    return nd;
}

void cms_node_update_ll(cms_node_ll* nd){
    cms_node_ll* left = nd->left;
    cms_node_ll* right = nd->right;
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
    cms_node_ll* root;
    int size;
} comultiset_ll;

comultiset_ll* comultiset_init_ll(){
    comultiset_ll* cms = (comultiset_ll*)malloc(sizeof(comultiset_ll));
    cms->root = NULL;
    cms->size = 0;
    return cms;
}

void _cms_clear_ll(cms_node_ll* nd){
    if (nd->left!=NULL) _cms_clear_ll(nd->left);
    if (nd->right!=NULL) _cms_clear_ll(nd->right);
    free(nd);
    return;
}

void cms_clear_ll(comultiset_ll* cms){
    if (cms->root==NULL) return;
    _cms_clear_ll(cms->root);
    cms->root = NULL;
    cms->size = 0;
}

int cms_get_size_ll(comultiset_ll* cms){
    return cms->size;
}

cms_node_ll* _cms_max_ll(cms_node_ll* nd){
    if (nd->right==NULL) return nd;
    return _cms_max_ll(nd->right);
}

cms_node_ll* cms_max_ll(comultiset_ll* cms){
    if (cms->root==NULL) return NULL;
    return _cms_max_ll(cms->root);
}

cms_node_ll* _cms_min_ll(cms_node_ll* nd){
    if (nd->left==NULL) return nd;
    return _cms_min_ll(nd->left);
}

cms_node_ll* cms_min_ll(comultiset_ll* cms){
    if (cms->root==NULL) return NULL;
    return _cms_min_ll(cms->root);
}

cms_node_ll* _cms_lower_bound_ll(cms_node_ll* nd, cms_data_t_ll k){
	if (nd==NULL) return NULL;
	if (nd->key < k) return _cms_lower_bound_ll(nd->right, k);
	return _cms_lower_bound_ll(nd->left, k)?:nd;
}

cms_node_ll* cms_lower_bound_ll(comultiset_ll* cms, cms_data_t_ll k){
    return _cms_lower_bound_ll(cms->root, k);
}

cms_node_ll* _cms_rlower_bound_ll(cms_node_ll* nd, cms_data_t_ll k){
	if (nd==NULL) return NULL;
	if (nd->key > k) return _cms_rlower_bound_ll(nd->left, k);
	return _cms_rlower_bound_ll(nd->right, k)?:nd;
}

cms_node_ll* cms_rlower_bound_ll(comultiset_ll* cms, cms_data_t_ll k){
    return _cms_rlower_bound_ll(cms->root, k);
}

cms_node_ll* _cms_upper_bound_ll(cms_node_ll* nd, cms_data_t_ll k){
	if(nd==NULL) return NULL;
	if(nd->key <= k) return _cms_upper_bound_ll(nd->right, k);
	return _cms_upper_bound_ll(nd->left, k)?:nd;
}

cms_node_ll* cms_upper_bound_ll(comultiset_ll* cms, cms_data_t_ll k){
    return _cms_upper_bound_ll(cms->root, k);
}

cms_node_ll* _cms_rupper_bound_ll(cms_node_ll* nd, cms_data_t_ll k){
	if(nd==NULL) return NULL;
	if(nd->key >= k) return _cms_rupper_bound_ll(nd->left, k);
	return _cms_rupper_bound_ll(nd->right, k)?:nd;
}

cms_node_ll* cms_rupper_bound_ll(comultiset_ll* cms, cms_data_t_ll k){
    return _cms_rupper_bound_ll(cms->root, k);
}

cms_node_ll* _cms_find_ll(cms_node_ll* nd, cms_data_t_ll k){
    if(nd==NULL) return NULL;
    if(nd->key==k) return nd;
    if(nd->key<k) return _cms_find_ll(nd->right, k);
    if(nd->key>k) return _cms_find_ll(nd->left, k);
}

cms_node_ll* cms_find_ll(comultiset_ll* cms, cms_data_t_ll k){
    return _cms_find_ll(cms->root, k);
}

int cms_count_ll(cms_node_ll* cms, cms_data_t_ll k){
    cms_node_ll* nd = _cms_find_ll(cms, k);
    if (nd==NULL) return 0;
    return nd->count;
}

cms_node_ll* cms_rotate_sl_ll(cms_node_ll* nd, cms_node_ll* ch){
    cms_node_ll* beta = ch->left;
    ch->left = nd;
    nd->right = beta;
    cms_node_update_ll(nd);
    cms_node_update_ll(ch);
    return ch;
}

cms_node_ll* cms_rotate_dr_ll(cms_node_ll* nd, cms_node_ll* ch){
    cms_node_ll *chch, *beta, *gamma;
    chch = ch->left;
    beta = chch->left;
    gamma = chch->right;
    chch->left = nd;
    chch->right = ch;
    nd->right = beta;
    ch->left = gamma;
    cms_node_update_ll(nd);
    cms_node_update_ll(ch);
    cms_node_update_ll(chch);
    return chch;
}

cms_node_ll* cms_rotate_sr_ll(cms_node_ll* nd, cms_node_ll* ch){
    cms_node_ll* beta = ch->right;
    ch->right = nd;
    nd->left = beta;
    cms_node_update_ll(nd);
    cms_node_update_ll(ch);
    return ch;
}

cms_node_ll* cms_rotate_dl_ll(cms_node_ll* nd, cms_node_ll* ch){
    cms_node_ll *chch, *beta, *gamma;
    chch = ch->right;
    beta = chch->right;
    gamma = chch->left;
    chch->right = nd;
    chch->left = ch;
    nd->left = beta;
    ch->right = gamma;
    cms_node_update_ll(nd);
    cms_node_update_ll(ch);
    cms_node_update_ll(chch);
    return chch;
}

cms_node_ll* _cms_insert_ll(cms_node_ll* nd, cms_data_t_ll k, int count){
    if(nd->key==k) {
        (nd->count) += count;
        nd->size += count;
        return nd;
    }
    cms_node_ll* ch;
    if(nd->key<k) {
        if (nd->right==NULL) {
            ch = cms_new_node_ll(k, count); 
            nd->right = ch;
        } else {
            ch = _cms_insert_ll(nd->right, k, count);
            nd->right = ch;
        }
        cms_node_update_ll(nd);
        if (nd->isR==2) {
            if (ch->isR==1) return cms_rotate_sl_ll(nd, ch);
            if (ch->isR==-1) return cms_rotate_dr_ll(nd, ch);
        }
        return nd;
    }
    else {
        if (nd->left==NULL) {
            ch = cms_new_node_ll(k, count); 
            nd->left = ch;
        } else {
            ch = _cms_insert_ll(nd->left, k, count);
            nd->left = ch;
        }
        cms_node_update_ll(nd);
        if (nd->isR==-2) {
            if (ch->isR==-1) return cms_rotate_sr_ll(nd, ch);
            if (ch->isR==1) return cms_rotate_dl_ll(nd, ch);
        }
        return nd;
    }
    exit(1);
    return NULL;
}

void cms_insert_ll(comultiset_ll* cms, cms_data_t_ll k, int count){
    if (cms->root==NULL){
        cms->root = cms_new_node_ll(k, count);
        cms->size = (cms->root)->size;
        return;
    }
    cms_node_ll* ptr = _cms_insert_ll(cms->root, k, count);
    if (ptr!=NULL) cms->root = ptr;
    cms->size = (cms->root)->size;
}

//これから
//削除したnodeの子が一つ→それをそのまま上げる
//二つ→左側の子孫の最大値を持ってくる
cms_node_ll* _cms_remove_max_ll(cms_node_ll* nd, cms_node_ll* targ){
    if (nd->right==NULL) {
        targ->key = nd->key;
        targ->count = nd->count;
        cms_node_ll* ch = nd->left;
        free(nd);
        return ch;
    }
    cms_node_ll *ch, *cha; 
    ch = _cms_remove_max_ll(nd->right, targ);
    nd->right = ch;
    
    cms_node_update_ll(nd);
    if (nd->isR==-2) {
        cha = nd->left;
        if (cha->isR<=0) return cms_rotate_sr_ll(nd, cha);
        if (cha->isR==1) return cms_rotate_dl_ll(nd, cha);
    }
    return nd;
}

cms_node_ll* _cms_remove_from_targ_ll(cms_node_ll* nd, Boolean remove_all){
    if (nd->count>1 && !remove_all){
        --(nd->count);
        --(nd->size);
        return nd;
    }
    cms_node_ll* left = nd->left;
    cms_node_ll* right = nd->right;
    if (left==NULL && right==NULL) {
        free(nd);
        return NULL;
    }
    if (left!=NULL && right!=NULL) {
        cms_node_ll* ch = _cms_remove_max_ll(left, nd);
        nd->left = ch;
        cms_node_update_ll(nd);
        if (nd->isR==2) {
            cms_node_ll* cha = nd->right;
            if (cha->isR>=0) return cms_rotate_sl_ll(nd, cha);
            if (cha->isR==-1) return cms_rotate_dr_ll(nd, cha);
        }
        return nd;
        
    }
    free(nd);
    if (left!=NULL) return left;
    else return right;
}


cms_node_ll* _cms_remove_ll(cms_node_ll* nd, cms_data_t_ll k, Boolean remove_all){
    if(nd->key==k) return _cms_remove_from_targ_ll(nd, remove_all);
    cms_node_ll *ch, *cha;
    if(nd->key<k) {
        if (nd->right==NULL) {
            return nd;
        } else {
            ch = _cms_remove_ll(nd->right, k, remove_all);
            nd->right = ch;
        }
        cms_node_update_ll(nd);
        if (nd->isR==-2) {
            cha = nd->left;
            if (cha->isR<=0) return cms_rotate_sr_ll(nd, cha);
            if (cha->isR==1) return cms_rotate_dl_ll(nd, cha);
        }
        return nd;
    }
    else {
        if (nd->left==NULL) {
            return nd;
        } else {
            ch = _cms_remove_ll(nd->left, k, remove_all);
            nd->left = ch;
        }
        cms_node_update_ll(nd);
        if (nd->isR==2) {
            cha = nd->right;
            if (cha->isR>=0) return cms_rotate_sl_ll(nd, cha);
            if (cha->isR==-1) return cms_rotate_dr_ll(nd, cha);
        }
        return nd;
    }
}

void cms_remove_ll(comultiset_ll* cms, cms_data_t_ll k, Boolean remove_all){
    cms->root = _cms_remove_ll(cms->root, k, remove_all);
    if (cms->root==NULL) cms->size = 0;
    else cms->size = (cms->root)->size;
}

cms_node_ll* _cms_get_k_ll(cms_node_ll* nd, int k, int l){
    int ls;
    if (nd->left!=NULL) ls = (nd->left)->size;
    else ls = 0;
    int count = nd->count;
    if (l+ls<k && k<=l+ls+count) return nd;
    if (l+ls>=k) return _cms_get_k_ll(nd->left, k, l);
    if (l+ls+count<k) return _cms_get_k_ll(nd->right, k, l+ls+count);
}

cms_node_ll* cms_get_k_ll(comultiset_ll* cms, int k){
    //assert (cms->root!=NULL);
    //assert ((cms->root)->size>k);
    return _cms_get_k_ll(cms->root, k+1, 0);
}