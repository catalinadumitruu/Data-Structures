#include <stdio.h>
#include <string.h>
#include <malloc.h>

//structura
typedef struct Message{
	int priority;
	char* message;
}Message;

Message createMessage(int priority, const char* message){
	Message m;
	m.priority = priority;
	m.message = (char*)malloc(sizeof(char)*(strlen(message) + 1));
	strcpy(m.message, message);

	return m;
}

void printMessage(Message m){
	printf("%d -> %s.\n", m.priority, m.message);
}

typedef struct Heap{
	Message* vect;
	int dim;
}Heap;


void printHeap(Heap h){
	if(h.dim > 0){
		for(int i = 0; i < h.dim; i++){
			printMessage(h.vect[i]);
		}
	}else{
		printf("There is no heap to display.\n");
	}
}

//filtrare
void filtrare(Heap h, int pozitie){
	int fiuS = 2 * pozitie + 1;
	int fiuD = 2 * pozitie + 2;
	int max = pozitie;

	if(h.vect[fiuS].priority > h.vect[max].priority && fiuS < h.dim){
		max = fiuS;
	}

	if(h.vect[fiuD].priority > h.vect[max].priority && fiuD < h.dim){
		max = fiuD;
	}

	if(max != pozitie){
		Message temp = h.vect[pozitie];
		h.vect[pozitie] = h.vect[max];
		h.vect[max] = temp;

		if(2 * max + 1 < h.dim){
			filtrare(h, max);
		}	
	}
}

//extragere nod
Message popMessage(Heap &heap){
	if(heap.dim > 0){
		Message result = heap.vect[0];
		Message* temp = (Message*)malloc(sizeof(Message)*(heap.dim -1));

		for(int i = 1; i < heap.dim; i++){
			temp[i-1] = heap.vect[i];
		}

		free(heap.vect);
		heap.vect = temp;
		heap.dim--;

		for(int i = (heap.dim - 2)/2; i >= 0; i--){
			filtrare(heap, i);
		}

		return result;

	}else{
		printf("There is no heap structure \n");
		return createMessage(-1, "");
	}
}

//inserare nod
void pushMessage(Heap& heap, Message m){
	if(heap.dim >= 0){
 		Message* temp = (Message*)malloc(sizeof(Message)*(heap.dim + 1));

 		for(int i = 0; i< heap.dim; i++){
 			temp[i] = heap.vect[i];
 		}

 		temp[heap.dim] = m;
 		free(heap.vect);
 		heap.vect = temp;
 		heap.dim++;

 		for(int i = (heap.dim - 2)/2; i >= 0; i--){
 			filtrare(heap, i);
 		}
	}
}

//functie care sa extraga si sa aafiseze mesajele cu o prioritate mai mare decat cea prim ca param
void parcurgereConditionata(Heap heap, int prioritate){
	if(heap.dim > 0){
		for(int i = 0; i < heap.dim; i++){
			if(heap.vect[i].priority > prioritate){
				printMessage(heap.vect[i]);
			}
		}
	}
}

int main(){

	Message m1 = createMessage(1, "Hello, how are you? how do you feel?");
	Message m2 = createMessage(2, "Hei, I have something important to tell you.");
	Message m3 = createMessage(3, "25 calls missed");
	Message m4 = createMessage(9, "Call me right now");
	Message m5 = createMessage(5, "It s kind of urgent");

	Heap heap;
	heap.dim = 5;

	heap.vect = (Message*)malloc(sizeof(Message) * heap.dim);
	heap.vect[0] = m1;
	heap.vect[1] = m5;
	heap.vect[2] = m4;
	heap.vect[3] = m2;
	heap.vect[4] = m3;

	printHeap(heap);

	for(int i = (heap.dim - 2)/2; i >= 0; i--){
		filtrare(heap, i);
	}

	printf("Heap after filter:\n");
	printHeap(heap);

	printf("\n\nAdding 2 more messages:\n");
	pushMessage(heap, createMessage(18, "Mesaj nou"));
	pushMessage(heap, createMessage(10, "ALta mesaj"));
	printHeap(heap);

	printf("\n\n Pop a message: ");
	Message msj = popMessage(heap);
	printMessage(msj);

	printf("\n\nThe heap after pop up: \n");
	printf("\n");
	printHeap(heap);

	printf("\n\nParcurgere conditionata\n");
	parcurgereConditionata(heap, 8);
}