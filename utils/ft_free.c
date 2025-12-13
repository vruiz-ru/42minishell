/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:20:33 by aghergut          #+#    #+#             */
/*   Updated: 2025/12/13 14:36:59 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	del_redir(void *content)
{
	t_io	*io;

	io = (t_io *)content;
	if (io->path)
		free(io->path);
	if (io->type == IO_HEREDOC && io->fd != -1)
	{
		close(io->fd);
	}
	free(io);
}

void	free_env_items(char ***map)
{
	char	**ptr;
	int		i;

	ptr = *map;
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	ptr = NULL;
	*map = ptr;
}

void	ft_free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;

	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->args)
		{
			i = 0;
			while (cmds->args[i])
				free(cmds->args[i++]);
			free(cmds->args);
		}
		if (cmds->path)
			free(cmds->path);
		if (cmds->redirs)
			ft_lstclear(&cmds->redirs, del_redir);
		free(cmds);
		cmds = tmp;
	}
}

static void	ft_free_envs(t_envs *envs)
{
	if (!envs)
		return ;
	if (envs->parent_env)
		free_env_items(&envs->parent_env);
	if (envs->static_env)
		free_env_items(&envs->static_env);
	free(envs);
}

void	ft_free_process(t_process *proc)
{
	if (!proc)
		return ;
	ft_free_envs(proc->envs);
	if (proc->prompt)
	{
		if (proc->prompt->shell_name)
			free(proc->prompt->shell_name);
		if (proc->prompt->display)
			free(proc->prompt->display);
		if (proc->prompt->home_path)
			free(proc->prompt->home_path);
		if (proc->prompt->current_wd)
			free(proc->prompt->current_wd);
		if (proc->prompt->last_wd)
			free(proc->prompt->last_wd);
		free(proc->prompt);
	}
	if (proc->line)
		free(proc->line);
	if (proc->tokens)
		ft_lstclear(&proc->tokens, free);
	if (proc->commands)
		ft_free_cmds(proc->commands);
	free(proc);
}
