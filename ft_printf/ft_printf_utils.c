/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manand <manand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 16:26:14 by manand            #+#    #+#             */
/*   Updated: 2026/10/13 15:57:26 by manand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putnbr(long n)
{
	long	num;
	int		len;
	int		aux;

	len = 0;
	num = n;
	if (n < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		len = len + 1;
		n *= -1;
	}
	num = n % 10 + '0';
	if (n > 9)
	{
		aux = ft_putnbr(n / 10);
		if (aux == -1)
			return (-1);
		len = len + aux;
	}
	if (write(1, &num, 1) == -1)
		return (-1);
	len = len + 1;
	return (len);
}

int	ft_putstr(char *str1)
{
	int	len;

	if (!str1)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	len = 0;
	while (*str1 != '\0')
	{
		if (write(1, str1, 1) == -1)
			return (-1);
		len++;
		str1++;
	}
	return (len);
}

int	ft_putnbr_hexdec(unsigned long num, char up)
{
	char	*base;
	int		len;
	int		mod;
	int		aux;

	mod = 0;
	len = 0;
	if (up == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (num > 15)
	{
		aux = ft_putnbr_hexdec((num / 16), up);
		if (aux == -1)
			return (-1);
		len = len + aux;
	}
	mod = num % 16;
	if (write(1, &base[mod], 1) == -1)
		return (-1);
	len = len + 1;
	return (len);
}

int	ft_putptr(void *p)
{
	int	len;
	int	aux;

	len = 0;
	aux = 0;
	if (!p)
	{
		if (ft_putstr("(nil)") == -1)
			return (-1);
		return (5);
	}
	if (ft_putstr("0x") == -1)
		return (-1);
	len = len + 2;
	aux = ft_putnbr_hexdec((unsigned long)p, 'x');
	if (aux == -1)
		return (-1);
	len = len + aux;
	return (len);
}
