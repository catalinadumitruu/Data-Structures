#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Car{
	int id;
	char* brand;
	int year;
	float price;
	int number_of_owners;
	char** owners;
}Car;

Car createCar(int id, const char* brand, int year, float price, int nr, char**owners){
	Car c;
	c.id = id;

	c.brand = (char*)malloc(sizeof(char)*(strlen(brand) + 1));
	strcpy(c.brand, brand);

	c.year = year;
	c.price = price;
	c.number_of_owners = nr;

	c.owners = (char**)malloc(sizeof(char*)*nr);
	for(int i = 0; i < nr; i++){
		c.owners[i] = (char*)malloc(sizeof(char)*(strlen(owners[i]) + 1));
		strcpy(c.owners[i], owners[i]);
	}

	return c;
}

Car read_car_from_file(FILE * file){
	Car car;
	fscanf(file, "%d", &car.id);

	char buffer[10];
	fscanf(file, "%s", buffer);
	car.brand = (char*)malloc(sizeof(char*)*(strlen(buffer) + 1));
	strcpy(car.brand, buffer);

	fscanf(file, "%d", &car.year);
	fscanf(file, "%f", &car.price);
	fscanf(file, "%d", &car.number_of_owners);

    car.owners = (char**)malloc(sizeof(char*)*car.number_of_owners);
	for(int i = 0; i < car.number_of_owners; i++){
		char buffer1[10] = "";
		fscanf(file, "%s", buffer1);
		car.owners[i] = (char*)malloc(sizeof(char)*(strlen(buffer1) + 1));
		strcpy(car.owners[i], buffer1);
	}

	return car;
}

void printCar(Car c){
 	printf("< %d > This car is %s from %d (year), it is %.2f Euros and it had %d owners so far: \n", c.id, c.brand, c.year, c.price, c.number_of_owners);
 	for(int i = 0; i < c.number_of_owners; i++){
 		printf("-->> %s\n", c.owners[i]);
 	}
 	printf("\n");
}

typedef struct Nod{
	Car info;
	Nod* st;
	Nod* dr;
}Nod;


Nod* insert(Nod* root, Car c){
	if(root){
		if(root->info.id > c.id){
			root->st = insert(root->st, c);
		}else{
			root->dr = insert(root->dr, c);
		}

		return root;
	}else{
		//daca nu avem arbore sau daca am gasit spatiu gol de inserat
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = c;
		nou->st = NULL;
		nou->dr = NULL;

		return nou;
	}
}

void printNodes_INorder(Nod* root){
	if(root){
		printNodes_INorder(root->st);
		printCar(root->info);
		printNodes_INorder(root->dr);
	}
}

void printNodes_PREorder(Nod* root){
	if(root){
		printCar(root->info);
		printNodes_PREorder(root->st);
		printNodes_PREorder(root->dr);
	}
}


void printNodes_POSTorder(Nod* root){
	if(root){
		printNodes_POSTorder(root->st);
		printNodes_POSTorder(root->dr);
		printCar(root->info);
	}
}

Car search(Nod* root, int id){
	if(root){
		if(root->info.id == id){
			return root->info;
		}else if(root->info.id > id){
			return search(root->st, id);
		}else{
			return search(root->dr, id);
		}
	}else{
		return createCar(0, "", 0, 0, 0, NULL);
	}
}

// DELETE A NODE 
Nod* minValue_from_rightTree(Nod* node){
	Nod* current = node;

	while(current && current->st != NULL){
		current = current->st;
	}

	return current;
}

Nod* deleteNode(Nod* root,int id){
 	
 	if(root == NULL) return root;

 	if(root->info.id < id){
 		root->dr = deleteNode(root->dr, id);
 	}else if(root->info.id > id){
 		root->st = deleteNode(root->st, id);
 	}else{
 		//inseamna ca suntem pe nodul pe care trebuie sa l stergem -> avem 2 situatii

 		//cazul 1 & 2
 		if(root->st == NULL){
 			Nod* temp =  root->dr;
 			free(root);
 			return temp;
 		}
 		if(root->dr == NULL){
 			Nod* temp = root->st;
 			free(root);
 			return temp;
 		}

 		Nod* temp = minValue_from_rightTree(root->dr);
 		root->info = temp->info;

 		root->dr = deleteNode(root->dr, temp->info.id);
 	}

 	return root;
}

//inaltimea arborelui -> calculam inaltimea in dr si st si o returnam pe cea mai mare
int height(Nod* root){
	if(root){

		int height_st = height(root->st);
		int height_dr = height(root->dr);

		return 1 + (height_dr > height_st ? height_dr : height_st);

	}else{
		return 0;
	}
}

//afisare elemente de pe un anumit nivel
void afisare_pe_nivel(Nod* root, int nivel_curent, int nivel_dorit){
	if(root){

		if(nivel_dorit == nivel_curent){
			printCar(root->info);
		}else{
			afisare_pe_nivel(root->st, nivel_curent + 1, nivel_dorit);
			afisare_pe_nivel(root->dr, nivel_curent + 1,nivel_dorit);
		}
	}
}

//sa se returneze doar masinile care au o vechime mai mare de 7 ani
int vechime(Car c){
	return 2019 - c.year;
}

void afisare_conditionata(Nod* root){

	if(root){
		afisare_conditionata(root->st);

		if(vechime(root->info) > 10) {
			printCar(root->info);
			printf("Vechime: %d", vechime(root->info));
		}

		afisare_conditionata(root->dr);
	}else{
		printf("There is no binary search tree to be displayed");
	}
}

int inaltime_arbore(Nod* root){
	if(root){
		int inaltime_st = inaltime_arbore(root->st);
		int inaltime_dr = inaltime_arbore(root->dr);

		return 1 + (inaltime_st > inaltime_dr ? inaltime_st : inaltime_dr);
	}else{
		return 0;
	}
}

int grad_echilibru(Nod* root){

	return inaltime_arbore(root->st) - inaltime_arbore(root->dr);
}

Nod* rotire_la_dreapta(Nod* root){
	if(root){
		Nod* temp = root->st;
		root->st = temp->dr;
		temp->dr = root;
		return temp;
	}else{
		return root;
	}
}

Nod* rotire_la_stanga(Nod* root){
	if(root){
		Nod* temp = root->dr;
		root->dr = temp->st;
		temp->st = root;
		return temp;
	}else{
		return root;
	}
}

Nod* insert_echilibrat(Nod* root, Car c){
	if(root){
		if(root->info.id > c.id){
			root->st = insert_echilibrat(root->st, c);
		}

		if(root->info.id < c.id){
			root->dr = insert_echilibrat(root->dr, c);
		}

		if(grad_echilibru(root) == 2){  //dezechilibru in stanga
			if(grad_echilibru(root->st) != 1){
				root->st = rotire_la_stanga(root->st);
			}
			root = rotire_la_dreapta(root);
		}

		if(grad_echilibru(root) == -2){  //dezechilibru in dreapta
			if(grad_echilibru(root->dr) != -1){
				root->dr = rotire_la_dreapta(root->dr);
			}
			root = rotire_la_stanga(root);
		}
		return root;
	}else{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = c;
		nou->st = NULL;
		nou->dr = NULL;

		return nou;
	}
}

int main(){
	FILE* file = fopen("masini.txt", "r");
	int no_of_cars = 0;
    fscanf(file, "%d", &no_of_cars);

    // printf("\nThere are %d elements in the file:\n\n", no_of_cars);
    // for(int i = 0; i < no_of_cars; i++){
    // 	printCar(read_car_from_file(file));
    // }

    Nod* root = NULL;

    for(int i = 0; i < no_of_cars; i++){
    	root = insert_echilibrat(root, read_car_from_file(file));
    }

    printf("Our binary search tree is:\n");
    printNodes_PREorder(root);

    printf("\nAfiseaza nodul cu id-ul 4040:\n");
    Car c = search(root, 4040);
    printCar(c);

    printf("\n Delete the car with the code 5050:\n");
    root = deleteNode(root, 5050);
    printNodes_PREorder(root);

    printf("\nThe height of our binary tree is %d.\n", height(root));

    printf("\nThe elements on the 2nd level are: \n");
    afisare_pe_nivel(root, 0, 2);

    printf("\nPrint the elements older than 10 years:\n");
    afisare_conditionata(root);
}