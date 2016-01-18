
#include "HandleManager.h"
#include <cstddef>

HandleManager::HandleEntry_::HandleEntry_()
: m_nextFreeIndex(0)
, m_counter(1)
, m_active(0)
, m_endOfList(0)
, m_entry(NULL)
{}

HandleManager::HandleEntry_::HandleEntry_(uint32 nextFreeIndex)
: m_nextFreeIndex(nextFreeIndex)
, m_counter(1)
, m_active(0)
, m_endOfList(0)
, m_entry(NULL)
{}



HandleManager::HandleManager()
{
	Reset();
}


void HandleManager::Reset(std::vector<HandleEntry_> m_entries)
{
	m_activeEntryCount = 0;
	m_firstFreeEntry = 0;

	for (int i = 0; i < MaxGameObjects - 1; ++i)
		m_entries[i] = HandleEntry_(i + 1);
	m_entries[MaxGameObjects - 1] = HandleEntry_();
	m_entries[MaxGameObjects - 1].m_endOfList = true;
}


Handle HandleManager::Add(void* p, uint32 type, std::vector<HandleEntry_> m_entries)
{
	const int newIndex = m_firstFreeEntry;

	m_firstFreeEntry = m_entries[newIndex].m_nextFreeIndex;
	m_entries[newIndex].m_nextFreeIndex = 0;
	m_entries[newIndex].m_counter = m_entries[newIndex].m_counter + 1;
	if (m_entries[newIndex].m_counter == 0)
		m_entries[newIndex].m_counter = 1;
	m_entries[newIndex].m_active = true;
	m_entries[newIndex].m_entry = p;

	++m_activeEntryCount;

	return Handle(newIndex, m_entries[newIndex].m_counter, type);
}


void HandleManager::Update(Handle handle, void* p, std::vector<HandleEntry_> m_entries)
{
	const int index = handle.m_index;
	m_entries[index].m_entry = p;
}


void HandleManager::Remove(const Handle handle, std::vector<HandleEntry_> m_entries)
{
	const uint32 index = handle.m_index;

	m_entries[index].m_nextFreeIndex = m_firstFreeEntry;
	m_entries[index].m_active = 0;
	m_firstFreeEntry = index;

	--m_activeEntryCount;
}

std::vector<HandleEntry> HandleManager::CreateComponentList(ComponentType type)
{

}

std::vector<HandleEntry> HandleManager::CreateEntityList(Entity::EntityType type)
{

}

void* HandleManager::Get(Handle handle, std::vector<HandleEntry_> m_entries) const
{
	void* p = NULL;
	if (!Get(handle, p))
		return NULL;
	return p;
}


bool HandleManager::Get(const Handle handle, void*& out, std::vector<HandleEntry_> m_entries) const
{
	const int index = handle.m_index;
	if (m_entries[index].m_counter != handle.m_counter ||
		m_entries[index].m_active == false)
		return false;

	out = m_entries[index].m_entry;
	return true;
}


int HandleManager::GetCount(std::vector<HandleEntry_> m_entries) const
{
	return m_entries.size();
}
