/**
 * This file is part of Hercules.
 * http://herc.ws - http://github.com/HerculesWS/Hercules
 *
 * Copyright (C) 2012-2024 Hercules Dev Team
 * Copyright (C) Athena Dev Teams
 *
 * Hercules is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#define HERCULES_CORE

#include "random.h"

#include "common/cbasetypes.h" // for WIN32
#include "common/showmsg.h"
#include "common/timer.h" // gettick

#include <sfmt/SFMT.h> // init_genrand, genrand_int32, genrand_res53
#include <stdlib.h>

#if defined(WIN32)
#	include "common/winapi.h"
#elif defined(HAVE_GETPID) || defined(HAVE_GETTID)
#	include <sys/types.h>
#	include <unistd.h>
#endif

/** @file
 * Implementation of the random number generator interface.
 */

static struct rnd_interface rnd_s;
struct rnd_interface *rnd;

/// @copydoc rnd_interface::init()
static void rnd_init(void)
{

	uint32 seed = (uint32)timer->gettick();
	seed += (uint32)time(NULL);
#if defined(WIN32)
	seed += (uint32)GetCurrentProcessId();
	seed += (uint32)GetCurrentThreadId();
#else
#if defined(HAVE_GETPID)
	seed += (uint32)getpid();
#endif // HAVE_GETPID
#if defined(HAVE_GETTID)
	seed += (uint32)gettid();
#endif // HAVE_GETTID
#endif
	sfmt_init_gen_rand(&rnd->sfmt, seed);

	// Also initialize the stdlib rng, just in case it's used somewhere.
	srand((unsigned int)seed);
}

/// @copydoc rnd_interface::final()
static void rnd_final(void)
{
}

/// @copydoc rnd_interface::seed()
static void rnd_seed(uint32 seed)
{
	sfmt_init_gen_rand(&rnd->sfmt, seed);
}

/// @copydoc rnd_interface::random()
static int32 rnd_random(void)
{
	return (int32)(sfmt_genrand_uint32(&rnd->sfmt) >> 1);
}

/// @copydoc rnd_interface::roll()
static uint32 rnd_roll(uint32 dice_faces)
{
	return (uint32)(rnd->uniform()*dice_faces);
}

/// @copydoc rnd_interface::value()
static int32 rnd_value(int32 min, int32 max)
{
	if (min >= max)
		return min;
	return min + (int32)(rnd->uniform()*(max-min+1));
}

/// @copydoc rnd_interface::uniform()
static double rnd_uniform(void)
{
	return sfmt_to_real2(sfmt_genrand_uint32(&rnd->sfmt));
}

/// @copydoc rnd_interface::uniform53()
static double rnd_uniform53(void)
{
	return sfmt_to_res53(sfmt_genrand_uint32(&rnd->sfmt));
}

/// Interface base initialization.
void rnd_defaults(void)
{
	rnd = &rnd_s;
	rnd->init = rnd_init;
	rnd->final = rnd_final;
	rnd->seed = rnd_seed;
	rnd->random = rnd_random;
	rnd->roll = rnd_roll;
	rnd->value = rnd_value;
	rnd->uniform = rnd_uniform;
	rnd->uniform53 = rnd_uniform53;
}
