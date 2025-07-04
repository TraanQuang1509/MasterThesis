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

/* Auto-generated by genmsg_cpp from file /home/uav/PX4-Autopilot/msg/VehicleCommandAck.msg */


#pragma once


#include <uORB/uORB.h>


#ifndef __cplusplus
#define VEHICLE_COMMAND_ACK_VEHICLE_CMD_RESULT_ACCEPTED 0
#define VEHICLE_COMMAND_ACK_VEHICLE_CMD_RESULT_TEMPORARILY_REJECTED 1
#define VEHICLE_COMMAND_ACK_VEHICLE_CMD_RESULT_DENIED 2
#define VEHICLE_COMMAND_ACK_VEHICLE_CMD_RESULT_UNSUPPORTED 3
#define VEHICLE_COMMAND_ACK_VEHICLE_CMD_RESULT_FAILED 4
#define VEHICLE_COMMAND_ACK_VEHICLE_CMD_RESULT_IN_PROGRESS 5
#define VEHICLE_COMMAND_ACK_VEHICLE_CMD_RESULT_CANCELLED 6
#define VEHICLE_COMMAND_ACK_ARM_AUTH_DENIED_REASON_GENERIC 0
#define VEHICLE_COMMAND_ACK_ARM_AUTH_DENIED_REASON_NONE 1
#define VEHICLE_COMMAND_ACK_ARM_AUTH_DENIED_REASON_INVALID_WAYPOINT 2
#define VEHICLE_COMMAND_ACK_ARM_AUTH_DENIED_REASON_TIMEOUT 3
#define VEHICLE_COMMAND_ACK_ARM_AUTH_DENIED_REASON_AIRSPACE_IN_USE 4
#define VEHICLE_COMMAND_ACK_ARM_AUTH_DENIED_REASON_BAD_WEATHER 5
#define VEHICLE_COMMAND_ACK_ORB_QUEUE_LENGTH 4

#endif


#ifdef __cplusplus
struct __EXPORT vehicle_command_ack_s {
#else
struct vehicle_command_ack_s {
#endif
	uint64_t timestamp;
	uint32_t command;
	int32_t result_param2;
	uint16_t target_component;
	uint8_t result;
	uint8_t result_param1;
	uint8_t target_system;
	bool from_external;
	uint8_t _padding0[2]; // required for logger


#ifdef __cplusplus
	static constexpr uint8_t VEHICLE_CMD_RESULT_ACCEPTED = 0;
	static constexpr uint8_t VEHICLE_CMD_RESULT_TEMPORARILY_REJECTED = 1;
	static constexpr uint8_t VEHICLE_CMD_RESULT_DENIED = 2;
	static constexpr uint8_t VEHICLE_CMD_RESULT_UNSUPPORTED = 3;
	static constexpr uint8_t VEHICLE_CMD_RESULT_FAILED = 4;
	static constexpr uint8_t VEHICLE_CMD_RESULT_IN_PROGRESS = 5;
	static constexpr uint8_t VEHICLE_CMD_RESULT_CANCELLED = 6;
	static constexpr uint16_t ARM_AUTH_DENIED_REASON_GENERIC = 0;
	static constexpr uint16_t ARM_AUTH_DENIED_REASON_NONE = 1;
	static constexpr uint16_t ARM_AUTH_DENIED_REASON_INVALID_WAYPOINT = 2;
	static constexpr uint16_t ARM_AUTH_DENIED_REASON_TIMEOUT = 3;
	static constexpr uint16_t ARM_AUTH_DENIED_REASON_AIRSPACE_IN_USE = 4;
	static constexpr uint16_t ARM_AUTH_DENIED_REASON_BAD_WEATHER = 5;
	static constexpr uint8_t ORB_QUEUE_LENGTH = 4;

#endif
};

#ifdef __cplusplus
namespace px4 {
	namespace msg {
		using VehicleCommandAck = vehicle_command_ack_s;
	} // namespace msg
} // namespace px4
#endif

/* register this as object request broker structure */
ORB_DECLARE(vehicle_command_ack);


#ifdef __cplusplus
void print_message(const orb_metadata *meta, const vehicle_command_ack_s& message);
#endif
