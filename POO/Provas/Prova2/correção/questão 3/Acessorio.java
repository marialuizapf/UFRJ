public abstract class Acessorio extends Traje {
	
	protected Traje traje;
	
	public Acessorio( double val, String comp, Traje traje ){
		super( val, comp );
		this.traje = traje;
	}

	@Override
	public double getValor(){
		return traje.getValor() + this.valor;
	}
	
	@Override
	public String getComposicao(){
		return traje.getComposicao() + ", " + this.composicao;
	}
}
