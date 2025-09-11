abstract class Movel {
    private String material;
    private int custo;
    private int preco;

    public abstract int calcularPreco();

    public Movel(String material, int custo, int preco){
        this.material = material;
        this.custo = custo;
        this.preco = preco;        
    }
}

