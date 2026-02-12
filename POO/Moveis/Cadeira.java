class Cadeira extends Movel {
    private int num_pernas;
    private static float valor_minimo = 80.0f;

    public Cadeira(String material, float custo, int num_pernas){
        super(material, custo);
        this.num_pernas = num_pernas;
    }

    protected float setPreco(){
        float preco = 2*this.custo;
        if (preco < this.valor_minimo){
            preco = this.valor_minimo;
        }  
        return preco;
    }
}
