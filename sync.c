/* synrchonization-related stuff. In theory, that should
 * help porting to something different from pthreads.
 *
 * Copyright 2007 Rainer Gerhards and Adiscon GmbH.
 *
 * This file is part of rsyslog.
 *
 * Rsyslog is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Rsyslog is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Rsyslog.  If not, see <http://www.gnu.org/licenses/>.
 *
 * A copy of the GPL can be found in the file "COPYING" in this distribution.
 */

#include "config.h"

#include <stdlib.h>

#include "rsyslog.h"
#include "sync.h"


void
SyncObjInit(pthread_mutex_t **mut)
{
	*mut = (pthread_mutex_t *) malloc (sizeof (pthread_mutex_t));
	pthread_mutex_init(*mut, NULL);
}


/* This function destroys the mutex and also sets the mutex object
 * to NULL. While the later is not strictly necessary, it is a good
 * aid when debugging problems. As this function is not exepected to 
 * be called quite frequently, the additional overhead can well be
 * accepted. If this changes over time, setting to NULL may be
 * reconsidered. - rgerhards, 2007-11-12
 */
void
SyncObjExit(pthread_mutex_t **mut)
{
	if(*mut != NULL) {
		pthread_mutex_destroy(*mut);
		free(*mut);
		*mut = NULL;
	}
}

#ifndef	NDEBUG
/* lock an object. The synchronization tool (mutex) must be passed in.
 */
void
lockObj(pthread_mutex_t *mut)
{
	pthread_mutex_lock(mut);
}

/* unlock an object. The synchronization tool (mutex) must be passed in.
 */
void
unlockObj(pthread_mutex_t *mut)
{
	pthread_mutex_unlock(mut);
}
#endif /* #ifndef NDEBUG */
