/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:28:42 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/12 10:47:36 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_checkpair(char *str, char ch)
{
	int	pair;
	int	i;

	pair = 0;
	i = 0;
    ft_printf("str in checkpair -> %s\n", str);
	while (str[i])
	{
		if (str[i] == ch)
			pair++;
		i++;
	}
	if (pair % 2 == 0)
		return (1);
	return (0);
}

int	ft_getquote_idx(char *token, char type)
{
	char	*normal;
	char	*dquotes;
	char	*squotes;
	int		idx_normal;
	int		idx_dquote;
	int		idx_squote;
	
	normal = ft_strchr(token, ' ');
	dquotes = ft_strchr(token, '"');
	squotes = ft_strchr(token, '\'');
	if (type == '"' && dquotes == NULL)
		return (-1);
	if (type == '\'' && squotes == NULL)
		return (-1);
	idx_dquote = dquotes - token;
	idx_squote = squotes - token;
	idx_normal = -1;
	if (normal)
		idx_normal = normal - token;
    // ft_printf("dquotes idx -> %d\nsquotes idx -> %d\nnormal idx -> %d\n", idx_dquote, idx_squote, idx_normal);
	if (type == '"' && (idx_normal < 0 || idx_dquote < idx_normal))
		return (idx_dquote);
	if (type == '\'' && (idx_normal < 0 || idx_squote < idx_normal))
		return (idx_squote);
	return (-1);
}
