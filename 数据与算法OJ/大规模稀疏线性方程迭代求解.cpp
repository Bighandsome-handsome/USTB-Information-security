#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include<tuple>
using namespace std;

// 稀疏矩阵存储：用三个数组表示CSR格式
class SparseMatrix {
public:
    vector<double> values; // 存储非零元素的值
    vector<int> col_idx;   // 存储非零元素的列索引
    vector<int> row_ptr;   // 存储每一行的非零元素的起始位置
    int m;                 // 矩阵的行数

    // 构造函数，初始化行指针数组
    SparseMatrix(int m) : m(m) {
        row_ptr.resize(m + 1, 0); // 多一个元素存储结束位置
    }

    // 添加一个非零元素
    void add_value(int row, int col, double value) {
        col_idx.push_back(col);
        values.push_back(value);
        row_ptr[row + 1]++; // 增加该行的非零元素个数
    }

    // 完成行指针的最终计算并排序values和col_idx
    void finalize_and_sort() {
        // 累加每一行的非零元素数量
        for (int i = 1; i <= m; i++) {
            row_ptr[i] += row_ptr[i - 1];
        }

        // 按照行优先的顺序排序，行内按列升序排列
        //sort(idx.begin(), idx.end());

        // 根据排序后的索引重新排列values和col_idx
        /*vector<double> sorted_values(values.size());
        vector<int> sorted_col_idx(col_idx.size());
        for (int i = 0; i < idx.size(); ++i) {
            sorted_values[i] = values[idx[i]];
            sorted_col_idx[i] = col_idx[idx[i]];
        }

        values = sorted_values;
        col_idx = sorted_col_idx;*/
        

    }

    // 辅助函数：根据全局索引返回对应的行索引
    int row_of_index(int global_idx) const {
        int row_count = 0;
        for (int i = 0; i < m + 1; ++i) {
            if (global_idx < row_ptr[i]) {
                return i - 1;
            }
            row_count += row_ptr[i] - (i > 0 ? row_ptr[i - 1] : 0);
        }
        return -1; // 理论上不应该到达这里
    }

    // 矩阵与向量相乘：result = A * x
    void mat_vec_mult(const vector<double>& x, vector<double>& result) const {
        fill(result.begin(), result.end(), 0.0); // 清空结果向量
        for (int row = 0; row < m; row++) {
            // 遍历当前行的非零元素
            for (int idx = row_ptr[row]; idx < row_ptr[row + 1]; idx++) {
                int col = col_idx[idx];
                result[row] += values[idx] * x[col];
            }
        }
    }
};

// 高斯-赛德尔迭代法求解 Ax = b
void gauss_seidel(const SparseMatrix& A, const vector<double>& b, vector<double>& x, double tol = 1e-6, int max_iter = 1000) {
    int m = A.m;
    vector<double> r(m), Ap(m); // 迭代求解
    for (int iter = 0; iter < max_iter; iter++) {
        bool converged = true; // 用于判断是否收敛
        // 对每一行进行更新
        for (int row = 0; row < m; row++) {
            double sum = 0.0; // 先计算已更新部分的和
            // 遍历当前行的非零元素
            for (int idx = A.row_ptr[row]; idx < A.row_ptr[row + 1]; idx++) {
                int col = A.col_idx[idx];
                if (col < row) { // 已经更新的解
                    sum += A.values[idx] * x[col];
                }
                else if (col > row) {  // 未更新的解，忽略
                    sum += A.values[idx] * x[col];
                }
            }

            // 查找当前行的对角元素位置
            int diag_idx = -1;
            for (int idx = A.row_ptr[row]; idx < A.row_ptr[row + 1]; idx++) {
                if (A.col_idx[idx] == row) {
                    diag_idx = idx;
                    break;
                }
            }

            if (diag_idx != -1) {
                // 更新当前行的解
                double new_x = (b[row] - sum) / A.values[diag_idx];
                // 检查收敛
                if (abs(new_x - x[row]) > tol) {
                    converged = false;
                }
                // 更新解向量
                x[row] = new_x;
            }
        }

        // 计算残差 A * x = Ap
        A.mat_vec_mult(x, Ap);
        double res_norm = 0.0;
        for (int i = 0; i < m; i++) {
            r[i] = b[i] - Ap[i];
            res_norm += r[i] * r[i];
        }

        // 判断收敛性
        if (sqrt(res_norm) < tol || converged) {
            break;
        }
    }
}

int main() {
	std::ios::sync_with_stdio(false); 
    int m, k;
    cin >> m >> k;
    SparseMatrix A(m); // 创建稀疏矩阵

    // 读取稀疏矩阵的非零元素
    std :: vector<std :: tuple<int, int, double>> entries (k);
    for (int i = 0; i < k; ++i) {
        int row, col;
        double value;
        //scanf ("%d %d %1f", &row, &col, &value);
        cin>>row>>col>>value;
        entries[i] = std :: make_tuple(row, col, value);
    }
    //按照行优先的方式排列
    std :: sort(entries.begin(), entries.end());
    for(tuple<int, int, double>en:entries){
        A.add_value(get<0>(en),get<1>(en),get<2>(en));
    }

    // 完成稀疏矩阵的行指针构建并排序
    A.finalize_and_sort();

    // 读取 b 向量
    vector<double> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    // 初始化解向量 x
    vector<double> x(m, 0.0);

    // 求解 Ax = b
    gauss_seidel(A, b, x);

    // 输出结果，保留五位小数
    for (double xi : x) {
        cout << xi << endl;
    }

    return 0;
}

/*
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class SparseMatrix {
public:
    std::vector<double> values;
    std::vector<int> column_indices;
    std::vector<int> row_pointers;
    // 新增：每行非零元素在values和column_indices数组中的偏移量
    std::vector<int> row_offsets;
};

// 计算向量的二范数（即欧几里得范数）
double vectorNorm2(const std::vector<double>& v) {
    double norm_squared = 0;
    for (double val : v) {
        norm_squared += val * val;
    }
    return sqrt(norm_squared);
}

// 计算Ax - b的残差值
double residual(const SparseMatrix& A, const std::vector<double>& b, const std::vector<double>& x) {
    int N = b.size();
    std::vector<double> Ax(N);

    for (int i = 0; i < N; ++i) {
        double sum = 0;
        int rowStart = A.row_offsets[i];
        int rowEnd = A.row_offsets[i + 1];
        for (int j = rowStart; j < rowEnd; ++j) {
            int col = A.column_indices[j];
            sum += A.values[j] * x[col];
        }
        Ax[i] = sum;
    }

    std::vector<double> residual_vector(N);
    for (int i = 0; i < N; ++i) {
        residual_vector[i] = Ax[i] - b[i];
    }

    return vectorNorm2(residual_vector);
}

// 高斯-赛德尔迭代法求解线性方程组（整合优化后）
void gaussSeidel(const SparseMatrix& A, const std::vector<double>& b, std::vector<double>& x, int maxIterations, double tolerance) {
    int N = b.size();
    // 辅助向量，用于存储上一次迭代的x值
    std::vector<double> prev_x(N);

    for (int iter = 0; iter < maxIterations; ++iter) {
        // 在每次迭代开始时，先将当前的x值复制到prev_x
        std::copy(x.begin(), x.end(), prev_x.begin());

        double maxDiff = 0;
        for (int i = 0; i < N; ++i) {
            double sum = 0;
            int rowStart = A.row_offsets[i];
            int rowEnd = A.row_offsets[i + 1];
            for (int j = rowStart; j < rowEnd; ++j) {
                int col = A.column_indices[j];
                sum += A.values[j] * prev_x[col];
            }
            double newX = (b[i] - sum) / A.values[A.row_offsets[i] + i];
            double diff = std::abs(newX - x[i]);
            if (diff > maxDiff) {
                maxDiff = diff;
            }
            x[i] = newX;
        }
                
        if (maxDiff < tolerance) {
            // 计算残差值
            double res = residual(A, b, x);
            cout<<res<<endl;
            // 检查残差值是否满足要求
            if (res < tolerance) break;
            else continue;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    int m, k;
    cin >> m >> k;

    SparseMatrix A;
    A.values.resize(k);
    A.column_indices.resize(k);
    A.row_pointers.resize(m + 1);
    A.row_offsets.resize(m);

    // 读取稀疏矩阵A的非零元素并初始化row_offsets
    for (int i = 0; i < k; ++i) {
        int row, col;
        double value;
        cin >> row >> col >> value;
        A.values[i] = value;
        A.column_indices[i] = col;
        A.row_pointers[row + 1]++;
        // 初始化row_offsets
        if (i == 0) {
            A.row_offsets.push_back(0);
        } else if (A.row_pointers[row] == 0) {
            A.row_offsets.push_back(A.row_offsets.back() + 1);
        } else {
            A.row_offsets.push_back(A.row_offsets.back());
        }
    }

    // 计算每行非零元素的起始位置（虽然这里row_pointers的作用有所变化，但保留此计算以兼容可能的其他用途）
    for (int i = 1; i <= m; ++i) {
        A.row_pointers[i] += A.row_pointers[i - 1];
    }

    vector<double> b(m);
    // 读取向量b
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }

    // 初始化解向量x
    vector<double> x(m, 0);

    // 设置最大迭代次数和容差
    int maxIterations = 1000;
    double tolerance = 0.1;

    // 使用高斯-赛德尔迭代法求解线性方程组
    gaussSeidel(A, b, x, maxIterations, tolerance);

    // 输出解向量x，设置输出精度
    for (int i = 0; i < m; ++i) {
        std::cout << fixed << setprecision(5) << x[i] << endl;
    }

    return 0;
}
*/