package Excecoes;

public class Conta {
    private int id;
    private double saldo;

    public Conta(int id){
        this.id = id;
    }

    public int getId() {
        return id;
    }
    
    public double getSaldo() {
        return saldo;
    }
}
