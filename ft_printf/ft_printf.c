/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manand <manand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 13:38:56 by manand            #+#    #+#             */
/*   Updated: 2026/09/10 16:16:53 by manand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_spec_printf(va_list args, const char spec)
{
	if (spec == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (spec == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (spec == 'p')
		return (ft_putptr(va_arg(args, void *)));
	else if ((spec == 'i') || (spec == 'd'))
		return (ft_putnbr(va_arg(args, int)));
	else if (spec == 'u')
		return (ft_putnbr(va_arg(args, unsigned int)));
	else if (spec == '%')
		return (ft_putchar('%'));
	else if(spec == 'x' || spec == 'X')
		return (ft_putnbr_hexdec(va_arg(args, unsigned int), spec));
	return (-1);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int	len;
	int	check;

	va_start(args, str);
	len = 0;
	while (*str)
	{
		if (*str == '%')
		{
			check = ft_spec_printf(*(str++), args);
			if (check == -1)
				return (-1);
			len = len + check;
		}
		else
		{
			if (write(1, str, 1) == -1)
				return (-1);
			len++;
		}
		str++;
	}
	va_end(args);
	return (len);
}