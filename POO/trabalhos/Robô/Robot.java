package trabalhos.Robô;
public class Robot extends Mobile{
	
	private State state = State.CENTER;
	
	public Robot(){
	}	
	
	public Move move(){
		return Move.RIGHT;
	}
	
	public void setState( State newState ) {
		this.state = newState;
	}
}
