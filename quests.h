//////////////////////////////////////////////////////////////////////
// OpenTibia - an opensource roleplaying game
//////////////////////////////////////////////////////////////////////
// Quests
//////////////////////////////////////////////////////////////////////
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//////////////////////////////////////////////////////////////////////

#ifndef _QUESTS_H_
#define _QUESTS_H_

#include <list>
#include <string>
#include "player.h"
#include "networkmessage.h"

class MissionState;
class Mission;
class Quest;

typedef std::map<uint32_t, MissionState*> StateList;
typedef std::list<Mission*> MissionsList;
typedef std::list<Quest*> QuestsList;

class MissionState
{
	public:
		MissionState(std::string _description, uint32_t _missionID);
		virtual ~MissionState() {}

		uint32_t getMissionID() const {return missionID;}
		std::string getMissionDescription() const {return description;}

	private:
		std::string description;
		uint32_t missionID;
};

class Mission
{
	public:
		Mission(std::string _missionName, uint32_t _storageID, uint32_t _startValue, int32_t _endValue);
		virtual ~Mission();

		bool isCompleted(Player* player) const;
		bool isStarted(Player* player) const;

		std::string getName(Player* player);
		std::string getDescription(Player* player);

		StateList state;

	private:
		std::string missionName;
		uint32_t storageID, startValue, endValue;
};

class Quest
{
	public:
		Quest(std::string _name, uint16_t _id, uint32_t _startStorageID, uint32_t _startStorageValue);
		virtual ~Quest();

		bool isCompleted(Player* player);
		bool isStarted(Player* player) const;

		uint16_t getID() const {return id;}
		std::string getName() const {return name;}

		uint16_t getMissionsCount(Player* player);
		void getMissionList(Player* player, NetworkMessage* msg);

		MissionsList missions;

	private:
		std::string name;
		uint16_t id;
		uint32_t startStorageID, startStorageValue;
};

class Quests
{
	public:
		Quests() {}
		virtual ~Quests();

		static Quests* getInstance()
		{
			static Quests instance;
			return &instance;
		}

		bool reload();
		bool loadFromXml();

		uint16_t getQuestsCount(Player* player);
		void getQuestsList(Player* player, NetworkMessage* msg);

		Quest* getQuestByID(uint16_t id);
		QuestsList quests;
};

#endif
