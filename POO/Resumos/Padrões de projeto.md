## Padrões de projeto
### Observer
- 
### Decorator
- É um padrão estrutural , ele ajuda a organizar classes e objetos em estruturas maiores, mantendo-as flexíveis e eficientes
- Adiciona novas responsabilidades e funcionalidades a um objeto de forma dinâmica e transparente, sem modificar sua estrutura original nem usar herança.
- Utiliza Composição: o objeto a ser estendido (Componente) é envolvido por classes wrapper (Decorators) que adicionam o novo comportamento antes e/ou depois de chamar o objeto original.

### Singleton
- É um padrão de projeto de criação
- Garante que tenha somente uma instância e fornece um ponto de acesso global a essa instância.
- Utiliza um construtor é privado e um método estático (getInstance()) é usado para fornecer a única instância criada sob demanda.

```java
public class Singleton{
    private static Singleton inst;
    private Singleton(){}

    public static Singleton getInst(){
        if(inst == null) inst = new Singleton();
        return inst;
    }
}
```

### Factory 
- É um padrão de projeto de criação
- Define uma interface para criar um objeto, mas permite que as sublcasses decidam qual classe instanciar, em vez de usar ``new`` no código, você chama um metodo estático que retorna a nova instância.
- **Simple Factory:** A Simple Factory se resume em centralizar a lógica de criação em um único método estático, com propósito de Controle de Instanciação e Validação:
    - Uma Classe/Método de Fábrica: Centraliza a lógica de criação.
    - Uma Condição de Decisão: Geralmente uma estrutura ``if/else`` ou ``switch`` baseada em um parâmetro.
    - Retorno do Objeto: O método retorna o objeto criado (geralmente uma interface ou superclasse).
```java
public interface Produto{
    void processar();
}
```
```java
public class ProdutoA implements Produto{
    @Override
    public void processar(){
        System.out.println("Produto A sendo processado.");
    }
}

public class ProdutoB implements Produto{
    @Override
    public void processar(){
        System.out.println("Produto B sendo processado.");
    }
}
```
```java
public class SimplesFabrica{
    public static Produto criarProduto(String tipo){
        if(tipo.equals("A")){
            return new ProdutoA();
        }else if (tipo.equals("B")){
            return new ProdutoB();
        }
        return null;
    }
}
```
- **Formato Canônico Padrão Factory Method:**
```java
public interface Produto{
    void processar();
}
```
```java
public class ProdutoA implements Produto{
    @Override
    public void processar(){
        System.out.println("Produto A sendo processado.");
    }
}

public class ProdutoB implements Produto{
    @Override
    public void processar(){
        System.out.println("Produto B sendo processado.");
    }
}
```
```java
public abstract Criador {
    protected abstract Produto criarTransporte();

    public void planejarEntrega() {
        Transporte t = criarTransporte();
        t.entregar();
    }
}
```
```java
public abstract CriadorConcreto extends Criador{
    protected abstract Produto criarTransporte();
}
```