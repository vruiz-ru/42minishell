/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:21:54 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/20 19:42:55 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int token_exist(t_list *tokens)
{
	if (tokens == NULL)
		return (0);
	return (1);
}

int	is_varformat(char *token)
{
	int	i;

	i = 0;
	while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
		i++;
	if (token[i] == '=')
		return (1);
	return (0);
}

void	ft_builtins(t_subproc *process)
{
	char    *cmd;
	int		size;
	
	if (!token_exist(process->builtins->tokens))
		return ;
	cmd = (char *)process->builtins->tokens->content;
	size = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "clear", size))
		ft_clear();
	else if (!ft_strncmp(cmd, "exit", size))
		ft_exit(process);
	else if (!ft_strncmp(cmd, "export", size))
		ft_export(process);
	else if (!ft_strncmp(cmd, "pwd", size))
		ft_pwd(process);
	else if (!ft_strncmp(cmd, "env", size))
		ft_getenv(process);
	else if (!ft_strncmp(cmd, "echo", size))
		ft_echo(process);
	else if (!ft_strncmp(cmd, "unset", size))
		ft_unset(&process);
	else if (is_varformat(cmd))
		ft_mapitem_add(&process->buffer_env, cmd);
	else if (!ft_strncmp(cmd, "cd", size))
		ft_cd(process);
}
