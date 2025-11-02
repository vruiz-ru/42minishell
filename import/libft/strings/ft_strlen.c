/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:02:28 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/28 23:47:47 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (i);
	while (str[i])
		i++;
	return (i);
}
