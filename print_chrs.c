/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_chrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:55:01 by afelten           #+#    #+#             */
/*   Updated: 2022/05/06 13:29:53 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

size_t	ft_strlen(const char *s);
int		print_filler(int n, char c);
int		get_int_index(va_list args, int index);
char	*get_str_index(va_list args, int index);

int	print_s(va_list args, t_convers *conv)
{
	char	*str;
	int		nbrc;
	int		len;

	nbrc = 0;
	str = get_str_index(args, conv->index);
	len = ft_strlen(str);
	if (conv->precision != -1 && conv->precision < len)
		len = conv->precision;
	if (!conv->minus)
		nbrc += print_filler(conv->width - len, ' ');
	write(1, str, len);
	nbrc += len;
	if (conv->minus)
		nbrc += print_filler(conv->width - len, ' ');
	return (nbrc);
}

int	print_c(va_list args, t_convers *conv)
{
	char	c;
	int		nbrc;

	nbrc = 1;
	c = (char)get_int_index(args, conv->index);
	if (!conv->minus)
		nbrc += print_filler(conv->width - 1, ' ');
	write(1, &c, 1);
	if (conv->plus)
		nbrc += print_filler(conv->width - 1, ' ');
	return (nbrc);
}
