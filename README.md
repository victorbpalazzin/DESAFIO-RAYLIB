# Desafio 5 — Coletor de moedas

Abra esta pasta (DESAFIO-RAYLIB) no VS Code.

1. Pressione Ctrl+Shift+B para compilar.
2. No menu Terminal > Executar Tarefa, escolha Rodar desafio5.

A configuração usa a instalação existente em C:/raylib.

## Controles

- WASD ou setas: mover.
- R: reiniciar a partida.
- Esc: sair.

Colete as 10 moedas para vencer. Cada moeda vale 1 ponto. O tempo para ao vencer.
Para ativar o inimigo opcional, altere ATIVAR_INIMIGO de 0 para 1 em desafio5.c e compile novamente. Se o inimigo encostar no jogador, a partida termina; R reinicia.

## Requisitos

As moedas ficam em um vetor de structs com campo ativo. A colisão usa CheckCollisionCircleRec. ContarMoedasRestantes realiza um fold, acumulando a quantidade de moedas ativas. A tela de vitória apresenta o tempo total.
