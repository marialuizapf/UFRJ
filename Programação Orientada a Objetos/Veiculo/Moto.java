public class Moto extends Veiculo{
	private int cilindradas;
	
	public Moto(String chassi, String modelo, int ano, int cilindradas){
		super(chassi, modelo, ano);
		System.out.println("Fabricar moto");
	}	

	protected void imprimir_dados(){
		super.imprimir_dados();
		System.out.println("Dados" + cilindradas);
	}
}
