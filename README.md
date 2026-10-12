# Desafio 5 — Coletor de moedas

Jogo desenvolvido em **C com Raylib** para praticar estruturas, vetores, funções, colisões e atualização de uma cena em tempo real.

O objetivo é controlar o quadrado azul e coletar as **10 moedas** espalhadas pela tela. Cada moeda vale **1 ponto**. Ao coletar todas, o jogo apresenta uma tela de vitória com o tempo total da partida.

O projeto também inclui um inimigo opcional que persegue o jogador.

## Sumário

- [Requisitos do desafio](#requisitos-do-desafio)
- [Arquivos do projeto](#arquivos-do-projeto)
- [Preparação do ambiente](#preparação-do-ambiente)
- [Tutorial: executar pelo VS Code](#tutorial-executar-pelo-vs-code)
- [Tutorial: executar pelo terminal](#tutorial-executar-pelo-terminal)
- [Como jogar](#como-jogar)
- [Tutorial: ativar o inimigo](#tutorial-ativar-o-inimigo)
- [Entendendo o código](#entendendo-o-código)
- [Tutorial: personalizar o jogo](#tutorial-personalizar-o-jogo)
- [Roteiro de teste manual](#roteiro-de-teste-manual)
- [Problemas comuns](#problemas-comuns)
- [Tutorial: enviar alterações ao GitHub](#tutorial-enviar-alterações-ao-github)

## Requisitos do desafio

| Requisito | Implementação |
| --- | --- |
| Dez moedas espalhadas pela tela | Vetor `moedas` com posições iniciais fixas |
| Jogador com movimento nas quatro direções | Teclas WASD ou setas |
| Moedas em um vetor de `struct` com campo `ativo` | Tipo `Moeda`, com `posicao` e `ativo` |
| Moeda desaparece ao encostar e vale um ponto | Desativação da moeda e incremento de `pontos` |
| Colisão com `CheckCollisionCircleRec` | Teste entre a moeda circular e o jogador retangular |
| Contagem das moedas por uma função separada (fold) | Função `ContarMoedasRestantes` |
| Vitória com o tempo total gasto | Estado `VITORIA` e exibição de `tempoTotal` |
| Extra: inimigo que persegue o jogador | Ativado pela constante `ATIVAR_INIMIGO` |

## Arquivos do projeto

```text
DESAFIO-RAYLIB/
├── .vscode/
│   ├── c_cpp_properties.json  # Configuração de análise de C no editor
│   └── tasks.json             # Tarefas de compilação e execução
├── .gitignore                # Evita enviar o executável ao Git
├── desafio5.c                # Código-fonte do jogo
└── README.md                 # Este guia
```

O arquivo `desafio5.exe` é gerado ao compilar. Ele não é versionado: cada pessoa deve compilar o código no próprio ambiente.

O jogo usa formas geométricas desenhadas pelo código. Não é necessário baixar imagens, fontes ou sons.

## Preparação do ambiente

Este tutorial usa **Windows e PowerShell**, com Raylib e GCC instalados na seguinte estrutura:

```text
C:\raylib\w64devkit\bin\gcc.exe
C:\raylib\raylib\src\raylib.h
C:\raylib\raylib\src\raymath.h
C:\raylib\raylib\src\libraylib.a
```

Esses são os caminhos utilizados nas tarefas do projeto. A instalação do Raylib e do compilador precisa existir antes da compilação.

Para conferir o compilador no PowerShell:

```powershell
& "C:\raylib\w64devkit\bin\gcc.exe" --version
```

Se a instalação estiver em outro lugar, ajuste os caminhos nos comandos deste guia e nos arquivos `.vscode/tasks.json` e `.vscode/c_cpp_properties.json`.

## Tutorial: executar pelo VS Code

1. Abra o VS Code.
2. Acesse **Arquivo → Abrir Pasta**.
3. Selecione a pasta **DESAFIO-RAYLIB**, que contém `desafio5.c` e `.vscode`.
4. Abra `desafio5.c` e salve qualquer alteração com **Ctrl+S**.
5. Acesse **Terminal → Executar Tarefa** e escolha **Rodar desafio5**.
6. Essa tarefa compila o código e, se a compilação funcionar, abre o jogo.

Para apenas compilar, pressione **Ctrl+Shift+B**. Essa ação gera o executável, mas não abre a janela do jogo.

> Abra a pasta `DESAFIO-RAYLIB` diretamente. Abrir somente o arquivo C ou a pasta que contém o repositório pode impedir que as tarefas apareçam.

## Tutorial: executar pelo terminal

### 1. Entrar na pasta

No terminal PowerShell do VS Code, execute:

```powershell
cd "C:\Users\fabia\Documents\Desafio Raylib\DESAFIO-RAYLIB"
```

Esse é o caminho do ambiente em que o projeto foi preparado. Em outro computador, substitua pelo local onde você salvou o repositório.

### 2. Compilar

Copie o comando completo:

```powershell
& "C:\raylib\w64devkit\bin\gcc.exe" desafio5.c -o desafio5.exe -I C:/raylib/raylib/src -L C:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm -std=c99 -Wall -Wextra
```

Se funcionar, o compilador normalmente termina sem imprimir mensagens e cria `desafio5.exe`.

| Parte do comando | Para que serve |
| --- | --- |
| `&` | Executa o programa cujo caminho está entre aspas no PowerShell |
| `desafio5.c` | Arquivo de entrada com o código-fonte |
| `-o desafio5.exe` | Nome do executável gerado |
| `-I ...` | Pasta dos cabeçalhos, como `raylib.h` |
| `-L ...` | Pasta em que o compilador procura as bibliotecas |
| `-lraylib` | Liga o programa à Raylib |
| `-lopengl32 -lgdi32 -lwinmm` | Bibliotecas do Windows usadas nesta compilação |
| `-std=c99` | Seleciona o padrão C99 |
| `-Wall -Wextra` | Habilita avisos úteis sobre o código |

### 3. Executar

Depois de compilar sem erros:

```powershell
.\desafio5.exe
```

O prefixo `.\` indica que o programa está na pasta atual.

**Ao modificar o código:** salve, feche a janela do jogo, compile novamente e execute. Rodar o `.exe` sem recompilar usa a versão anterior.

## Como jogar

| Tecla | Ação |
| --- | --- |
| `W` ou seta para cima | Subir |
| `S` ou seta para baixo | Descer |
| `A` ou seta para a esquerda | Ir para a esquerda |
| `D` ou seta para a direita | Ir para a direita |
| `R` | Reiniciar, inclusive durante uma partida |
| `Esc` | Fechar o jogo |

- O quadrado azul representa o jogador.
- Os círculos dourados são as moedas.
- A barra superior mostra pontos, moedas restantes e tempo decorrido.
- Encoste em cada moeda para coletá-la. A mesma moeda não pode pontuar duas vezes.
- Ao chegar a 10 pontos, aparece a vitória e o cronômetro para.
- É possível combinar duas direções para mover na diagonal.

## Tutorial: ativar o inimigo

Por padrão, o extra está desativado. Para jogar com ele:

1. Abra `desafio5.c`.
2. Localize esta linha perto do início:

   ```c
   #define ATIVAR_INIMIGO 0
   ```

3. Troque `0` por `1`:

   ```c
   #define ATIVAR_INIMIGO 1
   ```

4. Salve, compile novamente e execute.

Um círculo vermelho perseguirá o centro do jogador. Se encostar nele antes de você coletar todas as moedas, a partida termina em derrota. Pressione `R` para tentar novamente.

Para voltar ao modo básico, restaure o valor `0` e recompile.

## Entendendo o código

### Estrutura de uma moeda

```c
typedef struct {
    Vector2 posicao;
    bool ativo;
} Moeda;
```

`Vector2` guarda as coordenadas `x` e `y`. O campo `ativo` informa se a moeda ainda está disponível. Quando ela é coletada, o campo passa de `true` para `false`.

O vetor `Moeda moedas[TOTAL_MOEDAS]` reúne as dez moedas. Elas continuam no vetor após a coleta, mas deixam de ser desenhadas e consideradas nos testes de coleta.

### Contagem com fold

```c
static int ContarMoedasRestantes(const Moeda moedas[], int quantidade)
{
    int restantes = 0;
    for (int i = 0; i < quantidade; i++) {
        restantes += moedas[i].ativo ? 1 : 0;
    }
    return restantes;
}
```

Um **fold**, ou redução, percorre uma coleção e acumula um único resultado. Aqui, cada moeda ativa acrescenta `1` à soma; cada moeda inativa acrescenta `0`. O resultado é a quantidade restante.

O trecho `condicao ? 1 : 0` é o operador ternário: escolhe o primeiro valor se a condição for verdadeira e o segundo se for falsa.

### Movimento e tempo entre quadros

O jogo lê o teclado a cada quadro. A mudança de posição depende da direção, da velocidade e de `GetFrameTime()`, que informa o tempo decorrido desde o quadro anterior:

```c
jogador.x += direcao.x * VELOCIDADE_JOGADOR * dt;
jogador.y += direcao.y * VELOCIDADE_JOGADOR * dt;
```

Multiplicar por `dt` faz a velocidade ser expressa em pixels por segundo. Quando há movimento diagonal, as componentes são multiplicadas por aproximadamente `0.7071` para evitar que a diagonal seja mais rápida.

O código também limita a posição do jogador à área de jogo, abaixo da barra de informações.

### Colisão e pontuação

```c
if (moedas[i].ativo &&
    CheckCollisionCircleRec(moedas[i].posicao, RAIO_MOEDA, jogador)) {
    moedas[i].ativo = false;
    pontos++;
}
```

`CheckCollisionCircleRec` verifica a colisão entre um círculo e um retângulo. A condição `ativo` evita contar novamente uma moeda coletada.

### Estados e cronômetro

O tipo `Estado` define três situações:

| Estado | Comportamento |
| --- | --- |
| `JOGANDO` | Atualiza movimento, coleta, inimigo e tempo |
| `VITORIA` | Exibe a conclusão com a pontuação e o tempo final |
| `DERROTA` | Exibe o fim da partida após a colisão com o inimigo |

O tempo da partida é calculado por `GetTime() - inicio`. Quando o estado deixa de ser `JOGANDO`, esse valor para de ser atualizado. Reiniciar redefine o instante inicial.

### Funções principais

| Função | Responsabilidade |
| --- | --- |
| `ContarMoedasRestantes` | Somar as moedas ainda ativas |
| `ReiniciarJogo` | Restaurar moedas, posições, pontos, estado e cronômetro |
| `TextoCentralizado` | Desenhar texto centralizado horizontalmente |
| `main` | Criar a janela e executar o ciclo de atualização e desenho |

Em `ReiniciarJogo`, os parâmetros com `*` são ponteiros. Eles permitem alterar as variáveis originais da partida; na chamada, `&` fornece o endereço dessas variáveis.

## Tutorial: personalizar o jogo

### Alterar as velocidades

Edite as constantes no início do arquivo:

```c
#define VELOCIDADE_JOGADOR 250.0f
#define VELOCIDADE_INIMIGO 120.0f
```

Valores maiores aumentam a velocidade. Para tornar a perseguição mais difícil, experimente aumentar gradualmente a velocidade do inimigo.

### Alterar as posições das moedas

Dentro de `ReiniciarJogo`, edite o vetor `posicoes`. Cada par representa `{x, y}`, em pixels. A origem fica no canto superior esquerdo; `x` aumenta para a direita e `y` aumenta para baixo.

Mantenha os círculos inteiros dentro da tela e abaixo da barra superior. Evite colocar moedas sobrepostas ou em cima do ponto inicial do jogador.

### Alterar a quantidade de moedas

Para experimentar além do enunciado, altere `TOTAL_MOEDAS` **e ajuste a lista de posições para ter exatamente a mesma quantidade de elementos**. A entrega original usa dez moedas.

Se aumentar apenas a constante, os elementos sem posição explícita serão inicializados com coordenadas zero, fora da área alcançável pelo jogador.

### Alterar a janela e as cores

`LARGURA` e `ALTURA` definem o tamanho da janela. Algumas posições da interface, das moedas e do inimigo são fixas; ao mudar a resolução, revise essas posições também.

Para mudar as cores, localize chamadas como `DrawRectangleRec(jogador, SKYBLUE)` e `DrawCircleV(..., GOLD)`, substituindo a cor desejada.

Depois de qualquer personalização, salve e recompile.

## Roteiro de teste manual

Use esta lista para conferir o comportamento ao executar:

- [ ] A partida começa com 0 pontos e 10 moedas restantes.
- [ ] WASD e setas movimentam o jogador.
- [ ] O jogador não sai da área de jogo.
- [ ] Cada moeda desaparece ao ser coletada e acrescenta somente 1 ponto.
- [ ] Pontos mais moedas restantes somam 10 durante a partida.
- [ ] A última moeda abre a tela de vitória com o tempo final congelado.
- [ ] `R` restaura as moedas, a pontuação e o cronômetro.
- [ ] Com o extra ativado, o círculo vermelho persegue o jogador.
- [ ] Encostar no inimigo antes da vitória causa derrota.
- [ ] `Esc` fecha a janela.

## Problemas comuns

| Problema | O que conferir |
| --- | --- |
| `gcc` não é reconhecido | Use o caminho completo do compilador mostrado no tutorial |
| O caminho do `gcc.exe` não existe | Confira onde Raylib e w64devkit foram instalados e ajuste a configuração |
| `raylib.h` ou `raymath.h`: arquivo não encontrado | Verifique se `-I` aponta para a pasta que contém esses cabeçalhos |
| `cannot find -lraylib` | Confira o caminho de `-L` e a presença de `libraylib.a` |
| `undefined reference` para funções da Raylib | Use o comando completo, com as bibliotecas depois do arquivo C |
| `Permission denied` ao gerar `desafio5.exe` | Feche o jogo antes de recompilar; confira também a permissão de escrita da pasta |
| `.\desafio5.exe` não é encontrado | Confira a pasta atual e se a compilação terminou com sucesso |
| As alterações não aparecem no jogo | Salve o arquivo e recompile; verifique mensagens de erro antes de executar |
| A tarefa não aparece no VS Code | Abra diretamente a pasta que contém `.vscode/tasks.json` |
| O editor sublinha os includes, mas o jogo compila | Confira os caminhos de `.vscode/c_cpp_properties.json` usados pela extensão C/C++ |
| As teclas não movimentam o jogador | Clique na janela do jogo para dar foco; se a partida acabou, pressione `R` |

Se ainda houver erro, copie a mensagem completa do terminal. Ela ajuda a distinguir um problema no código de um problema no caminho ou na compilação.

## Tutorial: enviar alterações ao GitHub

Execute os comandos abaixo no PowerShell, dentro da pasta do repositório. Eles pressupõem que o remoto `origin` e a autenticação do GitHub já estão configurados.

Primeiro confira os arquivos modificados:

```powershell
git status
git diff
```

Para enviar somente uma atualização deste guia:

```powershell
git add README.md
git commit -m "Amplia README com tutoriais e explicacoes"
git push origin main
```

Para uma alteração no jogo, selecione os arquivos correspondentes, por exemplo:

```powershell
git add desafio5.c README.md
git commit -m "Atualiza jogo e documentacao"
git push origin main
```

`git add` seleciona as alterações, `git commit` registra uma versão local e `git push` envia os commits para o GitHub. Execute cada etapa após a anterior terminar sem erros.

Se aparecer `nothing to commit`, não há alterações selecionadas para um novo commit. Se o envio for rejeitado, leia a mensagem antes de continuar e não use envio forçado para tentar contornar o problema.
