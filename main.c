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
    double potencia;

} Motor;

typedef struct {
    int id;
    char nome[CHAR_MAX];
    char categoria[CHAR_MAX];

} Ferramenta;

typedef struct {
    int id;
    char tipo; 
    double custo;
    Ferramenta ferramenta_utilizada;

} Manutencao;

/* ============================================================================ */
void cadastro_motor(int *ptr_mq, Motor motor[]){
    int id_duplicada;
    printf("\nInsira a quantidade de motores para cadastrar: ");
    scanf("%d", ptr_mq);

    //Avalia se o usuário digitou a quantidade certa de motores que deseja cadastrar
    while(*ptr_mq < 0 || *ptr_mq > MOTORES_MAX){
        printf("\nValor Invalido!! Insira novamente quantos motores serao cadastrados: ");
        scanf("%d", ptr_mq);
    }
    
    //Laço em for para realizar a leitura dos dados de cada motor e guardar dentro de vetores
    for(int i = 0; i < *ptr_mq; i++){
        
        //Avalia se o usuário digitou uma ID diferente das outras
        do{
            id_duplicada = 0;
            printf("\nInsira a ID do motor(%d): ", i+1);
            scanf("%d", &motor[i].id);

            //Avalia se o usuário digitou um número positivo
            if(motor[i].id <= 0){
                printf("\nValor invalido!! a ID deve ser um numero inteiro positivo!");
                id_duplicada = 1;
                continue;
            }

            //Laço em for para comparar as ID´s
            for(int c = 0; c < i; c++){
                if(motor[i].id == motor[c].id){
                    printf("\nValor Invalido!! ID igual a outra digitada.");
                    id_duplicada = 1;
                    break;
                }
            }
        }while(id_duplicada == 1);
        
        // Limpa o '\n' deixado pelo scanf anterior
        while(getchar() != '\n'); 

        //Avalia se o usuário digitou o nome do motor correto, ou apenas espaço vazio
        do{
            printf("\nInsira o nome ou descricao do motor(%d): ", i+1);
            fgets(motor[i].nome, CHAR_MAX, stdin);
            motor[i].nome[strcspn(motor[i].nome, "\n")] = '\0';
            if(motor[i].nome[0] == '\0') printf("\n[ERRO] O nome nao pode ser vazio!\n");
        }while(motor[i].nome[0] == '\0'); // Verifica o primeiro caractere
        
        printf("Insira a potencia do motor(%d)", i+1);
        scanf("%lf", &motor[i].potencia);
        while(motor[i].potencia <= 0){
            printf("Valor invalido!! Insira a potencia do motor(%d) novamente: ", i+1);
            scanf("%lf", &motor[i].potencia);
        }
    }

}




/* ============================================================================ */


/* ============================================================================ */



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
    int motores_quantidade;

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
                cadastro_motor(&motores_quantidade, motor);
                printf("\nMotores cadastrados com sucesso!!");
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