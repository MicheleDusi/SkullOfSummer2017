#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ArrayList.h"

#define INCREASING_FACTOR 2
#define INCREASING_CHECK 0.75
#define DECREASING_FACTOR 0.5
#define DECREASING_CHECK 0.25
#define DEFAulT_CAPACITY 10
#define MINIMUM_CAPACITY DEFAulT_CAPACITY * DECREASING_FACTOR


const char* STRING_TITLE = "LISTA [size: %d]\n";
const int STRING_TITLE_LENGTH = 26;

/**
 * Inizializzazione di una lista vuota con capacità iniziale personalizzata.
 */
arraylist* al_initListWithCapacity(int cap) {
	arraylist* new_list = malloc(sizeof(arraylist));
	if (!new_list) {
		printf("Errore: memoria insufficiente per la creazione della lista!\n");
		exit(1);
	}
	new_list->size = 0;
	new_list->capacity = cap > MINIMUM_CAPACITY ? cap : MINIMUM_CAPACITY;
	new_list->array = malloc(new_list->capacity * sizeof(void*));
	return new_list;
}

/** 
 * Inizializzazione della lista vuota con capacità iniziale di default.
 */
arraylist* al_initList() {
	return al_initListWithCapacity(DEFAulT_CAPACITY);
}

/**
 * Elimina la lista passata come parametro, liberando le zone di memoria occupate
 * dalla struttura ArrayList e dal vettore interno.
 * <b>NON</b> elimina gli oggetti a cui i puntatori nel vettore puntano.
 */
void al_cleanList(arraylist* l) {
	free(l->array);
	free(l);
}

/**
 * Elimina la lista passata come parametro, liberando le zone di memoria occupate
 * dalla struttura ArrayList, dal vettore interno e dagli oggetti contenuti all'interno del vettore.
 * Questo significa che essi non saranno più utilizzabili dopo la chiamta a funzione.
 */
void al_purgeList(arraylist* l) {
	for (int i = 0; i < l->size; i++) {
		free(l->array[i]);
	}
	al_cleanList(l);
}

/**
 * Controlla la dimensione dell'arraylist dopo che è stata effettuata un'aggiunta di un elemento.
 * In caso la capacità debba essere aumentata, viene re-allocato l'array in una porzione di memoria maggiore.
 */
static void checkAndIncreaseCapacity(arraylist* l) {
	if (l->size > l->capacity * INCREASING_CHECK) {
		int new_capacity = (int)(l->capacity * INCREASING_FACTOR);
		l->array = realloc(l->array, new_capacity * sizeof(void*));
		l->capacity = new_capacity;
	}
}

/**
 * Controlla la dimensione dell'arraylist dopo che è stata effettuata una rimozione.
 * In caso la capacità possa essere ridotta, viene re-allocato l'array in una porzione di memoria minore.
 */
static void checkAndDecreaseCapacity(arraylist* l) {
	if (l->size < l->capacity * DECREASING_CHECK
			&& l->capacity > MINIMUM_CAPACITY) {
		int new_capacity = (int)(l->capacity * DECREASING_FACTOR);
		l->array = realloc(l->array, new_capacity * sizeof(void*));
		l->capacity = new_capacity;
	}
}

/**
 * Controlla che la posizione inserita sia ammessa nella lista.
 */
static bool al_checkPositionValidity(arraylist* l, int pos) {
	return pos >= 0 && pos < l->size;
}

/** 
 * Inserimento di un elemento in testa alla lista.
 */
void al_insertElementFirst(arraylist* l, void* new_element_data) {
	for (int i = l->size; i > 0; i--) {
		l->array[i] = l->array[i - 1];
	}
	l->array[0] = new_element_data;
	l->size++;
	checkAndIncreaseCapacity(l);
}

/**
 * Inserimento di un elemento in coda alla lista.
 */
void al_insertElementLast(arraylist* l, void* new_element_data) {
	l->array[l->size] = new_element_data;
	l->size++;
	checkAndIncreaseCapacity(l);
}

void al_insertElementAtPosition(arraylist* l, void* new_element_data, int pos) {
	if (al_checkPositionValidity(l, pos)) {
		for (int i = l->size; i > pos; i--) {
			l->array[i] = l->array[i - 1];
		}
		l->array[pos] = new_element_data;
		l->size++;
		checkAndIncreaseCapacity(l);
	} else {
		// TODO errore
	}
}

void al_deleteFirstElement(arraylist* l) {
	for (int i = 0; i < l->size - 1; i++) {
		l->array[i] = l->array[i + 1];
	}
	l->size--;
	checkAndDecreaseCapacity(l);
}

void al_deleteLastElement(arraylist* l) {
	l->size--;
	checkAndDecreaseCapacity(l);
}

/**
 * Rimuove un elemento alla posizione desiderata.
 */
void al_deleteElementAtPosition(arraylist* l, int pos) {
	if (al_checkPositionValidity(l, pos)) {
		for (int i = pos; i < l->size - 1; i++) {
			l->array[i] = l->array[i + 1];
		}
		l->size--;
		checkAndDecreaseCapacity(l);
	}
}

/**
 * Rimuove tutti gli elementi che soddisfano una data condizione.
 */
void al_deleteElementsByConditions(arraylist* l, bool (*condition)(void*)) {
	for (int i = 0; i < l->size;) {
		if (condition(l->array[i])) {
			l->size--;
			for (int j = i; j < l->size; j++) {
				l->array[j] = l->array[j + 1];
			}
		} else {
			i++;
		}
	}
	checkAndDecreaseCapacity(l);
}

/**
 * Restituisce il contenuto del primo elemento della lista.
 */
void* al_getHeadContent(arraylist* l) {
	return l->array[0];
}

/**
 * Restituisce il contenuto del primo elemento.
 */
void* al_extractHeadContent(arraylist* l) {
	void* aux = l->array[0];
	l->size--;
	for (int i = 0; i < l->size; i++) {
		l->array[i] = l->array[i + 1];
	}
	checkAndDecreaseCapacity(l);
	return aux;
}

/**
 * Estrae un elemento alla posizione desiderata, lo cancella dalla lista e lo restituisce come puntatore.
 * Il primo elemento della lista ha posizione "0".
 */
void* al_extractElementAtPosition(arraylist* l, int pos) {
	if (al_checkPositionValidity(l, pos)) {
		void* aux = l->array[pos];
		l->size--;
		for (int i = pos; i < l->size; i++) {
			l->array[i] = l->array[i + 1];
		}
		checkAndDecreaseCapacity(l);
		return aux;
	} else {
		return NULL;
	}
}

/**
 * Restituisce il contenuto dell'ultimo elemento della lista.
 * Se la lista è vuota, restituisce NULL.
 */
void* al_getTailContent(arraylist* l) {
	if (l->size > 0)
		return l->array[l->size - 1];
	return NULL;
}

/**
 * Restituisce il contentuto di un elemento alla posizione desiderata.
 */
void* al_getElementContentAtPosition(arraylist* l, int pos) {
	if (al_checkPositionValidity(l, pos))
		return l->array[pos];
	return NULL;
}

/**
 * Restituisce la quantità di elementi presenti nella lista.
 */
int al_getListSize(arraylist* l) {
	return l->size;
}

/**
 * Restituisce la posizione dell'elemento corrispondente a quello cercato.
 * Se l'elemento non è presente all'interno della lista, viene restituito il valore -1.
 */
int ul_getElementPosition(arraylist* l, void* element_content) {
	for (int i = 0; i < l->size; i++) {
		if (element_content == l->array[i]) {
			return i;
		}
	}
	return -1;
}

/**
 * Verifica che all'interno della lista sia presente almeno un elemento che soddisfi una data condizione.
 */
bool al_containsElement(arraylist* l, bool (*condition)(void*)) {
	for (int i = 0; i < l->size; i++) {
		if (condition(l->array[i])) {
			return true;
		}
	}
	return false;
}

/**
 * Scambia di posto due elementi della lista, date le loro posizioni.
 */
void al_swapTwoElements(arraylist* l, int pos1, int pos2) {
	if (al_checkPositionValidity(l, pos1) && al_checkPositionValidity(l, pos2)) {
		void* aux = malloc(sizeof(void*));
		aux = l->array[pos1];
		l->array[pos1] = l->array[pos2];
		l->array[pos2] = aux;
		free(aux);
	} else {
		// TODO Errore
	}
}

/**
 * Clona una lista, data in ingresso una funzione per la clonazione del contenuto di un elemento.
 * Garantisce il mantenimento dell'ordine durante il processo.
 */
arraylist* al_cloneOrderedList(arraylist* l, void* (*clone)(void*)) {
	// Inizializzo la nuova lista
	arraylist* new_list = al_initListWithCapacity(l->capacity);
	// Clonazione
	for (int i = 0; i < l->size; i++) {
		new_list->array[i] = clone(l->array[i]);
	}
	new_list->size = l->size;
	// Fine
	return new_list;
}

/**
 * Unisce gli elementi di due liste in un'unica nuova lista.
 * Le liste originali <b>NON</b> vengono modificate.
 * E' possibile personalizzare il processo di clonazione attraverso la funzione <i>clone</i> passata come parametro.
 */
arraylist* al_concatenateTwoLists(arraylist* l1, arraylist* l2, void* (*clone)(void*)) {
	// Inizializzo la lista vuota pronta ad accogliere gli elementi clonati
	arraylist* new_list = al_initListWithCapacity(l1->capacity + l2->capacity);
	new_list->size = l1->size + l2->size;
	// Clono gli elementi
	int i;
	for (i = 0; i < l1->size; i++) {
		new_list->array[i] = clone(l1->array[i]); // Clono la prima lista
	}
	for (i = l1->size; i < new_list->size; i++) {
		new_list->array[i] = clone(l2->array[i - l1->size]); // Clono la seconda lista
	}
	// Fine
	return new_list;
}

/**
 * Data una lista e una relazione d'ordine definita sui suoi elementi, la funzione
 * restitutisce l'elemento "minimo" (sotto forma di puntatore ad esso).
 * La relazione deve essere implementata come una funzione che prende in ingresso il contenuto di due nodi, 
 * e li confronta restituendo:
 * - un numero negativo se il primo dato è "minore" del secondo (stando alla relazione).
 * - 0 se i due dati sono considerati uguali dalla relazione d'ordine.
 * - un numero positivo se il primo dato è "maggiore" del secondo (stando alla relazione).
 */
void* al_getMinimumContent(arraylist* l, int (*compare)(void*, void*)) {
	if (l->size > 0) {
		void* minimum = l->array[0];
		for (int i = 1; i < l->size; i++) {
			if (compare(l->array[i], minimum) < 0) {
				minimum = l->array[i];
			}
		}
		return minimum;
	} else {
		return NULL;
	}
}

/**
 * Data una lista e una relazione d'ordine definita sui suoi elementi, la funzione
 * restitutisce l'elemento "massimo".
 * La relazione deve essere implementata come una funzione che prende in ingresso il contenuto di due nodi, 
 * e li confronta restituendo:
 * - un numero negativo se il primo dato è "minore" del secondo (stando alla relazione).
 * - 0 se i due dati sono considerati uguali dalla relazione d'ordine.
 * - un numero positivo se il primo dato è "maggiore" del secondo (stando alla relazione).
 */
void* al_getMaximumContent(arraylist* l, int (*compare)(void*, void*)) {
	if (l->size > 0) {
		void* maximum = l->array[0];
		for (int i = 1; i < l->size; i++) {
			if (compare(l->array[i], maximum) > 0) {
				maximum = l->array[i];
			}
		}
		return maximum;
	} else {
		return NULL;
	}
}

/**
 * Ordina una lista in modo <i>crescente</i> secondo una relazione d'ordine definita dall'utente e passata come parametro.
 * La relazione deve essere implementata come una funzione che prende in ingresso il contenuto di due nodi, 
 * e li confronta restituendo:
 * - un numero negativo se il primo dato è "minore" del secondo (stando alla relazione).
 * - 0 se i due dati sono considerati uguali dalla relazione d'ordine.
 * - un numero positivo se il primo dato è "maggiore" del secondo (stando alla relazione).
 */
void al_sortByOrder(arraylist* l, int (*compare)(void*, void*)) {
	// Implemento un lento e noioso BubbleSort
	for (int i = 0; i < l->size; i++) {
		for (int j = l->size - 1; j > i; j--) {
			if (compare(l->array[j], l->array[j - 1]) < 0) {
				void* aux = l->array[j];
				l->array[j] = l->array[j - 1];
				l->array[j -1] = aux;
			}
		}
	}
}

/**
 * Restituisce una stringa che rappresenta gli elementi contenuti all'interno della lista.
 * Per rappresentare ogni singolo elemento viene passata come parametro la funzione che converte in stringa il contenuto
 * di un elemento.
 */
char* al_listToString(arraylist* l, char* (*toStringFunction)(void*)) {
	// Alloco lo spazio necessario nella stringa di destinazione
	char* final_str = malloc((STRING_TITLE_LENGTH + 1) * sizeof(char));
	if (!final_str) {
		printf("OutOfMemoryError\n");
		exit(1);
	}
	sprintf(final_str, STRING_TITLE, l->size);
	char* aux_string = " ";
	for (int i = 0; i < l->size; i++) {
		aux_string = toStringFunction(l->array[i]);
		int new_length = strlen(final_str) + strlen(aux_string) + 2;
		final_str = realloc(final_str, new_length * sizeof(char));
		strcat(final_str, aux_string);
	}
	strcat(final_str, "\n");
	return final_str;
}

//////////////////////////////////////////////////////
// TESTING //


typedef struct {
	char first_letters[2];
	int three_numbers;
	char last_letters[2];
} string;


char getRandomChar() {
	return (char)((rand() % ('Z' - 'A')) + 'A');
}

string* initString() {
	string* new = malloc(sizeof(string));
	if (!new) {
		printf("ERRORE NULL");
	}
	new->first_letters[0] = getRandomChar();
	new->first_letters[1] = getRandomChar();
	new->three_numbers = rand() % 1000;
	new->last_letters[0] = getRandomChar();
	new->last_letters[1] = getRandomChar();
	return new;
}


char* stringifyMyStruct(void* my_object) {
	char* created_string = malloc(sizeof(char) * 13);
	sprintf(created_string, "[%c%c %03d %c%c] ", 
		((string*)my_object)->first_letters[0],
		((string*)my_object)->first_letters[1],
		((string*)my_object)->three_numbers,
		((string*)my_object)->last_letters[0],
		((string*)my_object)->last_letters[1]);
	return created_string;
}

int compareMyStruct(void* obj1, void* obj2) {
	return strcmp(
		stringifyMyStruct(((string*)obj1)), 
		stringifyMyStruct(((string*)obj2)));
}

bool hasEvenNumber(void* targa) {
	if (((string*)targa)->three_numbers % 2 == 0) {
		return true;
	} else {
		return false;
	}
}

#include <time.h>

int main(void) {
	arraylist* arr = al_initList();
	char* string_of_list;
	
	srand(time(NULL));
	
	int dim = 10;
	
	for (int i = 0; i < dim; i++) {
		al_insertElementLast(arr, initString());
	}
	
	// Stampo la lista
	string_of_list = al_listToString(arr, stringifyMyStruct);
	printf("%s\n", string_of_list);
	free(string_of_list);
	
	// Ordino la lista
	al_sortByOrder(arr, compareMyStruct);
	printf("Ho ordinato la lista\n\n");
	
	// Stampo la lista
	string_of_list = al_listToString(arr, stringifyMyStruct);
	printf("%s\n", string_of_list);
	free(string_of_list);
	
	// Elimino le targhe pari
	al_deleteElementsByConditions(arr, hasEvenNumber);
	printf("Elimino le targhe pari.\n\n");
	
	// Stampo la lista
	string_of_list = al_listToString(arr, stringifyMyStruct);
	printf("%s\n", string_of_list);
	free(string_of_list);
	
	// FREE
	al_purgeList(arr);
		
	return 0;
}
//////////////////////*/

