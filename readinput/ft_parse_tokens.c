/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:53:45 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/07 14:33:37 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int  ft_wildcards(char *str, char *wildcards)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (ft_strchr(wildcards, str[i]))
            return (1);
        i++;
    }
    return (0);
}

static char *ft_cleanline(char *content)
{
    char    *new;
    int     i;

    i = 0;
    new = NULL;
    if (!content || !*content)
        return (NULL);
    while (content[i] != '\0')
    {
        if (content[i] == '\\')
            i++;
        if (content[i] != '\0')
            new = ft_addchar(new, content[i]);
        i++;
    }
    free(content);
    return (new);
}

char    *ft_build_line(char *content)
{
    char    *new;
    int     i;

    i = 0;
    new = ft_cleanline(content);
    if (!new)
        return (NULL);
    while (new[i])
}

char	*ft_parse_tokens(t_subproc *process)
{
	t_list	*tokens;
    t_list  *temp;
    char    *content;
	char	*new_line;

	tokens = process->builtins->tokens;
	new_line = NULL;
	while (tokens)
	{
		content = tokens->content;
        if (ft_wildcards(content, "\\\"'$"))
            new_line = ft_build_line(content);
        else if (new_line == NULL)
            new_line = ft_strdup(content);
        else
            new_line = ft_strjoin_free(new_line, content);
        temp = tokens->next;
        ft_lstdelone(tokens, free);
		tokens = temp;
	}
	return (1);
}
