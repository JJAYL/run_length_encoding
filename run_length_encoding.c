#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    FILE *file = fopen("file_to_encode.txt", "r");
    FILE *output = fopen("encoded_file.txt", "w");
    char *code;
    size_t n = 0;
    int c;
    int count = 0;

    if (file == NULL)
        return -1; //return NULL; //could not open file
    fseek(file, 0, SEEK_END); // seek to end of file
    long size = ftell(file); // get current file pointer
    fseek(file, 0, SEEK_SET); // seek back to beginning of file
    //code = malloc(1000);
    code = malloc(size);

    while ((c = fgetc(file)) != EOF)
    {
        code[n++] = (char) c;
        //printf("%c \n", (char) c);
        if(c == code[n-2])
        {
            count++;
        }
        else
        {
            if(count < 5) //if it is 4 characters/bytes it costs more bytes to represent with an integer ex: 1B is larger than just B
            {
                for(int i = 0; i <= count; i++)
                {
                    fprintf(output, "%c", (char) code[n-2]);
                }
            }
            else 
            {
                fprintf(output, "%d%c", count + 1, (char) code[n-2]);
            }
            count = 0;
        }
    }
    fclose(file);
    fclose(output);

    //printf("%s", code);
    // don't forget to terminate with the null character
    code[n] = '\0';        

    return 0;

}
