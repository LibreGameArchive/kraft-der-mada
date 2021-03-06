/*
	This file is part of Kraft der Mada.
	Copyright (c) 2010 Timm Eversmeyer

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

#include "sound/SoundEntity.h"
#include "Sound.h"
#include "SoundEntity.h"

namespace mada
{
	__mada_implement_root_class(SoundEntity);

        SoundEntity::SoundEntity() : m_isAttached(false), m_mesh(NULL), m_sound(NULL)
        {

        }

        SoundEntity::~SoundEntity()
        {

        }

        void SoundEntity::attach()
        {
            mada_assert(!m_isAttached)
        }
        
        void SoundEntity::deattach()
        {

        }

        void SoundEntity::setSound(Ptr<Sound> sound)
        {
            mada_assert(!m_isAttached)

	    m_sound = sound;
        }

	void SoundEntity::setPosition(const Vector3& pos)
	{
	    mada_assert(m_isAttached)

	    m_sound->setPosition(pos);
	}

	Vector3 SoundEntity::getPosition() const
	{
	    mada_assert(!m_isAttached)

	    return m_sound->getPosition();
	}

        bool SoundEntity::isAttached()
        {
            return m_isAttached;
        }
}
