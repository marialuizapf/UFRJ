public class Pessoa {
	private int id;
	public Pessoa( int i ) {
		this.id = i;
	}

	public void comprar_Bilhete(int num, Loteria l){
		System.out.println("Pessoa " + this.id + " comprou bilhete " + num);
	}

	

}
