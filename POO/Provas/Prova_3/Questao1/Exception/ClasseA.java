package Provas.Prova_3.Questao1.Exception;

public class ClasseA {
    private static int contadorA = 0;

    public ClasseA(){
        int tamA = metodoA();
        int tamB = ClasseB.metodoB();
        if (tamA < (tamB/2)){
            contadorA++;
        } else {
            throw new RuntimeException("Inválido");
        }
    }

    public int metodoA(){
        return contadorA; 
    }
}
