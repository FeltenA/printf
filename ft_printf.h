/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:31:00 by afelten           #+#    #+#             */
/*   Updated: 2022/05/06 09:42:57 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

typedef struct s_convers
{
	int	index;
	int	incremented;
	int	width;
	int	precision;
	int	minus;
	int	plus;
	int	hash;
	int	space;
	int	zero;
}	t_convers;

#endif
