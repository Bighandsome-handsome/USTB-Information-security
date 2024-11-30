import java.math.*;
import java.util.*;
import java.text.*;
public class MatrixKey
{
    public int determinant(int[][] matrix) {
        int n = matrix.length;
        if (n == 1) {
            return matrix[0][0];
        }
        if (n == 2) {
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        }
        int det = 0;
        for (int p = 0; p < n; p++) {
            int[][] submatrix = new int[n - 1][n - 1];
            for (int i = 1; i < n; i++) {
                int subRow = i - 1;
                for (int j = 0; j < n; j++) {
                    if (j != p) {
                        submatrix[subRow][j < p ? j : j - 1] = matrix[i][j];
                    }
                }
            }
            det += matrix[0][p] * (p % 2 == 0 ? 1 : -1) * determinant(submatrix);
        }
        return det;
    }

    public int[][] adjugate(int[][] matrix) {
        int n = matrix.length;
        int[][] adj = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int[][] submatrix = new int[n - 1][n - 1];
                for (int x = 0; x < n; x++) {
                    for (int y = 0; y < n; y++) {
                        if (x != i && y != j) {
                            submatrix[x < i ? x : x - 1][y < j ? y : y - 1] = matrix[x][y];
                        }
                    }
                }
                adj[i][j] = (int)(Math.pow(-1, i + j) * determinant(submatrix));
            }
        }
        return adj;
    }

    public boolean isMatrixInvertible(int[][] matrix) {
        return determinant(matrix) != 0;
    }

    public static int gcd(int m, int n) {
        int mm = m;
        int nn = n;
        if (mm < nn) {
            int c = mm;
            mm = nn;
            nn = c;
        }
        int w = 1;
        while (w != 0) {
            w = mm % nn;
            mm = nn;
            nn = w;
        }
        return mm;
    }

    public void printAnswer(int m, int n)
    {
        if (n * m < 0) {
            System.out.printf("-");
            printAnswer(Math.abs(m), Math.abs(n));
            return;
        }
        MatrixKey matrix = new MatrixKey();
        if (m == 1)
            System.out.print(n + "\t");
        else if (n % m == 0)
            System.out.print(n / m + "\t");
        else
            System.out.print((n / matrix.gcd(m, n)) + "/" + (m / matrix.gcd(m, n)) + "\t");
    }

    public int[][] inverse(int[][] matrix) {
        if (!isMatrixInvertible(matrix)) {
            throw new IllegalArgumentException("Matrix is not invertible");
        }
        int det = determinant(matrix);
        int[][] adj = adjugate(matrix);
        int[][] inv = new int[adj.length][adj[0].length];
        for (int i = 0; i < adj.length; i++) {
            for (int j = 0; j < adj[i].length; j++) {
                printAnswer((int)det,(int)adj[i][j]);
            }
            System.out.println();
        }
        return inv;
    }

    public void print(int[][] matrix) {
        int n = matrix.length;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.printf(matrix[i][j] + " ");
            }
            System.out.println();
        }
    }
}