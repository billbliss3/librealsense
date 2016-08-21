// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2015 Intel Corporation. All Rights Reserved.

#pragma once
#ifndef LIBREALSENSE_DS5_PRIVATE_H
#define LIBREALSENSE_DS5_PRIVATE_H

#include "uvc.h"
#include <mutex>

namespace rsimpl {
namespace ds5 {

    enum gvd_fields : int32_t
    {
        fw_version_offset = 12
    };

    struct calibration_tables
    {
        int version;
        uint32_t serial_number;
        rs_intrinsics modesLR[3];
        rs_intrinsics intrinsicsThird[2];
        rs_intrinsics modesThird[2][2];
        float Rthird[9], T[3], B;
    };

    std::string read_firmware_version(uvc::device & device);

    // Claim USB interface used for device
    void claim_ds5_monitor_interface(uvc::device & device);
    void claim_ds5_motion_module_interface(uvc::device & device);

    // Read device state
    void get_gvd(uvc::device & device, std::timed_mutex & mutex, size_t sz, char * gvd);
    void get_firmware_version_string(uvc::device & dev, std::timed_mutex & mutex, std::string & version);
    void get_module_serial_string(uvc::device & dev, std::timed_mutex & mutex, std::string & serial, unsigned int offset);
    calibration_tables read_calibrations(uvc::device & dev, std::timed_mutex & mutex);

    // XU read/write
    void get_laser_power(const uvc::device & device, uint8_t & laser_power);
    void set_laser_power(uvc::device & device, uint8_t laser_power);


} //namespace rsimpl::ds5
} // namespace rsimpl

#endif  // DS5_PRIVATE_H