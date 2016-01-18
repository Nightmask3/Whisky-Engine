#include <vector>

#include "Handle.h"
#include "..\Entity Library\Entity.h"
#include "..\Component Library\Component.h"

#ifndef HANDLEMANAGER_H
#define HANDLEMANAGER_H

#define MaxGameObjects 4096 // 2 ^ 12 entries, max number of gameobjects in the world, and belonging to any system
#define MaxComponents 10	// Max number of components allowed to belong to any gameobject
class HandleManager
{
private:
	HandleManager(const HandleManager&);
	HandleManager& operator=(const HandleManager&);

	struct HandleEntry_
	{
		HandleEntry_();
		explicit HandleEntry_(uint32 nextFreeIndex);

		// Holds ID of next free slot in array
		uint32 m_nextFreeIndex : 12;
		uint32 m_counter : 15;
		uint32 m_active : 1;
		uint32 m_endOfList : 1;
		void* m_entry;
	};
	struct ListEntry_
	{
		int m_activeEntryCount;
		uint32 m_firstFreeEntry;
		int m_List
	};
	// A List that holds information about all the other handle lists in the game
	std::vector<ListEntry_> MetaDataList_;
	
	
public:

	HandleManager();

	void Reset(std::vector<HandleEntry_> m_entries);
	Handle Add(void* p, uint32 type, std::vector<HandleEntry_> m_entries);
	void Update(Handle handle, void* p, std::vector<HandleEntry_> m_entries);
	void Remove(Handle handle, std::vector<HandleEntry_> m_entries);
	std::vector<HandleEntry_> CreateComponentList(ComponentType type);
	std::vector<HandleEntry_> CreateEntityList(Entity::EntityType type);
	void * Get(Handle handle, std::vector<HandleEntry_> m_entries) const;
	bool Get(Handle handle, void*& out, std::vector<HandleEntry_> m_entries) const;
	template< typename T > bool GetAs(Handle handle, std::vector<HandleEntry_> m_entries, T& out) const;

	int GetCount(std::vector<HandleEntry_> m_entries) const;


};


template< typename T >
inline bool HandleManager::GetAs(Handle handle, T& out) const
{
	void* outAsVoid;
	const bool rv = Get(handle, outAsVoid);
	out = union_cast<T>(outAsVoid);

	return rv;
}

#endif