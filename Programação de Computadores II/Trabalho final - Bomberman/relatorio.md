# Relatório Final – Projeto Bomberman  
**Disciplina:** Programação de Computadores II – 2025/1 
**Turma:** 9071 
**Grupo:** Ana Caroline de Oliveira, Maria Luiza Pinheiro

# Relatório do Trabalho Final — Bomberman

## 🎯 Descrição do Projeto

Este projeto consiste na implementação de uma versão simplificada do jogo **Bomberman**, como atividade final da disciplina **Programação de Computadores II (2025/1)** da UFRJ. O jogo foi desenvolvido em linguagem C utilizando a biblioteca **Raylib**, e permite ao jogador explorar um mapa, plantar bombas para destruir caixas e inimigos, e coletar chaves para avançar de fase.

O objetivo em cada mapa é coletar **5 chaves** escondidas em caixas para progredir para o próximo nível. Bombas possuem tempo de explosão, afetam inimigos, obstáculos e o próprio jogador. A interface gráfica apresenta os elementos do jogo em tempo real com movimentação responsiva e HUD informativo.

---

## Como Compilar e Executar

### Requisitos:
- Compilador `gcc`
- Biblioteca `raylib` instalada

### Compilar:
```bash
make clean && make
```

### Executar:
```bash
./bomberman
```

---

## Controles do Jogo

| Tecla       | Ação                     |
|-------------|--------------------------|
| W, A, S, D   | Movimenta o jogador     |
| Setas       | Movimenta o jogador     |
| B           | Planta bomba             |
| TAB         | Abre menu                |
| N           | Novo jogo (no menu)      |
| C           | Carregar jogo (menu)     |
| S           | Salvar jogo (menu)       |
| Q           | Sair do jogo (menu)      |
| V           | Voltar ao jogo (menu)    |
| ENTER       | Avança para o próximo mapa |

---

## Organização dos Arquivos

- `main.c` — Lógica principal do jogo
- `mapa.c/.h` — Leitura e exibição do mapa
- `jogador.c/.h` — Movimento e estado do jogador
- `inimigo.c/.h` — Lógica de inimigos
- `bomba.c/.h` — Fila de bombas, explosões, recolhimento
- `pontuacao.c/.h` — Gerenciamento de pontuação e vidas
- `menu.c/.h` — Interface e estados do menu
- `save.c/.h` — Salvamento e carregamento do jogo
- `utils.c/.h` — Funções utilitárias
- `mapas` — Mapas do jogo
- `assets` — Imagens usadas do jogo
- `bin/ bomberman` — Executável

---

## Funcionalidades Implementadas

- [x] Movimentação imediata do jogador (sem delay)
- [x] Leitura dos mapas `.txt`
- [x] Mapeamento de caracteres para sprites
- [x] HUD com bombas, pontuação e vidas
- [x] Chaves escondidas em caixas
- [x] Explosão de bombas em cruz 100x100px
- [x] Colisão com obstáculos
- [x] Plantio de bomba em célula livre
- [x] Estoque de 3 bombas por jogador
- [x] Restaurar bomba após explosão
- [x] Dano ao jogador por bomba e inimigo
- [x] 5 inimigos por mapa
- [x] Movimento aleatório e redirecionamento de inimigos
- [x] +10 pontos por caixa destruída
- [x] +20 pontos por inimigo destruído
- [x] −100 pontos por vida perdida
- [x] Pontuação nunca negativa
- [x] Menu completo com N/C/S/Q/V
- [x] Salvar e carregar jogo (`save.dat`)
- [x] Avança para mapa seguinte após 5 chaves
- [x] Implementado com structs e alocação dinâmica
- [x] Sem variáveis globais
- [x] Modularização em `.c/.h`
- [x] Comentários e organização

---

## Divisão de Tarefas

### Maria Luiza
Responsável por:
- Recolhimento de Bomba (tecla R)  
  - Implementado com uma fila ligada (FIFO).  
  - As bombas são armazenadas por ordem de colocação usando ponteiros `head` e `tail`.  
  - A tecla `R` remove apenas a bomba mais antiga (posição `head`).  

- Movimento do Jogador e HUD  
  - Movimento feito com `IsKeyDown()` para alterar `linha/coluna` do jogador.  
  - Verificação de colisão com o mapa antes de mover.  
  - Animações feitas com spritesheets, usando:  
    `frameAtual`, `frameTotal`, `timer`, `frameTime`.  
  - A HUD é desenhada no final de cada frame com `DrawText()`, exibindo:  
    bombas, vidas e pontuação (armazenadas na `struct Jogador`).

- Leitura e Geração de Mapas (`.txt`)  
  - Função `carregarMapa()` recebe como parâmetro, o nome do mapa que é construído com `snprintf` na main, concateando o nome 'mapa%d' com a faseAtual, assim na função `carregarMapa()` abre o mapa `mapa%d.txt` com base na fase atual, por isso é necessário que os mapas sejam nomeados 'mapa1', 'mapa2' e etc. 
  - Aloca dinamicamente matriz `LINHAS x COLUNAS` com `malloc`. Durante a leitura, remove o caractere `'\n'` no final de cada linha (caso exista), e garante a terminação com `'\0'`. Se a linha for menor que `COLUNAS`, os espaços restantes são preenchidos manualmente com `' '`. Isso garante que a matriz fique com tamanho fixo e totalmente preenchida. 
  - Cada caractere (`W`, `D`, `B`, `K`, `C`) representa um tipo de tile.  
  - `desenharMapa()` desenha o tile correto com `DrawTexture()`.

- Chaves Escondidas nas Caixas  
  - Caixas comuns ('B') e caixas com chave ('K') são visualmente iguais.  
  - Após explosão, se o tile era 'K', ele se transforma em 'C' (chave visível).  
  - Lógica de substituição feita diretamente no `mapa->tiles[i][j]`.

- Sistema de Menus (novo jogo, salvar, carregar, sair)  
  - Implementado com máquina de estados (`enum MenuState`).  
  - `atualizarMenu()` detecta teclas e troca de estado (`N`, `C`, `S`, `Q`, `V`).  
  - Cada estado (`MENU_JOGO`, `NOVO_JOGO`, etc.) executa uma ação diferente.  
  - Menus e ações são controlados dentro da `main.c`.

- Salvamento e Carregamento (`save.dat`)  
  - Usado `fwrite` e `fread` em ordem rígida de serialização.  
  - Dados salvos:
    - Fase atual  
    - Dados do jogador  
    - Mapa completo (`tiles`)  
    - Bombas (posição, timer)  
    - Inimigos (posição, direção, tempo)  
  - Carregamento realoca memória (`malloc`) e reinicializa os sprites.  
  - A `struct Jogo` é reconstruída com ponteiros válidos e texturas reassociadas.

- Avanço de Fase (5 chaves)  
  - Verificação via `player->chaves >= 5`.  
  - Testa existência de `mapa%d.txt` usando `fopen()`.  
  - Se existir, você passa de fase:
    - Libera fase atual com `liberarJogo()`.  
    - Carrega nova fase com `carregarMapa()`, novo jogador, inimigos e bombas.  
    - Mantém vidas e pontuação anteriores.  
  - Se não existir, não tem mais mapas e você venceu: ativa `gameVenceu` que mostra a tela de vitória.

- Lógica do Loop Principal (`main.c`)  
  - Controlado por `enum MenuState`.  
  - Executa enquanto `!WindowShouldClose()`:
    - `MENU_JOGO`: atualiza lógica do jogo (jogador, bombas, inimigos, checa chaves).  
    - `NOVO_JOGO`: reinicializa jogo do zero.  
    - `SALVAR_JOGO`: chama `salvarJogo()` e volta ao jogo.  
    - `CARREGAR_JOGO`: carrega estado anterior e restaura ponteiros/sprites.  
    - `Game Over` ou `Vitória`: exibe mensagens e aguarda `ENTER` ou `Q`.   
  - Toda renderização feita entre `BeginDrawing()` e `EndDrawing()`.

- Spritesheets e Animações  
  - Texturas carregadas uma vez na `main`, passadas como parâmetro e armazenadas nas structs (`Jogador`, `Inimigo`, `Bomba`) no momento da criação.  
  - Animações controladas por:  
    `frameAtual` (índice do quadro atual),  
    `frameTotal` (número total de quadros da animação),  
    `frameTime` (tempo por quadro),  
    `timer` (tempo acumulado entre frames).  
    O `timer` é incrementado a cada frame com `dt`, e quando passa de `frameTime`, avança para o próximo `frameAtual`.  
  - Recorte feito com `Rectangle source = {frame * largura, 0, largura, altura}` para pegar apenas o quadro atual da spritesheet. Esse retângulo define a parte da imagem a ser desenhada.  
  - A animação é desenhada com `DrawTextureRec()`, que aplica o recorte (`source`) na posição desejada na tela.

### Ana Caroline
Responsável por:
- Lógica de plantio de bombas:
  - Verificação de posição válida
  - Inserção na fila dinâmica
  - Posicionamento à frente do jogador
- Sistema de invencibilidade do jogador após dano:
  - Temporizador e piscagem
  - **Decisão técnica:** foi implementado um período de invulnerabilidade de 3 segundos após o jogador levar dano para evitar penalizações repetidas em sequência. Durante esse tempo, o jogador pisca para indicar o estado de invencibilidade.
- Colisões:
  - Jogador respeita colisão com obstáculos e bombas
  - Inimigos não ocupam mesma célula (uso de `ListaInimigos` para controle)
  - **Decisão técnica:** foi utilizado um controle de colisão entre inimigos com a função `temInimigoNaPosicao`, evitando que múltiplos inimigos fiquem na mesma posição, o que causaria sobreposição visual e comportamento incorreto.
- Lógica de eliminação de inimigos atingidos (`eliminarInimigosExplodidos`)
- Registro da pontuação no terminal via `TraceLog` com mensagens específicas:
  - `+10 pontos por caixa destruída`
  - `+20 pontos por inimigo explodido`
  - `-100 pontos por vida perdida`
- Sistema de Pontuação
  A pontuação do jogador é atualizada com funções específicas:
  - `pontuarInimigo()`: +20 pontos por inimigo eliminado  
  - `pontuarCaixa()`: +10 pontos por caixa destruída  
  - `penalizarVida()`: -1 vida e -100 pontos
  A pontuação nunca fica negativa; o valor mínimo é 0. A função `ajustarPontuacao()` garante isso quando necessário.
- Relatório final
