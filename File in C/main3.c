#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_SIZE  16

 //definiamo le dimensioni della stanza //
/*Algoritmo per la simulazione del movimento di un robot in una stanza. */
/*La stanza è pavimentata a tasselli quadrati (caselle) ed è dotata di pareti esterne e 
interne come in figura. Il robot si muove sempre solo di una casella alla volta, scelta 
tra una delle quattro caselle vicine. Il robot è in grado di “vedere”, cioè di stabilire, 
guardando in una delle quattro direzioni (avanti, indietro, sinistra, destra), quante 
sono le caselle libere (in linea retta) fino alla parete. La legge con cui il robot si 
muove è la seguente: nel 30% dei casi il robot si muove a caso in una delle quattro 
caselle vicine possibili (parete permettendo); nel 70% dei casi il robot prima “vede” e 
individua la direzione (avanti, indietro, sinistra, destra) del movimento (scegliendo 
quella cui corrisponde il percorso possibile più lungo; nel caso di più percorsi di 
minima lunghezza, la direzione viene scelta a caso tra questi) e poi si muove (sempre 
di un solo passo) in quella direzione. In ogni caso, il robot non deve mai fare un 
passo in una direzione e allo step successivo un passo nella direzione opposta. La 
simulazione termina quando il robot “esce dalla porta” della stanza (in basso a 
sinistra nella figura). L’algoritmo deve visualizzare il percorso del robot dopo ogni 
passo, mostrando la stanza e la posizione del robot. */


typedef struct robot {  //struct per definire le coordinate del robot//
	int riga;//indice di riga
	int colonna;//indice di colonna
	int direzione;//direzione consentita
}robot;
robot r;


//function e procedure//
void inserisci_robot(char stanza[][MAX_SIZE]);
void visualizza_stanza(char stanza[][MAX_SIZE]);
void movimento_casuale(char stanza[][MAX_SIZE],int *f);
void movimento_intelligente(char stanza[][MAX_SIZE],int *f);
int max_array(int arr[]);
void start_robot(char stanza[][MAX_SIZE]);
int controllo_robot(char stanza[][MAX_SIZE]);

int main() { 
	time_t m;
    time_t now = time(NULL);
   
    
		int nc ;//numero casuale// 
		int conta_passi=0; //contatore numero passi effettuati dal robot
		int flag=0 , flag2=0;//flag per il controllo della corretta posizione del robot
		
		//rappresentazione della stanza//
	char stanza[MAX_SIZE][MAX_SIZE]={
	                                {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
									{'-', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '-'},
									{'-', ' ', ' ', '-', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '-'},
									{'-', ' ', ' ', '-', ' ', ' ', ' ', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
									{'-', ' ', ' ', '-', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '-'},
									{'-', ' ', ' ', '-', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '-'},
									{'-', ' ', ' ', '-', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '-'},
									{'-', ' ', ' ', '-', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' ,'-'},
					  				{'-', ' ', ' ', '-', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '-'},
									{'-', ' ', ' ', '-', ' ', ' ', ' ', '-', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '-'},
									{'-', ' ', ' ', ' ', ' ', ' ', ' ', '-', ' ', ' ', ' ', '-', '-', '-', ' ', '-'},
									{'#', ' ', ' ', ' ', ' ', ' ', ' ', '-', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '-'},
									{'#', ' ', ' ', ' ', ' ', ' ', ' ', '-', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '-'},
									{'#', ' ', ' ', ' ', ' ', ' ', ' ', '-', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '-'},
									{'-', ' ', ' ', ' ', ' ', ' ', ' ', '-', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '-'},
									{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}
									};	
	start_robot(stanza);//procedura per una migliore comprensione del progetto
	
	//inserisco il robot all'interno della stanza//
	srand(time(NULL));
	printf("INSERIMENTO DELLE COORDINATE INIZIALI DEL ROBOT\n\n");
		
	do{//eseguiamo questo blocco
		
		inserisci_robot(stanza);//inserimento da tastiera delle coordinate iniziali del robot
		flag = controllo_robot(stanza);//in base all'output della function :
		if(flag == 0)//se output=0 :
			printf("\nATTENZIONE !!! LE COORDINATE CHE HAI INSERITO CORRISPONDONO AD UNA PARETE , IL ROBOT NON PUO' ESSERE INSERITO IN QUESTA POSIZIONE...\n");
		else if(flag == 1)//se output=1 :
			printf("\nROBOT INSERITO CORRETTAMENTE\n\n");
		else if(flag == 2)//se output=2 :
			printf("\nCOORDINATE ERRATE\n");
			
	}while(flag == 0 || flag == 2);//finche risulta vera una di queste condizioni 
	
    visualizza_stanza(stanza);//dopo aver posizionato il robot , visualizziamo la stanza con il robot al suo interno
	system("pause");
	system("CLS");
	//il ciclo si ripete finché il robot non esce dalla stanza.
	while(flag2 == 0){
	
		//generazione di un numero casuale
		nc = rand()%10;
		visualizza_stanza(stanza);	
		//system("pause");
		system("CLS");
		//30%: se viene generato casualente un numero tra 0 e 2 il robot 
		//si muove in una delle quattro direzioni in maniera casuale .
		if(nc >= 0 && nc < 3){
			movimento_casuale(stanza , &flag2);//richiamo la procedura per il movimento casuale
			conta_passi++;//incremento il contatore per i passi
		}
		//70%: se viene generato casualmente un numero tra 3 e 9 il robot
		//si muove nella direzione con il percorso più lungo.
		else{
		    movimento_intelligente(stanza, &flag2);//richiamo la procedura per il movimento intelligente
		    conta_passi++;//incremento il contatore dei passi
		}
	}
	//quando il robot esce dalla stanza il programma termina// 
	visualizza_stanza(stanza);
	m = difftime(time(NULL), now);//calcolo il tempo trascorso tra l'inizio del programma e il suo termine 
    
	printf("\nIl robot e' uscito dalla stanza\n");
   
	printf("il robot ha impiegato circa  %ld secondi per uscire dalla stanza\n",m); //stampo il tempo impiegato dal robot per uscire dalla stanza

    printf("Il robot si è spostato per un totale di : %d passi\n",conta_passi);//stampo anche il numero di passi compiuti dal robot 

	return 0;
}

//PROCEDURA
//inserisci_robot:procedura per l'inserimento da tastiera (tramite coordinate) del robot nella stanza//
//input:l'array stanza[][MAX_SIZE] che rappresenta appunto la stanza ;
void inserisci_robot(char stanza[][MAX_SIZE]){
	    printf("Inserisci indice riga (DA 0 A 15) ");
		scanf("%d", &r.riga);
		printf("Inserisci indice colonna (DA 0 A 15) ");
		scanf("%d", &r.colonna);
}			
//FUNCTION
//controllo_robot:function per il controllo delle coordinate , per evitare che il robot venga inserito in posti della stanza errati
//l'array stanza[][MAX_SIZE] che rappresenta appunto la stanza ;
//outputs:indice che può essere : 0,1,2 che regola nel main una	selezione a 3 vie ;
int controllo_robot(char stanza[][MAX_SIZE]){	
if((r.riga >= 0 && r.colonna <= MAX_SIZE - 1) && (r.colonna >= 0 && r.riga <= MAX_SIZE - 1)){

		if(stanza[r.riga][r.colonna] == ' '){
			stanza[r.riga][r.colonna] = 'x';
			return 1;
		}

		else{
			return 0;
		}
	}
	else
		return 2;

}



//PROCEDURA
//visualizza_stanza: procedura per permettere la visualizzazione della stanza di volta in volta//
//input: l'array stanza[][MAX_SIZE] che rappresenta appunto la stanza ;
void visualizza_stanza(char stanza[][MAX_SIZE])
{
	int i,j;
		for(i=0;i<MAX_SIZE;++i)
			{	
				for(j=0;j<MAX_SIZE;++j)
					printf("%c",stanza[i][j]);
				printf("\n");
				
			}
}	
//PROCEDURA
//movimento_casuale: procedura che consente al robot di muoversi in maniera casuale 
//in una delle quattro caselle vicine
//input: l'array stanza[][MAX_SIZE] che rappresenta appunto la stanza ;
       //int *p: Puntatore contenente l'indirizzo della 
					//variabile int flag2 dichiarata nel main.

void movimento_casuale(char stanza[][MAX_SIZE], int *p)
{ int nc1, flag = 0, flag3 = 0;
	
	stanza[r.riga][r.colonna]= ' ';
	
	
	
	while(flag3 == 0){
		nc1 = rand()%4+1; //genera un numero casuale rappresentante la direzione
					  //in cui il robot deve andare
		flag = 0;
		while(flag == 0){
			//controllo sulla direzione precedente
			if((nc1 == 1 && r.direzione == 3) || (nc1 == 3 && r.direzione == 1) || (nc1 == 2 && r.direzione == 4) || (nc1 == 4 && r.direzione == 2))
				nc1 = rand()%4+1;
			else
				flag = 1;		
				}	
		
		switch(nc1){//in base al numero casuale viene scelta la direzione 
			
			case 1: //nord
				if(stanza[r.riga - 1][r.colonna] != '-'){//controllo eventuale presenza pareti
					flag3 = 1;
					r.riga--;//decremento l'indice di riga
					r.direzione = 1;
				}
				break;
			case 2: //est
				if(stanza[r.riga][r.colonna + 1] != '-'){//controllo eventuale presenza pareti
					flag3 = 1;
					r.colonna++;//incremento l'indice di colonna
					r.direzione = 2;	
				}
				break;
			case 3: //sud
				if(stanza[r.riga + 1][r.colonna] != '-'){//controllo eventuale presenza pareti
					flag3 = 1;
					r.riga++;//incremento l'indice di riga
					r.direzione = 3;	
				}
				break;
			case 4: //ovest
				if(stanza[r.riga][r.colonna - 1] != '-'){//controllo eventuale presenza pareti
					flag3 = 1;
					r.colonna--;//incremento l'indice di colonna
					r.direzione = 4;	
				}
				break;
			}	
	}	
		
		if((r.riga >= 0 && r.riga <= MAX_SIZE - 1) && (r.colonna >= 0 && r.colonna <= MAX_SIZE - 1)){
			if(stanza[r.riga][r.colonna] == '#'){//se alle nuove coordinate corrisponde l'uscita
				stanza[r.riga][r.colonna] = 'x';//inserimento del robot nella nuova posizione
				*p = 1;//il puntatore viene posto uguale ad 1 per indicare che il robot è uscito dalla stanza
			}
			else{//altrimenti
				stanza[r.riga][r.colonna] = 'x';//controllo eventuale presenza pareti
			}		
		}
}

 //PROCEDURA
/*movimento_intelligente:procedura che conta il numero di caselle libere 
in ogni direzione a partire dalla posizione in cui si trova il robot 
e sposta il robot scegliendo il percorso possibile più lungo
input:l'array stanza[][MAX_SIZE] che rappresenta appunto la stanza ;
//int *p: Puntatore contenente l'indirizzo della 
					//variabile int flag2 dichiarata nel main.
*/
void movimento_intelligente(char stanza[][MAX_SIZE] , int *p)
{
				
	int pos[4]={0},i,j,ind_max;
	int flag=0,flag2=0;
    
	
	/*pos[]   = array di 4 elementi che contiene il numero di caselle libere per ogni direzione
			pos[0]=numero di caselle libere verso ovest
			pos[1]=numero di caselle libere verso est
			pos[2]=numero di caselle libere verso nord
			pos[3]=numero di caselle libere verso sud
	  ind_max = indice del massimo. Serve per stabilire (tramite switch) in quale locazione dell'array pos vi è il massimo
	*/
		
		
	    //conta celle-nord	
    i = r.riga;
	while(stanza[i-1][r.colonna] != '-' && i >= 0){
		i--;
		pos[0]++;
	}
	
        //conta celle - est
	j = r.colonna;
	while(stanza[r.riga][j+1] != '-' && j < MAX_SIZE){
		j++;
		pos[1]++;
	}
	
        //conta celle - sud      
	i = r.riga;
	while(stanza[i+1][r.colonna] != '-' && i < MAX_SIZE){
		i++;
		pos[2]++;
	}
	
        //conta celle - ovest
	j = r.colonna;
	while(stanza[r.colonna][j-1] != '-' && j >= 0){
		j--;
		pos[3]++;
	}
	
	//sceglie il percorso più lungo
	ind_max = max_array(pos);
    stanza[r.riga][r.colonna] = ' ';
	
	switch(ind_max){
		case 1: //nord
				if(stanza[r.riga-1][r.colonna] != '-'){
					flag2 = 1;
					r.riga--;
					r.direzione = 1;
				}
				break;
			case 2: //est
				if(stanza[r.riga ][r.colonna+1] != '-'){
					flag2 = 1 ;
					r.colonna++;
					r.direzione = 2;	
				}
				break;
			case 3: //sud
				if(stanza[r.riga+1 ][r.colonna] != '-'){
					flag2 = 1;
					r.riga++;
					r.direzione = 3;	
				}
				break;
			case 4: //ovest
				if(stanza[r.riga][r.colonna-1] != '-'){
					flag2 = 1;
					r.colonna--;
					r.direzione = 4;	
				}
				break;
	}//stesso controllo presente in movimento_casuale
		if((r.riga >= 0 && r.riga <= MAX_SIZE - 1) && (r.colonna >= 0 && r.colonna <= MAX_SIZE - 1)){
			if(stanza[r.riga][r.colonna] == '#'){
				stanza[r.riga][r.colonna] = 'x';
				*p = 1;
			}
			else{
				stanza[r.riga][r.colonna] = 'x';
			}		
		}
}
       	

//FUNCTION
/*max_array:function che restituisce l'indice dell'elemento massimo dell'array che riceve in input
input:arr[] = rappresenta l'array pos che  quale contiene il numero di caselle libere per ogni direzione
*/
int max_array(int arr[])
{
	int i, max1, max2, ind_max1, ind_max2;
	srand(time(NULL));
	if(arr[0] >= arr[1]){
	max1 = arr[0];
	max2 = arr[1];
	ind_max1 = 1;
	ind_max2 = 2;
}
else{
	max1 = arr[1];
	max2 = arr[0];
	ind_max1 = 2;
	ind_max2 =1;
}

for(i = 2; i < 4; i++){
	
	if(arr[i] > max1){
		max2 = max1;
		ind_max2 = ind_max1;
		max1 = arr[i];
		ind_max1 = i+1;
	}
	else if(arr[i] >= max2){
		max2 = arr[i];
		ind_max2 = i+1;
	}
}
	//controllo sulla posizione precedente
	if(max1 != max2){
		if((ind_max1 == 1 && r.direzione == 3) || (ind_max1 == 3 && r.direzione == 1) || (ind_max1 == 2 && r.direzione == 4) || (ind_max1 == 4 && r.direzione == 2))
			return ind_max2;
		else
			return ind_max1;
	}
	
	else if(rand() % 2 == 0){
		if((ind_max1 == 1 && r.direzione == 3) || (ind_max1 == 3 && r.direzione == 1) || (ind_max1 == 2 && r.direzione == 4) || (ind_max1 == 4 && r.direzione == 2))
			return ind_max2;
		else
			return ind_max1;
	}
	else{
		if((ind_max2 == 1 && r.direzione == 3) || (ind_max2 == 3 && r.direzione == 1) || (ind_max2 == 2 && r.direzione == 4) || (ind_max2 == 4 && r.direzione == 2))
			return ind_max1;
		else
			return ind_max2;
	}
}
//PROCEDURA
//start_robot:procedura che viene utilizzata solo per inizializzare il programma e renderlo più comprensibile ; 
// input : l'array stanza[][MAX_SIZE] che rappresenta appunto la stanza ;
void start_robot(char stanza[][MAX_SIZE]){
	
	printf("Ciao , sono il tuo robot , ecco la stanza che hai a disposizione:\n");
	visualizza_stanza(stanza);
	printf("Posizionami all'interno della stanza , ma fai attenzione alle pareti !!\n");
}

	
