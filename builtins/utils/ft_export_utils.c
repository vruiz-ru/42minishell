/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:45:00 by aghergut          #+#    #+#             */
/*   Updated: 2025/12/12 21:51:00 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	ft_print_export_line(char *str)
{
	char	*eq;

	if (ft_strncmp(str, "_=", 2) == 0)
		return ;
	ft_putstr_fd("declare -x ", 1);
	eq = ft_strchr(str, '=');
	if (eq)
	{
		write(1, str, eq - str);
		write(1, "=\"", 2);
		ft_putstr_fd(eq + 1, 1);
		write(1, "\"\n", 2);
	}
	else
	{
		ft_putstr_fd(str, 1);
		write(1, "\n", 1);
	}
}

void	ft_export_from_static(t_process *process, char *name)
{
	char	*static_var;
	int		static_idx;

	static_idx = ft_mapitem_index(process->envs->static_env, name);
	if (static_idx >= 0)
	{
		static_var = ft_strdup(process->envs->static_env[static_idx]);
		if (static_var)
		{
			ft_mapitem_add(&process->envs->parent_env, static_var);
			free(static_var);
		}
	}
	else
	{
		ft_mapitem_add(&process->envs->parent_env, name);
	}
}

void	ft_export_logic(t_process *process, char *arg)
{
	char	*name;
	char	*eq_pos;
	int		idx;

	eq_pos = ft_strchr(arg, '=');
	if (eq_pos)
		name = ft_substr(arg, 0, eq_pos - arg);
	else
		name = ft_strdup(arg);
	idx = ft_mapitem_index(process->envs->parent_env, name);
	if (idx >= 0 && eq_pos)
		ft_mapitem_replace(&process->envs->parent_env, arg, idx);
	else if (idx < 0)
	{
		if (eq_pos)
			ft_mapitem_add(&process->envs->parent_env, arg);
		else
			ft_export_from_static(process, name);
	}
	free(name);
}

int	ft_is_valid_id(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
