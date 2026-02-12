package Estrutura_autoajustavel;

public class Cliente implements Patrimonio{
	// identifica o cliente
	private static int id = 0;
	private double valorEmprestimo;

	public Cliente(double valorEmprestimo){
		id++;
		this.valorEmprestimo = valorEmprestimo;
	}

	public double getValor(){
		return this.valorEmprestimo;
	};

	public void setValor(double valorEmprestimo){
		this.valorEmprestimo =  this.valorEmprestimo + valorEmprestimo;
	};

	public int getId(){
		return id;
	}

}
