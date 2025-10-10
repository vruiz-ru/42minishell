/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:07:38 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/10 09:14:40 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*parse_token(t_subproc *process, char *content, char token)
{
	char	*res;
	char	*var_name;
	int		i;

	i = 0;
	if (!content || !*content)
		return (NULL);
	content = clean_line(content, token);
	res = NULL;
	while (content[i] != '\0')
	{
		var_name = NULL;
		scan_char(content, &var_name, &i);
		if (var_name != NULL)
		{
			insert_value(process, &res, var_name);
			if (!res)
				return (NULL);
			free(var_name);
		}
		res = ft_addchar(res, content[i]);
		i++;
	}
	return (free(content), res);	
}

int	ft_create_tokens(t_subproc *process)
{
	char	*cmd;
	char    *ptr_line;

	ptr_line = process->line;
	cmd = ft_strtok(ptr_line, " ");
	ft_lstadd_back(&process->builtins->tokens, ft_lstnew(cmd));
	if (!ft_strchr(ptr_line, ' '))
		return (1);
	if (!ft_nonquotes(process, ptr_line) && !ft_quotes(process, ptr_line))
		return (0);
	return (1);
}
