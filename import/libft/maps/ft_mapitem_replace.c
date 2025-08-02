/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapitem_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:08:38 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/02 20:20:00 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maps.h"

int	ft_mapitem_replace(char ***map, char *item, size_t idx)
{
	if (!map || !*map || ft_mapsize(*map) <= idx)
		return (0);
	if ((*map)[idx] != NULL)
		free((*map)[idx]);
	(*map)[idx] = ft_strdup(item);
	if (!(*map)[idx])
		return (0);
	return (1);
}
