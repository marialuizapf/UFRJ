## 2. Herança

- Mecanismo onde uma classe (subclasse) herda atributos e métodos de outra (superclasse).

- O que a subclasse herda?

    - Todos os atributos e métodos public e protected.

    - Métodos concretos já prontos para usar.

- A subclasse pode:

    - Usar esses métodos.

    - Sobrescrever para comportamento próprio.

    - Adicionar novas funcionalidades.

- O que não herda?

    - Construtores (mas podem ser chamados via super()).

    - Atributos e métodos private.

```java
public class Pessoa {
    protected String nome;

    public Pessoa(String nome) {
        this.nome = nome;
    }

    public void apresentar() {
        System.out.println("Olá, eu sou " + nome);
    }
}

public class Cachorro extends Animal{
   private int matricula;

    public Aluno(String nome, int matricula) {
        super(nome); // chama o construtor da superclasse (Pessoa)
        this.matricula = matricula;
    }

    @Override
    public void apresentar() {
        super.apresentar(); // reaproveita o comportamento da superclasse
        System.out.println("Minha matrícula é: " + matricula);
    }
}
```

### Métodos da Classe Object 

- Todas as classes em Java herdam implicitamente de Object.

- Métodos mais importantes:
    - toString(): 
        - Retorna uma representação textual do objeto.

        - Usado ao imprimir objetos.

        - Normalmente sobrescrito para deixar mais legível.

    - equals(Object obj)
        - Compara dois objetos.

        - Por padrão, compara endereços (mesmo objeto na memória).

        - Deve ser sobrescrito quando você quer comparar conteúdo lógico.


```java
@Override
public String toString() {
    return "Pessoa: " + this.nome;
}

@Override
public boolean equals(Object obj) {
    if (this == obj) return true;
    if (!(obj instanceof Pessoa)) return false;
    Pessoa p = (Pessoa) obj;
    return this.id == p.id;
}
```
