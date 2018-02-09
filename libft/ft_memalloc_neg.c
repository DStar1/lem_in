/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc_neg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:04:44 by hasmith           #+#    #+#             */
/*   Updated: 2018/02/08 19:36:36 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc(3)) and returns a “fresh” memory area
*/

#include "libft.h"

static void	ft_bneg(void *s, size_t n)
{
	ft_memset(s, 1, n);
}

void		*ft_memalloc_neg(size_t size)
{
	void	*mem;

	if (!size)
		return (NULL);
	mem = (void *)malloc(sizeof(void*) * size);
	if (!mem)
		return (NULL);
	ft_bneg(mem, size);
	return (mem);
}
