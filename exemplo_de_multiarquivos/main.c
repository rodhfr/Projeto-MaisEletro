#include <stdio.h>
#include "funcoes.h"

int main() {
    saudacao(); // Chama a função de saudação

    int a = 5, b = 10;
    int resultado = soma(a, b); // Chama a função soma

    printf("A soma de %d e %d é: %d\n", a, b, resultado);
    
    return 0;
}
