public class Principal {
	public static void main(String[] args) {
		
		Loteria l1 = new Loteria(); // números de 1 a 10
		
		int qtde_pessoas = 5;
		
		Pessoa[] c_pessoas = new Pessoa[ qtde_pessoas ];
		
		for( int i = 0; i < qtde_pessoas; i++ ) {
			Pessoa p1 = new Pessoa( 1 );
			c_pessoas[i] = p1;
		}
		
		// pessoa1 compra bilhete 2
		
		// pessoa2 compra bilhete 3 

		// pessoa3 compra bilhete 7
		
		// pessoa4 compra bilhete 2
		
		// loteria1 sorteia e imprime resultado		
		int num = (int)(Math.random() * (10) + 1);
		System.out.print(num);
	}	
}
