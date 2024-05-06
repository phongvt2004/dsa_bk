#include "kDTree.hpp"

/* TODO: You can implement methods, functions that support your data structures here.

 * */
kDTreeNode* kDTreeNode::copyTree() {
    kDTreeNode* node = new kDTreeNode(this->data);
    if(this->left != nullptr) node->left = this->left->copyTree();
    else node->left = nullptr;
    if(this->right != nullptr) node->right = this->right->copyTree();
    else node->right = nullptr;
    return node;
}

void kDTreeNode::print() {
    cout << "(";
    for(int i = 0; i < data.size(); i++) {
        cout << data[i];
        if(i != data.size() - 1) cout << ",";
    }
    cout << ")";
}

void kDTreeNode::inorder(bool &first) {
    if(left != nullptr) left->inorder(first);
    if(!first) cout << " ";
    print();
    first = false;
    if(right != nullptr) right->inorder(first);
}

void kDTreeNode::preorder(bool &first) {
    if(!first) cout << " ";
    print();
    first = false;
    if(left != nullptr) left->preorder(first);
    if(right != nullptr) right->preorder(first);
}

void kDTreeNode::postorder(bool &first) {
    if(left != nullptr) left->postorder(first);
    if(right != nullptr) right->postorder(first);
    if(!first) cout << " ";
    print();
    first = false;
}

int kDTreeNode::height() const {
    if(left == nullptr && right == nullptr) return 1;
    int hl = 0, hr = 0;
    if(left != nullptr) hl = left->height();
    if(right != nullptr) hr = right->height();
    return max(hl, hr) +1;
}

int kDTreeNode::nodeCount() const {
    if(left == nullptr && right == nullptr) return 1;
    int cl = 0, cr = 0;
    if(left != nullptr) cl = left->nodeCount();
    if(right != nullptr) cr = right->nodeCount();
    return cl + cr +1;
}

int kDTreeNode::leafCount() const {
    if(left == nullptr && right == nullptr) return 1;
    int cl = 0, cr = 0;
    if(left != nullptr) cl = left->nodeCount();
    if(right != nullptr) cr = right->nodeCount();
    return cl + cr;
}

void kDTreeNode::insert(const vector<int> &point, int k, int depth) {
    if(data[depth%k] < point[depth%k]) {
        if(right != nullptr) right->insert(point,k,depth+1);
        else right = new kDTreeNode(point);
    } else {
        if(left != nullptr) left->insert(point,k,depth+1);
        else left = new kDTreeNode(point);
    }
}

bool kDTreeNode::equal(const kDTreeNode * other) {
    for(int i=0; i<data.size(); i++) {
        if(data[i] != other->data[i]) return false;
    }
    return true;
}

bool kDTreeNode::equal(const vector<int> &point) {
    for(int i=0; i<data.size(); i++) {
        if(data[i] != point[i]) return false;
    }
    return true;
}

double kDTreeNode::distance(const kDTreeNode * other) {
    ll L2 = 0;
    for(int i=0; i<data.size(); i++) L2 += pow(data[i] - other->data[i], 2);
    return sqrt(L2);
}


kDTreeNode* replaceNode(kDTreeNode* root, int k, int alpha, int depth) {
    if(root == nullptr) return nullptr;
    if(depth % k == alpha) {
        if(root->left == nullptr) return root;
        return replaceNode(root->left, k, alpha, depth + 1);
    } else {
        kDTreeNode* minNode = root;
        kDTreeNode* left = replaceNode(root->left, k, alpha, depth+1);
        if(left != nullptr) {
            if(left->data[alpha] < minNode->data[alpha]) minNode = left;
        }
        kDTreeNode* right = replaceNode(root->right, k, alpha, depth+1);
        if(right != nullptr) {
            if(right->data[alpha] < minNode->data[alpha]) minNode = right;
        }
        return minNode;        
    }
}

void deleteNode(kDTreeNode* target, const kDTreeNode* root, int k, int alpha) {
    if(target == nullptr) return;
    int depth = root->height() - target->height();
    if(target->left == nullptr && target->right == nullptr) {
        delete target;
        target = nullptr;
        return;
    } else if(target->right != nullptr) {
        kDTreeNode* replace = replaceNode(target->right, k, alpha, depth+1);
        target->data = replace->data;
        alpha = root->height() - replace->height();
        deleteNode(replace, root, k, alpha);
    } else {
        kDTreeNode* replace = replaceNode(target->left, k, alpha, depth+1);
        target->data = replace->data;
        alpha = root->height() - replace->height();
        target->right = target->left;
        target->left = nullptr;
        deleteNode(replace, root, k, alpha);
    }
}

kDTreeNode* kDTreeNode::search(const vector<int> &point, int k, int depth) {

    if(equal(point)) return this;

    if(data[depth%k] < point[depth%k]) {
        if(right != nullptr) return right->search(point,k,depth+1);
        else return nullptr;
    } else {
        if(left != nullptr) return left->search(point,k,depth+1);
        else return nullptr;
    }
}


void deleteAll(kDTreeNode* node) {
    if(node == nullptr) return;
    deleteAll(node->left);
    deleteAll(node->right);
    delete node;
    node = nullptr;
}

kDTree::kDTree(int k) {
    _k=k;
}

kDTree::~kDTree() {
    deleteAll(root);
}


const kDTree &kDTree::operator=(const kDTree &other) {
    _k = other._k;
    root = new kDTreeNode(other.root->data);
    root->left = other.root->left->copyTree();
    root->right = other.root->right->copyTree();
    return *this;
}

kDTree::kDTree(const kDTree &other) {
    _k = other._k;
    root = new kDTreeNode(other.root->data);
    root->left = other.root->left->copyTree();
    root->right = other.root->right->copyTree();
}

void kDTree::inorderTraversal() const {
    kDTreeNode* curr = root;
    bool first = true;
    curr->inorder(first);
}

void kDTree::preorderTraversal() const {
    kDTreeNode* curr = root;
    bool first = true;
    curr->preorder(first);
}

void kDTree::postorderTraversal() const {
    kDTreeNode* curr = root;
    bool first = true;
    curr->postorder(first);
}

int kDTree::height() const {
    return root->height();
}

int kDTree::nodeCount() const {
    return root->nodeCount();
}

int kDTree::leafCount() const {
    return root->leafCount();
}

void kDTree::insert(const vector<int> &point) {
    if(root == nullptr) {
        root = new kDTreeNode(point);
        return;
    }
    root->insert(point,_k);
}

void kDTree::remove(const vector<int> &point) {
    if(root == nullptr) return;
    kDTreeNode* target = root->search(point, _k);
    if(target == nullptr) return;
    int alpha = root->height() - target->height();
    alpha %= _k;
    deleteNode(target, root, _k, alpha);
}

bool kDTree::search(const vector<int> &point) {
    if(root == nullptr) return false;
    if(root->search(point,_k) == nullptr) return false;
    else return true;
}

void kDTree::buildTree(const vector<vector<int>> &pointList) {

}

void kDTree::nearestNeighbour(const vector<int> &target, kDTreeNode *best) {

}

void kDTree::kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList) {

}


kNN::kNN(int k) {

}

void kNN::fit(Dataset &X_train, Dataset &y_train) {

}

Dataset kNN::predict(Dataset &X_test) {
    return X_test;
}

double kNN::score(const Dataset &y_test, const Dataset &y_pred) {
    return 0.1;
}
