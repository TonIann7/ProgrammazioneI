//CHIAMATE TELEFONICHE//
/* Programma che simula l'archivio mensile (31 giorni) di chiamate di un gestore telefonico */
/* MAX. CHIAMATE GIORNALIERE = 10 */
/* COSTO AL MINUTO DELLA CHIAMATA = 10 cent */
/* IDENTIFICATIVI DELLA CHIAMATA :
-NUMERO CHIAMANTE 
-NUMERO RICEVENTE
-DURATA CHIAMATA */
/*NON PREVISTI DALLA TRACCIA MA IMPOSTATI PER VELOCIZZARE L'ESECUZIONE DEL PROGRAMMA :
-MAX. DURATA CHIAMATA = 30 MIN */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>  //time.h è l'header file della libreria standard del C che fornisce un accesso standardizzato alle funzioni di acquisizione e manipolazione del tempo//
#include <string.h> 
#include <conio.h>
//NUMERO MASSIMO DI GIORNI IN UN MESE//
#define GIORNI_MAX_MESE 31
//COSTO AL MINUTO DI OGNI CHIAMATA= 10 cent AL MINUTO//
#define COSTO_AL_MINUTO 0.10
//NUMERO MASSIMO DI CHIAMATE IN UN GIORNO = 10 CHIAMATE //
#define MAX_CHIAM_GIORN 10
//TEMPO MASSIMO DURATA DI UNA CHIAMATA = 30 MINUTI //
#define MAX_DURATA_CHIAM 30
// NUMERO MASSIMO DI NUMERI REGISTRATI IN RUBRICA//
#define NUM_RUBRICA 25
// NUMERO MASSIMO DI REGISTRAZIONI CHE POSSONO ESSERE CONTENUTE NELL'ARCHIVIO//
#define MAX_REGISTRAZIONI 200
/*DEFINIAMO UN NUOVO TIPO DI STRUCT : "struct numero_telefonico" CHE HA COME CAMPO  I NUMERI DI TELEFONO */
struct numero_telefonico{
       char *numero;
                       };
//DEFINIAMO UN NUOVO TIPO DI STRUCT : "struct dati_chiamata" CHE HA COME CAMPI TUTTE LE INFORMAZIONI RELATIVE AD OGNI SINGOLA CHIAMATA//                       
struct dati_chiamata {
       int giorno;   // GIORNO DELLA CHIAMATA //
       struct numero_telefonico chiamante; // RICHIAMO LA STRUCT DEFINITA PRECEDENTEMENTE PER DEFINIRE IL NUMERO CHIAMANTE //
       struct numero_telefonico ricevente; // RICHIAMO LA STRUCT DEFINITA PRECEDENTEMENTE PER DEFINIRE IL NUMERO CHIAMANTE //
       unsigned int durata; //DURATA DELLA CHIAMATA //                  
       float costo;//COSTO DELLA CHIAMATA//
       };
//PROCEDURA CHE CI PERMETTE DI INSERIRE I NUMERI ALL'INTERNO DELLA RUBRICA//       
void inseriscinum(struct numero_telefonico elenco[]);//COME INPUT HA L'ARRAY ELENCO DELLA STRUCT NUMERO TELEFONICO//
//FUNZIONE CHE CI PERMETTE DI VERIFICARE L'APPARTENENZA DI UN DATO NUMERO INSERITO ALL'ELENCO DEI NUMERI MEMORIZZATI//
int esisteNumero(struct numero_telefonico elenco[], struct numero_telefonico numero);//COME INPUT HA L'ARRAY ELENCO DELLA STRUCT numero_telefonico E LA STRUCT NUMERO//
//PROCEDURA CHE CI PERMETTE DI VISUALIZZARE TUTTE LE CHIAMATE CON LE RELATIVE INFORMAZIONI IN UN SINGOLO GIORNO,DATO UN NUMERO DI TELEFONO//
void ricerca_giornaliera(struct dati_chiamata archivio[],struct numero_telefonico num,int registrazioni);//COME INPUT HA L'ARRAY ARCHIVIO DELLA STRUCT dati_chiamata , LA STRUCT NUM E LE REGISTRAZIONI // 
//PROCEDURA CHE CI PERMETTE DI VISUALIZZARE IL COSTO TOTALE DELLE CHIAMATE ,DATO UN  GIORNO E UN NUMERO DI TELEFONO //
void ricerca_costo(struct dati_chiamata archivio[],struct numero_telefonico num,int registrazioni);//COME INPUT HA L'ARRAY ARCHIVIO DELLA STRUCT dati_chiamata , LA STRUCT NUM E LE REGISTRAZIONI //

int main(int argc, char *argv[]) {
	
 srand(time(NULL));//INIZIALIZZO IL GENERATORE DEI NUMERI CASUALI//
 struct numero_telefonico elenconum[25]; //DICHIARO UN ARRAY ELENCONUM DI TIPO numero_telefonico//
 struct dati_chiamata  archivio[MAX_REGISTRAZIONI];//DICHIARO UN ARRAY ARCHIVIO DI TIPO dati_chiamata//
 //VARIABILI DA UTILIZZARE IN SEGUITO//
 int d;//per controllare i giorni//
 int num_r=0;//numero registrazioni//
 int n_max_d;//numero massimo chiamate giornaliere//
 int conta_reg=0;//contatore registrazioni//
 int n_c_g;//controlla il numero di chiamate ogni giorno//
 int n_chiam;//numero chiamante//
 int n_ricev;//numero ricevente//
 unsigned int durata;//durata della chiamata//
 struct numero_telefonico ricerca_num;
 char scelta;//numero opzione inserito da tastiera//
 char n[20];//stringa in cui viene memorizzata il numero inserito da tastiera//
 char g[10];//stringa in cui viene memorizzata il giorno inserito da tastiera//
 inseriscinum(elenconum);
 /* CREO ARCHIVIO TELEFONICO UTILIZZANDO I NUMERI CHE HO DICHIARATO NELLA RUBRICA */
 //ciclo dei giorni // 
 for(d=1;d<GIORNI_MAX_MESE;d++){
 	// genero il numero totale di chiamate che vengono effettuate quotidianamente//
      /* utilizzo La funziona srand che serve ad inizializzare il generatore dei numero psuedocasuali,
      senza questa procedura ,la sequenza dei numeri ( in questo caso il numero delle chiamate) sarebbe sempre uguale 
      ad ogni avvio del programma e per ogni ciclo*/
      n_max_d=1+rand()%MAX_CHIAM_GIORN; /* serve a generare il numero di chiamate giornaliere in maniera casuale fino ad un massimo di  10 chiamate al giorno*/
      // generazione numero chiamate//
      for(n_c_g=1;n_c_g<=n_max_d;n_c_g++){
      	n_chiam=rand()%NUM_RUBRICA;/* Il numero chiamante viene scelto casualmente all'interno della rubrica */
         /*   e' importante che il numero chiamanete sia diverso dal numero ricevente
         per questo motivo  utilizzo un ciclo while per evitare questo problema */
         n_ricev=n_chiam;
         while (n_chiam==n_ricev){
         	n_ricev=rand()%NUM_RUBRICA;// Il numero ricevente viene scelto casualmente all' interno della rubrica//
		 }
		 durata=1+rand()%MAX_DURATA_CHIAM;/* si sceglie in maniera casuale la durata di una telefonata fino ad un massimo di  30 MIN per chiamata*/
		 archivio[num_r].giorno=d;
		 archivio[num_r].chiamante.numero=elenconum[n_chiam].numero;//definisco il numero chiamante
		 archivio[num_r].ricevente.numero=elenconum[n_ricev].numero;//definisco il numero ricevente
		 archivio[num_r].durata=durata;//definisco la durata 
		 archivio[num_r].costo=(durata*COSTO_AL_MINUTO);//calcolo del costo complessivo di una chiamata//
		 num_r++;//numero registrazioni
		 conta_reg++;//contatore registrazioni
	  }
 }
 do{
       system("cls"); // PULISCE LO SCHERMO//
    // presentazione programma //
    printf(" **************************************************************************************************************************************************** \n");
    printf(" *                                                                         BENVENUTO !                                                              * \n");
    printf(" *                                                                   ECCO IL NOSTRO ARCHIVIO                                                        * \n");
    printf(" *                                                                     DEL MESE DI GENNAIO                                                          * \n");
    printf(" **************************************************************************************************************************************************** \n");
    printf("\n");
   
    
    
	
    printf("SCEGLIERE L'OPERAZIONE DA ESEGUIRE\n\n1   -RICERCA INFORMAZIONI TRAMITE NUMERO DI TELEFONO\n\n2   -COSTO TOTALE TELEFONATE IN UN DATO GIORNO \n\n3  -ESCI\n\n scelta: ");
    fflush(stdin); // pulisce il buffer di tastiera //
	scelta= getch(); // legge da tastiera un carattere //
	fflush(stdin);
	if (scelta== '1') // tasto 1 del menù
	  {
	    printf("\n INSERIRE NUMERO TELEFONO "); //si inserisce il numero desiderato   
		scanf("%s", &n);
		ricerca_num.numero=n;
		// con questo if controlliamo se il numero inserito da tastiera è presente nella rubrica //
	    if ((esisteNumero(elenconum, ricerca_num) == 1 ))// se il numero inserito esiste
            ricerca_giornaliera(archivio,ricerca_num,conta_reg);// posso utilizzare la funzione che ci permette di ricerca le informazioni delle chiamate
         else
             printf("Numero telefonico non trovato\n");// altrimenti si deve visualizzare sullo schermo che il numero non è stato trovato//
             system("pause");
	  }
	  if (scelta=='2'){//tasto 2 del menù
	  	printf("\n INSERIRE NUMERO TELEFONO ");//si inserisce il numero desiderato
		scanf("%s", &n);
		ricerca_num.numero=n;
		if ((esisteNumero(elenconum, ricerca_num) == 1 )){// con questo if controlliamo se il numero inserito da tastiera è presente nella rubrica //
		//se il numero inserito esiste//
	   
	   ricerca_costo(archivio,ricerca_num,conta_reg);// utilizzo quindi la funzione che ci permette di ricerca le informazioni delle chiamate//
       }
         else
             printf("Numero telefonico non trovato\n");
             system("pause"); //altrimenti , se il numero inserito non è presente nella rubrica , si visualizza sullo schermo : "numero telefonico non trovato" //
	  }
}
	while(scelta !='3');// esce dal programma/
	printf("\n");


	return 0;
}
	
	
	
/*  FUNZIONI */
//adesso andremo a implementare tutte le funzioni dichiarate precedentemente //
//la prima è quella che ci permette di inserire numeri in archivio//
//input: elenco numerico
void inseriscinum(struct numero_telefonico elenconum[]){//inseriamo i numeri manualmente per semplificare il programma 
 elenconum[0].numero="3365874120";
 elenconum[1].numero="3214569782";
 elenconum[2].numero="3217050741";
 elenconum[3].numero="0828547630";
 elenconum[4].numero="3201456789";
 elenconum[5].numero="3654758962";
 elenconum[6].numero="0123456789";
 elenconum[7].numero="0789456123";
 elenconum[8].numero="3665435472";
 elenconum[9].numero="0102030405";
 elenconum[10].numero="3287450123";
 elenconum[11].numero="3272525100";
 elenconum[12].numero="0818924574";
 elenconum[13].numero="0818162323";
 elenconum[14].numero="0892192600";
 elenconum[15].numero="3458020136";
 elenconum[16].numero="3201728396";
 elenconum[17].numero="3331323123";
 elenconum[18].numero="3380011223";
 elenconum[19].numero="3474900042";
 elenconum[20].numero="3894561230";
 elenconum[21].numero="3312546842";
 elenconum[22].numero="0215645789";
 elenconum[23].numero="3457891230";
 elenconum[24].numero="7894561230";
}

	
int esisteNumero(struct numero_telefonico elenconum[], struct numero_telefonico numero){//procedura che ci permette di capire se il numero inserito da tastiera appartiene al nostro elenco//
//input: elenco telefonico e numero di telefono che inseriremo da tastiera//
// se output=1 il numero appartiene all'elenco//
//se output=0 il numero non appartiene all'elenco//
	int i;
	for(i=0;i<NUM_RUBRICA-1;i++){
		if(strcmp(numero.numero,elenconum[i].numero)==0)//utilizzo la strcmp per comparare il numero inserito da tastiera con i numeri presenti in archivio
		return 1;
	}
	return 0;
}
// procedura che ricerca ,dato un numero di telefono, tutte le informazioni relative a quel numero//
//input: archivio( che contiene tutte le chiamate), numero telefonico, Il numero di informazioni presenti nell 'archivio
//:output: stamapre su schermo tutte le informazioni relative a quel determinato numero di telefono//
void ricerca_giornaliera(struct dati_chiamata archivio[],struct numero_telefonico num,int registrazioni){
	int j;
	int trovato=0;
	system("cls"); // pulisce lo schermo
     printf(" CHIAMATE EFFETTUATE \n");
     printf("\n");
     printf("\n");
     printf("GIORNO  ");
           printf(" N.RICEVENTE ");
           printf("   DUARATA  ");
           printf("    COSTO ");
           printf("\n");
           for(j=0;j<registrazioni;j++)
     {
        if(strcmp(num.numero,archivio[j].chiamante.numero)==0) // se strcmp == 0 significa che il numero appartiene all'archvio
        {
		  trovato =1;
		  printf("\n"); // stampo informazioni relative al numero inserito
          printf("%3d ",archivio[j].giorno);//stampo il giorno
          printf("     %s ",archivio[j].ricevente.numero);//stampo il numero ricevente
          printf("      %2d min",archivio[j].durata);//stampo la durata              
          printf("    %5.2f EURO ",archivio[j].costo);//stampo il costo
          printf("\n");
        }
    }
    if(trovato ==0) // il numero non è stato trovato nell'archivio
     {
       printf(" Il numero non ha effettuato nessuna chiamata \n");
     }
     trovato=0;
     printf("\n");
     printf("\n CHIAMATE RICEVUTE \n");   // effettuo lo stesso procedimento di prima per trovare tutte le informazioni riguardo le chiamate ricevute
     printf("\n");
     printf("\n");
     printf("GIORNO  ");
           printf("N.CHIAMANTE ");
           printf("   DUARATA  ");
           printf("   COSTO ");
           printf("\n");
     for(j=0;j<registrazioni;j++)
     {
    
		if(strcmp(num.numero,archivio[j].ricevente.numero)==0) // se strcmp==0 il numero inserito appartiene all'archivio
        {
		  trovato =1;
		  printf("\n");//stampo tutte le informazioni relative al numero inserito
          printf("%3d ",archivio[j].giorno);//giorno
          printf("    %s ",archivio[j].chiamante.numero);//numero chiamante
          printf("     %2d min ",archivio[j].durata);   //durata             
          printf("     %4.2f EURO ",archivio[j].costo);//costo
          printf("\n");
        }
     }
     if(trovato ==0)// il numero non è stato trovato all interno dell'archvio
     {
       printf(" Il numero non ha ricevuto nessuna chiamata \n");
     }
    
}

// Dato un numero di telefono calcolare il costo totale delle chiamate in un dato giorno//
void ricerca_costo(struct dati_chiamata archivio[],struct numero_telefonico num,int registrazioni)
{//input: archivio, numero di telefono, numero di dati dell'archivio
//output: costo totale telefonata
	int k,g;
	float costo=0;
	
	  for(k=0;k<registrazioni;k++) // controllo ad uno ad uno tutte le informazioni ,relative al costo ,nell'archivio
	  {
	     if(strcmp(num.numero,archivio[k].chiamante.numero)==0)// se il num. inserito si trova nell'archivio
		 {
		 	// stampo le informazioni relative al costo
		 }
	} 
            	printf("\n INSERIRE GIORNO: ");//si inserisce il giorno di cui si vogliono avere informazioni//
	         scanf("%d",&g);
	         if(g>31 || g<=0){
	         	printf("HAI INSERITO IL GIORNO ERRATO \n\n ");
	         	
			 }
	        else{
			
		   costo=costo+archivio[g].costo; 
		   
	   if(costo==0)// se il costo ==0 significa che il numero nn ha effettuato nessuna chiamata
	   {
	     printf("\n IL NUMERO NON HA EFFETTUATO NESSUNA CHIAMATA \n\n"); //
       }
       else{//altrimenti stampo il costo delle chiamate effettuate da quel numero in quel giorno
	   printf(" IL COSTO TOTALE DELLE CHIAMATE EFFETTUATE NEL GIORNO %d E' %7.2f EURO \n\n",g,costo);
	   }
}
	  
}		   


