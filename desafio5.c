#include "raylib.h"
#include "raymath.h"

#define LARGURA 900
#define ALTURA 600
#define TOTAL_MOEDAS 10
#define TAMANHO_JOGADOR 30.0f
#define RAIO_MOEDA 11.0f
#define VELOCIDADE_JOGADOR 250.0f
#define VELOCIDADE_INIMIGO 120.0f

// Troque para 1 para ativar o desafio extra.
#define ATIVAR_INIMIGO 0

typedef struct {
    Vector2 posicao;
    bool ativo;
} Moeda;

typedef enum { JOGANDO, VITORIA, DERROTA } Estado;

// Fold: reduz o vetor a um unico valor, acumulando as moedas ativas.
static int ContarMoedasRestantes(const Moeda moedas[], int quantidade)
{
    int restantes = 0;
    for (int i = 0; i < quantidade; i++) {
        restantes += moedas[i].ativo ? 1 : 0;
    }
    return restantes;
}

static void ReiniciarJogo(Moeda moedas[], Rectangle *jogador,
                         Vector2 *inimigo, int *pontos, Estado *estado,
                         double *inicio, double *tempoTotal)
{
    // Posicoes espalhadas, sem sobreposicao com o inicio do jogador.
    const Vector2 posicoes[TOTAL_MOEDAS] = {
        {100, 130}, {310, 110}, {560, 140}, {790, 120}, {180, 290},
        {690, 290}, {100, 490}, {330, 460}, {550, 490}, {790, 480}
    };
    for (int i = 0; i < TOTAL_MOEDAS; i++) {
        moedas[i] = (Moeda){posicoes[i], true};
    }
    *jogador = (Rectangle){435, 285, TAMANHO_JOGADOR, TAMANHO_JOGADOR};
    *inimigo = (Vector2){840, 540};
    *pontos = 0;
    *estado = JOGANDO;
    *inicio = GetTime();
    *tempoTotal = 0.0;
}

static void TextoCentralizado(const char *texto, int y, int tamanho, Color cor)
{
    DrawText(texto, (LARGURA - MeasureText(texto, tamanho)) / 2, y, tamanho, cor);
}

int main(void)
{
    InitWindow(LARGURA, ALTURA, "Desafio 5 - Coletor de moedas");
    SetTargetFPS(60);

    Moeda moedas[TOTAL_MOEDAS];
    Rectangle jogador;
    Vector2 inimigo;
    int pontos;
    Estado estado;
    double inicio, tempoTotal;
    ReiniciarJogo(moedas, &jogador, &inimigo, &pontos, &estado, &inicio, &tempoTotal);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_R)) {
            ReiniciarJogo(moedas, &jogador, &inimigo, &pontos, &estado, &inicio, &tempoTotal);
        }

        if (estado == JOGANDO) {
            float dt = GetFrameTime();
            Vector2 direcao = {0};
            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) direcao.x += 1;
            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) direcao.x -= 1;
            if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) direcao.y += 1;
            if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) direcao.y -= 1;
            // Mantem a mesma velocidade ao combinar duas direcoes.
            if (direcao.x != 0 && direcao.y != 0) {
                direcao.x *= 0.70710678f;
                direcao.y *= 0.70710678f;
            }
            jogador.x += direcao.x * VELOCIDADE_JOGADOR * dt;
            jogador.y += direcao.y * VELOCIDADE_JOGADOR * dt;
            if (jogador.x < 0) jogador.x = 0;
            if (jogador.x > LARGURA - jogador.width) jogador.x = LARGURA - jogador.width;
            if (jogador.y < 75) jogador.y = 75;
            if (jogador.y > ALTURA - jogador.height) jogador.y = ALTURA - jogador.height;

            for (int i = 0; i < TOTAL_MOEDAS; i++) {
                if (moedas[i].ativo &&
                    CheckCollisionCircleRec(moedas[i].posicao, RAIO_MOEDA, jogador)) {
                    moedas[i].ativo = false;
                    pontos++;
                }
            }

            tempoTotal = GetTime() - inicio;
            if (ContarMoedasRestantes(moedas, TOTAL_MOEDAS) == 0) {
                estado = VITORIA;
            }

            if (ATIVAR_INIMIGO && estado == JOGANDO) {
                Vector2 alvo = {jogador.x + jogador.width / 2,
                                jogador.y + jogador.height / 2};
                // Move um passo limitado na direcao do centro do jogador.
                Vector2 diferenca = {alvo.x - inimigo.x, alvo.y - inimigo.y};
                float distancia = Vector2Distance(inimigo, alvo);
                if (distancia > 0) {
                    float passo = VELOCIDADE_INIMIGO * dt;
                    if (passo > distancia) passo = distancia;
                    inimigo.x += diferenca.x / distancia * passo;
                    inimigo.y += diferenca.y / distancia * passo;
                }
                if (CheckCollisionCircleRec(inimigo, 16, jogador)) estado = DERROTA;
            }
        }

        BeginDrawing();
        ClearBackground((Color){22, 27, 40, 255});
        DrawRectangle(0, 0, LARGURA, 70, (Color){34, 42, 60, 255});
        DrawText(TextFormat("Pontos: %d / %d", pontos, TOTAL_MOEDAS), 20, 12, 22, GOLD);
        DrawText(TextFormat("Restantes: %d", ContarMoedasRestantes(moedas, TOTAL_MOEDAS)),
                 290, 12, 22, RAYWHITE);
        DrawText(TextFormat("Tempo: %.1f s", tempoTotal), 640, 12, 22, RAYWHITE);
        DrawText("WASD ou setas: mover | R: reiniciar | ESC: sair", 20, 43, 18, LIGHTGRAY);

        for (int i = 0; i < TOTAL_MOEDAS; i++) {
            if (moedas[i].ativo) {
                DrawCircleV(moedas[i].posicao, RAIO_MOEDA, GOLD);
                DrawCircleLines((int)moedas[i].posicao.x, (int)moedas[i].posicao.y,
                                RAIO_MOEDA - 4, ORANGE);
            }
        }
        DrawRectangleRec(jogador, SKYBLUE);
        if (ATIVAR_INIMIGO) DrawCircleV(inimigo, 16, RED);

        if (estado != JOGANDO) {
            DrawRectangle(0, 75, LARGURA, ALTURA - 75, Fade(BLACK, 0.85f));
            TextoCentralizado(estado == VITORIA ? "VITORIA!" : "O INIMIGO TE PEGOU!",
                              215, 40, estado == VITORIA ? GOLD : RED);
            TextoCentralizado(TextFormat("Pontos: %d / %d", pontos, TOTAL_MOEDAS), 285, 26, RAYWHITE);
            TextoCentralizado(TextFormat("Tempo total: %.2f segundos", tempoTotal), 330, 26, RAYWHITE);
            TextoCentralizado("Pressione R para jogar novamente", 395, 22, LIGHTGRAY);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
