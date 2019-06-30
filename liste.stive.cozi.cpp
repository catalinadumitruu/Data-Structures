#include <stdio.h>
#include <string.h>
#include <malloc.h>

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                             SINGLE LINKED LIST
// -----------------------------------------------------------------------------------------------------------------------------------------------------------


//structura Book
typedef struct Book {
	char* title;
	char* author;
	float price;
	int noPages;
}Book;

Book createBook(const char* title, const char* author, float price, int no) {
	Book book;

	book.title = (char*)malloc(sizeof(char)*(strlen(title) + 1));
	strcpy(book.title, title);

	book.author = (char*)malloc(sizeof(char)*(strlen(author) + 1));
	strcpy(book.author, author);

	book.price = price;
	book.noPages = no;

	return book;
}

void printBook(Book b) {
	printf("The book %s is written by %s, it is %.2f RONs and has %d pages.\n", b.title, b.author, b.price, b.noPages);
}

typedef struct Nod {
	Book info;
	Nod* next;
}Nod;

Nod* createNode(Nod* next, Book b) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = b;
	nou->next = next;

	return nou;
}

void printList(Nod* head) {
	
	if(head){
		while (head) {
		   printBook(head->info);
		   head = head->next;
	    }
    } else {
    	printf("Nu avem lista.\n");
    }
}

//inserare la sfarsit
Nod* insertEnd(Nod* head, Book b) {
	Nod* nou = createNode(NULL, b);

	if (head) {
		Nod* temp = head;
		while (temp->next) {
			temp = temp->next;
		}

		temp->next = nou;
	}
	else {
		head = nou;
	}

	return head;
}


//inserare la inceput
Nod* insertBegging(Nod* head, Book b){
	Nod* nou = createNode(NULL, b);
	nou->next = head;
	head = nou;

	return nou;
}


//inserare INAINTEA unui nod -> daca sunt mai multe cu acelasi titlu, inaintea nodului cu cartea mai ieftina
Nod* insertBefore(Nod* head, Book b, const char* title){
	Nod* nou = createNode(NULL, b);

	if(head){
          
          Nod* temp = head;
          Nod* minPrice = NULL;
          
            while(temp){
              if(temp->next && strcmp(temp->next->info.title, title) == 0){
                    if(minPrice == NULL){
                       minPrice = temp;
                    }

                    if(minPrice->info.price > temp->next->info.price){
                    	minPrice =  temp;
                    }
                }

              temp = temp->next;
            }

        // if(minPrice-> next == NULL){
        //   	if(strcmp(minPrice->info.title, title) == 0){
        //   		head = insertEnd(head, b);
        //   	} else {
        //         printf("Sorry, but I couldn t find the given title in my list.\n");
        //   	}
        // } else {
             
        //      //verificam daca e pe primul nod pretul min si inseram acolo daca e cazul -> temp verifica de la temp->next
        //         if(strcmp(head->info.title, title) == 0){
        //               if(head->info.price < minPrice->info.price){
        //               	 head = insertBegging(head,b);
        //               	 return head;
        //               }
        //         }
        //      	//daca nu e pe primul nod se executa urmatoarea secventa

        //         temp->next = nou;
        //         nou->next = temp->next;
        //     }

            if(minPrice != NULL) {
            	printf("Inseram in interior.");
            	 nou->next = minPrice->next;
            	 minPrice->next = nou;

            }else{
            	if(strcmp(head->info.title, title) == 0){
            		head = insertBegging(head, b);
            		return head;
            	}else {
            		printf("Sorry, but I couldn t find the given title in my list.\n");
            	}
            }
	}else {

		head =  nou;
	}

	return head;
}


//inserare DUPA primul nod gasit cu numele dat
Nod* insertAfter(Nod* head, Book b, const char* title){

    Nod* nou = createNode(NULL, b);

    if(head){
        Nod* temp = head;
        Nod* insertHere = NULL;
        while(temp && strcmp(temp->info.title, title) != 0){
        	// if(strcmp(temp->info.title, title) == 0){
        	// 	insertHere = temp;
        	// }
        	temp = temp->next;
        }

        // if(insertHere == NULL){
        // 	printf("Sorry, but I couldn t find the given title in my list.\n");
        // }else{
        // 	nou->next = insertHere->next;
        // 	insertHere->next = nou;
        // }
      
        if(temp == head) {
        	if(strcmp(head->info.title, title) != 0){
        	      printf("Sorry, but I couldn t find the given title in my list.\nI will insert it at the begging.\n");
        	      head = insertBegging(head, b);
        	      return head;
            }else {
            	 nou->next = temp->next;
                 temp->next = nou;
            }
        }else{
           nou->next = temp->next;
           temp->next = nou;
        }
    } else {
     	head = nou;
    }

  return head;
}


//nr mediu de pagini
float avgPages(Nod* head){
	int number_of_nodes = 0;
	int sum = 0;

	if(head){
		Nod* temp = head;

		while(temp){
			number_of_nodes++;
			sum += temp->info.noPages;
			temp = temp->next;
		}
		return sum / number_of_nodes;
	}else{
		return 0.0;
	}

}

//dezalocare
void freeMem(Nod* &head){
	
	if(head){
        while(head){
		   Nod*temp = head;
		   head = head->next;
		   free(temp->info.title);
		   free(temp->info.author);
		   free(temp);
	    }
	}
}

//cautare nod dupa un criteriu -> dupa numele dat
Book searchBook(Nod* head, const char* title){
    
    if(head){
    	Nod* temp = head;

    	while(temp && strcmp(temp->info.title, title) != 0){
    		temp = temp->next;
    	}

    	if(temp != NULL){
    		return temp->info;
    	}else return createBook("","", 0.0, 0);
    }else printf("Nu avem lista, imi pare rau.\n");
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                            DOUBLY LINKED LIST
// -----------------------------------------------------------------------------------------------------------------------------------------------------------


//structura
typedef struct Exam{
    char* teacher;
    char* subject;
    int hour;
    float grade;
}Exam;

Exam createExam(const char* teacher, const char* subject, int hour, float grade){
	Exam e;
	e.teacher = (char*)malloc(sizeof(char)*(strlen(teacher) + 1));
	strcpy(e.teacher, teacher);

	e.subject = (char*)malloc(sizeof(char)*(strlen(subject) + 1));
	strcpy(e.subject, subject);

	e.hour = hour;
	e.grade = grade;

	return e;
}

void printExam(Exam e){
	printf("The exam for the subject: %s (course held by teacher %s) will be at %d o'clock and the max grade will be %.2f.\n", e.subject, e.teacher, e.hour, e.grade);
}

typedef struct DNode{
   Exam info;
   DNode* next;
   DNode* prev;
}DNode;

typedef struct Node{
   DNode* first;
   DNode* last;
}Node;

DNode* createDNode(DNode* prev, DNode* next, Exam e){
	DNode* nou = (DNode*)malloc(sizeof(DNode));
	nou->info = e;
	nou->next = next;
	nou->prev = prev;

	return nou;
}

void printDNode(Node list, int flag){

	if(list.first){
		if(flag == 0){
			DNode* temp = list.first;

			while(temp){
				printExam(temp->info);
				temp = temp->next;
			}
		}else if (flag == 1){
			DNode* temp = list.last;
  
            while(temp){
            	printExam(temp->info);
            	temp = temp->prev;
            }
		}
	}else{
		printf("Nu avem o lista dubla.\n");
	}
}

//adaugare inceput
Node addBegging(Node list, Exam e){
	DNode* nou = createDNode(NULL,list.first,e);
	if(list.first){
		nou->next = list.first;
		list.first->prev = nou;
		list.first = nou;
	}else{
		list.first = nou;
		list.last = nou;
	}

	return list;
}

//adaugare final
Node addEnd(Node list, Exam e){
	DNode* nou = createDNode(list.last, NULL, e);
	if(list.last){
       nou->prev = list.last;
       list.last->next = nou;
       list.last = nou;
	}else{
       list.last = nou;
       list.first = nou;
	}

	return list;
}

//adaugare interior
// INAINTE DE UN NOD DAT -> daca sunt 2 examene la aceiasi materie, inainte de cea care are sanse mai mare de trecere => nota max mai mare
Node addBefore(Node list, Exam e, const char* subject){
   DNode* nou = createDNode(NULL, NULL, e);

   if(list.first){

        DNode* temp = list.first;
        DNode* insert = list.first;

        while(temp){
        	if(temp && strcmp(temp->info.subject, subject) == 0){
        		if(insert->info.grade < temp->info.grade){
        			insert = temp;
        		}
        	}
        	temp = temp->next;
        }

        if(insert == list.first){
        	if(strcmp(insert->info.subject, subject) == 0){
        		list = addBegging(list, e);
        	}else{
        		printf("I couldn't find the given node. The insertion will be by default at the end of the list.\n");
        		list = addEnd(list, e);
        	}
        }else{
        	nou->next = insert;
        	nou->prev = insert->prev;
        	insert->prev->next = nou;
        	insert->prev = nou;
        }
   }else{
   	list.first = nou;
   	list.last = nou;
   }

   return list;
}

//ADD AFTER
Node addAfter(Node list, Exam e, const char* subject){
	DNode* nou =  createDNode(NULL, NULL, e);

      if(list.first){
            
            DNode* temp = list.first;
            DNode* insert = list.first;

            while(temp){
            	if(temp && strcmp(temp->info.subject, subject) == 0){
            		//if(insert->info.grade < temp->info.grade){
            			insert = temp;
            		//}
            	}
            	temp = temp->next;
            }
           // printf("Nodul dupa care adaugam: "); printExam(insert->info);

            if(insert->next == NULL){
            	if(strcmp(insert->info.subject, subject) == 0){
                      list = addEnd(list, e);
            	}else{
            		printf("I couldn't find the given node. The insertion will be by default at the begging of the list.\n");
            		list = addBegging(list, e);
            	}
            }else{
            	nou->next = insert->next;
            	nou->prev = insert;
            	insert->next->prev = nou;
            	insert->next = nou;
            }

      }else{
      	list.first = nou;
      	list.last = nou;
      }

    return list;
}

//extrage un nod
Exam searchExam(Node list, const char* subject){
	if(list.first){

         DNode* temp = list.first;
         Exam result = createExam("", "", 0, 0);
         DNode* extragere = NULL;

        while(temp){
             if(temp && strcmp(temp->info.subject, subject) == 0){
             	result = temp->info; 
             	extragere = temp;
             }
             temp = temp->next;
        }
         
         //legam nodurile astfel incat sa l excludem pe cel extras
        if(extragere == NULL){
        	printf("The node is not in our list.\n");
        }else{
            extragere->prev->next = extragere->next;
            extragere->next->prev = extragere->prev;
            free(extragere);
        }
  
         return result;
	}else{
		return createExam("", "", 0, 0);
	}
}

//extrage dupa un criteriu -> dupa materie -> daca sunt mai multe examene la aceiasi materie -> vector
Exam* searchExams(Node list, const char* subject, int &i){

    i = 0;

	if(list.first){
		DNode* temp = list.first;

		while(temp){
			if(strcmp(temp->info.subject, subject) == 0){
				i++;
			}
			temp = temp->next;
		}

        Exam* array = (Exam*)malloc(sizeof(Exam)*i);
       // int j = i;
        i = 0;
        temp = list.first;

        while(temp){
        	if(strcmp(temp->info.subject, subject) == 0){
        		array[i++] = temp->info;
        	}
        	temp = temp->next;
        }

        return array;
	}else{
		printf("There is no list.\n");
	}
}

//dezalocare mem
void freeMemDoubly(Node list){
       if(list.first){
       	    while(list.first){
       	    	DNode* temp = list.first;
       	    	list.first = list.first->next;
       	    	free(temp->info.teacher);
       	    	free(temp->info.subject);
       	    	free(temp);
       	    }

       	    list.first = NULL;
       	    list.last = NULL;
       	    printf("List successfuly freed.\n");
       }else{
       	printf("There is no list.\n");
       }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                             CIRCULAR LINKED LIST - single linked list 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

//structura
typedef struct Client{
	int id;
    char* name;
    int age;
    float order;
}Client;

Client createClient(int id, const char* name, int age, float order){
	Client c; 
	c.id = id;
	c.age = age;
	c.order = order;
	c.name = (char*)malloc(sizeof(char)*(strlen(name) + 1));
	strcpy(c.name, name);

	return c;
}

void printClient(Client c){
   printf("<%d> Client %s is %d years old and the value of the order is %0.2f RONs.\n", c.id, c.name, c.age, c.order);
}

typedef struct CNode{
   Client info;
   CNode* next;
}CNode;

void printCList(CNode* head){
	if(head){
        CNode* temp = head->next;
        printClient(head->info);

        while(temp != head){
        	printClient(temp->info);
        	temp = temp->next;
        }
	}else{
		printf("There is no list to print.\n");
	}
}

//add inceput
CNode* add_begging(CNode* head, Client c){
    CNode* nou = (CNode*)malloc(sizeof(CNode));
    nou->info = c;

    if(head){
        nou->next = head;

        CNode* temp = head;
        while(temp->next != head){
        	temp = temp->next;
        }

        temp->next = nou;
    }else{
       nou->next = nou;
    }

    return nou;
}


//copiaza intr un vector clientii care au comenzi de peste un parg dat de la tastatura
Client* arrayOf(CNode* head,float value, int &i){

     if(head){
         i = 0;
         CNode* temp = head;

         do{
           if(temp->info.order >= value){
           	i++;
           }
           temp = temp->next;
         }while(temp != head);

         Client* arrayOf_Clients = (Client*)malloc(sizeof(Client)*i);
         i = 0;
         temp = head;

          do{
          	if(temp->info.order >= value){
          		arrayOf_Clients[i++] = temp->info;
          	}
            temp = temp->next;
          }while(temp != head);

          return arrayOf_Clients;
     }else{
     	printf("There is no list");
     	Client * c = NULL;
     	return c;
     }
}



//dezalocare memorie
void freeMemCirculaR(CNode*& head){
	if(head){
        CNode* temp = head;

        while(temp->next != head){
            CNode* aux = temp->next;
            free(temp->info.name);
            free(temp);
            temp = aux;
        }
          free(temp->info.name);
          free(temp);
          head = NULL;
        printf("List successfuly freed.\n");
	}else{
		printf("There is no list to free.\n");
	}
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                              STACK
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct Vagon {
	int nrPasageri;
	float* preturi;
	int id;
}Vagon;

Vagon createVagon(int id,int nr_pasageri, float* preturi){
     Vagon v;
     v.id = id;
     v.nrPasageri = nr_pasageri;
     v.preturi = (float*)malloc(sizeof(float)*(v.nrPasageri + 1));
     for(int i = 0; i < v.nrPasageri; i++){
     	v.preturi[i] = preturi[i];
     }

   return v;
}

void printVagon(Vagon v){
   printf("<%d> Vagonul acesta are %d pasageri, acestia platind bilete in valoare de: \n", v.id, v.nrPasageri);
   for(int i = 0; i < v.nrPasageri; i++){
   	printf("-> %3.2f RONs \n", v.preturi[i]);
   }
   printf("\n");
}

typedef struct Nod_stiva{
	Vagon info;
	Nod_stiva* next;
}Nod_stiva;

Nod_stiva* createNod_Stiva(Nod_stiva* next, Vagon v){
	Nod_stiva* nou = (Nod_stiva*)malloc(sizeof(Nod_stiva));
	nou->info = v;
	nou->next = next;

	return nou;
}

void printStack(Nod_stiva* head){
	if(head){
       Nod_stiva* temp = head;

       while(temp){
       	printVagon(temp->info);
       	temp = temp->next;
       }   
	}else{
		printf("There is no stack to print\n.");
	}
}

//push -> adaugare in tiva
//in stiva adaugarea si extragerea se fac la acelasi capat
Nod_stiva* push(Nod_stiva* head, Vagon v){
Nod_stiva* nou = createNod_Stiva(NULL, v);

    if(head){
       nou->next = head;
       head = nou;
    }else{
      head = nou;
    }

  return head;
}


//pop - exragerea din stiva - prmul nod
Vagon pop(Nod_stiva*& head){
   if(head){
       Vagon result = createVagon(head->info.id, head->info.nrPasageri, head->info.preturi);
       Nod_stiva* temp = head;
       head = head->next;
      // free(head->info.preturi);
       free(temp);

       return result;
   }else{
   	return createVagon(0, 0, NULL);
   }
}


//is empty
bool isEmpty(Nod_stiva* head){
	return head == NULL;
}


// -----------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                              QUEUE	
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
//cu liste dublu inalntuite
typedef struct Nod_queue{
   Vagon info;
   Nod_queue* next;
   Nod_queue* prev;
}Nod_queue;


typedef struct Queue{
   Nod_queue* first;
   Nod_queue* last;
}Queue;

Nod_queue* createNode_queue(Nod_queue* prev, Nod_queue* next, Vagon v){
    Nod_queue* nou = (Nod_queue*)malloc(sizeof(Nod_queue));
    nou->info = v;
    nou->prev = prev;
    nou->next = next;

    return nou;
}

Queue pushQ(Queue list, Vagon v){
	Nod_queue* nou = createNode_queue(NULL, list.first, v);

	if(list.first){
         nou->next - list.first;
         list.first->prev = nou;
         list.first = nou;
	}else{
		list.first = nou;
		list.last = nou;
	}

	return list;
}

void printQueue(Queue list, int flag){
	if(flag == 0){
        Nod_queue* temp = list.first;

        while(temp){
        	printVagon(temp->info);
        	temp = temp->next;
        }

	}else if(flag == 1){
        Nod_queue* temp = list.last;

        while(temp){
        	printVagon(temp->info);
        	temp = temp->prev;
        }
	}
}

Vagon popQ(Queue list){
	if(list.last){

        Vagon result = createVagon(list.last->info.id, list.last->info.nrPasageri, list.last->info.preturi);

        if(list.last != list.first){
             list.last = list.last->prev;
             free(list.last->next);
             list.last->next = NULL;
        }else {
        	free(list.last);
        	list.last = list.first = NULL;
        }
	}else{
		return createVagon(0, 0, NULL);
	}
}

int main() {

    printf("\n\n ------ SINGLE LINKED LIST -------\n\n");

	Book b1 = createBook("1984", "George Orwell", 32.909, 250);
	Book b2 = createBook("Ferma animalelor", "George Orwell", 45, 300);
	Book b3 = createBook("Morometii", "Marin Preda", 35.99, 266);
    Book b4 = createBook("Idiotul", "Dostoievski", 98.5, 450);
    Book b5 = createBook("1984" ,"Alta autor", 20, 150);

	Nod* nod = NULL;

	nod = insertEnd(nod, b1);
	nod = insertEnd(nod, b2);
	nod = insertEnd(nod, b3);
	nod = insertBegging(nod, createBook("Outlander", "Diana Gabaldon", 79.99, 600));
	nod = insertBegging(nod, b4);
	nod = insertEnd(nod, b5);
    nod = insertAfter(nod, createBook("Ion", "Liviu Rebreanu", 32.99, 230), "1984");

	printList(nod);

    float avg = avgPages(nod);
	printf("\nThe average number of pages is %.2f.\n\n", avg);

	//freeMem(nod);
	printList(nod);
	Book searched = searchBook(nod, "Morometii");
	printf("Cartea cautata: "); printBook(searched);
    
    freeMem(nod);

	printf("\n\n ------ DOUBLY LINKED LIST -------\n\n");

	Exam e1 = createExam("Zmafiroiu Alin", "SDD", 13, 9);
	Exam e2 = createExam("Marales Razvan", "Java", 7, 7);
	Exam e3 = createExam("Popescu Madalina", "Macroeconomie", 7, 10);
	Exam e4 = createExam("Ciurea Cristian", "C#", 7, 10);
	Exam e5 = createExam("Cocianu Catalina", "PEAG", 16, 8);
	Exam e6 = createExam("Toma Cristian", "Java", 7, 3);

	Node list;
	list.first = NULL;
	list.last = NULL;
	list = addBegging(list, e1);
	list = addBegging(list, e2);
    list = addEnd(list, e6);
    list = addEnd(list, e3);
    list = addBefore(list, e4, "Java");
    list = addAfter(list, e5, "Macroeconomie");

	printDNode(list, 0);

	printf("\nExtragem un nod.");
	Exam e = searchExam(list,"Macroeconomie");
	printf("\nExamen extras: "); printExam(e); 
	printf("\n\n");
	printDNode(list, 0);

    printf("\n\nExtragem toate examenele sustinute la o materie aleasa:\n");
	int size;
	Exam* array = searchExams(list, "Java", size);
	for(int i = 0; i < size; i++){
		printExam(array[i]);
	}

	freeMemDoubly(list);

	printf("\n\n ------ CIRCULAR LINKED LIST -------\n\n");

    Client c1 = createClient(1, "Popescu Tina", 21, 978);
    Client c2 = createClient(2, "Toader Maria", 19, 234);
    Client c3 = createClient(3, "Ionescu Mara", 20, 455);
    Client c4 = createClient(4, "Dumitru Laura", 21, 512);
    Client c5 = createClient(5, "Popescu Mihai", 20, 541);

    CNode* head = NULL;
    head = add_begging(head, c1);
    head = add_begging(head, c2);
    head = add_begging(head, c3);
    head = add_begging(head, c4);
    head = add_begging(head, c5);


    printCList(head);

    printf("\n\nReturn the clients that have an order bigger than 500 RONs:\n");
    int sizee;
    Client* array_C = arrayOf(head, 500, sizee);

    for(int i = 0; i < sizee; i++){
    	printClient(array_C[i]);
    }
    freeMemCirculaR(head);
    //printCList(head);

    printf("\n\n ------------- STACK --------------\n\n");

    float* p1 = (float*)malloc(sizeof(float)*3);
    for(int i = 0; i < 3; i++){
    	p1[i] = i * 10 +5;
    }
    Vagon v1 = createVagon(1, 3, p1);

    float* p2 = (float*)malloc(sizeof(float)*2);
    p2[0] = 35;
    p2[1] = 25.99;
    Vagon v2  = createVagon(2, 2, p2);
    
    float* p3 = (float*)malloc(sizeof(float)*1);
    p3[0] = 12.99;
    Vagon v3 = createVagon(3, 1, p3);

    float* p4 = (float*)malloc(sizeof(float)*2);
    p4[0] = 16.78;
    p4[1] = 19.91;
    Vagon v4 = createVagon(4, 2, p4);

    Nod_stiva* stack = NULL;

    stack = push(stack, v1);
    stack = push(stack, v2);
    stack = push(stack, v3);
    stack = push(stack, v4);
    printStack(stack);

    printf("Extract the first node of the stack:\n\n");
    Vagon v = pop(stack);
    printVagon(v);

    printf("\n\n");

    printStack(stack);
    Vagon vv = pop(stack);
    Vagon vvv = pop(stack);
    Vagon vvvv = pop(stack);
    Vagon vvvvv = pop(stack);
    printVagon(vvvvv);
    
    if(isEmpty(stack)) printf("\nThe stack is empty.\n");
    else printf("\nThe stack has elements.\n");

    printf("\n\n ------------- QUEUE --------------\n\n");
    //we use the Vagon structure here too!!! 

    Queue queue;
    queue.last = NULL;
    queue.first = NULL;

     queue = pushQ(queue, v1);
     queue = pushQ(queue, v2); 
     queue = pushQ(queue, v3); 
     queue = pushQ(queue, v4); 

     printQueue(queue, 0);

     printf("\n\nPOP from queue\n");
     Vagon vag = popQ(queue);
     printQueue(queue, 0);
}