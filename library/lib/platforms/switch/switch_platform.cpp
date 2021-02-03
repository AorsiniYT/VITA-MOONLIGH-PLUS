/*
    Borealis, a Nintendo Switch UI Library
    Copyright (C) 2021  natinusala

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <switch.h>

#include <borealis/platforms/switch/switch_platform.hpp>

namespace brls
{

SwitchPlatform::SwitchPlatform()
{
    this->videoContext = new SwitchVideoContext();
    this->audioPlayer  = new SwitchAudioPlayer();
    this->inputManager = new SwitchInputManager();
    this->touchManager = new SwitchTouchManager();
}

std::string SwitchPlatform::getName()
{
    return "Switch";
}

bool SwitchPlatform::mainLoopIteration()
{
    return appletMainLoop();
}

VideoContext* SwitchPlatform::getVideoContext()
{
    return this->videoContext;
}

AudioPlayer* SwitchPlatform::getAudioPlayer()
{
    return this->audioPlayer;
}

InputManager* SwitchPlatform::getInputManager()
{
    return this->inputManager;
}

TouchManager* SwitchPlatform::getTouchManager()
{
    return this->touchManager;
}

SwitchPlatform::~SwitchPlatform()
{
    delete this->audioPlayer;
    delete this->inputManager;
}

} // namespace brls
