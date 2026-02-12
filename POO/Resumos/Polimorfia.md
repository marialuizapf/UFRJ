## 3. Polimorfismo

- Polimorfismo = “muitas formas”
Permite que o mesmo nome (método) tenha comportamentos diferentes dependendo do contexto.

- ### Polimorfismo por Sobrescrita (Override)

    - Acontece em herança.

    - Uma subclasse redefine um método da superclasse com a mesma assinatura (mesmo nome, parâmetros e tipo de retorno compatível).

    - Usado para especializar o comportamento.
```java
public class Animal {
    public void fazerSom() {
        System.out.println("Som genérico");
    }
}

public class Cachorro extends Animal {
    @Override
    public void fazerSom() {
        System.out.println("Au au!");
    }
}
```
- ### Polimorfismo por Sobrecarga (Overload)

- Acontece na mesma classe.

- Vários métodos com mesmo nome, mas parâmetros diferentes (quantidade ou tipos).

- Usado para oferecer várias formas de usar o mesmo método.

```java
public class Calculadora {
    public int somar(int a, int b) {
        return a + b;
    }

    public int somar(int a, int b, int c) {
        return a + b + c;
    }

    public double somar(double a, double b) {
        return a + b;
    }
}
```