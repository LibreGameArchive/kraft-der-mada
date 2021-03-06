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
#include "stdmadainc.h"

#include "properties/PropertyTable.h"

namespace mada
{
	__mada_implement_root_class(PropertyTable);

	PropertyTable::PropertyTable() : m_columns(), m_columnIndices(), m_rows(), m_rowSize(0)
	{
	}

	PropertyTable::~PropertyTable()
	{
	}

	int PropertyTable::getNumCols() const
	{
		return m_columns.size();
	}

	int PropertyTable::getNumRows() const
	{
		return m_rows.size();
	}

	/// Must be called before first use of addRow()
	int PropertyTable::addColumn(const PropertyId& id)
	{
		mada_assert(getNumRows() == 0);

		ColumnDefinition def = { id, m_rowSize};
		m_columns.push_back(def);
		m_rowSize += id.getValueTypeSize();

		int idx = m_columns.size() - 1;

		m_columnIndices.insert(std::make_pair(id, idx));

		return idx;
	}

	PropertyId PropertyTable::getColumnPropertyId(int idx) const
	{
		mada_assert(idx < (int)m_columns.size());
		return m_columns[idx].id;
	}

	int PropertyTable::getColumnIndex(const PropertyId& id) const
	{
		ColumnIndexMap::const_iterator it = m_columnIndices.find(id);
		mada_assert(it != m_columnIndices.end());

		return it->second;
	}

	bool PropertyTable::hasColumn(const PropertyId& id) const
	{
		return m_columnIndices.find(id) != m_columnIndices.end();
	}

	int PropertyTable::addRow()
	{
		mada_assert(getNumCols() > 0);
		void* rowData = mada_malloc(m_rowSize);
		// We need to zero init mem, else String asignment operator fails in setValue.
		SysUtils::memset(rowData, 0, m_rowSize);
		m_rows.push_back(rowData);
		return m_rows.size() - 1;
	}

	void PropertyTable::removeRow(int idx)
	{
		delete m_rows[idx];
		m_rows.erase(m_rows.begin() + idx);
	}

	void PropertyTable::removeAllRows()
	{
		for (size_t i = 0, end = m_rows.size(); i < end; ++i)
		{
			delete m_rows[i];
		}
		m_rows.clear();
	}

	Property PropertyTable::getValue(const PropertyId& id, int row) const
	{
		mada_assert(0 <= row && row < getNumRows());

		int idx = getColumnIndex(id);
		mada_assert(0 <= idx && idx < getNumCols());

		char* valuePtr = (char*)m_rows[row];
		valuePtr += m_columns[idx].offset;

		Property rval;
		switch (id.getValueType())
		{
		case BoolType:
			rval = Property(id, *((bool*)valuePtr));
			break;
		case IntType:
			rval = Property(id, *((int*)valuePtr));
			break;
		case FloatType:
			rval = Property(id, *((float*)valuePtr));
			break;
		case StringType:
			rval = Property(id, *((String*)valuePtr));
			break;
		case Vector3Type:
			rval = Property(id, *((Vector3*)valuePtr));
			break;
		case QuaternionType:
			rval = Property(id, *((Quaternion*)valuePtr));
			break;
		default:
			mada_assert(false && "Unknown ValueType");
			break;
		}

		return rval;
	}

	bool PropertyTable::getBoolValue(const PropertyId& id, int row) const
	{
		mada_assert(id.getValueType() == BoolType);
		mada_assert(0 <= row && row < getNumRows());

		int idx = getColumnIndex(id);
		mada_assert(0 <= idx && idx < getNumCols());

		char* valuePtr = (char*)m_rows[row];
		valuePtr += m_columns[idx].offset;

		return *((bool*)valuePtr);
	}

	int PropertyTable::getIntValue(const PropertyId& id, int row) const
	{
		mada_assert(id.getValueType() == IntType);
		mada_assert(0 <= row && row < getNumRows());

		int idx = getColumnIndex(id);
		mada_assert(0 <= idx && idx < getNumCols());

		char* valuePtr = (char*)m_rows[row];
		valuePtr += m_columns[idx].offset;

		return *((int*)valuePtr);
	}

	float PropertyTable::getFloatValue(const PropertyId& id, int row) const
	{
		mada_assert(id.getValueType() == FloatType);
		mada_assert(0 <= row && row < getNumRows());

		int idx = getColumnIndex(id);
		mada_assert(0 <= idx && idx < getNumCols());

		char* valuePtr = (char*)m_rows[row];
		valuePtr += m_columns[idx].offset;

		return *((float*)valuePtr);
	}

	String PropertyTable::getStringValue(const PropertyId& id, int row) const
	{
		mada_assert(id.getValueType() == StringType);
		mada_assert(0 <= row && row < getNumRows());

		int idx = getColumnIndex(id);
		mada_assert(0 <= idx && idx < getNumCols());

		char* valuePtr = (char*)m_rows[row];
		valuePtr += m_columns[idx].offset;

		return *((String*)valuePtr);
	}

	Vector3 PropertyTable::getVector3Value(const PropertyId& id, int row) const
	{
		mada_assert(id.getValueType() == Vector3Type);
		mada_assert(0 <= row && row < getNumRows());

		int idx = getColumnIndex(id);
		mada_assert(0 <= idx && idx < getNumCols());

		char* valuePtr = (char*)m_rows[row];
		valuePtr += m_columns[idx].offset;

		return *((Vector3*)valuePtr);
	}

	Quaternion PropertyTable::getQuaternionValue(const PropertyId& id, int row) const
	{
		mada_assert(id.getValueType() == QuaternionType);
		mada_assert(0 <= row && row < getNumRows());

		int idx = getColumnIndex(id);
		mada_assert(0 <= idx && idx < getNumCols());

		char* valuePtr = (char*)m_rows[row];
		valuePtr += m_columns[idx].offset;

		return *((Quaternion*)valuePtr);
	}

	void PropertyTable::setValue(const Property& prop, int row)
	{
		mada_assert(0 <= row && row < getNumRows());

		PropertyId id = prop.getPropertyId();
		int idx = getColumnIndex(id);
		mada_assert(0 <= idx && idx < getNumCols());

		char* valuePtr = (char*)m_rows[row];
		valuePtr += m_columns[idx].offset;

		switch (id.getValueType())
		{
		case BoolType:
			new (valuePtr) bool(prop.getBoolValue());
			break;
		case IntType:
			new (valuePtr) int(prop.getIntValue());
			break;
		case FloatType:
			new (valuePtr) float(prop.getFloatValue());
			break;
		case StringType:
			new (valuePtr) String(prop.getStringValue());
			break;
		case Vector3Type:
			new (valuePtr) Vector3(prop.getVector3Value());
			break;
		case QuaternionType:
			new (valuePtr) Quaternion(prop.getQuaternionValue());
			break;
		default:
			mada_assert(false && "Unknown ValueType");
			break;
		}
	}

	void PropertyTable::setBoolValue(const PropertyId& id, int row, bool value)
	{
		mada_assert(id.getValueType() == BoolType);
		mada_assert(0 <= row && row < getNumRows());

		int idx = getColumnIndex(id);
		mada_assert(0 <= idx && idx < getNumCols());

		char* valuePtr = (char*)m_rows[row];
		valuePtr += m_columns[idx].offset;

		new (valuePtr) bool(value);
	}

	void PropertyTable::setIntValue(const PropertyId& id, int row, int value)
	{
		mada_assert(id.getValueType() == IntType);
		mada_assert(0 <= row && row < getNumRows());

		int idx = getColumnIndex(id);
		mada_assert(0 <= idx && idx < getNumCols());

		char* valuePtr = (char*)m_rows[row];
		valuePtr += m_columns[idx].offset;

		new (valuePtr) int(value);
	}

	void PropertyTable::setFloatValue(const PropertyId& id, int row, float value)
	{
		mada_assert(id.getValueType() == FloatType);
		mada_assert(0 <= row && row < getNumRows());

		int idx = getColumnIndex(id);
		mada_assert(0 <= idx && idx < getNumCols());

		char* valuePtr = (char*)m_rows[row];
		valuePtr += m_columns[idx].offset;

		new (valuePtr) float(value);
	}

	void PropertyTable::setStringValue(const PropertyId& id, int row, const String& value)
	{
		mada_assert(id.getValueType() == StringType);
		mada_assert(0 <= row && row < getNumRows());

		int idx = getColumnIndex(id);
		mada_assert(0 <= idx && idx < getNumCols());

		char* valuePtr = (char*)m_rows[row];
		valuePtr += m_columns[idx].offset;

		new (valuePtr) String(value);
	}

	void PropertyTable::setVector3Value(const PropertyId& id, int row, const Vector3& value)
	{
		mada_assert(id.getValueType() == Vector3Type);
		mada_assert(0 <= row && row < getNumRows());

		int idx = getColumnIndex(id);
		mada_assert(0 <= idx && idx < getNumCols());

		char* valuePtr = (char*)m_rows[row];
		valuePtr += m_columns[idx].offset;

		new (valuePtr) Vector3(value);
	}

	void PropertyTable::setQuaternionValue(const PropertyId& id, int row, const Quaternion& value)
	{
		mada_assert(id.getValueType() == QuaternionType);
		mada_assert(0 <= row && row < getNumRows());

		int idx = getColumnIndex(id);
		mada_assert(0 <= idx && idx < getNumCols());

		char* valuePtr = (char*)m_rows[row];
		valuePtr += m_columns[idx].offset;

		new (valuePtr) Quaternion(value);
	}
}
