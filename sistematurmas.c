//SISTEMA DE DIAGNOSTICO DE TURMAS - EPT

//JOSE ERNESTO

#include <stdio.h>
#include <string.h>

#define MAX 100 // Limite maximo de alunos que é possivel cadastrar

//VARIAVEIS GLOBAIS: Acessiveis por todas as funcoes do programa.

float notas_teoricas[MAX];
float notas_praticas[MAX];
int   aulas[MAX];
int   total_alunos = 0; // Quantos alunos ja foram cadastrados

char motivos_evasao[MAX][200];
int  aulas_perdidas_evasao[MAX];
int  total_evasoes = 0; // Quantos registros de evasao existem

/*
FUNCAO: CONVERTER TEMPO
OBJETIVO: Transformar minutos brutos em Dias, Horas e Minutos.
COMO FUNCIONA: Usa laços while para subtrair blocos de tempo (1440 min = 1 dia / 60 min = 1 hora) sem usar divisao direta.
*/

void converter_tempo(int minutos_total) {
    int dias = 0, horas = 0, minutos = minutos_total;

    while (minutos >= 1440) { // Retira os dias
        dias++;
        minutos -= 1440;
    }
    while (minutos >= 60) {   // Retira as horas
        horas++;
        minutos -= 60;
    }
    printf("%d dia(s), %d hora(s) e %d minuto(s)", dias, horas, minutos);
}

/* 
FUNCAO: MENU ADICIONAR NOTAS (Opcao 1)
OBJETIVO: Inserir novos alunos com validacao total (nao aceita letras nem valores fora da faixa permitida).
*/

void menu_adicionar_notas() {
    int quantidade, i = 0;

    if (total_alunos >= MAX) {
        printf("\nLimite maximo de %d alunos ja atingido!\n", MAX);
        return;
    }

    printf("\n--- ADICIONAR NOTAS ---\n");
    printf("Quantos alunos deseja cadastrar? ");
    
    // Validacao: impede letras e garante que o numero caiba no vetor
    while (scanf("%d", &quantidade) != 1 || (total_alunos + quantidade > MAX) || quantidade <= 0) {
        while (getchar() != '\n'); // Esvazia o buffer do teclado (limpa o "lixo" digitado)
        printf("Erro! O limite restante e de %d aluno(s). Digite um numero valido: ", MAX - total_alunos);
    }

    while (i < quantidade) {
        printf("\n  Aluno %d:\n", total_alunos + 1);
        printf("  (1 aula equivale a 45 minutos)\n");

        /* Pede a nota teorica e trava num loop ate ser um numero valido entre 0 e 10 */
        printf("  Nota teorica (0.0 a 10.0): ");
        while (scanf("%f", &notas_teoricas[total_alunos]) != 1 || notas_teoricas[total_alunos] < 0 || notas_teoricas[total_alunos] > 10) {
            while (getchar() != '\n'); 
            printf("  Invalido! Digite um valor numerico entre 0.0 e 10.0: ");
        }

        /* Faz a mesma validacao estrita para a nota pratica */
        printf("  Nota pratica (0.0 a 10.0): ");
        while (scanf("%f", &notas_praticas[total_alunos]) != 1 || notas_praticas[total_alunos] < 0 || notas_praticas[total_alunos] > 10) {
            while (getchar() != '\n');
            printf("  Invalido! Digite um valor numerico entre 0.0 e 10.0: ");
        }

        /* Pede quantidade de aulas; nao aceita letras ou numeros negativos */
        printf("  Total de aulas assistidas: ");
        while (scanf("%d", &aulas[total_alunos]) != 1 || aulas[total_alunos] < 0) {
            while (getchar() != '\n');
            printf("  Invalido! Digite uma quantidade de aulas nula ou positiva: ");
        }

        total_alunos++;
        i++;
    }
    printf("\nAlunos cadastrados com sucesso!\n");
}
//JOAO FLAVIO

/*
FUNCAO: menu_visualizar_diagnostico (Opcao 2)
OBJETIVO: Varrer os arrays, calcular medias e emitir status da turma e de cada aluno individualmente.
*/

void menu_visualizar_diagnostico() {
    printf("\n--- DIAGNOSTICO DA TURMA ---\n");

    if (total_alunos == 0) {
        printf("Nenhum aluno cadastrado ainda.\n");
        return;
    }

    // Variaveis acumuladoras
    float soma_teorica = 0, soma_pratica = 0, soma_horas = 0;
    
    // Variaveis de rastreio (procurando o melhor e o pior aluno)
    float maior_media = -1, menor_media = 11;  
    int idx_maior = 0, idx_menor = 0, i = 0;

    // Loop de processamento de dados
    while (i < total_alunos) {
        float media = (notas_teoricas[i] + notas_praticas[i]) / 2.0;

        soma_teorica += notas_teoricas[i];
        soma_pratica += notas_praticas[i];
        soma_horas   += (aulas[i] * 45.0) / 60.0; // Converte aulas de 45m para horas

        // Verifica os extremos (Maior e Menor nota)
        if (media > maior_media) { maior_media = media; idx_maior = i; }
        if (media < menor_media) { menor_media = media; idx_menor = i; }
        i++;
    }

    // Calculo das Medias Gerais
    float media_teorica = soma_teorica / total_alunos;
    float media_pratica = soma_pratica / total_alunos;
    float media_geral   = (media_teorica + media_pratica) / 2.0;
    float media_horas   = soma_horas / total_alunos;

    // Exibicao 1: Estatisticas Gerais
    printf("\nTotal de alunos      : %d\n",   total_alunos);
    printf("Media geral da turma : %.2f\n",   media_geral);
    printf("Frequencia media     : %.1f horas\n", media_horas);
    printf("\nAluno destaque       -> Aluno %d (media: %.2f)\n", idx_maior + 1, maior_media);
    printf("Aluno com menor nota -> Aluno %d (media: %.2f)\n",  idx_menor + 1, menor_media);

    // Exibicao 2: Status da Turma
    printf("\n=== STATUS DA TURMA ===\n");

    /* Defasagem de frequencia: se a media de horas ASSISTIDAS for menor
      q 20h, a turma nao atingiu o minimo de presenca esperado.
      Quanto menos horas assistidas, maior o grau de defasagem. */
      
    if (media_horas < 20) {
        printf("[ALERTA] Turma com defasagem! Frequencia media abaixo de 20h (%.1fh assistidas).\n", media_horas);
    }
    if (media_geral >= 7.0) {
        printf("[OK]     Turma Destaque! (Media >= 7.0)\n");
    } else {
        printf("[ATENC.] Turma com Problemas. (Media < 7.0)\n");
    }

    // Exibicao 3: Tabela individual com status por aluno
    printf("\n  #   Teorica  Pratica  Aulas  Media   Status\n");
    printf("  --------------------------------------------------\n");
    i = 0;
    while (i < total_alunos) {
        float media = (notas_teoricas[i] + notas_praticas[i]) / 2.0;

        /* Verifica se o aluno individualmente tem media suficiente ou nao */
        if (media >= 7.0) {
            printf("  %-3d %-8.2f %-8.2f %-6d %-7.2f [OK]\n",
                   i + 1, notas_teoricas[i], notas_praticas[i], aulas[i], media);
        } else {
            printf("  %-3d %-8.2f %-8.2f %-6d %-7.2f [ATENC.]\n",
                   i + 1, notas_teoricas[i], notas_praticas[i], aulas[i], media);
        }
        i++;
    }

    // Exibicao 4: Historico de evasoes registradas
    printf("\n=== EVASOES REGISTRADAS ===\n");
    if (total_evasoes == 0) {
        printf("Nenhuma evasao registrada ate o momento.\n");
    } else {
        printf("Total de evasoes: %d\n\n", total_evasoes);

        /* Percorre todos os registros de evasao salvos na opcao 3
         e exibe o motivo e o tempo perdido de forma legivel */
        int j = 0;
        while (j < total_evasoes) {
            printf("  Evasao %d:\n", j + 1);
            printf("    Motivo         : %s\n", motivos_evasao[j]);
            printf("    Aulas perdidas : %d aula(s)\n", aulas_perdidas_evasao[j]);
            printf("    Tempo perdido  : ");
            converter_tempo(aulas_perdidas_evasao[j] * 45); // 1 aula = 45 minutos
            printf("\n\n");
            j++;
        }
    }
}

//KERLON
void menu_registrar_evasao() {
    printf("\n--- REGISTRAR EVASAO ---\n");

    // Limite do vetor
    if (total_evasoes >= MAX) {
        printf("Limite maximo de evasoes atingido!\n");
        return;
    }

    while (getchar() != '\n');

  
    printf("Motivo da evasao: ");
    fgets(motivos_evasao[total_evasoes], 200, stdin);

    int tamanho = strlen(motivos_evasao[total_evasoes]);
    if (tamanho > 0 && motivos_evasao[total_evasoes][tamanho - 1] == '\n') {
        motivos_evasao[total_evasoes][tamanho - 1] = '\0';
    }


    printf("Quantas aulas o aluno perdeu? ");
    while (scanf("%d", &aulas_perdidas_evasao[total_evasoes]) != 1 
           || aulas_perdidas_evasao[total_evasoes] < 0) {
        
        while (getchar() != '\n');
        printf("Erro! Digite um numero inteiro nao negativo: ");
    }

    int minutos_perdidos = aulas_perdidas_evasao[total_evasoes] * 45;
    double minutos_db = (double)minutos_perdidos;
    int minutos_retorno = (int)minutos_db;

    printf("\n--- Evasao registrada com sucesso! ---\n");
    printf("Motivo: %s\n", motivos_evasao[total_evasoes]);
    printf("Tempo perdido: ");
    converter_tempo(minutos_perdidos);
    printf("\n");

    total_evasoes++;
}

//YURI

/* 
FUNCAO PRINCIPAL: main
OBJETIVO: Controlar o fluxo do usuario. Nao encerra ate digitar 4.
*/

int main() {
    printf("============================================\n");
    printf("  SISTEMA DE DIAGNOSTICO DE TURMAS - EPT   \n");
    printf("  Tema 2 - Laboratorio de Programacao      \n");
    printf("============================================\n");

    int opcao = 0;

    while (opcao != 4) {
        printf("\n--- MENU ---\n");
        printf("1. Adicionar notas\n");
        printf("2. Visualizar diagnostico\n");
        printf("3. Registrar evasao\n");
        printf("4. Encerrar\n");
        printf("Opcao: ");
        
        // Protege contra usuario digitando letra no menu principal
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = 0; // Forca a dar invalido e repetir
        }

        // Garante que so avança se for uma opcao de 1 a 4
        while (opcao < 1 || opcao > 4) {
            printf("Opcao invalida! Digite um numero entre 1 e 4: ");
            if (scanf("%d", &opcao) != 1) {
                while (getchar() != '\n');
            }
        }

        // Direcionamento do menu
        if (opcao == 1) menu_adicionar_notas();
        else if (opcao == 2) menu_visualizar_diagnostico();
        else if (opcao == 3) menu_registrar_evasao();
        else if (opcao == 4) printf("\nEncerrando o simulador. Ate a proxima!\n");
    }

    return 0;
}