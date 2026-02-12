## Exceptions
- Exceções (exceptions) são objetos que representam problemas ocorridos durante a execução do programa. Elas servem pra sinalizar erros, interromper o fluxo normal e permitir tratamento (com try/catch/finally) ou propagação (throws)

### Checked vs Unchecked
CHECKED (verificadas):
  - O compilador OBRIGA tratar ou declarar.
  - Normalmente: `extends Exception` 
  - Ex.: IOException, SQLException.
 
UNCHECKED (não verificadas):
  - O compilador NÃO obriga tratar.
  - Não precisa colocar throws
  - São: `extends RuntimeException`.
  - Ex.: IllegalArgumentException, NullPointerException.

### try/catch vs throws

#### Ocorre na Main 
try:
   - Você trata o erro NAQUELE ponto (ex.: mostrar mensagem, pedir outro valor, fallback).
   - Colocar na main
   - Colocar nesse bloco o código que pode dar erro
catch:
   - `catch(Exception e) { System.out.println("e.getMessage()") }`
   - Colocar oque deve ser feio ocorrer ocorrer o erro

#### Ocorre no Metodo
 
throws:
   - `public Metodo() throws (Exception/IOExceptin/RuntimeException)` na assinatura do método
   - Você NÃO trata ali; você “avisa” que o método pode lançar e deixa quem chamou decidir.
   - coloca na declaração do método

throw:
   - `if() { throw new Exception/RuntimeException("...") }`
   - Usar com o a codição que chama o erro
   - Fica dentro do método junto com a condição que traz a excessão

finally:
   - Bloco que roda SEMPRE (dando erro ou não).
   - Usado para “limpeza” (fechar recurso, liberar lock etc.).

