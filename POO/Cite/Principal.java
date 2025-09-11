package POO.Cite;

public class Principal {
    public static void main(String[] args){

        System.out.println("Bem vindo ao Cite!");

        User u = new User(1, "Maria", "premium");

        System.out.println("nome: " + u.get_name());
    }
    
}
