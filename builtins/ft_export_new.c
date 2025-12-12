/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:51:21 by aghergut          #+#    #+#             */
/*   Updated: 2025/12/12 22:13:55 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	ft_sort_env_array(char **dup)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (dup[++i])
	{
		j = -1;
		while (dup[++j])
		{
			if (ft_strncmp(dup[i], dup[j], ft_strlen(dup[i])) > 0)
			{
				tmp = dup[i];
				dup[i] = dup[j];
				dup[j] = tmp;
			}
		}
	}
}

static int	ft_export_no_args(t_process *p)
{
	char	**dup;
	int		i;

	dup = ft_mapdup(p->envs->parent_env);
	if (!dup)
		return (1);
	ft_sort_env_array(dup);
	i = -1;
	while (dup[++i])
		ft_print_export_line(dup[i]);
	ft_free_array(dup);
	return (0);
}

int	ft_export(t_process *process, t_cmd *cmd)
{
	int	i;
	int	status;

	status = 0;
	if (!cmd->args[1])
		return (ft_export_no_args(process));
	i = 1;
	while (cmd->args[i])
	{
		if (!ft_is_valid_id(cmd->args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else
			ft_export_logic(process, cmd->args[i]);
		i++;
	}
	return (status);
}
