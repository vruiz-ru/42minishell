/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:51:21 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/02 20:21:01 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_transfer(t_subproc *process, char *var)
{
	char	*get_var;
	int		idx;

	idx = ft_mapitem_index(process->buffer_env, var);
	if (idx < 0)
		return (0);
	get_var = ft_strdup(process->buffer_env[idx]);
	if (!get_var)
		return (0);
	if (!ft_mapitem_del(&process->buffer_env, idx))
		return (free(get_var), 0);
	if (!ft_mapitem_add(&process->local_env, get_var))
		return (free(get_var), 0);
	return (1);
}

static int	check_update(char **map, char *var_name)
{
	int idx;
	
	idx = ft_mapitem_index(map, var_name);
	if (idx < 0)
		return (0);
	if (!ft_mapitem_replace(&map, var_name, idx))
		return (0);
	return (1);
}

int ft_export(t_subproc *process)
{
	t_list	*ptr_tokens;
	char	*var;
	int		check;
	bool	done;
	
	ptr_tokens = process->builtins->tokens->next;
	while (ptr_tokens)
	{
		done = false;
		var = (char *)ptr_tokens->content;
		check = check_update(process->local_env, var);
		if (check)
			done = true;
		if (done == false && check_transfer(process, var))
			done = true;
		if (done == false && !ft_mapitem_add(&process->local_env, var))
			return (0);
		ptr_tokens = ptr_tokens->next;
	}
	return (1);
}
