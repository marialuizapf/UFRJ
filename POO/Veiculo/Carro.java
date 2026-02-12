public class Carro extends Veiculo{
	private int num_portas;
	
	public Carro(String modelo, int ano, int num_portas, String chassi){
		// tem de chamar o construtor da classe mae na primeira linha
		// a nao ser que ele não tenha parâmetros
		super(modelo, ano, chassi);
		this.num_portas = num_portas;
		System.out.println("Fabricar carro");
	}	

	@Override
	public String toString() {
		return super.toString() + "Carro [num_portas=" + num_portas + "]";
	}
}
