/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trmstart.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 22:00:29 by ncoden            #+#    #+#             */
/*   Updated: 2015/08/29 00:31:19 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include "libft/basics/booleans.h"
#include "libft/basics/strings.h"
#include "libft/basics/types.h"
#include "libft/containers/tree.h"
#include "libft/system/signals.h"
#include "libft-termcaps/termcaps.h"
#include "libft/utils/events.h"

static inline t_mt_tps	*tps_start(t_trm *trm, t_mt_tps *tps_father)
{
	t_mt_tps			*tps;

	if (!(tps = (t_mt_tps *)ft_mtnew__(sizeof(t_mt_tps))))
		return (NULL);
	if (tps_father)
		ft_mtaddchild((t_mt *)tps_father, (t_mt *)tps);
	else
		g_trm_tpss = tps;
	tps->father = tps_father;
	tps->trm = trm;
	tps->status |= TRM_STACTIVE;
	g_trm_current = tps;
	return (tps);
}

static inline t_tdata	*trm_switch(t_mt_tps *tps, t_mt_tps *tps_prev)
{
	t_tdata				*esrc;

	if (!tps_prev)
		ft_trmputcmd("ti");
	ft_trmset(tps->trm);
	if (tps->trm->on_start)
		ft_esrccall(tps->trm->on_start, TYPE_TPS, tps);
	if (tps->trm->inherit_signal)
		ft_sgnlpush(tps->trm->on_signal);
	else
		ft_sgnlset(tps->trm->on_signal);
	ft_sgnlhook(SIGCONT, (void (*)(void *))&ft_trmrestore, tps);
	if (!(esrc = ft_tdatanew(TYPE_TPS, tps)))
		return (NULL);
	ft_sgnlesrcset(esrc);
	return (esrc);
}

static inline t_bool	trm_restore(t_mt_tps *tps, t_mt_tps *tps_prev,
							t_tdata *esrc)
{
	free(esrc);
	ft_sgnldel(SIGCONT);
	if (tps->trm->on_stop)
		ft_esrccall(tps->trm->on_stop, TYPE_TPS, tps);
	if (tps->trm->inherit_signal)
		ft_sgnlpull();
	else
		ft_sgnlunset();
	if (tps_prev)
		ft_trmset(tps_prev->trm);
	else
		ft_trmputcmd("te");
	return (TRUE);
}

static inline t_bool	tps_stop(t_mt_tps *tps)
{
	if (tps->father)
		tps->father->child = NULL;
	free(tps);
	return (TRUE);
}

t_bool					ft_trmstart(t_trm *trm)
{
	t_tdata				*esrc;
	t_mt_tps			*tps;
	t_mt_tps			*tps_prev;
	t_mt_tps			*tps_father;
	char				*cmd;

	tps_prev = g_trm_current;
	tps_father = (t_mt_tps *)ft_esrcget(TYPE_TPS);
	if (!(tps = tps_start(trm, tps_father)))
		return (FALSE);
	if (!(esrc = trm_switch(tps, tps_prev)))
		return (FALSE);
	while (tps->status & TRM_STACTIVE)
	{
		tps->status |= TRM_STREADING;
		cmd = ft_read_trm();
		tps->status &= ~TRM_STREADING;
		if (cmd && !ft_strequ(cmd, ""))
			ft_tpskeytrigger(tps, cmd);
	}
	if (!trm_restore(tps, tps_prev, esrc))
		return (FALSE);
	if (!(tps_stop(tps)))
		return (FALSE);
	return (TRUE);
}
