#include <stdbool.h>
#include <stdio.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} tdata, *pdata;

typedef struct {
    char *nome_ingrediente;
    float percentagem;
    bool alergico;
} tIngredientes, *pIngredientes;

typedef struct {
    char *nome_produtos;
    int num_em_stock;
    pdata data_criacao;
    float preco;
    pIngredientes lista;
} tprodutos, *pprodutos;

int main() {
    return 0;
}