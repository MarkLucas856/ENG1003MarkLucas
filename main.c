#include <stdio.h>
#include <stdlib.h>

void railFence(char *message, char *cipherText, int length, int A);

void railFence2(char *message, char *cipherText, int length, int A, int B,
int dir);

int main()
{
    int a, b; //
    int dir; // users selected option
    int length;
    char *message;

    printf("Welcome to rail-fence cipher.\n\n");
    printf("To encrypt a message enter: 0)\nTo decrypt a message enter: 1)\n\n");
    scanf("%d", &dir);        // scans user input for option a or b, assigns selected option to c.




}
void railFence2(char *message, char *cipherText, int length, int A, int B,
int dir)
{   // rail fence 2 function definition
   switch(dir)
    {
    case 0:
        { // if dir = 0 do:
        printf("\nWhich encryption algorithm would you like to use?\n\n");
        printf("For classical rial-fence chiper enter: 1)\n");
        printf("For 2-level rial-fence chiper enter: 2)\n");
            //scanf("%d", &);
    break;
        }



    case'1':
        {  //if dir = 1 do:
        printf("\nWhich decryption algorithm would you like to use?\n\n");
        printf("For classical rial-fence chiper enter: 1)\n");
        printf("For 2-level rial-fence chiper enter: 2)\n");
            //scanf("%d", &);
    break;
        }



    default:
        printf("\nError, please select option 1 or 2\n");
    break;


    }
}
