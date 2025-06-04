#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

// MaxPQ 抽象類別
template <class T>
class MaxPQ {
public:
    virtual ~MaxPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};

// MaxHeap 類別
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
