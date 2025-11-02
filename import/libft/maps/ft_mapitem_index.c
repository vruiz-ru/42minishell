/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapitem_index.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 20:12:06 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 22:21:19 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maps.h"

static int	get_length(char *str)
{
	char	*name;
	int		length;
	
	name = ft_strchr(str, '=');
	if (name)
		length = name - str;
	else
		length = ft_strlen(str);
	return (length);
}

int  ft_mapitem_index(char **map, char *str)
{
	size_t  mv_len;
	size_t	sv_len;
	size_t  idx;
	
	if (!map || !*map || !str || !*str)
		return (-1);
	sv_len = get_length(str);
	idx = 0;
	while (map[idx])
	{
		mv_len = get_length(map[idx]);
		if (mv_len == sv_len && !ft_strncmp(map[idx], str, mv_len))
			return (idx);
		idx++;
	}
	return (-1);
}
