#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LETTERS 20

int *data;
int maxLines;
char **reserved_words;
int *reserved_numbers;
int reserved_words_count = 13;

// get
void Welcome();
void PrgLoadLoop();
void DataInitialization();
void ReserveWords();
int GetLine(int line_index);
bool Translate(char typed_line[], int *result);
bool CheckWord(char typed_word[], int *result);

// set
void PrgExtLoop();

// help
int DigitCount(int n);
bool isLetter(char c);
bool isNumber(char c);

int main()
{
    Welcome();
    char controller;
    do
    {
        // get data
        DataInitialization();
        ReserveWords();
        PrgLoadLoop();

        do
        {
            // execute data
            PrgExtLoop();
            do
            {
                printf("Press P to write another program.\n");
                printf("Press E to execute the remaining program again.\n");
                printf("Press S to stop the compiler.\n");

                fflush(stdin);
                scanf("%c", &controller);
                fflush(stdin);

                if(controller != 'P' && controller != 'E' && controller != 'S')
                {
                    printf("Undefined letter pressed!\n");
                    printf("Please press the following: \n");
                }
            } while(controller != 'P' && controller != 'E' && controller != 'S');
        } while(controller == 'E');

    } while(controller == 'P');

    printf("Program finished successfully!\n");

    return 0;
}

/// get
void Welcome()
{
    printf("***        Welcome to Parsa's SML (Simpletron Machine Language)        ***\n");
    printf("***        ____________________________________________________        ***\n");
    printf("***        ____________________________________________________        ***\n");
    printf("***        ____________________________________________________        ***\n");
    printf("***        ____________________________________________________        ***\n");
    printf("***        ____________________________________________________        ***\n\n\n\n");
}

void PrgLoadLoop()
{
    printf("Please enter your SML code: \n");

    int nxtLn;
    nxtLn = GetLine(0);
    for(int i = 0; nxtLn != -99999; i++)
    {
        if(nxtLn > 9999)
        {
            printf("Syntax error!");
            exit(-1);
        }

        data[i] = nxtLn;
        nxtLn = GetLine(i + 1);
    }

    printf("--   Program loading completed   --\n");
}

void DataInitialization()
{
    while(true)
    {
        printf("How many lines is your max need? ");
        char str[100];
        fgets(str, 100, stdin);

        char *temp;
        maxLines = (int) strtol(str, &temp, 10);

        if(maxLines < 100)
            printf("Max lines should be more than 100\n");
        else
            break;
    }
    data = calloc(maxLines, sizeof(int));
}

void ReserveWords()
{
    // reserve storage for words
    reserved_words = (char **) malloc(reserved_words_count * sizeof(char *));
    for(int i = 0; i < reserved_words_count; i++)
        reserved_words[i] = (char *) malloc(MAX_WORD_LETTERS * sizeof(char));

    reserved_numbers = (int *) malloc(reserved_words_count * sizeof(int));

    // define words and their assigned numbers
    reserved_words[0] = "READ";
    reserved_numbers[0] = 10;

    reserved_words[1] = "WRITE";
    reserved_numbers[1] = 11;

    reserved_words[2] = "LOAD";
    reserved_numbers[2] = 20;

    reserved_words[3] = "STORE";
    reserved_numbers[3] = 21;

    reserved_words[4] = "ADD";
    reserved_numbers[4] = 30;

    reserved_words[5] = "SUBTRACT";
    reserved_numbers[5] = 31;

    reserved_words[6] = "DIVIDE";
    reserved_numbers[6] = 32;

    reserved_words[7] = "MULTIPLY";
    reserved_numbers[7] = 33;

    reserved_words[8] = "BRANCH";
    reserved_numbers[8] = 40;

    reserved_words[9] = "BRANCHNEG";
    reserved_numbers[9] = 41;

    reserved_words[10] = "BRANCHZERO";
    reserved_numbers[10] = 42;

    reserved_words[11] = "BRANCHPOS";
    reserved_numbers[11] = 43;

    reserved_words[12] = "HALT";
    reserved_numbers[12] = 50;
}

int GetLine(int line_index)
{
    printf("%0*d : ", DigitCount(maxLines - 1), line_index);
    char typed_line[100];

    fgets(typed_line, 100, stdin);

    if(strncmp(typed_line, "END", 3) == 0)
        return -99999;

    int command;
    if(Translate(typed_line, &command) == false)
    {
        printf("Syntax error!\n");
        exit(-1);
    }

    int location = 0;
    for(int i = 0; typed_line[i] != 0; i++)
        if(isNumber(typed_line[i]))
            location = location * 10 + (typed_line[i] - '0');

    return command * 100 + location;
}

bool Translate(char typed_line[], int *result)
{
    char temp_line[100];
    for(int i = 0; ; i++)
    {
        if(isLetter(typed_line[i]))
            temp_line[i] = typed_line[i];
        else
        {
            temp_line[i] = 0;
            break;
        }
    }

    return CheckWord(temp_line, result);
}

bool CheckWord(char typed_word[], int *result)
{
    for(int i = 0; i < reserved_words_count; i++)
        if(strcmp(typed_word, reserved_words[i]) == 0)
        {
            *result = reserved_numbers[i];
            return true;
        }

    return false;
}


/// set
void PrgExtLoop()
{
    printf("--   Program execution starts   --\n");
    register int accumulator = 0;
    register int instructionCounter = 0;
    register int instructionRegister = data[0];
    register int operationCode = instructionRegister / 100;
    register int operand = instructionRegister % 100;

    while(operationCode != 50)
    {
        {
            if(operationCode == 10)
            {
                // read
                char str[4];
                scanf("%s", str);
                int temp;
                char *endptr;
                temp = (int) strtol(str, &endptr, 10);
                data[operand] = temp;

                instructionCounter++;
            } else if(operationCode == 11)
            {
                // write
                printf("%d\n", data[operand]);
                instructionCounter++;
            } else if(operationCode == 20)
            {
                // load
                accumulator = data[operand];
                instructionCounter++;
            } else if(operationCode == 21)
            {
                // store
                data[operand] = accumulator;
                instructionCounter++;
            } else if(operationCode == 30)
            {
                // add
                accumulator += data[operand];
                instructionCounter++;
            } else if(operationCode == 31)
            {
                // subtract
                accumulator -= data[operand];
                instructionCounter++;
            } else if(operationCode == 32)
            {
                // divide
                if(data[operand] == 0)
                {
                    printf("--   Divided by zero   --\n");
                    printf("--   Program abnormally terminated   --");
                    exit(-1);
                }
                accumulator /= data[operand];
                instructionCounter++;
            } else if(operationCode == 33)
            {
                // multiply
                accumulator *= data[operand];
                instructionCounter++;
            } else if(operationCode == 40)
            {
                // branch
                instructionCounter = operand;
            } else if(operationCode == 41)
            {
                // branch if  accumulator is negative
                if(accumulator < 0)
                    instructionCounter = operand;
                else
                    instructionCounter++;
            } else if(operationCode == 42)
            {
                // branch if  accumulator is zero
                if(accumulator == 0)
                    instructionCounter = operand;
                else
                    instructionCounter++;
            }else if(operationCode == 43)
            {
                // branch if  accumulator is zero
                if(accumulator > 0)
                    instructionCounter = operand;
                else
                    instructionCounter++;
            }
        }

        instructionRegister = data[instructionCounter];
        operationCode = instructionRegister / 100;
        operand = instructionRegister % 100;
    }
    printf("--   Program execution finished   --\n");
}



/// help
int DigitCount(int n)
{
    int count = 0;
    while(n > 0)
    {
        n /= 10;
        count++;
    }

    return count;
}

bool isLetter(char c)
{
    if(c >= 'A' && c <= 'Z')
        return true;
    if(c >= 'a' && c <= 'z')
        return true;

    return false;
}

bool isNumber(char c)
{
    if(c >= '0' && c <= '9')
        return true;

    return false;
}