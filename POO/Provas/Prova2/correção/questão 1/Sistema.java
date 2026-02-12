public class Sistema {

	private static Senha[] vetSenhas = new Senha[100];
	private static int qtde = 0;
	
    public static void main (String args[]) {
		
		cadastroDeSenhas();
		
		while( qtde > 0){
			try {
				Senha se1 = proximo();
				System.out.println("Senha " + se1.getSenha() + " com id " + se1.getId());		
				
			} catch( VizinhosException ve1 ) {
				int pos = ve1.getPos();
				vetSenhas[ pos ] = vetSenhas[ --qtde ];
				System.out.println("Posições " + (pos-1) + " e " + pos + " tinham o mesmo id!");		
			}
		}
    }
    
    private static Senha proximo( ) throws VizinhosException {
		if( qtde == 0 )
			return null;
		int posMenor = 0;
		
		for( int i = 1; i < qtde; i++ ){
			if( vetSenhas[ i ].getSenha() < vetSenhas[ posMenor ].getSenha() )
				posMenor = i;
			if( vetSenhas[ i ].getId() == vetSenhas[ i-1 ].getId() )
				throw new VizinhosException( i );
		}
		Senha menorSenha = vetSenhas[ posMenor ]; 
		vetSenhas[ posMenor ] = vetSenhas[ --qtde ];
		return menorSenha;
	}
	
	private static void cadastroDeSenhas(){
		Senha senha = new Senha(1, 400);
		vetSenhas[ qtde++ ] = senha;
		senha = new Senha(3, 200);
		vetSenhas[ qtde++ ] = senha;
		senha = new Senha(3, 300);
		vetSenhas[ qtde++ ] = senha;
		senha = new Senha(1, 100);
		vetSenhas[ qtde++ ] = senha;
	}
}
