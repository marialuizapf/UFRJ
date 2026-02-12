package trabalhos.Drones;
// Não pode ser alterada
public abstract class Mobile {
	private static int qtty = 0;

	protected int id;
	protected int line;
	protected int column;
	protected Matrix GPS;
	
	public Mobile(){
		qtty++;
		this.id = qtty;
	}
	
	public void setMatrix( Matrix mat1 ){
		this.GPS = mat1;
	}
	
	public int getId() {
		return this.id;
	}
}

