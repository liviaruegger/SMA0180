/**
 * @author Ana Lívia Ruegger Saldanha (N.USP 8586691)
 * @brief  SMA0180 - Matemática Discreta I - Trabalho 08 (Parte 2)
 *         RSA com chave de 16 bits.
 *         
 * @date   2021-12-10
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define CODIFICAR   'c'
#define DECODIFICAR 'd'

#define COMENTARIOS 1 // 1 para imprimir comentários, 0 para não imprimir.

int euclides_estendido(int a, int d, int* i, int* j);
unsigned int calcular_resto(unsigned int mensagem, unsigned short d, unsigned int e);
unsigned int codificar(unsigned int mensagem, unsigned short n, unsigned int e);
unsigned int decodificar(unsigned int n, unsigned int e, unsigned int mensagem, int phi);
void erro();

int main(int argc, char **argv)
{
    // Linha de comando: ./prog <modo> <mensagem>
    if (argc != 3) erro();
    
    char modo = argv[1][0];
    unsigned int mensagem = atoi(argv[2]);
    if (modo != 'c' && modo != 'd') erro();
    
    // Segredos p,q > 100 escolhidos, tais que n = pq cabe em 16 bits:
    unsigned short p = 167; // 167 é um número primo maior que 100
    unsigned short q = 269; // 269 é um número primo maior que 100
    // Observação: n = pq = 44923  ->  n < 2^16 (cabe em 16 bits)

    // Expoente de codificação escolhido:
    unsigned int e = 23;

    // Justificativa: a escolha do expoente deve ser tal que e seja invertível
    // em Z_phi, ou seja, que MCD(e,phi) = 1. Escolhendo um número primo,
    // garantimos que ele sempre será invertível em Z_phi (com phi != e).

    if(COMENTARIOS)
    {
        printf("Esta codificação foi realizada utilizando os seguintes valores:\n\n");

        printf("\tSegredos p,q > 100 escolhidos, tais que n = pq cabe em 16 bits:\n");
        printf("\t-- p = %u\n", p);
        printf("\t-- q = %u\n\n", q);

        printf("\tExpoente de codificação escolhido:\n");
        printf("\t-- e = %d\n\n", e);
    }
    
    if (modo == CODIFICAR)
    {
        printf("CODIFICANDO...\n\n");

        unsigned int codificacao = codificar(mensagem, p * q, e);
        printf("A codificação de %u é %u.\n\n", mensagem, codificacao);
    }
    else if (modo == DECODIFICAR)
    {
        printf("DECODIFICANDO...\n\n");

        unsigned int decodificacao = decodificar(p * q, e, mensagem, (p - 1) * (q - 1));
        printf("A decodificação de %u é %u.\n\n", mensagem, decodificacao);
    }
    
    return 0;
}

/**
 * @brief (Função desenvolvida no Trabalho 5) Algoritmo de Euclides Estendido:
 * recebe dois inteiros a e d, sendo d > a e a >= 0, e calcula seu MCD (Máximo
 * Divisor Comum) e os coeficientes i e j tais que: i*a + j*d = MCD(a,d).
 * 
 * Neste programa, o que nos interessa é o valor que será armazenado em i,
 * que usaremos na função de decodificação.
 * 
 * @param a inteiro não negativo, a >= 0;
 * @param d inteiro positivo, d > a;
 * @param i endereço para armazenar o coeficiente i de a na identidade de Bézout;
 * @param j endereço para armazenar o coeficiente j de d na identidade de Bézout;
 * @return máximo divisor comum entre a e d (int). 
 */
int euclides_estendido(int a, int d, int* i, int* j)
{
    // Caso base.
    if (d == 0)
    {
        *i = 1; // Esta variável i vai armazenar o valor que buscamos para usar
        *j = 0;                                            // na decodificação.
        return a;
    }
  
    int i_temp, j_temp; // Armazena os resultados da chamada recursiva.
    int mcd = euclides_estendido(d, a % d, &i_temp, &j_temp);
  
    // Atualiza i e j utilizando os resultados da chamada recursiva.
    *i = j_temp;
    *j = i_temp - (a / d) * j_temp;
  
    return mcd;
}

/**
 * @brief (Função desenvolvida no Trabalho 7) Calcula a^e (mod d), onde a, e, d
 * são unsigned int (32 bits), a < d e d,e < 256^2 (16 bits).
 * 
 * @param base número a descrito acima;
 * @param d divisor (número d descrito acima);
 * @param e expoente (número e descrito acima);
 * @return resto calculado (unsigned int). 
 */
unsigned int calcular_resto(unsigned int base, unsigned short d, unsigned int e)
{
    unsigned int res = 1;

    for (int i = e; i > 0; i /= 2)
    {
        if (i % 2) // O bit menos significativo é 1.
        {
            // Reduzir (mod d) sempre que fizer um produto.
            res = (res * base) % d; // Atualiza o resultado.
        }

        // Reduzir (mod d) sempre que fizer um produto.
        base = (base * base) % d; // Atualiza a base.
    }

    return res;
}

/**
 * @brief Usa a função calcula_resto para codificar a mensagem.
 * Observação: esta função existe apenas para melhorar a legibilidade do código,
 * poderíamos apenas ter usado a função calcular_resto.
 * 
 * @param mensagem mensagem a ser codificada;
 * @param n produto dos segredos (p * q);
 * @param e expoente de codificação escolhido;
 * @return mensagem codificada (unsigned int).
 */
unsigned int codificar(unsigned int mensagem, unsigned short n, unsigned int e)
{
    return calcular_resto(mensagem, n, e);
}

/**
 * @brief Decodifica, pelo algoritmo RSA, uma mensagem codificada. O expoente f
 * de decodificação é descoberto pelo Algoritmo de Euclides Estendido, de forma
 * que f = e^(-1) em Z_phi. A mensagem decodificada é c^f (mod n), em que c é a
 * mensagem codificada.
 * 
 * @param n produto dos segredos (p * q);
 * @param e expoente de codificação escolhido;
 * @param mensagem mensagem codificada;
 * @param phi phi(n) = (p - 1) * (q - 1);
 * @return mensagem decodificada (unsigned int).
 */
unsigned int decodificar(unsigned int n, unsigned int e, unsigned int mensagem, int phi)
{
    int i, j;
    euclides_estendido(e, phi, &i, &j);

    // Expoente de decodificação:
    int f = i;
    
    if (f < 0) f = f + phi;
    
    if (COMENTARIOS)
    {
        printf("\tValores usados na decodificação:\n");
        printf("\tphi = %d\n", phi);
        printf("\tf = %d\n\n", f);
    }

    return calcular_resto(mensagem, n, f);
}

/**
 * @brief Esta função tem como objetivo imprimir uma mensagem de erro na saída
 * padrão e encerrar o programa caso não tenha recebido os argumentos esperados
 * na linha de comando.
 * 
 */
void erro()
{
    printf("Atenção! Formato de entrada esperado na linha de comando:\n");
    printf("./prog <modo> <mensagem>\n\n");
    printf("Modos disponíveis:\n");
    printf("'c' para codificar mensagem\n");
    printf("'d' para decodificar mensagem\n");
    exit(0);
}