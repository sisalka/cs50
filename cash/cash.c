#include <cs50.h>
#include <stdio.h>
#include <math.h>

float get_change(string prompt);

int main(void)
{

    float n = get_change("Change owed: ");
    printf ("%.2f\n", n);

    // cd = Coin denomination
    int next_cd[] = {25, 10, 5, 1};
    int n_int = (int) (n * 100);
    printf ("Krat sto je: %.d\n", n_int);
    int i = 0;
    int x = 0;
    int cd = next_cd[x];

   do {
        printf("iteracia %d: %d / %d = %d, zv %d\n", x, n_int, cd, n_int / cd, (n_int% cd));

        i += n_int / cd;
        printf("i je %d\n",i);
        n_int = n_int% cd;
        printf("zvysok je %d\n", n_int);
        x++;
        if (x<4) {
            cd=next_cd[x];
                    printf("next iteracia %d: %d / %d, mod = %d \n", x, n_int, cd,  (n_int% cd));

        } else {
                    printf("next iteracia %d: %d / %d, mod = %d \n", x, n_int, cd,  (n_int% cd));

            break;
        }
    }
     while (x<4);


    printf("%d\n",i);
    return i;


}

float get_change(string prompt)
{
    float n;
    do
    {
        n = get_float("%s", prompt);
    }
    while (n<=0);
    return n;
}


