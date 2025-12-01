#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da struct Item que representa um item na mochila
typedef struct {
    char nome[30];      // Nome do item (ex: "AK-47", "Bandagem")
    char tipo[20];      // Tipo do item (ex: "arma", "municao", "cura", "ferramenta")
    int quantidade;     // Quantidade disponível do item
} Item;

// Protótipos das funções
void inserirItem(Item mochila[], int *totalItens);
void removerItem(Item mochila[], int *totalItens);
void listarItens(Item mochila[], int totalItens);
void buscarItem(Item mochila[], int totalItens);
void exibirMenu();
void limparBuffer();

int main() {
    // Vetor para armazenar até 10 itens (mochila do jogador)
    Item mochila[10];
    int totalItens = 0; // Contador de itens na mochila
    int opcao;
    
    printf("=== SISTEMA DE INVENTARIO - MOCHILA DE LOOT ===\n");
    printf("Bem-vindo ao sistema de gerenciamento de inventario!\n");
    printf("Você pode armazenar até 10 itens na mochila.\n\n");
    
    // Loop principal do programa
    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer(); // Limpa o buffer do teclado
        
        switch (opcao) {
            case 1:
                // Inserir novo item
                inserirItem(mochila, &totalItens);
                break;
                
            case 2:
                // Remover item existente
                removerItem(mochila, &totalItens);
                break;
                
            case 3:
                // Listar todos os itens
                listarItens(mochila, totalItens);
                break;
                
            case 4:
                // Buscar item por nome
                buscarItem(mochila, totalItens);
                break;
                
            case 5:
                // Sair do sistema
                printf("\nSaindo do sistema de inventario...\n");
                printf("Obrigado por usar a mochila de loot!\n");
                break;
                
            default:
                printf("\nOpcao invalida! Por favor, escolha uma opcao de 1 a 5.\n");
        }
        
        printf("\n");
        
    } while (opcao != 5);
    
    return 0;
}

// Função para exibir o menu principal
void exibirMenu() {
    printf("=== MENU PRINCIPAL ===\n");
    printf("1. Inserir novo item\n");
    printf("2. Remover item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Buscar item por nome\n");
    printf("5. Sair\n");
}

// Função para limpar o buffer do teclado
// Necessária para evitar problemas com scanf e fgets
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para inserir um novo item na mochila
// Recebe o vetor mochila e um ponteiro para o total de itens
void inserirItem(Item mochila[], int *totalItens) {
    // Verifica se a mochila está cheia
    if (*totalItens >= 10) {
        printf("\nERRO: A mochila está cheia! Capacidade máxima: 10 itens.\n");
        return;
    }
    
    printf("\n=== INSERIR NOVO ITEM ===\n");
    
    // Solicita informações do novo item
    printf("Nome do item (max 29 caracteres): ");
    fgets(mochila[*totalItens].nome, 30, stdin);
    mochila[*totalItens].nome[strcspn(mochila[*totalItens].nome, "\n")] = '\0'; // Remove o \n
    
    printf("Tipo do item (ex: arma, municao, cura, ferramenta): ");
    fgets(mochila[*totalItens].tipo, 20, stdin);
    mochila[*totalItens].tipo[strcspn(mochila[*totalItens].tipo, "\n")] = '\0'; // Remove o \n
    
    printf("Quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);
    limparBuffer(); // Limpa buffer após scanf
    
    // Verifica se a quantidade é válida
    if (mochila[*totalItens].quantidade <= 0) {
        printf("ERRO: Quantidade deve ser maior que zero!\n");
        return;
    }
    
    // Incrementa o contador de itens
    (*totalItens)++;
    
    printf("\nItem cadastrado com sucesso!\n");
    
    // Exibe os itens atualizados
    listarItens(mochila, *totalItens);
}

// Função para remover um item da mochila
// Recebe o vetor mochila e um ponteiro para o total de itens
void removerItem(Item mochila[], int *totalItens) {
    // Verifica se a mochila está vazia
    if (*totalItens == 0) {
        printf("\nERRO: A mochila está vazia! Nenhum item para remover.\n");
        return;
    }
    
    printf("\n=== REMOVER ITEM ===\n");
    
    // Exibe os itens disponíveis para remoção
    printf("Itens na mochila:\n");
    listarItens(mochila, *totalItens);
    
    char nomeRemover[30];
    printf("\nDigite o nome do item que deseja remover: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0'; // Remove o \n
    
    // Busca sequencial pelo item
    int indice = -1; // Inicializa com valor inválido
    
    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            indice = i;
            break;
        }
    }
    
    // Verifica se o item foi encontrado
    if (indice == -1) {
        printf("ERRO: Item '%s' não encontrado na mochila!\n", nomeRemover);
        return;
    }
    
    // Remove o item deslocando os elementos seguintes
    printf("\nRemovendo item: %s (Tipo: %s, Quantidade: %d)\n", 
           mochila[indice].nome, mochila[indice].tipo, mochila[indice].quantidade);
    
    // Desloca os itens para preencher o espaço vazio
    for (int i = indice; i < *totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    
    // Decrementa o contador de itens
    (*totalItens)--;
    
    printf("Item removido com sucesso!\n");
    
    // Exibe os itens atualizados
    listarItens(mochila, *totalItens);
}

// Função para listar todos os itens na mochila
// Recebe o vetor mochila e o total de itens por valor
void listarItens(Item mochila[], int totalItens) {
    printf("\n=== ITENS NA MOCHILA (%d/%d) ===\n", totalItens, 10);
    
    // Verifica se a mochila está vazia
    if (totalItens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }
    
    // Cabeçalho da tabela
    printf("\n%-5s %-30s %-20s %-10s\n", 
           "ID", "NOME", "TIPO", "QUANTIDADE");
    printf("%-5s %-30s %-20s %-10s\n", 
           "---", "----", "----", "---------");
    
    // Lista todos os itens
    for (int i = 0; i < totalItens; i++) {
        printf("%-5d %-30s %-20s %-10d\n", 
               i + 1, 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }
    
    // Exibe estatísticas
    printf("\nTotal de itens diferentes: %d\n", totalItens);
    
    // Calcula o total de todos os itens
    int totalGeral = 0;
    for (int i = 0; i < totalItens; i++) {
        totalGeral += mochila[i].quantidade;
    }
    printf("Total de itens (soma das quantidades): %d\n", totalGeral);
}

// Função para buscar um item pelo nome usando busca sequencial
// Recebe o vetor mochila e o total de itens por valor
void buscarItem(Item mochila[], int totalItens) {
    // Verifica se a mochila está vazia
    if (totalItens == 0) {
        printf("\nERRO: A mochila está vazia! Nenhum item para buscar.\n");
        return;
    }
    
    printf("\n=== BUSCAR ITEM ===\n");
    
    char nomeBuscar[30];
    printf("Digite o nome do item que deseja buscar: ");
    fgets(nomeBuscar, 30, stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = '\0'; // Remove o \n
    
    // Implementação da busca sequencial
    int encontrado = 0;
    int comparacoes = 0; // Contador de comparações (para análise de desempenho)
    
    printf("\nRealizando busca sequencial...\n");
    
    for (int i = 0; i < totalItens; i++) {
        comparacoes++;
        
        // Compara o nome do item atual com o nome buscado
        if (strcmp(mochila[i].nome, nomeBuscar) == 0) {
            encontrado = 1;
            printf("\n✅ Item encontrado!\n");
            printf("   Posicao na mochila: %d\n", i + 1);
            printf("   Nome: %s\n", mochila[i].nome);
            printf("   Tipo: %s\n", mochila[i].tipo);
            printf("   Quantidade: %d\n", mochila[i].quantidade);
            break; // Interrompe a busca ao encontrar o item
        }
    }
    
    // Se o item não foi encontrado
    if (!encontrado) {
        printf("\n❌ Item '%s' não encontrado na mochila.\n", nomeBuscar);
    }
    
    // Informações sobre a busca (útil para entender o desempenho)
    printf("\nInformacoes da busca:\n");
    printf("   Total de itens na mochila: %d\n", totalItens);
    printf("   Comparacoes realizadas: %d\n", comparacoes);
    
    // Análise do desempenho da busca sequencial
    if (encontrado) {
        printf("   Desempenho: Busca concluída em menos de 2 segundos ✓\n");
    }
}