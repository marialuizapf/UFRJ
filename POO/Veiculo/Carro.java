
public class Carro extends Veiculo{
	private int num_portas;
	
	public Carro(String chassi, String modelo, int ano, int num_portas){
		// tem de chamar o construtor da classe mae na primeira linha
		// a nao ser que ele não tenha parâmetros

		super(chassi, modelo, ano);
		this.num_portas = num_portas;
		System.out.println("Fabricar carro");
	}	

	protected void imprimir_dados(){
		super.imprimir_dados();
		System.out.println("Dados" + num_portas);
	}
}
