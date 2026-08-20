public class Principal {

    public static void main(String[] args) {

        ContaCorrente contaDoFulano = new ContaCorrente(5425);

//        System.out.println("saldo = " + contaDoFulano.saldo);
//        System.out.println("cpf = " + contaDoFulano.cpf);
//        System.out.println("senha = " + contaDoFulano.senha);

//        System.out.println("Vou modificar o saldo (quebrando o encapsulamento)");
//        contaDoFulano.saldo -= 7000;  // AGORA IRIA FALHAR!!!!!! NÃO POSSO MAIS QUEBRAR O ENCAPSULAMENTO!!!
        contaDoFulano.sacar(30);
        contaDoFulano.imprimirExtrato();

        System.out.println("saldo = " + contaDoFulano.getSaldo());




    }

}
