import java.util.HashSet;
import java.util.Set;

public class GetKey {
    public static boolean hasUniqueElements(int[] array) {
        Set<Integer> set = new HashSet<>();
        for (int num : array) {
            if (!set.add(num)) {
                return false; // 如果添加失败，说明集合中已经存在该元素
            }
        }
        return true; // 遍历完数组后没有发现重复元素
    }

    public static void main(String[] args) {
        int a = 10, b = 20, c;
        int[] number = new int[26];
        for (c = 1; c <= 300; c++) {
            String testSentence = "abcdefghijklmnopqrstuvwxyz";
            Encryption encryption = new Encryption(testSentence, 10, 20, c);
            String answer = encryption.transferToPassword();
            for (int i = 0; i < 26; i++) {
                //String answer=encryption.transferToPassword();
                String subTest = answer.substring(3 * i, 3 * (i + 1));
                number[i] = Integer.parseInt(subTest);
            }
            if (hasUniqueElements(number)) System.out.println(c);
        }
    }
}
//a=10,b=20,c的组合可以为1，2，4，5，6，8，10，12，15，16，17，20，21，22，25，28