#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ============================================
// DEFINIÇÕES DAS STRUCTS
// ============================================

// Struct para representar um item (usada em ambas as estruturas)
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Struct para nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ============================================
// IMPLEMENTAÇÃO COM VETOR (LISTA SEQUENCIAL)
// ============================================

// Variáveis globais para contagem de operações (vetor)
int comparacoes_vetor = 0;
int comparacoes_binaria = 0;

// Estrutura para a mochila com vetor
typedef struct {
    Item itens[100];    // Capacidade máxima de 100 itens
    int tamanho;        // Número atual de itens
    int capacidade;     // Capacidade máxima (100)
} MochilaVetor;

// Inicializa a mochila vetor
void inicializarVetor(MochilaVetor* mochila) {
    mochila->tamanho = 0;
    mochila->capacidade = 100;
    printf("Mochila vetor inicializada com capacidade para %d itens\n", mochila->capacidade);
}

// Insere item no vetor (no final)
int inserirItemVetor(MochilaVetor* mochila, Item novoItem) {
    if (mochila->tamanho >= mochila->capacidade) {
        printf("ERRO: Mochila vetor cheia!\n");
        return 0;
    }
    
    // Verifica se item já existe
    for (int i = 0; i < mochila->tamanho; i++) {
        if (strcmp(mochila->itens[i].nome, novoItem.nome) == 0) {
            printf("Item '%s' já existe na mochila. Atualizando quantidade.\n", novoItem.nome);
            mochila->itens[i].quantidade += novoItem.quantidade;
            return 1;
        }
    }
    
    // Insere no final
    mochila->itens[mochila->tamanho] = novoItem;
    mochila->tamanho++;
    printf("Item '%s' inserido na mochila vetor\n", novoItem.nome);
    return 1;
}

// Remove item do vetor por nome
int removerItemVetor(MochilaVetor* mochila, char* nome) {
    comparacoes_vetor = 0; // Reset contador
    
    for (int i = 0; i < mochila->tamanho; i++) {
        comparacoes_vetor++;
        if (strcmp(mochila->itens[i].nome, nome) == 0) {
            // Move todos os elementos uma posição para frente
            for (int j = i; j < mochila->tamanho - 1; j++) {
                mochila->itens[j] = mochila->itens[j + 1];
            }
            mochila->tamanho--;
            printf("Item '%s' removido da mochila vetor\n", nome);
            printf("Comparacoes necessarias para encontrar o item: %d\n", comparacoes_vetor);
            return 1;
        }
    }
    
    printf("Item '%s' não encontrado na mochila vetor\n", nome);
    printf("Comparacoes realizadas: %d\n", comparacoes_vetor);
    return 0;
}

// Lista todos os itens no vetor
void listarItensVetor(MochilaVetor* mochila) {
    if (mochila->tamanho == 0) {
        printf("Mochila vetor vazia!\n");
        return;
    }
    
    printf("\n=== ITENS NA MOCHILA VETOR (%d/%d) ===\n", mochila->tamanho, mochila->capacidade);
    printf("%-5s %-30s %-20s %-10s\n", "ID", "NOME", "TIPO", "QUANTIDADE");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < mochila->tamanho; i++) {
        printf("%-5d %-30s %-20s %-10d\n", 
               i + 1, 
               mochila->itens[i].nome, 
               mochila->itens[i].tipo, 
               mochila->itens[i].quantidade);
    }
    printf("------------------------------------------------------------\n");
}

// Busca sequencial no vetor
int buscarSequencialVetor(MochilaVetor* mochila, char* nome, Item* resultado) {
    comparacoes_vetor = 0; // Reset contador
    
    for (int i = 0; i < mochila->tamanho; i++) {
        comparacoes_vetor++;
        if (strcmp(mochila->itens[i].nome, nome) == 0) {
            *resultado = mochila->itens[i];
            return 1; // Encontrado
        }
    }
    
    return 0; // Não encontrado
}

// Ordena o vetor por nome usando Bubble Sort
void ordenarVetor(MochilaVetor* mochila) {
    if (mochila->tamanho <= 1) return;
    
    int trocas;
    int comparacoes_ordenacao = 0;
    
    printf("Ordenando vetor com Bubble Sort...\n");
    
    do {
        trocas = 0;
        for (int i = 0; i < mochila->tamanho - 1; i++) {
            comparacoes_ordenacao++;
            if (strcmp(mochila->itens[i].nome, mochila->itens[i + 1].nome) > 0) {
                // Troca os itens
                Item temp = mochila->itens[i];
                mochila->itens[i] = mochila->itens[i + 1];
                mochila->itens[i + 1] = temp;
                trocas++;
            }
        }
    } while (trocas > 0);
    
    printf("Vetor ordenado! Comparacoes realizadas: %d\n", comparacoes_ordenacao);
}

// Busca binária no vetor ordenado
int buscarBinariaVetor(MochilaVetor* mochila, char* nome, Item* resultado) {
    comparacoes_binaria = 0; // Reset contador
    
    int inicio = 0;
    int fim = mochila->tamanho - 1;
    int meio;
    
    while (inicio <= fim) {
        comparacoes_binaria++;
        meio = (inicio + fim) / 2;
        
        int comparacao = strcmp(mochila->itens[meio].nome, nome);
        
        if (comparacao == 0) {
            *resultado = mochila->itens[meio];
            return 1; // Encontrado
        }
        
        if (comparacao < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    return 0; // Não encontrado
}

// ============================================
// IMPLEMENTAÇÃO COM LISTA ENCADEADA
// ============================================

// Variáveis globais para contagem de operações (lista)
int comparacoes_lista = 0;

// Estrutura para a mochila com lista encadeada
typedef struct {
    No* inicio;
    int tamanho;
} MochilaLista;

// Inicializa a lista encadeada
void inicializarLista(MochilaLista* lista) {
    lista->inicio = NULL;
    lista->tamanho = 0;
    printf("Mochila lista encadeada inicializada\n");
}

// Insere item na lista encadeada (no início)
int inserirItemLista(MochilaLista* lista, Item novoItem) {
    // Verifica se item já existe
    No* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, novoItem.nome) == 0) {
            printf("Item '%s' já existe na mochila lista. Atualizando quantidade.\n", novoItem.nome);
            atual->dados.quantidade += novoItem.quantidade;
            return 1;
        }
        atual = atual->proximo;
    }
    
    // Cria novo nó
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("ERRO: Falha na alocação de memória!\n");
        return 0;
    }
    
    novoNo->dados = novoItem;
    novoNo->proximo = lista->inicio;
    lista->inicio = novoNo;
    lista->tamanho++;
    
    printf("Item '%s' inserido na mochila lista encadeada\n", novoItem.nome);
    return 1;
}

// Remove item da lista por nome
int removerItemLista(MochilaLista* lista, char* nome) {
    comparacoes_lista = 0; // Reset contador
    
    if (lista->inicio == NULL) {
        printf("Lista vazia!\n");
        return 0;
    }
    
    // Caso especial: remover o primeiro elemento
    if (strcmp(lista->inicio->dados.nome, nome) == 0) {
        comparacoes_lista++;
        No* temp = lista->inicio;
        lista->inicio = lista->inicio->proximo;
        printf("Item '%s' removido da mochila lista\n", nome);
        printf("Comparacoes necessarias: %d\n", comparacoes_lista);
        free(temp);
        lista->tamanho--;
        return 1;
    }
    
    // Procura o item na lista
    No* atual = lista->inicio;
    No* anterior = NULL;
    
    while (atual != NULL) {
        comparacoes_lista++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            // Remove o nó encontrado
            anterior->proximo = atual->proximo;
            printf("Item '%s' removido da mochila lista\n", nome);
            printf("Comparacoes necessarias: %d\n", comparacoes_lista);
            free(atual);
            lista->tamanho--;
            return 1;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    
    printf("Item '%s' não encontrado na mochila lista\n", nome);
    printf("Comparacoes realizadas: %d\n", comparacoes_lista);
    return 0;
}

// Lista todos os itens na lista encadeada
void listarItensLista(MochilaLista* lista) {
    if (lista->inicio == NULL) {
        printf("Mochila lista vazia!\n");
        return;
    }
    
    printf("\n=== ITENS NA MOCHILA LISTA (%d itens) ===\n", lista->tamanho);
    printf("%-5s %-30s %-20s %-10s\n", "POS", "NOME", "TIPO", "QUANTIDADE");
    printf("------------------------------------------------------------\n");
    
    No* atual = lista->inicio;
    int posicao = 1;
    
    while (atual != NULL) {
        printf("%-5d %-30s %-20s %-10d\n", 
               posicao, 
               atual->dados.nome, 
               atual->dados.tipo, 
               atual->dados.quantidade);
        atual = atual->proximo;
        posicao++;
    }
    printf("------------------------------------------------------------\n");
}

// Busca sequencial na lista encadeada
int buscarSequencialLista(MochilaLista* lista, char* nome, Item* resultado) {
    comparacoes_lista = 0; // Reset contador
    
    No* atual = lista->inicio;
    
    while (atual != NULL) {
        comparacoes_lista++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            *resultado = atual->dados;
            return 1; // Encontrado
        }
        atual = atual->proximo;
    }
    
    return 0; // Não encontrado
}

// Libera toda a memória da lista encadeada
void liberarLista(MochilaLista* lista) {
    No* atual = lista->inicio;
    No* proximo;
    
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    
    lista->inicio = NULL;
    lista->tamanho = 0;
    printf("Memória da lista encadeada liberada\n");
}

// ============================================
// FUNÇÕES AUXILIARES E MENU
// ============================================

// Cria um item com dados fornecidos pelo usuário
Item criarItem() {
    Item novoItem;
    
    printf("Nome do item: ");
    scanf("%s", novoItem.nome);
    
    printf("Tipo do item (arma, municao, cura, ferramenta): ");
    scanf("%s", novoItem.tipo);
    
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    
    return novoItem;
}

// Menu principal
void exibirMenuPrincipal() {
    printf("\n=== SISTEMA COMPARATIVO: VETOR vs LISTA ENCADEADA ===\n");
    printf("1. Trabalhar com Mochila Vetor\n");
    printf("2. Trabalhar com Mochila Lista Encadeada\n");
    printf("3. Comparar desempenho das buscas\n");
    printf("4. Sair\n");
    printf("Escolha uma opcao: ");
}

// Menu para operações com vetor
void exibirMenuVetor() {
    printf("\n=== OPERACOES COM VETOR ===\n");
    printf("1. Inserir item\n");
    printf("2. Remover item por nome\n");
    printf("3. Listar todos os itens\n");
    printf("4. Busca sequencial por nome\n");
    printf("5. Ordenar vetor (Bubble Sort)\n");
    printf("6. Busca binaria (apos ordenacao)\n");
    printf("7. Voltar ao menu principal\n");
    printf("Escolha uma opcao: ");
}

// Menu para operações com lista
void exibirMenuLista() {
    printf("\n=== OPERACOES COM LISTA ENCADEADA ===\n");
    printf("1. Inserir item\n");
    printf("2. Remover item por nome\n");
    printf("3. Listar todos os itens\n");
    printf("4. Busca sequencial por nome\n");
    printf("5. Voltar ao menu principal\n");
    printf("Escolha uma opcao: ");
}

// Teste de desempenho comparativo
void testarDesempenho(MochilaVetor* mochilaVetor, MochilaLista* mochilaLista) {
    printf("\n=== TESTE DE DESEMPENHO COMPARATIVO ===\n");
    
    if (mochilaVetor->tamanho == 0 || mochilaLista->tamanho == 0) {
        printf("Ambas as estruturas precisam ter itens para testar!\n");
        return;
    }
    
    char nomeBusca[30];
    printf("Digite o nome do item para buscar: ");
    scanf("%s", nomeBusca);
    
    Item resultado;
    clock_t inicio, fim;
    double tempoVetorSeq, tempoListaSeq, tempoVetorBin;
    
    // Teste 1: Busca sequencial no vetor
    comparacoes_vetor = 0;
    inicio = clock();
    int encontradoVetor = buscarSequencialVetor(mochilaVetor, nomeBusca, &resultado);
    fim = clock();
    tempoVetorSeq = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    // Teste 2: Busca sequencial na lista
    comparacoes_lista = 0;
    inicio = clock();
    int encontradoLista = buscarSequencialLista(mochilaLista, nomeBusca, &resultado);
    fim = clock();
    tempoListaSeq = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    // Teste 3: Busca binária no vetor (se estiver ordenado)
    int encontradoBinario = 0;
    tempoVetorBin = 0;
    
    printf("\n--- RESULTADOS DA COMPARACAO ---\n");
    printf("Item buscado: '%s'\n", nomeBusca);
    printf("\n1. BUSCA SEQUENCIAL NO VETOR:\n");
    printf("   Resultado: %s\n", encontradoVetor ? "ENCONTRADO" : "NAO ENCONTRADO");
    printf("   Comparacoes: %d\n", comparacoes_vetor);
    printf("   Tempo: %.6f segundos\n", tempoVetorSeq);
    
    printf("\n2. BUSCA SEQUENCIAL NA LISTA ENCADEADA:\n");
    printf("   Resultado: %s\n", encontradoLista ? "ENCONTRADO" : "NAO ENCONTRADO");
    printf("   Comparacoes: %d\n", comparacoes_lista);
    printf("   Tempo: %.6f segundos\n", tempoListaSeq);
    
    // Verificar se podemos fazer busca binária
    printf("\n3. BUSCA BINARIA NO VETOR (requer ordenacao):\n");
    
    // Verificar se o vetor está ordenado
    int ordenado = 1;
    for (int i = 0; i < mochilaVetor->tamanho - 1; i++) {
        if (strcmp(mochilaVetor->itens[i].nome, mochilaVetor->itens[i + 1].nome) > 0) {
            ordenado = 0;
            break;
        }
    }
    
    if (!ordenado) {
        printf("   Vetor não está ordenado! Use a opcao 5 no menu do vetor primeiro.\n");
    } else {
        comparacoes_binaria = 0;
        inicio = clock();
        encontradoBinario = buscarBinariaVetor(mochilaVetor, nomeBusca, &resultado);
        fim = clock();
        tempoVetorBin = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        
        printf("   Resultado: %s\n", encontradoBinario ? "ENCONTRADO" : "NAO ENCONTRADO");
        printf("   Comparacoes: %d\n", comparacoes_binaria);
        printf("   Tempo: %.6f segundos\n", tempoVetorBin);
    }
    
    printf("\n--- ANALISE DE DESEMPENHO ---\n");
    printf("Eficiencia das buscas (menor numero de comparacoes = mais eficiente):\n");
    
    if (ordenado && encontradoVetor && encontradoBinario) {
        printf("Busca Binaria: %d comparacoes\n", comparacoes_binaria);
        printf("Busca Sequencial Vetor: %d comparacoes\n", comparacoes_vetor);
        printf("Busca Sequencial Lista: %d comparacoes\n", comparacoes_lista);
        
        printf("\nConclusao: ");
        if (comparacoes_binaria < comparacoes_vetor && comparacoes_binaria < comparacoes_lista) {
            printf("Busca binaria e a mais eficiente para dados ordenados!\n");
        } else if (comparacoes_vetor < comparacoes_lista) {
            printf("Vetor e mais eficiente que lista encadeada para esta busca.\n");
        } else {
            printf("Lista encadeada e mais eficiente que vetor para esta busca.\n");
        }
    }
}

// ============================================
// FUNÇÃO PRINCIPAL
// ============================================

int main() {
    MochilaVetor mochilaVetor;
    MochilaLista mochilaLista;
    
    // Inicializar ambas as estruturas
    inicializarVetor(&mochilaVetor);
    inicializarLista(&mochilaLista);
    
    int opcaoPrincipal, opcaoSecundaria;
    int executando = 1;
    
    // Inserir alguns itens iniciais para testes
    Item itensTeste[] = {
        {"AK-47", "arma", 1},
        {"Bandagem", "cura", 5},
        {"M4A1", "arma", 1},
        {"Kit Medico", "cura", 2},
        {"Munição 5.56", "municao", 120},
        {"Faca", "arma", 1},
        {"Analgesico", "cura", 3},
        {"Mochila", "ferramenta", 1},
        {"Binoculos", "ferramenta", 1},
        {"Radio", "ferramenta", 1}
    };
    
    int numTestes = 5; // Inserir apenas 5 itens para teste
    
    printf("\nInserindo %d itens de teste em ambas as estruturas...\n", numTestes);
    for (int i = 0; i < numTestes; i++) {
        inserirItemVetor(&mochilaVetor, itensTeste[i]);
        inserirItemLista(&mochilaLista, itensTeste[i]);
    }
    
    while (executando) {
        exibirMenuPrincipal();
        scanf("%d", &opcaoPrincipal);
        
        switch (opcaoPrincipal) {
            case 1: // Trabalhar com Mochila Vetor
                do {
                    exibirMenuVetor();
                    scanf("%d", &opcaoSecundaria);
                    
                    switch (opcaoSecundaria) {
                        case 1: { // Inserir item
                            Item novoItem = criarItem();
                            inserirItemVetor(&mochilaVetor, novoItem);
                            break;
                        }
                        case 2: { // Remover item
                            char nome[30];
                            printf("Nome do item a remover: ");
                            scanf("%s", nome);
                            removerItemVetor(&mochilaVetor, nome);
                            break;
                        }
                        case 3: // Listar itens
                            listarItensVetor(&mochilaVetor);
                            break;
                        case 4: { // Busca sequencial
                            char nome[30];
                            Item resultado;
                            printf("Nome do item a buscar: ");
                            scanf("%s", nome);
                            
                            if (buscarSequencialVetor(&mochilaVetor, nome, &resultado)) {
                                printf("\nItem encontrado!\n");
                                printf("Nome: %s\n", resultado.nome);
                                printf("Tipo: %s\n", resultado.tipo);
                                printf("Quantidade: %d\n", resultado.quantidade);
                                printf("Comparacoes realizadas: %d\n", comparacoes_vetor);
                            } else {
                                printf("Item não encontrado. Comparacoes: %d\n", comparacoes_vetor);
                            }
                            break;
                        }
                        case 5: // Ordenar vetor
                            ordenarVetor(&mochilaVetor);
                            break;
                        case 6: { // Busca binária
                            char nome[30];
                            Item resultado;
                            printf("Nome do item a buscar: ");
                            scanf("%s", nome);
                            
                            // Verificar se o vetor está ordenado
                            int ordenado = 1;
                            for (int i = 0; i < mochilaVetor.tamanho - 1; i++) {
                                if (strcmp(mochilaVetor.itens[i].nome, mochilaVetor.itens[i+1].nome) > 0) {
                                    ordenado = 0;
                                    break;
                                }
                            }
                            
                            if (!ordenado) {
                                printf("ERRO: Vetor não está ordenado! Use a opcao 5 primeiro.\n");
                            } else if (buscarBinariaVetor(&mochilaVetor, nome, &resultado)) {
                                printf("\nItem encontrado com busca binaria!\n");
                                printf("Nome: %s\n", resultado.nome);
                                printf("Tipo: %s\n", resultado.tipo);
                                printf("Quantidade: %d\n", resultado.quantidade);
                                printf("Comparacoes realizadas: %d\n", comparacoes_binaria);
                            } else {
                                printf("Item não encontrado. Comparacoes: %d\n", comparacoes_binaria);
                            }
                            break;
                        }
                        case 7: // Voltar
                            printf("Voltando ao menu principal...\n");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                    }
                } while (opcaoSecundaria != 7);
                break;
                
            case 2: // Trabalhar com Mochila Lista Encadeada
                do {
                    exibirMenuLista();
                    scanf("%d", &opcaoSecundaria);
                    
                    switch (opcaoSecundaria) {
                        case 1: { // Inserir item
                            Item novoItem = criarItem();
                            inserirItemLista(&mochilaLista, novoItem);
                            break;
                        }
                        case 2: { // Remover item
                            char nome[30];
                            printf("Nome do item a remover: ");
                            scanf("%s", nome);
                            removerItemLista(&mochilaLista, nome);
                            break;
                        }
                        case 3: // Listar itens
                            listarItensLista(&mochilaLista);
                            break;
                        case 4: { // Busca sequencial
                            char nome[30];
                            Item resultado;
                            printf("Nome do item a buscar: ");
                            scanf("%s", nome);
                            
                            if (buscarSequencialLista(&mochilaLista, nome, &resultado)) {
                                printf("\nItem encontrado!\n");
                                printf("Nome: %s\n", resultado.nome);
                                printf("Tipo: %s\n", resultado.tipo);
                                printf("Quantidade: %d\n", resultado.quantidade);
                                printf("Comparacoes realizadas: %d\n", comparacoes_lista);
                            } else {
                                printf("Item não encontrado. Comparacoes: %d\n", comparacoes_lista);
                            }
                            break;
                        }
                        case 5: // Voltar
                            printf("Voltando ao menu principal...\n");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                    }
                } while (opcaoSecundaria != 5);
                break;
                
            case 3: // Comparar desempenho
                testarDesempenho(&mochilaVetor, &mochilaLista);
                break;
                
            case 4: // Sair
                printf("\nEncerrando programa...\n");
                liberarLista(&mochilaLista);
                printf("Memoria liberada. Programa finalizado com sucesso!\n");
                executando = 0;
                break;
                
            default:
                printf("Opcao invalida! Escolha uma opcao de 1 a 4.\n");
        }
    }
    
    return 0;
}