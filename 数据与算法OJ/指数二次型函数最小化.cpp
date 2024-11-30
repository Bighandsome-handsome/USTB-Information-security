#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
double epsilon=1e-6;
using namespace std;
// �������ͱ���
typedef vector<double> Vector;
typedef vector<Vector> Matrix;
// ��ȡ��������
void read_input(int &N, Matrix &A, Vector &b) 
{
    cin >> N;
    A.resize(N, Vector(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> A[i][j];
        }
    }
    b.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> b[i];
    }
}

// ���������Ķ�����
double norm(const Vector &v) 
{
    double sum = 0.0;
    for (double val : v) {
        sum += val * val;
    }
    return sqrt(sum);
}

// �������������ĳ˻�
Vector mat_vec_mul(const Matrix &A, const Vector &x) 
{
    int N = x.size();
    Vector result(N, 0.0);
    for (int i = 0; i < N; ++i) 
	{
        double sum = 0.0;
        for (int j = 0; j < N; ++j) 
            sum += A[i][j] * x[j];
        result[i] = sum;
    }
    return result;
}
// �������
double dot_product(const Vector &a, const Vector &b) 
{
    double sum = 0.0;
    int N = a.size();
    for (int i = 0; i < N; ++i) 
        sum += a[i] * b[i];
    return sum;
}

// ����Ŀ�꺯�� f(x)
double compute_f(const Vector &x, const Matrix &A, const Vector &b) 
{
    double xTAx = dot_product(x, mat_vec_mul(A, x));
    double exp_term = exp(0.5 * xTAx);
    double bt_x = dot_product(b, x);
    return exp_term - bt_x;
}

// ţ�ٷ��������
Vector newton_method(int N, const Matrix &A, const Vector &b, double &f_min, double epsilon) 
{
    Vector x(N, 0.0); // ��ʼֵ x0
    Vector x_new(N, 0.0);
    double alpha = 0.25; // ��ʼ������ ��
    double val_0 = compute_f(x, A, b); // ��ʼ����ֵ
    while (1)
	{
        Vector Ax = mat_vec_mul(A, x);
        double xTAx = dot_product(x, Ax);
        double exp_term = exp(0.5 * xTAx);
        // ���� g(x)
        Vector g(N);
        for (int i = 0; i < N; ++i)   g[i] = exp_term * Ax[i] - b[i];
        // �����ſɱȾ���ĶԽ���Ԫ�أ������� delta_x
        Vector J_diag(N);
        Vector delta_x(N);
        for (int i = 0; i < N; ++i) 
		{
            double Aii = A[i][i];
            double Ai_x = Ax[i];
            J_diag[i] = exp_term * (Aii + Ai_x * Aii);
            if (fabs(J_diag[i]) < 1e-8) 
                J_diag[i] = 1e-8; // ��ֹ������
            delta_x[i] = -alpha * (g[i] / J_diag[i]);
            x_new[i] = x[i] + delta_x[i];
        }
        // �����µĺ���ֵ
        double val_1 = compute_f(x_new, A, b);
        // �����������������ֵ�������������������������ָ� x_new
        while (val_1 > val_0) 
		{
            alpha /= 2; // ��������
            // ���¼��� delta_x �� x_new
            for (int i = 0; i < N; ++i) {
            	
                delta_x[i] = -alpha * (g[i] / J_diag[i]);
                x_new[i] = x[i] + delta_x[i];
            }
            val_1 = compute_f(x_new, A, b);
        }
        // ���� x �ͺ���ֵ
        x = x_new;
        // �ж�������
        if (fabs(val_1 - val_0) < epsilon) 
		{
            f_min = val_1;
            break;
        }
       val_0 = val_1; // ���º���ֵ
    }
    return x;
}

int main() {
    int N;
    Matrix A;
    Vector b;
    read_input(N, A, b);

    // ���ò���
    double epsilon = 1e-6; // ��������
    double f_min = 0.0;

    Vector x_solution = newton_method(N, A, b, f_min, epsilon);

    // ������������4λС��
    cout << fixed << setprecision(4) << f_min << endl;

    return 0;
}

