//这是一个加密类
/*
    加密算法：
    （1）秘钥有三个正整数a,b,c，a,b,c可以随意更改
    （2）一个英文字母用一个三位整数存储，第一位只有2和1，1表示小写，2表示大写；
    （3）后两位的整数表述它在字母表中的顺序，并且在加密的过程中会再次加上(c^a)*a*b模26的余数，
         假设这个字母在字母表中的序号位x，那么最后的秘文计算方式为：
         if(x为大写）
         int password=200+(a*x+b)%26+c^a*a*b%26；
         if(x为小写）
         int password=100+(a*x+b)%26+c^a*a*b%26；
     （4）如果为标点符号，则正常输出和输出，当然在输入的过程中，因为已经可以区分大小写，所以没有必要引入标点
     （5）所有的空格全部采用随机数生成的方式，生成的随机整数random的范围为[300,999]
     这样就可以对所有的英文进行加密，得到一个只含有数字和标点组成的字符串。
*/
public class Encryption
{
   private String sentence;
   final int min=300,max=999;
   public int a,b,c;
   public Encryption(String sentence,int a,int b,int c)
   {
       this.sentence=sentence;
       this.a=a;
       this.b=b;
       this.c=c;
   }
   public String transferToPassword()
   {

       String password="";
       char letter;
       int passwordNumber;
       for (int i = 0; i < sentence.length(); i++) {
           letter=sentence.charAt(i);
           if((('a'<=letter)&&('z'>=letter))||(('A'<=letter)&&('Z'>=letter))||(letter==' ')) {
               passwordNumber = GetPassword(letter);
               password += String.valueOf(passwordNumber);
           }
           else password+=String.valueOf(letter);
       }
       return password;
   }
    private int GetPassword(char letter)
    {
        if(letter==' ')
        {
            int passwordAnswer = (int) (Math.random() * (max - min + 1)) + min;
            return passwordAnswer;
        }
        if(('a'<=letter)&&('z'>=letter))
        {
            int temp=letter - 'a' + 1;
            return (int) (100+(a*temp+b)%26+Math.pow(c,a)*temp*b%73);
        }
        if(('A'<=letter)&&('Z'>=letter))
        {
            int temp=letter - 'A' + 1;
            return (int) (200+(a*temp+b)%26+Math.pow(c,a)*temp*b%73);
        }
        else return 0;
    }
    public void printPassword()
    {
        System.out.println(transferToPassword());
    }
}
