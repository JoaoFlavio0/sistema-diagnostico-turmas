/*
 * ================================================
 *   SISTEMA DE DIAGNOSTICO DE TURMAS - EPT
 *   Tema 2
 * ================================================
 *   Integrantes:
 *     - [Nome 1]
 *     - [Nome 2]
 *     - [Nome 3]
 * ================================================
 */

#include <stdio.h>
#include <string.h>

/* --- Tamanho maximo de alunos na turma --- */
#define MAX 100

/* ================================================
 *   VARIAVEIS GLOBAIS
 *   Ficam aqui fora para todas as funcoes
 *   conseguirem ler e alterar os dados.
 * ================================================ */

/* Notas e aulas de cada aluno (arrays paralelos) */
float notas_teoricas[MAX];
float notas_praticas[MAX];
int   aulas[MAX];
int   total_alunos = 0;

/* Evasoes registradas */
char motivos_evasao[MAX][200];
int  aulas_perdidas_evasao[MAX];
int  total_evasoes = 0;


/* ================================================
 *   FUNCAO: converter_tempo
 *
 *   Recebe um total de minutos e mostra na tela
 *   quantos dias, horas e minutos isso representa.
 *   Usa dois lacos while para fazer a conversao.
 * ================================================ */
void converter_tempo(int minutos_total) {

    int dias    = 0;
    int horas   = 0;
    int minutos = minutos_total; /* começa com o total e vai subtraindo */

    /* Cada dia tem 1440 minutos (24h x 60min) */
    while (minutos >= 1440) {
        dias++;
        minutos -= 1440;
    }

    /* Cada hora tem 60 minutos */
    while (minutos >= 60) {
        horas++;
        minutos -= 60;
    }

    /* O que sobrou sao os minutos restantes */
    printf("%d dia(s), %d hora(s) e %d minuto(s)", dias, horas, minutos);
}


/* ================================================
 *   FUNCAO: menu_adicionar_notas  (Opcao 1)
 *
 *   Pede ao usuario as notas e aulas de cada aluno.
 *   Valida se as notas estao entre 0.0 e 10.0.
 * ================================================ */
void menu_adicionar_notas() {

    int quantidade;
    int i;

    printf("\n--- ADICIONAR NOTAS ---\n");
    printf("Quantos alunos deseja cadastrar? ");
    scanf("%d", &quantidade);

    i = 0;
    while (i < quantidade) {

        int posicao = total_alunos + 1; /* numero do aluno na turma */
        printf("\n  Aluno %d:\n", posicao);

        /* --- Nota teorica com validacao --- */
        printf("  Nota teorica (0.0 a 10.0): ");
        scanf("%f", &notas_teoricas[total_alunos]);

        while (notas_teoricas[total_alunos] < 0.0 || notas_teoricas[total_alunos] > 10.0) {
            printf("  Nota invalida! Digite um valor entre 0.0 e 10.0: ");
            scanf("%f", &notas_teoricas[total_alunos]);
        }

        /* --- Nota pratica com validacao --- */
        printf("  Nota pratica (0.0 a 10.0): ");
        scanf("%f", &notas_praticas[total_alunos]);

        while (notas_praticas[total_alunos] < 0.0 || notas_praticas[total_alunos] > 10.0) {
            printf("  Nota invalida! Digite um valor entre 0.0 e 10.0: ");
            scanf("%f", &notas_praticas[total_alunos]);
        }

        /* --- Total de aulas assistidas --- */
        printf("  Total de aulas assistidas: ");
        scanf("%d", &aulas[total_alunos]);

        total_alunos++;
        i++;
    }

    printf("\nAlunos cadastrados com sucesso!\n");
}


/* ================================================
 *   FUNCAO: menu_visualizar_diagnostico  (Opcao 2)
 *
 *   Calcula e exibe todas as estatisticas da turma:
 *   medias, aluno destaque, status da turma, etc.
 * ================================================ */
void menu_visualizar_diagnostico() {

    printf("\n--- DIAGNOSTICO DA TURMA ---\n");

    /* Nao tem o que mostrar se nao ha alunos */
    if (total_alunos == 0) {
        printf("Nenhum aluno cadastrado ainda.\n");
        return;
    }

    /* --- Calculos gerais --- */
    float soma_teorica  = 0;
    float soma_pratica  = 0;
    float soma_horas    = 0;

    float maior_media = -1;  /* comeca baixo para qualquer nota ser maior */
    float menor_media = 11;  /* comeca alto para qualquer nota ser menor  */
    int   idx_maior   = 0;
    int   idx_menor   = 0;

    int i = 0;
    while (i < total_alunos) {

        /* Media individual deste aluno */
        float media = (notas_teoricas[i] + notas_praticas[i]) / 2.0;

        soma_teorica += notas_teoricas[i];
        soma_pratica += notas_praticas[i];

        /* Frequencia: aulas x 45 minutos, convertido para horas */
        float horas_frequencia = (aulas[i] * 45.0) / 60.0;
        soma_horas += horas_frequencia;

        /* Verifica se este aluno tem a maior ou menor media */
        if (media > maior_media) {
            maior_media = media;
            idx_maior   = i;
        }
        if (media < menor_media) {
            menor_media = media;
            idx_menor   = i;
        }

        i++;
    }

    /* Medias gerais da turma */
    float media_teorica = soma_teorica / total_alunos;
    float media_pratica = soma_pratica / total_alunos;
    float media_geral   = (media_teorica + media_pratica) / 2.0;
    float media_horas   = soma_horas / total_alunos;

    /* --- Exibicao dos dados --- */
    printf("\nTotal de alunos      : %d\n",   total_alunos);
    printf("Media teorica        : %.2f\n",   media_teorica);
    printf("Media pratica        : %.2f\n",   media_pratica);
    printf("Media geral da turma : %.2f\n",   media_geral);
    printf("Frequencia media     : %.1f horas\n", media_horas);

    printf("\nAluno com MAIOR media -> Aluno %d (%.2f)\n", idx_maior + 1, maior_media);
    printf("Aluno com MENOR media -> Aluno %d (%.2f)\n",  idx_menor + 1, menor_media);

    /* Frequencia do aluno destaque convertida em dias/horas/minutos */
    int minutos_destaque = aulas[idx_maior] * 45;
    printf("Frequencia do aluno destaque: %d aulas = ", aulas[idx_maior]);
    converter_tempo(minutos_destaque);
    printf("\n");

    /* --- Status: defasagem por frequencia --- */
    printf("\n=== STATUS DA TURMA ===\n");

    if (media_horas > 20) {
        printf("[ALERTA] Turma com defasagem!\n");
        printf("         Frequencia media (%.1fh) esta acima de 20h.\n", media_horas);
    }

    /* --- Status: desempenho por media --- */
    if (media_geral >= 7.0) {
        printf("[OK]     Turma Destaque! Media geral: %.2f\n", media_geral);
    } else {
        printf("[ATENC.] Turma com Problemas. Media geral: %.2f\n", media_geral);
    }

    /* --- Lista de todos os alunos --- */
    printf("\n  #   Teorica  Pratica  Aulas  Media\n");
    printf("  --- -------- -------- ------ ------\n");

    i = 0;
    while (i < total_alunos) {
        float media = (notas_teoricas[i] + notas_praticas[i]) / 2.0;
        printf("  %-3d %-8.2f %-8.2f %-6d %.2f\n",
               i + 1,
               notas_teoricas[i],
               notas_praticas[i],
               aulas[i],
               media);
        i++;
    }

    /* --- Lista de evasoes --- */
    if (total_evasoes > 0) {
        printf("\nEvasoes registradas: %d\n", total_evasoes);

        int j = 0;
        while (j < total_evasoes) {
            int minutos_ausencia = aulas_perdidas_evasao[j] * 45;
            printf("  [%d] Motivo: %s\n", j + 1, motivos_evasao[j]);
            printf("       Ausencia: %d aula(s) = ", aulas_perdidas_evasao[j]);
            converter_tempo(minutos_ausencia);
            printf("\n");
            j++;
        }
    }
}


/* ================================================
 *   FUNCAO: menu_registrar_evasao  (Opcao 3)
 *
 *   Registra um aluno que parou de comparecer,
 *   guardando o motivo e calculando o tempo perdido.
 * ================================================ */
void menu_registrar_evasao() {

    printf("\n--- REGISTRAR EVASAO ---\n");

    /* Limpa o buffer do teclado antes de ler texto */
    getchar();

    printf("Motivo da evasao: ");
    fgets(motivos_evasao[total_evasoes], 200, stdin);

    /* Remove a quebra de linha que o fgets captura */
    int tamanho = strlen(motivos_evasao[total_evasoes]);
    if (motivos_evasao[total_evasoes][tamanho - 1] == '\n') {
        motivos_evasao[total_evasoes][tamanho - 1] = '\0';
    }

    printf("Quantas aulas o aluno perdeu? ");
    scanf("%d", &aulas_perdidas_evasao[total_evasoes]);

    /* Mostra o tempo total perdido convertido */
    int minutos_perdidos = aulas_perdidas_evasao[total_evasoes] * 45;
    printf("\nEvasao registrada! Tempo ausente: %d aula(s) = ", aulas_perdidas_evasao[total_evasoes]);
    converter_tempo(minutos_perdidos);
    printf("\n");

    total_evasoes++;
}


/* ================================================
 *   FUNCAO PRINCIPAL  -  main
 *
 *   Exibe o cabecalho e fica em loop no menu
 *   ate o usuario escolher encerrar.
 * ================================================ */
int main() {

    /* --- Cabecalho de boas-vindas --- */
    printf("============================================\n");
    printf("  SISTEMA DE DIAGNOSTICO DE TURMAS - EPT   \n");
    printf("  Tema 2                                   \n");
    printf("============================================\n");
    printf("  Integrantes:                             \n");
    printf("    - Joao Flavio Pedroso do Carmo                             \n");
    printf("    - Kerlon Ramirez Oliveria Rodrigues                             \n");
    printf("    - [Nome 3]                             \n");
    printf("============================================\n");
    printf("  Bem-vindo! Selecione uma opcao no menu.  \n");
    printf("============================================\n");

    int opcao = 0;

    /* Loop principal: continua ate o usuario digitar 4 */
    while (opcao != 4) {

        /* Exibe o menu */
        printf("\n--- MENU ---\n");
        printf("1. Adicionar notas\n");
        printf("2. Visualizar diagnostico\n");
        printf("3. Registrar evasao\n");
        printf("4. Encerrar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        /* Valida se a opcao existe */
        while (opcao < 1 || opcao > 4) {
            printf("Opcao invalida! Digite um numero de 1 a 4: ");
            scanf("%d", &opcao);
        }

        /* Chama a funcao correspondente */
        if (opcao == 1) {
            menu_adicionar_notas();
        }
        else if (opcao == 2) {
            menu_visualizar_diagnostico();
        }
        else if (opcao == 3) {
            menu_registrar_evasao();
        }
        else if (opcao == 4) {
            printf("\nPrograma encerrado. Ate logo!\n");
        }
    }

    return 0;
}