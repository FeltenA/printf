/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   va_arg_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:26:08 by afelten           #+#    #+#             */
/*   Updated: 2022/05/06 10:28:08 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

int	get_int_index(va_list args, int index)
{
	va_list	cargs;
	int		i;
	int		result;

	i = 0;
	va_copy(cargs, args);
	while (++i < index)
		(void)va_arg(cargs, int);
	result = va_arg(cargs, int);
	va_end(cargs);
	return (result);
}

char	*get_str_index(va_list args, int index)
{
	va_list	cargs;
	int		i;
	char	*result;

	i = 0;
	va_copy(cargs, args);
	while (++i < index)
		(void)va_arg(cargs, int);
	result = va_arg(cargs, char *);
	va_end(cargs);
	return (result);
}
