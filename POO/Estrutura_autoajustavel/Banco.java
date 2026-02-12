package Estrutura_autoajustavel;
import java.util.ArrayList;

public class Banco {
	private ArrayList<Cliente> clientes = new ArrayList<Cliente>();
	private ArrayList<Acao> acoes = new ArrayList<Acao>();
	
	// métodos de ArrayList
	// add: adiciona no final
	// remove: exclui o da posição i
	// set: substitui o da posição i 
	// get: retorna o da posição i

	// recebo 

	public void comprar_acao(double valor){

	}

	public void emprestimo(Cliente cliente, double valor){
		cliente.setValor(valor);
	}

	public void insercao(ArrayList<Acao> acoes, Acao acao){
		int tam = acoes.size();
		for (int i = 0;i < tam + 1;i++){
			acoes.add(i, acao);
			acao = acoes.get(i+1);	
		}
	}

	public Acao busca(ArrayList<Acao> acoes, int posicao){
		Acao acao = acoes.get(posicao);
		int tam = acoes.size();
		for(int i = 0;i < tam + 1;i++){
			acoes.add(i, acao);
			acao = acoes.get(i+1);	
		}

		return acao;
	}

	public void imprimir_aptrimonio(){
		double valorAcoes = 56;
		double valorEprestimos = 56;
		System.out.println(valorAcoes + valorEprestimos);
	}

}
