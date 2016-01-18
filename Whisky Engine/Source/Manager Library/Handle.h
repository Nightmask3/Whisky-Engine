
#ifndef Handle_h
#define Handle_h

typedef unsigned int uint32; // 4 byte unsigned integer - 32 bits

struct Handle
{
	Handle() : m_index(0), m_counter(0), m_type(0)
	{}

	Handle(uint32 index, uint32 counter, uint32 type)
		: m_index(index), m_counter(counter), m_type(type)
	{}

	inline operator uint32() const;

	uint32 m_index : 12;
	uint32 m_counter : 15;
	uint32 m_type : 5;
};


Handle::operator uint32() const
{
	// Returns a uint32 with m_type shifted 27 bits to the right, m_counter shifted 12 bits to the right, m_index in the least important position
	return m_type << 27 | m_counter << 12 | m_index;
}

#endif