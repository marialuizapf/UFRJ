package Estrutura_autoajustavel;

public class Acao implements Patrimonio{
	// identifica a acao
	private static int id = 0;
	private static double valorEmprestimo; 

	public Acao(){
		this.valorEmprestimo = valorEmprestimo;
	}

	public double getValor(){
		return this.valorEmprestimo;
	};

	public void setValor(double valorEmprestimo){
		this.valorEmprestimo = valorEmprestimo;
	};

}
