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

#include "graphicsfeature/MeshGraphicsComponent.h"

#include "graphicsfeature/MeshGraphicsManager.h"
#include "graphicsfeature/GraphicsProperties.h"

#include "game/core/GameObject.h"
#include "game/core/CoreProperties.h"

#include "graphics/GraphicsEntity.h"
#include "graphics/GraphicsServer.h"

namespace mada
{
	__mada_implement_class(MeshGraphicsComponent, Component);

	MeshGraphicsComponent::MeshGraphicsComponent() : m_entity()
	{
	}

	MeshGraphicsComponent::~MeshGraphicsComponent()
	{
		mada_assert(m_entity == NULL);
	}

	void MeshGraphicsComponent::onActivate()
	{
		mada_assert(m_entity == NULL);

		String meshName = getGameObject()->getStringProperty(prop::_graphics_object);

		m_entity = GraphicsEntity::create();
		m_entity->setMeshName(meshName);

		m_entity->attach();

		Vector3 pos = getGameObject()->getVector3Property(prop::_position);
		Quaternion orientation = getGameObject()->getQuaternionProperty(prop::_orientation);

		m_entity->setPosition(pos);
		m_entity->setOrientation(orientation);
	}

	void MeshGraphicsComponent::onDeactivate()
	{
		mada_assert(m_entity != NULL);

		m_entity->detach();
		m_entity = NULL;
	}
}
