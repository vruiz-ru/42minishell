/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_strtok.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:49:38 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/10 10:51:44 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clear_strtok(void)
{
	char	*buffer;

	buffer = ft_strtok(NULL, " ");
	if (!buffer)
		return ;
	while (buffer)
	{
		free(buffer);
		buffer = ft_strtok(NULL, " ");
	}
	return ;
}
