class Armario extends Movel {
    private int num_portas;
    private static float valor_minimo = 150.0f;

    public Armario(String material, float custo, int num_portas){
        super(material, custo);
        this.num_portas = num_portas;
    }

    protected float setPreco(){
        float preco = this.custo + 100;
        if (preco < this.valor_minimo){
            preco = this.valor_minimo;
        }  
        return preco;
    }
}

