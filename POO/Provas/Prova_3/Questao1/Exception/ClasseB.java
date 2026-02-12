package Provas.Prova_3.Questao1.Exception;

public class ClasseB {
    private static int contadorB = 0;

    public ClasseB(){
        contadorB++;
    }

    public static int metodoB(){
        return contadorB;
    }
}
