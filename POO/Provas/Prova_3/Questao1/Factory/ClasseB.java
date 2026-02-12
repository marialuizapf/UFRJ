package Provas.Prova_3.Questao1.Factory;

public class ClasseB {
    private static int contadorB = 0;

    public ClasseB(){
        contadorB++;
    }

    public static int metodoB(){
        return contadorB;
    }
    
}
