//APS105 Lab 9 
//Author: Divya Sivakumaran
//Student Number: 1004907979

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

//Introduces the linked list and shows the content in it 
typedef struct node {
    char *artist;
    char *songData;
    char *artistData;
    char *genreData;
    
    struct node *next;
} Node;


typedef struct linkedList {
    Node *head;
}LinkedList;

// Creates a node that has all the necessary components and allocates the required memory
Node *createNode (char *songName, char *artist, char *genre ){
    Node *newNode = (Node*)malloc(sizeof(Node));

    if (newNode != NULL){
		//Allocates memory for each string
        newNode->songData = (char *) malloc(sizeof(char)*(strlen(songName)+1));
        newNode->genreData  = (char *) malloc(sizeof(char)*(strlen(genre)+1));
        newNode->artistData = (char *)malloc(sizeof(char)*(strlen(artist)+1));
        
		//Copies input string to the node
        strcpy(newNode->songData, songName);
        strcpy (newNode->genreData, genre);
        strcpy (newNode->artistData, artist);
        newNode->next= NULL;

    }
    return newNode;
}

//Creates the head for the linked list
void initList (LinkedList *list){
    list -> head = NULL;
}

//Checks if the lsit is empty
bool isEmpty(LinkedList *list){
    if(list->head == NULL){
        return true;
    }
    return false;
}



// Prompt the user for a string safely, without buffer overflow
void inputStringFromUser(char *prompt, char *s, int maxStrLength) {
    int i = 0;
    char c;
    
    printf("%s --> ", prompt);
    while (i < maxStrLength && (c = getchar()) != '\n'){
        s[i++] = c;
    }
    s[i] = '\0';
}

// Function to call when the user is trying to insert a song name that is already in the personal music library.
void songNameDuplicate(char *songName) {
    printf("\nA song with the name '%s' is already in the music library.\n"
           "No new song entered.\n", songName);
}

// Function to call when a song name that is to be deleted was found in the personal music library.
void songNameDeleted(char *songName) {
    printf("\nDeleting a song with name '%s' from the music library.\n",
           songName);
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void) {
    printf("\nThe music library is empty.\n");
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void) {
    printf("\nMy Personal Music Library: \n");
}

//Outputs the dong list to the user with the proper formatting
void printList(LinkedList *list) {
    if (isEmpty(list)==true){
        printMusicLibraryEmpty();
    }else{
    
    printMusicLibraryTitle();
    Node *n = list->head;
    while(n != NULL) {
        printf("\n%s\n", n->songData);
        printf("%s\n", n->artistData);
        printf("%s\n", n->genreData);
        n = n->next;
    }
    
    }
}


//Inserts the node right after the head
bool insertAtFront (LinkedList *list, char *songName, char *genre, char *artist){
    Node *temp = createNode (songName, genre, artist);
    if(temp == NULL){
        return false;
    }
    
    temp-> next = list->head;
    list->head = temp;
    return true;
    
}

//Uses strcmp to compare the song names and organize them accordingly
bool insertIntoOrderedList (LinkedList *list, char *songName, char *genre, char *artist){
    if (isEmpty (list)==true){
        return insertAtFront(list, songName, artist, genre);
    }
    
    if(strcmp(songName,list->head->songData)<0){
        return insertAtFront(list, songName, artist, genre);
    }
    
    Node *newNode = createNode(songName, artist, genre);
    if(newNode ==NULL){
        return false;
    }
    Node *n = list->head;
    while(n->next !=NULL && strcmp(songName, n->next->songData)>0){
        n= n->next;
    }
    newNode ->next = n->next;
    n->next = newNode;
    return true;
}
// Function to call when a song name was found in the personal music library.
void songNameFound(char *songName) {
    printf("\nThe song name '%s' was found in the music library.\n",
           songName);
}

// Function to call when a song name was not found in the personal music library.
void songNameNotFound(char *songName) {
    printf("\nThe song name '%s' was not found in the music library.\n",
           songName);
}

//Find the first node that has the desired song and then returns the pointer pointing to that node 
Node *findFirstNode(LinkedList *list, char *songName){
    Node *n = list->head;
    while (n!=NULL){
        if(strcmp(n->songData,songName)==0){
            return n;
        }
        n = n->next;
    }
    return NULL;
}

bool deleteNode (LinkedList *list, char *deleteSong){
    if (isEmpty(list)==true){
        return false;
    }
	//Frees the memory of the node right after the head
    if(strcmp(list->head->songData, deleteSong)==0){
        Node *temp = list->head->next;

        free (list->head->songData);
        free(list->head->artistData);
        free(list->head->genreData);
        free(list->head);
        list->head = temp;
        
        return true;
        
    }
	
    Node *n = list->head;
	//Frees the memory of nodes after the head
    while(n->next!=NULL && strcmp(n->next->songData, deleteSong)!=0){
        n = n->next;
    }
    
    if(n->next !=NULL){
        Node *temp = n->next;
        n->next = temp->next;
		//Frees the memory
        free(temp->songData);
        free(temp->artistData);
        free(temp->genreData);
        free(temp);
        
        return true;
    }
    
    return false;
}

// Used to delete all the nodes in the song list
void deleteAllNodes(LinkedList *list){
    Node *n = list->head;
    
    while(isEmpty(list)==false){
        songNameDeleted(n->songData);
        deleteNode(list, n->songData);
        
        n = n->next;
    }
    
    list->head = NULL;
    printMusicLibraryEmpty();
}

const int MAX_LENGTH = 1024;


int main (void){
	//Initializing all the arrays and the linked list 
    char songName [MAX_LENGTH+1];
    char artist [MAX_LENGTH+1];
    char genre [MAX_LENGTH+1];
    char deleteSong[MAX_LENGTH+1];
    LinkedList myList;
    initList (&myList);
    
    printf ("Personal Music Library.\n\n");
    printf("%s", "Commands are I (insert), D (delete), S (search by song name),\n"
    "P (print), Q (quit).\n");
    
    char response;
    char input[MAX_LENGTH +1];
    
     do { 
        inputStringFromUser("\nCommand", input, MAX_LENGTH);

        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);

        if (response == 'I') {
            // Insert a song into the linked list.
            // Maintain the list in alphabetical order by song name.

            // Using the following prompts to get the information from the user
                char *promptName = "Song name" ;
                inputStringFromUser(promptName, songName, MAX_LENGTH );
                char *promptArtist =  "Artist" ;
                inputStringFromUser (promptArtist, artist, MAX_LENGTH);
                char *promptGenre = "Genre" ;
                inputStringFromUser (promptGenre, genre, MAX_LENGTH);
                Node *n = findFirstNode(&myList,songName);
                if(n==NULL){
                    insertIntoOrderedList(&myList, songName, genre, artist);
                } else if(n!=NULL){
                    songNameDuplicate(songName);
                } 
        }
        else if (response == 'D') {
            // Delete a song from the list.
            char *promptDelete = "\nEnter the name of the song to be deleted" ;
            inputStringFromUser(promptDelete, deleteSong, MAX_LENGTH);
            
			//Find the node with the desired song 
            Node *n = findFirstNode(&myList, deleteSong);
            
            if (n!=NULL){
				//If song that exists
                songNameDeleted(deleteSong);
                deleteNode(&myList, deleteSong);
            }
            else if (n==NULL){
                songNameNotFound(deleteSong);
            }
        }
        else if (response == 'S') {

            // Search for a song by its name.
            char nameSearch [MAX_LENGTH+1];
            char *promptSearch = "\nEnter the name of the song to search for" ;
            inputStringFromUser(promptSearch, nameSearch, MAX_LENGTH);
            
			//Uses findFirstNode function to find the node with desired song
            Node *n = findFirstNode(&myList, nameSearch);
            if (n!=NULL){
				//Prints all the components in that node
                songNameFound(nameSearch);
                printf("%s\n", n->songData);
                printf("%s\n", n->artistData);
                printf("%s\n", n->genreData);
            } else if(n==NULL){
                songNameNotFound(nameSearch);
            }

        }
        else if (response == 'P') {
			//Prints the song list
            printList(&myList);

        }
        else if (response == 'Q') {
            ; // do nothing, we'll catch this below
        }
        else {
            // do this if no command matched ...
            printf ("\nInvalid command.\n");
        }
    } while (response != 'Q');
	//Deletes and frees all the memory
    deleteAllNodes(&myList);
    return 0;
}