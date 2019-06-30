#include <stdio.h>
#include <malloc.h>
#include <string.h>

//----------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                  LISTA CIRCULARA SI ARBORE BINAR DE CAUTARE
//----------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct Film{
	char* titlu;
	int durata;
}Film;

Film createFilm(const char* titlu, int durata){
	Film f;
	f.titlu = (char*)malloc(sizeof(char)*(strlen(titlu) + 1));
	strcpy(f.titlu, titlu);
	f.durata = durata;

	return f;
}

void printFilm(Film f){
	printf("-> Filmul %s dureaza %d minute.\n", f.titlu, f.durata);
}

//lista simpla circulara
typedef struct Nod{
	Film info;
	Nod* next;
}Nod;

//inserare
Nod* insert(Nod* head, Film f){
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = f;

	if(head){
		nou->next = head;

		Nod* temp = head;
		while(temp->next != head){
			temp = temp->next;
		}

		temp->next = nou;

	}else{
		nou->next = nou;
	}

	return nou;
}

//afisare lista
void printList(Nod* head){
	if(head){
		Nod* temp = head->next;
		printFilm(head->info);

		while(temp != head){
			printFilm(temp->info);
			temp = temp->next;
		}
	}else{
		printf("There is no list to print\n");
	}
}

//functia care copiaza intr un vector doar filmele cu o lungine mai mare de 100 de min
Film* vectOfFilms(Nod* head, int value, int &size){
	if(head){
		size = 0;
		Nod* temp =  head->next;

		if(head->info.durata >= value){
			size++;
		}

		while(temp != head){
			if(temp->info.durata >= value){
				size++;
			}
			temp = temp->next;
		}

		Film* array = (Film*)malloc(sizeof(Film) * size);
		size = 0;
		temp = head->next;

		if(head->info.durata >= value){
			array[size++] = head->info;
		}

		while(temp != head){
			if(temp->info.durata >= value){
				array[size++] = temp->info;
			}
			temp = temp->next;
		}

		return array;
	}else{
		printf("There is no list.\n");
		Film* empty = (Film*)malloc(sizeof(Film)*0);
		return empty;
	}
}

//dezalocare mem lista circulara
void freeMem(Nod*& head){
	if(head){
		Nod* temp = head;
		while(temp->next != head){
			Nod* temp2 = temp->next;
			free(temp->info.titlu);
			free(temp);
			temp = temp2;
		}
		 free(temp->info.titlu);
		 free(temp);
		 head = NULL;

		printf("List successfuly freed.\n");
	}else{
		printf("There is no list to free.\n");
	}
}

//struct
typedef struct Nod_a{
	Film info;
	Nod_a* st;
	Nod_a* dr;
}Nod_a;

//inserare
Nod_a* insertArbore(Nod_a* root, Film f){
	if(root){
		if(root->info.durata > f.durata){
			root->st = insertArbore(root->st, f);
		}else{
			root->dr = insertArbore(root->dr, f);
		}

		return root;
	}else{
		Nod_a* nou = (Nod_a*)malloc(sizeof(Nod_a));
		nou->info = f;
		nou->st = NULL;
		nou->dr = NULL;	

		return nou;
	}

}

//copiere filme din lista in arbore //luam elementele din aceasta lista si le pune intr-un arbore binar de cautare
Nod_a* return_tree_from_list(Nod* head){
	if(head){
		Nod_a* root = NULL;
		Nod* temp = head;

		do{
			root = insertArbore(root, temp->info);
			temp = temp->next;
		}while(temp != head);

		return root;
	}else{
		return NULL;
	}
}

//parcurgere arborep
void inordine(Nod_a* root){
	if(root){
		inordine(root->st);
		printFilm(root->info);
		inordine(root->dr);
	}else{
	//	printf("There is no root, I am sorry.\n");
	}
}


int main(){
	Film f1 = createFilm("Avengers", 180);
	Film f2 = createFilm("How I met your mother", 20);
	Film f3 = createFilm("Game of thrones", 60);
	Film f4 = createFilm("Inchisoarea ingerilor", 160);
	Film f5 = createFilm("Tacerea mieilor", 120);
	Film f6 = createFilm("Inside out", 90);

	Nod* list = NULL;

	list = insert(list, f1);
	list = insert(list, f2);
	list = insert(list, f3);
	list = insert(list, f4);
	list = insert(list, f5);
	list = insert(list, f6);

	printList(list);

	printf("\nArray of films and tv show that are longer than 100 mins:\n");
	int size = 0;
	Film* array = vectOfFilms(list, 100, size);
	for(int i  = 0; i < size; i++){
		printFilm(array[i]);
	}
	//freeMem(list);
	//printList(list);

	Nod_a* root = NULL;
	//root = insertArbore(root, f1);
	//root = insertArbore(root ,f2);
	root = return_tree_from_list(list);
	printf("\n");
	inordine(root);
}