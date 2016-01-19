
#include "HandleManager.h"
#include "GameObjectFactory.h"
#include <cstddef>

HandleEntry_::HandleEntry_()
: m_nextFreeIndex(0)
, m_counter(1)
, m_active(0)
, m_endOfList(0)
, m_entry(NULL)
{}

HandleEntry_::HandleEntry_(uint32 nextFreeIndex)
: m_nextFreeIndex(nextFreeIndex)
, m_counter(1)
, m_active(0)
, m_endOfList(0)
, m_entry(NULL)
{}

HandleManager::HandleManager(GameObjectFactory & factory)
{
	_pObjectFactory = &factory;
}


bool HandleManager::InitializeList(std::vector<HandleEntry_> & m_entries, type_info const & CallerType)
{
	ListEntry_ listValue;
	listValue.m_activeEntryCount = 0;
	listValue.m_firstFreeEntry = 0;
	// Creates a meta data list entry and inserts with Caller Type as index in a map
	MetaDataList_.insert(std::make_pair(CallerType, listValue));
	for (int i = 0; i < MaxGameObjects - 1; ++i)
		m_entries[i] = HandleEntry_(i + 1);
	m_entries[MaxGameObjects - 1] = HandleEntry_();
	m_entries[MaxGameObjects - 1].m_endOfList = true;

	return true;
}


Handle HandleManager::Add(void* p, uint32 type, std::vector<HandleEntry_> & m_entries, type_info const & CallerType)
{
	const int newIndex = MetaDataList_[CallerType].m_firstFreeEntry;

	MetaDataList_[CallerType].m_firstFreeEntry = m_entries[newIndex].m_nextFreeIndex;
	m_entries[newIndex].m_nextFreeIndex = 0;
	m_entries[newIndex].m_counter = m_entries[newIndex].m_counter + 1;
	if (m_entries[newIndex].m_counter == 0)
		m_entries[newIndex].m_counter = 1;
	m_entries[newIndex].m_active = true;
	m_entries[newIndex].m_entry = p;

	++MetaDataList_[CallerType].m_activeEntryCount;

	return Handle(newIndex, m_entries[newIndex].m_counter, type);
}


void HandleManager::Update(Handle handle, void* p, std::vector<HandleEntry_> & m_entries)
{
	const int index = handle.m_index;
	m_entries[index].m_entry = p;
}


void HandleManager::Remove(const Handle handle, std::vector<HandleEntry_> & m_entries, type_info const & CallerType)
{
	const uint32 index = handle.m_index;

	m_entries[index].m_nextFreeIndex = MetaDataList_[CallerType].m_firstFreeEntry;
	m_entries[index].m_active = 0;
	MetaDataList_[CallerType].m_firstFreeEntry = index;

	--MetaDataList_[CallerType].m_activeEntryCount;
}

std::vector<HandleEntry_> HandleManager::CreateComponentList(Component::ComponentType type)
{

}

std::vector<HandleEntry_> HandleManager::CreateEntityList(Entity::EntityType type)
{

}

void* HandleManager::Get(Handle handle, std::vector<HandleEntry_> const & m_entries) const
{
	void* p = NULL;
	if (!Get(handle, p, m_entries))
		return NULL;
	return p;
}


bool HandleManager::Get(const Handle handle, void*& out, std::vector<HandleEntry_> const & m_entries) const
{
	const int index = handle.m_index;
	if (m_entries[index].m_counter != handle.m_counter ||
		m_entries[index].m_active == false)
		return false;

	out = m_entries[index].m_entry;
	return true;
}


int HandleManager::GetCount(std::vector<HandleEntry_> const & m_entries) const
{
	return m_entries.size();
}
