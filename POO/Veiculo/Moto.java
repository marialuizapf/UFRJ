public class Moto extends Veiculo{
	private int cilindradas;
	
	public Moto(String modelo, int ano, int cilindradas, String chassi){
		super(modelo, ano, chassi);
		this.cilindradas = cilindradas;
		System.out.println("Fabricar moto");
	}	

	@Override
	public String toString() {
		return super.toString() + "Moto [cilindradas=" + cilindradas + "]";
	}
	
}
