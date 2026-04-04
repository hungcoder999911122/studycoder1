#include <iostream>
#include <vector>
#include <cmath>
#include <cfloat> // Thư viện để dùng DBL_MAX (số thực lớn nhất)

using namespace std;

// Các biến toàn cục để lưu trạng thái
int n; // Số lượng công việc
int m; // Số lượng công nhân
vector<int> v; // Mảng chứa giá trị phần thưởng của từng công việc

vector<int> worker_sums;      // Tổng phần thưởng hiện tại của mỗi công nhân
vector<int> current_assign;   // Cách chia việc hiện tại (Lưu worker_id cho từng task)
vector<int> best_assign;      // Cách chia việc tốt nhất tìm được
double min_s = DBL_MAX;       // Độ lệch chuẩn nhỏ nhất (khởi tạo bằng một số cực lớn)

// Hàm tính độ lệch chuẩn (Standard Deviation) của m người công nhân
double calculate_s() {
    if (m == 1) return 0.0; // Nếu chỉ có 1 người thì không có độ lệch

    double total_sum = 0;
    for (int i = 0; i < m; ++i) {
        total_sum += worker_sums[i];
    }
    
    // Tính giá trị trung bình (x ngang)
    double mean = total_sum / m;

    // Tính tổng bình phương độ lệch
    double variance_sum = 0;
    for (int i = 0; i < m; ++i) {
        variance_sum += (worker_sums[i] - mean) * (worker_sums[i] - mean);
    }

    // Trả về căn bậc hai (Dùng m-1 vì đây là độ lệch chuẩn mẫu cho m công nhân)
    return sqrt(variance_sum / (m - 1));
}

// Hàm đệ quy vét cạn (Brute-force / Backtracking)
void solve(int task_index) {
    // 1. ĐIỂM DỪNG: Đã phân chia xong tất cả n công việc
    if (task_index == n) {
        double current_s = calculate_s();
        
        // Nếu tìm được cách chia công bằng hơn (s nhỏ hơn) thì cập nhật
        if (current_s < min_s) {
            min_s = current_s;
            best_assign = current_assign; // Sao chép cách chia tốt nhất
        }
        return;
    }

    // 2. VÉT CẠN: Thử giao công việc hiện tại (task_index) cho từng người công nhân
    for (int j = 0; j < m; ++j) {
        // [Tiến bước] - Giao việc cho người j
        worker_sums[j] += v[task_index];
        current_assign[task_index] = j + 1; // Lưu lại (j+1 để in ra cho đẹp, từ 1 đến m)

        // [Đệ quy] - Đi sâu vào để xét tiếp công việc tiếp theo
        solve(task_index + 1);

        // [QUAY LUI - Backtracking] - Lấy lại công việc để thử giao cho người khác (j+1)
        worker_sums[j] -= v[task_index];
    }
}

int main() {
    // 1. Nhập dữ liệu
    cout << "Nhap so luong cong viec (n): ";
    cin >> n;
    cout << "Nhap so luong cong nhan (m): ";
    cin >> m;

    v.resize(n);
    cout << "Nhap phan thuong cho tung cong viec: ";
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    // Khởi tạo các mảng với kích thước tương ứng
    worker_sums.assign(m, 0);
    current_assign.resize(n);
    best_assign.resize(n);

    // 2. Chạy thuật toán (bắt đầu từ công việc 0)
    solve(0);

    // 3. In kết quả
    cout << "\n--- KET QUA ---" << endl;
    cout << "Do lech chuan nho nhat (s) = " << min_s << endl;
    
    // Tính lại tổng của cách chia tốt nhất để in ra cho rõ ràng
    vector<int> final_sums(m, 0);
    for (int i = 0; i < n; ++i) {
        int worker_id = best_assign[i];
        cout << "Cong viec " << i + 1 << " (gia tri " << v[i] << ") -> Giao cho Cong nhan " << worker_id << endl;
        final_sums[worker_id - 1] += v[i];
    }

    cout << "\nTong phan thuong cua tung cong nhan: " << endl;
    for (int j = 0; j < m; ++j) {
        cout << "Cong nhan " << j + 1 << " : " << final_sums[j] << endl;
    }

    return 0;
}
