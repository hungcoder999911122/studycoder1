#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// SỬ DỤNG STRUCT ĐỂ QUẢN LÝ DỮ LIỆU 
struct Point {
    int x, y;
};

struct Robot {
    string name;
    Point pos;
    long long totalScore = 0;
    vector<int> path;
    bool isStuck = false;
    bool isActive = false; // Trạng thái robot có tham gia chơi không
};

int N, M;
int **matrix;     // CẤP PHÁT ĐỘNG 
bool **visited;   // CẤP PHÁT ĐỘNG 

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool isValid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < M && matrix[x][y] > 0 && !visited[x][y]);
}

// SỬ DỤNG ĐỆ QUY ĐỂ TÌM Ô KẾ TIẾP TỐT NHẤT 
void findBestNeighbor(int currX, int currY, int index, int &maxVal, int &nextX, int &nextY) {
    if (index == 4) return; 

    int nx = currX + dx[index];
    int ny = currY + dy[index];

    if (isValid(nx, ny)) {
        if (matrix[nx][ny] > maxVal) {
            maxVal = matrix[nx][ny];
            nextX = nx;
            nextY = ny;
        }
    }
    findBestNeighbor(currX, currY, index + 1, maxVal, nextX, nextY);
}

bool moveOneStep(Robot &rb) {
    if (!rb.isActive || rb.isStuck) return false;

    int nextX = -1, nextY = -1, maxVal = -1;
    findBestNeighbor(rb.pos.x, rb.pos.y, 0, maxVal, nextX, nextY);

    if (nextX != -1) {
        rb.pos = {nextX, nextY};
        visited[nextX][nextY] = true;
        rb.totalScore += matrix[nextX][nextY];
        rb.path.push_back(matrix[nextX][nextY]);
        return true;
    } else {
        rb.isStuck = true;
        return false;
    }
}

int main() {
    // ĐỌC FILE INPUT.TXT 
    ifstream inFile("input.txt");
    if (!inFile) {
        cout << "Khong the mo file input.txt!" << endl;
        return 1;
    }

    inFile >> N >> M;
    matrix = new int*[N];
    visited = new bool*[N];
    for (int i = 0; i < N; i++) {
        matrix[i] = new int[M];
        visited[i] = new bool[M];
        for (int j = 0; j < M; j++) {
            inFile >> matrix[i][j];
            visited[i][j] = false;
        }
    }
    inFile.close();

    int mode;
    cout << "--- ROBOT TIM DUONG ---" << endl;
    cout << "1. Che do 1 Robot (Luyen tap)" << endl;
    cout << "2. Che do 2 Robot (Doi khang)" << endl;
    cout << "Chon che do (1-2): ";
    cin >> mode;

    Robot r1, r2;
    r1.name = "Robot 1";
    r2.name = "Robot 2";

    // Thiết lập Robot 1 luôn hoạt động
    r1.isActive = true;
    cout << "Nhap vi tri Robot 1 (x y): ";
    cin >> r1.pos.x >> r1.pos.y;

    if (mode == 2) {
        r2.isActive = true;
        cout << "Nhap vi tri Robot 2 (x y): ";
        cin >> r2.pos.x >> r2.pos.y;
    }

    // Kiểm tra tính hợp lệ ban đầu
    if (!isValid(r1.pos.x, r1.pos.y) || (mode == 2 && (!isValid(r2.pos.x, r2.pos.y) || (r1.pos.x == r2.pos.x && r1.pos.y == r2.pos.y)))) {
        cout << "Vi tri nhap vao khong hop le hoac bi trung!" << endl;
        return 1;
    }

    // Đánh dấu vị trí xuất phát
    visited[r1.pos.x][r1.pos.y] = true;
    r1.path.push_back(matrix[r1.pos.x][r1.pos.y]);
    r1.totalScore += matrix[r1.pos.x][r1.pos.y];

    if (r2.isActive) {
        visited[r2.pos.x][r2.pos.y] = true;
        r2.path.push_back(matrix[r2.pos.x][r2.pos.y]);
        r2.totalScore += matrix[r2.pos.x][r2.pos.y];
    }

    // LOGIC DI CHUYỂN LUÂN PHIÊN [cite: 25]
    bool r1Moving = true, r2Moving = r2.isActive;
    while (r1Moving || r2Moving) {
        if (r1Moving) r1Moving = moveOneStep(r1);
        if (r2Moving) r2Moving = moveOneStep(r2);
    }

    // XUẤT KẾT QUẢ [cite: 26]
    ofstream outFile("output.txt");
    auto printResult = [&](Robot rb) {
        if (!rb.isActive) return;
        cout << "\n=== " << rb.name << " ===" << endl;
        cout << "Diem: " << rb.totalScore << endl;
        cout << "Duong di: ";
        outFile << rb.name << " - Diem: " << rb.totalScore << "\nPath: ";
        for (int v : rb.path) {
            cout << v << " ";
            outFile << v << " ";
        }
        cout << endl;
        outFile << "\n\n";
    };

    printResult(r1);
    printResult(r2);

    if (mode == 2) {
        cout << "\n--- SO SANH ---" << endl;
        if (r1.totalScore > r2.totalScore) cout << "Robot 1 thang!" << endl;
        else if (r2.totalScore > r1.totalScore) cout << "Robot 2 thang!" << endl;
        else cout << "Hai robot hoa nhau!" << endl;
    }

    // GIẢI PHÓNG BỘ NHỚ 
    for (int i = 0; i < N; i++) {
        delete[] matrix[i];
        delete[] visited[i];
    }
    delete[] matrix; delete[] visited;
    outFile.close();
    return 0;
}