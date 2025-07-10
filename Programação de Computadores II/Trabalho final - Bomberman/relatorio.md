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
- `mapa1.txt`, `mapa2.txt` — Mapas do jogo
- `key.png` — Imagem da chave
- `bomberman` — Executável

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

### Maria
Responsável por:
- Recolhimento de bomba com tecla R
- Movimento do jogador, HUD com bombas, vidas, pontuação
- Pontuação dinâmica com controle de limites (nunca negativa)
- Leitura dos mapas `.txt` e criação dos mapas
- Chaves escondidas nas caixas, exibição ao explodir
- Sistema de menus (novo jogo, salvar, carregar, sair)
- Salvamento e carregamento completo (`save.dat`)
- Avanço para o próximo mapa após 5 chaves
- Inicialização da janela, loop principal (`main.c`)

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
- Relatório final
