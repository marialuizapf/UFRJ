package Provas.Prova_3.Questao1.Factory;

public class ClasseA {
    private static int contadorA = 0;

    // construtor privado para forçar o uso do método de fábrica
    private ClasseA(){
        contadorA++;
    }

    public static ClasseA criarInstacia(){
        int tamA = metodoA();
        int tamB = ClasseB.metodoB();
        if(tamA < (tamB/2)){
            return new ClasseA();
        }else {
            return null;
        }
    }


    public static int metodoA(){
        return contadorA;
    }
}
