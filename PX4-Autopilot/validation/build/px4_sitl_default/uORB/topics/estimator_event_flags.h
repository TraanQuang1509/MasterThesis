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

/* Auto-generated by genmsg_cpp from file /home/uav/PX4-Autopilot/msg/EstimatorEventFlags.msg */


#pragma once


#include <uORB/uORB.h>


#ifndef __cplusplus

#endif


#ifdef __cplusplus
struct __EXPORT estimator_event_flags_s {
#else
struct estimator_event_flags_s {
#endif
	uint64_t timestamp;
	uint64_t timestamp_sample;
	uint32_t information_event_changes;
	uint32_t warning_event_changes;
	bool gps_checks_passed;
	bool reset_vel_to_gps;
	bool reset_vel_to_flow;
	bool reset_vel_to_vision;
	bool reset_vel_to_zero;
	bool reset_pos_to_last_known;
	bool reset_pos_to_gps;
	bool reset_pos_to_vision;
	bool starting_gps_fusion;
	bool starting_vision_pos_fusion;
	bool starting_vision_vel_fusion;
	bool starting_vision_yaw_fusion;
	bool yaw_aligned_to_imu_gps;
	bool reset_hgt_to_baro;
	bool reset_hgt_to_gps;
	bool reset_hgt_to_rng;
	bool reset_hgt_to_ev;
	bool gps_quality_poor;
	bool gps_fusion_timout;
	bool gps_data_stopped;
	bool gps_data_stopped_using_alternate;
	bool height_sensor_timeout;
	bool stopping_navigation;
	bool invalid_accel_bias_cov_reset;
	bool bad_yaw_using_gps_course;
	bool stopping_mag_use;
	bool vision_data_stopped;
	bool emergency_yaw_reset_mag_stopped;
	bool emergency_yaw_reset_gps_yaw_stopped;
	uint8_t _padding0[3]; // required for logger


#ifdef __cplusplus

#endif
};

#ifdef __cplusplus
namespace px4 {
	namespace msg {
		using EstimatorEventFlags = estimator_event_flags_s;
	} // namespace msg
} // namespace px4
#endif

/* register this as object request broker structure */
ORB_DECLARE(estimator_event_flags);


#ifdef __cplusplus
void print_message(const orb_metadata *meta, const estimator_event_flags_s& message);
#endif
