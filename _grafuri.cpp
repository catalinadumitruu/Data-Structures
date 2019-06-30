#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Facultate{
	int id;
	char* nume;
}Facultate;

void printFacultate(Facultate f){
	printf(" << %d >> Facultatea %s.\n", f.id, f.nume);
}

struct nodListaSecundara;

typedef struct nodListaPrincipala{
	Facultate info;
	nodListaPrincipala* next;
	nodListaSecundara* vecini;
}nodListaPrincipala;

typedef struct nodListaSecundara{
	nodListaPrincipala* info;
	nodListaSecundara* next;
}nodListaSecundara;

nodListaSecundara* adauga_lista_secundara(nodListaSecundara* head, nodListaPrincipala* info){ //adaugam la final in lista simplu inlantuita
	nodListaSecundara* nou = (nodListaSecundara*)malloc(sizeof(nodListaSecundara));
	nou->info = info;
	nou->next = NULL;

	if(head){
		nodListaSecundara* temp = head;

		while(temp->next){
			temp = temp->next;
		}

		temp->next = nou;
	}else{
		head = nou;
	}

	return head;
}

void printListaSecundara(nodListaSecundara* head){
	if(head){
		nodListaSecundara* temp = head;

		while(temp){
			printFacultate(temp->info->info);
			temp = temp->next;
		}
	}else{
		printf("Nu exista o lista secundara pe care sa o printam.\n");
	}
}

nodListaPrincipala* adauga_lista_principala(nodListaPrincipala* head, Facultate f){
	nodListaPrincipala* nou = (nodListaPrincipala*)malloc(sizeof(nodListaPrincipala));
	nou->info = f;
	nou->next = NULL;
	nou->vecini = NULL;

	if(head){
		nodListaPrincipala* temp = head;

		while(temp->next){
			temp = temp->next;
		}

		temp->next = nou;
	}else{	
		head = nou;
	}

	return head;
}

void printListaPrincipala(nodListaPrincipala* head){
	if(head){
		nodListaPrincipala* temp = head;

		while(temp){
			printf("**** %d *****  Facultatea %s are vecinii:\n", temp->info.id, temp->info.nume);
			printListaSecundara(temp->vecini);
			temp = temp->next;
		}
	}else{
		printf("Nu exista o lista principala pe care sa o afisam.\n");
	}
}

nodListaPrincipala* cauta_nod_in_graf_dupa_id(nodListaPrincipala* graf, int id){
	if(graf){
		nodListaPrincipala* temp = graf;

		while(temp && temp->info.id != id){
			temp = temp->next;
		}

		return temp;
	}else{
		return NULL;
	}
}

void adaugare_arce(nodListaPrincipala*graf, int idStart, int idStop){
	if(graf){
		nodListaPrincipala* nodStart = cauta_nod_in_graf_dupa_id(graf, idStart);
		nodListaPrincipala* nodStop = cauta_nod_in_graf_dupa_id(graf, idStop);

		if(nodStop && nodStart){
			nodStart->vecini = adauga_lista_secundara(nodStart->vecini, nodStop);
			nodStop->vecini = adauga_lista_secundara(nodStop->vecini, nodStart);
		}
	}
}

// --------------------------------------------------------------
//     PARCURGERE IN ADANCIME
// --------------------------------------------------------------
int nr_noduri_din_graf(nodListaPrincipala* graf){
	if(graf){
		nodListaPrincipala* temp = graf;
		int count = 0;

		while(temp){
			count++;
			temp = temp->next;
		}

		return count;
	}else{
		return 0;
	}
}

typedef struct nodStiva{
	int id;
	nodStiva* next;	
}nodStiva;

//push si pop la acelasi capat -> la inceput
nodStiva* push(nodStiva* head, int id){
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->id = id;
	if(head){
		nou->next = head;
	}else{
		head = nou;
	}

	return head;
}

int pop(nodStiva*& head){
	if(head){
		int id = head->id;
		nodStiva* temp = head;
		head = head->next;

		free(temp);
		return id;
	}else{
		return -1;
	}
}

void parcurgere_DFS(nodListaPrincipala* graf, int idNodStart){
	if(graf){
		nodStiva* stiva = NULL;

		int nr_noduri = nr_noduri_din_graf(graf);
		//printf("\nsunt %d noduri in graf\n", nr_noduri);
		int* vizitat = (int*)malloc(sizeof(int)*nr_noduri);
		for(int i = 0; i < nr_noduri; i++){
			vizitat[i] = 0;
		}

		stiva = push(stiva, idNodStart);
		vizitat[idNodStart] = 1;

		while(stiva){		
			int idCurent = pop(stiva);
			nodListaPrincipala* nodCurent = cauta_nod_in_graf_dupa_id(graf, idCurent);
			printFacultate(nodCurent->info);
			//printf(" << %d >> Facultatea %s.\n", nodCurent->info.id, nodCurent->info.nume);
			nodListaSecundara* vecini = nodCurent->vecini;

			while(vecini){
				if(vizitat[vecini->info->info.id] == 0){
					stiva = push(stiva, vecini->info->info.id);
					vizitat[vecini->info->info.id] = 1;
				}
				vecini = vecini->next;
			}
		}
	}
}

int main(){

	nodListaPrincipala* graf = NULL;
	int nr_noduri_graf = 0;
	printf("Numar noduri graf: "); scanf("%d", &nr_noduri_graf);

	for(int i = 0; i < nr_noduri_graf; i++){
		Facultate f;
		int id = 0;
		printf("Id-ul facultatii: "); scanf("%d" , &id);
		f.id = id;

		char buffer[20];
		printf("Numele facultatii: "); scanf("%s", buffer);
		f.nume = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
		strcpy(f.nume, buffer);

		graf = adauga_lista_principala(graf, f);
	}

	//printListaPrincipala(graf);

	int nr_arce = 0;
	printf("Numarul de arce: "); scanf("%d", &nr_arce);

	for(int i = 0; i < nr_arce; i++){
		int idNodStart = 0;
		printf("Nod start: "); scanf("%d", &idNodStart);

		int idNodStop = 0;
		printf("Nod stop: "); scanf("%d", &idNodStop);

		adaugare_arce(graf, idNodStart, idNodStop);
	}

	printListaPrincipala(graf);
	printf("\nParcurgere DFS:\n");
	parcurgere_DFS(graf, 1);
}