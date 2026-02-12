
import java.util.ArrayList;

public class Senha {
    private static ArrayList<Senha> senhas = new ArrayList<>();
    private int id;
    private int senha;

    public Senha(int id, int senha){
        this.id = id;
        this.senha = senha;
        senhas.add(this);
    }

    public Senha Proximo() throws IDigualException{
        int min = 0;
        for (int i = 0; i < senhas.size()-1 ;i++){
            if(senhas.get(i).getId() == senhas.get(i+1).getId()){
                throw new IDigualException("IDs iguais nao sao permitidos");
            }
            
        }
        for (int i = 1; i < senhas.size();i++){
            if(senhas.get(i).getSenha() < senhas.get(min).getSenha()){
                min = i;
            }
        }
        Senha minSenha = senhas.get(min);
        senhas.remove(min);
        return minSenha;
    }

    public int getId(){
        return this.id;
    }

    public int getSenha(){
        return this.senha;
    }
}
