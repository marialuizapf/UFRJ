import java.util.Scanner;

public class Principal {
	public static void main(String[] args) {
        Scanner scan1 = new Scanner(System.in);
        String s1 = "\n\n Jogo da velha \n\n 1 Pessoa x Pessoa \n 2 Pessoa x Computador";
        String s2 = "\n 3 Computador x Computador \n 9 Sair \n Escolha uma opção: ";
        String menu = s1 + s2;
        
        while( true ) {
            System.out.printf( menu );
            int choice = scan1.nextInt();
            switch( choice ) {
                case 1:
					System.out.printf( "Digite o nome da pessoa 1" );
					System.out.printf( "Digite o nome da pessoa 2" );
                case 2:
					System.out.printf( "Digite o nome da pessoa" );
                case 3:
					// 2 computadores
				case 9:
					System.out.printf( "Saindo" );
					break;			
			}
			
			// jogo de fato
			// imprime o resultado
		}		
	}
}		

