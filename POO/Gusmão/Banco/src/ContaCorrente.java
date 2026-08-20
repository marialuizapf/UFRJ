import java.util.ArrayList;

public class ContaCorrente {

    // atributos
    private long cpf;
    private float saldo;
    private String nome;
    private int agencia;
    private int numeroDaConta;
    private int digitoVerificador;
    private int senha;
    private ArrayList<String> extrato;  // veremos depois!!!

    public ContaCorrente(long cpf) {
        this.cpf = cpf;
        this.saldo = 50;
        this.senha = 123;
        this.extrato = new ArrayList<>();
    }

    public void sacar(float valor) {
        if (saldo < valor) {
            throw new RuntimeException("Saldo insuficiente!!!!");  // veremos depois!!
        } else {
            saldo = saldo - valor;
        }
        extrato.add(String.format("Saque de R$%.2f efetuado.", valor));
    }

    public void imprimirExtrato() {
        for (String itemExtrato : extrato) {
            System.out.println(itemExtrato);
        }
    }

    public float getSaldo() {
        return saldo;
    }
}




