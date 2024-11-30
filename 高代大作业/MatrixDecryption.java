public class MatrixDecryption {
    private int[][] keyMatrix; // 秘钥矩阵
    private int matrixSize; // 矩阵的大小

    public MatrixDecryption(int[][] keyMatrix) {
        this.keyMatrix = findInverse(keyMatrix);
        this.matrixSize = keyMatrix.length;
    }

    private int[][] findInverse(int[][] matrix) {
        MatrixKey matrixKey=new MatrixKey();
        return matrixKey.inverse(matrix);
    }

    public String decrypt(String ciphertext) {
        StringBuilder plaintext = new StringBuilder();
        for (int i = 0; i < ciphertext.length(); i += matrixSize) {
            String block = ciphertext.substring(i, i + matrixSize);
            int[] decryptedBlock = decryptBlock(block);
            for (int value : decryptedBlock) {
                plaintext.append((char) (value + 'A'));
            }
        }
        return plaintext.toString().replaceAll("X", "");
    }

    private int[] decryptBlock(String block) {
        int[] decryptedBlock = new int[matrixSize];
        for (int row = 0; row < matrixSize; row++) {
            for (int col = 0; col < matrixSize; col++) {
                decryptedBlock[row] += keyMatrix[row][col] * (block.charAt(col) - 'A');
            }
            decryptedBlock[row] = (decryptedBlock[row] % 26 ) % 26;
        }
        return decryptedBlock;
    }
}
