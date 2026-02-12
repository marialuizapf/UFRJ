public class VizinhosException extends Exception {
	
	private int pos;
	
	public VizinhosException( int pos) {
		this.pos = pos;
	}
	
	public int getPos(){
		return this.pos;
	}		
}
