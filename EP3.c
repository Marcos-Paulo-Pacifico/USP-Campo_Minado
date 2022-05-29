/***************************************************************/
/**                                                                                        **/
/**   Marcos Paulo Pacifico             11233817                 **/
/**   Exercício-Programa 03                                             **/
/**   Professor: Alair do Lago                                          **/
/**   Turma: (03)                                                                **/
/**                                                                                       **/
/**************************************************************/



#include<stdio.h>
#include<stdlib.h>
#define MAX 90

void GeraMatrizT (int A[MAX][MAX], int m, int n, int z, int s){                       /*Funcao que gera matriz inteira que sera responsaveis pelas posicoes das bombas*/

int i, j, q, numero;

srand(s);


for(q = 0; q<z; q++){

    numero = rand();                                      /*Geracao de casas aleatorias para as bombas*/
    i = numero % m + 1;
    j = (numero / m) % n + 1;

        while(A[i][j] == -1) {
            numero = rand();
            i = numero % m + 1;
            j = (numero / m) % n + 1;
        }
     A[i][j] = -1;
}


for(i = 1; i<=m; i++)
    for(j = 1; j<= n; j++)
            if(A[i][j] != -1){                                                /*Atribuicao de valores para o numero de bombas vizinhas as posicoes*/
                if(A[i-1][j-1] == -1) A[i][j] ++;
                if(A[i-1][j] == -1) A[i][j] ++;
                if(A[i-1][j+1] == -1) A[i][j] ++;
                if(A[i][j-1] == -1) A[i][j] ++;
                if(A[i][j+1] == -1) A[i][j] ++;
                if(A[i+1][j-1] == -1) A[i][j] ++;
                if(A[i+1][j] == -1) A[i][j] ++;
                if(A[i+1][j+1] == -1) A[i][j] ++;
            }

}

void GeraMatrizC(char C[MAX][MAX], int m, int n){                            /*Funcao que gera matriz char que sera responsavel pelo requisito visual*/
int i, j;

for(i = 0, j = 2; j<= n; j++)
   C[i][j] = '=';
for(i = 1, j = 0; i<= m; i++)
   C[i][j] = '|';
for(i = m +1, j = 2; j<= n; j++)
   C[i][j] = '=';
for(i = 1, j = n +1; i<= m; i++)
   C[i][j] = '|';

C[0][1] = '/';
C[m+1][1] = 92;
C[0][n+1] = 92;
C[m+1][n+1] = '/';

for(i = 1; i<=m; i++)
    for(j = 1; j<=n; j++)
        C[i][j] = '.';


}

void ImprimeMatriz (char A[MAX][MAX], int m, int n){                    /*Funcao que imprime a matriz visual com seus respectivos parametros*/

int i,j, S[MAX];

printf("   ");
for(j = 1; j  <= n; j++){
    S[j] = j;
    printf("%2d", S[j]);
}

printf("\n");
for(i = 0; i<=m+1; i++){
        if(i>0&&i<m+1)printf("%d", i);
    for(j = 0; j<=n+1; j++)
        printf("%2c", A[i][j]);
        if(i>0&&i<m+1)printf("%d", i);
        printf("\n");
}
printf("   ");
for(j = 1; j  <= m; j++){
    printf("%2d", S[j]);
}
printf("\n");
}

void AbreZeros(int T[MAX][MAX], char C[MAX][MAX], int i, int j, int m, int n){                  /*Funcao que abre as casas vizinhas aos zeros e as casas vizinhas as vizinhas...*/


if(i > 0&& j>0&&i<m+1&&j<n+1){
T[i][j] = 9;                                                                            /*Indicador de passagem da funcao abre zeros*/
if(T[i-1][j-1] == 0) {
    AbreZeros(T, C, i-1, j-1, m, n);
}else C[i-1][j-1] = T[i-1][j-1] + '0';

if(T[i-1][j] == 0) {
    AbreZeros(T, C, i-1, j, m, n);
}else C[i-1][j] = T[i-1][j] + '0';

if(T[i-1][j+1] == 0) {
    AbreZeros(T, C, i-1, j+1, m, n);
}else C[i-1][j+1] = T[i-1][j+1] + '0';

if(T[i][j-1] == 0) {
    AbreZeros(T, C, i, j-1, m, n);                                       /*Caso alguma casa vizinha ao zero for zero, ela chamara essa mesma funcao para a vizinha, e assim por diante*/
}else C[i][j-1] = T[i][j-1] + '0';                                            /*So ira parar de chamar essa funcao quando os zeros acabarem e entao ira retornando chamada por chamada ate a sua primeira recorrencia*/

if(T[i][j+1] == 0) {
    AbreZeros(T, C, i, j+1, m, n);
}else C[i][j+1] = T[i][j+1] + '0';

if(T[i+1][j-1] == 0) {
    AbreZeros(T, C, i+1, j-1, m, n);
}else C[i+1][j-1] = T[i+1][j-1] + '0';

if(T[i+1][j] == 0){
    AbreZeros(T, C, i+1, j, m, n);
}else C[i+1][j] = T[i+1][j] + '0';

if(T[i+1][j+1] == 0) {
    AbreZeros(T, C, i+1, j+1, m, n);
}else C[i+1][j+1] = T[i+1][j+1] + '0';                                         /*Caso nao for zero, a matriz visual 'abre'(Se torna o mesmo elemento da matriz inteira)*/
}

}

int Jogo(int T[MAX][MAX], char C[MAX][MAX], int m, int n, int z){    /*Funcao que faz as operacoes referentes ao jogo*/

int i, j, marcadas, livres;
char jogada;

livres  = m * n;
marcadas = 0;

while(livres > z) {                                                          /*O jogo continua ate que nao haja mais posicoes possiveis a serem abertas a nao ser bombas*/
printf("Proximo chute:");

fflush(stdin);                                                                   /*Tive que usar essa funcao antes desconhecida para limpar o buffer do teclado e ele recorrer ao scanf nas passagens subsequentes*/
scanf("%c", &jogada);

scanf("%d", &i);
scanf("%d", &j);

if(jogada == 'd'){
     if(C[i][j] == '.'||C[i][j] > '0'){                                       /*Laco que desmarca posicoes marcadas*/
        printf("Sem efeito!!!\n");
     }else{
     C[i][j] = '.';
     marcadas --;
     }
}

if (jogada == 'm'){
    if(C[i][j] == '*'||C[i][j] > '0'||marcadas >= z){         /*Laco que marca posicoes*/
        printf("Sem efeito!!!\n");
    }else {
        C[i][j] = '*';
        marcadas ++;
    }
}

if (jogada == 'a'){                                                  /*Laco que abre as posicoes da matriz visual*/
    if(C[i][j] != '*'&&C[i][j]<'0'){
        if(T[i][j] == -1){
            C[i][j] = '@';
            return 0;                                                   /*Se o jogador achar uma bomba, a funcao retorna 0*/
        }
        if(T[i][j] == 0) AbreZeros(T, C, i, j, m, n);     /*Caso seja zero, a funcao AbreZeros eh recorrida*/
        if(T[i][j] > 0)C[i][j] = T[i][j] + '0';                     /*Caso seja somente uma casa livre e nao nula, a matriz visual torna-se o numero da inteira de posicao equivalente*/
    }else printf("Sem efeito!!!\n");
}

for(i = 1; i<=m; i++)
    for(j = 1; j<=n; j++)                                           /*Laco que retira todos os indicadores de passagem da funcao AbreZeros*/
        if(T[i][j] == 9)
            C[i][j] = '0';

livres = 0;
for(i = 1; i<=m; i++)
    for(j = 1; j<=n; j++)
        if(C[i][j] == '.'|| C[i][j] == '*')                           /*Faz a contagem de casas livres*/
            livres ++;
printf("Por enquanto: %d/%d marcadas, %d livres\n", marcadas, z, livres);
ImprimeMatriz(C, m, n);                                                                                      /*Imprime as devidas informacoes e a matriz visual apos todas as operacoes anteriores*/
}
return 1;                                                              /*Caso o jogador tenha aberto o maior numero possiveis de casas sem achar bombas, o laco principal eh quebrado e a funcqao jogo retorna o valor 1*/

}

int main(){

int m, n, i, j, z, s, ganhou;
int T[MAX][MAX];
char C[MAX][MAX];                                                                                           /*Declaracao de variaveis e inicializacao de valores*/
ganhou = 0;

m = 91;
n = 91;

while(m > MAX){
    printf("De o numero de linhas do tabuleiro do jogo:");
    scanf("%d", &m);
     if(m>MAX)printf("Numero excede o limite de %d linhas!\n", MAX);
}

while(n>MAX){
    printf("De o numero de colunas do tabuleiro do jogo:");                                 /*So sao aceitos valores dentro do estabelecido*/
    scanf("%d", &n);
    if(n>MAX)printf("Numero excede o limite de %d colunas!!\n", MAX);
}

while(z>=m*n){
    printf("De o numero de minas:");
    scanf("%d", &z);
    if(z>=m*n)printf("Numero excede o limite de %d linhas!!!\n", (m*n-1));
}
printf("De a semente:");
scanf("%d", &s);

GeraMatrizT(T, m, n, z, s);
GeraMatrizC(C, m, n);
printf("Bem Vindo ao Campo Minado!\n");                                                    /*Primeiro gera ambas as matrizes e imprime a matriz visual pela primeira vez*/
ImprimeMatriz(C, m, n);

if(Jogo(T, C, m, n, z)){
    printf("VOCE GANHOU!");                                                                        /*Caso a funcao Jogo retorne 1, o jogador ganhou e eh impressa essa mensagem na tela*/
}else {
    printf("BOOM!!!!!! Voce encontrou uma bomba!!\n");
    for(i = 1; i<=m; i++)
        for(j = 1; j<=n; j++){
            if(T[i][j] == -1)C[i][j] = '@';
            if(T[i][j]>0)C[i][j] = T[i][j] + '0';                                                              /*Caso a funcao retorne 0, o jogador perdeu e entao eh impressa a matriz visual completamente revelada*/
            if(T[i][j]==9||T[i][j] == 0)C[i][j] = '0';
        }
 ImprimeMatriz(C, m, n);
 }
return 0;
}
