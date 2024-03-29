/*
 * Copyright (C) 2020 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <aidl/android/hardware/power/BnPower.h>
#include <android-base/file.h>
#include "power-common.h"

#define BATTERY_SAVER_NODE "/sys/module/battery_saver/parameters/enabled"
#define GPU_MIN_PWRLEVEL_NODE "/sys/class/kgsl/kgsl-3d0/min_pwrlevel"

namespace aidl {
namespace google {
namespace hardware {
namespace power {
namespace impl {
namespace pixel {

using ::aidl::android::hardware::power::Mode;
using ::android::base::WriteStringToFile;

bool isDeviceSpecificModeSupported(Mode type, bool* _aidl_return) {
    switch (type) {
        case Mode::EXPENSIVE_RENDERING:
        case Mode::LOW_POWER:
            *_aidl_return = true;
            return true;
        default:
            return false;
    }
}

bool setDeviceSpecificMode(Mode type, bool enabled) {
    switch (type) {
        case Mode::EXPENSIVE_RENDERING:
            WriteStringToFile(enabled ? "0" : "6", GPU_MIN_PWRLEVEL_NODE, true);
            return true;
        case Mode::LOW_POWER:
            WriteStringToFile(enabled ? "Y" : "N", BATTERY_SAVER_NODE, true);
            return true;
        default:
            return false;
    }
}

}  // namespace pixel
}  // namespace impl
}  // namespace power
}  // namespace hardware
}  // namespace google
}  // namespace aidl
