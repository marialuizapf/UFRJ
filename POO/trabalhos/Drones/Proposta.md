### Trabalho 3: Padrões de projeto - Drones

- Uma empresa possui drones (classe `Robot`) divididos em grupos. Cada
  drone pertence a no máximo um grupo.

- Os drones ficam parados enquanto recebem as coordenadas para as quais
  devem ir.

- A central lê as coordenadas e as repassa para os drones.

- A qualquer momento, a central pode dar novas diretrizes para um grupo
  de drones, como, por exemplo: ficar parado, ir para o canto superior
  esquerdo ou ir para um novo destino (coordenadas).

- Implemente a central e os drones. Os arquivos `Central`, `Robot` e `State`
  podem ser alterados e outros arquivos podem ser criados.

- Os arquivos `Matriz`, `Principal`, `Move` e `Mobile` **não** podem ser alterados.

- Utilize os padrões de projeto **Singleton** e **Observer**.
