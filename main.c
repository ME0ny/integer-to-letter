#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct  p_dict
{
    char            *key;
    char            *value;
    struct p_dict   *next;
}               t_dict;

//char    *ft_indict(char *number, t_dict *dict);

t_dict  *ft_create_node()
{
    t_dict *node; 
    node = malloc(sizeof(t_dict));
    node->next = NULL;
    return (node);
}

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
        write(1, str + i, 1);
}

char    *ft_strcmp(char *str)
{
    int     i;
    char    *copy;

    copy = malloc(sizeof(char) * ft_lenstr(str));
    i = -1;
    while(str[++i] != 0)
        copy[i] = str[i];
    copy[i] = str[i];
    return (copy);
}

/*void    ft_printletter(char *number, int shift, t_dict *dict)
{
    char    *lettes;
    char    *fel;

    fel = ft_strcmp("\0\0\0");
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
        *(fel + 1) = "0";
        letters = ft_indict(fel, dict);
        ft_putstr(letters);
        fel[1] = number[1];
        ft_printletter(&fel[1], 1, dict);
    }
    else if(*number != "0")
    {
        letters = ft_indict(fel, dict);
        ft_putstr(letters);
    }
}*/

char *ft_atoi(char *str)
{
    int i;
    char *number;
    char *key;

    number = malloc(sizeof(char) * ft_lenstr(str));
    i = 0;
    while (*(str + i) >= '0' && *(str + i) <= '9')
    {
        number[i] = str[i];
        i++;
    }
    number[i] = '\0';
    while (*(str + i) != ':' && *(str + i) != ' ' && *(str + i) != '\n')
        i++;
    if (*(str + i) == '\n')
        return (0);
    key = ft_strcmp(number);
    free(number);
    return (key);
}

int ft_find_value(char *str, t_dict *curr)
{
    int     i;
    char    *value;

    i = 0;
    while(str[i] != '\n' && str[i] != ':')
        i++;
    if (str[i] == '\n')
        return (0);
    i++;
    while(str[i] != '\n' && str[i] == ' ')
        i++;
    value  = ft_strcmp(str + i);
    value[ft_lenstr(value) - 1] = 0;
    curr->value = value;
    return (1);    
}

int ft_strdiff(char *s1, char *s2)
{
    int i;

    i = 0;
    while(s1[i] != 0 || s2[i] != 0)
    {
        if(s1[i] != s2[i])
            return (1);
        i++;
    }
    return (0);
}

int ft_check_key(char *key, t_dict *dict)
{
    t_dict  *curr;

    curr = dict;
    while (curr->next != NULL)
    {
        if (ft_strdiff(key, curr->key) == 0)
            return (0);
        curr = curr->next;
    }
    return (1);
}

int     main(int argc, char **argv)
{
    char    *file = "numbers.dict";
    int     fd;
    char    buff[2];
    char    *dictbuff;
    char    *dictbuffcur;
    int     lendict;
    int     di;
    t_dict  *dict;
    t_dict  *curr;
    t_dict  *prev;

    lendict = 0;
    di = -1;
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        write(2, "Dict Error\n", 11);
        return (0);
    }
    dictbuff = malloc(sizeof(char) * 30000);
    dictbuffcur = dictbuff;
    dict = ft_create_node();
    curr = dict;
    prev = NULL;
    while(read(fd, buff, 1))
    {
        if(buff[0] != '\n')
            dictbuff[++di] = buff[0];
        else
        {
            dictbuff[++di] = 0;
            curr->key = ft_atoi(dictbuff);
            int check_key = ft_check_key(curr->key, dict);
            int find_value = ft_find_value(dictbuff, curr);
            if (curr->key == 0 || check_key == 0
            || find_value == 0)
            {
                write(2, "Dict Error\n", 11);
                //ft_free(curr);
                free(dictbuff);
                return (0);
            }
            if (prev != NULL)
                prev->next = curr;
            prev = curr;
            curr = ft_create_node();
            di = -1;
            printf("%s\n", prev->value);
        }
    }
    free(dictbuff);
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