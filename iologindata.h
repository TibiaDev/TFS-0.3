//////////////////////////////////////////////////////////////////////
// OpenTibia - an opensource roleplaying game
//////////////////////////////////////////////////////////////////////
// Base class for the LoginData loading/saving
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

#ifndef __IOLOGINDATA_H
#define __IOLOGINDATA_H
#include "otsystem.h"
#include "database.h"

#include "player.h"
#include "account.h"
#include "group.h"

enum DeleteCharacter_t
{
	DELETE_INTERNAL,
	DELETE_LEADER,
	DELETE_HOUSE,
	DELETE_ONLINE,
	DELETE_SUCCESS
};

typedef std::pair<int32_t, Item*> itemBlock;
typedef std::list<itemBlock> ItemBlockList;

class IOLoginData
{
	public:
		virtual ~IOLoginData() {}
		static IOLoginData* getInstance()
		{
			static IOLoginData instance;
			return &instance;
		}

		Account loadAccount(uint32_t accId, bool preLoad = false);
		bool saveAccount(Account acc);

		bool getAccountId(const std::string& name, uint32_t& number);
		bool getAccountName(uint32_t number, std::string& name);

		bool hasFlag(uint32_t accId, PlayerFlags value);
		bool hasCustomFlag(uint32_t accId, PlayerCustomFlags value);
		bool hasFlag(PlayerFlags value, const std::string& accName);
		bool hasCustomFlag(PlayerCustomFlags value, const std::string& accName);

		bool accountExists(uint32_t accId);
		bool accountNameExists(const std::string& name);

		bool getPassword(uint32_t accId, const std::string& name, std::string& password);
		bool setNewPassword(uint32_t accountId, std::string newPassword);
		bool validRecoveryKey(uint32_t accountId, const std::string recoveryKey);
		bool setRecoveryKey(uint32_t accountId, std::string recoveryKey);

		bool createAccount(std::string name, std::string password);
		void removePremium(Account account);

		bool loadPlayer(Player* player, const std::string& name, bool preLoad = false);
		bool savePlayer(Player* player, bool preSave = true);
		bool updateOnlineStatus(uint32_t guid, bool login);

		const Group* getPlayerGroupByAccount(uint32_t accId);
		uint32_t getLastIPByName(std::string name);

		bool hasFlag(const std::string& name, PlayerFlags value);
		bool hasCustomFlag(const std::string& name, PlayerCustomFlags value);
		bool hasFlag(PlayerFlags value, uint32_t guid);
		bool hasCustomFlag(PlayerCustomFlags value, uint32_t guid);

		bool isPremium(uint32_t guid);
		uint32_t getAccountIdByName(std::string name);

		bool playerExists(uint32_t guid, bool multiworld = false, bool checkCache = true);
		bool playerExists(std::string& name, bool multiworld = false, bool checkCache = true);
		bool getNameByGuid(uint32_t guid, std::string& name, bool multiworld = false);
		bool getGuidByName(uint32_t& guid, std::string& name, bool multiworld = false);
		bool getGuidByNameEx(uint32_t& guid, bool& specialVip, std::string& name);

		bool changeName(uint32_t guid, std::string newName, std::string oldName);
		bool createCharacter(uint32_t accountId, std::string characterName, int32_t vocationId, PlayerSex_t sex);
		DeleteCharacter_t deleteCharacter(uint32_t accountId, const std::string characterName);

		uint32_t getLevel(uint32_t guid) const;
		uint32_t getLastIP(uint32_t guid) const;

		bool updatePremiumDays();
		bool resetOnlineStatus();
		bool resetGuildInformation(uint32_t guid);

	protected:
		IOLoginData() {}
		struct StringCompareCase
		{
			bool operator()(const std::string& l, const std::string& r) const
			{
				return strcasecmp(l.c_str(), r.c_str()) < 0;
			}
		};

		bool storeNameByGuid(uint32_t guid);
		typedef std::map<int32_t, std::pair<Item*, int32_t> > ItemMap;

		void loadItems(ItemMap& itemMap, DBResult* result);
		bool saveItems(const Player* player, const ItemBlockList& itemList, DBInsert& query_insert);

		typedef std::map<uint32_t, std::string> NameCacheMap;
		NameCacheMap nameCacheMap;

		typedef std::map<std::string, uint32_t, StringCompareCase> GuidCacheMap;
		GuidCacheMap guidCacheMap;
};

#endif
