/**
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SMA0180 - Matemática Discreta I - Trabalho 07
 *         Este programa calcula a^e (mod d), onde a, e, d são unsigned int
 *         (32 bits), a < d e d,e < 256^2 (16 bits).
 *         
 * @date   2021-11-29
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define COMENTARIOS 1 // 1 para imprimir comentários, 0 para não imprimir.

int main(int argc, char **argv)
{
    // Formato: a^e (mod d)
    unsigned int a = atoi(argv[1]);
    unsigned int e = atoi(argv[2]);
    unsigned int d = atoi(argv[3]);

    // Aqui se inicia o cálculo.
    unsigned int base = a % d;
    unsigned int res = 1;

    if (COMENTARIOS)
    {
        printf("===== Calculando: %u^%u (mod %u) =====\n\n", a, e, d);
        printf("Resultado parcial: %u\n", res);
        printf("Potência: %u (mod %u) = %u\n\n", a, d, base);
    }

    for (int i = e; i > 0; i /= 2)
    {
        if (i % 2) // O bit menos significativo é 1.
        {
            // Reduzir (mod d) sempre que fizer um produto.
            res = (res * base) % d; // Atualiza o resultado.
        }

        // Reduzir (mod d) sempre que fizer um produto.
        base = (base * base) % d; // Atualiza a base.

        if (COMENTARIOS)
        {
            printf("Resultado parcial: %u\n", res);
            printf("Potência atualizada: %u\n\n", base);
        }
    }

    printf("Resultado final: %u∧%u (mod %u) = %u\n", a, e, d, res);

    return 0;
}