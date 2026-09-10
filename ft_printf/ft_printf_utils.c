/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manand <manand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 16:26:14 by manand            #+#    #+#             */
/*   Updated: 2026/09/10 16:45:01 by manand           ###   ########.fr       */
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