public class Decrypt {
    private String sentence;
    final int minRandom = 300, maxRandom = 999;
    public int a, b, c;

    public Decrypt(String sentence, int a, int b, int c) {
        this.sentence = sentence;
        this.a = a;
        this.b = b;
        this.c = c;
    }

    public String PasswordTransfer() {
        StringBuilder answer = new StringBuilder();
        int i = 0;
        while (i < sentence.length()) {
            char currentChar = sentence.charAt(i);
            if (Character.isDigit(currentChar)) {

                int start = i;
                String numberStr = sentence.substring(start, i+3);
                if(numberStr!=null&& numberStr.length() > 0) {
                    int number = Integer.parseInt(numberStr);
                    answer.append(getLetter(number));
                    i = i + 3;
                }
            } else {
                answer.append(currentChar);
                i++;
            }
        }
        return answer.toString();
    }

    public char getLetter(int number) {
        if (number >= minRandom && number <= maxRandom) {
            return ' ';
        }
        if (number >= 100 && number < 200)
        {
            // Decrypt for lowercase letters
            for (int j = 0; j < 26; j++) {
                int decryptedValue = (int) (100 + (a * (j + 1) + b) % 26 + Math.pow(c, a) * (j + 1) * b % 73);
                if (decryptedValue == number) {
                    return (char) ('a' + j);
                }
            }
        }
        if (number >= 200 && number < 300)
        {
            // Decrypt for uppercase letters
            for (int j = 0; j < 26; j++) {
                int decryptedValue = (int) (200 + (a * (j + 1) + b) % 26 + Math.pow(c, a) * (j + 1) * b % 73);
                if (decryptedValue == number) {
                    return (char) ('A' + j);
                }
            }
        }
        return '?';
    }
    public void print() {
        System.out.println(PasswordTransfer());
    }
}
