/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safeadd_nodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:40:35 by vruiz-ru          #+#    #+#             */
/*   Updated: 2025/12/14 12:55:17 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_safeadd_tokens(t_list **tokens, char **token)
{
	char	*ptr;
	char	*to_list;

	ptr = *token;
	if (!ptr || (!*ptr && ptr[0] != 1))
	{
		free(ptr);
		*token = NULL;
		return ;
	}
	to_list = ft_strdup(ptr);
	if (!to_list)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_lstadd_back(tokens, ft_lstnew(to_list));
	free(ptr);
	*token = NULL;
}
