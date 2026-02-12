package Provas.Prova_3.Questao_2;
import java.util.ArrayList;
/*
O proprietario quer saber a lista dos 10 itens mais 
caros de cada um dos trˆes grupos. Apresente uma classe
para fazer esse controle, ou seja, dessa classe ser ̃ao criados trˆes objetos, um para cada grupo
que essa loja comercializa. Nome dessa classe M aisCaros.
*/

public class MaisCaros<T extends Produto> {
    private ArrayList<T> itens = new ArrayList<>();

    public void add(T item){
        if (item == null) return;

        int pos = 0;
        while (pos < itens.size() && itens.get(pos).getPreco() >= item.getPreco()) {
            pos++;
        }
        itens.add(pos, item);

        if (itens.size() > 10) {
            itens.remove(10);
        }
    }
}
