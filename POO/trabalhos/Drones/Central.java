package trabalhos.Drones;
public class Central {
	public Central(){}
	
	public void createGroup(){}
	
	// adiciona Drone em um grupo
	public void addDrone( int group, Robot ro1 ){}

	// remove Drone
	public void removeDrone( Robot ro1 ) {}
	
	// dá uma coordenada destino para todos os drones de um grupo
	public void command( int group, int line, int columnd ){}
	
	// dá um comando para todos os drones de um grupo
	public void command( int group, Move mov ){}

}

