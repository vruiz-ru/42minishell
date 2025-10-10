/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 11:57:13 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/10 14:05:24 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_special_vars(t_subproc *process, char **var_name, char ch)
{
    process->special_var = false;
	if (ch == '$')
		*var_name = ft_itoa(process->pid);
	else if (ch == '?')
		*var_name = ft_itoa(process->exit_status);
	else if (ch == '0')
		*var_name = ft_strdup(process->ptr_main->home_path);
	else if (ch == '_')
		*var_name = ft_strdup(process->last_arg);
	if (*var_name)
	{
		process->special_var = true;
		return (1);
	}
	return (0);
}
