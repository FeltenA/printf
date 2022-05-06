/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ints.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:32:10 by afelten           #+#    #+#             */
/*   Updated: 2022/05/06 16:37:58 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

void	print_uint(unsigned int n);
int		get_nbr_len(int n, int base);
int		print_filler(int n, char c);
int		get_int_index(va_list args, int index);

void	print_int(int n)
{
	char	c;

	if (n > 9 || c < -9)
		print_int(n / 10);
	if (n < 0)
		c = (n % 10) * -1 + 48;
	else
		c = n % 10 + 48;
	write(1, &c, 1);
}

int	print_di(va_list args, t_convers *conv)
{
	int	nbr;
	int	nbrc;
	int	len;
	int	tlen;

	nbrc = 0;
	nbr = get_int_index(args, conv->index);
	len = get_nbr_len(nbr, 10);
	tlen = len;
	if (len < conv->precision)
		tlen = conv->precision;
	if (nbr < 0 || (nbr > 0 && (conv->plus || (conv->space && conv->width < tlen))))
		tlen++;
	if (!conv->minus)
	{
		if (conv->zero && conv->precision == -1)
			nbrc += print_filler(conv->width - tlen, '0');
		else
			nbrc += print_filler(conv->width - tlen, ' ');
	}
	if (nbr < 0)
		write(1, "-", 1);
	if (nbr > 0 && conv->plus)
		write(1, "+", 1);
	else if (nbr > 0 && conv->space && conv->width < tlen)
		write(1, " ", 1);
	print_filler(conv->precision - len, '0');
	print_int(nbr);
	nbrc += tlen;
	if (conv->minus)
		nbrc += print_filler(conv->width - tlen, ' ');
	return (nbrc);
}
