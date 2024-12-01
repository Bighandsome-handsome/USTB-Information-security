import java.util.Scanner;

public class MainFunction {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        final int a = 10, b = 20, c=4;
        boolean test = true;
        String operation;
        while (test) {
            operation=scanner.nextLine();
            String sentence;
            //if (sentence != null && sentence.length() > 0)
            if (operation.equals("加密")) {
                System.out.print("请输入明文是：");
                sentence = scanner.nextLine();
                //String part = sentence.substring(1, sentence.length());
                Encryption encryption = new Encryption(sentence, a, b, c);
                System.out.print("加密后的秘文是:");
                encryption.printPassword();
            }
            if (operation.equals("解密")) {
                System.out.print("请输入秘文是：");
                sentence = scanner.nextLine();
                //String part = sentence.substring(1, sentence.length());
                Decrypt decrypt = new Decrypt(sentence, a, b, c);
                System.out.print("原文是：");
                System.out.println(decrypt.PasswordTransfer());
            }
            if (operation.equals("退出"))
                break;
        }
        scanner.close();
    }
}
