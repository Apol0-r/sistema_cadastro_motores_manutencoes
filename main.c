// Nome: Arthur Sobral Moreira e Ricardo Augusto Bona Barbosa
// Disciplina: Programação I - Engenharia Elétrica
// Trabalho Computacional: Cadastro de Motores

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define CHAR_MAX 100 // Limita os caracteres de um nome ou descrição.
#define MOTORES_MAX 100 // Define um teto para a quantidade de motores a serem cadastrados.
#define MANUTENCOES_MAX 100 // Define um teto para a quantidade manutenções realizadas.

// Definições de cores ANSI para estilização do terminal
#define RESET   "\033[0m"
#define VERMELHO "\033[1;31m"
#define VERDE    "\033[1;32m"
#define AMARELO  "\033[1;33m"
#define CIANO    "\033[1;36m"
#define BRANCO   "\033[1;37m"

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
    printf("\n" CIANO "=======================================================" RESET);
    printf("\n  Insira a quantidade de motores para cadastrar: ");
    scanf("%d", ptr_mq);
    printf("\n" CIANO "-------------------------------------------------------" RESET "\n");

    //Avalia se o usuário digitou a quantidade certa de motores que deseja cadastrar
    while(*ptr_mq <= 0 || *ptr_mq > MOTORES_MAX){
        printf("\n" VERMELHO "[ERRO] Valor Invalido!!" RESET " Insira novamente quantos motores serao cadastrados: ");
        scanf("%d", ptr_mq);
    }
    
    //Laço em for para realizar a leitura dos dados de cada motor e guardar dentro de vetores
    for(int i = 0; i < *ptr_mq; i++){
        
        //Avalia se o usuário digitou uma ID diferente das outras
        do{
            id_duplicada = 0;
            printf("\n  Insira a ID do motor (%d): ", i + 1);
            scanf("%d", &motor[i].id);

            //Avalia se o usuário digitou um número positivo
            if(motor[i].id <= 0){
                printf("\n" VERMELHO "[ERRO] Valor invalido!!" RESET " A ID deve ser um numero inteiro positivo!\n");
                id_duplicada = 1;
                continue;
            }

            //Laço em for para comparar as ID´s
            for(int c = 0; c < i; c++){
                if(motor[i].id == motor[c].id){
                    printf("\n" VERMELHO "[ERRO] Valor Invalido!!" RESET " ID igual a outra digitada.\n");
                    id_duplicada = 1;
                    break;
                }
            }
        }while(id_duplicada == 1);
        
        // Limpa o '\n' deixado pelo scanf anterior
        while(getchar() != '\n'); 

        //Avalia se o usuário digitou o nome do motor correto, ou apenas espaço vazio
        do{
            printf("  Insira o nome ou descricao do motor (%d): ", i+1);
            fgets(motor[i].nome, CHAR_MAX, stdin);
            motor[i].nome[strcspn(motor[i].nome, "\n")] = '\0';
            if(motor[i].nome[0] == '\0') printf("\n" VERMELHO "[ERRO] Valor invalido!! O nome nao pode ser vazio!" RESET "\n\n");
        }while(motor[i].nome[0] == '\0'); // Verifica o primeiro caractere
        
        printf("  Insira a potencia do motor (%d) em kW: ", i+1);
        scanf("%lf", &motor[i].potencia);
        while(motor[i].potencia <= 0){
            printf("\n" VERMELHO "[ERRO] Valor invalido!!" RESET " Insira a potencia do motor (%d) novamente: ", i+1);
            scanf("%lf", &motor[i].potencia);
        }
        printf("\n" CIANO "-------------------------------------------------------" RESET "\n");
    }

}

void listar_motor(int *ptr_mq, Motor motor[], int variavel_sentinela){

    if (variavel_sentinela == 0) {
        printf("\n" AMARELO "[ALERTA] Exibindo Motores Anteriores" RESET "\n");
    } else {
        printf("\n" AMARELO "[ALERTA] Exibindo Motores Novos" RESET "\n");
    }

    if (*ptr_mq == 0) {
        printf("\n" AMARELO "[AVISO] Nenhum motor cadastrado para listar." RESET "\n");
        return;
    }
    

    printf("\n" CIANO "%-6s   %-10s   %-40s   %-15s" RESET "\n", "NUM", "ID", "NOME", "POTENCIA");
    printf(CIANO "----------------------------------------------------------------------------" RESET "\n");
    for(int i = 0; i < *ptr_mq; i++){
        printf("%-6d   %-10d   %-40s   %.2lf kW\n", i + 1, motor[i].id, motor[i].nome, motor[i].potencia);
    }
    printf(CIANO "----------------------------------------------------------------------------" RESET "\n");
}

void salvar_motores(int *ptr_mq, Motor motor[], int variavel_sentinela){
    //Abre o arquivo que vai salvar os dados dos motores
    FILE *fp = fopen("motores.txt", "wt");
    //Confere se o arquivo pode ser aberto ou não
    if (fp == NULL) {
        printf("\n" VERMELHO "[ERRO] Nao foi possivel abrir o arquivo 'motores.txt' para salvar!" RESET "\n");
        return;
    }
    //grava os dados no arquivo motores.txt
    for(int i = 0; i < *ptr_mq; i++) fprintf(fp, "%d;%s;%.2lf\n", motor[i].id, motor[i].nome, motor[i].potencia);
    //fecha o arquivo
    fclose(fp);

    if (variavel_sentinela == 1) {
        printf("\n" VERDE "[SUCESSO] Dados salvos com sucesso em 'motores.txt'!" RESET "\n"); 
    }
}

void carregar_motores(int *ptr_mq, Motor motor[]){
    int i = 0;
    char c;
    //Abre o arquivo para leitura
    FILE *arquivo = fopen("motores.txt", "rt");
    //Verifica se o arquivo pode ser aberto
    if (arquivo == NULL) {
        *ptr_mq = 0; //Garante que comece com zero motores 
        printf("\n" AMARELO "[AVISO] Nao foi possivel abrir o arquivo 'motores.txt' para leitura." RESET "\n");
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

    printf("\n" VERDE "[SUCESSO] %d motores anteriores carregados da memoria!" RESET "\n", *ptr_mq);
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

int verificar_tipo_manutencao(char tipo_informdo) {
    // Função que verifica a entrada do usuário para o tipo de manutenção, retornando
    // 1 para um valor válido e -1 para um valor inválido.

    if (tipo_informdo == 'C' || tipo_informdo == 'c' || tipo_informdo == 'P' || tipo_informdo == 'p') {
        return 1;
    }

    return -1;

}

void registrar_manutencao(int *ptr_manutencoes, Motor motor[], Manutencao manutencao[], int quantidade_motores) {
    int id_motor;
    int variavel_sentinela;
    double custo_ferramenta;
    int id_ferramenta;

    // Loop de validação para o ID do Motor
    do {
        printf("\n  Insira o ID do motor: ");
        scanf("%d", &id_motor);

        variavel_sentinela = verificar_id_motor(id_motor, motor, quantidade_motores);

        if (variavel_sentinela == -1) {
            printf("\n" VERMELHO "[ERRO] ID invalida. O motor informado nao existe. Tente novamente." RESET "\n");
        }
    } while (variavel_sentinela == -1);

    manutencao[*ptr_manutencoes].id = motor[variavel_sentinela].id;

    // Loop de validação para o Tipo de Manutenção
    do {
        printf("  Insira o tipo de manutencao (P - Preventiva / C - Corretiva): ");
        scanf(" %c", &manutencao[*ptr_manutencoes].tipo);

        if (verificar_tipo_manutencao(manutencao[*ptr_manutencoes].tipo) == -1) {
            printf("\n" VERMELHO "[ERRO] Entrada invalida para o Tipo de Manutencao. Tente novamente." RESET "\n");
        }
    } while (verificar_tipo_manutencao(manutencao[*ptr_manutencoes].tipo) == -1);

    // Loop de validação para o Custo
    do {
        printf("  Insira o custo de manutencao: R$ ");
        scanf("%lf", &custo_ferramenta);
        if (custo_ferramenta < 0) {
            printf("\n" VERMELHO "[ERRO] Valor de custo invalido. Tente novamente." RESET "\n");
        }
    } while (custo_ferramenta < 0);
    manutencao[*ptr_manutencoes].custo = custo_ferramenta;

    // CADASTRO DA FERRAMENTA
    printf(CIANO "\n  [ Dados da Ferramenta ]" RESET "\n");

    // Loop de validação para o ID da Ferramenta
    do {
        printf("    ID da ferramenta: ");
        scanf("%d", &id_ferramenta);
        if (id_ferramenta <= 0) {
            printf("\n" VERMELHO "[ERRO] Valor de ID da ferramenta invalido. Tente novamente." RESET "\n");
        }
    } while (id_ferramenta <= 0);
    manutencao[*ptr_manutencoes].ferramenta_utilizada.id = id_ferramenta;

    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer antes do fgets

    // Loop de validação para o Nome da Ferramenta
    do {
        printf("    Nome da ferramenta: ");
        fgets(manutencao[*ptr_manutencoes].ferramenta_utilizada.nome, CHAR_MAX, stdin);
        manutencao[*ptr_manutencoes].ferramenta_utilizada.nome[strcspn(manutencao[*ptr_manutencoes].ferramenta_utilizada.nome, "\n")] = '\0';
        
        if (manutencao[*ptr_manutencoes].ferramenta_utilizada.nome[0] == '\0') {
            printf("\n" VERMELHO "[ERRO] Entrada vazia para o nome. Tente novamente." RESET "\n");
        }
    } while (manutencao[*ptr_manutencoes].ferramenta_utilizada.nome[0] == '\0');

    // Loop de validação para a Categoria da Ferramenta
    do {
        printf("    Categoria da ferramenta: ");
        fgets(manutencao[*ptr_manutencoes].ferramenta_utilizada.categoria, CHAR_MAX, stdin);
        manutencao[*ptr_manutencoes].ferramenta_utilizada.categoria[strcspn(manutencao[*ptr_manutencoes].ferramenta_utilizada.categoria, "\n")] = '\0';
        
        if (manutencao[*ptr_manutencoes].ferramenta_utilizada.categoria[0] == '\0') {
            printf("\n" VERMELHO "[ERRO] Entrada vazia para a categoria. Tente novamente." RESET "\n");
        }
    } while (manutencao[*ptr_manutencoes].ferramenta_utilizada.categoria[0] == '\0');

    printf("\n" VERDE "[SUCESSO] Manutencao registrada para o motor ID %d!" RESET "\n", motor[variavel_sentinela].id);

    (*ptr_manutencoes)++;
}

int carregar_manutencoes_realizadas(Manutencao manutencao[]) {

    // Logo no início do programa essa função é rodada a fim de carregar todas as manutenções feitas anterior à 
    // execução do código, indicando, dessa forma, quantas manutenções foram feitas anteriormente. Caso ela não 
    // consiga abrir o arquivo ela apontará este erro, tal como se ela abrir o arquivo e não conter nenhuma manutenção
    // ela informará ao usuário.

    int quantidade_manutencoes = 0;
    FILE *arquivo = fopen("manutencoes.txt", "rt");

    if (arquivo == NULL) {
        printf("\n" AMARELO "[AVISO] Nao foi possivel abrir o arquivo 'manutencoes.txt' para leitura." RESET "\n");
        return 0;
    }

    while (fscanf(arquivo, "%d; %c;%lf;%d;%[^;];%[^;\n]\n",
        &manutencao[quantidade_manutencoes].id,
        &manutencao[quantidade_manutencoes].tipo,
        &manutencao[quantidade_manutencoes].custo,
        &manutencao[quantidade_manutencoes].ferramenta_utilizada.id,
        manutencao[quantidade_manutencoes].ferramenta_utilizada.nome,
        manutencao[quantidade_manutencoes].ferramenta_utilizada.categoria) == 6) {
        
        quantidade_manutencoes++;
    }


    fclose(arquivo);
    printf("\n" VERDE "[SUCESSO] %d manutencoes anteriores carregadas da memoria!" RESET "\n", quantidade_manutencoes);

    return quantidade_manutencoes;

}

void salvar_manutencoes_realizadas(Manutencao manutencao[], int manutencoes_quantidade, int variavel_sentinela){

    // Como o próprio nome já diz, essa função é responsible por salvar todo o conteúdo do vetor estrutura manutencao[]
    // num .txt. A função não sobrescreve o conteúdo pré-existente, ela adiciona o novo conteúdo na linha de baixo.

    FILE *arquivo = fopen("manutencoes.txt", "wt");



    if (arquivo == NULL) {
        printf("\n" VERMELHO "[ERRO] Nao foi possivel abrir o arquivo 'manutencoes.txt' para salvar." RESET "\n");
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
    if (variavel_sentinela == 1) {
        printf("\n" VERDE "[SUCESSO] Dados salvos com sucesso em 'manutencoes.txt'!" RESET "\n", manutencoes_quantidade);
    }
}

void listar_manutencoes(Manutencao manutencao[], int quantidade_manutencoes, int variavel_sentinela) {
    
    // Essa função é utilizada para listar todas as manunteções atualmente registradas. Ela imprime todas elas
    // para que o usuário tenha noção do que foi realizado.

    if (quantidade_manutencoes == 0) {
        printf("\n" AMARELO "[AVISO] Nenhuma manutencao cadastrada para listar." RESET "\n");
        return;
    }

    if (variavel_sentinela == 0) {
        printf("\n" AMARELO "[ALERTA] Exibindo Manutencoes Anteriores" RESET "\n");
    } else {
        printf("\n" AMARELO "[ALERTA] Exibindo Manutencoes Novas" RESET "\n");
    }
    

    printf("\n" CIANO "%-5s   %-8s   %-6s   %-14s   %-9s   %-25s" RESET "\n", 
           "NUM", "ID_MOT", "TIPO", "CUSTO", "ID_FERR", "FERRAMENTA");
    printf(CIANO "-----------------------------------------------------------------------------------" RESET "\n");
    
    for(int i = 0; i < quantidade_manutencoes; i++){
        
        printf("%-5d   %-8d   %-6c   R$ %-11.2lf   %-9d   %-25s\n", 
            i + 1, 
            manutencao[i].id,               
            manutencao[i].tipo,             
            manutencao[i].custo,            
            manutencao[i].ferramenta_utilizada.id,   
            manutencao[i].ferramenta_utilizada.nome  
        );
    }
    printf(CIANO "-----------------------------------------------------------------------------------" RESET "\n");
}

void carregar_matriz_resumo(double (*matriz_resumo)[3], Motor motor[], int quantidade_motores, Manutencao manutencao[], int quantidade_manutencoes){
    
    // Essa função permite que carreguemos a matriz resumo (definida globalmente) com
    // os dados respectivos à cada motor cadastrado. A identação dos laços for se dá 
    // devido à necessidade de separar as manutenções realizadas por ID, uma vez que 
    // cada linha da matriz simboliza um motor diferente.
 

    for (int i = 0; i < quantidade_motores; i++) {
        int id = motor[i].id;

        for (int j = 0; j < quantidade_manutencoes; j++) {
            if (id == manutencao[j].id) {
                
                if (manutencao[j].tipo == 'P') {
                    matriz_resumo[i][0]++;
                } else if (manutencao[j].tipo == 'C') {
                    matriz_resumo[i][1]++;
                }
                matriz_resumo[i][2] += manutencao[j].custo;
            }
        }
    }
}

void exibir_relatorio(double (*matriz_resumo)[3], Manutencao manutencao[], int quantidade_manutencoes, Motor motor[], int quantidade_motores, int variavel_sentinela) {
    
    // A função exibe o relatório geral dos motores, quantidade de manutenções preventivas, corretivas etc. Enfim, o funcionamento
    // é concebido graças à função 'carregar_matriz_resumo' que atualiza os dados da matriz global, tal como o vetor_ids_motores, 
    // que também é global. Sendo assim, não fica difícil manipular os dados e computá-los.
    

    if (quantidade_motores == 0) {
        printf("\n" AMARELO "[AVISO] Nenhum motor cadastrado para gerar relatorio." RESET "\n");
        return;
    }

    if (variavel_sentinela == 0) {
        printf("\n" AMARELO "[ALERTA] Exibindo Relatorio Anterior" RESET "\n");
    }

    carregar_matriz_resumo(matriz_resumo, motor, quantidade_motores, manutencao, quantidade_manutencoes);

    
    int id_motor_maior_custo = motor[0].id;
    double maior_custo_acumulado = matriz_resumo[0][2];
    double valor_gasto_manutencoes_preventivas = 0;
    double valor_gasto_manutencoes_corretivas = 0;

    printf("\n" CIANO "===========================================================" RESET);
    printf("\n" BRANCO "                  RELATORIO DE MOTORES" RESET);
    printf("\n" CIANO "===========================================================" RESET "\n");

    for (int i = 0; i < quantidade_motores; i++) {
        
        printf("\n  " BRANCO "Motor ID (%d):" RESET "\n", motor[i].id);
        printf("    - Quantidade manutencoes preventivas: " CIANO "%.0f" RESET "\n", matriz_resumo[i][0]);
        printf("    - Quantidade manutencoes corretivas:  " CIANO "%.0f" RESET "\n", matriz_resumo[i][1]);
        printf("    - Custo total acumulado:             " VERDE "R$ %.2f" RESET "\n", matriz_resumo[i][2]);

        
        if (matriz_resumo[i][2] > maior_custo_acumulado) {
            maior_custo_acumulado = matriz_resumo[i][2];
            id_motor_maior_custo = motor[i].id; 
        }
    }

    for (int j = 0; j < quantidade_manutencoes; j++) {
        if (manutencao[j].tipo == 'P' || manutencao[j].tipo == 'p') {
            valor_gasto_manutencoes_preventivas += manutencao[j].custo;
        } else if (manutencao[j].tipo == 'C' || manutencao[j].tipo == 'c') {
            valor_gasto_manutencoes_corretivas += manutencao[j].custo;
        }
    }

    printf("\n" CIANO "===========================================================" RESET);
    printf("\n" BRANCO "                  RESUMO CONSOLIDADO" RESET);
    printf("\n" CIANO "===========================================================" RESET "\n");
    printf("  -> Motor com maior custo acumulado: ID " CIANO "%d" RESET " (" VERMELHO "R$ %.2lf" RESET ")\n", id_motor_maior_custo, maior_custo_acumulado);
    printf("  -> Valor total em manutencoes preventivas: " VERDE "R$ %.2lf" RESET "\n", valor_gasto_manutencoes_preventivas);
    printf("  -> Valor total em manutencoes corretivas:  " VERDE "R$ %.2lf" RESET "\n", valor_gasto_manutencoes_corretivas);
    printf(CIANO "===========================================================" RESET "\n");
}
/* ============================================================================ */

int main(void) {

    Motor motor[MOTORES_MAX];
    Manutencao manutencao[MANUTENCOES_MAX];
    
    int opcao;

    // A variável 'motores_anteriores' recebe o total carregado do arquivo
    int motores_quantidade_atual = 0;
    int motores_anteriores;
    carregar_motores(&motores_anteriores, motor);
    
    // A variável 'manutencao_atual' recebe o total carregado do arquivo
    int manutencoes_anteriores = carregar_manutencoes_realizadas(manutencao); 
    int manutencoes_atuais = 0;

    // Variável que permite o programa saber se o usuário já salvou ou não os dados.
    int clicou_salvar = 0;

    do {
        printf("\n" CIANO "===========================================" RESET "\n");
        printf("  1. " BRANCO "Cadastrar motor" RESET "\n");
        printf("  2. " BRANCO "Registrar manutencao" RESET "\n");
        printf("  3. " BRANCO "Listar motores cadastrados" RESET "\n");
        printf("  4. " BRANCO "Listar manuntencoes registradas" RESET "\n");
        printf("  5. " BRANCO "Exibir relatorios" RESET "\n");
        printf("  6. " VERDE "Salvar dados" RESET "\n");
        printf("  7. " VERMELHO "Sair do programa" RESET "\n");
        printf(CIANO "===========================================" RESET "\n");
        printf("  Escolha uma opcao: ");

        scanf("%d", &opcao); 
        getchar(); // Limpa o \n para não atrapalhar futuras leituras de strings

        if (opcao < 1 || opcao > 7) {
            printf("\n" VERMELHO "[ERRO] Opcao Invalida! Digite apenas numeros de 1 a 7." RESET "\n");
            continue;
        }

        switch (opcao){
            case 1:
                cadastro_motor(&motores_quantidade_atual, motor);
                printf("\n" VERDE "[SUCESSO] Motores cadastrados com sucesso!!" RESET "\n");
                break;
            
            case 2:
                if (motores_quantidade_atual == 0) registrar_manutencao(&manutencoes_atuais, motor, manutencao, motores_anteriores);
                else registrar_manutencao(&manutencoes_atuais, motor, manutencao, motores_quantidade_atual);
                break;
            
            case 3:
                if (motores_quantidade_atual == 0) listar_motor(&motores_anteriores, motor, 0);
                else listar_motor(&motores_quantidade_atual, motor, 1);
                break;
            
            case 4:
                if (manutencoes_atuais == 0) listar_manutencoes(manutencao, manutencoes_anteriores, 0);
                else listar_manutencoes(manutencao, manutencoes_atuais, 1);
                break;

            case 5: {
                double matriz_resumo[MOTORES_MAX][3] = {0};
                if (manutencoes_atuais == 0) exibir_relatorio(matriz_resumo, manutencao, manutencoes_anteriores, motor, motores_anteriores, 0);
                else exibir_relatorio(matriz_resumo, manutencao, manutencoes_atuais, motor, motores_quantidade_atual, 1);
                
                break;
            }
            case 6:
                // Salva o estado atual exato da memória nos arquivos
                salvar_motores(&motores_quantidade_atual, motor, 1); 
                salvar_manutencoes_realizadas(manutencao, manutencoes_atuais, 1);

                clicou_salvar = 1; 

                printf("\n" AMARELO "[SUCESSO] Todos os dados disponiveis na MEMORIA foram salvos nos arquivos com exito!" RESET "\n");
                break;

            case 7:
                if (clicou_salvar == 1) {
                    printf("\n" BRANCO "Encerrando o sistema. Ate logo!..." RESET "\n\n");
                    break;
                }
                
                printf("\n" AMARELO "[AVISO] Salvamento automatico ativado antes de encerrar." RESET "\n");
                if (motores_quantidade_atual == 0) {
                    printf("\n" AMARELO "[ALERTA] 'motores.txt' nao foi alterado (dados antigos mantidos)." RESET "\n");
                    salvar_motores(&motores_anteriores, motor, 0);
                } else {
                    salvar_motores(&motores_quantidade_atual, motor, 1);
                }

                if (manutencoes_atuais == 0) {
                    printf("\n" AMARELO "[ALERTA] 'manutencoes.txt' nao foi alterado (dados antigos mantidos)." RESET "\n");
                    salvar_manutencoes_realizadas(manutencao, manutencoes_anteriores, 0);
                } else {
                    salvar_manutencoes_realizadas(manutencao, manutencoes_atuais, 1);
                }
                
                printf("\n" BRANCO "Sistema finalizado com seguranca. Ate mais!" RESET "\n\n");
                break;
        }

    } while(opcao != 7);
    return 0;
}