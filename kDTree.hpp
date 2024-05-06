#include "main.hpp"
#include "Dataset.hpp"
/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

#define ll long long

struct kDTreeNode
{
    vector<int> data;
    kDTreeNode *left;
    kDTreeNode *right;
    kDTreeNode(vector<int> data, kDTreeNode *left = nullptr, kDTreeNode *right = nullptr)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }
    kDTreeNode* copyTree();
    void inorder(bool &first);
    void preorder(bool &first);
    void postorder(bool &first);
    void print();
    int height() const;
    int nodeCount() const;
    int leafCount() const;
    void insert(const vector<int> &point, int k, int depth = 0);
    kDTreeNode* search(const vector<int> &point, int k, int depth = 0);
    bool equal(const kDTreeNode * other);
    bool equal(const vector<int> &point);
    double distance(const kDTreeNode * other);
    friend kDTreeNode* replaceNode(kDTreeNode* root, int k, int alpha, int depth);
    friend void deleteAll(kDTreeNode* node);
    friend void deleteNode(kDTreeNode* target, const kDTreeNode* root, int k, int alpha);
};

class kDTree
{
private:
    int _k;
    kDTreeNode *root = nullptr;

public:
    kDTree(int k = 2);
    ~kDTree();

    const kDTree &operator=(const kDTree &other);
    kDTree(const kDTree &other);

    void inorderTraversal() const;
    void preorderTraversal() const;
    void postorderTraversal() const;
    int height() const;
    int nodeCount() const;
    int leafCount() const;

    void insert(const vector<int> &point);
    void remove(const vector<int> &point);
    bool search(const vector<int> &point);
    void buildTree(const vector<vector<int>> &pointList);
    void nearestNeighbour(const vector<int> &target, kDTreeNode *best);
    void kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList);
};

class kNN
{
private:
    int k;
    Dataset *X_train;
    Dataset *y_train;
    int numClasses;

public:
    kNN(int k = 5);
    void fit(Dataset &X_train, Dataset &y_train);
    Dataset predict(Dataset &X_test);
    double score(const Dataset &y_test, const Dataset &y_pred);
};

// Please add more or modify as needed
