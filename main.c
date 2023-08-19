// Amaan Shah, UIC, Spring 2021
// Project 2: Balanced Symbol Checker
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

// struct declaration for stack
typedef struct Stack {
	char* darr;
	int size;
	int inUse;
} Stack;

// initializes values of the stack
void init (Stack *x) {
	x->size = 4;
	x->darr = (char*)malloc(sizeof(char) * x->size);
	x->inUse = 0;
}

// checks to see if the stack is empty
int is_empty (Stack *x) {
   if (x->inUse == 0) {
      return TRUE;
   } else {
      return FALSE;
   }
}

// allocates memory and copies over thye data to the larger array
void grow (Stack *x, int DBM) {
	char* temp = x->darr;
	x->darr = (char*)malloc(sizeof(char) * (x->size + 4));

	for (int i = 0; i < x->size; i++) {
		x->darr[i] = temp[i];
	}

	free(temp);

	if(DBM) {
		int oldSize = x->size;
		int newSize = x->size + 4;
		int numCopied = oldSize; 

		printf("Stack size increased from %d to %d, a total of %d values were copied \n", oldSize, newSize, numCopied);
	}


	x->size = x->size + 4;

// adds a new char to the array and grows if needed
}

void push(Stack *x, char y, int DBM) {
	if (x->inUse == x->size) {
		grow(x, DBM);
	}

	x->darr[x->inUse] = y;
	x->inUse = x->inUse + 1;
}

// returns the char on top of the stack
char top(Stack *x) {
	return (x->darr[x->inUse - 1]);
}

// "removes" the char on top of the stack
void pop(Stack *x) {
	x->inUse = x->inUse - 1;
}

// deallocates memory associated with the stack
void clear (Stack* x) {
	free(x->darr);
}

// output helper function 
void diffClosing (int index, char y) {
	for (int j = 0; j < index; j++) {
		printf(" ");
	}
	printf("^ ");

	if (y == '<') {
		printf("expecting >\n");
	} else if (y == '(') {
		printf("expecting )\n");
	} else if (y == '{') {
		printf("expecting }\n");
	} else if (y == '[') {
		printf("expecting ]\n");
	}
}

// output helper function
void missingOpen (int index, char x) {
	for (int i = 0; i < index; i++) {
		printf(" ");
	}
	printf("^ ");

	if (x == '>') {
		printf("missing <\n");
	} else if (x == ')') {
		printf("missing (\n");
	} else if (x == '}') {
		printf("missing {\n");
	} else if (x == ']') {
		printf("missing [\n");
	}
}

// output helper function
void missingClose(int length, char top) {
	for (int i = 0; i < length; i++) {
		printf(" ");
	}
	printf("^ ");

	if (top == '<') {
		printf("missing >\n");
	} else if (top == '(') {
		printf("missing )\n");
	} else if (top == '{') {
		printf("missing }\n");
	} else if (top == '[') {
		printf("missing ]\n");
	}
}

//
int main (int argc, char** argv)
{
 char input[301];

 /* set up an infinite loop */
while (1)
{
    /* get line of input from standard input */
	printf ("\nEnter input to check or q to quit\n");
    fgets(input, 300, stdin);

    /* remove the newline character from the input */
    int i = 0;
    while (input[i] != '\n' && input[i] != '\0')
    {
    	i++;
    }
    input[i] = '\0';

    /* check if user enter q or Q to quit program */
    if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
    	break;

    /* run the algorithm to determine is input is balanced */
    Stack st;
    init (&st);
    char a;

    int x = 0;
    int error = FALSE;

    // Debug Mode:
    int DBM = FALSE;
    for (int i = 0; i < argc; i++) {
    	if (strcmp(argv[i],"-d") == 0) {
    		DBM = TRUE;
    	}
    }


    for (int i = 0; i < strlen(input); i++) {
	   	if (input[i] == '<' || input[i] == '(' || input[i] == '[' || input[i] == '{') {
			a = input[i];
		   	push(&st, a, DBM);
		   	if (DBM) {
		   		printf("Character %c was pushed into the stack \n", a);
		   	}
	   	} 
	   	else if (input[i] == '>' ) {
		   	if (!is_empty(&st)) {
		   		char b = top(&st);
		   		if (b == '<') { // if top is matching char
			   		pop(&st);
			   		if (DBM) {
				   		printf("Character %c was popped from the stack \n", b);
				   	}
		   		} 
		   		else { // if top is not matching char
		   			printf("Unbalanced expression. Error 1: expecting a different closing symbol\n");
		   			printf("%s\n", input);
		   			diffClosing(i, b);
		   			error = TRUE;
		   			break;
		   		}
		   	}
		   	else { // if stack is empty 
		   		printf("Unbalanced expression. Error 2: missing an opening symbol\n");
		   		printf("%s\n", input);
		   		missingOpen(i, input[i]);
		   		error = TRUE;
		   		break;
		   	}

	   	}
	   	else if (input[i] == ')') {
		   	if (!is_empty(&st)) {
		   		char b = top(&st);
		   		if (b == '(') { // if top is matching char
			   		pop(&st);
			   		if (DBM) {
				   		printf("Character %c was popped from the stack \n", b);
				   	}
		   		} 
		   		else { // if top is not matching char
		   			printf("Unbalanced expression. Error 1: expecting a different closing symbol\n");
		   			printf("%s\n", input);
		   			diffClosing(i, b);
		   			error = TRUE;
		   			break;
		   		}
		   	}
		   	else { // if stack is empty 
		   		printf("Unbalanced expression. Error 2: missing an opening symbol\n");
		   		printf("%s\n", input);
		   		missingOpen(i, input[i]);
		   		error = TRUE;
		   		break;
		   	}

	   	}
	   	else if (input[i] == ']') {
		   	if (!is_empty(&st)) {
		   		char b = top(&st);
		   		if (b == '[') { // if top is matching char
			   		pop(&st);
			   		if (DBM) {
				   		printf("Character %c was popped from the stack \n", b);
				   	}
		   		} 
		   		else { // if top is not matching char
		   			printf("Unbalanced expression. Error 1: expecting a different closing symbol\n");
		   			printf("%s\n", input);
		   			diffClosing(i, b);
		   			error = TRUE;
		   			break;
		   		}
		   	}
		   	else { // if stack is empty 
		   		printf("Unbalanced expression. Error 2: missing an opening symbol\n");
		   		printf("%s\n", input);
		   		missingOpen(i, input[i]);
		   		error = TRUE;
		   		break;
		   	}
	   	}
	   	else if (input[i] == '}') {
		   	if (!is_empty(&st)) {
		   		char b = top(&st);
		   		if (b == '{') { // if top is matching char
			   		pop(&st);
			   		if (DBM) {
				   		printf("Character %c was popped from the stack \n", b);
				   	}
		   		} 
		   		else { // if top is not matching char
		   			printf("Unbalanced expression. Error 1: expecting a different closing symbol\n");
		   			printf("%s\n", input);
		   			diffClosing(i, b);
		   			error = TRUE;
		   			break;
		   		}
		   	}
		   	else { // if stack is empty 
		   		printf("Unbalanced expression. Error 2: missing an opening symbol\n");
		   		printf("%s\n", input);
		   		missingOpen(i, input[i]);
		   		error = TRUE;
		   		break;
		   	}
	   	}
	}

	if (error != TRUE) {
		if (is_empty(&st)) {
			printf("%s\n", input);
			printf("Expression is balanced\n");
		} else {
			printf("Unbalanced expression. Error 3: missing a closing symbol\n");
			printf("%s\n", input);
			char t = top(&st);
			missingClose(strlen(input), t);
		}
	}
	
	clear(&st);
 }


 printf ("\nGoodbye\n");
 return 0;
}
