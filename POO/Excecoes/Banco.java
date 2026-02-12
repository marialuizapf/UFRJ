package Excecoes;
import java.util.ArrayList;

public class Banco {
    private ArrayList<Conta> contas = new ArrayList();

    //Exceção verificada, ela é uma Exception que obriga o tratamento do erro
    public void depositar(double valor, Conta conta) throws SaldoMaximoException{
        if(conta.getSaldo() + valor > 1000){
            throw new SaldoMaximoException("Saldo máximo excedido, insira um valor menor ou -1 para cancelar");
        }

    }

    //Exceção não verificada, ele é uma RuntimeException que somente avisa o erro
    public void retirada(double valor, Conta conta) throws SaldoNegativoException{
        if(conta.getSaldo() - valor < 0){
            throw new SaldoNegativoException("Saldo insuficiente para retirada");
        }
    }

    public void transferir(Conta origem, Conta destino, double valor){

    }
}
