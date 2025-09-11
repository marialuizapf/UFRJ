import java.util.Scanner;

// Criar uma fábrica que tem uma lista de carros e uma lista de motos
// fabricados, inicialmente vazias.
// A cada veículo fabricado um custo correspondente é debitado do seu saldo.

// Criar um objeto que faz controle dos chassis. Fornece um número de chassi
// novo cada vez que solicitado.

public class Principal {
	public static void main(String[] args) {
		
		// formatacao para o chassi
		int num = 5;
		String numeroFormatado = String.format("ABC%05d", num);
		System.out.print( numeroFormatado );
		
		double custo_carro = 1000.00;
		double custo_moto = 800.50;
		
		Scanner scan1 = new Scanner(System.in);
        String s1 = "\n\n 1 Fabricar carro \n 2 Fabricar moto";
        String s2 = "\n 3 Contabilidade da fábrica \n 9 Sair \n Escolha uma opção: ";
        String menu = s1 + s2;

		int choice = 0;
        while( choice != 9 ) {
            System.out.printf( menu );
            choice = scan1.nextInt();
            switch( choice ) {
                case 1:
					System.out.println("Fabricar carro");
					Carro c1 = new Carro("Gol", 2025, 4);					
					break;			
                case 2:
					System.out.println("Fabricar moto");
					break;			
                case 3:
					System.out.println("Imprimir dados de todos os veículos da fábrica");
					break;			
				case 9:
					System.out.println("Sair");
					break;			
			}
		}		
	}
}
