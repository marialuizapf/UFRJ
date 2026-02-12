package Provas.Prova_3.Questao1.Exception;
import java.util.ArrayList;

public class ClasseA2 {
    private static ArrayList<ClasseA2> listaA2 = new ArrayList<>();
    public ClasseA2(){
        int tamA = metodoA();
        int tamB = ClasseB.metodoB();
        if (tamA < (tamB/2)){
            listaA2.add(this);
        } else {
            throw new RuntimeException("Inválido");
        }
    }

    public int metodoA(){
        return listaA2.size(); 
    }
}
