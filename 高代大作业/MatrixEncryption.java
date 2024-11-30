public class MatrixEncryption
{

    private int[][] keyMatrix; // 秘钥矩阵
    private int matrixSize; // 矩阵的大小

    // 构造函数，初始化秘钥矩阵
    public MatrixEncryption(int[][] keyMatrix) {
        this.keyMatrix = keyMatrix;
        this.matrixSize = keyMatrix.length; // 是一个方阵
    }

    // 加密方法
    public String encrypt(String plaintext) {
        plaintext = removeSpacesAndToUpper(plaintext);
        int padding = calculatePadding(plaintext);
        plaintext = padText(plaintext, padding);
        return processEncryption(plaintext);
    }

    private String removeSpacesAndToUpper(String text) {
        return text.replaceAll("\\s", "").toUpperCase();
    }

    private int calculatePadding(String text) {
        return matrixSize - (text.length() % matrixSize);
    }

    private String padText(String text, int padding) {
        if (padding != matrixSize) {
            return text + "X".repeat(padding);
        }
        return text;
    }

    private String processEncryption(String cleanedText) {
        StringBuilder ciphertext = new StringBuilder();
        for (int i = 0; i < cleanedText.length(); i += matrixSize) {
            String block = cleanedText.substring(i, i + matrixSize);
            int[] encryptedBlock = encryptBlock(block);
            for (int value : encryptedBlock) {
                ciphertext.append((char) (value + 'A'));
            }
        }
        return ciphertext.toString();
    }

    private int[] encryptBlock(String block) {
        int[] encryptedBlock = new int[matrixSize];
        for (int row = 0; row < matrixSize; row++) {
            for (int col = 0; col < matrixSize; col++) {
                encryptedBlock[row] += keyMatrix[row][col] * (block.charAt(col) - 'A');
            }
            encryptedBlock[row] = (encryptedBlock[row] % 26 + 26) % 26;
        }
        return encryptedBlock;
    }
}
