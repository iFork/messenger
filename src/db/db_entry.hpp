#ifndef MESSENGER_DATABASE_DB_ENTRY_HPP
#define MESSENGER_DATABASE_DB_ENTRY_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"

/**
 * @file src/db/db_entry.hpp
 * @author ITC students
 * @brief database_entry class definition
*/

//#include <iostream>
#include <string>
#include <sstream>
#include <Poco/JSON/Object.h>

namespace messenger {
	namespace database {
		
		/**
		 * @class An abstract class specifying common interface for
		 * db entries
		 */ 
		class database_entry 
		{
			protected:
				/**
				 * @brief JSON object pointer with the db entry.
				 */
				Poco::JSON::Object::Ptr m_db_entry;
			public:
			
			//Helpers
			
				/**
				 * @brief Write database_entry obj into provided stringstream
				 */
				void stringify(std::stringstream& str) const noexcept; 
		
				/**
				 * @brief Def constructor
				 */

			    database_entry() = default;
			    
				/**
				 * @brief Copy constructor
				 */
			    database_entry(const database_entry&) = delete;
			
			    /**
				 * @brief Move constructor
				 */ 
			    database_entry(const database_entry&&) = delete;
			
			    /**
				 * @brief Copy assignment operator
				 */ 
			    database_entry& operator=(const database_entry&) = default;
			
			    /**
				 * @brief Move assignment operator
				 */ 
			    database_entry& operator=(const database_entry&&) = delete;
			
			    /**
				 * @brief Destructor
				 */ 
			    ~database_entry() noexcept;
		};
	}
}

#endif // MESSENGER_DATABASE_DB_ENTRY_HPP
