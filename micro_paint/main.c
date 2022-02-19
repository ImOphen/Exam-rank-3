#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define ERR_ARG "Error: argument\n"
#define ERR_FILE "Error: Operation file corrupted\n"

int x;
int y;
char c;
char **tab = NULL;


typedef struct s_element
{
    char t;
    float x;
    float y;
    float w;
    float h;
    char c;
}               t_element;

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

void ft_putstr_ln(char *str)
{
    int i = 0;
    while (str[i])
        write(1, &str[i++], 1);
    write(1, "\n", 1);
}

void error(FILE *fd, int err)
{
    if (err == 1)
        write(1, ERR_ARG, ft_strlen(ERR_ARG));
    else if (err == 2)
        {
            write(1, ERR_FILE, ft_strlen(ERR_FILE));
            if (fd)
                fclose(fd);
        }
}

int check_if_rectangle(t_element *el,int line,int col)
{
    if (line < el->y || line > el->y + el->h || col < el->x || col > el->x + el->w)
        return 0;
    if (col - el->x < 1 || (el->x + el->w) - col < 1 || line - el->y < 1 || (el->y +el->h) - line < 1)
        return 2;
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return(error(NULL, 1),1);
    FILE *fd = NULL;
    int res;
    t_element el;
    int line = 0;
    int col;
    int i = 0;
    if ((fd = fopen(argv[1], "r")))
    {
        if ((res = fscanf(fd, "%d %d %c\n", &x, &y, &c)) == 3 && x > 0 && x <= 300 && y > 0 && y <= 300)
        {
            tab = malloc(sizeof(char *) * y + 1);
            tab[y] = 0;
            while (i < y)
            {
                tab[i] = malloc(sizeof(char) * x + 1);
                tab[i][x] = 0;
                memset(tab[i], c, x);
                i++;
            }
            while(1)
            {
                res = fscanf(fd, "%c %f %f %f %f %c\n", &el.t, &el.x, &el.y, &el.w, &el.h, &el.c);
                if (res == -1)
                {
                    i = 0;
                    while (tab[i])
                        ft_putstr_ln(tab[i++]);
                    fclose(fd);
                    return 0;
                }
                else if (res != 6 || el.w <= 0 || el.h <= 0 || (el.t != 'r' && el.t != 'R'))
                    return(error(fd, 2), 1);
                else
                {
                    line = 0;
                    while(line < y)
                    {
                        col = 0;
                        while (col < x)
                        {
                            res = check_if_rectangle(&el, line, col);
                            if (res == 2 && el.t == 'r')
                                tab[line][col] = el.c;
                            else if (res && el.t == 'R')
                                tab[line][col] = el.c;
                            col++;
                        }
                        line++;
                    }
                }
            }
        }
    }
    return(error(fd, 2), 1);
}