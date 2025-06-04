#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    // 題目給定的參數
    double t_s = 0.08;       // seek time (秒)
    double t_l = 0.02;       // latency time (秒)
    double t_t = 0.001;      // 傳輸一筆記錄時間 (秒)
    int n = 200000;          // 總資料筆數
    int m = 64;              // runs 數量
    int S = 2000;            // 可使用記憶體 (筆數)
    double t_CPU = 50000;    // 假設 CPU 處理合併時間 (秒)，僅示例用

    // 可測試的 k 路合併值
    vector<int> k_values = { 2, 4, 8, 16, 32, 64 };

    // 計算單筆記錄的輸入時間
    double t_record = t_s + t_l + t_t;

    cout << "--------------------------------------" << endl;
    cout << "外部合併排序 (Phase 2) 總輸入時間計算" << endl;
    cout << "每筆記錄輸入時間: " << t_record << " 秒" << endl;
    cout << "--------------------------------------" << endl;

    cout << fixed << setprecision(3);
    cout << " k\tceil(log_k(m))\tt_input (秒)" << endl;

    // 逐個 k 值計算
    for (int k : k_values) {
        // 計算 ceil(log_k m)
        double log_k_m = log(m) / log(k);
        int num_passes = static_cast<int>(ceil(log_k_m));

        // Phase 2 總輸入時間
        double t_input = 2 * n * t_record * num_passes;

        // 輸出
        cout << setw(2) << k << "\t" << setw(10) << num_passes
            << "\t\t" << setw(10) << t_input << endl;

        // 提示是否接近 CPU 處理時間
        if (abs(t_input - t_CPU) < 5000) {
            cout << "  --> t_input ≈ t_CPU (可能最佳 k 值)" << endl;
        }
    }

    cout << endl;
    cout << "說明：" << endl;
    cout << "1. 本程式僅計算 I/O 時間 (不含實際檔案操作)" << endl;
    cout << "2. 若已知 CPU merge 時間 t_CPU，可比較是否存在 k 使得 t_input ≈ t_CPU" << endl;
    cout << "--------------------------------------" << endl;

    return 0;
}
