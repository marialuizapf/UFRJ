package Excecoes;
import java.util.Scanner;

public class Principal {
    public static void main(String[] args) {
        Banco banco = new Banco();
        Scanner s = new Scanner(System.in);

        Conta c1 =new Conta(1);
        Conta c2 =new Conta(2);
        
        try{
            banco.depositar(10000, c1);
        }catch(SaldoMaximoException e){
            System.out.println(e.getMessage());
        }

        try{
            banco.retirada(1000, c1);
        }catch(SaldoNegativoException e){
            System.out.println(e.getMessage());
        }
       
    }
}
