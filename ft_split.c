/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkocan <hkocan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:54:52 by hkocan            #+#    #+#             */
/*   Updated: 2023/10/27 08:25:52 by hkocan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	**my_free(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

static size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			count++;
		s++;
	}
	return (count);
}

static char	*copy_word(const char *s, char c)
{
	size_t	len;
	char	*word;
	size_t	i;

	len = 0;
	i = -1;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word || !s)
		return (NULL);
	while (++i, i < len)
		word[i] = s[i];
	word[len] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**split;
	size_t	i;

	count = count_words(s, c);
	split = (char **)malloc((count + 1) * sizeof(char *));
	if (!s || !split)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			split[i] = copy_word(s, c);
			if (!split[i])
				return (my_free(split));
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	split[i] = NULL;
	return (split);
}
