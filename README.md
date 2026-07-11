# ⚙️ Sistema de Gerenciamento de Motores

O **Sistema de Gerenciamento de Motores** é uma aplicação de terminal desenvolvida em Linguagem C voltada para o cadastro de motores elétricos industriais e o registro de suas intervenções de manutenção (preventivas e corretivas). O software conta com um banco de dados persistente em arquivos de texto, mecanismos de validação de entradas de dados e geração automatizada de relatórios estatísticos consolidados por meio de matrizes de desempenho.

---

## 🚀 Funcionalidades Principais

* **Cadastro Estruturado de Motores:** Permite registrar novos motores validando dinamicamente o impedimento de IDs duplicados e o bloqueio de potências nulas ou negativas.
* **Histórico de Intervenções:** Registro detalhado de manutenções vinculadas ao ID de um motor existente, catalogando o tipo (Preventiva/Corretiva), o custo da operação e a ferramenta específica utilizada.
* **Persistência de Dados Automatizada:** Carregamento automático dos históricos salvos ao iniciar o programa e salvamento obrigatório ao encerrar a aplicação, evitando a perda de dados.
* **Relatórios Estatísticos Dinâmicos:** Mapeia os dados em uma Matriz de Resumo global para calcular custos acumulados por motor, identificar a máquina com maior despesa e realizar o balanço financeiro do setor.
* **Interface Colorida (Terminal):** Utilização de códigos de escape ANSI para prover feedbacks visuais claros de erro (vermelho), sucesso (verde) e alertas (amarelo) diretamente no terminal de comandos.

---

## 🛠️ Tecnologias e Diretrizes Técnicas

O projeto foi construído utilizando estritamente as bibliotecas padrão da linguagem, garantindo portabilidade máxima e ausência de dependências externas:

* `<stdio.h>` — Operações de entrada e saída padrão (I/O).
* `<stdlib.h>` — Alocação e gerenciamento de fluxo de execução.
* `<string.h>` — Manipulação e tratamento de vetores de caracteres.
* `<math.h>` — Suporte para operações matemáticas vinculadas (linkagem de biblioteca).

### Limitações do Escopo (Constantes)
* **Caracteres máximos de strings:** 100 (`CHAR_MAX`) 
* **Limite máximo de motores:** 100 (`MOTORES_MAX`) 
* **Limite máximo de manutenções:** 100 (`MANUTENCOES_MAX`) 
---

## 📂 Estrutura do Ecossistema de Arquivos

O ecossistema do projeto é integrado por quatro arquivos fundamentais:

| Arquivo | Tipo | Descrição 
| :--- | :--- | :--- |
| `main.c` | Código-Fonte | Arquivo principal com as definições das structs (`Motor`, `Ferramenta`, `Manutencao`), lógica de validação, manipulação de arquivos e máquina de estados do menu interativo. |
| `motores.txt` | Banco de Dados | Armazenamento persistente dos motores no formato delimitado por ponto e vírgula (`;`). <br> *Formato:* `[ID];[Nome/Descrição];[Potência]`. |
| `manutencoes.txt` | Banco de Dados | Histórico persistente das intervenções com composição integrada dos dados da ferramenta utilizada. <br> *Formato:* `[ID_Motor];[Tipo];[Custo];[ID_Ferramenta];[Nome_Ferramenta];[Categoria_Ferramenta]. |
| `ELE_LEIAME.txt` | Documentação | Relatório técnico contendo as diretrizes operacionais originais para avaliação acadêmic. |

---

## 💻 Como Compilar e Executar

A compilação via terminal é universal e pode ser realizada no Windows, Linux ou macO.

### 1. Compilação
Abra o seu terminal, navegue com o comando `cd` até a pasta onde o arquivo `main.c` está localizado e execute o comando do compilador GCC:

```bash
gcc main.c -o programa -lm
```
> ⚠️ **Nota técnica:** O parâmetro `-lm` é obrigatório para realizar a vinculação correta da biblioteca matemática (`<math.h>`) em ambientes Linux e macOS.

### 2. Execução

* **No Windows (Prompt de Comando ou PowerShell):**
    ```bash
    programa.exe
    ```
    *(ou simplesmente digite: `programa`)* 
* **No Linux ou macOS:**
    ```bash
    ./programa
    ```

---

## 📊 Demonstração do Fluxo de Operação

O software funciona baseado em um fluxo guiado por menus interativos:

1. **Inicialização:** O sistema tenta ler `motores.txt` e `manutencoes.txt`. Se os arquivos existirem, os dados populam a RAM; caso contrário, os vetores iniciam zerados.
2. **Cadastro (Opção 1):** O usuário informa a quantidade de motores e fornece ID, nome descritivo e potência em kW. O sistema recusa IDs repetidos ou dados inconsistentes.
3. **Intervenção (Opção 2):** Ao registrar uma manutenção, o software verifica se o ID do motor de fato existe. O tipo aceita estritamente `P` (Preventiva) ou `C` (Corretiva).
4. **Exibição de Relatórios (Opção 5):** Consolida a matriz exibindo individualmente as métricas de cada motor e destaca o balanço financeiro final com o total investido por categoria.
5. **Encerramento Seguro (Opção 7):** Se o usuário optar por sair sem salvar manualmente (Opção 6), o gatilho de salvamento automático é disparado gravando o estado atual de forma íntegra no disco antes de fechar.

---

## 👥 Autores

Trabalho computacional desenvolvido para a disciplina de Programação I do curso de Engenharia Elétrica:
* **Arthur Sobral Moreira** — *Universidade Federal do Espírito Santo (UFES)* 
* **Ricardo Augusto Bona Barbosa** — *Universidade Federal do Espírito Santo (UFES)* 

**Professor(a) Orientador(a):** Norminda Luiza Oliveira Bodart   
**Semestre Letivo:** 2026/1 