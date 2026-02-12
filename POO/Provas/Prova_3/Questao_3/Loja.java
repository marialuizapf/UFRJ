package Provas.Prova_3.Questao_3;

public class Loja {
    private int qtde;
    private int meiavenda;

    public void venda(String codigo, int qtde){
        int estoqueAtual = estoque(codigo);
        try{
            if(estoqueAtual < qtde){
                throw new EstoqueInsuficienteException("Estoque insuficiente para o produto");
            }
        }catch(EstoqueInsuficienteException e){
            System.out.println(e.getMessage());
            if(estoqueAtual > 0)
                meiavenda++;
            qtde = estoqueAtual;
        }
        estoque(codigo, estoqueAtual - qtde);
    }
    public int estoque(String codigo){
        return qtde;
    }

    public void estoque( String codigo, int qtde ){
        this.qtde = qtde;
    }

    public int getMeiavenda() {
        return meiavenda;
    }
}
