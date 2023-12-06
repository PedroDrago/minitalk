#include "minitalk.h"

static int	ft_retputstr(char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
		return (ft_retputstr("(null)"));
	while (str[count])
		count++;
	write(1, str, count);
	return (count);
}

static int	ft_putnbr_base(int n, int base, int sign, char charset[])
{
	unsigned int	number;
	int				count;
	char			buff[16];

	count = 0;
	if (n == 0)
		return (write(1, "0", 1));
	if (sign && n < 0)
		number = -n;
	else
		number = n;
	while (number != 0)
	{
		buff[count++] = charset[number % base];
		number /= base;
	}
	if (sign && n < 0)
		buff[count++] = '-';
	while (--count >= 0)
		number += write(1, &buff[count], 1);
	return (number);
}

static int	ft_putpointer(void *ptr)
{
	unsigned long int	number;
	int					count;
	char				*charset;
	char				buff[16];
	unsigned long		ptr2;

	ptr2 = (unsigned long) ptr;
	if (ptr2 == (unsigned long) NULL)
		return (ft_retputstr("(nil)"));
	count = 0;
	charset = "0123456789abcdef";
	while (ptr2 != 0)
	{
		buff[count++] = charset[(unsigned long) ptr2 % 16];
		ptr2 /= 16;
	}
	number = count--;
	ft_retputstr("0x");
	while (count >= 0)
		write(1, &buff[count--], 1);
	return (number + 2);
}

static int	ft_resolve_print(char c, va_list args)
{
	char	local;

	if (c == 'c')
	{
		local = va_arg(args, int);
		return (write(1, &local, 1));
	}
	else if (c == 'i' || c == 'd')
		return (ft_putnbr_base(va_arg(args, int), 10, 1, "0123456789"));
	else if (c == 's')
		return (ft_retputstr(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_putpointer(va_arg(args, void *)));
	else if (c == 'u')
		return (ft_putnbr_base(va_arg(args, unsigned int),
				10, 0, "0123456789"));
	else if (c == 'x')
		return (ft_putnbr_base(va_arg(args, int), 16, 0, "0123456789abcdef"));
	else if (c == 'X')
		return (ft_putnbr_base(va_arg(args, int), 16, 0, "0123456789ABCDEF"));
	else if (c == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		index;
	int		total_count;
	va_list	args;

	index = -1;
	total_count = 0;
	va_start(args, str);
	while (str[++index])
	{
		if (str[index] == '%')
		{
			index++;
			total_count += ft_resolve_print(str[index], args);
		}
		else
			total_count += write(1, &str[index], 1);
	}
	va_end(args);
	return (total_count);
}
