// AVL tree
typedef struct cms_node_TAG {
    cms_data_t_TAG key;
    int count;
    struct cms_node_TAG* left;
    struct cms_node_TAG* right;
    int rank;
    int size;
    int isR;    // L: -1, E: 0, R: 1
} cms_node_TAG;

cms_node_TAG* cms_new_node_TAG(cms_data_t_TAG key, int count){
    cms_node_TAG* nd = (cms_node_TAG*)malloc(sizeof(cms_node_TAG));
    nd->key = key;
    nd->count = count;
    nd->left = NULL;
    nd->right = NULL;
    nd->rank = 0;
    nd->size = count;
    nd->isR = 0;
    return nd;
}

void cms_node_update_TAG(cms_node_TAG* nd){
    cms_node_TAG* left = nd->left;
    cms_node_TAG* right = nd->right;
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
    cms_node_TAG* root;
    int size;
} comultiset_TAG;

comultiset_TAG* comultiset_init_TAG(){
    comultiset_TAG* cms = (comultiset_TAG*)malloc(sizeof(comultiset_TAG));
    cms->root = NULL;
    cms->size = 0;
    return cms;
}

void _cms_clear_TAG(cms_node_TAG* nd){
    if (nd->left!=NULL) _cms_clear_TAG(nd->left);
    if (nd->right!=NULL) _cms_clear_TAG(nd->right);
    free(nd);
    return;
}

void cms_clear_TAG(comultiset_TAG* cms){
    if (cms->root==NULL) return;
    _cms_clear_TAG(cms->root);
    cms->root = NULL;
    cms->size = 0;
}

int cms_get_size_TAG(comultiset_TAG* cms){
    return cms->size;
}

cms_node_TAG* _cms_max_TAG(cms_node_TAG* nd){
    if (nd->right==NULL) return nd;
    return _cms_max_TAG(nd->right);
}

cms_node_TAG* cms_max_TAG(comultiset_TAG* cms){
    if (cms->root==NULL) return NULL;
    return _cms_max_TAG(cms->root);
}

cms_node_TAG* _cms_min_TAG(cms_node_TAG* nd){
    if (nd->left==NULL) return nd;
    return _cms_min_TAG(nd->left);
}

cms_node_TAG* cms_min_TAG(comultiset_TAG* cms){
    if (cms->root==NULL) return NULL;
    return _cms_min_TAG(cms->root);
}

cms_node_TAG* _cms_lower_bound_TAG(cms_node_TAG* nd, cms_data_t_TAG k){
	if (nd==NULL) return NULL;
	if (nd->key < k) return _cms_lower_bound_TAG(nd->right, k);
	return _cms_lower_bound_TAG(nd->left, k)?:nd;
}

cms_node_TAG* cms_lower_bound_TAG(comultiset_TAG* cms, cms_data_t_TAG k){
    return _cms_lower_bound_TAG(cms->root, k);
}

cms_node_TAG* _cms_rlower_bound_TAG(cms_node_TAG* nd, cms_data_t_TAG k){
	if (nd==NULL) return NULL;
	if (nd->key > k) return _cms_rlower_bound_TAG(nd->left, k);
	return _cms_rlower_bound_TAG(nd->right, k)?:nd;
}

cms_node_TAG* cms_rlower_bound_TAG(comultiset_TAG* cms, cms_data_t_TAG k){
    return _cms_rlower_bound_TAG(cms->root, k);
}

cms_node_TAG* _cms_upper_bound_TAG(cms_node_TAG* nd, cms_data_t_TAG k){
	if(nd==NULL) return NULL;
	if(nd->key <= k) return _cms_upper_bound_TAG(nd->right, k);
	return _cms_upper_bound_TAG(nd->left, k)?:nd;
}

cms_node_TAG* cms_upper_bound_TAG(comultiset_TAG* cms, cms_data_t_TAG k){
    return _cms_upper_bound_TAG(cms->root, k);
}

cms_node_TAG* _cms_rupper_bound_TAG(cms_node_TAG* nd, cms_data_t_TAG k){
	if(nd==NULL) return NULL;
	if(nd->key >= k) return _cms_rupper_bound_TAG(nd->left, k);
	return _cms_rupper_bound_TAG(nd->right, k)?:nd;
}

cms_node_TAG* cms_rupper_bound_TAG(comultiset_TAG* cms, cms_data_t_TAG k){
    return _cms_rupper_bound_TAG(cms->root, k);
}

cms_node_TAG* _cms_find_TAG(cms_node_TAG* nd, cms_data_t_TAG k){
    if(nd==NULL) return NULL;
    if(nd->key==k) return nd;
    if(nd->key<k) return _cms_find_TAG(nd->right, k);
    if(nd->key>k) return _cms_find_TAG(nd->left, k);
}

cms_node_TAG* cms_find_TAG(comultiset_TAG* cms, cms_data_t_TAG k){
    return _cms_find_TAG(cms->root, k);
}

int cms_count_TAG(cms_node_TAG* cms, cms_data_t_TAG k){
    cms_node_TAG* nd = _cms_find_TAG(cms, k);
    if (nd==NULL) return 0;
    return nd->count;
}

cms_node_TAG* cms_rotate_sl_TAG(cms_node_TAG* nd, cms_node_TAG* ch){
    cms_node_TAG* beta = ch->left;
    ch->left = nd;
    nd->right = beta;
    cms_node_update_TAG(nd);
    cms_node_update_TAG(ch);
    return ch;
}

cms_node_TAG* cms_rotate_dr_TAG(cms_node_TAG* nd, cms_node_TAG* ch){
    cms_node_TAG *chch, *beta, *gamma;
    chch = ch->left;
    beta = chch->left;
    gamma = chch->right;
    chch->left = nd;
    chch->right = ch;
    nd->right = beta;
    ch->left = gamma;
    cms_node_update_TAG(nd);
    cms_node_update_TAG(ch);
    cms_node_update_TAG(chch);
    return chch;
}

cms_node_TAG* cms_rotate_sr_TAG(cms_node_TAG* nd, cms_node_TAG* ch){
    cms_node_TAG* beta = ch->right;
    ch->right = nd;
    nd->left = beta;
    cms_node_update_TAG(nd);
    cms_node_update_TAG(ch);
    return ch;
}

cms_node_TAG* cms_rotate_dl_TAG(cms_node_TAG* nd, cms_node_TAG* ch){
    cms_node_TAG *chch, *beta, *gamma;
    chch = ch->right;
    beta = chch->right;
    gamma = chch->left;
    chch->right = nd;
    chch->left = ch;
    nd->left = beta;
    ch->right = gamma;
    cms_node_update_TAG(nd);
    cms_node_update_TAG(ch);
    cms_node_update_TAG(chch);
    return chch;
}

cms_node_TAG* _cms_insert_TAG(cms_node_TAG* nd, cms_data_t_TAG k, int count){
    if(nd->key==k) {
        (nd->count) += count;
        nd->size += count;
        return nd;
    }
    cms_node_TAG* ch;
    if(nd->key<k) {
        if (nd->right==NULL) {
            ch = cms_new_node_TAG(k, count); 
            nd->right = ch;
        } else {
            ch = _cms_insert_TAG(nd->right, k, count);
            nd->right = ch;
        }
        cms_node_update_TAG(nd);
        if (nd->isR==2) {
            if (ch->isR==1) return cms_rotate_sl_TAG(nd, ch);
            if (ch->isR==-1) return cms_rotate_dr_TAG(nd, ch);
        }
        return nd;
    }
    else {
        if (nd->left==NULL) {
            ch = cms_new_node_TAG(k, count); 
            nd->left = ch;
        } else {
            ch = _cms_insert_TAG(nd->left, k, count);
            nd->left = ch;
        }
        cms_node_update_TAG(nd);
        if (nd->isR==-2) {
            if (ch->isR==-1) return cms_rotate_sr_TAG(nd, ch);
            if (ch->isR==1) return cms_rotate_dl_TAG(nd, ch);
        }
        return nd;
    }
    exit(1);
    return NULL;
}

void cms_insert_TAG(comultiset_TAG* cms, cms_data_t_TAG k, int count){
    if (cms->root==NULL){
        cms->root = cms_new_node_TAG(k, count);
        cms->size = (cms->root)->size;
        return;
    }
    cms_node_TAG* ptr = _cms_insert_TAG(cms->root, k, count);
    if (ptr!=NULL) cms->root = ptr;
    cms->size = (cms->root)->size;
}

//これから
//削除したnodeの子が一つ→それをそのまま上げる
//二つ→左側の子孫の最大値を持ってくる
cms_node_TAG* _cms_remove_max_TAG(cms_node_TAG* nd, cms_node_TAG* targ){
    if (nd->right==NULL) {
        targ->key = nd->key;
        targ->count = nd->count;
        cms_node_TAG* ch = nd->left;
        free(nd);
        return ch;
    }
    cms_node_TAG *ch, *cha; 
    ch = _cms_remove_max_TAG(nd->right, targ);
    nd->right = ch;
    
    cms_node_update_TAG(nd);
    if (nd->isR==-2) {
        cha = nd->left;
        if (cha->isR<=0) return cms_rotate_sr_TAG(nd, cha);
        if (cha->isR==1) return cms_rotate_dl_TAG(nd, cha);
    }
    return nd;
}

cms_node_TAG* _cms_remove_from_targ_TAG(cms_node_TAG* nd, Boolean remove_all){
    if (nd->count>1 && !remove_all){
        --(nd->count);
        --(nd->size);
        return nd;
    }
    cms_node_TAG* left = nd->left;
    cms_node_TAG* right = nd->right;
    if (left==NULL && right==NULL) {
        free(nd);
        return NULL;
    }
    if (left!=NULL && right!=NULL) {
        cms_node_TAG* ch = _cms_remove_max_TAG(left, nd);
        nd->left = ch;
        cms_node_update_TAG(nd);
        if (nd->isR==2) {
            cms_node_TAG* cha = nd->right;
            if (cha->isR>=0) return cms_rotate_sl_TAG(nd, cha);
            if (cha->isR==-1) return cms_rotate_dr_TAG(nd, cha);
        }
        return nd;
        
    }
    free(nd);
    if (left!=NULL) return left;
    else return right;
}


cms_node_TAG* _cms_remove_TAG(cms_node_TAG* nd, cms_data_t_TAG k, Boolean remove_all){
    if(nd->key==k) return _cms_remove_from_targ_TAG(nd, remove_all);
    cms_node_TAG *ch, *cha;
    if(nd->key<k) {
        if (nd->right==NULL) {
            return nd;
        } else {
            ch = _cms_remove_TAG(nd->right, k, remove_all);
            nd->right = ch;
        }
        cms_node_update_TAG(nd);
        if (nd->isR==-2) {
            cha = nd->left;
            if (cha->isR<=0) return cms_rotate_sr_TAG(nd, cha);
            if (cha->isR==1) return cms_rotate_dl_TAG(nd, cha);
        }
        return nd;
    }
    else {
        if (nd->left==NULL) {
            return nd;
        } else {
            ch = _cms_remove_TAG(nd->left, k, remove_all);
            nd->left = ch;
        }
        cms_node_update_TAG(nd);
        if (nd->isR==2) {
            cha = nd->right;
            if (cha->isR>=0) return cms_rotate_sl_TAG(nd, cha);
            if (cha->isR==-1) return cms_rotate_dr_TAG(nd, cha);
        }
        return nd;
    }
}

void cms_remove_TAG(comultiset_TAG* cms, cms_data_t_TAG k, Boolean remove_all){
    cms->root = _cms_remove_TAG(cms->root, k, remove_all);
    if (cms->root==NULL) cms->size = 0;
    else cms->size = (cms->root)->size;
}

cms_node_TAG* _cms_get_k_TAG(cms_node_TAG* nd, int k, int l){
    int ls;
    if (nd->left!=NULL) ls = (nd->left)->size;
    else ls = 0;
    int count = nd->count;
    if (l+ls<k && k<=l+ls+count) return nd;
    if (l+ls>=k) return _cms_get_k_TAG(nd->left, k, l);
    if (l+ls+count<k) return _cms_get_k_TAG(nd->right, k, l+ls+count);
}

cms_node_TAG* cms_get_k_TAG(comultiset_TAG* cms, int k){
    //assert (cms->root!=NULL);
    //assert ((cms->root)->size>k);
    return _cms_get_k_TAG(cms->root, k+1, 0);
}