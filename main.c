#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    /**  high-level operation
    Variables:
                 A = 'key' or the number of rows,
                 B = second key or height of the second peak in the algorithm
                 c = message character counter
            length = number of characters in the message
               dir = users option of encrypting or decrypting. used in switch case.
           message = users entered message
        Ciphertext = 1d array. used to store array size
            Matrix = 2d array. A grid used to build the message 'shape'
         Character = character used in decryption to help determine location of the message characters
            case a = 2-level rail-fence cihper algorithm
            case b = classic rail-fence cihper algorithm
          FileText = text read from a file to be encrypted or decrypted
    Functions
        RailFence2
            void function, this returns no value. Take 6 arguments, 2 char pointers & 4 int variables.\
            print statement within fuctinon prints directly to console.
        RailFence
             void function This returns no value. takes 4 arguments 2 char pointers & 2 int variables.
             print statement within fuctinon prints directly to console.
    Encryption
        user enteres a message and key. these are used to either encode or decode the message according to which option the user selects.
        Encrypts message by creating a 'W' shape inside a 2-D array using the message characters to draw the shape.
        it then prints these characters out from left to right moving down a collum once the last character on a row is printed.

    Decryption
        Function decrypts messages by taking users encrypted message and its key. draws the W shape using the key and message length as its bounds
        and filling in the shape 0's. This is to determine the peaks and character locations. Then it writes the
        encoded message characters from left to right and then down a row on the grid. Then Prints characters out in order of the 'W' shape
        to get the original message.

    To use:
        run program and follow the instructions. You will be given options to use the classic cipher or 2-level. You will then be given further options
        to either encrypt or decrypt a message. To select an option enter the specified number and press enter. Do not enter a character or the program will fail.
        Once message is entered you will be promped to enter 2 seperate int values for the keys.

    limitations are:
        -message must be atleast 3 characters in length
        -Character limit of 1028

    brief program flow overview:
        -run program
        -ask user; classic(0) or 2-level cipher algorithm.

        -ask user; encrypt (0) or decrypt (1) (encryption only, for classic rail-fence cipher)
        -enter switch case
        -take users message
        if message < 3 characters.. error message, try again.
        -take users key(s)
        -call function
        -create matrix
        -set matrix to 0
        -Begin arranging characters in the classic or 2-level cipher pattern
        -print characters to console in the calculated order
    */
//function prototypes:
void railFence(char *message, char *cipherText, int length, int A);
void railFence2(char *message, char *cipherText, int length, int A, int B, int dir);
/// printing for 2-level encrypt and decrypt
int main()
{
    int dir,length, A, B, FileSize, i=0;        // Declaring main's int variables
    char  userOptions, c;                      // Users algorithm choice & a file text character counter
    FILE *FileText;                           // pointer for the text held witin the chosen message file
    FILE *Size;                              // Used to measure file size & declare arrays with.

    printf("Welcome to cipher algorithms.\n\n");                                // User interface
    printf("For 2-level rail-fence cipher algorithm, enter:\n");
    printf(" a)\n\n");
    printf("for classical rail-fence cipher  encryption algorithm, enter:\n");
    printf(" b)\n");
    scanf("%c", &userOptions);

    if(userOptions <'a' || userOptions >'b')                            //Ensuring user selects a valid option.
    {
        printf("Error, select option: a) or b)\n");
        scanf("%c", &userOptions);
    }

    else;
    switch(userOptions)
    {
        case 'a':   ///option 'a' (2-level rail cipher)
        {
            printf("For message encryption, enter:\n 0)\n");
            printf("For message decryption, enter:\n 1)\n");
            scanf("%d", &dir);
            if((int)dir <0 || (int)dir >1)                   // Ensuring user selects a valid input
            {
                printf("\n Error, Invalid selction. \n Please re-run the program and select options 0 or 1 \n"); //  A necessary evil
                return 0;
            }
            switch(dir)
            {
                case 0:   ///(2-level encryption)
                {
                  //  printf("Enter your message:\n\n");
                    printf("Retrieving message from file...\n\n");

                    Size = fopen("Message1.txt", "r");                         // read message from .txt file called message
                    if(Size == NULL)
                    {
                        perror("fopen()");                                  // Print a scripted error message for error encountered
                        return 1;
                    }
                    fseek(Size, 0, SEEK_END);                            // measuring message length held within the file
                    FileSize = ftell(Size);
                    char message[FileSize+1], cipherText[FileSize+1]; // Using size of file to declare and initialise array sizes.

                    FileText = fopen("Message1.txt", "r");                      // read message from .txt file called message
                    printf("Message contains %d characters",FileSize);
                    if(FileText == NULL)
                    {
                        perror("fopen()");                                    // Print a pre-scripted error message for specific error encountered
                        return 1;
                    }
                    fscanf(FileText, "%c", &c);                            // scan here to know if at end of file before entering loop
                    while(!feof(FileText)&& i< FileSize)                      // determines if at end of file
                    {
                        message[i]=c;                                   // Scanning file, adding character to array element i, increment i add next character to array.
                        i++;                                           // c holds a message character, adds it to the ith array element, moves on to next character and repeats
                        fscanf(FileText, "%c", &c);                   //feof is self incrementing for its counter 'c'
                    }
                    length = strlen(message);
                    if(message[i-1]=='\n')                    // removing extra newline character read by fscanf from message
                    {
                        message[i-1]='\0';
                    }
                    message[i]=0;                              // changing last element of array to 0 from extra increment of i to avoid extra characters being printed

                    printf("\nMessage found: '%s'\n", message);
                    length = strlen(message);
                /**   user message input option
                   char message[]="hello there friendgg";
                   char cipherText[2000];
                   fflush(stdin);                                         //clearing buffer to read new string
                   fgets(message, 1028, stdin);
                   length = strlen(message);                            //scanning users input from console & storing it in message, character limit of 1028.
                   if(message[length-1] == '\n')                       // if last element of string before the terminating character is a new line
                   {
                        message[length-1] = '\0';                    // replace newline character read by fgets with a null byte
                   }
                */

                    printf("Enter your two seperate integer keys:\n Key A: \n");
                    scanf("%d", &A);
                    printf("Key B (must be less than the previous key 'A'): \n");
                    scanf("%d", &B);
                    while(B>=A)
                    {
                        printf("\nError, key B must be < key A\n\n");
                        printf("Enter your two seperate integer keys:\n Key A: \n");
                        scanf("%d", &A);
                        printf("Key B (must be less than the previous key 'A'): \n");
                        scanf("%d", &B);
                    }

                    railFence2(message, cipherText, length, A, B, dir);
                    printf("\n Your encryted message is: ''%s''\n", cipherText);
                    return 0;
                 }
                case 1: ///(2-level decryption)
                {
                    //printf("Enter your message:\n\n");
                    printf("Retrieving message from file...\n\n");

                    Size = fopen("cipherText1.txt", "r");                     // read message from .txt file called message
                    if(Size == NULL)
                    {
                        perror("fopen()");                                // Print a scripted error message for error encountered
                        return 1;
                    }
                    fseek(Size, 0, SEEK_END);                         // measuring message length held within the file
                    FileSize = ftell(Size);
                    printf("File contains %d\n\n", FileSize);

                    char message[FileSize+2], cipherText[FileSize+2];       // Using size of file to declare and initialise array sizes.

                    FileText = fopen("cipherText1.txt", "r");             // read message from .txt file called message
                    if(FileText == NULL)
                    {
                        perror("fopen()");                             // Print a pre-scripted error message for specific error encountered
                        return 1;
                    }
                    fscanf(FileText, "%c", &c);                     // scan here to know if at end of file before entering loop
                    while(!feof(FileText)&& i< 1027)               // determines if at end of file
                    {
                        cipherText[i]=c;                         // Scanning file, adding character to array element i, increment i add next character to array.
                        i++;                                    // c holds a message character, adds it to the ith array element, moves on to next character and repeats
                        fscanf(FileText, "%c", &c);            //feof is self incrementing for its counter 'c'
                    }
                    length = strlen(cipherText);
                    if(cipherText[i-1]=='\n')               // removing extra newline character read by fscanf from message
                    {
                        cipherText[i-1]='\0';
                    }
                    cipherText[i]='\0';                  // changing last element of array to 0 from extra increment of i to avoid extra characters being printed
                    printf(" The encrypted message is: %s\n\n", cipherText);

        /** user input option
                   fflush(stdin);                                         //clearing buffer to read new string
                   fgets(cipherText, 1028, stdin);
                   length = strlen(cipherText);                            //scanning users input from console & storing it in message, character limit of 1028.
                   if(cipherText[length-1] == '\n')                       // if last element of string before the terminating character is a new line
                   {
                        cipherText[length-1] = '\0';                    // replace newline character read by fgets with a null byte
                   }
            */
                    printf("Enter your two seperate integer keys:\n Key A: \n");
                    scanf("%d", &A);
                    printf("\nKey B (must be less than the previous key 'A'): \n");
                    scanf("%d", &B);
                    while(B>=A)                             // Ensuring the key rule B<A remains true.
                    {
                        printf("\nError, key B must be < key A\n\n");
                        printf("Enter your two seperate integer keys:\n Key A: \n");
                        scanf("%d", &A);
                        printf("Key B (must be less than the previous key 'A'): \n");
                        scanf("%d", &B);
                    }

                    railFence2(message, cipherText, length, A, B, dir);
                    printf("The decrypted message is:''%s''", message);

                    return 01;
                }
            }
        }
        case 'b':   ///option 'b'(classic encryption)
        {
            //printf("Enter your message:\n\n");
            printf("Retrieving message from file...\n\n");

            Size = fopen("Message1.txt", "r");                         // read message from .txt file called message
            if(Size == NULL)
            {
                perror("fopen()");                                  // Print a scripted error message for error encountered
                return 1;
            }
            fseek(Size, 0, SEEK_END);                            // measuring message length held within the file
            FileSize = ftell(Size);
            char message[FileSize+1], cipherText[FileSize+1]; // Using size of file to declare and initialise array sizes.

            FileText = fopen("Message1.txt", "r");                      // read message from .txt file called message
            if(FileText == NULL)
            {
                perror("fopen()");                                    // Print a pre-scripted error message for specific error encountered
                return 1;
            }
            fscanf(FileText, "%c", &c);                            // scan here to know if at end of file before entering loop
            while(!feof(FileText)&& i< 1027)                      // determines if at end of file
            {
                message[i]=c;                                   // Scanning file, adding character to array element i, increment i add next character to array.
                i++;                                           // c holds a message character, adds it to the ith array element, moves on to next character and repeats
                fscanf(FileText, "%c", &c);                   //feof is self incrementing for its counter 'c'
            }
            length = strlen(message);
            if(message[length-1]=='\n')                    // removing extra newline character read by fscanf from message
            {
                message[length-1]='\0';
            }
            message[i]=0;                              // changing last element of array to 0 from extra increment of i to avoid extra characters being printed

                    printf("\nMessage found: '%s'\n", message);
                /**   user message input option
                   fflush(stdin);                                         //clearing buffer to read new string
                   fgets(message, 1028, stdin);
                   length = strlen(message);                            //scanning users input from console & storing it in message, character limit of 1028.
                   if(message[length-1] == '\n')                       // if last element of string before the terminating character is a new line
                   {
                        message[length-1] = '\0';                    // replace newline character read by fgets with a null byte
                   }
                */

            printf("\nEnter your key (must be an integer): \n");
            scanf("%d", &A);

            railFence(message, cipherText, length, A);                       //Calling function for message encryption
            printf("\n Your encryted message is: ''%s''\n", cipherText);

            return 02;
        }
        break;
    }
}
/** railfence 2 description
railFence 2
    variables
        message (char) is the un encrypted message eiter before encryption or after decryption
        cipherTesx (char) is the encrypted message either after encryption or before decryption
        length(int) is the number of characters in the message
        A (int)is the uers key & number of rows on the grid
        B (int) is the users second key & height of the second peak inside the grid
        dir (int) is the users choice of either encryption (dir =0)
        or decryption (dir =1)

*/
void railFence2(char *message, char *cipherText, int length, int A, int B, int dir) ///2-level rail-fence cipher algorithm
 {

    int matrix[A+2][length+2];
    int i=0, j=0, c=0;

    switch(dir)
    {
        case 0: /// Case '0' -> 2-level Encription.
        {
            length = strlen(message);                           // re-declaring length to ensure it was not altered in the file i/o section in main
            printf("\n encrypting:''%s'' please wait...\n\n", message);

            for (i = 0; i <A; i++)                           // for i < integer value of key
            {
                for (j = 0; j<=length; j++)                // for number of characters in users message
                {
                  matrix[i][j] = '-';                    // setting each grid location to 0, limits of grid are the key & users message length
                  cipherText[j]= 0;
                }
            }
            j=0,i=0;                                                        // reinitialising counters to begin new loop.
            while(j<length)
            {
                for(i = 0; i < A-1; i++)
                {
                    if (j>length)
                    {
                        break;
                    }
                    matrix[i][j] = (int)message[j];              // add each character to the (ith & jth) co-ordinates on the matrix in a diagonal incrementing order.
                    j++;                                        //move accross 1 collum repeat loop
                }
                for (i = A-1; i > B ; i--)                    // when i is at bottom row & greater than B decrement i to B
                {
                    if (j>length)                          // Ensuring loop cannot break grid limits
                    {
                        break;
                    }
                    matrix[i][j] = (int)message[j];      //add message character to the new position
                    j++;
                }
                for(i = B; i < A; i++)                               // when i is at position B increment i to A
                {
                    if (j>length)                                 // Ensuring loop cannot break grid limits
                    {
                        break;
                    }
                    matrix[i][j] = (int)message[j];           // add message character to the new position
                    j++;
                }                                         // tests if i or j are going past their 'key' or 'length' limits. if so, reverse i (go back up the grid)
                for(i = A-2; i >0; i--)                  // move down the (rows) by 1 // "A -2" is important here
                {
                    if (j>length)
                    {
                        break;                        // Ensuring loop cannot break grid limits
                    }
                    matrix[i][j] = (int)message[j]; // add each message letter  to the (ith,jth) co-ordinates to the matrix
                    j++;
                }
            }
///Debugger, prints message characters on the grid-------------------------------
            for(i = 0; i < A; i++)
            {
                printf(" i = %d   ", i);                   // this frints the ith collum number
                for(j = 0; j < length; j++)              // j is collum number, length is the number of characters in users message
                {
                    printf("%c", matrix[i][j]);        // prints the i x j sized grid
                    if(j>length)
                    {
                        break;
                    }
                }
                printf("\n");                      // need this on seperate printf statement, messes with character printing
            }
///------------------------------------------------------------------------------
            j=0,i=0;
           while(j<length)
            {
                for(i = 0; i <A; i++)                                // from 0th row to 'keys' integer value row
                {
                    for(j = 0; j <length; j++)                     // from 0th collum to message length collum
                    {
                        if(matrix[i][j] != '-')                     // grid at given i & j values location is not = 0
                        {
                            cipherText[c] =  matrix[i][j];      // print the strings element for given i & j values
                            c++;
                        }
                    }
                }
            }
            break;      // stopping program from entering second switch case
        }
        case 1: /// 2-level Decryption
        {
            length = strlen(cipherText);
            printf("\nDecrypting:''%s'' please wait...\n\n", cipherText);
            char character[length], Padding[length];
            for (i = 0; i <=A; i++)                           // for integer value of key
            {
                for (j = 0; j<=length; j++)                 // for number of characters in users message
                {
                  matrix[i][j] = '-';                     // populating grid with '-' symbols. limits are the key & users message length
                  message[j]=0;                          // populating message array with 0's to avoid errors
                  character[j]=0;                     // Generating array of 0's characters to buile the 'W' shape on the grid with
                  Padding[j]='~';
                }                       /// ADD PADDING TO MESSAGES, WHEN CHARACTER[J] = '~' IT ADDS THAT CHARACTER TO END OF MESSAGE.
            }
            j=0,i=0;                                 // reinitialising counters to begin new loop.
            while(j<length)                          /// Using '-' character to build the message 'shape' inside the matrix. Use this to calculate the position of each character
            {
                for(i = 0; i < A-1; i++)
                {

                    if (j>length)                    // Ensuring loop will not go outside its bounds
                    {
                        break;
                    }
                    matrix[i][j] = (int)character[j];   // add message character to the calculated location, i.e. in a diagonal incrementing order.
                    j++;                               //move accross 1 collum repeat loop
                }
                for (i = A-1; i > B ; i--)                    // when i is at bottom row & greater than B decrement i to B
                {
                    if (j>length)                        // Ensuring loop will not go outside its bounds
                    {
                        break;
                    }
                    matrix[i][j] = (int)character[j];       //add message character to the new position
                    j++;
                }
                for(i = B; i < A; i++)                        // when i is at position B increment i to A
                {
                    if(j>length)                        // Ensuring loop will not go outside its bounds
                    {
                        break;
                    }
                    matrix[i][j] = (int)character[j];       // add message character to the new position
                    j++;
                }                                             // tests if i or j are going past their 'key' or 'length' limits. if so, reverse i (go back up the grid)
                for(i = A-2; i >0; i--)                      // move down the (rows) by 1
                {
                    if (j>length)                        // Ensuring loop will not go outside its bounds
                    {
                        break;
                    }
                    matrix[i][j] = (int)character[j];      //add message character to the new position
                    j++;
                }

                if(j>length-2)
                {
                    while(i>0)
                    {
                        matrix[i][j]=(int)Padding[j];
                        i--;
                        j++;
                    }
                }

    ///replacing '-' character placed on the grid with the message characters
                int c = 0,j=0,i=0;
                for(i = 0; i < A; i++)                                // from 0th row to A, the bottom row
                {
                    for(j = 0; j <length; j++)                     // from 0th collum to the last collum. Determined by message length
                    {
                        if(matrix[i][j] != '-')                     // if strings element at given i & j values is not = 0
                        {
                            matrix[i][j] = (int)cipherText[c];  // add message character to the calculated location
                            c++;
                            j++;                             //move accross 1 collum repeat loop
                        }
                    }
                }
            }


        /// DEBUGGER ------------------------------------------------------

        for(i = 0; i < A; i++)                          // i is the rows or 'key'
        {
            printf("i = %d   ", i);                   // this frints the ith collum number
            for(j = 0; j < length; j++)              // j is collum number, length is the number of characters in users message
            {
                printf("%c", matrix[i][j]);       // prints the i x j sized grid
            }
            printf("\n");
        }
        printf("\n");
    ///-------------------------------------------------------------------

     /// Printing message characters in the calculated order.
            i=0,j=0;
            while(j<length)
            {
                for(i = 0; i < A-1; i++)
                {
                    if(matrix[i][j] != '-')                  // Grid was set to 0, all non 0 elements must be character locations
                    {
                        if(j>length)                        // Ensuring loop will not go outside its bounds
                        {
                            break;
                        }
                        message[j]= matrix[i][j];        // Assigning message characters placed on the grid in order to the message array to get final message
                        j++;
                    }
                }
                for (i = A-1; i > B ; i--)                     // when i is at bottom row & greater than B decrement i to B
                {
                    if(matrix[i][j] != '-')                    // Grid was set to 0, all non 0 elements must be character locations
                    {
                        if(j>length)                        // Ensuring loop will not go outside its bounds
                        {
                            break;
                        }
                        message[j]= matrix[i][j];          // Assigning message characters placed on the grid in order to the message array to get final message
                        j++;
                    }
                }
                for(i = B; i < A; i++)                        // when i is at position B increment i to A
                {
                    if(matrix[i][j] != '-')                   // Grid was set to 0, all non 0 elements must be character locations
                    {
                        if(j>length)                        // Ensuring loop will not go outside its bounds
                        {
                            break;
                        }
                        message[j]= matrix[i][j];         // Assigning message characters placed on the grid in order to the message array to get final message
                        j++;
                    }

                }                                             // tests if i or j are going past their 'key' or 'length' limits. if so, reverse i (go back up the grid)
                for(i = A-2; i >0; i--)                      // move down the (rows) by 1 // "A -2" is important here
                {
                    if(matrix[i][j] != '-')                  // Grid was set to 0, all non 0 elements must be character locations
                    {
                        message[j]= matrix[i][j];        // Assigning message characters placed on the grid in order to the message array to get final message
                        j++;
                        if (j>length)
                        {
                            break;                    //Ensure loop cannot go outside its bounds
                        }
                    }
                }
            }
        }
    }
}
/** railfence description
railFence 2
    variables
        message (char) is the un encrypted message eiter before encryption or after decryption
        cipherTesx (char) is the encrypted message either after encryption or before decryption
        length(int) is the number of characters in the message & the number of coluoms
        A (int)is the uers key & number of rows on the grid
*/
void railFence(char *message, char *cipherText, int length, int A) ///classic rail-fence cipher encryption
{
    int matrix[A+1][length+1];
    int i=0, j=0;

    for (i = 0; i <A; i++)                           // for integer value of key
    {
        for (j = 0; j<length+1; j++)                 // for number of characters in users message
        {
           matrix[i][j] = '-';                     // setting grid to 0, limits are the key & users message length
        }                                       // setting entire grid to zero so we can print all non zero elements later, i.e. the characters
    }
    j=0,i=0;                                              // reinitialising counters to begin new loop.
    while(j<length)
    {
        if(i+1>A || j+1>length)                        // tests if i or j are going past their 'key' or 'length' limits. if so, reverse i (go back up the grid)
        {
            for(i = A-2; i >0; i--)                  // move down the (rows) by 1 // "key -2" is important here
            {
                matrix[i][j] = (int)message[j];    /// add each message letter  to the (ith,jth) co-ordinates to the matrix in a diagonal decrementing order.
                j++;                              //move accross 1 collum repeat loop
            }
        }
        else
        {
            for(i = 0; i < A; i++)
            {
                matrix[i][j] = (int)message[j]; /// add each character to the (ith & jth) co-ordinates on the matrix in a diagonal incrementing order.
                j++;                           //move accross 1 collum repeat loop
            }
        }
    }
    //debugger-------
    for(i = 0; i < A; i++)                     // i is the rows or 'key'
    {
        printf("i = %d ", i);                // prints the ith collum number
        for(j = 0; j < length; j++)         // j is collum number, length is the number of characters in users message
        {
            printf("%c", matrix[i][j]);   // prints the characters as they are placed on the grid
        }
        printf("\n");
    }
    //------------


    int c=0;
    for(i = 0; i < A; i++)                             // from 0th row to 'keys' integer value row
    {
        for(j = 0; j < length+1; j++)                  // from 0th collum to message length value collum
        {
            if(matrix[i][j] != '-')                  // if grid element at given i & j values is not = 0
            {
                cipherText[c] = matrix[i][j];    // Assigns message character at i, j co-ordinates to the Cth array element
                c++;
            }
        }
    }
}
