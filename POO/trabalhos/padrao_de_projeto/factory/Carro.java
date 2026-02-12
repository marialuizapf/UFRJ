package trabalhos.padrao_de_projeto.factory;

public class Carro implements Produto{
    @Override
    public void montar(){
        System.out.println("Carro");
    }
}