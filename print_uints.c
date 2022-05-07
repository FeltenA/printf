#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

unsigned int    get_unbr_len(unsigned int n, int base);
int		print_filler(int n, char c);
int		get_int_index(va_list args, int index);

int	print_uint(unsigned int n)
{
	char	c;

	if (n > 9)
		print_uint(n / 10);
	c = n % 10 + 48;
	write(1, &c, 1);
}

int	print_start_u(int nbr, int len, int *tlen, t_convers *conv)
{
	int	nbrc;

	nbrc = 0;
	if (!conv->minus)
	{
		if (conv->zero && conv->precision == -1)
		{
			if (conv->width > conv->precision)
			{
				conv->precision = conv->width;
				if (conv->width < *tlen)
					conv->precision--;
			}
		}
		else
			nbrc += print_filler(conv->width - *tlen, ' ');
	}
	return (nbrc);
}

int	print_u(va_list args, t_convers *conv)
{
	unsigned int	nbr;
	int	nbrc;
	int	len;
	int	tlen;

	nbrc = 0;
	nbr = (unsigned int)get_int_index(args, conv->index);
	len = get_unbr_len(nbr, 10);
	tlen = len;
	if (len < conv->precision)
		tlen = conv->precision;
	nbrc += print_start_u(nbr, len, &tlen, conv);
	nbrc += print_filler(conv->precision - len, '0');
	print_uint(nbr);
	nbrc += len;
	if (conv->minus)
		nbrc += print_filler(conv->width - tlen, ' ');
	return (nbrc);
}