# Sistema de Gestão de Motores e Manutenções (UFES - 2026/1)

Este projeto consiste em um sistema desenvolvido em **linguagem C** para o gerenciamento de motores elétricos e o registro de suas respectivas manutenções. O software foi criado como parte da disciplina de **Programação I** do curso de **Engenharia Elétrica** da Universidade Federal do Espírito Santo (UFES).

## 📌 Objetivo
O objetivo principal é cadastrar motores e registrar intervenções (preventivas e corretivas), utilizando persistência de dados em arquivos de texto e gerando relatórios estatísticos através de uma matriz de resumo.

## 🚀 Funcionalidades
O sistema opera através de um menu interativo com as seguintes opções:
1. **Cadastrar motor:** Registro de ID único, nome e potência.
2. **Registrar manutenção:** Associa uma manutenção (Preventiva ou Corretiva) a um motor, incluindo os dados da ferramenta utilizada.
3. **Listar motores:** Exibe todos os motores cadastrados.
4. **Listar manutenções:** Exibe o histórico de intervenções registradas.
5. **Exibir relatórios:** Gera estatísticas como o custo total acumulado por motor e identifica o motor com maior gasto.
6. **Salvar/Sair:** Os dados são salvos automaticamente nos arquivos ao encerrar o programa.

## 🛠️ Detalhes Técnicos
*   **Estruturas (structs):** Utilização obrigatória de três estruturas principais: `Motor`, `Ferramenta` e `Manutenção` (sendo que a manutenção compõe a ferramenta).
*   **Armazenamento:** Os dados são mantidos em vetores de estruturas e consolidados em uma **Matriz de Resumo** para a geração de relatórios.
*   **Manipulação de Arquivos:** Utiliza as funções da biblioteca `stdio.h` (`fopen`, `fprintf`, `fscanf`, `fclose`) para persistência em arquivos `.txt`.
*   **Validação:** O sistema valida IDs duplicados, valores negativos e tipos de manutenção inválidos.

## 📂 Estrutura de Arquivos
O projeto utiliza os seguintes arquivos para persistência:
*   `motores.txt`: Armazena os dados dos motores no formato `id;nome;potencia`.
*   `manutencoes.txt`: Armazena as manutenções no formato `idMotor;tipo;custo;idFerramenta;nomeFerramenta;categoriaFerramenta`.
*   `ELE_LEIAME.txt`: Instruções técnicas de compilação e execução.

## 💻 Como Compilar e Executar
...

## 📋 Regras de Negócio Implementadas
*   **IDs de Motor:** Devem ser únicos e inteiros positivos.
*   **Tipos de Manutenção:** Apenas 'P' (Preventiva) ou 'C' (Corretiva) são aceitos.
*   **Persistência Automática:** O carregamento dos dados ocorre no início da execução e o salvamento é realizado ao sair.

---
**Curso:** Engenharia Elétrica - UFES  
**Disciplina:** Programação I  
**Professor(a):** Norminda Luiza Oliveira Bodart
