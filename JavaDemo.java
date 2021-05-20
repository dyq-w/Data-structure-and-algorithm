class LsException extends Exception{
    public LsException(String e){
        super(e);
    }
}
class Food{
    public static void work(int num) throws Exception{
        if(num>10){
            try {
                throw new LsException("������̫�࣬�����ˣ�");
            }finally {
                System.out.println("���λ�� ���������˶���������� 39/Сʱ");
            }
        }else {
            System.out.println("�����������ܰ���");
        }
    }
}
public class JavaDemo {
    public static void main(String args[]) throws Exception {
            Food.work(39);
    }
}
