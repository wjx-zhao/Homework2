#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
using namespace std;

// 節點結構
struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

// 插入節點
Node* insert(Node* root, int key) {
    if (!root) return new Node(key);
    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    return root;
}

// 計算樹高度
int getHeight(Node* root) {
    if (!root) return 0;
    int l = getHeight(root->left);
    int r = getHeight(root->right);
    return 1 + max(l, r);
}

// 中序遍歷
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

// 找中序後繼（右子樹中的最小值）
Node* findMin(Node* node) {
    while (node->left) node = node->left;
    return node;
}

// 刪除節點
Node* deleteNode(Node* root, int key) {
    if (!root) return nullptr;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    else {
        // 找到要刪除的節點
        if (!root->left) {
            Node* rightChild = root->right;
            delete root;
            return rightChild;
        }
        else if (!root->right) {
            Node* leftChild = root->left;
            delete root;
            return leftChild;
        }
        else {
            // 兩個子節點：找到中序後繼，替換值並遞迴刪除後繼
            Node* succ = findMin(root->right);
            root->key = succ->key;
            root->right = deleteNode(root->right, succ->key);
        }
    }
    return root;
}

// 刪除整棵樹
void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// 主程式
int main() {
    srand(time(0));

    // ========== (a) 隨機插入 & 計算比值 ==========
    vector<int> ns = { 100, 500, 1000, 2000, 3000, 5000, 10000 };
    cout << "=== (a) BST 高度與 log2(n) 比值 ===" << endl;
    cout << "n\theight\tlog2(n)\tratio (height/log2n)" << endl;

    for (int n : ns) {
        Node* root = nullptr;
        for (int i = 0; i < n; i++) {
            int val = rand();
            root = insert(root, val);
        }

        int height = getHeight(root);
        double log2n = log2(n);
        double ratio = height / log2n;

        cout << n << "\t" << height << "\t" << log2n << "\t" << ratio << endl;

        deleteTree(root);
    }

    // ========== (b) 刪除節點測試 ==========
    cout << "\n=== (b) BST 節點刪除測試 ===" << endl;
    Node* root = nullptr;
    int keys[] = { 50, 30, 20, 40, 70, 60, 80 };
    for (int key : keys) {
        root = insert(root, key);
    }

    cout << "BST 中序遍歷（刪除前）: ";
    inorder(root);
    cout << endl;

    cout << "刪除 20（葉節點）..." << endl;
    root = deleteNode(root, 20);
    inorder(root);
    cout << endl;

    cout << "刪除 30（有一個子節點）..." << endl;
    root = deleteNode(root, 30);
    inorder(root);
    cout << endl;

    cout << "刪除 50（有兩個子節點）..." << endl;
    root = deleteNode(root, 50);
    inorder(root);
    cout << endl;

    deleteTree(root);

    // ========== (b) 刪除時間複雜度說明 ==========
    cout << "\n=== 刪除函式時間複雜度說明 ===" << endl;
    for (int n : ns) {
        double log2n = log2(n);
        cout << "n=" << n
            << "，平均比較次數約 2*log2(n)=" << 2 * log2n
            << "，最壞比較次數=" << n << endl;
    }

    cout << "說明：" << endl;
    cout << "平均情況時間複雜度：O(log n)，例如 n=10000 平均比較次數約 26。" << endl;
    cout << "最壞情況時間複雜度：O(n)，例如 n=10000 需最多比較 10000 次（退化成鏈狀）。" << endl;

    return 0;
}
