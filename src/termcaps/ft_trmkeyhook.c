/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trmkeyhook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 19:30:12 by ncoden            #+#    #+#             */
/*   Updated: 2015/08/28 19:08:28 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/containers/klst.h"
#include "libft-termcaps/termcaps.h"
#include "libft/utils/events.h"

void			ft_trmkeyhook(t_trm *trm, char *key, void (*func)(void *),
					void *data)
{
	t_klst_evnt		*event;

	if ((event = (t_klst_evnt *)ft_klstpush__(sizeof(t_klst_evnt),
			(t_klst **)&trm->on_key, key)))
	{
		event->event.func = func;
		event->event.data = data;
	}
}
