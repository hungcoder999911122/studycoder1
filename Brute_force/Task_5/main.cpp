#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

// Biến lưu trữ các quả cân đầu vào
vector<int> weights;
int n;

void solve(int index, int leftSum, int rightSum, vector<int>& leftSide, vector<int>& rightSide) {
    // Điều kiện dừng: Đã xét hết tất cả n quả cân
    if (index == n) {
        // Kiểm tra thăng bằng và phải có ít nhất 1 quả cân trên bàn
        if (leftSum == rightSum && leftSum > 0) {
            cout << "Cach dat: [Trai] ";
            for (int w : leftSide) cout << w << " ";
            cout << "== [Phai] ";
            for (int w : rightSide) cout << w << " ";
            cout << endl;
        }
        return;
    }

    // Lựa chọn 1: Bỏ vào đĩa TRÁI
    leftSide.push_back(weights[index]);
    solve(index + 1, leftSum + weights[index], rightSum, leftSide, rightSide);//index, leftSum, rightSum là các bản sao, tham số truyền vào , 
                                                                            //còn left/right side vì có tham chiếu(thay đổi trực tiếp) nên phải làm thủ công 
    leftSide.pop_back(); // Backtrack: lấy ra để thử lựa chọn khác

    // Lựa chọn 2: Bỏ vào đĩa PHẢI
    rightSide.push_back(weights[index]);
    solve(index + 1, leftSum, rightSum + weights[index], leftSide, rightSide);
    rightSide.pop_back(); // Backtrack

    // Lựa chọn 3: KHÔNG DÙNG quả cân này
    solve(index + 1, leftSum, rightSum, leftSide, rightSide);
}

int main() {
    cout << "Nhap so luong qua can n: ";
    cin >> n;
    weights.resize(n);
    cout << "Nhap khoi luong cac qua can: ";
    for (int i = 0; i < n; i++) cin >> weights[i];

    vector<int> leftSide, rightSide;
    cout << "\nCac phuong an thang bang tim duoc:\n";
    solve(0, 0, 0, leftSide, rightSide);

    return 0;
}