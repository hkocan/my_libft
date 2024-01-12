/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkocan <hkocan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:32:43 by hkocan            #+#    #+#             */
/*   Updated: 2023/10/27 08:37:16 by hkocan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static unsigned int	ft_numbersize(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*s;
	unsigned int	number;
	unsigned int	len;

	len = ft_numbersize(n);
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	if (n < 0)
	{
		s[0] = '-';
		number = -n;
	}
	else
		number = n;
	if (number == 0)
		s[0] = '0';
	s[len] = '\0';
	while (number != 0)
	{
		len--;
		s[len] = (number % 10) + '0';
		number = number / 10;
	}
	return (s);
}
