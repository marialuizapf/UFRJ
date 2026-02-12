import java.util.ArrayList;
import java.util.List;

public class Fabrica {
    private List<Carro> carros;
    private List<Moto> motos;
    private double saldo;

    public Fabrica() {
        this.carros = new ArrayList<>();
        this.motos = new ArrayList<>();
        this.saldo = 10000.0;
    }

    public void ComprarCarro(Carro carro, double custo) {
        carros.add(carro);
        this.saldo -= custo;
    }
    public void ComprarMoto(Moto moto, double custo) {
        motos.add(moto);
        this.saldo -= custo;
    }

    public double getSaldo() {
        return saldo;
    }

    public void imprimirVeiculos() {
        System.out.println("Salso da fábrica:"+ saldo);
        
        System.out.println("Carros fabricados:");
        for (Carro carro : carros) {
            System.out.println(carro.toString());
        }
        System.out.println("Motos fabricadas:");
        for (Moto moto : motos) {
            System.out.println(moto.toString());
        }
    }
}
