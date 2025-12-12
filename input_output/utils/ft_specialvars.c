/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specialvars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 17:04:00 by aghergut          #+#    #+#             */
/*   Updated: 2025/12/12 22:06:44 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../input_output.h"

int	ft_specialvars(t_process *proc, char **var_name, char ch)
{
	proc->is_special = false;
	if (ch == '$')
		*var_name = ft_itoa(proc->pid);
	else if (ch == '?')
		*var_name = ft_itoa(proc->status);
	else if (ch == '0')
		*var_name = ft_strdup(proc->prompt->home_path);
	if (ft_strchr("$?0_", ch) && !*var_name)
		return (perror("malloc"), exit(EXIT_FAILURE), 0);
	if (*var_name)
	{
		proc->is_special = true;
		return (1);
	}
	return (0);
}

int	check_heredoc_trigger(t_list *tokens)
{
	t_list	*curr;
	char	*last_valid;

	curr = tokens;
	last_valid = NULL;
	while (curr)
	{
		if (curr->content && ft_strncmp((char *)curr->content, " ", 2) != 0)
			last_valid = (char *)curr->content;
		curr = curr->next;
	}
	if (last_valid && !ft_strncmp(last_valid, "<<", 3))
		return (1);
	return (0);
}
