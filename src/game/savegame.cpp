//       _________ __                 __
//      /   _____//  |_____________ _/  |______     ____  __ __  ______
//      \_____  \\   __\_  __ \__  \\   __\__  \   / ___\|  |  \/  ___/
//      /        \|  |  |  | \// __ \|  |  / __ \_/ /_/  >  |  /\___ |
//     /_______  /|__|  |__|  (____  /__| (____  /\___  /|____//____  >
//             \/                  \/          \//_____/            \/
//  ______________________                           ______________________
//                        T H E   W A R   B E G I N S
//         Stratagus - A free fantasy real time strategy game engine
//
/**@name savegame.cpp - Save game. */
//
//      (c) Copyright 2001-2005 by Lutz Sammer, Andreas Arens
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; only version 2 of the License.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//      02111-1307, USA.
//

//@{

/*----------------------------------------------------------------------------
--  Includes
----------------------------------------------------------------------------*/

#include <time.h>
#include <ctype.h>
#include <string>

#include "stratagus.h"
#include "icons.h"
#include "ui.h"
#include "construct.h"
#include "unittype.h"
#include "unit.h"
#include "upgrade.h"
#include "depend.h"
#include "interface.h"
#include "missile.h"
#include "tileset.h"
#include "map.h"
#include "player.h"
#include "ai.h"
#include "results.h"
#include "trigger.h"
#include "settings.h"
#include "iolib.h"
#include "spells.h"
#include "commands.h"
#include "script.h"
#include "actions.h"
#include "replay.h"

/*----------------------------------------------------------------------------
--  Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
--  Functions
----------------------------------------------------------------------------*/

/**
** Get the save directory and create dirs if needed
*/
static std::string GetSaveDir()
{
	struct stat tmp;
	std::string dir(Parameters::Instance.GetUserDirectory());
	if (!GameName.empty()) {
		dir += "/";
		dir += GameName;
	}
	dir += "/save";
	if (stat(dir.c_str(), &tmp) < 0) {
		makedir(dir.c_str(), 0777);
	}
	return dir;
}

/**
**  Save a game to file.
**
**  @param filename  File name to be stored.
**  @return  -1 if saving failed, 0 if all OK
**
**  @note  Later we want to store in a more compact binary format.
*/
int SaveGame(const std::string &filename)
{
	time_t now;
	CFile file;
	std::string s;
	std::string fullpath(GetSaveDir());

	fullpath += "/";
	fullpath += filename;
	if (file.open(fullpath.c_str(), CL_WRITE_GZ | CL_OPEN_WRITE) == -1) {
		fprintf(stderr, "Can't save to `%s'\n", filename.c_str());
		return -1;
	}

	time(&now);
	s = ctime(&now);
	size_t pos = s.find('\n');
	if (pos != std::string::npos) {
		s.erase(pos);
	}

	//
	// Parseable header
	//
	file.printf("SavedGameInfo({\n");
	file.printf("---  \"comment\", \"Generated by Stratagus Version " VERSION "\",\n");
	file.printf("---  \"comment\", \"Visit https://launchpad.net/stratagus for more informations\",\n");
	file.printf("---  \"type\",    \"%s\",\n", "single-player");
	file.printf("---  \"date\",    \"%s\",\n", s.c_str());
	file.printf("---  \"map\",     \"%s\",\n", Map.Info.Description.c_str());
	file.printf("---  \"media-version\", \"%s\"", "Undefined");
	file.printf("---  \"engine\",  {%d, %d, %d},\n",
				StratagusMajorVersion, StratagusMinorVersion, StratagusPatchLevel);
	file.printf("  SyncHash = %d, \n", SyncHash);
	file.printf("  SyncRandSeed = %d, \n", SyncRandSeed);
	file.printf("  SaveFile = \"%s\"\n", CurrentMapPath);
	file.printf("\n---  \"preview\", \"%s.pam\",\n", filename.c_str());
	file.printf("} )\n\n");

	// FIXME: probably not the right place for this
	file.printf("GameCycle = %lu\n", GameCycle);

	SaveCcl(file);
	SaveUnitTypes(file);
	SaveUpgrades(file);
	SavePlayers(file);
	Map.Save(file);
	SaveUnits(file);
	SaveUserInterface(file);
	SaveAi(file);
	SaveSelections(file);
	SaveGroups(file);
	SaveMissiles(file);
	SaveReplayList(file);
	// FIXME: find all state information which must be saved.
	s = SaveGlobal(Lua, true);
	if (!s.empty()) {
		file.printf("-- Lua state\n\n %s\n", s.c_str());
	}
	SaveTriggers(file); //Triggers are saved in SaveGlobal, so load it after Global
	file.close();
	return 0;
}

/**
**  Delete save game
**
**  @param filename  Name of file to delete
*/
void DeleteSaveGame(const std::string &filename)
{
	// Security check
	if (filename.find_first_of("/\\") != std::string::npos) {
		return;
	}

	std::string fullpath = GetSaveDir() + "/" + filename;
	if (unlink(fullpath.c_str()) == -1) {
		fprintf(stderr, "delete failed for %s", fullpath.c_str());
	}
}

//@}
