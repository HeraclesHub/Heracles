/**
 * This file is part of Hercules.
 * http://herc.ws - http://github.com/HerculesWS/Hercules
 *
 * Copyright (C) 2012-2025 Hercules Dev Team
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
#ifndef CHAR_INT_HOMUN_H
#define CHAR_INT_HOMUN_H

#include "common/hercules.h"
#include "common/mmo.h"

/**
 * inter_homunculus interface
 **/
struct inter_homunculus_interface {
	int (*sql_init) (void);
	void (*sql_final) (void);
	int (*parse_frommap) (int fd);

	bool (*create) (struct s_homunculus *hd);
	bool (*save) (const struct s_homunculus *hd);
	bool (*load) (int homun_id, struct s_homunculus* hd);
	bool (*delete) (int homun_id);
	bool (*rename) (const char *name);
};

#ifdef HERCULES_CORE
void inter_homunculus_defaults(void);
#endif // HERCULES_CORE

HPShared struct inter_homunculus_interface *inter_homunculus;

#endif /* CHAR_INT_HOMUN_H */
