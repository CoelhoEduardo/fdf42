#include "fdf.h"

static int	ft_getwords(char *s, char c)
{
	int	wrd;
	int	i;

	wrd = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			wrd++;
            while (s[i] != c && s[i])
            {
                i++;
            }
		}
        else
        {
            i++;
        }
		
	}
	return (wrd);
}

int get_rows(char *file_name)
{
    int row;
    int fd;
    char    *gnl;


    fd = open(file_name, O_RDONLY);
    row = 0;
    gnl = get_next_line(fd);
    while(gnl)
    {
        row++;
        gnl = get_next_line(fd);
        free(gnl);
    }
    close(fd);
    free(gnl);
    return (row);
}

int get_collumn(char *file_name)
{
    int collumn;
    int fd;
    char    *gnl;

    fd = open(file_name, O_RDONLY);
    gnl = get_next_line(fd);
    collumn = ft_getwords(gnl, ' ');
    while (gnl)
    {
        gnl = get_next_line(fd);
        free(gnl);
    }
    close(fd);
    return(collumn);
}
