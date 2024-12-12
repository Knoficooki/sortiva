#pragma once

#include <string>
#include <iostream>
#include <unordered_map>

namespace sva
{
	class Logging
	{
		std::unordered_map<size_t, std::string> m_Level_Names;
		size_t m_Active_Level;
		std::ostream& m_Stream;
	public:
		Logging(std::ostream& stream);

		template<typename T> requires std::is_enum_v<T>
		std::string& levelName(const T lvl)
		{
			return m_Level_Names[static_cast<size_t>(lvl)];
		}

		template<typename ...Args>
		Logging& logln(Args&& ...args)
		{
			m_Stream << " [" << m_Level_Names[m_Active_Level] << "] " << (std::forward<Args>(args) << ...) << std::endl;
			return *this;
		}

		template<typename T> requires std::is_enum_v<T>
		Logging& operator()(const T lvl)
		{
			try
			{
				std::string& lvn = m_Level_Names.at(static_cast<size_t>(lvl));
			}
			catch (...)
			{
				return *this;
			}
			m_Active_Level = static_cast<size_t>(lvl);
			return *this;
		}
	};
}



#ifdef SVA_LOGGING_IMPLEMENTATION
#undef SVA_LOGGING_IMPLEMENTATION

sva::Logging::Logging(std::ostream& stream) : m_Active_Level(0), m_Stream(stream)
{
	m_Level_Names[0] = "General";
}
#endif