class Mesa extends Movel {
    private float comprimento;
    private static float valor_minimo = 100.0f;

    public Mesa(String material, float custo, float comprimento){
        super(material, custo);
        this.comprimento = comprimento;
    }

    protected float setPreco(){
        float preco = this.custo + 100;
        if (preco < this.valor_minimo){
            preco = this.valor_minimo;
        }  
        return preco;
    }
}
