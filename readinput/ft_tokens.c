/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:07:38 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/06 22:17:18 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_cmd_token(t_subproc *process)
{
	char	*cmd;

	if (!process->line)
		return (0);
	cmd = ft_strtok(process->line, " ");
	ft_lstadd_back(&process->builtins->tokens, ft_lstnew(cmd));
	return (1);
}

static int	ft_normal_token(t_subproc *process)
{
	t_list	*tokens;
	char	*token;
	
	tokens = process->builtins->tokens;
	token = ft_strtok(NULL, " ");
	if (!token)
		return (0);
	if (!ft_strncmp((char *)tokens->content, "echo", 4))
		ft_lstadd_back(&tokens, ft_lstnew(ft_strdup(" ")));
	ft_lstadd_back(&tokens, ft_lstnew(token));
	return (1);
}

static int	ft_dquotes_token(t_subproc *process)
{
	t_list	*tokens;
	char	*token;
	char	*new;
	
	new = NULL;
	tokens = process->builtins->tokens;
	token = ft_strtok(NULL, "\"");
	if (ft_checkpair(token, '"'))
		new = ft_strjoin_free(new, token);
	else
		new = ft_strjoin(token, ft_strtok(NULL, "\""));
	if (new == NULL)
		return (perror("malloc"), 0);
	ft_lstadd_back(&tokens, ft_lstnew(new));
	return (1);
}

static int	ft_squotes_token(t_subproc *process)
{
	t_list	*tokens;
	char	*token;
	char	*new;
	
	new = NULL;
	tokens = process->builtins->tokens;
	token = ft_strtok(NULL, "'");
	if (ft_checkpair(token, '\''))
		new = ft_strjoin_free(new, token);
	else
		new = ft_strjoin(token, ft_strtok(NULL, "\'"));
	if (new == NULL)
		return (perror("malloc"), 0);
	ft_lstadd_back(&tokens, ft_lstnew(new));
	return (1);
}

int	create_tokens(t_subproc *process)
{
	char	*line;
	int		dquote_idx;
	int		squote_idx;

	if (!ft_cmd_token(process))
		return (0);
	line = ft_strchr(process->line, ' ');
	while (line)
	{
		dquote_idx = ft_getidx(line + 1, '"');
		squote_idx = ft_getidx(line + 1, '\'');
		if (dquote_idx < squote_idx && ft_dquotes_token(process))
			line = ft_strchr(ft_strchr(line, '"') + 1, '"');
		else if (dquote_idx > squote_idx && ft_squotes_token(process))
			line = ft_strchr(ft_strchr(line, '\'') + 1, '\'');
		else if (ft_normal_token(process))
			line = ft_strchr(ft_strchr(line, ' ') + 1, ' ');
	}
	return (1);
}
