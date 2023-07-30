/* Program to generate term-biased snippets for paragraphs of text.

   Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
   August 2022, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by or in collaboration with other students or
   non-students constitutes Academic Misconduct, and may be penalized by mark
   deductions, or by other penalties determined via the University of
   Melbourne Academic Honesty Policy, as described at
   https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: [Jess Lee]
   Dated:     [15/09/2022]

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

	/* you may need to delete this next line on some platforms
	   in order to get it to compile; if you end up doing that
	   make sure you put it back before you submit to the
	   Gradescope system, because it is required there */
#include <strings.h>

	/* maximum number of characters per word */
#define MAX_WORD_LEN 23
	/* maximum number of words per paragraph */
#define MAX_PARA_LEN 10000

	/* return code from get_word if end of paragraph found */
#define PARA_END 1
	/* return code from get_word if a word successfully found */
#define WORD_FND 2

	/* terminating punctuation that may follow a word */
#define TERM_PUNCT ".,;:!?"
	/* terminating punctuation that needs dots added */
#define NEEDS_DOTS ",;:"
	/* the string the separates paragraphs */
#define PARA_SEPARATOR "\n\n"
	/* insertion characters to indicate "bold" */
#define BBOLD "**"
	/* length of those characters when wrapped around a word */
#define BBOLD_LEN (2*strlen(BBOLD))
	/* insertion characters to indicate omitted text */
#define DDOTS "..."

	/* maximum words in any output snippet */
#define MAX_SNIPPET_LEN 30
	/* minimum words in any output snippet */
#define MIN_SNIPPET_LEN 20
	/* maximum length of output lines */
#define MAX_OUTPUT_LINE 72

	/* maximum terms allowed on command line */
#define MAX_TERMS 50
	/* signal for no match between word and query term */
#define NO_MATCH (-1)

typedef char word_t[MAX_WORD_LEN+1];
int     get_word(word_t w, int limit);

/* If you wish to add further #defines, put them below this comment,
   then prototypes for the functions that you add

   The only thing you should alter above this line is to complete the
   Authorship Declaration 
*/

/****************************************************************/

int result_type;
void get_paragraph();
void stage_1(char para_arr[MAX_PARA_LEN][MAX_WORD_LEN+1], int para_count, 
     int word_count);
void stage_2(char para_arr[MAX_PARA_LEN][MAX_WORD_LEN+1], int para_count, 
     int word_count);
void stage_3(char para_arr[MAX_PARA_LEN][MAX_WORD_LEN+1], int para_count, 
     int word_count);
int num_of_char(char word[MAX_WORD_LEN+1]);



/****************************************************************/
/* main program controls all the action
*/
int main(int argc, char *argv[]) {
    char query_terms[argc][MAX_WORD_LEN+1];
    int term_num = 1;

    //find query terms in main function, then pass onto get_paragraph
    for (int i=0; i<argc-1; i++) {
        strcpy(query_terms[i], argv[term_num]);
        printf("%d\n", term_num);
        term_num += 1;
    }

    get_paragraph();

    printf("ta daa!\n");


	return 0;
}

/****************************************************************/

/* stage 1 function: prints the number of words for each paragraph
   in the text
*/
void stage_1(char para_arr[MAX_PARA_LEN][MAX_WORD_LEN+1], int para_count, 
     int word_count) {
    printf("======= Stage 1 [para %d; %d words]\n\n", para_count, word_count);
}

/****************************************************************/
/* stage 2 function: writes each paragraph’s words across the 
page, making sure that no line contains more than 72 characters
*/
void stage_2(char para_arr[MAX_PARA_LEN][MAX_WORD_LEN+1], int para_count, 
     int word_count) {
    int num_char_used = 0;

    printf("======= Stage 2 [para %d; %d words; d matches]\n\n", para_count, 
         word_count);

    /* process through all the word in each paragraph */
    for (int i=0; i< word_count; i++) {
        /* counting the number of characters in each line */
        num_char_used += num_of_char(para_arr[i]) + 1;

        /* when the last word is reached */
        if (i == word_count - 1) {
            /* when a word and a space can fit on the line */
            if (num_char_used <= MAX_OUTPUT_LINE || num_char_used - 1 <= 
                MAX_OUTPUT_LINE) {
                printf("%s\n\n", para_arr[i]);
                /* when a word can not fit on the line at all */
            } else if (num_char_used > MAX_OUTPUT_LINE) {
                printf("\n%s\n\n", para_arr[i]);
            }
        } else {
            /* when a word and a space can fit on the line */
            if (num_char_used <= MAX_OUTPUT_LINE) {
                printf("%s ", para_arr[i]);
            /* when a word without a space can fit on the line */
            } else if(num_char_used - 1 <= MAX_OUTPUT_LINE) {
                printf("%s\n", para_arr[i]);
                num_char_used = 0;
            /* when a word can not fit on the line at all */
            } else if (num_char_used > MAX_OUTPUT_LINE) { 
                printf("\n%s ", para_arr[i]);
                num_char_used = num_of_char(para_arr[i]) + 1;
            }
        }
    }

}

/****************************************************************/
/* stage 3 function: calculates the score of a snippit relative
to a set of query terms
*/

void stage_3(char para_arr[MAX_PARA_LEN][MAX_WORD_LEN+1], int para_count, 
     int word_count) {
    // printf("======= Stage 3 [para %d; start x; length y; score z]\n\n", para_count);
}

/****************************************************************/
/* takes a single word as an input and returns the number of 
characters in that word
*/
int num_of_char(char word[MAX_WORD_LEN+1]) {
    int char_count = 0;

    for (int i=0; i<strlen(word); i++) {
        char_count += 1;
    }

    return char_count;
}

/****************************************************************/

/* calls function get_word() repeatedly, to build up a paragraph
   of words in an array. Each paragraph as at most "limit" words
   in it with each word at least MAX_WORD_LEN (23) characters
*/
void get_paragraph() {
    word_t w;
    char para_arr[MAX_PARA_LEN][MAX_WORD_LEN+1];
    int para_count = 0;
    int word_count = 0;

    /* read each word */
    while (get_word(w, MAX_WORD_LEN) != EOF) {
        /* building a paragraph of words in array para_arr */
        if (result_type == 2) {
            strcpy(para_arr[word_count], w);
            word_count += 1;
        }
        /* at the end of each paragraph, apply stage 1, 2 and 3 */
        if (result_type == 1) {
            para_count += 1;
            stage_1(para_arr, para_count, word_count);
            stage_2(para_arr, para_count, word_count);
            stage_3(para_arr, para_count, word_count);
            word_count = 0;
        }
    }
    /* apply stage 1, 2 and 3 to the last paragraph of the text */
    if (result_type == 3) {
        para_count += 1;
        stage_1(para_arr, para_count, word_count);
        stage_2(para_arr, para_count, word_count);
        stage_3(para_arr, para_count, word_count);

    }
}

/****************************************************************/
/* extract a single word out of the standard input, but not
   more than "limit" characters in total. One character of
   sensible trailing punctuation is retained.  
   argument array W must be limit+1 characters or bigger
*/
int get_word(word_t W, int limit) {
	int c;
	int first_newline = 0;

	/* first, skip over any non alphanumerics */
	while ((c=getchar())!=EOF && !isalnum(c) && first_newline == 0) {
		if (c == '\n') {
			first_newline = 1;
		}
	}
    /* when a new paragraph is read, return */
	if ((c == '\n') && (first_newline == 1)) {
        result_type = 1;
		return PARA_END;
	}

	if (c==EOF) {
        result_type = 3;
		return EOF;
	}

	/* ok, first character of next word has been found */
	*W = c;
	W += 1;
	limit -= 1;
	while (limit>0 && (c=getchar())!=EOF && isalnum(c)) {
		/* another character to be stored */
		*W = c;
		W += 1;
		limit -= 1;
	}
	/* take a look at that next character, is it a sensible trailing
	   punctuation? */
	if (strchr(TERM_PUNCT, c) && (limit>0)) {
		/* yes, it is */
		*W = c;
		W += 1;
		limit -= 1;
	}

	/* now close off the string */
	*W = '\0';
    result_type = 2;
	return WORD_FND;
}

/* Algorithms are fun!!! */