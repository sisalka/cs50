#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>


bool has_dup (string prompt){
    int occ [26] = { 0 };

     for (int i = 0, n = strlen(prompt); i < n; i++){
         char c = tolower(prompt[i]);
         int poz = c-97;
         occ[poz] = occ[poz]+1;
         // occ[poz]++;
     }

     for (int i = 0; i< 26; i++){
         int n = occ[i];
         if (n>1) {
             return true;
         }
     }
    return false;
}

bool is_alpha (string prompt){
    for (int i = 0, n = strlen(prompt); i < n; i++){
        if (!isalpha(prompt[i])) {
            return false;
        }
    }
    return true;
}

bool is_valid (string prompt){

    bool dup = has_dup(prompt);
    bool alpha = is_alpha(prompt);
    int n = strlen(prompt);

    if (dup == true){
        printf("Duplicitne znaky\n");
    }
    if (alpha == false){
        printf("Znaky ine ako pismena\n");
    }
    if (n != 26){
        printf("Key musi mat 26 znakov\n");
    }

    return dup == false && alpha == true && n == 26;

    // alternativne
    return ! dup && alpha && n == 26;
    // alternative 2
    return ! has_dup(prompt) && is_alpha(prompt) && strlen(prompt) == 26;
}

string get_key(){
    string key;
    do{
        key = get_string("Key:");
    }
    while (is_valid(key) == false);
    return key;
}


char sifra_f (char p, string key){
    char p_val = p;
    int p_poz=0;
    char c_val;
    if (p >= 'a' && p <= 'z'){
        p_poz= p_val-97;

    }
    if (p >= 'A' && p <= 'Z'){
        p_poz= p_val-65;

    }
    c_val = key[p_poz];
    return c_val;
}


int main (void){
    string p = get_string("Text: ");
    string key = get_key();

    int n = strlen(p);
    char *vysledna_sifra;
    vysledna_sifra= malloc(n * sizeof(char));

     for (int i = 0; i < n; i++){

         char sifra = isalpha (p[i]) ? sifra_f(p[i], key) : p[i];

         vysledna_sifra[i] = isupper(p[i]) ? toupper(sifra) : tolower(sifra);




     }

    printf("%s\n",vysledna_sifra);

    free(vysledna_sifra);


}