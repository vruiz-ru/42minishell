/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:51:21 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 22:27:24 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_transfer(t_process *process, char *var)
{
	char	*get_var;
	int		idx;

	idx = ft_mapitem_index(process->envs->static_env, var);
	if (idx < 0)
		return (0);
	get_var = ft_strdup(process->envs->static_env[idx]);
	if (!get_var)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	if (!ft_mapitem_del(&process->envs->static_env, idx))
		return (free(get_var), 0);
	if (!ft_mapitem_add(&process->envs->parent_env, get_var))
		return (free(get_var), 0);
	return (1);
}

static int	check_update(char **map, char *var)
{
	int 	env_idx;
	
	env_idx = ft_mapitem_index(map, var);
	if (env_idx < 0)
		return (0);
	if (!ft_mapitem_replace(&map, var, env_idx))
		return (0);
	return (1);
}

int ft_export(t_process *process)
{
	char	**local;
	char	*line;
	int		idx;

	local = process->envs->static_env;
	line = ft_construct(process->tokens, NULL);
	if (!ft_strchr(line, '='))
	{
		idx = ft_mapitem_index(local, line);
		if (idx < 0)
			return (1);
		if (!ft_mapitem_add(&process->envs->parent_env, local[idx]))
			return (perror("malloc"), exit(EXIT_FAILURE), 0);
	}
	if (check_update(process->envs->parent_env, line))
		return (1);
	if (!check_update(process->envs->static_env, line))
		return (0);
	if (!check_transfer(process, line))
		return (0);
	return (free(line), 1);
}
