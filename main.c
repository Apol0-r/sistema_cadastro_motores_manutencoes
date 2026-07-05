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


int verificar_id_motor(int id_informado, Motor motor[], int quantidade_motores){
    // Essa função percorrer o vetor de motores atrás de uma correspondência para
    // o vetor informado. Ela retorna o índice caso o encontre. No caso de não
    // encontrá-lo, a função retornará -1 (um valor sentinela).

    for (int i = 0; i < quantidade_motores; i++) {
        if (id_informado == motor[i].id) {
            return i;
        }
    }

    return -1;
};

void registrar_manutencao(int *ptr_manutencoes, Motor motor[],Manutencao manutencao[], int quantidade_motores) {
    // FUNÇÃO ATUALMENTE SEM TRATAMENTO PARA A ENTRADA DE DADOS INVÁLIDOS PELO USUÁRIO

    int id_motor;
    char tipo_manutencao;
    int variavel_sentinela;

    printf("\nInsira o ID do motor: ");
    scanf("%d", &id_motor);

    manutencao[*ptr_manutencoes].id = motor[variavel_sentinela].id;

    if (variavel_sentinela == -1){
        printf("\n[ERRO] ID invalida.\n");
        return;
    }

    manutencao[*ptr_manutencoes].id = variavel_sentinela;
    printf("Insira o tipo de manutencao: ");
    scanf(" %c", &manutencao[*ptr_manutencoes].tipo);

    printf("Insira o custo de manutencao: ");
    scanf("%lf", &manutencao[*ptr_manutencoes].custo);

    // Vou insirir a parte da ferramenta logo, logo...

    printf("\n[SUCESSO] Manutencao registrada para o motor ID %d!\n", motor[variavel_sentinela].id);
    (*ptr_manutencoes)++;
};

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

    int manuntecao_atual = 0; 
    // Ao mesmo tempo que me informa a posição no vetor,
    // me informa a quantidade total de manunteções já feitas (manutencao atual += 1;).

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