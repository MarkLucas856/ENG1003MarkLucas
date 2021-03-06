#include <stdio.h>
#include <stdlib.h>
#include <string.h>
    /**  high-level operation
    Variables:
            int:
                 A = 'key' or the number of rows,
                 B = second key or height of the second peak in the algorithm
                 c = message character counter
            length = number of characters in the message
               dir = users option of encrypting or decrypting. used in switch case.
          Filesize = after filesize is measured it is stored in this variable
        Char:
               *message = pointer to users entered message
            EndMessage = pointer to Character scanned from user input to indicate end of message
            *Ciphertext = pointer to 1-D array. used to store array size
                Matrix = 2d array. A grid used to build the message 'shape'
             Character = a '-'character used in decryption to build the message shape on the grid
        FILE:
            *FileText = text read from a file to be encrypted or decrypted
                *Size = Used to measure the filesize
              Message = file containing users message, either before encryption or after decryption.
           CipherText = file containing users message, either before decryption or after encryption
        case a = 2-level rail-fence cihper algorithm
            case 0 = encryption
            case 1 = decryption
        case b = classic rail-fence cihper encryption algorithm
    Functions
        RailFence2
            void function, this returns no value. Take 6 arguments, 2 char pointers & 4 int variables.
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
        run program and follow the instructions. You will be given options to use the classic cipher or 2-level. to select an option enter the character or number
        shown followed by the <enter> key. You will then be given further options to either encrypt or decrypt a message.
        Do not enter a different datatype to what is being asked or the program will fail.

        Once message isread from file you will be promped to enter 2 seperate int values for the keys.
    limitations are:

    brief program flow overview:
        -run program
        -ask user; classic(0) or 2-level cipher algorithm.
        -ask user; encrypt (0) or decrypt (1) (encryption only, for classic rail-fence cipher)
        -enter designated switch case
        -read message from file
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
int main()
{
    int dir,length, A, B, FileSize, i=0;        // Declaring main's int variables
    char  userOptions, c, EndMessage;          // Users algorithm choice, a file text character counter & a character to indicate end of message
    FILE *FileText;                           // pointer for the text held witin the chosen message file
    FILE *Size;                              // Used to measure file size & declare arrays with.
    FILE *OutPut;
    printf("Welcome to cipher algorithms.\n\n");                                // User interface
    printf("For 2-level rail-fence cipher algorithm, press:\n");
    printf(" a) followed by <enter>\n");
    printf("for classical rail-fence cipher  encryption algorithm, enter:\n");
    printf(" b) followed by <enter>\n");
    scanf("%c", &userOptions);
    if(userOptions <'a' || userOptions >'b')                    //Ensuring user selects a valid option.
    {
        printf("Error, select option: a) or b)\n");
        scanf("%c", &userOptions);
    }
    else;
    switch(userOptions)
    {
        case 'a':  ///option 'a' (2-level rail-fence cipher)
        {
            printf("For message encryption, press\n 0) followed by <enter>\n");
            printf("For message decryption, press\n 1) followed by <enter>\n");
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
                    printf("2-level rail-fence encryption\n\n");
                    printf("Retrieving message from file...\n");
                    Size = fopen("Message.txt", "r");                         // Measuring size of file
                    if(Size == NULL)
                    {
                        perror("fopen()");                                  // Print a scripted error message for error encountered
                        return 1;
                    }
                    fseek(Size, 0, SEEK_END);                            // measuring message length held within the file
                    FileSize = ftell(Size);
                    char message[FileSize+1], cipherText[FileSize+1]; // Using size of file to declare and initialise array sizes.
                    printf("Message contains %d characters",FileSize);
                    FileText = fopen("Message.txt", "r");                        // read message from .txt file called message
                    if(FileText == NULL)
                    {
                        perror("fopen()");                                    // Print a pre-scripted error message for specific error encountered
                        return 1;
                    }
                    fscanf(FileText, "%c", &c);                            // scan here to know if at end of file before entering loop
                    while(!feof(FileText)&& i< FileSize)                  // determines if at end of file
                    {
                        message[i]=c;                                   // Scanning file, adding character to array element i, increment i add next character to array.
                        i++;                                           // c holds a message character, adds it to the ith array element, moves on to next character and repeats
                        fscanf(FileText, "%c", &c);                   //feof is self incrementing for its counter 'c'
                    }
                    length = strlen(message);
                    if(message[i-1]=='\n')                         // removing extra newline character read by fscanf from message
                    {
                        message[i-1]='\0';
                    }
                    message[i]=0;                              // changing last element of array to 0 from extra increment of i to avoid extra characters being printed
                    printf("\nMessage found: '%s'\n\n", message);
                    printf("If this is correct, press the '~' key followed by <enter> to continue.\n");
                    fflush(stdin);
                    scanf("%[^~]c", &EndMessage);           // scan for a '~' symbol
                    fflush(stdin);                         // Clearing buffer for next input
                    length = strlen(message);
                    printf("Enter your two seperate integer keys:\n Key A: \n");
                    scanf("%d", &A);
                    printf("Key B (must be less than the previous key 'A'): \n");
                    scanf("%d", &B);
                    while(B>=A)                                 // Ensuring the required rule of B<A is met
                    {
                        printf("\nError, key B must be < key A\n\n");
                        printf("Enter your two seperate integer keys:\n Key A: \n");
                        scanf("%d", &A);
                        printf("Key B (must be less than the previous key 'A'): \n");
                        scanf("%d", &B);
                    }
                    railFence2(message, cipherText, length, A, B, dir);
                    printf(" Your encryted message is:\n '%s'\n", cipherText);
                    OutPut = fopen("CipherText.txt", "w");
                    if(OutPut == NULL)                                          // Writing encrypted message to the cipherText.txt file
                    {
                        perror("fopen()");                                    // Print a pre-scripted error message for specific error encountered
                        return 1;
                    }
                    fprintf(OutPut, "%s", cipherText);                     //   printing the ciphertext string inside the file
                    printf("Successfully written to CipherText file.\n\n");
                    return 0;
                }
                case 1: ///(2-level decryption)
                {
                    printf("2-level rail-fence Decryption\n\n");
                    printf("Reading from file, ");
                    Size = fopen("CipherText.txt", "r");                     // read message from .txt file called message
                    if(Size == NULL)
                    {
                        perror("fopen()");                                // Print a scripted error message for error encountered
                        return 1;
                    }
                    fseek(Size, 0, SEEK_END);                         // measuring message length held within the file
                    FileSize = ftell(Size);
                    printf("File contains %d characters.\n", FileSize);
                    char message[FileSize+2], cipherText[FileSize+2];      // Using filesize to declare and initialise array sizes.
                    FileText = fopen("CipherText.txt", "r");              // read message from .txt file called message
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
                    printf(" The encrypted message is: '%s'\n\n", cipherText);
                    printf("If this is correct, press the '~' key followed by <enter> to continue.\n");
                    fflush(stdin);
                    scanf("%[^~]c", &EndMessage);
                    fflush(stdin);
                    printf("Enter your two seperate integer keys:\n Key A: \n");
                    scanf("%d", &A);
                    printf("Key B (must be less than the previous key 'A'): \n");
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
                    printf("The decrypted message is:\n '%s'\n", message);
                    OutPut = fopen("Message.txt", "w");
                    if(OutPut == NULL)
                    {
                        perror("fopen()");
                        return 1;
                    }
                    fprintf(OutPut, "%s", message);
                    fclose(OutPut);
                    printf("Successfully written to message file \n\n");
                    return 01;
                }
            }
        }
        case 'b':   ///option 'b'(classic encryption)
        {
            printf("Classic rail-fence encryption\n\n");
            printf("reading file..");
            Size = fopen("Message.txt", "r");                         // read message from .txt file called message
            if(Size == NULL)
            {
                perror("fopen()");                                  // Print a scripted error message for error encountered
                return 1;
            }
            fseek(Size, 0, SEEK_END);                            // measuring message length held within the file
            FileSize = ftell(Size);
            printf("contains %d characters\n",FileSize);
            char message[FileSize+1], cipherText[FileSize+1]; // Using size of file to declare and initialise array sizes.
            FileText = fopen("Message.txt", "r");                      // read message from .txt file called message
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
            printf("Message found: '%s'\n\n", message);
            printf("If this is correct, press the '~' key followed by <enter> to continue.\n");
            fflush(stdin);
            scanf("%[^~]c", &EndMessage);
            fflush(stdin);
            printf("\nEnter your key (must be an integer): \n");
            scanf("%d", &A);
            railFence(message, cipherText, length, A);                       //Calling function for message encryption
            printf("\n Your encryted message is: ''%s''\n", cipherText);
            OutPut = fopen("CipherText.txt", "w");
            if(OutPut == NULL)                                          // Writing encrypted message to the cipherText.txt file
            {
                perror("fopen()");                                    // Print a pre-scripted error message for specific error encountered
                return 1;
            }
            fprintf(OutPut, "%s", cipherText);
            printf("Successfully written to CipherText file.\n\n");
            return 02;
        }
        break;
    }
}
/** railfence 2 description
railFence 2
    This function takes users message length and key (A) and creates a grid. it encrypts messages by placing them on the grid
    in a 'W' pattern and printing off the characters one by one going from left to right on the collums then down a row
    and left to right again.
    i - increasing i moves down the grid
    j - increasing j moves accross the grid (to the right)
*/
void railFence2(char *message, char *cipherText, int length, int A, int B, int dir) ///2-level rail-fence cipher algorithm
 {
    int matrix[A+2][length+2];
    int i=0, j=0, c=0;
    switch(dir)
    {
        case 0: /// 2-level Encription.
        {
            length = strlen(message);                                      // re-declaring length to ensure it was not altered in the file i/o section in main
            printf("\n encrypting:''%s'' please wait...\n\n", message);
            for (i = 0; i <A; i++)                                       // for i < integer value of key
            {
                for (j = 0; j<=length; j++)                            // for number of characters in users message
                {
                  matrix[i][j] = '-';                                // setting each grid location to '-' symbol limits of grid are the key & users message length
                  cipherText[j]= 0;
                }
            }
            j=0,i=0;                                                      // reinitialising counters to begin new loop.
            while(j<length)
            {
                for(i = 0; i < A-1; i++)                                // Moving down the grid
                {
                    if (j>length)                                     // Keeping loop within its limits
                    {
                        break;
                    }
                    matrix[i][j] = (int)message[j];                // add a message character to the (ith & jth) co-ordinates on the matrix in a diagonal incrementing order.
                    j++;                                          //move accross (to the right) 1 collum repeat loop
                }
                for (i = A-1; i > B ; i--)               // when i is at bottom row & greater than B decrement i to B
                {
                    if (j>length)                      // Ensuring loop cannot break grid limits
                    {
                        break;
                    }
                    matrix[i][j] = (int)message[j]; //add message character to the new position
                    j++;
                }
                for(i = B; i < A; i++)                                // when i is at position B increment i to A
                {
                    if (j>length)                                   // Ensuring loop cannot break grid limits
                    {
                        break;
                    }
                    matrix[i][j] = (int)message[j];             // add message character to the new position
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
            j=0,i=0;
           while(j<length)
            {
                for(i = 0; i <A; i++)                                 // from 0th row to 'keys' integer value row
                {
                    for(j = 0; j <length; j++)                      // from 0th collum to message length collum
                    {
                        if(matrix[i][j] != '-')                   // grid at given i & j values location is not = 0
                        {
                            cipherText[c] =  matrix[i][j];      // Assigning message character to the Cth array element
                            c++;
                        }
                    }
                }
            }
            break;                                         // stopping program from entering second switch case
        }
        case 1: /// 2-level Decryption
        {
            length = strlen(cipherText);                         // re-initialising length to avoid file i/o altering value in any way
            printf("\nDecrypting:''%s'' please wait...\n\n", cipherText);
            char character[length];
            for (i = 0; i <=A; i++)                           // for integer value of key
            {
                for (j = 0; j<=length; j++)                 // for number of characters in users message
                {
                  matrix[i][j] = '-';                     // populating grid with '-' symbols. limits are the key & users message length
                  message[j]=0;                          // populating message array with 0's to avoid errors
                  character[j]=0;                       // Generating array of 0's characters to buile the 'W' shape on the grid with
                }
            }
            j=0,i=0;                                                 // reinitialising counters to begin new loop.
            while(j<length)                                         // Using '-' character to build the message 'shape' inside the matrix. Use this to calculate the position of each character
            {
                for(i = 0; i < A-1; i++)
                {
                    if (j>length)                               // Ensuring loop will not go outside its bounds
                    {
                        break;
                    }
                    matrix[i][j] = (int)character[j];        // add message character to the calculated location, i.e. in a diagonal incrementing order.
                    j++;                                    //move accross 1 collum repeat loop
                }
                for (i = A-1; i > B ; i--)                            // when i is at bottom row & greater than B decrement i to B
                {
                    if (j>length)                                   // Ensuring loop will not go outside its bounds
                    {
                        break;
                    }
                    matrix[i][j] = (int)character[j];           //add message character to the new position
                    j++;
                }
                for(i = B; i < A; i++)                                // when i is at position B increment i to A
                {
                    if(j>length)                                    // Ensuring loop will not go outside its bounds
                    {
                        break;
                    }
                    matrix[i][j] = (int)character[j];           // add message character to the new position
                    j++;
                }                                                     // tests if i or j are going past their 'key' or 'length' limits. if so, reverse i (go back up the grid)
                for(i = A-2; i >0; i--)                              // move down the (rows) by 1
                {
                    if (j>length)                                  // Ensuring loop will not go outside its bounds
                    {
                        break;
                    }
                    matrix[i][j] = (int)character[j];          //add message character to the new position
                    j++;
                }
                int c = 0,j=0,i=0;                                     //replacing '-' character placed on the grid with the message characters
                for(i = 0; i < A; i++)                                // from 0th row to A, the bottom row
                {
                    for(j = 0; j <length; j++)                      // from 0th collum to the last collum. Determined by message length
                    {
                        if(matrix[i][j] != '-')                   // if strings element at given i & j values is not = 0
                        {
                            matrix[i][j] = (int)cipherText[c];  // add message character to the calculated location
                            c++;
                            j++;                             //move accross 1 collum repeat loop
                        }
                    }
                }
            }
            i=0,j=0;
            while(j<length)                                      // Moving through the grid in the 'W' pattern to assign each character in to array in the correct order
            {
                for(i = 0; i < A-1; i++)
                {
                    if(matrix[i][j] != '-')                  // Grid was set to '-' characters all non '-' elements must be character locations
                    {
                        if(j>length)                       // Ensuring loop will not go outside its bounds
                        {
                            break;
                        }
                        message[j]= matrix[i][j];       // Assigning message characters placed on the grid in order to the message array to get final message
                        j++;
                    }
                }
                for (i = A-1; i > B ; i--)                            // when i is at bottom row & greater than B decrement i to B
                {
                    if(matrix[i][j] != '-')                         // Grid was set to 0, all non 0 elements must be character locations
                    {
                        if(j>length)                              // Ensuring loop will not go outside its bounds
                        {
                            break;
                        }
                        message[j]= matrix[i][j];              // Assigning message characters placed on the grid in order to the message array to get final message
                        j++;
                    }
                }
                for(i = B; i < A; i++)                                     // when i is at position B increment i to A
                {
                    if(matrix[i][j] != '-')                              // Grid was set to 0, all non 0 elements must be character locations
                    {
                        if(j>length)                                   // Ensuring loop will not go outside its bounds
                        {
                            break;
                        }
                        message[j]= matrix[i][j];                   // Assigning message characters to the message array
                        j++;
                    }
                }                                          // tests if i or j are going past their 'key' or 'length' limits. if so, reverse i (go back up the grid)
                for(i = A-2; i >0; i--)                   // move down the (rows) by 1 // "A -2" is important here
                {
                    if(matrix[i][j] != '-')             // Grid was set to 0, all non 0 elements must be character locations
                    {
                        message[j]= matrix[i][j];     // Assigning message characters placed on the grid in order to the message array to get final message
                        j++;
                        if (j>length)
                        {
                            break;                 //Ensure loop cannot go outside its bounds
                        }
                    }
                }
            }
        }
    }
}
/** railfence description
railFence
    This function takes the users message and arranged them on a grid in a zig-zag pattern.
    then it prints characters from left to right then down a row and left to right again.
    the grid called(matix)is a 2-d array, its size is determined by the users key (A)and message length.

*/
void railFence(char *message, char *cipherText, int length, int A) ///classic rail-fence cipher encryption
{
    int matrix[A+1][length+1];
    int i=0, j=0;
    for (i = 0; i <A; i++)                      // i is the rows, from the top row (0) to the bottom row (A)
    {
        for (j = 0; j<length+1; j++)          // from the first collum to the last collum (Length of users message)
        {
           matrix[i][j] = '-';              // Building grid with '-' characters, so we can print all non '-' elements later, i.e. the characters
        }
    }
    j=0,i=0;                                              // reinitialising counters to begin new loop.
    while(j<length)
    {
        if(i+1>A || j+1>length)                        // Moving back up the grid
        {
            for(i = A-2; i >0; i--)                  // move down the (rows) by 1 // "key -2" is important here
            {
                matrix[i][j] = (int)message[j];    // add each message letter  to the (ith,jth) co-ordinates to the matrix in a diagonal decrementing order.
                j++;                              //move accross 1 collum repeat loop
            }
        }
        else
        {
            for(i = 0; i < A; i++)                      //moving down the grid
            {
                matrix[i][j] = (int)message[j];       //add each character to the (ith & jth) co-ordinates on the matrix in a diagonal incrementing order.
                j++;                                 //move accross 1 collum repeat loop
            }
        }
    }
    int c=0;
    for(i = 0; i < A; i++)                               // from 0th row to 'keys' integer value row
    {
        for(j = 0; j < length+1; j++)                  // from 0th collum to message length value collum
        {
            if(matrix[i][j] != '-')                  // if grid element at given i & j values is not = 0
            {
                cipherText[c] = matrix[i][j];      // Assigns message character at i, j co-ordinates to the Cth array element
                c++;
            }
        }
    }
}
