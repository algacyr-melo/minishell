/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:27:47 by almelo            #+#    #+#             */
/*   Updated: 2022/06/24 15:39:08 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_putarg(va_list p_arg, char flag)
{
	char	*buffer;
	size_t	len_b;

	buffer = NULL;
	if (flag == 's')
		buffer = ft_strdup(va_arg(p_arg, char *));
	else if (flag == 'p')
		buffer = ft_handle_prefix(p_arg, "0x");
	else if (flag == 'd' || flag == 'i')
		buffer = ft_itoa(va_arg(p_arg, int));
	else if (flag == 'u')
		buffer = ft_ulltoa(va_arg(p_arg, unsigned), 10);
	else if (flag == 'x' || flag == 'X')
		buffer = ft_ulltoa(va_arg(p_arg, unsigned), 16);
	if (buffer == NULL)
		buffer = ft_strdup("(null)");
	len_b = ft_strlen(buffer);
	if (flag == 'X')
		ft_xtoupper(buffer);
	if (flag == 'p')
		len_b += 2;
	ft_putstr_fd(buffer, 1);
	free(buffer);
	return (len_b - 1);
}

static int	ft_handle_args(va_list arg, const char *format)
{
	int	offset;
	int	n;

	n = 0;
	offset = 0;
	while (*(format + offset))
	{
		if (*(format + offset) == '%')
		{
			offset++;
			if (*(format + offset) == '%')
				ft_putchar_fd(*(format + offset), 1);
			else if (*(format + offset) == 'c')
				ft_putchar_fd(va_arg(arg, int), 1);
			else
				n += ft_putarg(arg, *(format + offset));
			n--;
		}
		else
			ft_putchar_fd(*(format + offset), 1);
		offset++;
	}
	n += offset;
	return (n);
}

int	ft_printf(const char *format, ...)
{
	va_list		p_arg;
	int			n;

	va_start(p_arg, format);
	n = ft_handle_args(p_arg, format);
	va_end(p_arg);
	return (n);
}
