/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_construct_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:54:14 by aghergut          #+#    #+#             */
/*   Updated: 2025/10/10 11:04:23 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_construct_line(t_list *tokens)
{
	t_list	*args;
	char	*content;
	char	*line;
	int		i;

	line = NULL;
	args = tokens->next;
	if (!args)
		return (NULL);
	while (args)
	{
		content = (char *)args->content;
		i = -1;
		while (content[++i])
			line = ft_addchar(line, content[i]);
		args = args->next;
	}
	return (line);
}