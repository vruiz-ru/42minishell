/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:51:08 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/02 11:42:28 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_getenv(t_subproc *process)
{
	char    **ptr;
	
	if (!process || !*process->local_env)
		return (0);
	ptr = process->local_env;
	while (*ptr)
	{
		ft_printf("%s\n", *ptr);
		ptr++;
	}
	return (1);
}
