#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int count_letters (string s){

    int letters = 0;
    for (int i = 0, n = strlen(s); i < n; i++){
        if (isalpha(s[i]))
        {
            letters ++;
        }
    }
    return letters;
};

int count_words (string s){

    int words = 1;
    for (int i = 0, n = strlen(s); i < n; i++){
        if (isspace (s[i]))
        {
            words ++;
        }
    }
    return words;
};

int count_sentences (string s){

    int sentences = 0;
    for (int i = 0, n = strlen(s); i < n; i++){
        if (s[i]=='.'|| s[i]=='!' || s[i]=='?')
        {
            sentences ++;
        }
    }
    return sentences;
};



int main(void){
    string s = get_string("Text: ");
    printf("Output:\n");
    printf("%s\n", s);

    int letters = count_letters(s);
    printf ("Letters: %d,\n", letters);

    int words = count_words(s);
    printf ("Words: %d,\n", words);

    int sentences = count_sentences(s);
    printf ("Sentences: %d,\n", sentences);

    float L = (float)letters / (float)words*100;
    float S = (float)sentences / (float)words*100;
    printf ("L: %0.2f,\n", L);
    printf ("S: %0.2f,\n", S);


    float CLI = 0.0588*L-0.296*S-15.8;
    printf ("Index: %0.2f,\n", CLI);

    int Grade = round(CLI);
    if (Grade <1){
        printf("Grade Before 1\n");
    } else if (Grade>16){
        printf ("Grade 16+\n");
    } else {
        printf ("Grade %d\n", Grade);
    }
}