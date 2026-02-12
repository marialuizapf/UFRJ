public class Principal {

    public static void main (String args[]) {
		Object[] vetObj = new Object[100];
		
		// adicionar objetos no vetor vetObj
		
		percorrer( vetObj );		
	}

	private static void percorrer( Object[] vetObj ){
			
		for(Object ob1 : vetObj ){
			if( ob1 instanceof ClasseA ){
				ClasseA clA = (ClasseA) ob1;
				clA.print();
			}
			else if( ob1 instanceof ClasseB ){
				ClasseB clB = (ClasseB) ob1;
				clB.metB();
			}
		}
	}
}
