package Provas.Prova_3.Questao1.Exception;
import java.util.ArrayList;

public class ClasseB2 {
    private static ArrayList<ClasseB2> listaB2 = new ArrayList<>();

    public ClasseB2(){
        listaB2.add(this);
    }

    public static int metodoB(){
        return listaB2.size();
    }
}
