### Exercício: Exceções

- Faça um programa para cadastrar contas que guardam pontos. Cada
  instância tem um número identificador digitado pelo usuário e um saldo
  inicialmente 0.

- As operações permitidas para uma conta cadastrada são: depósito, retirada
  e transferência para outra conta.

- O saldo mínimo é 0 e o máximo é 1000.

- Lançar uma exceção *unchecked* se uma operação produziria um saldo ne-
  gativo e tratá-la, imprimindo mensagem dizendo que a operação não foi
  realizada por esse motivo.

- Lançar uma exceção *checked* se uma operação produziria um saldo maior
  que o máximo permitido e tratá-la pedindo para o usuário digitar um valor
  menor ou -1 para desistir dessa operação.

- Tratar entrada de dados com exceções usando `IllegalArgumentException`.

  Por exemplo: se o usuário digitar um texto em vez de um número, o pro-
  grama não deve parar; deve imprimir uma mensagem e continuar normalmente.

- Também usar `IllegalArgumentException` para lançar uma exceção em uma
  tentativa de operação com valor de pontos negativo. Tratá-la informando
  a situação e pedindo autorização do usuário para realizar a operação
  multiplicando o valor por -1.

- O programa deve manter o histórico das ocorrências das exceções que
  produziriam saldo negativo.

- Use `throws` em algum dos casos.
