#pragma once

/*
	This file is part of Kraft der Mada.
	Copyright (c) 2009 Daniel Wickert

    Kraft der Mada is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Kraft der Mada is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Kraft der Mada. If not, see <http://www.gnu.org/licenses/>.
*/

#include "db/sqlite/sqlite3.h"
#include "properties/PropertyId.h"

namespace mada
{
	class Database : public RefCounted
	{
		__mada_declare_class(Database);
	public:
		enum AccessMode {ReadOnly, ReadWriteExisting, ReadWriteCreate};

		Database();
		~Database();

		void setPath(const String& path);
		const String& getPath() const;

		void setAccessMode(AccessMode mode);
		AccessMode getAccessMode() const;

		void open();
		void close();
		bool isOpen() const;

		void createTable(const String& tableName, const PropertyIdVector& propertyIds, bool dropExisting);
		void dropTable(const String& tableName);
		bool tableExists(const String& tableName) const;

		void beginTransaction();
		void commitTransaction();
		void rollbackTransaction();

	private:
		friend class Command;
		friend class ResultSet;

		String m_path;
		AccessMode m_mode;
		sqlite3* m_db;

		sqlite3* _getDbHandle() const;
	};
}
