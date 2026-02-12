package Provas.Prova2.Questao2;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void processarVetor(List<Object> v){
        for(Object c: v){
            if(c instanceof ClasseA){
                ClasseA a = (ClasseA)c;
                a.print();
            } else if(c instanceof ClasseB){
                ClasseB b = (ClasseB)c;
                b.metB();
            }
        }
    }
    public static void main(String[] args){
    ArrayList<Object> vetObj = new ArrayList<>();

    vetObj.add(new ClasseA());
    vetObj.add(new ClasseB());
    }
}
