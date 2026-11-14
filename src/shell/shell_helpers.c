void tokenize(char *input, int *argc) /*This function changes spaces to /0. To be abble to address it as a array*/
{
    *argc = 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == ' ')
        {
            input[i] = '\0';
            argc++;
        }
    }

}