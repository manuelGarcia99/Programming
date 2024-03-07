/**
 * @autores:
 * Nome: Manuel Garcia                   Número de Aluno: a45500
 * Nome: Gabriel Maria                   Número de Aluno: a47922
 * Nome: Marco Tavares                   Número de Aluno: a49009
 **/ 

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define B 6
#define N 8
#define M 8

/**Representa uma coordenada*/
typedef struct
{
    int x;
    int y;
} Position;

/**Associa cada coordenada do barco com um estado**/
typedef struct
{
    int afloat;        //0 indica que está afundada, 1 indica que não
    Position pos;      //Coordenada
} StateCoord;

/**Representa um barco**/
typedef struct
{
    int afloat;        //Posições que ainda não foram afundadas
    int tSize;         //Tamanho do tipo do barco 
    StateCoord coord[5]; //O barco maior tem 5 coordenadas, usando o tSize garantimos que acedemos apenas às existentes
    char type;         //Caracter que representa o tipo do barco
} Boat;

/**Representa um tabuleiro**/
typedef struct
{
    int numBoatsAfloat; //Número de barcos não afundados
    int numBoats; //Número de barcos que foram colocados
    Boat boats[B]; //Array de barcos. Cada barco é do tipo Boat.
    char board[N][M]; //Array que contém a informação de cada posição do tabuleiro
} Board;


/**
 * NOTA IMPORTANTE: 
 * Não pode alterar nenhuma das assinaturas das funções abaixo. 
 * Este ficheiro tem de ser considerado em conjunção com o enunciado do TP2.
 **/


/**
 * Function: init_board
 * 
 * Inicializa um Board.
 * 
 * n: dimensão x do tabuleiro
 * m: dimensão y do tabuleiro
 * b: apontador para o Board que vai ser inicializado
 * 
 **/

 
void init_board(int n, int m, Board *b)
{
    b->numBoatsAfloat = 0;
    b->numBoats = 0;

    //Inicializa o array board
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        { 
            b->board[i][j] = ' ';
        }
    }
}

/**
 * Function: print_board
 * 
 * Mostra no ecrã o estado atual do tabuleiro.
 * Se a flag é 0 (zero) não mostra os barcos, se for 1, mostra. 
 * Quando a flag é 1, para indicar a posição de cada barco, é colocada em todas
 * as posições do barco a letra que representa o seu tipo.
 * 
 * n: número de linhas do tabuleiro
 * m: número de colunas do tabuleiro
 * board: estado do tabuleiro
 * flag: indicador do modo de visualização do tabuleiro -- se for 0 (zero) não 
 *       mostra os barcos; se for diferente de 0 (zero) mostra.
 */

void print_board(int n, int m, char board[n][m], int flag)
{
    printf("+");
    for (int j = 0; j < n; j++)
    {
        printf("---+");
    }
    printf("\n");

    for (int i = 0; i < m; i++)
    {
        printf("|");
        if (flag) //Mostra tudo
        {
            for (int j = 0; j < n; j++)
            {
                printf(" %c |", board[i][j]);
            }
            printf("\n");
        }
        else // Esconde os barcos
        {
            for(int j=0;j<n;j++)
            {
            	if(board[i][j]=='A'||board[i][j]=='*'||board[i][j]=='F')
            	{
            		printf(" %c |", board[i][j]);
            	}
            	else{
            		printf("   |");
            	}
            }	 	
            printf("\n");
            //Implementar
        }

        printf("+");
        for (int j = 0; j < n; j++)
        {
            printf("---+");
        }
        printf("\n");
    }
}


/** 
 * Function: typeToSize
 * 
 * Dado o tipo do barco devolve o seu tamanho.
 * 
 * type: tipo do barco ('P', 'N', 'C', ou 'S')
 * 
 * return
 *  -1 se o tipo de barco for inválido
 *  caso contrário, devolve o tamanho do barco
 **/
int typeToSize(char type)
{
	if(type=='P'){
		return 5;
	}
	else{
		if(type=='N'){
			return 4;
		}
		else{
			if(type=='C'){
				return 3;
			}
			else{
				if(type=='S'){
					return 2;
				}
				else{
					return -1;
				}
			}
		}
	}
    //Implementar

    return 0;
}

/**
 * Function: init_boat
 * 
 * Dado um apontador para um barco, o tipo, a posição inicial e a direcção, 
 * inicializa o barco com todas as sua posições, tamanho e tipo. 
 * Por exemplo, se o tipo do barco é 'C' (contratorpedeiro),
 * a posição inicial (1,1), e a direcção 'H', então o barco fica inicializado 
 * com os seguintes valores
 * 
 * afloat = 3;
 * tSize = 3;
 * coord = [(1,(1,1)),(1,(1,2)),(1,(1,3))]; Onde (s,(x,y)) representa um elemento do tipo StateCoord
 * type = 'C';
 * 
 * b: barco que vai ser inicializado
 * type: tipo do barco
 * xy: posição inicial do barco
 * dir: direcção do barco
 * 
 **/
void init_boat(Boat *b, char type, Position xy, char dir)
{

    //Implementar
    if(type=='P'){
    	b->afloat=typeToSize('P');
    	b->tSize=typeToSize('P');
    	b->type=type;
    	for(int j=0;j<b->tSize;j++){
   		b->coord[j].afloat=1;
   		if(dir=='H'){
   			if(j==0){
   				b->coord[j].pos.y=xy.y;
   				b->coord[j].pos.x=xy.x;
   			}
   			else{
   					b->coord[j].pos.y=b->coord[j-1].pos.y+1;
   				b->coord[j].pos.x=b->coord[j-1].pos.x;
   			}
   		}
   		if(dir=='V'){
   			if(j==0){
   				b->coord[j].pos.y=xy.y;
   				b->coord[j].pos.x=xy.x;
   			}
   			else{
   							b->coord[j].pos.x=b->coord[j-1].pos.x+1;
   				b->coord[j].pos.y=b->coord[j-1].pos.y;
   			}
   		}
    	}
    }
    if(type=='N'){
    	b->afloat=typeToSize('N');
    	b->tSize=typeToSize('N');
    	b->type=type;
    	for(int j=0;j<b->tSize;j++){
   		b->coord[j].afloat=1;
   		if(dir=='H'){
   			if(j==0){
   				b->coord[j].pos.y=xy.y;
   				b->coord[j].pos.x=xy.x;
   			}
   			else{
   					b->coord[j].pos.y=b->coord[j-1].pos.y+1;
   				b->coord[j].pos.x=b->coord[j-1].pos.x;
   			}
   		}
   		if(dir=='V'){
			if(j==0){
   				b->coord[j].pos.y=xy.y;
   				b->coord[j].pos.x=xy.x;
   			}
   			else{
   							b->coord[j].pos.x=b->coord[j-1].pos.x+1;
   				b->coord[j].pos.y=b->coord[j-1].pos.y;
   			}
   		}
    	}
    }
    if(type=='C'){
    	b->afloat=typeToSize('C');
    	b->tSize=typeToSize('C');
    	b->type=type;
    	for(int j=0;j<b->tSize;j++){
   		b->coord[j].afloat=1;
   		if(dir=='H'){
   			if(j==0){
   				b->coord[j].pos.y=xy.y;
   				b->coord[j].pos.x=xy.x;
   			}
   			else{
   				b->coord[j].pos.y=b->coord[j-1].pos.y+1;
   				b->coord[j].pos.x=b->coord[j-1].pos.x;
   			}
   		}
   		if(dir=='V'){
   			if(j==0){
   				b->coord[j].pos.y=xy.y;
   				b->coord[j].pos.x=xy.x;
   			}
   			else{
   							b->coord[j].pos.x=b->coord[j-1].pos.x+1;
   				b->coord[j].pos.y=b->coord[j-1].pos.y;
   			}
   		}
    	}
    }
    if(type=='S'){
    	b->afloat=typeToSize('S');
    	b->tSize=typeToSize('S');
    	b->type=type;
    	for(int j=0;j<b->tSize;j++){
   		b->coord[j].afloat=1;
   		if(dir=='H'){
   			if(j==0){
   				b->coord[j].pos.y=xy.y;
   				b->coord[j].pos.x=xy.x;
   			}
   			else{
   					b->coord[j].pos.y=b->coord[j-1].pos.y+1;
   				b->coord[j].pos.x=b->coord[j-1].pos.x;
   			}
   			
   		}
   		if(dir=='V'){
   			if(j==0){
   				b->coord[j].pos.y=xy.y;
   				b->coord[j].pos.x=xy.x;
   			}
   			else{
   					b->coord[j].pos.x=b->coord[j-1].pos.x+1;
   				b->coord[j].pos.y=b->coord[j-1].pos.y;
   			}
   		}
    	}
    }
   // printf("O tipo e %c a direcao e %c\n",type,dir);
    //printf("O afloat= %d o tsize= %d\n",b->afloat,b->tSize);
    for(int j=0;j<b->tSize;j++)
    {
    	//printf("As coordenadas sao x=%d e y=%d\n",b->coord[j].pos.x,b->coord[j].pos.y);
    }
    
}


/**
 * Function: check_free
 * 
 * Verifica se estão livres todas as posições que serão ocupadas por um 
 * barco no tabuleiro.
 * 
 * n: dimensão x do tabuleiro
 * m: dimensão y do tabuleiro
 * boat: barco a colocar no tabuleiro
 * board: estado atual do tabuleiro
 * 
 * returns:
 *  1 se todas as posições estão livres
 *  0 caso contrário
 * 
 **/
int check_free(int n, int m, Boat *boat, char board[n][m])
{
   //Implementar
	for(int j=0;j<boat->tSize;j++){
		if(board[boat->coord[j].pos.x][boat->coord[j].pos.y]!=' ' || boat->coord[j].pos.x >= N || boat->coord[j].pos.y >= M)
		{
			return 0;
		}
		
	}
	
   return 1;
}

/** 
 * Function: place_boat
 * 
 * Cria e coloca, se tal for possível, um barco no tabuleiro.
 * 
 * x1: coordenada x inicial do barco  
 * y1: coordenada y inicial do barco  
 * dir: dirrecção do barco ('H' ou 'V')
 * type: o tipo de barco 
 * board: estado atual do tabuleiro
 *
 * returns: 
 * 0 se o barco for colocado com sucesso.
 * -1 se alguma das posições já está ocupada.
 * -2 se as coordenadas forem inválidas.
 * -3 se a direcção for inválida.
 * -4 se o tipo de barco for inválido.
 **/
int place_boat(int x1, int y1, char dir, char type, Board *board)
{
    //Implementar
    	if(dir == 'H')
	{
		for(int j=0 ;j<typeToSize(type);j++){
			if(board->board[x1][y1+j]!=' ')
			{
				return -1;
			}
		}
	}
	else{
		if(dir == 'V')
			for(int j = 0 ; j<typeToSize(type); j++){
				if(board->board[x1+j][y1]!=' ')
				{
					return -1;
				}
			}
	}
	if(x1<0 || y1<0 || x1>=N || y1>=M || (dir == 'H' && y1> M - typeToSize(type)) || (dir == 'V' && x1 > M - typeToSize(type)))
	{
		return -2;
	}
    	
	if(dir!= 'H' && dir!= 'V'){
		return -3;
	}
	if(type!='P' && type!='N' && type != 'C' && type != 'S')
	{
		return -4;
	}
	int numero_de_casas;
	if(type=='P'){
		numero_de_casas=typeToSize('P');
	}
	else{
		if(type=='N')
		{
			numero_de_casas=typeToSize('N');
		}
		else{
			if(type=='C'){
				numero_de_casas=typeToSize('C');
			}
			else{
				if(type=='S')
				{
					numero_de_casas=typeToSize('S');
				}
			}
		}
	}
	board->numBoatsAfloat+=1;
	board->numBoats+=1;
	//boars->boats[0]
	int num_de_barco;
	if(type=='S'){
		if(board->boats[0].tSize==typeToSize('S')){
			num_de_barco=1;
			board->boats[num_de_barco].tSize=typeToSize('S');
			board->boats[num_de_barco].afloat=typeToSize('S');
			board->boats[num_de_barco].type='S';
		}
		else{
			num_de_barco=0;
			board->boats[num_de_barco].tSize=typeToSize('S');
			board->boats[num_de_barco].afloat=typeToSize('S');
			board->boats[num_de_barco].type='S';
		}
	}
	else{
		if(type=='C'){
			if(board->boats[2].tSize==typeToSize('C')){
				num_de_barco=3;
				board->boats[num_de_barco].tSize=typeToSize('C');
				board->boats[num_de_barco].afloat=typeToSize('C');
				board->boats[num_de_barco].type='C';
			}
			else{
				num_de_barco=2;
				board->boats[num_de_barco].tSize=typeToSize('C');
				board->boats[num_de_barco].afloat=typeToSize('C');
				board->boats[num_de_barco].type='C';
			}
		}
		else{
			if(type=='N'){
				num_de_barco=4;	
				board->boats[num_de_barco].tSize=typeToSize('N');
				board->boats[num_de_barco].afloat=typeToSize('N');
				board->boats[num_de_barco].type='N';
			}
			else{
				if(type=='P')
				{
					num_de_barco=5;	
					board->boats[num_de_barco].tSize=typeToSize('P');
					board->boats[num_de_barco].afloat=typeToSize('P');	
					board->boats[num_de_barco].type='P';
				}
			}
		}
		
	}
	
	for(int j=0;j<numero_de_casas;j++)
	{
		if(j==0)
		{
			board->boats[num_de_barco].coord[j].pos.x=x1;
			board->boats[num_de_barco].coord[j].pos.y=y1;
			board->boats[num_de_barco].coord[j].afloat=1;
		}
		else{
			if(dir=='H'){
				
				board->boats[num_de_barco].coord[j].pos.x=board->boats[num_de_barco].coord[j-1].pos.x;
				board->boats[num_de_barco].coord[j].pos.y=board->boats[num_de_barco].coord[j-1].pos.y+1;
				board->boats[num_de_barco].coord[j].afloat=1;
			}
			else{
				board->boats[num_de_barco].coord[j].pos.x=board->boats[num_de_barco].coord[j-1].pos.x+1;
				board->boats[num_de_barco].coord[j].pos.y=board->boats[num_de_barco].coord[j-1].pos.y;
				board->boats[num_de_barco].coord[j].afloat=1;
			}
		}
	}
	for(int j=0;j<numero_de_casas;j++)
	{
		board->board[board->boats[num_de_barco].coord[j].pos.x][board->boats[num_de_barco].coord[j].pos.y]=type;
	}
	
    return 0;
}
/**
* Function: mensagem_de_erro
*
* Mostra uma mensagem de erro se se enganar a submeter as coordenadas ou a indicar a direção
**/
void mensagem_de_erro(){
	printf("\nEnganou-se ao submeter as coordenadas ou a direcao lembre-se que a direcao so pode ser 'H' ou 'V' e que as coordenadas tem que ser exclusivamente numeros e nao podem sobrepor outros barcos ou tentar construir barcos que saiam para fora dos limites do tabuleiro\n");
}

/**
 * Function: check_sink
 * 
 * Verifica se ao atacar a posição (x,y) algum barco é afundado. 
 * 
 * x: coordenada x a atacar
 * y: coordenada y a atacar
 * board: estado atual do tabuleiro
 * 
 * returns:
 *   'F' se não for afundado nenhum barco.
 *   Se afundar um barco devolve a letra que representa o seu tipo: 'P', 'N', 'C' ou 'S' 
 *   'I' se a coordenada for inválida.
 * 
 **/
char check_sink(int x, int y, Board *board)
{

	if(x<0 || x>N-1 || y<0 || y>N-1){
		return 'I';
	}
	int num_de_asteriscos=0;
	for(int i=0;i<B;i++)
	{
		for(int j=0;j<board->boats[i].tSize;j++){
			if(x==board->boats[i].coord[j].pos.x && y==board->boats[i].coord[j].pos.y){
				for(int z=0;z<board->boats[i].tSize;z++)
				{
					if(board->board[board->boats[i].coord[z].pos.x][board->boats[i].coord[z].pos.y]=='*')
					{
						num_de_asteriscos++;
					}
				}
				if(num_de_asteriscos==board->boats[i].tSize){
					for(int z=0;z<board->boats[i].tSize;z++)
					{
						board->board[board->boats[i].coord[z].pos.x][board->boats[i].coord[z].pos.y]='A';
					
					}
				return board->boats[i].type;		
				}
			}
		}
	}

    //Implementar

    return 'F';
}
/**
*Function: afloat
* Reduz o numero de casas que estao ainda por afundar num dado barco
**/

void afloat(Board *board,char type, int x,int y){
	for(int i=0;i<B;i++){
		for(int j=0;j<typeToSize(type);j++){
				if((board->boats[i].type==type) && (board->boats[i].coord[j].pos.x==x) && (board->boats[i].coord[j].pos.y==y))
				{
					board->boats[i].afloat=board->boats[i].afloat-1;
					break;
				}
			}
	}
}

/**
 * Function: target
 * 
 * Ataca a coordenada (x,y) no tabuleiro.
 * Se a coordenada (x,y) é parte de um barco, então coloca um '*' nessa 
 * posição '*'; caso contrário coloca a letra 'F' nessa posição; caso afunde 
 * um barco coloca em todas as posições desse barco a letra 'A'.
 * 
 * x: coordenada x a atacar
 * y: coordenada y a atacar
 * board: estado atual do tabuleiro
 * 
 * returns:
 *   0 se a posicao já foi atacada anteriormente
 *   1 se acerta numa coordenada de um barco mas sem o afundar
 *   -1 se nao tiver sucesso
 *   -2 se a coordenada for inválida. 
 *   caso afunde um barco, devolve o número correspondente ao tamanho do barco 
 *   que afundou (valor de 2 a 5)
 * 
 **/
int target(int x, int y, Board *board)
{
	if(board->board[x][y]=='*' || board->board[x][y]=='F')
	{
		return 0;
	}
	if(board->board[x][y]=='S'||board->board[x][y]=='C'||board->board[x][y]=='N'||board->board[x][y]=='P')
	{
		if(board->board[x][y]!='A' || board->board[x][y]!='*'){
			afloat(board,board->board[x][y],x,y);
		}
		board->board[x][y]='*';
		
		if(check_sink(x,y,board)=='S')//&&&
		{
			return 2;
		}
		if(check_sink(x,y,board)=='C')
		{
			return 3;
		}
		if(check_sink(x,y,board)=='N')
		{
			return 4;
		}
		if(check_sink(x,y,board)=='P'){
			return 5;
		}
		return 1;
	}
	else{
		if(x<0||x>N-1||y<0||y>N-1)
		{
			return -2;
		}
		else{
			board->board[x][y]='F';
			return -1;
		}
	}
	
	

    //Implementar

    return -3;
}
/**function is_it_number 
*	Devolve 1 se houver na string algum caracter que nao se trate de um numero inteiro positivo
**/
int is_it_number(char* str){
	int i,flag=2;
	for(i=0;i<strlen(str);i++){
		if(*(str+i)<48 || *(str+i)>57){
			flag=1;
		}
	}
	
	return flag;

}

//int colocaNavio()
int main(void)
{
	
	//xy1.x=4;
	//xy1.y=1;
	char dir;
	char repetir;
	char nome1[50] , nome2[50];
	char coord1[10], coord2[10];
	int respostamenu, respostaajuda;


	while(respostamenu != 1  && respostamenu != 2)
	{
		printf("-----------------BATALHA NAVAL-----------------\n\tPrima '1' para iniciar o jogo.\n   Prima '2' se não souber as regras do jogo\n-----------------------------------------------\n");
		scanf("%d", &respostamenu);

		if(respostamenu == 1)
		{
			do{
				Boat boat1;
				Position xy1;
				int contratorpedeiros=2, submarinos=2 ,navios_de_tanques=1,portaavioes=1;
				printf("Indique o nome do jogador 1:");
				scanf(" %[^\n]s",nome1);
				printf("Indique o nome do jogador 2:");
				scanf(" %[^\n]s",nome2);


				Board brd;
				init_board(N, M, &brd);

				print_board(N, M, brd.board,1);
			
				do{
					do{
						printf("Indique as coordenadas do primeiro submarino %s, faltam por todos os barcos\n",nome1);
						printf("Coordenada x: ");
						scanf(" %s",coord1);
						printf("Coordenada y: ");
						scanf(" %s",coord2);
					}while(is_it_number(coord1)==1 || is_it_number(coord2)==1);
					xy1.x=atoi(coord1);
					xy1.y=atoi(coord2);
					do{
						printf("Indique a direcao 'H' para horizontal 'V' para vertical: ");
						scanf(" %c",&dir);
						if(dir!='H' && dir!='V')
						{
							mensagem_de_erro();
						}
					}while(dir!='H' && dir!='V');
					init_boat(&boat1,'S',xy1,dir);
					if(check_free(N,M,&boat1,brd.board)!=1){
						mensagem_de_erro();
					}
				}while(check_free(N,M,&boat1,brd.board)!=1 );
				place_boat(xy1.x,xy1.y,dir,'S',&brd);
				print_board(N, M, brd.board, 1);
				do{
					do{
						printf("Indique as coordenadas do segundo submarino %s, falta por este submarino 2 contratorpedeiros ,um navio de tanques e um porta-avioes\n",nome1);
						printf("Coordenada x: ");
						scanf(" %s",coord1);
						printf("Coordenada y: ");
						scanf(" %s",coord2);
					}while(is_it_number(coord1)==1 || is_it_number(coord2)==1);
					xy1.x=atoi(coord1);
					xy1.y=atoi(coord2);
					do{
					printf("Indique a direcao 'H' para horizontal 'V' para vertical: ");
					scanf(" %c",&dir);
						if(dir!='H' && dir!='V')
						{
							mensagem_de_erro();
						}
					}while(dir!='H' && dir!='V');
					init_boat(&boat1,'S',xy1,dir);
				if(check_free(N,M,&boat1,brd.board)!=1){
					mensagem_de_erro();
				}
				}while(check_free(N,M,&boat1,brd.board)!=1 );
				place_boat(xy1.x,xy1.y,dir,'S',&brd);
				print_board(N, M, brd.board, 1);
				do{
					do{
						printf("Indique as coordenadas do primeiro contratropedeiro %s, falta por 2 contratorpedeiros um navio de tanques e um porta-avioes\n",nome1);
						printf("Coordenada x: ");
						scanf(" %s",coord1);
						printf("Coordenada y: ");
						scanf(" %s",coord2);
					}while(is_it_number(coord1)==1 || is_it_number(coord2)==1);
					xy1.x=atoi(coord1);
					xy1.y=atoi(coord2);
					do{
					
						printf("Indique a direcao 'H' para horizontal 'V' para vertical: ");
						scanf(" %c",&dir);
						if(dir!='H' && dir!='V'){
							mensagem_de_erro();
						}
					}while(dir!='H' && dir!='V');
					init_boat(&boat1,'C',xy1,dir);
					if(check_free(N,M,&boat1,brd.board)!=1){
						mensagem_de_erro();
					}
				}while(check_free(N,M,&boat1,brd.board)!=1 );
				place_boat(xy1.x,xy1.y,dir,'C',&brd);
				print_board(N, M, brd.board, 1);
				do{
					do{
						printf("Indique as coordenadas do segundo contratorpedeiro %s, falta por este contratorpedeiro ,um navio de tanques e um porta avioes \n",nome1);
						printf("Coordenada x: ");
						scanf(" %s",coord1);
						printf("Coordenada y: ");
						scanf(" %s",coord2);
					}while(is_it_number(coord1)==1 || is_it_number(coord2)==1);
					xy1.x=atoi(coord1);
					xy1.y=atoi(coord2);
					do{
						printf("Indique a direcao 'H' para horizontal 'V' para vertical: ");
						scanf(" %c",&dir);
						if(dir!='H' && dir!='V'){
							mensagem_de_erro();
						}
					}while(dir!='H' && dir!='V');
					init_boat(&boat1,'C',xy1,dir);
					if(check_free(N,M,&boat1,brd.board)!=1){
						mensagem_de_erro();
					}
				}while(check_free(N,M,&boat1,brd.board)!=1 );
				place_boat(xy1.x,xy1.y,dir,'C',&brd);
				print_board(N, M, brd.board, 1);
				do{
					do{
						printf("Indique as coordenadas do navio de tanques %s falta por o navio de tanques e o porta avioes\n",nome1);
						printf("Coordenadas x:");
						scanf(" %s",coord1);
						printf("Coordenadas y:");
						scanf(" %s",coord2);
					}while(is_it_number(coord1)==1 || is_it_number(coord2)==1);
					xy1.x=atoi(coord1);
					xy1.y=atoi(coord2);
					do{
						printf("Indique a direcao 'H' para horizontal 'V' para vertical: ");
						scanf(" %c",&dir);
						if(dir!='H' && dir!='V'){
							mensagem_de_erro();
						}
					}while(dir!='H' && dir!='V');
					init_boat(&boat1,'N',xy1,dir);
					if(check_free(N,M,&boat1,brd.board)!=1){
						mensagem_de_erro();
					}
				}while(check_free(N,M,&boat1,brd.board)!=1 );
				place_boat(xy1.x,xy1.y,dir,'N',&brd);
				print_board(N, M, brd.board, 1);
				do{
					do{
						printf("Indique as coordenadas do porta-avioes %s ,este e o ultimo barco\n",nome1);
						printf("Coordenada x: ");
						scanf(" %s",coord1);
						printf("Coordenada y: ");
						scanf(" %s",coord2);
					}while(is_it_number(coord1)==1 || is_it_number(coord2)==1);
					xy1.x=atoi(coord1);
					xy1.y=atoi(coord2);
					do{
						printf("Indique a direcao 'H' para horizontal 'V' para vertical: ");
						scanf(" %c",&dir);
						if(dir!='H' && dir!='V')
						{
							mensagem_de_erro();
						}
					}while(dir!='H' && dir!='V');
					init_boat(&boat1,'P',xy1,dir);
					if(check_free(N,M,&boat1,brd.board)!=1)
					{
						mensagem_de_erro();
					}
				}while(check_free(N,M,&boat1,brd.board)!=1 );
				place_boat(xy1.x,xy1.y,dir,'P',&brd);
				print_board(N, M, brd.board, 1);
			
			
				int ataque1, ataque2;
				char resposta;
				int vitoria=-1;
				char coord3[10],coord4[10];
				int numero_de_as;
				for(int j=0;j<40;j++){
					print_board(N, M, brd.board, 0);
					printf("Deseja ver o tabuleiro %s?: 's' se o desejar, 'n' ou qualquer outro caracter se nao se nao desejar ver o tabuleiro, ou 'q' para deixar de jogar :",nome2);
				scanf(" %c",&resposta);
				if(resposta=='s')
				{
					vitoria=3;
					printf("O jogador %s venceu\n",nome1);
					print_board(N,M,brd.board,1);
				}
				else{
					if(resposta == 'q'){
						return 0;

					}
				}
					
						for(int i=0;i<B;i++){
							if(brd.boats[i].afloat==0 && brd.board[ataque1][ataque2]=='A'){
								if(brd.boats[i].type=='S' && submarinos!=0){
									submarinos=submarinos-1;
								}
								if(brd.boats[i].type=='C' && contratorpedeiros!=0){
									contratorpedeiros=contratorpedeiros-1;
								}
								if(brd.boats[i].type=='N' && navios_de_tanques!=0){
									navios_de_tanques =navios_de_tanques- 1;
								}
								if(brd.boats[i].type=='P' && portaavioes!=0){
									portaavioes=portaavioes- 1;
								}
								
							}
						}
					do{
						do{
							printf("Indique a coordenada a atacar %s, restam %d jogadas e ainda faltam afundar %d barcos do tipo submarino %d barcos do tipo contratorpedeiro %d barcos do tipo navio de tanques e %d portaavioes:\n",nome2,40-j,submarinos,contratorpedeiros,navios_de_tanques,portaavioes);
							printf("Coordenada x:");
							scanf(" %s",coord3);
							printf("Coordenada y:");
							scanf(" %s",coord4);
						}while(is_it_number(coord3)==1 || is_it_number(coord4)==1);
						ataque1=atoi(coord3);
						ataque2=atoi(coord4);
						if(ataque1<0 || ataque1>N || ataque2<0 ||ataque2>M|| brd.board[ataque1][ataque2]=='*' || brd.board[ataque1][ataque2] == 'A'|| brd.board[ataque1][ataque2] == 'F'){
							print_board(N,M,brd.board,0);
						}
					}while(ataque1<0 || ataque1 >N || ataque2<0 || ataque2>M || brd.board[ataque1][ataque2]=='*' || brd.board[ataque1][ataque2] == 'A'|| brd.board[ataque1][ataque2] == 'F');
					target(ataque1,ataque2,&brd);
					numero_de_as=0;
				for(int i=0;i<M;i++)
				{
					for(int z=0;z<N;z++)
					{
						if(brd.board[i][z]=='A')
						{
							numero_de_as++;
						}
					}
				}


				if(numero_de_as==19 && vitoria!=3){
					vitoria=2;
					printf("O jogador %s venceu\n",nome2);
					print_board(N,M,brd.board,1);
					break;
				}    	

					if(j==39 && vitoria!=2){
						vitoria=1;
						printf("O jogador %s venceu\n",nome1);
						print_board(N,M,brd.board,1);
					}
					if(numero_de_as== 19)
				{
					break;
				}
				}
			
				if(vitoria==3)
				{
					printf("O jogador %s venceu\n",nome1);
				}

				printf("Deseja jogar de novo? Prima 's' caso esse seja o caso \n");
				scanf(" %c",&repetir);	
				if(repetir=='s'){
					submarinos=2;
					contratorpedeiros=2;
					navios_de_tanques=1;
					portaavioes=1;
					memset(&boat1,0 ,sizeof(boat1));
					memset(&brd,0,sizeof(brd));
				}

			}while(repetir=='s');
				//print_board(N, M, brd.board, 0);
				//printf("%d\n",typeToSize('D'));  
				/**Exemplo de uso da print_board e da place_boat**/
				/**Precisa de as implementar primeiro**/
			
				//place_boat(1,3, 'H', 'P', &brd);
			
			
				return 0;
		}
		else
		{
			if(respostamenu == 2)
			{
				printf("------------------------------------AJUDA------------------------------------\nBatalha naval é um jogo de tabuleiro de dois jogadores, no qual os jogadores\ntêm de adivinhar em que quadrados estão os navios do oponente. Este jogo é\njogado num tabuleiro 8x8 em que cada jogador pode colocar 6 navios. Navios\nestes que são: um porta-aviões (ocupa cinco posições), um navio-tanque (ocupa\nquatro posições), dois contratorpedeiros (ocupam três posições cada) e por\nfim dois submarinos (ocupam duas posições cada).\n-----------------------------------------------------------------------------");
				printf("\n\t\t     Para voltar ao menu inicial prima '1'.\n");
				printf("\t     Se quiser apenas sair introduza qualquer outra tecla.\n");
				scanf("%d", &respostaajuda);
				if(respostaajuda == 1){
					main();
				}
				else{
					return 0;
				}
			}
		}
	}
	return 0;
}
