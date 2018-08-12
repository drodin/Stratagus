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
/**@name button_checks.cpp - The button checks. */
//
//      (c) Copyright 1999-2015 by Lutz Sammer, Vladi Belperchinov-Shabanski
//      and Andrettin
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

#include "stratagus.h"

#include "actions.h"
#include "depend.h"
#include "interface.h"
#include "network.h"
#include "player.h"
#include "unit.h"
#include "unittype.h"
#include "upgrade.h"

#include <stdio.h>
/*----------------------------------------------------------------------------
--  Functions
----------------------------------------------------------------------------*/

/**
**  ButtonCheck for button enabled, always true.
**  This needed to overwrite the internal tests.
**
**  @param unit    Pointer to unit for button.
**  @param button  Pointer to button to check/enable.
**
**  @return        True if enabled.
*/
bool ButtonCheckTrue(const CUnit &, const ButtonAction &)
{
	return true;
}

/**
**  Check for button enabled, always false.
**  This needed to overwrite the internal tests.
**
**  @param unit    Pointer to unit for button.
**  @param button  Pointer to button to check/enable.
**
**  @return        True if enabled.
*/
bool ButtonCheckFalse(const CUnit &, const ButtonAction &)
{
	return false;
}

/**
**  Check for button enabled, if upgrade is ready.
**
**  @param unit    Pointer to unit for button.
**  @param button  Pointer to button to check/enable.
**
**  @return        True if enabled.
*/
bool ButtonCheckUpgrade(const CUnit &unit, const ButtonAction &button)
{
	return UpgradeIdentAllowed(*unit.Player, button.AllowStr) == 'R';
}

/**
**  Check for button enabled, if unit has an individual upgrade.
**
**  @param unit    Pointer to unit for button.
**  @param button  Pointer to button to check/enable.
**
**  @return        True if enabled.
*/
bool ButtonCheckIndividualUpgrade(const CUnit &unit, const ButtonAction &button)
{
	return unit.IndividualUpgrades[UpgradeIdByIdent(button.AllowStr)];
}

/**
**  Check for button enabled, if unit's variables pass the condition check.
**
**  @param unit    Pointer to unit for button.
**  @param button  Pointer to button to check/enable.
**
**  @return        True if enabled.
*/
bool ButtonCheckUnitVariable(const CUnit &unit, const ButtonAction &button)
{
	char *buf = new_strdup(button.AllowStr.c_str());

	for (const char *var = strtok(buf, ","); var; var = strtok(NULL, ",")) {
		const char *type = strtok(NULL, ",");
		const char *binop = strtok(NULL, ",");
		const char *value = strtok(NULL, ",");
		const int index = UnitTypeVar.VariableNameLookup[var];// User variables
		if (index == -1) {
			fprintf(stderr, "Bad variable name '%s'\n", var);
			Exit(1);
			return false;
		}
		int varValue;
		if (!strcmp(type, "Value")) {
			varValue = unit.Variable[index].Value;
		} else if (!strcmp(type, "Max")) {
			varValue = unit.Variable[index].Max;
		} else if (!strcmp(type, "Increase")) {
			varValue = unit.Variable[index].Increase;
		} else if (!strcmp(type, "Enable")) {
			varValue = unit.Variable[index].Enable;
		} else if (!strcmp(type, "Percent")) {
			varValue = unit.Variable[index].Value * 100 / unit.Variable[index].Max;
		} else {
			fprintf(stderr, "Bad variable type '%s'\n", type);
			Exit(1);
			return false;
		}
		const int cmpValue = atoi(value);
		bool cmpResult = false;
		if (!strcmp(binop, ">")) {
			cmpResult = varValue > cmpValue;
		} else if (!strcmp(binop, ">=")) {
			cmpResult = varValue >= cmpValue;
		} else if (!strcmp(binop, "<")) {
			cmpResult = varValue < cmpValue;
		} else if (!strcmp(binop, "<=")) {
			cmpResult = varValue <= cmpValue;
		} else if (!strcmp(binop, "==")) {
			cmpResult = varValue == cmpValue;
		} else if (!strcmp(binop, "!=")) {
			cmpResult = varValue != cmpValue;
		} else {
			fprintf(stderr, "Bad compare type '%s'\n", binop);
			Exit(1);
			return false;
		}
		if (cmpResult == false) {
			delete[] buf;
			return false;
		}
	}
	delete[] buf;
	return true;
}

/**
**  Check for button enabled, if any unit is available.
**
**  @param unit    Pointer to unit for button.
**  @param button  Pointer to button to check/enable.
**
**  @return        True if enabled.
*/
bool ButtonCheckUnitsOr(const CUnit &unit, const ButtonAction &button)
{
	CPlayer *player = unit.Player;
	char *buf = new_strdup(button.AllowStr.c_str());

	for (const char *s = strtok(buf, ","); s; s = strtok(NULL, ",")) {
		if (player->HaveUnitTypeByIdent(s)) {
			delete[] buf;
			return true;
		}
	}
	delete[] buf;
	return false;
}

/**
**  Check for button enabled, if all units are available.
**
**  @param unit    Pointer to unit for button.
**  @param button  Pointer to button to check/enable.
**
**  @return        True if enabled.
*/
bool ButtonCheckUnitsAnd(const CUnit &unit, const ButtonAction &button)
{
	CPlayer *player = unit.Player;
	char *buf = new_strdup(button.AllowStr.c_str());

	for (const char *s = strtok(buf, ","); s; s = strtok(NULL, ",")) {
		if (!player->HaveUnitTypeByIdent(s)) {
			delete[] buf;
			return false;
		}
	}
	delete[] buf;
	return true;
}

/**
**  Check for button enabled, if no unit is available.
**
**  @param unit    Pointer to unit for button.
**  @param button  Pointer to button to check/enable.
**
**  @return        True if enabled.
*/
bool ButtonCheckUnitsNot(const CUnit &unit, const ButtonAction &button)
{
	return !ButtonCheckUnitsAnd(unit, button);
}

/**
**  Check if network play is enabled.
**
**  @param unit    Pointer to unit for button.
**  @param button  Pointer to button to check/enable.
**
**  @return        True if enabled.
**
**  @note: this check could also be moved into intialisation.
*/
bool ButtonCheckNetwork(const CUnit &, const ButtonAction &)
{
	return IsNetworkGame();
}

/**
**  Check if network play is disabled.
**
**  @param unit    Pointer to unit for button.
**  @param button  Pointer to button to check/enable.
**
**  @return        True if disabled.
**
**  @note: this check could also be moved into intialisation.
*/
bool ButtonCheckNoNetwork(const CUnit &, const ButtonAction &)
{
	return !IsNetworkGame();
}

/**
**  Check for button enabled, if the unit isn't working.
**  Working is training, upgrading, researching.
**
**  @param unit    Pointer to unit for button.
**  @param button  Pointer to button to check/enable.
**
**  @return        True if enabled.
*/
bool ButtonCheckNoWork(const CUnit &unit, const ButtonAction &)
{
	int action = unit.CurrentAction();
	return action != UnitActionTrain
		   && action != UnitActionUpgradeTo
		   && action != UnitActionResearch;
}

/**
**  Check for button enabled, if the unit isn't researching.
**
**  @param unit    Pointer to unit for button.
**  @param button  Pointer to button to check/enable.
**
**  @return        True if enabled.
*/
bool ButtonCheckNoResearch(const CUnit &unit, const ButtonAction &)
{
	int action = unit.CurrentAction();
	return action != UnitActionUpgradeTo && action != UnitActionResearch;
}

/**
**  Check for button enabled, if all requirements for an upgrade to unit
**  are met.
**
**  @param unit    Pointer to unit for button.
**  @param button  Pointer to button to check/enable.
**
**  @return        True if enabled.
*/
bool ButtonCheckUpgradeTo(const CUnit &unit, const ButtonAction &button)
{
	if (unit.CurrentAction() != UnitActionStill) {
		return false;
	}
	return CheckDependByIdent(*unit.Player, button.ValueStr);
}

/**
**  Check if all requirements for an attack are met.
**
**  @param unit    Pointer to unit for button.
**  @param button  Pointer to button to check/enable.
**
**  @return        True if enabled.
*/
bool ButtonCheckAttack(const CUnit &unit, const ButtonAction &)
{
	return unit.Type->CanAttack;
}

/**
**  Check if all requirements for upgrade research are met.
**
**  @param unit    Pointer to unit for button.
**  @param button  Pointer to button to check/enable.
**
**  @return        True if enabled.
*/
bool ButtonCheckResearch(const CUnit &unit, const ButtonAction &button)
{
	// don't show any if working
	if (!ButtonCheckNoWork(unit, button)) {
		return false;
	}

	// check if allowed
	if (!CheckDependByIdent(*unit.Player, button.ValueStr)) {
		return false;
	}
	if (!strncmp(button.ValueStr.c_str(), "upgrade-", 8)
		&& UpgradeIdentAllowed(*unit.Player, button.ValueStr) != 'A') {
		return false;
	}
	return true;
}

/**
**  Check if all requirements for upgrade research are met only one
**  running research allowed.
**
**  @param unit    Pointer to unit for button.
**  @param button  Pointer to button to check/enable.
**
**  @return        True if enabled.
*/
bool ButtonCheckSingleResearch(const CUnit &unit, const ButtonAction &button)
{
	if (ButtonCheckResearch(unit, button)
		&& !unit.Player->UpgradeTimers.Upgrades[UpgradeIdByIdent(button.ValueStr)]) {
		return true;
	}
	return false;
}

//@}
