public class Principal {

    public static void main (String args[]) {
		
		Terno pa1 = new Terno();		
		Gravata gr1 = new Gravata( pa1 );		
		Meia me1 = new Meia( gr1 );
		
		System.out.println( "Traje: " + me1.getComposicao() );
		System.out.print( "Valor: " + me1.getValor() );
	}
}
