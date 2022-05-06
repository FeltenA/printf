/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:43:25 by afelten           #+#    #+#             */
/*   Updated: 2022/05/06 11:31:33 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

int	get_index(const char *format, int *nbrf, int *i, int *incr);
int	get_width(va_list args, const char *format, int *nbrf, t_convers *conv);
int get_precision(va_list args, const char *format, int *nbrf, t_convers *conv);
int	get_flags(const char *format, t_convers *conv);

static void	init_convers(t_convers *conv)
{
	conv->index = 0;
	conv->incremented = 0;
	conv->width = 0;
	conv->precision = 0;
	conv->minus = 0;
	conv->plus = 0;
	conv->hash = 0;
	conv->space = 0;
	conv->zero = 0;
}

static void	compute_flag(va_list args,
						const char **format,
						int *nbrc,
						int *nbrf)
{
	int		i;
	int		save;
	t_convers	conv;

	i = 1;
	init_convers(&conv);
	conv.index = get_index(*format, nbrf, &i, &(conv->incremented));
	save = get_width(args, *format + i, nbrf, &conv);
	if (save == -1 || conv.index == -1)
		return (-1);
	i += save;
	i += get_flags(args, *format + i, &conv);
	save = get_precision(args, *format + i, nbrf, &conv);
	if (save == -1)
		return (-1);
}

int	ft_printf(const char *format, ...)
{
	int		nbrc;
	int		nbrf;
	va_list args;

	nbrc = 0;
	nbrf = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			compute_conv(args, &format, &nbrc, &nbrf);
			continue ;
		}
		write(1, format, 1);
		nbrc++;
		format++;
	}
	va_end(args);
}
