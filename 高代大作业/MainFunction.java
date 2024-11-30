import javax.lang.model.util.ElementKindVisitor14;
import java.util.Scanner;

public class MainFunction
{
    public static void matrixCalculator()
    {
        {
            Scanner scanner = new Scanner(System.in);
            MatrixKey matrixKey = new MatrixKey();
            while (true)
            {
                System.out.println("Input the number of line:");
                int lineOfMatrix = scanner.nextInt();
                if (lineOfMatrix != 0)
                {
                    System.out.println("Input the elements:");
                    int[][] matrix = new int[lineOfMatrix][lineOfMatrix];
                    for (int i = 0; i < lineOfMatrix; i++)
                    {
                        for (int j = 0; j < lineOfMatrix; j++) {
                            matrix[i][j] =scanner.nextInt();
                        }
                    }
                    System.out.println("The determinant of the matrix is:" + matrixKey.determinant(matrix));
                    System.out.println("The adjoint matrix is:");
                    matrixKey.print(matrixKey.adjugate(matrix));
                    System.out.println("The inverse matrix is:");
                    matrixKey.inverse(matrix);
                }
                else
                {
                    System.out.println("Invalid Input.");
                    break;
                }
            }
        }
    }
    public static void encryptionSentence() {
        while (true) {
            Scanner scanner = new Scanner(System.in);
            System.out.println("Please enter the size of the key matrix (for example, 3 represents a 3x3 matrix):");
            int size = scanner.nextInt();
            scanner.nextLine(); // 消耗掉换行符
            int[][] keyMatrix = new int[size][size];
            MatrixKey matrixKey = new MatrixKey();

            int matrixValue = 0;
            while (matrixValue != 1) {
                System.out.println("Please enter the key matrix (input for " + size + " each row):");
                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < size; j++) {
                        keyMatrix[i][j] = scanner.nextInt();
                    }
                }
                matrixValue = matrixKey.determinant(keyMatrix);
                if (matrixValue != 1) System.out.println("Invalid Matrix! Please input again.");
            }
            String plaintext = "";
            int operation;
            System.out.println("The password is established successfully.");
            System.out.println("(1) Input 1 to enter the English sentence that needs to be encrypted.");
            System.out.println("(2) Input 2 to enter the English sentence that needs to be decrypted.");
            System.out.println("(3) Input 0 to back the main menu.");
            while (true) {
                operation=scanner.nextInt();

                if(operation==1)
                {
                 scanner.nextLine(); // 消耗掉换行符
                // 输入明文
                System.out.println("Please enter the English sentence that needs to be encrypted:");
                plaintext = scanner.nextLine();
                // 创建加密对象
                MatrixEncryption encryption = new MatrixEncryption(keyMatrix);
                // 进行加密
                String ciphertext = encryption.encrypt(plaintext);
                // 输出密文
                System.out.println("The encrypted ciphertext is:" + ciphertext);
                if(plaintext.equals("Exit")) break;
               }

                if(operation==2)
                {
                    scanner.nextLine(); // 消耗掉换行符
                    System.out.println("Please enter the English sentence that needs to be decrypted:");
                    plaintext = scanner.nextLine();
                    MatrixDecryption decryption=new MatrixDecryption(keyMatrix);
                    String decryptedText = decryption.decrypt(plaintext);
                    // 输出解密后的明文
                    System.out.println("The decrypted plaintext is: " + decryptedText);
                }
        }
    }
    }
    public static void main(String[] args)
    {
        Scanner scanner=new Scanner(System.in);
        System.out.println("(1) Input 1 to enter the matrix Calculator.");
        System.out.println("(2) Input 2 to enter the encryption software.");
        System.out.println("(3) Input 0 to exit the system.");
        int operation;
        while(true)
        {
            operation=scanner.nextInt();
            if(operation==1) matrixCalculator();
            if(operation==2) encryptionSentence();
            if(operation==0) System.exit(3);
            else System.out.println("Invalid Operation! Please try again.");
        }
    }
}
