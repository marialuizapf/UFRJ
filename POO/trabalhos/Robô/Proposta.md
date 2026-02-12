### Trabalho 1: a classe Robô (Robot)

- Implementar a classe Robot.
- Considere um robô que encontra-se em uma sala vazia. Mas ele n ao sabe
as dimens oes da sala nem em qual posição ele se encontra.
Essa classe deve ter o m ́etodo move, o qual, ao ser chamado, deve retornar
UP, DOWN, LEFT, RIGHT ou STOP. Esse retorno significa o movimento
que o robo deseja fazer para uma posi ̧c ̃ao vizinha a atual na matriz que
representa a sala.
- O robo pode estar nos seguintes estados.
    - No estado STOP: o m ́etodo move retorna STOP.

    - No estado GO CENTER: ele realiza movimentos at ́e alcan ̧car o cen-
tro da sala e para.

    - No estado TOP LEFT: ele se move at ́e o canto esquerda superior e
para.
    - No estado SPIRAL: ele se move at ́e o canto superior esquerdo e depois
percorre todas as posi ̧c ̃oes da sala circularmente, no sentido hor ́ario,
formando uma espiral, at ́e o centro e para.
- A localiza ̧c ̃ao atual do robˆo  ́e representada por um par (l, c), onde l e c
representam a linha e a coluna. O robˆo tem um GPS, para o qual ele
pode perguntar qual a sua localiza ̧c ̃ao atual usando os m ́etodos getLine
e getColumn. Esses m ́etodos recebem como parˆametro um inteiro que
representa o id do robˆo.
- Um objeto dessa classe deve ser criado no estado CENTER.