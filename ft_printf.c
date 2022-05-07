/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:43:25 by afelten           #+#    #+#             */
/*   Updated: 2022/05/06 16:27:54 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include "ft_printf.h"

int	get_index(const char *format, int *nbrf, int *i, int *incr);
int	get_width(va_list args, const char *format, int *nbrf, t_convers *conv);
int	get_precision(va_list args, const char *format, int *nbrf, t_convers *conv);
int	get_flags(const char *format, t_convers *conv);
int	print_s(va_list args, t_convers *conv);
int	print_c(va_list args, t_convers *conv);
int	print_di(va_list args, t_convers *conv);
int	print_u(va_list args, t_convers *conv);

static void	init_convers(t_convers *conv)
{
	conv->index = 0;
	conv->incremented = 0;
	conv->width = 0;
	conv->precision = -1;
	conv->minus = 0;
	conv->plus = 0;
	conv->hash = 0;
	conv->space = 0;
	conv->zero = 0;
}

static int	print_conversion(va_list args, char format, t_convers *conv)
{
	if (format == 'c')
		return (print_c(args, conv));
	else if (format == 's')
		return (print_s(args, conv));
	else if (format == 'd' || format == 'i')
		return (print_di(args, conv));
	else if (format == 'u')
		return (print_u(args, conv));
	return (0);
}

static int	compute_conv(va_list args,
						const char **format,
						int *nbrc,
						int *nbrf)
{
	int			i;
	int			save;
	t_convers	conv;

	i = 1;
	init_convers(&conv);
	conv.index = get_index(*format + i, nbrf, &i, &(conv.incremented));
	if (conv.index == -1)
		return (-1);
	i += get_flags(*format + i, &conv);
	save = get_width(args, *format + i, nbrf , &conv);
	if (save == -1)
		return (-1);
	i += save;
	save = get_precision(args, *format + i, nbrf, &conv);
	if (save == -1)
		return (-1);
	i += save;
	if (conv.incremented)
	{
		conv.index = *nbrf;
		*nbrf += 1;
	}
	save = print_conversion(args, *(*format + i), &conv);
	*format += i + 1;
	*nbrc += save;
}

int	ft_printf(const char *format, ...)
{
	int		nbrc;
	int		nbrf;
	va_list	args;

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
