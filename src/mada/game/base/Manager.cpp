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

#include "game/base/Manager.h"

namespace mada
{
	__mada_implement_class(Manager, MessageDispatcher);

	Manager::Manager() : m_isActive(false)
	{
	}

	Manager::~Manager()
	{
	}

	void Manager::onActivate()
	{
		mada_assert(!m_isActive);
		m_isActive = true;
	}

	void Manager::onDeactivate()
	{
		mada_assert(m_isActive);
		m_isActive = false;
	}

	bool Manager::isActive() const
	{
		return m_isActive;
	}

	void Manager::onLoad()
	{
	}

	void Manager::onSave()
	{
	}

	void Manager::onBeginFrame()
	{
	}

	void Manager::onFrame()
	{
	}

	void Manager::onEndFrame()
	{
	}
}
