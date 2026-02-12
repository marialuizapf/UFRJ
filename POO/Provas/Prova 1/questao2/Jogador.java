import java.util.ArrayList;
import java.util.List;

public class Jogador {
    private int numero;
    private static ArrayList<Jogador> jogadores = new ArrayList<>();
    private static int max;

    public Jogador(int num){
        for(Jogador j : jogadores){
            if(j.getNumero() == num){
                j.setNumero(max);
                max++;
            }
        }

        this.numero = num;
        jogadores.add(this);
    }

    public int getNumero() {
        return this.numero;
    }
    public void setNumero(int num) {
        this.numero = num;
    }
}