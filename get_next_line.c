/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 15:15:22 by avella            #+#    #+#             */
/*   Updated: 2016/02/01 17:39:14 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		lineorend(char *chaine)
{
	int result;
	int i;

	i = 0;
	result = 4;
	while (chaine[i] != '\0' && result == 4 && chaine[i] != EOF)
	{
		if (chaine[i] == '\n')
			result = 1;
		i++;
	}
	if (i == 0)
		result = 0;
	else if (chaine[i] == EOF && result == 4)
		result = 3;
	else if (chaine[i] == '\0' && result == 4)
		result = 3;
	return (result);
}

int		amalloc(char *chaine)
{
	int i;

	i = 0;
	while (chaine[i] != '\n' && chaine[i] != '\0' && chaine[i] != EOF)
		i++;
	return (i);
}

int		give_thereturn(char *chaine, int ret)
{
	int thereturn;

	thereturn = 4;
	if (ret == -1)
		thereturn = -1;
	else if (lineorend(chaine) == 1)
		thereturn = 1;
	else if (lineorend(chaine) == 0)
		thereturn = 0;
	else if (lineorend(chaine) == 3 && ret == 0)
		thereturn = 1;
	return (thereturn);
}

char	**my_line(char **chaine, int fd, char **line, int mall)
{
	int i;

	i = 0;
	mall = amalloc(chaine[fd]);
	line[0] = ft_strnew(mall + 1);
	while (i < mall)
	{
		line[0][i] = chaine[fd][i];
		i++;
	}
	line[0][i] = '\0';
	i = 0;
	while (chaine[fd][i] != '\n' && chaine[fd][i] != '\0')
		i++;
	i++;
	chaine[fd] = ft_strsub(chaine[fd], i, ft_strlen(chaine[fd]));
	return (line);
}

int		get_next_line(int const fd, char **line)
{
  if(BUFF_SIZE > 200000)
    {
      ft_putstr("dqwqqwd");
    return (-1);
    }
	int			thereturn;
	int			ret;
	char		buf[BUFF_SIZE + 1];
	static char	*chaine[256];
	int			mall;

	mall = 0;
	thereturn = 4;
	if (fd < 0 || line == NULL || BUFF_SIZE < 1 || fd > 256)
		return (-1);
	if (!chaine[fd])
		chaine[fd] = ft_strnew(BUFF_SIZE + 1);
	while (thereturn == 4)
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) >= 0)
		{
			buf[ret] = '\0';
			chaine[fd] = ft_strjoin(chaine[fd], buf);
		}
		if (ret == -1)
			return (-1);
		thereturn = give_thereturn(chaine[fd], ret);
	}
	my_line(chaine, fd, line, mall);
	return (thereturn);
}


int main(int argc, char **argv)
{
	int fd;
	char *line;
	int res;


	res = 0;
	if(argc != 2)
		;  
	fd = open(argv[1], O_RDONLY);
	/*	while((res = get_next_line(fd, &line)) && res != -1)
	{
	  		ft_putendl(line);
		ft_putnbr(res);
		free(line);
	}*/
	res = get_next_line(fd, &line);
     	ft_putnbr(res);
	return (0);
}


