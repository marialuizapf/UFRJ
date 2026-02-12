package trabalhos.Robô;
public class Principal {
    public static void main (String args[]) {
		
		final int MAX_TIME = 100;
		int time = 0;
		
        Matrix mat1 = new Matrix(10,10);
        Robot rob1 = new Robot();
        
        mat1.addMobile( rob1 );
        
        System.out.print("\nInício\n");
		mat1.print();
        while( time++ < MAX_TIME ) {
            Move mov1 = rob1.move();
            mat1.move( rob1.getId(), mov1 );
            if( time == 50 )
				rob1.setState( State.TOP_LEFT );
			mat1.print();
        }
        System.out.print("\nFim\n");
    }
}
