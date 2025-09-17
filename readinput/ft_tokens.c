/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:07:38 by aghergut          #+#    #+#             */
/*   Updated: 2025/09/17 20:49:41 by aghergut         ###   ########.fr       */
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

static char	*ft_normal_token(t_subproc *process, char *line)
{
	t_list	*tokens;
	char	*new;
	char	*res;
	int		size;
	int		length;

	tokens = process->builtins->tokens;
	new = ft_strtok(NULL, " ");
	if (!new)
		return (NULL);
    // ft_printf("new -->> |%s|\n", new);
	ft_lstadd_back(&tokens, ft_lstnew(new));
	size = ft_strlen(line);
	length = ft_strlen(new);
	res = ft_strdup(ft_strnstr(line, new, size) + length);
	free(line);
	return (res);}

static char	*ft_quotes_token(t_subproc *process, char *line, char ch)
{
	t_list	*tokens;
	char	*token;
	char	delim[2];
	char	*new;
	char	*res;

	delim[0] = ch;
	delim[1] = '\0';
	new = NULL;
	tokens = process->builtins->tokens;
	token = ft_strtok(NULL, delim);
	if (ft_checkpair(token, ch))
    {
        ft_printf("checkpair where delim(%c)\n", ch);
        new = ft_strjoin_free(new, token);
    }
	else
    {
        ft_putstr_fd("not checkpair\n", 1);
        new = ft_strjoin_free(token, ft_strtok(NULL, delim));
    }	
	if (new == NULL)
		return (perror("malloc"), NULL);
	ft_lstadd_back(&tokens, ft_lstnew(new));
	res = ft_strdup(ft_strnstr(line, new, ft_strlen(line)) + ft_strlen(new));
	free(line);
	return (res);
}

int	create_tokens(t_subproc *process)
{
	char	*line;
	int		dquote_idx;
	int		squote_idx;

	if (!ft_cmd_token(process))
		return (0);
    // ft_printf("here create tokens -->> pricess line -> %s\nft strchr + 1 -->> %s\n", process->line, ft_strchr(process->line, ' '));
	line = ft_strdup(ft_strchr(process->line, ' '));
    // ft_printf("line at the beginning of while -->> |%s|\n", line);
	while (line)
	{
		dquote_idx = ft_getquote_idx(line, '"');
		squote_idx = ft_getquote_idx(line, '\'');
		if ((dquote_idx >= 0 && squote_idx < 0) || dquote_idx < squote_idx)
        {
            line = ft_quotes_token(process, line, '"');
        }
		else if ((squote_idx >= 0 && dquote_idx < 0) || squote_idx > dquote_idx)
        {
            line = ft_quotes_token(process, line, '\'');
        }
		else
			line = ft_normal_token(process, line);
        // ft_printf("line in while loop -->> |%s|\n", line);
	}
	return (1);
}
