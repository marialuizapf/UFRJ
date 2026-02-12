public class Veiculo {
	private String chassi;
	private String modelo;
	private int ano;
	private int tam_tanque;	

	protected Veiculo(String modelo, int ano, String chassi){
		this.modelo = modelo;
		this.ano = ano;
		this.chassi = chassi;
		System.out.println("Fabricar veículo");
	}
	
	public String toString() {
		return "Veiculo [chassi=" + chassi 
		+ ", modelo=" + modelo 
		+ ", ano=" + ano 
		+ ", tam_tanque=" + tam_tanque + "]";
	}
}
