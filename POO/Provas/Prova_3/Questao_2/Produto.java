package Provas.Prova_3.Questao_2;

public abstract class Produto {
    private String nome;
    private double preco;

    public Produto(String nome, double preco) {
        this.nome = nome;
        this.preco = preco;
    }

    public Double getPreco(){
        return this.preco;
    }
}
