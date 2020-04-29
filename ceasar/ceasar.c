#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int konst (char p){

    int konst = 0;
    if (p >= 'a' && p <= 'z'){
        konst = 96;
    }

    if (p >= 'A' && p <= 'Z'){
        konst = 64;
    }
    return konst;
}

int p_position (char p, int konst){
        return (int)p-konst;

}


char caesar_cipher (int p, int konst, int k) {
    int c = (p+k)%26;
    if (c == 0) {
        c=26;
    }
    return c + konst;

}


int main (void){
    string p = get_string("Text: ");
    int k = get_int("Key:");
    printf("Output:\n");
    printf("%s\n  %d\n", p, k);

    for (int i = 0, n = strlen(p); i < n; i++){
        int konstanta = konst(p[i]);
        int p_pos = p_position(p[i], konstanta);
        char sifra = caesar_cipher(p_pos, konstanta, k);

        printf ("%c\n",sifra );
    }



}