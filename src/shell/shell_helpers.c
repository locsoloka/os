void tokenize(char *input, int *argc)
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