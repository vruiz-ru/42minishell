/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:21:54 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 19:35:26 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int token_exist(t_list *tokens)
{
	if (tokens == NULL)
		return (0);
	return (1);
}

int	ft_builtins(t_process *process)
{
	char    *cmd;
	int		size;
	
	if (!token_exist(process->tokens))
		return (0);
	cmd = (char *)process->tokens->content;
	size = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "clear", size))
		return (ft_clear(), 1);
	else if (!ft_strncmp(cmd, "exit", size))
		return (ft_exit(process));
	else if (!ft_strncmp(cmd, "export", size))
		return (ft_export(process));
	else if (!ft_strncmp(cmd, "pwd", size))
		return (ft_pwd(process));
	else if (!ft_strncmp(cmd, "env", size))
		return (ft_env(process));
	else if (!ft_strncmp(cmd, "echo", size))
		return (ft_echo(process));
	else if (!ft_strncmp(cmd, "unset", size))
		return (ft_unset(&process));
	else if (!ft_strncmp(cmd, "cd", size))
		return (ft_cd(process));
	return (0);
}
