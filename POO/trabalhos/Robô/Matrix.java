package trabalhos.Robô;
public class Matrix {
	// bordas da sala	
	private static final int BORDER_TOP = 1;
	private static final int BORDER_LEFT = 1;
	private int border_bottom;
	private int border_right;

	// matriz que guarda as posições ocupadas
    private char[][] matrix;
	private static final char EMPTY = ' ';
	private static final char OCCUPIED = 'X';

	// constantes
	private static final int NOT_IN_THE_ROOM = -1;
	private static final int ID = 0;
	private static final int LINE = 1;
	private static final int COLUMN = 2;

	// vetor de móveis
    private int[][] occupied = new int[10][3];
    private int qtdeMobile;
    
	// construtor
	public Matrix( int lines, int columns){
		this.border_bottom = BORDER_TOP + lines -1;
		this.border_right = BORDER_LEFT + columns -1;

		// +2 para deixar as paredes visíveis
		this.matrix = new char[this.border_bottom - BORDER_TOP + 1+2][this.border_right - BORDER_LEFT + 1+2];
		// define como vazias todas as posições da sala
		for( int line = this.BORDER_TOP; line <= this.border_bottom; line++ )
			for( int column = this.BORDER_LEFT; column <= this.border_right; column++ )
				this.matrix[ line ][ column ] = this.EMPTY;		
		// desenha as paredes superior e inferior 
		for( int column = this.BORDER_LEFT -1; column <= this.border_right +1; column++ ){
			this.matrix[this.BORDER_TOP -1][column] = '-';
			this.matrix[this.border_bottom +1][column] = '-';
		}
		// desenha as paredes esquerda e direita
		for( int line = this.BORDER_TOP -1; line <= this.border_bottom +1; line++ ){
			this.matrix[line][this.BORDER_LEFT -1] = '|';
			this.matrix[line][this.border_right +1] = '|';
		}
	}
	
	public void addMobile( Mobile mob1 ){
		int line = 2;
		int column = 3;
		
		occupied[qtdeMobile][ID] = mob1.getId();
		occupied[qtdeMobile][LINE] = line;
		occupied[qtdeMobile++][COLUMN] = column;
		
		this.matrix[line][column] = OCCUPIED;
		
		mob1.setMatrix( this );
	}
	
	private int getPosition( int id ){
		for( int i = 0; i < this.qtdeMobile; i++ ) {
			if(occupied[i][ID] == id)
				return i;
		}
		return NOT_IN_THE_ROOM;
	}
	
    public int getLine( int id ) {
		int pos = this.getPosition( id );
		if( pos == NOT_IN_THE_ROOM )
			return NOT_IN_THE_ROOM;
		return occupied[ pos ][LINE];
    }

    public int getColumn( int id ) {
		int pos = this.getPosition( id );
		if( pos == NOT_IN_THE_ROOM )
			return NOT_IN_THE_ROOM;
		return occupied[ pos ][COLUMN];
    }

    public void move( int id, Move m1 ) {
		int pos = this.getPosition( id );
		if( pos == NOT_IN_THE_ROOM )
			return;
		switch( m1 ) {
			case UP:
				if( occupied[pos][LINE] > BORDER_TOP ) {
					this.matrix[ occupied[pos][LINE] ][ occupied[pos][COLUMN]] = EMPTY; 
					occupied[pos][LINE]--;
					this.matrix[ occupied[pos][LINE] ][ occupied[pos][COLUMN]] = OCCUPIED; 
				}
				break;
			case LEFT:
				if( occupied[pos][COLUMN] > BORDER_LEFT ) {
					this.matrix[ occupied[pos][LINE] ][ occupied[pos][COLUMN]] = EMPTY; 
					occupied[pos][COLUMN]--;
					this.matrix[ occupied[pos][LINE] ][ occupied[pos][COLUMN]] = OCCUPIED;
				}
				break;
			case DOWN:
				if( occupied[pos][LINE] < this.border_bottom ) {
					this.matrix[ occupied[pos][LINE] ][ occupied[pos][COLUMN]] = EMPTY; 
					occupied[pos][LINE]++;
					this.matrix[ occupied[pos][LINE] ][ occupied[pos][COLUMN]] = OCCUPIED;
				} 
				break;
			case RIGHT:
				if( occupied[pos][COLUMN] < this.border_right ) {
					this.matrix[ occupied[pos][LINE] ][ occupied[pos][COLUMN]] = EMPTY; 
					occupied[pos][COLUMN]++;
					this.matrix[ occupied[pos][LINE] ][ occupied[pos][COLUMN]] = OCCUPIED;
				}
				break;
		}
    }
    
    public void print(){
		for( int line = this.BORDER_TOP -1; line <= this.border_bottom +1; line++ ){
			for( int column = this.BORDER_LEFT -1; column <= this.border_right +1; column++ ){
				if( this.matrix[line][column] == EMPTY)
					System.out.print( EMPTY );
				else
					System.out.print( this.matrix[line][column]);
			}
			System.out.println();
		}
		System.out.println();
	}

}
