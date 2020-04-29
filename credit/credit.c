#include <stdio.h>
#include <cs50.h>
#include <stdbool.h>
#include <string.h>


bool is_valid_ccn(string n)
{
    return true;
}

string get_creditcardnumber(string prompt)
{
    string ccn;
    do
    {
        ccn = get_string("%s", prompt);
    }
    while (!is_valid_ccn(ccn));
    return ccn;
}


int sum_even(string ccn) {
    int strsize = strlen(ccn);
    printf("dlzka stringu %d\n", strsize);
    int sucet = 0;
    for (int i=-2; i>= 0; i=i-2) {
        int cislo = ccn[i];
        printf("cislo je %d \n", cislo);
        cislo = cislo *2;
        printf("\tcislo krat dva je %d \n", cislo);
        if (cislo>9){
            int pr_cifra = cislo -10;
            printf("\tprva cifra je %d \n", pr_cifra);
            int dr_cifra = 1;
            printf("\tdruha cifra je %d \n", dr_cifra);
            cislo = pr_cifra+dr_cifra;
            printf("\tmenim cislo na %d \n", cislo);
        }
        sucet += cislo;
        printf("sucet parnych cisel je %d \n", sucet);
    }

    return sucet;
}

string convert_to_numbers(string ccn) {
    
    int strsize = strlen(ccn);
    //printf("string size %d \n", strsize);
    for ( int i = 0; i < strsize; i++){
        //printf("character %d \n", i);
        //printf("\tbefore as char %c \n", ccn[i]);
        //printf("\tbefore as number %d \n", ccn[i]);
        ccn[i] = ccn[i] - 48;

        //printf("\tafter as number %d \n", ccn[i]);

    }
    return ccn;
}




int main() {
    string ccn = get_creditcardnumber("Cislo karty: ");
    printf ("%s\n", ccn);

    
    convert_to_numbers(ccn);
    int sucet_nepar = sum_even(ccn);
       
};



