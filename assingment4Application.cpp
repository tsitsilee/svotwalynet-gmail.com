/* 

assingmen4tApplication.cpp - Application file for a program named assingment4
============================================================================

This program is for Assignment No. 4, Course 04-630 Data Structures and Algorithms for Engineers. 


Pseudocode
----------
Create assingment 4 and copy the textAppication code to the assingment4Application.cpp 
the code the following functions
read the input file and print the filenames the output file
opened the file, and read the text in the file, word by word, wrote each word to the screen on a separate line
converted all the words are to lower case
Modified the code as following
remove characters that are not alphanumeric using the isalnum() function

since I did not know how I skipped steps 5-7 of the lab
then I copied the files of the binary tree that is its header and implementation file and added the binary tree application 
code in the assingment4Application.cpp  and printed the output to the terminal to check if its working
before bulding I ran my cmake again , upon completion thats when I tested the code

I then edidted the binarytree implementation file as instructed where in the function assign_element_value I 
changed number to frequency
then in the comparison instead of using number I used string for the two if statements
back to my application file I constructed 2 BSTs as tree 1 and tree2
which I tested by printing to terminal to ensure the words were being inserted correctly

through the search tree function in the binaryteeimplementation file I could check if a word existed by making the function bool 
that way it would return true or false 
which I then called the search function in my application file and when it returned false meaning the word does not exist it would then
be printed changed to uppercase by using toupper() function

then from the binarytreeImplmentation file created the function that computed the height of the tree which I then called at the 
far end before closing the files 
again the binaryteeImplementation created a function that computed the average probe, but simply ,aking use of a counter 
which I then called in my program

Throught the use of the inorder function I called already provided I reused it and ensured that it printed the words one by one
to the output file by adopting the function to accept the output file

I reused the code from Vernon for inserting line separators to separate files
Following the lab went back to my function for the height of the tree and make the function recursive when it was calling the right side 
and when calling the left side

Then finished off with trying to sort steps 4-7 but this time instead of using isallnum I used ispunct function which is inbult to check for punctuation
which from tests did not work so well





Author
------

Lynet T Svotwa, Carnegie Mellon University Africa
01/02/2020
revision date 16/02/2020
version 3 revision date 28/02/2020

acknowledgements
David Vernon Lab 6, textApplication code, binary tree code 
TA's for guidance
Charles Yasuf
Wuyeh Jobe



testing
---------

Test to see if it will print my andrewID to the output file
test to see if it prints the file name to the output file as expected
test to see if each found word is printed alongside its occurance in a formatted manner
test to see if it prints and outputs the correct values for 
	Maximum number of probes
	Average number of probes
test to see if I add extra 5 files if the program will still work
test to see if I add a new line in the textfile1 if it will still work
test to see if one of the files is empty if the program will crash
test to see if it reads a punctuation will it treat it as expected
test to see if there is a file with so many sentences will the program crush

my sample input is as follows

../data/words.txt
../data/textfile1.txt
../data/textfile2.txt

and my sample output is as follows

lsvotwa
../data/textfile1.txt
My heart is in the work
My heart is in the WIRK
Maximum number of probes: 4
Average number of probes: 2.5
heart 2 (1)
in 2 (3)
is 2 (2)
my 2 (0)
the 2 (1)
work 1 (2)
--------------------
../data/textfile2.txt
heart in is My the work
Maximum number of probes: 6
Average number of probes: 3.5
heart 1 (0)
in 1 (1)
is 1 (2)
my 1 (3)
the 1 (4)
work 1 (5)
--------------------

*/
// main program for where the program is first executed

#include "assingment4.h" // to ensure that I make use of the signatures in the header file.
#include "binaryTree.h"
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

int main() {

	// declaring and initialising everything I am going to use or might need to use 
	bool debug            = false; // print diagnostic information?
	bool input_dictionary = true;  // we begin by reading the dictionary
	int end_of_file;
	int end_of_file2;
	char filename[MAX_STRING_LENGTH];
	char word[MAX_STRING_LENGTH];
	char original_word[MAX_STRING_LENGTH];

	unsigned int i,j,k,l,m,n,o; 
	char ch;
	//int p;
	int treehght = 0;
	double treeavrg = 0;
	int searchprobe = 0;
	int cc[1];
	int totalprobe = 0;
	int totalwords = 0;

	double averageprobe = 0;
	//char punctuation[] = { '.', '?', '!', ':', ';', '(', ')', '[', ']', ',', '"','\s', '/','@'};
	//char space[1];

	//char newspace = " ";
	//char punctuation = Alternatives@@Characters[",.?:;'\"!-"];
	FILE *fp_in;   // declaring the input file
	FILE *fp_out;   //declaring the input file
	FILE *fp_in2;   // delaring the second input file

	if ((fp_in = fopen("../data/input.txt","r")) == 0)   //if condition to handle the issue of the file not opening with the read privileges
	{
		printf("Error can't open input input.txt\n");
		prompt_and_exit(1);
	}

	if ((fp_out = fopen("../data/output.txt","w")) == 0)  //if condition to handle the output file opening with the write privileges
	{
		printf("Error can't open output output.txt\n");
		prompt_and_exit(1);
	}

	fprintf(fp_out,"lsvotwa\n");   //printing my andrew id to the output file


	ELEMENT_TYPE e;              //element type to be used by the tree functions
	BINARY_TREE_TYPE tree1 = NULL;  //declaring the first tree to NULL, ensuring it is  empty
	BINARY_TREE_TYPE tree2 = NULL;  //declaring second tree to NULL to ensure its empty

	//initiliazing two trees as per instructions
	initialize(&tree1);  //initializing the first tree
	initialize(&tree2);    //initializing the second tree



	end_of_file = fscanf(fp_in, "%s", filename);  // read a filename

	while (end_of_file != EOF) //checking to ensure its not the end of file
	{


		if (!input_dictionary) //checking to ensure we not printing dictionary
		{
			fprintf(fp_out,"%s\n",filename);
		}

		/* open the target file: dictionary or text */

		if ((fp_in2 = fopen(filename,"r")) == 0) 
		{  
			printf("Error can't open text file %s\n",filename);
			prompt_and_exit(1);
		}

		end_of_file2 = fscanf(fp_in2, "%s", original_word);  // read a word from the file

		/* check the whitespace character after the word to see if it is a newline */
		ch = getc(fp_in2);



		if (ch == '\n')
		{ 
			strcat(original_word,"\n"); // add a newline character so that subsequent text in on the next line

		}

		else
		{
			strcat(original_word," ");  // add the whitespace

		}



		while (end_of_file2 != EOF) {

			strcpy(word,original_word); // make a copy of the word so that we can process it
			// but keep the original so that we can write it to the output file 


			/* convert to lower case */

			for (i=0; i<strlen(word); i++) //condition to ensure all the words are converted to lower
			{
				word[i] = tolower(word[i]);

			}

			// condition to check if the word is even there
			if (strlen(word) > 0) 
			{

				if (input_dictionary) 
				{

					/*** building the dictionary ***/

					word[strlen(word) - 1] = '\0'; //strip of last character
					assign_element_values(&e,1, word);
					insert(e, &tree1);

				}
				else {

					//removing multiple puntuations and apostrophe s
					int position = 0; //position of the punctuation
					char changedWord[MAX_STRING_LENGTH];  //storing the changed word here
					//condition to completely check and ensure if there are multiple punctuations all of them are remved
					for (int k=0;k<strlen(word);k++)    
					{
						if(!ispunct(word[k]) || word[k] =='-')   // adding condition to ensure that it does not remove apostrophe from the word
						{
							changedWord[position] = word[k];
							position++;
						}
						else if(word[k] == '\'') 
						{
							k++;
						}
					}
					changedWord[position-1] = '\0'; //strip of last character
					strcpy(word,changedWord);
					//--removing puncatuations end here --//

					/*** analyzing text ***/

					//bool found function is in the binaryTreeImplementation
					//using it here to check if a word exists
					bool found = searchtree(&tree1, word);  //calling the searchtree function and passing the tree with the dictionary and the word 
					                                         //to be found
					if (found == true)    //condition to execute if condition os found
					{

						cc[0] = 0;
						//add the total probes and words once for each word
						if (!searchtree(&tree2, word))
						{
							assign_element_values(&e,1, word);
							insert(e, &tree2);
							searchtreeprobe(&tree2,word, cc); //calling mt function same as searchtree but a bit different
							totalprobe = totalprobe + cc[0];
							totalwords = totalwords+1;   //incrementing the number of words for use later
						}
						else{
							assign_element_values(&e,1, word);
							insert(e, &tree2);
						}

					}
					else
					{
						/** convert to lower case **/
						for (n=0; n<strlen(original_word); n++) 
						{
							original_word[n] = toupper(original_word[n]);  //if the word is not found then convert it to upper

						}

					}

					fprintf(fp_out, "%s", original_word); // copy to output  file
				}
			}


			end_of_file2 = fscanf(fp_in2, "%s", original_word);

			/* check the whitespace character to see if it is a newline */
			ch = getc(fp_in2);
			if (ch == '\n') {
				strcat(original_word,"\n");  // add the newline
			}
			else {

				strcat(original_word," ");  // add the whitespace
			}


		}


		if (!input_dictionary) {
			treehght = treeheight(tree2);
			/** Check if total words is 0 before deviding **/

			//condition to reset the averageprobe
			if (totalwords ==0 )
			{
				averageprobe = 0;
			}
			//if not zero then allow for calculation of avaerage probe
			else
			{
				averageprobe = (double)totalprobe/(double)totalwords;
			}

			//printing to file
			fprintf(fp_out, "Maximum number of probes: %d\n", treehght); //printing the maximum number of probes
			fprintf(fp_out, "Average number of probes: %3.1f\n", averageprobe); //printing the average number of probes
			printtofile(fp_out,tree2); //printing the words inoder
			fprintf (fp_out,"--------------------\n");
			initialize(&tree2);

			totalwords = 0;   //resseting the totalwords for the next file
			totalprobe = 0; // resetting the total probe for the next file
		}

		fclose(fp_in2);   //closing the second file

		end_of_file = fscanf(fp_in, "%s", filename); // read the next filename

		input_dictionary = false; // the first file is the dictionary file; we've read it so now we reset this flag
	};


	//closing the files
	fclose(fp_in);
	fclose(fp_out);

	/*
	prompt_and_exit(1);
	_getch();
	*/
}