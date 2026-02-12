### Metodos e atributos estaticos
  - Static pertence à classe, não ao objeto.
  - Atributo estático é compartilhado por todas as instâncias.
  - Método estático pode ser chamado sem criar objeto o qual ele pertence e dentro dele so pode usar.

```java
public class Exemplo {
  private static int contador = 0;     // atributo estático (da classe)

  public static void somaUm() {       // método estático (da classe)
    contador++; //não precisa de this e todo objeto vai ter esse contador compartilhado
  }
}

public class Exemplo2{
  public void teste(){
    Exemplo.somaUm(); //pode usar o metodo de Exemplo sem precisar de um objeto
  }
}

```

### Arraylist
  - declarar:  ArrayList<String> exemplo = new ArrayList<>();
  - adicionar: exemplo.add(elemento) ou exemplo.add(0,elemento) para colocar no inicio
  - remover: exemplo.remove(indice/elemento) remove do indice, ou a primeira ocorrência de um objeto
  - acessar: exemplo.get(0) primiero elemento
  - mudar: exmeplo.set(0, elemento) mudar o elemento 0 para um novo elemento
  - limpar: exemplo.clear() retira tudo
  - tamanho: exemplo.size()
  - index: para saber p index de um elemento pode fazer exemplo.indexOf(elemento)
    
### Métodos e Classes Genêricas
  - São métodos que aceitam parâmetros de tipo. A declaração do parâmetro de tipo (ex: ``<T>``) deve vir antes do tipo de retorno do método.
  - ``<T extends 'AlgumaClasse'>``: O uso de T extends significa que o parâmetro de tipo T deve ser ou a classe/interface AlgumaClasse ou uma subclasse/subinterface dela e pode usar todos métodos dessa Classe, pois o parâmetro com certeza será daquela classe.
  - Uso Comum: Métodos utilitários que precisam funcionar com coleções ou arrays de qualquer tipo.

```java
abstract class Animal{
  void som()
}
class Gato extends Animal{}
class Cachorro extends Animal{}
class Teste<T extends Animal>{ //quando usa <T extends Algo> ele só pode fazer instacias dos filho de animal
  final ArrayList<T> animais = new ArrayList<>(); // final: não pode ser reatribuído

  Teste(T animal){ 
    animais.add(this)
  }
  void add(T animal) {  
    animais.add(animal);
  }
  void print(){
    for(T a: animais) a.som(); //é possivel usar o metodo som porque é garatido ter esse métodos
  }

}
class main{
  void main(){
    Teste<Gato> g = new Teste<>(new Gato);
    Teste<Cachorro> c = new Cachorro<>(new Cachorro);

    printList(intList);
    printList(StringList);
    printList(DoubleList);
  }
  static void printQualquer(List<?> list) { // wildcard: tipo desconhecido, recebe lista de qualquer objeto como parâmetro
    for (Object o : list) System.out.println(o);
  }
}
```

P2
- emun
- Classes anônimas
- override, overload
- Classes imutáveis, classes empacotadores (wrappers)
- final
- casting, Instanceof
- terminar arquivos
- temrinar padroes de projeto
