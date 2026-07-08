/* 
 * Nome: Arthur Sobral Moreira e Ricardo A.B. Barbosa
 * Disciplina: Programação I - Engenharia Elétrica
 * Trabalho Computacional: Cadastro de Motores
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define CHAR_MAX 100 // Limita os caracteres de um nome ou descrição.
#define MOTORES_MAX 100 // Define um teto para a quantidade de motores a serem cadastrados.
#define MANUTENCOES_MAX 100 // Define um teto para a quantidade manutenções realizadas.

double matriz_resumo[MOTORES_MAX][3]; // A matriz resumo é declarada globalmente. Todos as suas casas estão preenchidas por 0;

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
    printf("\n\nInsira a quantidade de motores para cadastrar: ");
    scanf("%d", ptr_mq);
    printf("\n-------------------------------------------------------\n");

    //Avalia se o usuário digitou a quantidade certa de motores que deseja cadastrar
    while(*ptr_mq <= 0 || *ptr_mq > MOTORES_MAX){
        printf("\nValor Invalido!! Insira novamente quantos motores serao cadastrados: ");
        scanf("%d", ptr_mq);
    }
    
    //Laço em for para realizar a leitura dos dados de cada motor e guardar dentro de vetores
    for(int i = 0; i < *ptr_mq; i++){
        
        //Avalia se o usuário digitou uma ID diferente das outras
        do{
            id_duplicada = 0;
            printf("\nInsira a ID do motor(%d): ", i + 1);
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
            if(motor[i].nome[0] == '\0') printf("\nValor invalido!! O nome nao pode ser vazio!\n");
        }while(motor[i].nome[0] == '\0'); // Verifica o primeiro caractere
        
        printf("\nInsira a potencia do motor(%d): ", i+1);
        scanf("%lf", &motor[i].potencia);
        while(motor[i].potencia <= 0){
            printf("\nValor invalido!! Insira a potencia do motor(%d) novamente: ", i+1);
            scanf("%lf", &motor[i].potencia);
        }
        printf("\n-------------------------------------------------------\n");
    }

}

void listar_motor(int *ptr_mq, Motor motor[]){
    printf("\n%-4s \t %-10s \t %-50s \t %-10s\n", "NUM", "ID", "NOME", "POTENCIA");
    printf("--------------------------------------------------------------------------------------------\n");
    for(int i = 0; i < *ptr_mq; i++){
        printf("%-4d \t %-10d \t %-50s \t %.2lf kW\n", i + 1, motor[i].id, motor[i].nome, motor[i].potencia);
    }
}

void salvar_motores(int *ptr_mq, Motor motor[]){
    //Abre o arquivo que vai salvar os dados dos motores
    FILE *fp = fopen("motores.txt", "wt");
    //Confere se o arquivo pode ser aberto ou não
    if (fp == NULL) {
        printf("\n[ERRO] Nao foi possivel abrir o arquivo para salvar!\n");
        return;
    }
    //grava os dados no arquivo motores.txt
    for(int i = 0; i < *ptr_mq; i++) fprintf(fp, "%d;%s;%.2lf\n", motor[i].id, motor[i].nome, motor[i].potencia);
    //fecha o arquivo
    fclose(fp);
    printf("\nDados salvos com sucesso em 'motores.txt'!\n");
}

void carregar_motores(int *ptr_mq, Motor motor[]){
    int i = 0;
    char c;
    //Abre o arquivo para leitura
    FILE *arquivo = fopen("motores.txt", "rt");
    //Verifica se o arquivo pode ser aberto
    if (arquivo == NULL) {
        *ptr_mq = 0; //Garante que comece com zero motores 
        printf("\n[AVISO] Nao foi possivel abrir o arquivo 'motores.txt' para leitura.\n");
        return;
    }
    // Tenta ler o ID e já consome o primeiro ';'
    while (fscanf(arquivo, "%d;", &motor[i].id) == 1) {
        int j = 0; // reseta j para 0 a cada novo motor
        // Lê o nome caractere por caractere até encontrar o próximo ';'
        // fgetc captura o próximo caractere do arquivo
        while ((c = fgetc(arquivo)) != ';' && c != EOF) {
            motor[i].nome[j] = c;
            j++;
        }
        motor[i].nome[j] = '\0'; // Finaliza a string do nome

        // Lê a potência e o pula para a próxima linha (\n)
        fscanf(arquivo, "%lf\n", &motor[i].potencia);
        i++;
    }
    *ptr_mq = i;
    fclose(arquivo);
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

/*void registrar_manutencao(int *ptr_manutencoes, Motor motor[],Manutencao manutencao[], int quantidade_motores) {
    // FUNÇÃO ATUALMENTE SEM TRATAMENTO PARA A ENTRADA DE DADOS INVÁLIDOS PELO USUÁRIO

    int id_motor;
    char tipo_manutencao;
    int variavel_sentinela;

    printf("\nInsira o ID do motor: ");
    scanf("%d", &id_motor);

    variavel_sentinela = verificar_id_motor(id_motor, motor, quantidade_motores);

   

    if (variavel_sentinela == -1){
        printf("\n[ERRO] ID invalida.\n");
        return;
    }

    manutencao[*ptr_manutencoes].id = motor[variavel_sentinela].id;

    printf("Insira o tipo de manutencao: ");
    scanf(" %c", &manutencao[*ptr_manutencoes].tipo);

    printf("Insira o custo de manutencao: ");
    scanf("%lf", &manutencao[*ptr_manutencoes].custo);

    // CADASTRO DA FERRAMENTA:
    printf("    ID da ferramenta: ");
    scanf("%d", &manutencao[*ptr_manutencoes].ferramenta_utilizada.id);
   
    getchar();
    printf("    Nome da ferramenta: ");
    fgets(manutencao[*ptr_manutencoes].ferramenta_utilizada.nome, CHAR_MAX, stdin);
    manutencao[*ptr_manutencoes].ferramenta_utilizada.nome[strcspn(manutencao[*ptr_manutencoes].ferramenta_utilizada.nome, "\n")] = '\0';
    

    printf("    Categoria da ferramenta: ");
    fgets(manutencao[*ptr_manutencoes].ferramenta_utilizada.categoria, CHAR_MAX, stdin);
    manutencao[*ptr_manutencoes].ferramenta_utilizada.categoria[strcspn(manutencao[*ptr_manutencoes].ferramenta_utilizada.categoria, "\n")] = '\0';

    printf("\n[SUCESSO] Manutencao registrada para o motor ID %d!\n", motor[variavel_sentinela].id);

    (*ptr_manutencoes)++;

    salvar_manutencoes_realizadas(manutencao, *ptr_manutencoes);
}*/

void atualizar_matriz_resumo(int indice, char tipo, double custo){

    if (tipo == 'P') {
        matriz_resumo[indice][0]++; 
    } else if (tipo == 'C') {
        matriz_resumo[indice][1]++;
    }

    matriz_resumo[indice][2] += custo;
    
}

int carregar_manutencoes_realizadas(Manutencao manutencao[]) {
    int quantidade_manutencoes = 0;
    FILE *arquivo = fopen("manutecoes.txt", "r");

    if (arquivo == NULL) {
        printf("\n[AVISO] Nao foi possivel abrir o arquivo 'manutencoes.txt' para leitura.\n");
        return 0;
    }

    while (fscanf(arquivo, "%d; %c;%.2f;%d;%s;%s\n",
        &manutencao[quantidade_manutencoes].id,
        &manutencao[quantidade_manutencoes].tipo,
        &manutencao[quantidade_manutencoes].custo,
        &manutencao[quantidade_manutencoes].ferramenta_utilizada.id,
        &manutencao[quantidade_manutencoes].ferramenta_utilizada.nome,
        &manutencao[quantidade_manutencoes].ferramenta_utilizada.categoria) == 6) {
            quantidade_manutencoes++;
        } 


    fclose(arquivo);
    printf("\n[SUCESSO] %d manutencoes carregadas da memoria!\n", quantidade_manutencoes);

    return quantidade_manutencoes;

}

/*void salvar_manutencoes_realizadas(Manutencao manutencao[], int manutencoes_quantidade){


    FILE *arquivo = fopen("manutencoes.txt", "w");



    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel abrir o arquivo 'manutencoes.txt' para salvar.\n");
        return;
    }

    for (int i = 0; i < manutencoes_quantidade; i++){
        fprintf(arquivo, "%d;%c;%.2f;%d;%s;%s\n",
            manutencao[i].id,
            manutencao[i].tipo,
            manutencao[i].custo,
            manutencao[i].ferramenta_utilizada.id,
            manutencao[i].ferramenta_utilizada.nome,
            manutencao[i].ferramenta_utilizada.categoria
        );
    }

    fclose(arquivo);
    printf("\n[SUCESSO] %d manutencoes salvas com exito!\n", manutencoes_quantidade);

}*/



/* ============================================================================ */


int main(void) {

    Motor motor[MOTORES_MAX];
    Manutencao manutencao[MANUTENCOES_MAX];
    
    int opcao;
    int entrada_valida;
    int motores_quantidade;
    
    // A variável 'manutencao_atual' recebe o total carregado do arquivo
    int manuntecao_atual = carregar_manutencoes_realizadas(manutencao); 
    carregar_motores(&motores_quantidade, motor);
    do {

        printf(" \n = MENU = \n");
        printf("1.      Cadastrar motor\n");
        printf("2.      Registrar manutencao\n");
        printf("3.      Listar motores cadastrados\n");
        printf("4.      Listar manuntencoes registradas\n");
        printf("5.      Exibir relatorios\n");
        printf("6.      Salvar dados\n");
        printf("7.      Sair do programa\n");
        printf("\n        Opcao: ");

        // Se o usuário digitar uma letra, entrada_valida recebe 0.
        entrada_valida = scanf("%d", &opcao);
        // Limpeza de buffer obrigatória após o scanf
        while (getchar() != '\n'); 
        if (entrada_valida != 1) {
            printf("\n[ERRO] Digite apenas numeros de 1 a 7!\n");
            opcao = -1;
            continue;
        }
        if (opcao < 0 || opcao > 7) {
            printf("\n[ERRO] Digite apenas numeros de 1 a 7!\n");
            continue;
        }
        switch (opcao){
            case 1:
                cadastro_motor(&motores_quantidade, motor);
                printf("\nMotores cadastrados com sucesso!!\n");
                break;
            
            case 2:
                //registrar_manutencao(&manuntecao_atual, motor, manutencao, motores_quantidade);
                printf("\n Manutencao cadastrada com sucesso!!\n");
                break;
            
            case 3:
                if(motores_quantidade == 0) printf("\n0 motores cadastrados, impossivel listar!!\n");
                else listar_motor(&motores_quantidade, motor);
                break;
            
            case 4:
                printf("\n[ERRO] Opcao 4 indisponivel.");
                break;

            case 5:
                printf("\n[ERRO] Opcao 5 indisponivel.");
                break;
            
            case 6:
                salvar_motores(&motores_quantidade, motor);
                printf("\nDados salvos com sucesso!!\n");
                break;

            case 7:
                salvar_motores(&motores_quantidade, motor);
                printf("\nSaindo...\n");
        }

    } while(opcao != 7);
    return 0;
}