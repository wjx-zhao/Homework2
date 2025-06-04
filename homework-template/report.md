# 41243201 
# 41243203

作業二

本作業要求實現Max/Min Heap、Binary Search Tree、exercise 1

---  

# **Max/Min Heap**

## 題目要求
- 撰寫一個 C++ 抽象類別，類似於 ADT 5.2 中的 ADT MinPQ，該類別定義一個最小優先佇列接著，撰寫一個從此抽象類別衍生出來的 C++ 類別 MinHeap，並實作 MinPQ 中所有虛擬函式每個函式的複雜度應該和對應的 MaxHeap 函式相同。 
  
## 解題說明
-最大堆積 (Max Heap)：每個父節點的值 ≥ 左右子節點 → 父節點最大，root是最大值。  
-最小堆積 (Min Heap)：每個父節點的值 ≤ 左右子節點 → 父節點最小，root是最小值。  

-index 0 為 root 節點：  
  1.父節點：(i - 1)/2  
  2.左子節點：2*i + 1  
  3.右子節點：2*i + 2  
  
-插入（Push）  
1️.把新元素放在陣列的最後面。  
2️.執行「Bubble Up / Shift Up」  

-刪除頂端（Pop）  
1️.把最後一個元素移到 root（堆頂）。
2️.移.除最後一個元素（現在 root 元素重複了）。
3️.執行「Bubble Down / Shift Down」  

## 程式實作

以下為最大堆積主要程式碼：  
使用的標頭  
```cpp
#include <iostream>
#include <vector>
#include <stdexcept>
```
MaxPQ 抽象類別  
```cpp
template <class T>
class MaxPQ {
public:
    virtual ~MaxPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};
```

MaxHeap 類別  
```cpp
template <class T>
class MaxHeap : public MaxPQ<T> {
private:
    vector<T> heap;

    void BubbleUp(int index) {
        while (index > 0 && heap[(index - 1) / 2] < heap[index]) {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    void BubbleDown(int index) {
        int size = heap.size();
        int child = 2 * index + 1;
        while (child < size) {
            if (child + 1 < size && heap[child] < heap[child + 1])
                child++;
            if (heap[index] >= heap[child])
                break;
            swap(heap[index], heap[child]);
            index = child;
            child = 2 * index + 1;
        }
    }

public:
    bool IsEmpty() const override {
        return heap.empty();
    }

    const T& Top() const override {
        if (IsEmpty())
            throw runtime_error("Heap 為空");
        return heap[0];
    }

    void Push(const T& e) override {
        heap.push_back(e);
        BubbleUp(heap.size() - 1);
        cout << "Push後 " << e << ", heap: ";
        PrintHeap();
    }

    void Pop() override {
        if (IsEmpty())
            throw runtime_error("Heap 為空，無法刪除");
        cout << "移除頂端元素: " << heap[0] << endl;
        heap[0] = heap.back();
        heap.pop_back();
        if (!IsEmpty())
            BubbleDown(0);
        cout << "移除後的Heap: ";
        PrintHeap();
    }

    void PrintHeap() const {
        for (const auto& val : heap)
            cout << val << " ";
        cout << endl;
    }

    // 產生一個複製堆，並輸出真正的「大到小排序」結果
    void PrintSortedHeap() {
        MaxHeap<T> copy = *this; // 複製堆
        cout << "\n最終排序順序: ";
        while (!copy.IsEmpty()) {
            cout << copy.Top() << " ";
            copy.Pop();
        }
        cout << endl;
    }
};
``` 
main函式    
```cpp
int main() {
    MaxHeap<int> maxHeap;
    int n;

    cout << "請輸入有多少筆資料加入堆疊: ";
    cin >> n;

    cout << "輸入 " << n << " 整數:\n";
    for (int i = 0; i < n; ++i) {
        int value;
        cout << "Push第 " << (i + 1) << " 筆資料: ";
        cin >> value;
        maxHeap.Push(value);
    }

    cout << "\n頂端元素: " << maxHeap.Top() << endl;

    cout << "\n移除頂端元素:\n";
    while (!maxHeap.IsEmpty()) {
        maxHeap.Pop();
    }

    system("pause");
    return 0;
}
```  
  
以下為最小堆積主要程式碼：    
```cpp
#include <iostream>
#include <vector>
#include <stdexcept>
```  
  
MinPQ 抽象類別  
```cpp
template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};
```
MinHeap 類別  
```cpp
template <class T>
class MinHeap : public MinPQ<T> {
private:
    vector<T> heap;

    void BubbleUp(int index) {
        while (index > 0 && heap[(index - 1) / 2] > heap[index]) {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    void BubbleDown(int index) {
        int size = heap.size();
        int child = 2 * index + 1;
        while (child < size) {
            if (child + 1 < size && heap[child] > heap[child + 1])
                child++;
            if (heap[index] <= heap[child])
                break;
            swap(heap[index], heap[child]);
            index = child;
            child = 2 * index + 1;
        }
    }

public:
    bool IsEmpty() const override {
        return heap.empty();
    }

    const T& Top() const override {
        if (IsEmpty())
            throw runtime_error("Heap 為空");
        return heap[0];
    }

    void Push(const T& e) override {
        heap.push_back(e);
        BubbleUp(heap.size() - 1);
        cout << "Push後 " << e << ", heap: ";
        PrintHeap();
    }

    void Pop() override {
        if (IsEmpty())
            throw runtime_error("Heap 為空，無法刪除");
        cout << "移除頂端元素: " << heap[0] << endl;
        heap[0] = heap.back();
        heap.pop_back();
        if (!IsEmpty())
            BubbleDown(0);
        cout << "移除後的Heap: ";
        PrintHeap();
    }

    void PrintHeap() const {
        for (const auto& val : heap)
            cout << val << " ";
        cout << endl;
    }

    // 產生一個複製堆，並輸出真正的「小到大排序」結果
    void PrintSortedHeap() {
        MinHeap<T> copy = *this; // 複製堆
        cout << "\n最終排序順序: ";
        while (!copy.IsEmpty()) {
            cout << copy.Top() << " ";
            copy.Pop();
        }
        cout << endl;
    }
};
```
main函式  
```cpp
int main() {
    MinHeap<int> minHeap;
    int n;

    cout << "請輸入有多少筆資料加入堆疊: ";
    cin >> n;

    cout << "輸入 " << n << " 整數:\n";
    for (int i = 0; i < n; ++i) {
        int value;
        cout << "Push第 " << (i + 1) << " 筆資料: ";
        cin >> value;
        minHeap.Push(value);
    }

    cout << "\n頂端元素: " << minHeap.Top() << endl;

    cout << "\n移除頂端元素:\n";
    while (!minHeap.IsEmpty()) {
        minHeap.Pop();
    }


    system("pause");
    return 0;
}
```

## 測試與驗證

### 測試結果範例  
最大堆積測驗結果  
![MaxHeap](https://github.com/wjx-zhao/data1/blob/a39b8617cc981eda337a4a64001beb242db9882f/MaxHeap.png)  

最小堆積測驗結果  
![MinHeap](https://github.com/wjx-zhao/data1/blob/a39b8617cc981eda337a4a64001beb242db9882f/MinHeap.png)  

## 申論及開發報告
在許多資料結構與演算法問題中，如何在資料集中快速找到最大值或最小值是常見需求。  
堆積（Heap） 是一種高效支援動態插入、刪除與查詢堆頂的資料結構，常用於優先佇列（Priority Queue） 實作。  

**最大堆積（Max Heap）**  
- 根節點最大，且每個父節點值 ≥ 子節點值。
- 適用於「動態取最大值」的情境。

**最小堆積（Min Heap）**  
- 根節點最小，且每個父節點值 ≤ 子節點值。
- 適用於「動態取最小值」的情境。  

**插入（Push）**  
- 新值放在陣列最後
- 進行 向上冒泡（Bubble Up），直到符合堆積性質  

**刪除頂端（Pop）**  
- 將最後一個值移到 root
- 刪除最後一個元素
- 進行 向下冒泡（Bubble Down），直到符合堆積性質

**時間複雜度**  
`Push()、Pop()`：$O(log n)$  

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

1.二元搜尋樹（BST）是基礎且實用的資料結構之一，廣泛應用於排序、搜尋以及資料庫系統中的索引。由於它具備平均搜尋、插入、刪除 O(logn) 的效率，對於大量資料操作而言，BST 具有非常好的效能表現。

2.根據理論，計算：平均比較次數 ≈2⋅log2n ，最壞情況比較次數=n

3.刪除操作邏輯

✅ 若節點為葉節點：直接刪除。

✅ 若節點有一個子節點：子節點接替父節點。

✅ 若節點有兩個子節點：

1️⃣ 找右子樹最小節點（中序後繼）

2️⃣ 複製中序後繼的值到要刪除的節點

3️⃣ 遞迴刪除中序後繼節點

# **exercise 1**

## 題目要求
- (a)有 n 筆記錄要在一台電腦上進行排序，該電腦的記憶體容量為 S 筆記錄（且S≪n）。假設整個 S-筆記錄的容量可用作輸入/輸出緩衝區。輸入資料位於磁碟上，總共分成 m 個 runs。
假設每次進行磁碟存取時，搜尋時間為ts，延遲時間為tl，每筆記錄的傳輸時間為tt。
若使用 k-路合併、並將內部記憶體分區作為輸入/輸出緩衝區（以允許輸入、輸出及 CPU 處理重疊，類似於 Buffering 中所述的方式（程式 7.21）），請問 phase two（外部排序的第二階段）的總輸入時間是多少？
- (b)假設合併所有 runs 的 CPU 所需時間為 tCPU（我們假設它與 k 無關，因此為常數）。給定：𝑡𝑠=80ms,𝑡𝑙=20ms,𝑛=200,000,𝑚=64,𝑡𝑡=10^−3秒/筆記錄S=2000
請大略繪製總輸入時間  t input 與k 的關係圖。並回答：是否永遠存在某個k 值，能使 t CPU≈t input？

## 解題說明
✅ 計算公式

  1️⃣ 每筆記錄的輸入時間𝑡record=𝑡𝑠+𝑡𝑙+𝑡𝑡=0.08+0.02+0.001=0.101秒
  
  2️⃣ 每個 k-路合併 pass 的次數⌈logk m⌉=⌈ logk/logm⌉
  
  3️⃣ Phase 2 總輸入時間 𝑡input=2⋅𝑛⋅𝑡record⋅⌈log𝑘 𝑚⌉

✅ 程式邏輯說明

  1️⃣ 輸入參數
  
```cpp
在 main 裡宣告：
double t_s = 0.08, t_l = 0.02, t_t = 0.001;
int n = 200000, m = 64, S = 2000;
double t_CPU = 50000;  // 供比較用   
```
    
  2️⃣ 計算單筆輸入時間
  
```cpp   
double t_record = t_s + t_l + t_t;  
```
    
  3️⃣ 對多個 k 值（2, 4, 8, 16, 32, 64）進行計算
  
```cpp  
double log_k_m = log(m) / log(k);
int num_passes = ceil(log_k_m);
double t_input = 2 * n * t_record * num_passes;
```
  4️⃣ 比較是否有接近 CPU 時間的 k
  
```cpp
if (abs(t_input - t_CPU) < 5000) {
cout << "  --> t_input ≈ t_CPU (可能最佳 k 值)" << endl;}
```
## 程式實作

以下為主要程式碼：
這是使用到的標頭檔  

```cpp
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;
``` 
計算單筆記錄的輸入時間
```cpp
double t_record = t_s + t_l + t_t;
```
逐個 k 值計算
```cpp
for (int k : k_values) {
    // 計算 ceil(log_k m)
    double log_k_m = log(m) / log(k);
    int num_passes = static_cast<int>(ceil(log_k_m));
```
Phase 2 總輸入時間
```cpp
double t_input = 2 * n * t_record * num_passes;
```
輸出
```cpp
cout << setw(2) << k << "\t" << setw(10) << num_passes
    << "\t\t" << setw(10) << t_input << endl;
```
提示是否接近 CPU 處理時間
```cpp
    if (abs(t_input - t_CPU) < 5000) {
        cout << "  --> t_input ≈ t_CPU (可能最佳 k 值)" << endl;
    }
}
```


## 效能分析

### 時間複雜度
主要運算量是針對 k 進行 log、ceil 計算 ➜ O(1)，不依賴 n 的大小。

由於 k 值數量固定，整個程式的時間複雜度為 O(1)（常數時間）。

## 測試與驗證

### 圖表
![t input and k](https://raw.githubusercontent.com/Lin-3203/image/main/t%20input%20and%20k%20.png)

### 測試結果範例  
![E1 圖片說明](https://raw.githubusercontent.com/Lin-3203/image/main/E1.png)

## 申論及開發報告
1.在處理大量資料時，外部排序（External Sorting），尤其是當資料量遠大於記憶體容量（S ≪ n）時。外部排序通常分為兩個階段：
    - 產生初始 runs（Phase One）
    - 多路合併（Phase Two）
    
2. 由於 ceil(log_k m) 隨 k 增大而減少，t_input 呈現明顯下降趨勢。
    - 只要資料量與 I/O 時間足夠大，理論上必定會存在某個 k 使得 t_input ≈ t_CPU，此為外部排序效能調校的重要理論基礎。
    - 這也是為何在真實資料庫系統中，經常需要針對不同環境參數調整最佳合併路數 k。
      
3.程式證明了在外部合併排序中，k 的選擇對 I/O 時間有極大影響。  



