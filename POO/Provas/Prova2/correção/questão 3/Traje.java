public abstract class Traje {
	
	protected double valor;
	protected String composicao;
	
	public Traje ( double val, String comp ){
		this.composicao = comp;
		this.valor = val;
	}
	
	public double getValor(){
		return this.valor;
	}
	
	public String getComposicao(){
		return this.composicao;
	}
}
