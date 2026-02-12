package Provas.Prova_3.Questao_2;

public class Main {
    public static void main(String[] args) {
        Chocolate ch1 = new Chocolate("Lindt", 25.0);
        Chocolate ch2 = new Chocolate("Nestle", 15.0);
        Chocolate ch3 = new Chocolate("Garoto", 10.0);
        Chocolate ch4 = new Chocolate("Hershey's", 20.0);
        Chocolate ch5 = new Chocolate("Ferrero Rocher", 30.0);
        Cerveja ce1 = new Cerveja("Heineken", 8.0);
        Camisa ca1 = new Camisa("Polo", 120.0);


        MaisCaros<Cerveja> mcCerveja = new MaisCaros<>();
        MaisCaros<Chocolate> mcChocolate = new MaisCaros<>();
        MaisCaros<Camisa> mcCamisa = new MaisCaros<>();

        mcChocolate.add(ch1);
        mcChocolate.add(ch2);
        mcChocolate.add(ch3);
        mcChocolate.add(ch4);
        mcChocolate.add(ch5);
    }
}
