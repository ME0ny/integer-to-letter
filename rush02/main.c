#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

typedef struct  p_dict
{
    char            *key;
    char            *value;
    struct p_dict   *next;
}               t_dict;

char    *ft_indict(char *number, t_dict *dict);

int ft_lenstr(char *str)
{
    int i;

    i = 0;
    while (str[i] != 0)
        i++;
    return (i);
}

void    ft_putstr(char *str)
{
    int i;

    i = -1;
    while (str[++i] != 0)
        write(1, *(str + i), 1);
}

void    ft_printletter(char *number, int shift, t_dict *dict)
{
    char    *lettes;
    char    fel[3];

    fel = "\0\0\0";
    fel[0] = number[0];
    if  (shift == 0)
    {
        letters = ft_indict(fel, dict);
        ft_putstr(letters);
        letters = ft_indict("100", dict);
        ft_putstr(letters);
    }
    else if (shift == 2)
    {
        fel[1] = "0";
        letters = ft_indict(fel, dict);
        ft_putstr(letters);
        fel[1] = number[1];
        ft_printletter(&fel[1], 1, dict);
    }
    else if(number[0] != "0")
    {
        letters = ft_indict(fel, dict);
        ft_putstr(letters);
    }
}
char    *ft_strcmp(char *str)
{
    int     i;
    char    *copy;

    copy = malloc(sizeof(char) * ft_lenstr(str));
    i = 0;
    while(str[i] != 0)
        copy[i] = str[i];
    copy[i] = str[i];
    return (copy);
}

char *ft_atoi(char *str)
{
    int i;
    char *number;
    char *key;

    number = malloc(sizeof(char) * ft_lenstr(str));
    i = 0;
    while(str[i] >= "0" && str[i] <= "9")
    {
        number[i] = str[i];
        i++;
    }
    number[i] = '\0';
    key = ft_strcmp(number);
    free(number);
    if (key[0] == 0)
        return (0);
    return (key);
}

int ft_find_value(char *str, t_dict curr)
{
    int     i;
    int     flag;
    char    *temp;
    char    *value;

    i = 0;
    while(str[i] != '\n' || str[i] != ':')
        i++;
    if (str[i] != ':')
        return (0);
    while(str[i] != '\n' || str[i] == ' ')
        i++;
    value  = ft_strcmp(str[i]);
    value[ft_lenstr(value) - 1] = 0;

    return (value);    
}

int     main(int argc, char **argv)
{
    char    *file = "numbers.dict";
    int     fd;
    char    buff[1];
    char    *dictbuff;
    int     di;
    int     lendict;
    t_dict  *dict;
    t_dict  *curr;
    t_dict  *prev;

    lendict = 0;
    bi = -1;
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        write(2, "Dict Error\n", 11);
        return (0);
    }
    dictbuff = maloc(sizeof(char) * 30000);
    dict = ft_create_node();
    curr = dict;
    while(read(fd, buffer, 1))
    {
        if(buffer != '\n')
            dictbuff[++bi] = buffer[0];
        else
            dictbuff[++bi] = 0;
            curr->key = ft_atoi(dictbuff);
            if (curr->key == 0 || ft_find_value(dictbuff, curr))
    }
    /*
    ...
    
    char    *number;
    int     i;
    int     shift;
    int     len;
    char    *letters;
    char    *copy;
    int     j;

    number = "42213000";
    i = -1;
    len = ft_lenstr(number);
    shift = 0;
    while (i < (len - 1))
    {
        i++;
        shift = (len - i) % 3;
        ft_printletter(number[i], shift, dict);
        if(shift == 2)
            i++;
        copy = ft_strcmp(number[i]);
        copy[0] = "1";
        j = 1;
        while (copy[j] != 0)
            copy[j] = 0;
        letters = ft_indict(copy, dict);
        ft_putstr(letters);
        free(copy);
    }*/
}