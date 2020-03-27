#include "db_entry.hpp"

#include <sstream>
#include <cassert>

namespace messenger {
	namespace database {
		
		void database_entry::stringify(std::stringstream& sstr) const noexcept
		{
			assert(m_db_entry);
			m_db_entry->stringify(sstr, 4);
		}

		database_entry::~database_entry() noexcept
		{

		}
	}
}
