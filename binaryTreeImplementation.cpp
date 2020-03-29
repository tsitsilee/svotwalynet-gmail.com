/************************************************************************/
/*                                                                      */
/* Interface file for a BINARY_TREE ADT                                 */
/*                                                                      */
/* Refer to lecture notes for details.                                  */
/*                                                                      */
/* Lynet Svotwa                                                         */
/* Original reused code taken from David Vernon                         */
/* 15/03/2020 added function to initialize the tree                     */
/*                                                                      */
/************************************************************************/

/* 

binaryTreeImplementation.cpp - implementation file for a program named assingment4
============================================================================

This program is for Assignment No. 4, Course 04-630 Data Structures and Algorithms for Engineers. 


Pseudocode
----------
reuse Vernon's code
all the functions here their signatures are found in the binaryTree.h file
for most of the functions

for the search tree function adjust it so that it checks string
for my searchtreeprobe function resuse the searchtree function and place a counter

add a maximum function that will be checking if the right side of the tree is greater or less  or equal to the left side
use this function in the tree height function with adding plus one as instructed in the lab to calculate the height of the tree

reuse the inorder function and ajust it such that new function takes the output file as one of its parameters
such that when called it prints the words in the output file in their order alphabetically

for the assign_element_values function adjust it so that it uses frequency instead of number

test the functions if they work by first printing them to the terminal if they work then adjust and print to output file
*/

#include "binaryTree.h"

/*** initialize a tree ***/

void initialize(BINARY_TREE_TYPE *tree) {

	static bool first_call = true;

	/* we don't know what value *tree has when the program is launched      */
	/* so we have to be careful not to dereference it                       */
	/* if it's the first call to initialize, there is no tree to be deleted */
	/* and we just set *tree to NULL                                        */

	if (first_call) {
		first_call = false;
		*tree = NULL;
	}
	else {
		if (*tree != NULL) postorder_delete_nodes(*tree);
		*tree = NULL;
	}
}


bool searchtree(BINARY_TREE_TYPE *tree, char str[])
{
	if (*tree != NULL) {
		bool found = false;
		if((strcmp(str, (*tree)->element.string)) == 0) { /* assume the number field is the key */
			found = true;
			return true;
		}
		else if((strcmp(str, (*tree)->element.string)) < 0) { /* assume the number field is the key */
			searchtree(&((*tree)->left), str);
		}
		else if((strcmp(str, (*tree)->element.string)) > 0) { /* assume the number field is the key */
			searchtree(&((*tree)->right), str);
		}
	}
	else{
		return false;
	}

}

//reuse of the searchtree function with addition of a counter
bool searchtreeprobe(BINARY_TREE_TYPE *tree,char str[], int counter[])
{
	if (*tree != NULL) {
		bool found = false;
		if((strcmp(str, (*tree)->element.string)) == 0) { /* assume the number field is the key */
			found = true;
			counter[0] = counter[0]+1;
			return true;
		}
		else if((strcmp(str, (*tree)->element.string)) < 0) 
		{ 
			/* assume the number field is the key */
			counter[0] = counter[0]+1;
			searchtreeprobe(&((*tree)->left), str, counter);
			
		}
		else if((strcmp(str, (*tree)->element.string)) > 0) { /* assume the number field is the key */
			counter[0] = counter[0]+1;
			searchtreeprobe(&((*tree)->right), str, counter);
			
		}
	}
	return false;

}

// maximum 
int maximum(int leftside, int rightside){
	if(leftside<rightside){
	return rightside;
	}
	else if(leftside>rightside){
		return leftside;
	}
	else if (leftside == rightside) {
		return leftside;
	}
}



int treeheight(BINARY_TREE_TYPE tree)
{
	if (tree != NULL)
	{
	int height = 1 + maximum(treeheight(tree->left),treeheight(tree->right));
	return height;
	 //treeheight(tree)
	}
}
/*** insert an element in a tree ***/

BINARY_TREE_TYPE *insert(ELEMENT_TYPE e,  BINARY_TREE_TYPE *tree ) {

	WINDOW_TYPE temp;

	if (*tree == NULL) {

		/* we are at an external node: create a new node and0 insert it */

		if ((temp = (NODE_TYPE) malloc(sizeof(NODE))) == NULL) 
			error("function insert: unable to allocate memory");
		else {
			temp->element = e;
			temp->left    = NULL;
			temp->right   = NULL;
			*tree = temp;
		}
	}
	else if ((strcmp(e.string, (*tree)->element.string)) < 0) { /* assume the number field is the key */
		insert(e, &((*tree)->left));

	}
	else if ((strcmp(e.string, (*tree)->element.string)) > 0) {
		insert(e, &((*tree)->right));

	}

	else if ((strcmp(e.string, (*tree)->element.string))==0) {
		//insert(e, &((*tree)->right));
		//return 0;
		(*tree)->element.frequency = (*tree)->element.frequency +1;

	}

	/* if e.number == (*tree)->element.number, e already is in the tree so do nothing */

	return(tree);
}


/*** returns & deletes the smallest node in a tree (i.e. the left-most node) */

ELEMENT_TYPE delete_min(BINARY_TREE_TYPE *tree) {

	ELEMENT_TYPE e;
	BINARY_TREE_TYPE p;

	if ((*tree)->left == NULL) {

		/* tree points to the smallest element */

		e = (*tree)->element;

		/* replace the node pointed to by tree by its right child */

		p = *tree;
		*tree = (*tree)->right;
		free(p);

		return(e);
	}
	else {

		/* the node pointed to by tree has a left child */

		return(delete_min(&((*tree)->left)));
	}

}

/*** delete an element in a tree ***/

BINARY_TREE_TYPE *delete_element(ELEMENT_TYPE e, BINARY_TREE_TYPE *tree) {

	BINARY_TREE_TYPE p;

	if (*tree != NULL) {

		if (e.frequency < (*tree)->element.frequency)  /* assume element.number is the */
			delete_element(e, &((*tree)->left));  /* key                          */

		else if (e.frequency > (*tree)->element.frequency)
			delete_element(e, &((*tree)->right));

		else if (((*tree)->left == NULL) && ((*tree)->right == NULL)) {

			/* leaf node containing e - delete it */

			p = *tree;
			free(p);
			*tree = NULL;
		} 
		else if ((*tree)->left == NULL) {

			/* internal node containing e and it has only a right child */
			/* delete it and make treepoint to the right child          */

			p = *tree;
			*tree = (*tree)->right;
			free(p);
		}
		else if ((*tree)->right == NULL) {

			/* internal node containing e and it has only a left child */
			/* delete it and make treepoint to the left child          */

			p = *tree;
			*tree = (*tree)->left;
			free(p);
		}
		else {

			/* internal node containing e and it has both left and right child */
			/* replace it with leftmost node of right sub-tree                 */      
			(*tree)->element = delete_min(&((*tree)->right));
		}
	}     
	return(tree);
}


/*** inorder traversal of a tree, printing node elements **/

int inorder( BINARY_TREE_TYPE tree, int n) {

	int i;

	if (tree != NULL) {
		inorder(tree->left, n+1);

		for (i=0; i<n; i++) printf("        ");
		printf( "%d %s\n", tree->element.frequency, tree->element.string);

		inorder( tree->right, n+1);
	}

	return(0);
}

//adopting the inorder function editing it to perform the functions I want
int inorderoutput(FILE *fp_out,BINARY_TREE_TYPE tree, int n) //accepts 3 inputs one of which is the output file
{

	int i;

	if (tree != NULL) {
		inorderoutput(fp_out, tree->left, n+1);   //calling the function recursively for the left side of the tree

		//for (i=0; i<n; i++);
		fprintf(fp_out, "%-13s %-1d (%d)\n", tree->element.string,   tree->element.frequency,   n ); //printing to output file
		printf("%-13s %-1d (%d)\n", tree->element.string, tree->element.frequency, n);
		//printf(FILE *fp_out);

		inorderoutput(fp_out, tree->right, n+1);  //calling the function recursively for the right hand side of the tree
	}
	//fclose(fp_out);
	return(0);
}



/*** inorder traversal of a tree, deleting node elements **/

int postorder_delete_nodes(BINARY_TREE_TYPE tree) {

	if (tree != NULL) {
		postorder_delete_nodes(tree->left);
		postorder_delete_nodes(tree->right);
		free(tree);
	}
	return(0);
}

/*** print all elements in a tree by traversing inorder ***/

int print( BINARY_TREE_TYPE tree) {

	printf("Contents of tree by inorder traversal: \n");

	inorder(tree,0);

	printf("--- \n");


	return(0);
}

int printtofile(FILE *fp_out, BINARY_TREE_TYPE tree) //adopting the print function and adjusting it to accept the output file as one of the parameters
{

	//fprintf(fp_out,"Contents of tree by inorder traversal: \n");
	printf("Contents of tree by inorder traversal: \n");

	inorderoutput(fp_out, tree,0);    //calling the inorder function so that the results can be printed to output file

	//fprintf(fp_out,"--- \n");          // printing the seprator to output file

	//fclose(fp_out);
	return(0);
}


/*** error handler:  
print message passed as argument and take appropriate action ***/

int error(char *s) {

	printf("Error: %s\n",s);

	exit(0);
}

/*** assign values to an element ***/

int assign_element_values(ELEMENT_TYPE *e, int frequency, char s[])  //changed number to frequency
{

	e->string = (char *) malloc(sizeof(char) * (strlen(s)+1));
	strcpy(e->string, s);
	e->frequency = frequency;   //edited to frequency
	return(0);
}

