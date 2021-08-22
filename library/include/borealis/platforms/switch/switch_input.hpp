/*
    Copyright 2021 natinusala
    Copyright (C) 2021  XITRIX

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#pragma once

#include <switch.h>

#include <borealis/core/input.hpp>

#define TOUCHES_MAX 10

namespace brls
{

// InputManager that uses the hid sysmodule to get inputs
class SwitchInputManager : public InputManager
{
  public:
    SwitchInputManager();

    void updateControllerState(ControllerState* state) override;

    void updateTouchStates(std::vector<RawTouchState>* states) override;

    void updateMouseStates(RawMouseState* state) override;

    void sendRumble(unsigned short controller, unsigned short lowFreqMotor, unsigned short highFreqMotor) override;

  private:
    PadState padState;
    HidVibrationDeviceHandle m_vibration_device_handles[2][2];
    HidVibrationValue m_vibration_values[2];
};

} // namespace brls
