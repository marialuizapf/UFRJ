abstract class Movel {
    protected String material;
    protected float preco;
    protected float custo;

    public Movel(String material, float custo){
        this.material = material;
        this.custo = custo;
        this.preco = setPreco();
    }

    abstract protected float setPreco();

    public void setCusto(float novo_custo){
        this.custo = novo_custo;
        this.preco = setPreco();
    }

    public void imprimirDados(){
        System.out.println("Material: " + this.material);
        System.out.println("Custo: " + this.custo);
        System.out.println("Preço: " + this.preco);
    }
}

