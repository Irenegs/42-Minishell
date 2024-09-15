/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:02:22 by irene             #+#    #+#             */
/*   Updated: 2024/09/15 18:02:59 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_char(char **result, char *orig, int pos)
{
    char    *new;
    size_t  len_result;
    printf("add_char:%c\n", orig[pos]);
    len_result = ft_strlen(*result);
    new = malloc((len_result + 2) * sizeof(char));
    if (!new)
    {
        free(result);
        result = NULL;
        write_error_null(1);
        return ;
    }
    ft_memmove(new, *result, len_result);
    new[len_result] = orig[pos];
    new[len_result + 1] = '\0';
    free(*result);
    *result = new;
}