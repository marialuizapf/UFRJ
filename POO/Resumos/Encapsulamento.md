## 1. Encapsulamento

### Encapsulamento
- Ideia principal: **esconder detalhes internos** de uma classe e expor apenas o necessário.
- Usa:
  - **Atributos `private`** (ou `protected`) para proteger dados.
  - **Métodos `public`** (getters/setters ou outros) para controlar o acesso.
- Benefícios:
  - Evita que código externo mexa nos dados de forma incorreta.
  - Facilita manutenção (mudanças internas sem quebrar quem usa a classe).
  - Garante regras, validações e consistência.

### Classe Abstrata

- Não suporta Herança Múltipla

- É uma classe que não pode ser instanciada diretamente.

- Serve como modelo/base para outras classes.

- Pode ter:

    - Métodos com implementação.

    - Métodos abstratos (sem corpo) que devem ser implementados pelas subclasses.

Representa um conceito genérico que não faz sentido existir sozinho.
```java
public abstract class Animal {
    public abstract void fazerSom(); // método abstrato

    public void dormir() { // método concreto
        System.out.println("Dormindo...");
    }
}

public class Cachorro extends Animal{
    @Override
    public  void fazerSom(){
          System.out.println("Au au!");
    }
}
```
### Interface

- É um contrato: define o que uma classe deve fazer, não como.

- **Permite apenas métodos abstratos:** Nenhum método com implementação. Temos algumas exceções que chegaram com o Java 8, mas essa é a ideia principal.

- Não contém atributos: Essa é outra regra que possui uma exceção. Enquanto é comum ouvirmos que interfaces não guardam o estado da classe por não suportarem a instância de atributos, elas ainda podem conter atributos constantes de classe (public static final).

- Não contém construtor.

- Uma classe pode implementar várias interfaces (forma de “herança múltipla” de comportamento).

Representa um conceito genérico que não faz sentido existir sozinho.
```java
public interface Atacante {
    void atacar();
}

public class Guerreiro implements Atacante {
    @Override
    public void atacar() {
        System.out.println("Guerreiro atacando!");
    }
}
```