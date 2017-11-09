# Ideia

## Main server
> Possuirá três queues: uma queue para conexão, utilizada enquanto não tem dois jogadores conectados ao client, e duas queues e jogadas, tal que cada uma será utilizada por um dos clients.
- Inicializa a queue de conexão, criando o descritor
- Aguarda a conexão de dois jogadores
> Ao receber a conexão de um jogador, envia uma mensagem com a chave a utilizar para a fila de mensagens
- Quando o segundo jogador conectar, fecha a queue de conexão
- Começa a partida, fica aguardando mensagens de jogadas para cada client e fica controlando as rodadas por jogador
- A cada jogada, verifica se o jogo deve ser encerrado
- Caso deva ser encerrado, envia a mensagem final a cada um dos clients e fecha as queues de jogadas

## Client
- Inicializa a queue de conexão (velha-lib.h)
- Solicita o nome do jogador
- Envia a mensagem de conexão com o nome do jogador
- Aguarda a mensagem de conexão bem sucedida com a chave da queue de jogadas
- Joga
1. Aguarda mensagem de liberação para jogar
2. Verifica se não é uma mensagem de finalização do jogo
3. Se puder jogar, efetua jogada (lê coordenadas e envia)
4. Retorna para o passo 1
- Ao receber mensagem de finalização de jogo, escreve resultado e encerra o processo

## Lib de renderização
- Centraliza a lógica de renderização do jogo da velha a ser utilizada pelo servidor e pelos dois clients
- Recebe uma matriz e "desenha" a board do jogo