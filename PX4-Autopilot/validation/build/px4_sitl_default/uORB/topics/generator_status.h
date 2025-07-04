/****************************************************************************
 *
 *   Copyright (C) 2013-2022 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/* Auto-generated by genmsg_cpp from file /home/uav/PX4-Autopilot/msg/GeneratorStatus.msg */


#pragma once


#include <uORB/uORB.h>


#ifndef __cplusplus
#define GENERATOR_STATUS_STATUS_FLAG_OFF 1
#define GENERATOR_STATUS_STATUS_FLAG_READY 2
#define GENERATOR_STATUS_STATUS_FLAG_GENERATING 4
#define GENERATOR_STATUS_STATUS_FLAG_CHARGING 8
#define GENERATOR_STATUS_STATUS_FLAG_REDUCED_POWER 16
#define GENERATOR_STATUS_STATUS_FLAG_MAXPOWER 32
#define GENERATOR_STATUS_STATUS_FLAG_OVERTEMP_WARNING 64
#define GENERATOR_STATUS_STATUS_FLAG_OVERTEMP_FAULT 128
#define GENERATOR_STATUS_STATUS_FLAG_ELECTRONICS_OVERTEMP_WARNING 256
#define GENERATOR_STATUS_STATUS_FLAG_ELECTRONICS_OVERTEMP_FAULT 512
#define GENERATOR_STATUS_STATUS_FLAG_ELECTRONICS_FAULT 1024
#define GENERATOR_STATUS_STATUS_FLAG_POWERSOURCE_FAULT 2048
#define GENERATOR_STATUS_STATUS_FLAG_COMMUNICATION_WARNING 4096
#define GENERATOR_STATUS_STATUS_FLAG_COOLING_WARNING 8192
#define GENERATOR_STATUS_STATUS_FLAG_POWER_RAIL_FAULT 16384
#define GENERATOR_STATUS_STATUS_FLAG_OVERCURRENT_FAULT 32768
#define GENERATOR_STATUS_STATUS_FLAG_BATTERY_OVERCHARGE_CURRENT_FAULT 65536
#define GENERATOR_STATUS_STATUS_FLAG_OVERVOLTAGE_FAULT 131072
#define GENERATOR_STATUS_STATUS_FLAG_BATTERY_UNDERVOLT_FAULT 262144
#define GENERATOR_STATUS_STATUS_FLAG_START_INHIBITED 524288
#define GENERATOR_STATUS_STATUS_FLAG_MAINTENANCE_REQUIRED 1048576
#define GENERATOR_STATUS_STATUS_FLAG_WARMING_UP 2097152
#define GENERATOR_STATUS_STATUS_FLAG_IDLE 4194304

#endif


#ifdef __cplusplus
struct __EXPORT generator_status_s {
#else
struct generator_status_s {
#endif
	uint64_t timestamp;
	uint64_t status;
	float battery_current;
	float load_current;
	float power_generated;
	float bus_voltage;
	float bat_current_setpoint;
	uint32_t runtime;
	int32_t time_until_maintenance;
	uint16_t generator_speed;
	int16_t rectifier_temperature;
	int16_t generator_temperature;
	uint8_t _padding0[6]; // required for logger


#ifdef __cplusplus
	static constexpr uint64_t STATUS_FLAG_OFF = 1;
	static constexpr uint64_t STATUS_FLAG_READY = 2;
	static constexpr uint64_t STATUS_FLAG_GENERATING = 4;
	static constexpr uint64_t STATUS_FLAG_CHARGING = 8;
	static constexpr uint64_t STATUS_FLAG_REDUCED_POWER = 16;
	static constexpr uint64_t STATUS_FLAG_MAXPOWER = 32;
	static constexpr uint64_t STATUS_FLAG_OVERTEMP_WARNING = 64;
	static constexpr uint64_t STATUS_FLAG_OVERTEMP_FAULT = 128;
	static constexpr uint64_t STATUS_FLAG_ELECTRONICS_OVERTEMP_WARNING = 256;
	static constexpr uint64_t STATUS_FLAG_ELECTRONICS_OVERTEMP_FAULT = 512;
	static constexpr uint64_t STATUS_FLAG_ELECTRONICS_FAULT = 1024;
	static constexpr uint64_t STATUS_FLAG_POWERSOURCE_FAULT = 2048;
	static constexpr uint64_t STATUS_FLAG_COMMUNICATION_WARNING = 4096;
	static constexpr uint64_t STATUS_FLAG_COOLING_WARNING = 8192;
	static constexpr uint64_t STATUS_FLAG_POWER_RAIL_FAULT = 16384;
	static constexpr uint64_t STATUS_FLAG_OVERCURRENT_FAULT = 32768;
	static constexpr uint64_t STATUS_FLAG_BATTERY_OVERCHARGE_CURRENT_FAULT = 65536;
	static constexpr uint64_t STATUS_FLAG_OVERVOLTAGE_FAULT = 131072;
	static constexpr uint64_t STATUS_FLAG_BATTERY_UNDERVOLT_FAULT = 262144;
	static constexpr uint64_t STATUS_FLAG_START_INHIBITED = 524288;
	static constexpr uint64_t STATUS_FLAG_MAINTENANCE_REQUIRED = 1048576;
	static constexpr uint64_t STATUS_FLAG_WARMING_UP = 2097152;
	static constexpr uint64_t STATUS_FLAG_IDLE = 4194304;

#endif
};

#ifdef __cplusplus
namespace px4 {
	namespace msg {
		using GeneratorStatus = generator_status_s;
	} // namespace msg
} // namespace px4
#endif

/* register this as object request broker structure */
ORB_DECLARE(generator_status);


#ifdef __cplusplus
void print_message(const orb_metadata *meta, const generator_status_s& message);
#endif
