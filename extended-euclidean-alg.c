/**
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SMA0180 - Matemática Discreta I - Trabalho 05
 *         Este programa, dados d e a inteiros (passados pela linha de comando),
 *         calcula o inverso de a em Z_d ou avisa que a não é invertível em Z_d.
 *         
 * @date   2021-10-25
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define COMENTARIOS 1 // 1 para imprimir comentários, 0 para não imprimir.

int euclides_estendido(int a, int d, int* i, int* j);
int calcular_inverso(int a, int d);


int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("A linha de comando deve conter os seguintes parametros:\n");
        printf("<nome_do_executavel> <d> <a>, com d e a inteiros.\n");
        return 1;
    }

    int d = atoi(argv[1]);
    int a = atoi(argv[2]);

    // O programa trabalha com valores que satisfazem a < d;
    // Caso a > d, podemos tratar esse valor:
    if (a > d) a = a % d;

    int inverso = calcular_inverso(a, d);

    if (inverso == -1) printf("%d não é invertível em Z_%d\n\n", a, d);
    else printf("O inverso de %d em Z_%d é %d\n\n", a, d, inverso);
    
    return 0;
}

/**
 * @brief Calcula o inverso de a em Z_d usando o Algoritmo de Euclides Estendido.
 * Caso a não seja invertível em Z_d, a função retorna -1.
 * 
 * @param a inteiro não negativo, a >= 0;
 * @param d inteiro positivo, d > a;
 * @return inverso de a em Z_d ou -1, caso a não seja invertível em Z_d (int).
 */
int calcular_inverso(int a, int d)
{
    int i, j;
    int mcd = euclides_estendido(a, d, &i, &j);
    
    if (COMENTARIOS)
    {
        printf("Aplicando o Algoritmo de Euclides estendido para a = %d e d = %d, obtemos:\n\n", a, d);
        printf("\tMCD(%d,%d) = %d\n", a, d, mcd);
        printf("\ti = %d; j = %d\n\n", i, j);
        printf("\tOu seja, temos:\n\ti*a + j*d = MCD(a,d)\n");
        printf("\t%d*%d + (%d)*%d = %d\n\n", i, a, j, d, i*a + j*d);
    }

    // O retorno -1 indica que a não é invertível em Z_d e occore
    // quando existe um MCD(a,d) que não seja 1 (ou seja, r > 1).
    if (mcd > 1) return -1;

    // Caso i seja um número negativo, trata esse valor para que fiquemos com
    // um i equivalente em Z_d, tal que 0 < i < d. Esse valor poder ser obtido
    // pela adição de d ao valor negativo de i, visto que d = 0 no sentido de
    // Z_d (d é elemento neutro da adição).
    if (i < 0) i += d;

    return i;
}

/**
 * @brief Algoritmo de Euclides Estendido: recebe dois inteiros a e d, sendo
 * d > a e a >= 0, e calcula seu MCD (Máximo Divisor Comum) e os coeficientes
 * i e j tais que: i*a + j*d = MCD(a,d).
 * 
 * @param a inteiro não negativo, a >= 0;
 * @param d inteiro positivo, d > a;
 * @param i endereço onde será armazenado o coeficiente i de a na identidade de Bézout;
 * @param j endereço onde será armazenado o coeficiente j de d na identidade de Bézout;
 * @return máximo divisor comum entre a e d (int). 
 */
int euclides_estendido(int a, int d, int* i, int* j)
{
    // Caso base.
    if (d == 0)
    {
        *i = 1;
        *j = 0;
        return a;
    }
  
    int i_temp, j_temp; // Armazena os resultados da chamada recursiva.
    int mcd = euclides_estendido(d, a % d, &i_temp, &j_temp);
  
    // Atualiza i e j utilizando os resultados da chamada recursiva.
    *i = j_temp;
    *j = i_temp - (a / d) * j_temp;
  
    return mcd;
}