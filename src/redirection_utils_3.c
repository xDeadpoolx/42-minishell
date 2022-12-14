/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:26:46 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/11 08:59:11 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_clean_redir(t_vault *data, int i)
{
	ft_free_n_null (data->tab_arg[i]);
	data->tab_arg[i] = ft_strdup(data->buffer);
	ft_free_n_null (data->buffer);
}
