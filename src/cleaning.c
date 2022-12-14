/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 00:19:39 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/11 08:47:16 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	clean_before_exit(t_vault *data)
// {
// 	free_struct_b_in(data);
// 	if (data->quote)
// 		free(data->quote);
// 	if (data->read_line)
// 		free(data->read_line);
// 	if (data->env && data->flag->execve == 0)
// 		ft_dbl_ptr_free((void **)data->env);
// 	if (data->flag->rl_exit == 0)
// 	{
// 		if (data->tab_arg)
// 			ft_dbl_ptr_free((void **)data->tab_arg);
// 		if (data->pid)
// 			free (data->pid);
// 	}
// 	close_fd(data);
// 	if (data->flag->execve == 0)
// 	{
// 		if (data->cmd->opt && data->flag->rl_exit == 0)
// 			ft_dbl_ptr_free((void **)data->cmd->opt);
// 		free (data->cmd->name);
// 		free (data->cmd);
// 	}
// 	if (data->flag)
// 		free(data->flag);
// }

void	clean_before_exit(t_vault *data)
{
	free_struct_b_in(data);
	if (data->quote)
		free(data->quote);
	ft_free_n_null(data->read_line);
	if (data->env && data->flag->execve == 0)
		ft_dbl_ptr_free((void **)data->env);
	if (data->flag->rl_exit == 0)
	{
		if (data->tab_arg)
			ft_dbl_ptr_free((void **)data->tab_arg);
		if (data->pid)
			free (data->pid);
	}
	close_fd(data);
	if (data->flag->execve == 0)
	{
		if (data->cmd->opt && data->flag->rl_exit == 0)
			ft_dbl_ptr_free((void **)data->cmd->opt);
		ft_free_n_null(data->cmd->name);
		free (data->cmd);
	}
	if (data->flag)
		free(data->flag);
}

void	free_struct_b_in(t_vault *data)
{
	ft_free_n_null(data->b_in->export_var);
	if (data->b_in->env_ord)
		ft_dbl_ptr_free((void **)data->b_in->env_ord);
	if (data->b_in)
		free(data->b_in);
	return ;
}

void	close_fd(t_vault *data)
{
	if (data->flag->fd_out > 0)
		close (data->flag->fd_out);
	if (data->flag->fd > 0)
		close (data->flag->fd);
	close (data->flag->stdin_backup);
	close (data->flag->stdout_backup);
	close (data->error_fd);
	return ;
}
