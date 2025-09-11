public class Veiculo {
	private String chassi;
	private String modelo;
	private int ano;
	private int tam_tanque;	

	protected Veiculo(String modelo, int ano){
		System.out.println("Fabricar veículo");
	}
	
	protected void imprimir_dados(){
		System.out.println("Dados");
		System.out.println(chassi, modelo, ano);
	}
}
