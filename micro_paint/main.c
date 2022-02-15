#include <libc.h>
#define ARG_ERR "Error: argument\n"
#define ERR "Error: Operation file corrupted\n"
char **tab = NULL;
char c;
int x, y;
typedef struct s_elem
{
	char c, t;
	float x,w,h,y;
}t_elem;
int	ft_strlen(char *str)
{
	int i = -1;
	while (str[++i]);
	return (i);
}
void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
}
int		check_if_rectangel(t_elem *el, int line, int col)
{
	if (line < el->y || line > el->y + el->h || col < el->x || col > el->x + el->w)
		return (0);
	else if (col - el->x < 1 || (el->x + el->w ) - col < 1 || line - el->y < 1 || (el->y + el->h) - line < 1)
		return (2);
	return (1);
}
int main(int ac, char **av)
{
	if (ac != 2)
		return (ft_putstr(ARG_ERR), 1);
	FILE *fd = NULL;
	int col, line, res, i = -1;
	t_elem el;
	if ((fd = fopen(av[1], "r")))
	{
		if ((res = fscanf(fd, "%d %d %c\n", &x, &y, &c)) == 3 && x > 0 && x <= 300 && y > 0 && y <= 300)
		{
			tab = (char **)malloc(sizeof(char *) * y + 1);
			tab[y] = 0;
			while (++i < y)
			{
				tab[i]  = malloc(sizeof(char ) * x + 1);
				tab[i][x] = 0;
				memset(tab[i], c, x);
			}
		}
		while (TRUE)
		{
			res = fscanf(fd, "%c %f %f %f %f %c\n", &el.t, &el.x, &el.y, &el.w, &el.h, &el.c);
			if (res == -1)
			{
				i = -1;
				while (tab[++i])
					ft_putstr(tab[i]);
				fclose (fd);
				return (0);
			}
			else if (res != 6 || el.w <= 0 || el.h <= 0 || (el.t != 'r' && el.t != 'R'))
				return (ft_putstr(ERR), 1);
			else{
				line = -1;
				while (++line < y)
				{
					col = -1;
					while (++col < x)
					{
						res = check_if_rectangel(&el, line, col);
						if ((res == 2 && el.t == 'r') || (res && el.t == 'R'))
							tab[line][col] = el.c;
					}
				}
			}
		}
	}
	return (ft_putstr(ERR), 1);
}