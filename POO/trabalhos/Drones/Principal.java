package trabalhos.Drones;
// Não pode ser alterada
public class Principal {
    public static void main (String args[]) {
		
		final int MAX_TIME = 15;
		int time = 0;		
        Matrix mat1 = new Matrix(10,10);
        System.out.print("\nInício\n");
		mat1.print();
		
		Central cet1 = new Central();

        while( time++ < MAX_TIME ) {
			
			// o que está dentro desse while pode ser alterado pelo professor
			
			// criar grupo de drones
			cet1.createGroup();

			// cria e adiciona drone na matriz e em um grupo
			// cada drone pertence a no máximo um grupo
			Robot rob1 = new Robot();
			mat1.addMobile( rob1 );
			cet1.addDrone( 1 , rob1 );

			// remove um drone
			cet1.removeDrone( rob1 );
			
			// dá uma coordenada destino para todos os drones de um grupo
			cet1.command( 1, 5, 5 );
	
			// dá um comando para todos os drones de um grupo
			cet1.command( 1, Move.STOP );

			// pergunta a cada drone se quer se mover
			mat1.moveAll();

			// mostra as posições do drones
			mat1.print();
        }
        System.out.print("\nFim\n");
    }
}
