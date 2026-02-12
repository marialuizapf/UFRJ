public class Main {
    public static void main(String[] args){
        Senha s1 = new Senha(1, 5);

        try{
            Senha p1 = s1.Proximo();
        }catch(IDigualException e){
            System.out.println(e.getMessage());

        }
    }
}
