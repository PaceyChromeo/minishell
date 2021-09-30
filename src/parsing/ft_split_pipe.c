
#include "minishell.h"

// static int	nbr_strings(char const *s1, char c)
// {
// 	int	nbr;
// 	int	cles;
// 	int	s;
// 	int	d;

// 	nbr = 0;
// 	cles = 0;
// 	d = 0;
// 	s = 0;
// 	if (*s1 == '\0')
// 		return (0);
// 	while (*s1 != '\0')
// 	{
// 		if (*s1 == 39)
// 		{
// 			s++;
// 			if (s == 2)
// 				s = 0;
// 		}
// 		else if (*s1 == 34)
// 		{
// 			d++;
// 			if (d == 2)
// 				d = 0;
// 		}
// 		if (*s1 == c && s == 0 && d == 0)
// 			cles = 0;
// 		else if (cles == 0)
// 		{
// 			cles = 1;
// 			nbr++;
// 		}
// 		s1++;
// 	}
// 	return (nbr);
// }

static int	index_pipe(char const *s1, char c, int i)
{
	int	s;
	int	d;

	d = 0;
	s = 0;
	if (s1[i] == '\0')
		return (0);
	while (s1[i] != '\0')
	{
		if (s == 2)
			s = 0;
		if (d == 2)
			d = 0;
		if (s1[i] == 39)
			s++;	
		else if (s1[i] == 34)
			d++;	
		if (s1[i] == c && s == 0 && d == 0)
			return (i);
		i++;
	}
	return (i);
}

static char	**ft_copy_strings(char const *s, char **dst, char c, int total)
{
	int	i;
	int	j;
	int	k;
	int	index;
	int	fd;

	i = 0;
	j = 0;
	fd = 0;
	while (s[i] != '\0' && j < total)
	{
		index = 0;
		k = 0;
		index = index_pipe(s, c, i);
		while (s[i] == ' ')
			i++;
		dst[j] = (char *)malloc(sizeof(char) * (index - i) + 1);
		if (!dst[j])
			return (NULL);
		printf("len : %d\n", index - i);
		if ((index - i) == 0)
		{
			i++;
			fd++; // si fd > 256 =>error
			free (dst[j]);
			dst[j] = NULL;
			continue;
		}
		
		while (i < index && s[i] != '\0')
			dst[j][k++] = s[i++];
	//	if (j < total - 1) // pour traiter la derniere string
	//		k--;
		dst[j][k] = '\0';
		j++;
	}
	dst[j] = 0;
	return (dst);
}

char	**ft_split_pipe(char const *s, char c)
{
	char	**dst;
	int		total;

	if (!s)
		return (NULL);
	total = count_pipe((char *)s) + 1;
	printf("Total strings: %d\n", total);
	dst = (char **)malloc(sizeof(char *) * (total + 1));
	if (!dst)
		return (NULL);
	return (ft_copy_strings(s, dst, c, total));
}
