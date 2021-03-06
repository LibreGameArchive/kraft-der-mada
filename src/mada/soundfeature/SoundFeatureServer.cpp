/*
	This file is part of Kraft der Mada.
	Copyright (c) 2009 Timm Eversmeyer

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

#include "soundfeature/SoundFeatureServer.h"

#include "soundfeature/SoundProperties.h"
#include "properties/PropertyId.h"

#include "GameServer.h"
#include "SoundFeatureServer.h"

namespace mada
{
	__mada_implement_class(SoundFeatureServer, FeatureServer);
	__mada_implement_singleton(SoundFeatureServer);

	SoundFeatureServer::SoundFeatureServer()
	{
		__mada_construct_singleton;

		// Init properties
		PropertyId soundVolume = prop::_sound_volume;
		PropertyId soundFile = prop::_sound_file;
	}

	SoundFeatureServer::~SoundFeatureServer()
	{
		__mada_destruct_singleton;
	}

        void SoundFeatureServer::onActivate()
        {
            m_SoundServer = SoundServer::create();
            m_SoundServer->open();
        }

        void SoundFeatureServer::onDeactivate()
        {
            m_SoundServer->close();
            m_SoundServer = NULL;
        }
}
