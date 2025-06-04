# 41243201 
# 41243203

作業二

本作業要求實現Max/Min Heap、Binary Search Tree、exercise 1

---  

# **Max/Min Heap**

## 題目要求
- 撰寫一個 C++ 抽象類別，類似於 ADT 5.2 中的 ADT MinPQ，該類別定義一個最小優先佇列接著，撰寫一個從此抽象類別衍生出來的 C++ 類別 MinHeap，並實作 MinPQ 中所有虛擬函式每個函式的複雜度應該和對應的 MaxHeap 函式相同。 
  
## 解題說明

## 程式實作

以下為主要程式碼：  
使用的標頭  
```cpp

```
 
```cpp

```

  
```cpp

``` 
  
```cpp

```  
  
  
```cpp


```  
  

```cpp

```



## 測試與驗證

### 測試案例



### 測試結果範例  




## 申論及開發報告

1. 

2.

3.



# **Binary Search Tree**

## 題目要求
- (a)寫一個程式，從一棵最初為空的二元搜尋樹（BST）開始，並進行 n 筆隨機插入。
使用均勻隨機數產生器來產生要插入的值。
接著，量測最終得到的二元搜尋樹的高度，並將此高度除以log2𝑛對於以下 n 值進行測試：
n=100,500,1000,2000,3000,…,10,000。
- (b)
寫一個 C++ 函式，從二元搜尋樹中刪除鍵值為 k 的節點，並說明這個函式的時間複雜度。
## 解題說明
### 節點結構 & 插入邏輯
- 以 Node 結構表示樹的節點（包含 key、左右子樹指標）。
- insert 函式用遞迴方式，根據 BST 規則放入新 key（左小右大）。
```cpp
struct Node { ... };
Node* insert(Node* root, int key) { ... }
```
### 高度計算 & 中序遍歷
- getHeight：回傳樹的高度（root 高度為 1）。
- inorder：中序列印樹節點，用來檢查 BST 結構正確性。

```cpp
int getHeight(Node* root) { ... }
void inorder(Node* root) { ... }
```
### 刪除節點操作
- findMin：找到某棵樹的最小值（右子樹的中序後繼節點）。

- deleteNode：
 - 若節點是葉節點 ➜ 直接刪除。
 - 若節點只有一個子節點 ➜ 讓子節點接替。
 - 若有兩個子節點 ➜ 找右子樹最小值（中序後繼），複製值後再刪除後繼。
```cpp
Node* findMin(Node* node) { ... }
Node* deleteNode(Node* root, int key) { ... }
```
### 隨機插入 + 計算比值
- 隨機插入 n 筆整數（rand()）。
計算：
1.最終高度
2.log2n比值
3.比值 高度/log2n
  - 列印出結果，驗證「高度~=2⋅log2n」。
```cpp
vector<int> ns = { 100, 500, 1000, 2000, 3000, 5000, 10000 };
for (int n : ns) { ... }

```
## 程式實作

以下為主要程式碼：
這是使用到的標頭檔  
```cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
using namespace std;
```
節點結構與插入節點
```cpp
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
```
計算樹的高度
```cpp
int getHeight(Node* root) {
    if (!root) return 0;
    int l = getHeight(root->left);
    int r = getHeight(root->right);
    return 1 + max(l, r);
}
```
中序遍歷
```cpp
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}
```
找中序後繼（右子樹中的最小值）
```cpp
Node* findMin(Node* node) {
    while (node->left) node = node->left;
    return node;
}
```
刪除節點
```cpp
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

```
刪除整棵樹
```cpp
void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
```
主程式
```cpp
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
```
刪除節點
```cpp
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
```
刪除時間複雜度說明
```cpp
cout << "\n=== 刪除函式時間複雜度說明 ===" << endl;
for (int n : ns) {
    double log2n = log2(n);
    cout << "n=" << n
        << "，平均比較次數約 2*log2(n)=" << 2 * log2n
        << "，最壞比較次數=" << n << endl;
}
```
## 效能分析

### 時間複雜度  
| n     | log₂(n)  (平均樹高度) | 最壞情況高度 (鏈狀) |
| ----- | ---------------- | ----------- |
| 100   | ≈ 6.64           | 100         |
| 500   | ≈ 8.97           | 500         |
| 1000  | ≈ 9.97           | 1000        |
| 5000  | ≈ 12.3           | 5000        |
| 10000 | ≈ 13.3           | 10000       |


## 測試與驗證

### 測試結果範例

![BST 二元搜尋樹示意圖](https://raw.githubusercontent.com/Lin-3203/image/main/BST.png)

## 申論及開發報告

1.

2.

3.

# **exercise 1**

## 題目要求
- (a)有 n 筆記錄要在一台電腦上進行排序，該電腦的記憶體容量為 S 筆記錄（且S≪n）。假設整個 S-筆記錄的容量可用作輸入/輸出緩衝區。輸入資料位於磁碟上，總共分成 m 個 runs。
假設每次進行磁碟存取時，搜尋時間為ts，延遲時間為tl，每筆記錄的傳輸時間為tt。
若使用 k-路合併、並將內部記憶體分區作為輸入/輸出緩衝區（以允許輸入、輸出及 CPU 處理重疊，類似於 Buffering 中所述的方式（程式 7.21）），請問 phase two（外部排序的第二階段）的總輸入時間是多少？
- (b)假設合併所有 runs 的 CPU 所需時間為 tCPU（我們假設它與 k 無關，因此為常數）。給定：𝑡𝑠=80ms,𝑡𝑙=20ms,𝑛=200,000,𝑚=64,𝑡𝑡=10^−3秒/筆記錄S=2000
請大略繪製總輸入時間  t input 與k 的關係圖。並回答：是否永遠存在某個k 值，能使 t CPU≈t input？

## 解題說明
- 


## 程式實作

以下為主要程式碼：
這是使用到的標頭檔  

```cpp

``` 
 
```cpp


```

```cpp

```

```cpp


```

```cpp

```

## 效能分析

### 時間複雜度


## 測試與驗證

### 測試案例



### 測試結果範例  




## 申論及開發報告
1.

2.  

3.  



