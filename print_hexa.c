#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

unsigned int    get_unbr_len(unsigned int n, int base);
int		print_filler(int n, char c);
int		get_int_index(va_list args, int index);
int 	putstr_count(char *str);

void	print_hexa(unsigned int n, int type)
{
	char	c;

	if (n > 9)
		print_hexa(n / 16, type);
    if (!type)
	    c = "0123456789abcdef"[n % 16];
    else
        c = "0123456789ABCDEF"[n % 16];
	write(1, &c, 1);
}

int	print_start_xX(int len, int *tlen, t_convers *conv, int type)
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
    if (conv->hash && type)
        nbrc += putstr_count("0X");
    else if (conv->hash)
        nbrc += putstr_count("0x");
	return (nbrc);
}

int print_hexa_prec(t_convers *conv, int len, int save)
{
    int nbrc;

    nbrc = 0;
    if (conv->hash && !conv->minus && conv->zero && save == -1)
	    nbrc += print_filler(conv->precision - len - 2, '0');
    else
        nbrc += print_filler(conv->precision - len, '0');
    return (nbrc);
}

int	print_xX(va_list args, t_convers *conv, int type)
{
	unsigned int	nbr;
	int	nbrc;
	int	len;
	int	tlen;
    int save;

	nbrc = 0;
	nbr = (unsigned int)get_int_index(args, conv->index);
    save = conv->precision;
    if (!nbr && !conv->precision)
        return (print_filler(conv->width, ' '));
	len = get_unbr_len(nbr, 16);
	tlen = len;
	if (len < conv->precision)
		tlen = conv->precision;
    if (conv->hash)
        tlen += 2;
	nbrc += print_start_xX(len, &tlen, conv, type);
    nbrc += print_hexa_prec(conv, len, save);
	print_hexa(nbr, type);
	nbrc += len;
	if (conv->minus)
		nbrc += print_filler(conv->width - tlen, ' ');
	return (nbrc);
}