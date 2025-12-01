#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ============================================
// DEFINIÇÃO DA STRUCT E VARIÁVEIS GLOBAIS
// ============================================

// Struct para representar um componente da torre
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // 1-10, onde 10 é a maior prioridade
} Componente;

// Variáveis globais para contagem de comparações
int comparacoes_bubble = 0;
int comparacoes_insertion = 0;
int comparacoes_selection = 0;
int comparacoes_busca = 0;

// ============================================
// FUNÇÕES DE ENTRADA E EXIBIÇÃO
// ============================================

// Limpa o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Cadastra componentes da torre
int cadastrarComponentes(Componente componentes[], int maxComponentes) {
    int quantidade;
    
    printf("\n=== CADASTRO DE COMPONENTES PARA A TORRE DE FUGA ===\n");
    printf("Quantos componentes deseja cadastrar? (max %d): ", maxComponentes);
    scanf("%d", &quantidade);
    limparBuffer();
    
    if (quantidade > maxComponentes || quantidade <= 0) {
        printf("Quantidade invalida! Cadastrando %d componentes.\n", maxComponentes);
        quantidade = maxComponentes;
    }
    
    printf("\nInstrucoes:\n");
    printf("- Prioridade: 1 (baixa) a 10 (critica)\n");
    printf("- Tipos sugeridos: controle, suporte, propulsao, energia, comunicacao\n\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("=== COMPONENTE %d/%d ===\n", i + 1, quantidade);
        
        printf("Nome do componente (ex: 'chip central', 'tanque combustivel'): ");
        fgets(componentes[i].nome, 30, stdin);
        componentes[i].nome[strcspn(componentes[i].nome, "\n")] = '\0';
        
        printf("Tipo do componente: ");
        fgets(componentes[i].tipo, 20, stdin);
        componentes[i].tipo[strcspn(componentes[i].tipo, "\n")] = '\0';
        
        printf("Prioridade (1-10): ");
        scanf("%d", &componentes[i].prioridade);
        limparBuffer();
        
        // Valida a prioridade
        if (componentes[i].prioridade < 1) {
            componentes[i].prioridade = 1;
        } else if (componentes[i].prioridade > 10) {
            componentes[i].prioridade = 10;
        }
        
        printf("Componente '%s' cadastrado com sucesso!\n\n", componentes[i].nome);
    }
    
    return quantidade;
}

// Exibe todos os componentes
void mostrarComponentes(Componente componentes[], int quantidade, const char* titulo) {
    if (quantidade == 0) {
        printf("Nenhum componente cadastrado!\n");
        return;
    }
    
    printf("\n=== %s (%d componentes) ===\n", titulo, quantidade);
    printf("==================================================================\n");
    printf("%-3s %-30s %-20s %-10s\n", "#", "NOME", "TIPO", "PRIORIDADE");
    printf("==================================================================\n");
    
    for (int i = 0; i < quantidade; i++) {
        // Destaca componentes de alta prioridade
        if (componentes[i].prioridade >= 8) {
            printf("🔥 ");
        } else if (componentes[i].prioridade >= 5) {
            printf("⚡ ");
        } else {
            printf("   ");
        }
        
        printf("%-30s %-20s %-10d\n", 
               componentes[i].nome, 
               componentes[i].tipo, 
               componentes[i].prioridade);
    }
    printf("==================================================================\n");
}

// ============================================
// ALGORITMOS DE ORDENAÇÃO
// ============================================

// Bubble Sort - Ordena por nome (crescente)
void bubbleSortPorNome(Componente componentes[], int quantidade) {
    comparacoes_bubble = 0;
    
    if (quantidade <= 1) return;
    
    printf("\n⚙️  Iniciando Bubble Sort (ordenacao por nome)...\n");
    
    int trocou;
    for (int i = 0; i < quantidade - 1; i++) {
        trocou = 0;
        for (int j = 0; j < quantidade - i - 1; j++) {
            comparacoes_bubble++;
            
            // Compara os nomes
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                // Troca os componentes
                Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
                trocou = 1;
            }
        }
        
        // Se não houve trocas, o vetor já está ordenado
        if (!trocou) break;
    }
    
    printf("✅ Bubble Sort concluido!\n");
    printf("   Comparacoes realizadas: %d\n", comparacoes_bubble);
}

// Insertion Sort - Ordena por tipo (crescente)
void insertionSortPorTipo(Componente componentes[], int quantidade) {
    comparacoes_insertion = 0;
    
    if (quantidade <= 1) return;
    
    printf("\n⚙️  Iniciando Insertion Sort (ordenacao por tipo)...\n");
    
    for (int i = 1; i < quantidade; i++) {
        Componente chave = componentes[i];
        int j = i - 1;
        
        // Move elementos maiores que a chave para frente
        while (j >= 0) {
            comparacoes_insertion++;
            if (strcmp(componentes[j].tipo, chave.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                j--;
            } else {
                break;
            }
        }
        componentes[j + 1] = chave;
    }
    
    printf("✅ Insertion Sort concluido!\n");
    printf("   Comparacoes realizadas: %d\n", comparacoes_insertion);
}

// Selection Sort - Ordena por prioridade (decrescente - maior prioridade primeiro)
void selectionSortPorPrioridade(Componente componentes[], int quantidade) {
    comparacoes_selection = 0;
    
    if (quantidade <= 1) return;
    
    printf("\n⚙️  Iniciando Selection Sort (ordenacao por prioridade)...\n");
    
    for (int i = 0; i < quantidade - 1; i++) {
        // Encontra o componente com maior prioridade
        int indice_maior = i;
        for (int j = i + 1; j < quantidade; j++) {
            comparacoes_selection++;
            
            // Ordena por prioridade decrescente
            if (componentes[j].prioridade > componentes[indice_maior].prioridade) {
                indice_maior = j;
            }
            // Se prioridades iguais, ordena por nome
            else if (componentes[j].prioridade == componentes[indice_maior].prioridade) {
                comparacoes_selection++;
                if (strcmp(componentes[j].nome, componentes[indice_maior].nome) < 0) {
                    indice_maior = j;
                }
            }
        }
        
        // Troca o componente atual pelo de maior prioridade
        if (indice_maior != i) {
            Componente temp = componentes[i];
            componentes[i] = componentes[indice_maior];
            componentes[indice_maior] = temp;
        }
    }
    
    printf("✅ Selection Sort concluido!\n");
    printf("   Comparacoes realizadas: %d\n", comparacoes_selection);
}

// ============================================
// BUSCA BINÁRIA
// ============================================

// Busca binária por nome (requer vetor ordenado por nome)
int buscaBinariaPorNome(Componente componentes[], int quantidade, const char* nome) {
    comparacoes_busca = 0;
    
    printf("\n🔍 Iniciando Busca Binaria por '%s'...\n", nome);
    
    int inicio = 0;
    int fim = quantidade - 1;
    
    while (inicio <= fim) {
        comparacoes_busca++;
        int meio = (inicio + fim) / 2;
        
        int comparacao = strcmp(componentes[meio].nome, nome);
        
        if (comparacao == 0) {
            printf("✅ Componente encontrado na posicao %d!\n", meio + 1);
            printf("   Nome: %s\n", componentes[meio].nome);
            printf("   Tipo: %s\n", componentes[meio].tipo);
            printf("   Prioridade: %d\n", componentes[meio].prioridade);
            printf("   Comparacoes realizadas: %d\n", comparacoes_busca);
            return meio; // Retorna o índice do componente
        }
        
        if (comparacao < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    printf("❌ Componente '%s' nao encontrado.\n", nome);
    printf("   Comparacoes realizadas: %d\n", comparacoes_busca);
    return -1; // Componente não encontrado
}

// ============================================
// MEDIÇÃO DE DESEMPENHO
// ============================================

// Função genérica para medir tempo de execução
void medirTempo(void (*algoritmo)(Componente[], int), Componente componentes[], 
                int quantidade, const char* nomeAlgoritmo) {
    
    // Faz uma cópia dos componentes para não alterar o original
    Componente* copia = (Componente*)malloc(quantidade * sizeof(Componente));
    if (copia == NULL) {
        printf("Erro ao alocar memoria para teste!\n");
        return;
    }
    
    // Copia os componentes
    for (int i = 0; i < quantidade; i++) {
        copia[i] = componentes[i];
    }
    
    printf("\n⏱️  Medindo tempo do %s...\n", nomeAlgoritmo);
    
    // Mede o tempo de execução
    clock_t inicio = clock();
    algoritmo(copia, quantidade);
    clock_t fim = clock();
    
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("   Tempo de execucao: %.6f segundos\n", tempo);
    
    // Libera a memória da cópia
    free(copia);
}

// Compara todos os algoritmos de ordenação
void compararAlgoritmos(Componente componentes[], int quantidade) {
    if (quantidade == 0) {
        printf("Nenhum componente para comparar!\n");
        return;
    }
    
    printf("\n📊 ===== COMPARACAO DE ALGORITMOS =====\n");
    printf("Quantidade de componentes: %d\n\n", quantidade);
    
    // Mede tempo de cada algoritmo
    medirTempo(bubbleSortPorNome, componentes, quantidade, "Bubble Sort (nome)");
    medirTempo(insertionSortPorTipo, componentes, quantidade, "Insertion Sort (tipo)");
    medirTempo(selectionSortPorPrioridade, componentes, quantidade, "Selection Sort (prioridade)");
    
    printf("\n📈 RESUMO DE COMPARACOES:\n");
    printf("   Bubble Sort:      %d comparacoes\n", comparacoes_bubble);
    printf("   Insertion Sort:   %d comparacoes\n", comparacoes_insertion);
    printf("   Selection Sort:   %d comparacoes\n", comparacoes_selection);
    
    printf("\n💡 DICAS ESTRATEGICAS:\n");
    printf("• Bubble Sort: Melhor para listas quase ordenadas\n");
    printf("• Insertion Sort: Eficiente para listas pequenas\n");
    printf("• Selection Sort: Bom quando trocas sao custosas\n");
    printf("• Busca Binaria: So funciona apos ordenacao por nome\n");
}

// ============================================
// MONTAGEM FINAL DA TORRE
// ============================================

// Simula a montagem da torre baseada na ordenação escolhida
void montarTorre(Componente componentes[], int quantidade, int criterio) {
    if (quantidade == 0) {
        printf("Nenhum componente para montar a torre!\n");
        return;
    }
    
    printf("\n🏗️  ===== INICIANDO MONTAGEM DA TORRE DE FUGA =====\n");
    
    // Faz uma cópia para ordenar
    Componente* copia = (Componente*)malloc(quantidade * sizeof(Componente));
    for (int i = 0; i < quantidade; i++) {
        copia[i] = componentes[i];
    }
    
    // Ordena conforme o critério escolhido
    switch (criterio) {
        case 1: // Ordenar por nome
            bubbleSortPorNome(copia, quantidade);
            printf("\nESTRATEGIA: Organizacao alfabetica\n");
            break;
        case 2: // Ordenar por tipo
            insertionSortPorTipo(copia, quantidade);
            printf("\nESTRATEGIA: Agrupamento por tipo\n");
            break;
        case 3: // Ordenar por prioridade
            selectionSortPorPrioridade(copia, quantidade);
            printf("\nESTRATEGIA: Priorizacao de componentes criticos\n");
            break;
    }
    
    printf("\n🔧 SEQUENCIA DE MONTAGEM:\n");
    printf("============================================================\n");
    
    // Simula a montagem passo a passo
    for (int i = 0; i < quantidade; i++) {
        printf("PASSO %d/%d:\n", i + 1, quantidade);
        printf("   Componente: %s\n", copia[i].nome);
        printf("   Tipo: %s\n", copia[i].tipo);
        printf("   Prioridade: %d ", copia[i].prioridade);
        
        // Emojis baseados na prioridade
        if (copia[i].prioridade >= 9) {
            printf("🚨 CRITICO");
        } else if (copia[i].prioridade >= 7) {
            printf("⚠️  ALTA");
        } else if (copia[i].prioridade >= 5) {
            printf("⚡ MEDIA");
        } else {
            printf("📋 BAIXA");
        }
        
        // Pequena pausa simulada (apenas visual)
        if (i < quantidade - 1) {
            printf("\n   [Montando...]\n");
        }
        printf("\n");
    }
    
    printf("============================================================\n");
    printf("✅ TORRE MONTADA COM SUCESSO!\n");
    printf("   Tempo estimado de fuga: %d segundos\n", 30 + (quantidade * 2));
    printf("   Chance de sucesso: %d%%\n\n", 70 + (quantidade * 3));
    
    free(copia);
}

// ============================================
// MENU PRINCIPAL
// ============================================

void exibirMenu() {
    printf("\n🎮 ==== MISSÃO FINAL: TORRE DE FUGA ====\n");
    printf("⏰ Última safe zone se fechando...\n\n");
    
    printf("1. Cadastrar componentes da torre\n");
    printf("2. Mostrar componentes cadastrados\n");
    printf("3. Ordenar por nome (Bubble Sort)\n");
    printf("4. Ordenar por tipo (Insertion Sort)\n");
    printf("5. Ordenar por prioridade (Selection Sort)\n");
    printf("6. Buscar componente-chave (Busca Binaria)\n");
    printf("7. Comparar algoritmos de ordenacao\n");
    printf("8. Montar torre com estrategia escolhida\n");
    printf("9. Sair e escapar da ilha\n");
    printf("\nEscolha uma opcao: ");
}

// ============================================
// FUNÇÃO PRINCIPAL
// ============================================

int main() {
    const int MAX_COMPONENTES = 20;
    Componente componentes[MAX_COMPONENTES];
    int quantidade = 0;
    int opcao;
    int ordenado_por_nome = 0; // Flag para controle da busca binária
    
    // Componente-chave pré-definido (objetivo final)
    char componente_chave[] = "chip central";
    
    printf("🚨 ALERTA: ZONA DE PERIGO ATIVA! 🚨\n");
    printf("========================================\n");
    printf("OBJETIVO: Montar a torre de fuga antes que\n");
    printf("a última safe zone se feche completamente!\n");
    printf("Componente crítico necessário: '%s'\n", componente_chave);
    printf("========================================\n");
    
    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1: // Cadastrar componentes
                quantidade = cadastrarComponentes(componentes, MAX_COMPONENTES);
                ordenado_por_nome = 0; // Reset flag ao cadastrar novos
                break;
                
            case 2: // Mostrar componentes
                mostrarComponentes(componentes, quantidade, "COMPONENTES CADASTRADOS");
                break;
                
            case 3: // Bubble Sort por nome
                if (quantidade == 0) {
                    printf("⚠️  Nenhum componente para ordenar!\n");
                } else {
                    bubbleSortPorNome(componentes, quantidade);
                    mostrarComponentes(componentes, quantidade, "ORDENADO POR NOME");
                    ordenado_por_nome = 1; // Marca que está ordenado por nome
                }
                break;
                
            case 4: // Insertion Sort por tipo
                if (quantidade == 0) {
                    printf("⚠️  Nenhum componente para ordenar!\n");
                } else {
                    insertionSortPorTipo(componentes, quantidade);
                    mostrarComponentes(componentes, quantidade, "ORDENADO POR TIPO");
                }
                break;
                
            case 5: // Selection Sort por prioridade
                if (quantidade == 0) {
                    printf("⚠️  Nenhum componente para ordenar!\n");
                } else {
                    selectionSortPorPrioridade(componentes, quantidade);
                    mostrarComponentes(componentes, quantidade, "ORDENADO POR PRIORIDADE");
                }
                break;
                
            case 6: // Busca binária
                if (quantidade == 0) {
                    printf("⚠️  Nenhum componente para buscar!\n");
                } else if (!ordenado_por_nome) {
                    printf("❌ ERRO: Para usar busca binária, primeiro ordene por nome (opção 3)!\n");
                    printf("   Busca binária só funciona em vetores ordenados.\n");
                } else {
                    char nome_busca[30];
                    printf("Digite o nome do componente a buscar: ");
                    fgets(nome_busca, 30, stdin);
                    nome_busca[strcspn(nome_busca, "\n")] = '\0';
                    
                    int encontrado = buscaBinariaPorNome(componentes, quantidade, nome_busca);
                    
                    // Verifica se é o componente-chave
                    if (strcmp(nome_busca, componente_chave) == 0 && encontrado != -1) {
                        printf("\n🎉 COMPONENTE-CHAVE ENCONTRADO!\n");
                        printf("A torre pode ser ativada! Prepare-se para a fuga!\n");
                    }
                }
                break;
                
            case 7: // Comparar algoritmos
                compararAlgoritmos(componentes, quantidade);
                break;
                
            case 8: // Montar torre
                if (quantidade == 0) {
                    printf("⚠️  Nenhum componente para montar a torre!\n");
                } else {
                    printf("\n🏗️  ESCOLHA A ESTRATEGIA DE MONTAGEM:\n");
                    printf("1. Ordem alfabetica (organizada)\n");
                    printf("2. Agrupamento por tipo (eficiente)\n");
                    printf("3. Por prioridade (sobrevivencia)\n");
                    printf("Escolha: ");
                    
                    int estrategia;
                    scanf("%d", &estrategia);
                    limparBuffer();
                    
                    if (estrategia >= 1 && estrategia <= 3) {
                        montarTorre(componentes, quantidade, estrategia);
                    } else {
                        printf("Estrategia invalida!\n");
                    }
                }
                break;
                
            case 9: // Sair
                printf("\n🚁 HELICOPTERO DE RESGATE A CAMINHO!\n");
                printf("Tempo restante: 15 segundos\n");
                
                // Verifica se o componente-chave foi cadastrado
                int tem_chip = 0;
                for (int i = 0; i < quantidade; i++) {
                    if (strcmp(componentes[i].nome, componente_chave) == 0) {
                        tem_chip = 1;
                        break;
                    }
                }
                
                if (tem_chip) {
                    printf("✅ CHIP CENTRAL CONECTADO!\n");
                    printf("🎉 FUGA BEM-SUCEDIDA! VOCE SOBREVIVEU!\n");
                } else {
                    printf("❌ CHIP CENTRAL NAO ENCONTRADO!\n");
                    printf("💀 MISSÃO FALHADA... A ZONA TE ALCANCOU.\n");
                }
                
                printf("\n=== ESTATISTICAS FINAIS ===\n");
                printf("Componentes coletados: %d\n", quantidade);
                printf("Tempo total de operacao: %.2f segundos\n", 
                       (double)clock() / CLOCKS_PER_SEC);
                printf("================================\n");
                break;
                
            default:
                printf("Opcao invalida! Escolha uma opcao de 1 a 9.\n");
        }
        
    } while (opcao != 9);
    
    return 0;
}