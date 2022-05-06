/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:29:04 by afelten           #+#    #+#             */
/*   Updated: 2022/05/06 13:43:19 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stddef.h>

size_t	ft_strlen(const char *s);
int		ft_atoi(const char *nptr);
int		get_int_index(va_list args, int index);

int	get_index(const char *format, int *nbrf, int *i, int *incr)
{
	int	index;
	int	j;

	j = 0;
	index = 0;
	if (format[*i] >= '0' && format[*i] <= '9')
	{
		index = ft_atoi(format + *i);
		while (format[*i + j] >= '0' && format[*i + j] <= '9')
			j++;
		if (!index && format[*i + j] == '$')
			index = -1;
		else if (format[*i + j] != '$')
			index = 0;
		else
			*i += j + 1;
	}
	if (!index)
	{
		index = *nbrf;
		*incr += 1;
	}
	return (index);
}

int	get_index_incre(const char *format, int *nbrf, t_convers *conv, int *i)
{
	int	save;
	int	index;

	*i += 1;
	save = conv->incremented;
	index = get_index(format + *i, nbrf, i, &(conv->incremented));
	if (conv->incremented > save)
	{
		conv->incremented = save;
		*nbrf += 1;
	}
	return (index);
}

int	get_width(va_list args, const char *format, int *nbrf, t_convers *conv)
{
	int		i;
	int		save;
	int		index;

	i = 0;
	index = 0;
	if (*format == '*')
	{
		index = get_index_incre(format, nbrf, conv, &i);
		if (index == -1)
			return (-1);
		conv->width = get_int_index(args, index);
	}
	else if (*format >= '0' && *format <= '9')
	{
		conv->width = ft_atoi(format);
		while (format[i] >= '0' && format[i] <= '9')
			i++;
	}
	return (i);
}

int	get_precision(va_list args, const char *format, int *nbrf, t_convers *conv)
{
	int		i;
	int		save;
	int		index;

	i = 0;
	index = 0;
	if (*format == '.')
	{
		i++;
		if (format[i] == '*')
		{
			index = get_index_incre(format, nbrf, conv, &i);
			if (index == -1)
				return (-1);
			conv->precision = get_int_index(args, index);
		}
		else if (*format >= '0' && *format <= '9')
		{
			conv->width = ft_atoi(format);
			while (format[i] >= '0' && format[i] <= '9')
				i++;
		}
	}
	return (i);
}

int	get_flags(const char *format, t_convers *conv)
{
	int	i;

	i = 0;
	while (format[i] == '-' || format[i] == '+' || format[i] == '0'
		|| format[i] == '#' || format[i] == ' ')
	{
		if (format[i] == '-')
			conv->minus = 1;
		else if (format[i] == '+')
			conv->plus = 1;
		else if (format[i] == '0')
			conv->zero = 1;
		else if (format[i] == '#')
			conv->hash = 1;
		else if (format[i] == ' ')
			conv->space = 1;
		i++;
	}
	return (i);
}
