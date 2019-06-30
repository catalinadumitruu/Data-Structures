#include <stdio.h>
#include <malloc.h>
#include <string.h>

//----------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                            LINEAR PROBING
//----------------------------------------------------------------------------------------------------------------------------------------------------------

//strctura de baza
typedef struct Za{
     int cod;
     char* material;
     int diametru;
}Za;  

Za* createZa(int cod, const char* material, int diametru){
	Za* z = (Za*)malloc(sizeof(Za));
	z->cod = cod;
	z->material = (char*)malloc(sizeof(char)*(strlen(material) + 1));
	strcpy(z->material, material);
	z->diametru = diametru;

	return z;
}

void printZa(Za za){
	printf("Za nr %d este din %s si are un diametru de %d.\n", za.cod, za.material, za.diametru);
}

//strcutura hash
typedef struct hashTable{
	Za** vect;
	int dim;
}hashTable;


hashTable initializeHashTable(int dim){
	hashTable ht;
	ht.dim = dim; 
	ht.vect = (Za**)malloc(sizeof(Za*)*dim);
	for(int i = 0; i < dim; i++){
		ht.vect[i] = NULL;
	}

  return ht;
}

//afisare hashTable
void printHashTable(hashTable ht){
	if(ht.dim > 0){
         for(int i = 0; i < ht.dim; i++){
         	if(ht.vect[i] != NULL){
         		printZa(*ht.vect[i]);
         	}
         }
	}else{
		printf("There is no initialized hashTabe.\n");
	}
}

// calculam functia hash
int hashFunction(hashTable hashTable, Za z){
  int result;
    for(int i = 0; i < strlen(z.material); i++){
         result += z.material[i];
    }

    return result % hashTable.dim;
}

//inseram un element
int insertElement(hashTable ht, Za* za){
	if(ht.dim > 0){
			int position = hashFunction(ht, *za);

			if(ht.vect[position] != NULL){
					int index = (position + 1) % ht.dim;

					while(ht.vect[index] != NULL && position != index){
						index = (index + 1) % ht.dim;
					}

					if(index == position){
						printf("There couldn't be found any spot to introduce the element with code %d.\n", za->cod);
						return -2;
					}else{
						ht.vect[index] = za;
						return index;
					}
			}else{
				ht.vect[position] = za;
				return position;
			}
	}else{
		printf("There is no hashTable, I am sorry.\n");
		return -1;
	}
}


//cautam un element in hashTable
int searchZa(hashTable ht, Za *za){
	if(ht.dim > 0){
		int position = hashFunction(ht, *za);

		if(ht.vect[position]->cod == za->cod){
			return position;
		}else{
			int index = position;

			do{ 
				index = (index + 1) % ht.dim;

				if(ht.vect[index]-> cod == za->cod){
					break;
				}

			}while(index != position);

			if(index == position){
				return -2;
				printf("Couldn't find the element.\n");
			}else{
				return index;
			}
		}

	}else{
		printf("There is no hashTable.\n");
		return -1;
	}
}

//extrage un element din hastable
Za* deleteAnElement(hashTable &ht, int pozitie){
    if(ht.dim > 0){
    	if( pozitie >= 0 && pozitie < ht.dim){
    		if(ht.vect[pozitie] != NULL){
    			Za* z = ht.vect[pozitie];
    			ht.vect[pozitie] =  NULL;
                return z;
    		}
    	}

    }else{
    	printf("There is no hashTable.\n");
    	return createZa(0, "", 0);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                            CHAINING
//----------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct Client{
	char* name;
	int age;
	float salary;
}Client;

Client* createClient (const char* name, int age, float salary) {
	Client* c = (Client*)malloc(sizeof(Client));
	c->age = age;
	c->salary = salary;
	c->name = (char*)malloc(sizeof(char)*(strlen(name) + 1));
	strcpy(c->name, name);

	return c;
}

void printClient(Client c) {
	printf("  ->  %s is %d years old and has a salary of %5.2f RONs.\n", c.name, c.age, c.salary);
}

typedef struct Nod{
	Client info;
	Nod* next;
}Nod;

//inserare la sf in lista simpla
Nod* add_in_list(Nod* head, Client c){
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
    nou->next = NULL;
	if(head){
        Nod* temp = head;

        while(temp->next){
        	temp = temp->next;
        }

        temp->next = nou;

	}else{
		head = nou;
	}

	return head;
}

int hashFunction1(Nod** hashTable, int size, Client* c ){

	int result = 0;
	for(int i = 0; i < strlen(c->name); i++){
		result += c->name[i];
	}

	return result % size;
}

void insertInHashTable(Nod** ht, int size, Client *c){
	if(size > 0){
		int hashCode = hashFunction1(ht,size,c);
		ht[hashCode] = add_in_list(ht[hashCode], *c);
	}else
	{
		printf("There is no hashTable.\n");
	}
}


void printHashTable_chaining(Nod** ht, int size){
	if(size > 0){
		for(int i = 0; i < size; i++){
			if(ht[i] != NULL){
				printf("List number: %d\n", i+1);
				Nod* temp = ht[i];

				while(temp){
					printClient(temp->info);
					temp = temp->next;
				}
			}
		}
	}else{
		printf("There is no hashTable.\n");
	}
}

int hashFunction_string(Nod** ht, int size, const char* name){
	int result = 0;
	for(int i = 0; i < strlen(name); i++){
		result += name[i];
	}

	return result % size;
}

//search element after name
Client searchClinet(Nod** ht, int size, const char* name){
	if(size > 0){
		int hashCode = hashFunction_string(ht, size, name);

		Nod* temp = ht[hashCode];

		while(temp){
			if(strcmp(temp->info.name, name) == 0){
				return temp->info;
			}
			temp = temp->next;
		}
	}else{
		printf("There is no hashTable.\n");
		return *createClient("", 0, 0);
	}
}

//delete element after name
void deleteFromHashTable(Nod**&ht, int size, const char* name){
	if(size > 0){
		int hashCode = hashFunction_string(ht, size, name);

		Nod* temp = ht[hashCode];
       // Nod* for_delete = NULL;

		while(temp){
            if(strcmp(temp->info.name, name) == 0){
            	Nod* aux = ht[hashCode];
            	while(aux->next != temp){
            		aux = aux->next;
            	}
                
                aux->next = temp->next;
                free(temp->info.name);
                free(temp);
            }
            temp = temp->next;
		}
	}else{
		printf("There is no hashTable!\n");
	}
}

int main(){

	printf("\n\n ----------------  LINERAR PROBING ----------------\n\n");
	Za* z1 = createZa(10, "argint", 3);
	Za* z2 = createZa(79, "otel", 1);
	Za* z3 = createZa(10, "aur", 1);
	Za* z4 = createZa(4, "otel", 2);
	Za* z5 = createZa(52, "argint", 2);

    hashTable hashTable;
    int dim = 4;
    hashTable = initializeHashTable(dim);

    insertElement(hashTable, z1);
    insertElement(hashTable, z2);
    insertElement(hashTable, z3);
    insertElement(hashTable, z4);
    insertElement(hashTable, z5);

    printHashTable(hashTable);

    printf("\nLooking for the element: "); printZa(*z3);
    printf("Se afla po pozitia: %d.\n", searchZa(hashTable, z3));

    printf("\nExtragem din hashTable elementul de pe pozitia 2: ");
    Za* z = deleteAnElement(hashTable, 2);
    printZa(*z);
    printf("\n");
    printHashTable(hashTable);

    printf("\n\n ----------------  CHAINING ----------------\n\n");
    Client* c1 = createClient("Anto", 21, 9000);
    Client* c2 = createClient("Dana", 49, 8900);
    Client* c3 = createClient("Adelin", 25, 9999);
    Client* c4 = createClient("Lidia", 20, 1475);
    Client* c5 = createClient("Diana", 19, 100);

    int size = 2;
    Nod** ht = (Nod**)malloc(sizeof(Nod*));
    for(int i = 0; i < size; i++){
         ht[i] = 0;
    }

    insertInHashTable(ht, size, c1);
    insertInHashTable(ht, size, c2);
    insertInHashTable(ht, size, c3);
    insertInHashTable(ht, size, c4);
    insertInHashTable(ht, size, c5);

    printHashTable_chaining(ht,size);

    printf("\n Cauta si afiseaza clientul cu numele Lidia:\n");
    Client c = searchClinet(ht, size, "Lidia");
    printClient(c);

    printf("\nDelete Diana from hashTable.\n");
    deleteFromHashTable(ht, size, "Diana");
    printHashTable_chaining(ht,size);

}