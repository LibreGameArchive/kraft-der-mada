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

#ifndef __MADA_MADA_SOUNDMANAGER_H__
#define __MADA_MADA_SOUNDMANAGER_H__

#include "MadaPrerequisites.h"

#include <map>
#include <set>

#include <irrKlang.h>

#include "MadaGameTask.h"

namespace mada
{
	class SoundManager : public GameTask, public Ogre::Singleton<SoundManager>
	{
	public:
		SoundManager(const String& basedir);
		~SoundManager();

		void playSound2d(const String& fileName, bool loop = false);
		void stopSound(const String& fileName, float fade = 0.0f);

		virtual void run(Real timeSinceLastFrame);

	private:
		typedef std::set<irrklang::ISound*> SoundSet;
		typedef std::map<String, irrklang::ISound*> SoundMap;
		irrklang::ISoundEngine* mEngine;
		String mBaseDir;
		SoundMap mSoundsPlaying;
		SoundSet mSoundsFading;
	};
}

#endif