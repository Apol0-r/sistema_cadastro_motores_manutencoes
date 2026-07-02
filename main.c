#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define CHAR_MAX 100 // Limita os caracteres de um nome ou descrição.
#define MOTORES_MAX 100 // Define um teto para a quantidade de motores a serem cadastrados.
#define MANUTENCOES_MAX 100 // Define um teto para a quantidade manutenções realizadas.

/* ============================================================================ */

typedef struct{
    int id;
    char nome[CHAR_MAX];
    float potencia;

} Motor;

typedef struct {
    int id;
    char nome[CHAR_MAX];
    char categoria[CHAR_MAX];

} Ferramenta;

typedef struct {
    int id;
    char tipo; 
    float custo;
    Ferramenta ferramenta_utilizada;

} Manutencao;

/* ============================================================================ */



//         ARTHUR FAÇA A PARTE DO MOTOR AQUI




/* ============================================================================ */


/* ============================================================================ */


int verificar_id_motor(void);


void registrar_manutencao(void);
void atualizar_matriz_resumo(void);
void salvar_manutencoes_realizadas(void);



/* ============================================================================ */


int main(void) {

    Motor motor[MOTORES_MAX];
    Manutencao manutencao[MANUTENCOES_MAX];
    float matriz_resumo[MOTORES_MAX][3]; 


    int opcao;
    int entrada_valida;


    do {

        printf(" \n = MENU = \n");
        printf("1.      Cadastrar motor\n");
        printf("2.      Registrar manutencao\n");
        printf("3.      Listar motores cadastrados\n");
        printf("4.      Listar manuntencoes registradas\n");
        printf("5.      Exibir relatorios\n");
        printf("6.      Sair do programa\n");
        printf("\n        Opcao: ");

        // Se o usuário digitar uma letra, entrada_valida recebe 0.
        entrada_valida = scanf("%d", &opcao);

        if (entrada_valida != 1) {
            printf("\n[ERRO] Digite apenas numeros de 1 a 6!\n");
            while (getchar() != '\n');
            opcao = -1;
            continue;
        }

        if (opcao < 0 || opcao > 6) {
            printf("\n[ERRO] Digite apenas numeros de 1 a 6!\n");
            continue;
        }

        switch (opcao){
            case 1:
                printf("\n[ERRO] Opcao 1 indisponivel.");
                break;
            
            case 2:
                printf("\n[ERRO] Opcao 2 indisponivel.");
                break;
            
            case 3:
                printf("\n[ERRO] Opcao 3 indisponivel.");
                break;
            
            case 4:
                printf("\n[ERRO] Opcao 4 indisponivel.");
                break;
            case 5:
                printf("\n[ERRO] Opcao 5 indisponivel.");
                break;
            
            case 6:
                printf("\nSaindo...");
        }

    } while(opcao != 6);

    return 0;
}