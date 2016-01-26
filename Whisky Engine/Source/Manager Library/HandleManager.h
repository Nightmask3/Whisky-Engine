#include <vector>
#include <map>

#include "Handle.h"

#include "..\Entity Library\Entity.h"
#include "..\Component Library\Component.h"

#ifndef HANDLEMANAGER_H
#define HANDLEMANAGER_H

#define MaxComponents Component::COMPONENT_COUNT	// Max number of components allowed to belong to any gameobject

// Made global as other classes need access to these types
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
	std::string m_ComponentType;
};
struct ListEntry_
{
	int m_activeEntryCount;
	uint32 m_firstFreeEntry;
};

// Forward Declaration
class GameObjectFactory;
class HandleManager
{
private:
	//HandleManager(const HandleManager&);
	HandleManager& operator=(const HandleManager&);

	// A List that holds information about all the other handle lists in the game
	std::map<std::string, ListEntry_> MetaDataList_;
	static GameObjectFactory* HandleManager::_pObjectFactory;

public:
	// Gets a reference to game object factory in use by engine
	HandleManager(GameObjectFactory & gameObject);
	// Getters
	void * Get(Handle handle, std::vector<HandleEntry_> const & m_entries) const;
	bool Get(Handle handle, void*& out, std::vector<HandleEntry_> const & m_entries) const;
	// Get as specific type
	template< typename T > bool GetAs(Handle handle, T& out) const;
	// Get number of elements
	int GetCount(std::vector<HandleEntry_> const & m_entries) const;

	// Creates a list of components for System callers
	bool InitializeListForSystem(std::vector<HandleEntry_> & m_entries, std::string SystemName);
	// Creates a list of components for Game object callers
	bool InitializeListForGameObject(std::vector<HandleEntry_> & m_entries, int);

	// Adds an element to a list of a game object
	Handle AddForGameObject(void* p, uint32 type, std::vector<HandleEntry_> & m_entries, std::string componentType, int index);
	// Adds an element to a list of a system
	Handle AddForSystem(void* p, uint32 type, std::vector<HandleEntry_> & m_entries, unsigned int componentID, std::string name);
	// Updates a list element
	void Update(Handle handle, void* p, std::vector<HandleEntry_> & m_entries);
	// Removes a list element
	void Remove(Handle handle, std::vector<HandleEntry_> & m_entries, type_info const & CallerType);
	
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