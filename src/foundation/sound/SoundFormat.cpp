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


#include "sound/SoundFormat.h"
#include "SoundFormat.h"

namespace mada
{
    __mada_implement_root_class(SoundFormat);

    SoundFormat::SoundFormat() : m_isOpen(false)
    {

    }

    SoundFormat::~SoundFormat()
    {

    }

    void SoundFormat::play()
    {
        // Empty. Override in subclass if needed.
    }

    void SoundFormat::pause()
    {
        // Empty. Override in subclass if needed.
    }

    void SoundFormat::stop()
    {
        // Empty. Override in subclass if needed.
    }

    ALenum SoundFormat::open(String fileName)
    {
        // Empty. Override in subclass if needed.
		return AL_INVALID_ENUM;
    }

    void SoundFormat::close()
    {
    }

    void SoundFormat::update()
    {

    }

    void SoundFormat::setLoop(bool loop)
    {
        m_loop = loop;
    }

    ALuint SoundFormat::getBufferHandle()
    {
        return m_buffer;
    }
}
