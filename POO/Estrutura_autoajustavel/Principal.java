package Estrutura_autoajustavel;

public class Principal {
    public static void main (String args[]) {

		Banco ba1 = new Banco();
		
		// comprar acao
		ba1.comprar_acao(120);
		// comprar acao
		ba1.comprar_acao(500);
		// criar cliente
		Cliente c1 = new Cliente(0);
		// criar cliente
		Cliente c2 = new Cliente(80);
		// emprestar para cliente
		ba1.emprestimo(c1, 120);
		// emprestar para cliente
		ba1.emprestimo(c2,500);
	
		// Imprimir os valores dos elementos da lista na ordem.
		// Imprimir valor total do patrimônio financeiro da empresa.
	}		
}
