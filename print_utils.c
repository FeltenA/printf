/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:46:35 by afelten           #+#    #+#             */
/*   Updated: 2022/05/06 16:06:52 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	print_uint(unsigned int n)
{
	char	c;

	while (n > 9)
		print_uint(n / 10);
	c = n % 10 + 48;
	write(1, &c, 1);
}

int	print_filler(int n, char c)
{
	int	i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		i++;
	}
	return (i);
}

int	get_nbr_len(int n, int base)
{
	int	len;

	len = 1;
	while (n <= -9 || n >= 9)
	{
		n /= base;
		len++;
	}
	return (len);
}
