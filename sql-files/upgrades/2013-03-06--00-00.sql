#1362528000

-- This file is part of Hercules.
-- http://herc.ws - http://github.com/HerculesWS/Hercules
--
-- Copyright (C) 2013-2025 Hercules Dev Team
-- Copyright (C) Athena Dev Teams
--
-- Hercules is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
--
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with this program.  If not, see <http://www.gnu.org/licenses/>.

-- This script resets all dewata quests that were done by your users before this revision
-- Author: Euphy
DELETE FROM `quest` WHERE `quest_id` > 5034 AND `quest_id` < 5055;
DELETE FROM `quest` WHERE `quest_id` > 9154 AND `quest_id` < 9166;
DELETE FROM `global_reg_value` WHERE `str` = 'dewata_gatti';
DELETE FROM `global_reg_value` WHERE `str` = 'dewata_legend';
DELETE FROM `global_reg_value` WHERE `str` = 'dewata_oldman';
INSERT INTO `sql_updates` (`timestamp`) VALUES (1362528000);
