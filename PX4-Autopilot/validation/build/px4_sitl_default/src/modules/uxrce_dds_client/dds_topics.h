
#include <utilities.hpp>

#include <uxr/client/client.h>
#include <ucdr/microcdr.h>

#include <mathlib/mathlib.h>
#include <uORB/Publication.hpp>
#include <uORB/PublicationMulti.hpp>
#include <uORB/uORB.h>
#include <uORB/ucdr/distance_sensor.h>
#include <uORB/topics/distance_sensor.h>
#include <uORB/ucdr/gimbal_device_attitude_status.h>
#include <uORB/topics/gimbal_device_attitude_status.h>
#include <uORB/ucdr/input_rc.h>
#include <uORB/topics/input_rc.h>
#include <uORB/ucdr/mount_orientation.h>
#include <uORB/topics/mount_orientation.h>
#include <uORB/ucdr/offboard_control_mode.h>
#include <uORB/topics/offboard_control_mode.h>
#include <uORB/ucdr/sensor_optical_flow.h>
#include <uORB/topics/sensor_optical_flow.h>
#include <uORB/ucdr/vehicle_attitude.h>
#include <uORB/topics/vehicle_attitude.h>
#include <uORB/ucdr/vehicle_attitude_setpoint.h>
#include <uORB/topics/vehicle_attitude_setpoint.h>
#include <uORB/ucdr/vehicle_command.h>
#include <uORB/topics/vehicle_command.h>
#include <uORB/ucdr/vehicle_global_position.h>
#include <uORB/topics/vehicle_global_position.h>
#include <uORB/ucdr/vehicle_local_position.h>
#include <uORB/topics/vehicle_local_position.h>
#include <uORB/ucdr/vehicle_status.h>
#include <uORB/topics/vehicle_status.h>
#include <uORB/ucdr/vehicle_thrust_setpoint.h>
#include <uORB/topics/vehicle_thrust_setpoint.h>
#include <uORB/ucdr/vehicle_torque_setpoint.h>
#include <uORB/topics/vehicle_torque_setpoint.h>

#define UXRCE_DEFAULT_POLL_RATE 10

typedef bool (*UcdrSerializeMethod)(const void* data, ucdrBuffer& buf, int64_t time_offset);

static constexpr int max_topic_size = 512;
static_assert(sizeof(vehicle_attitude_s) <= max_topic_size, "topic too large, increase max_topic_size");
static_assert(sizeof(vehicle_global_position_s) <= max_topic_size, "topic too large, increase max_topic_size");
static_assert(sizeof(vehicle_local_position_s) <= max_topic_size, "topic too large, increase max_topic_size");
static_assert(sizeof(vehicle_status_s) <= max_topic_size, "topic too large, increase max_topic_size");
static_assert(sizeof(input_rc_s) <= max_topic_size, "topic too large, increase max_topic_size");
static_assert(sizeof(distance_sensor_s) <= max_topic_size, "topic too large, increase max_topic_size");
static_assert(sizeof(gimbal_device_attitude_status_s) <= max_topic_size, "topic too large, increase max_topic_size");
static_assert(sizeof(mount_orientation_s) <= max_topic_size, "topic too large, increase max_topic_size");

struct SendSubscription {
	const struct orb_metadata *orb_meta;
	uxrObjectId data_writer;
	const char* dds_type_name;
	uint32_t topic_size;
	UcdrSerializeMethod ucdr_serialize_method;
};

// Subscribers for messages to send
struct SendTopicsSubs {
	SendSubscription send_subscriptions[8] = {
			{ ORB_ID(vehicle_attitude),
			  uxr_object_id(0, UXR_INVALID_ID),
			  "px4_msgs::msg::dds_::VehicleAttitude_",
			  ucdr_topic_size_vehicle_attitude(),
			  &ucdr_serialize_vehicle_attitude,
			},
			{ ORB_ID(vehicle_global_position),
			  uxr_object_id(0, UXR_INVALID_ID),
			  "px4_msgs::msg::dds_::VehicleGlobalPosition_",
			  ucdr_topic_size_vehicle_global_position(),
			  &ucdr_serialize_vehicle_global_position,
			},
			{ ORB_ID(vehicle_local_position),
			  uxr_object_id(0, UXR_INVALID_ID),
			  "px4_msgs::msg::dds_::VehicleLocalPosition_",
			  ucdr_topic_size_vehicle_local_position(),
			  &ucdr_serialize_vehicle_local_position,
			},
			{ ORB_ID(vehicle_status),
			  uxr_object_id(0, UXR_INVALID_ID),
			  "px4_msgs::msg::dds_::VehicleStatus_",
			  ucdr_topic_size_vehicle_status(),
			  &ucdr_serialize_vehicle_status,
			},
			{ ORB_ID(input_rc),
			  uxr_object_id(0, UXR_INVALID_ID),
			  "px4_msgs::msg::dds_::InputRc_",
			  ucdr_topic_size_input_rc(),
			  &ucdr_serialize_input_rc,
			},
			{ ORB_ID(distance_sensor),
			  uxr_object_id(0, UXR_INVALID_ID),
			  "px4_msgs::msg::dds_::DistanceSensor_",
			  ucdr_topic_size_distance_sensor(),
			  &ucdr_serialize_distance_sensor,
			},
			{ ORB_ID(gimbal_device_attitude_status),
			  uxr_object_id(0, UXR_INVALID_ID),
			  "px4_msgs::msg::dds_::GimbalDeviceAttitudeStatus_",
			  ucdr_topic_size_gimbal_device_attitude_status(),
			  &ucdr_serialize_gimbal_device_attitude_status,
			},
			{ ORB_ID(mount_orientation),
			  uxr_object_id(0, UXR_INVALID_ID),
			  "px4_msgs::msg::dds_::MountOrientation_",
			  ucdr_topic_size_mount_orientation(),
			  &ucdr_serialize_mount_orientation,
			},
	};

	px4_pollfd_struct_t fds[8] {};

	uint32_t num_payload_sent{};

	void init();
	void update(uxrSession *session, uxrStreamId reliable_out_stream_id, uxrStreamId best_effort_stream_id, uxrObjectId participant_id, const char *client_namespace);
	void reset();
};

void SendTopicsSubs::init() {
	for (unsigned idx = 0; idx < sizeof(send_subscriptions)/sizeof(send_subscriptions[0]); ++idx) {
		fds[idx].fd = orb_subscribe(send_subscriptions[idx].orb_meta);
		fds[idx].events = POLLIN;
		orb_set_interval(fds[idx].fd, UXRCE_DEFAULT_POLL_RATE);
	}
}

void SendTopicsSubs::reset() {
	num_payload_sent = 0;
	for (unsigned idx = 0; idx < sizeof(send_subscriptions)/sizeof(send_subscriptions[0]); ++idx) {
		send_subscriptions[idx].data_writer = uxr_object_id(0, UXR_INVALID_ID);
	}
};

void SendTopicsSubs::update(uxrSession *session, uxrStreamId reliable_out_stream_id, uxrStreamId best_effort_stream_id, uxrObjectId participant_id, const char *client_namespace)
{
	int64_t time_offset_us = session->time_offset / 1000; // ns -> us

	alignas(sizeof(uint64_t)) char topic_data[max_topic_size];

	for (unsigned idx = 0; idx < sizeof(send_subscriptions)/sizeof(send_subscriptions[0]); ++idx) {
		if (fds[idx].revents & POLLIN) {
			// Topic updated, copy data and send
			orb_copy(send_subscriptions[idx].orb_meta, fds[idx].fd, &topic_data);
			if (send_subscriptions[idx].data_writer.id == UXR_INVALID_ID) {
				// data writer not created yet
				create_data_writer(session, reliable_out_stream_id, participant_id, static_cast<ORB_ID>(send_subscriptions[idx].orb_meta->o_id), client_namespace, send_subscriptions[idx].orb_meta->o_name,
								   send_subscriptions[idx].dds_type_name, send_subscriptions[idx].data_writer);
			}

			if (send_subscriptions[idx].data_writer.id != UXR_INVALID_ID) {

				ucdrBuffer ub;
				uint32_t topic_size = send_subscriptions[idx].topic_size;
				if (uxr_prepare_output_stream(session, best_effort_stream_id, send_subscriptions[idx].data_writer, &ub, topic_size) != UXR_INVALID_REQUEST_ID) {
					send_subscriptions[idx].ucdr_serialize_method(&topic_data, ub, time_offset_us);
					// TODO: fill up the MTU and then flush, which reduces the packet overhead
					uxr_flash_output_streams(session);
					num_payload_sent += topic_size;

				} else {
					//PX4_ERR("Error uxr_prepare_output_stream UXR_INVALID_REQUEST_ID %s", send_subscriptions[idx].subscription.get_topic()->o_name);
				}

			} else {
				//PX4_ERR("Error UXR_INVALID_ID %s", send_subscriptions[idx].subscription.get_topic()->o_name);
			}

		}
	}
}

// Publishers for received messages
struct RcvTopicsPubs {
	uORB::Publication<offboard_control_mode_s> offboard_control_mode_pub{ORB_ID(offboard_control_mode)};
	uORB::Publication<sensor_optical_flow_s> sensor_optical_flow_pub{ORB_ID(sensor_optical_flow)};
	uORB::Publication<vehicle_attitude_setpoint_s> vehicle_attitude_setpoint_pub{ORB_ID(vehicle_attitude_setpoint)};
	uORB::Publication<vehicle_command_s> vehicle_command_pub{ORB_ID(vehicle_command)};
	uORB::Publication<vehicle_thrust_setpoint_s> vehicle_thrust_setpoint_pub{ORB_ID(vehicle_thrust_setpoint)};
	uORB::Publication<vehicle_torque_setpoint_s> vehicle_torque_setpoint_pub{ORB_ID(vehicle_torque_setpoint)};


	uint32_t num_payload_received{};

	bool init(uxrSession *session, uxrStreamId reliable_out_stream_id, uxrStreamId reliable_in_stream_id, uxrStreamId best_effort_in_stream_id, uxrObjectId participant_id, const char *client_namespace);
};

static void on_topic_update(uxrSession *session, uxrObjectId object_id, uint16_t request_id, uxrStreamId stream_id,
		     struct ucdrBuffer *ub, uint16_t length, void *args)
{
	RcvTopicsPubs *pubs = (RcvTopicsPubs *)args;
	const int64_t time_offset_us = session->time_offset / 1000; // ns -> us
	pubs->num_payload_received += length;

	switch (object_id.id) {
	case 0+ (65535U / 32U) + 1: {
			offboard_control_mode_s data;

			if (ucdr_deserialize_offboard_control_mode(*ub, data, time_offset_us)) {
				//print_message(ORB_ID(offboard_control_mode), data);
				pubs->offboard_control_mode_pub.publish(data);
			}
		}
		break;

	case 1+ (65535U / 32U) + 1: {
			sensor_optical_flow_s data;

			if (ucdr_deserialize_sensor_optical_flow(*ub, data, time_offset_us)) {
				//print_message(ORB_ID(sensor_optical_flow), data);
				pubs->sensor_optical_flow_pub.publish(data);
			}
		}
		break;

	case 2+ (65535U / 32U) + 1: {
			vehicle_attitude_setpoint_s data;

			if (ucdr_deserialize_vehicle_attitude_setpoint(*ub, data, time_offset_us)) {
				//print_message(ORB_ID(vehicle_attitude_setpoint), data);
				pubs->vehicle_attitude_setpoint_pub.publish(data);
			}
		}
		break;

	case 3+ (65535U / 32U) + 1: {
			vehicle_command_s data;

			if (ucdr_deserialize_vehicle_command(*ub, data, time_offset_us)) {
				//print_message(ORB_ID(vehicle_command), data);
				pubs->vehicle_command_pub.publish(data);
			}
		}
		break;

	case 4+ (65535U / 32U) + 1: {
			vehicle_thrust_setpoint_s data;

			if (ucdr_deserialize_vehicle_thrust_setpoint(*ub, data, time_offset_us)) {
				//print_message(ORB_ID(vehicle_thrust_setpoint), data);
				pubs->vehicle_thrust_setpoint_pub.publish(data);
			}
		}
		break;

	case 5+ (65535U / 32U) + 1: {
			vehicle_torque_setpoint_s data;

			if (ucdr_deserialize_vehicle_torque_setpoint(*ub, data, time_offset_us)) {
				//print_message(ORB_ID(vehicle_torque_setpoint), data);
				pubs->vehicle_torque_setpoint_pub.publish(data);
			}
		}
		break;


	default:
		PX4_ERR("unknown object id: %i", object_id.id);
		break;
	}
}

bool RcvTopicsPubs::init(uxrSession *session, uxrStreamId reliable_out_stream_id, uxrStreamId reliable_in_stream_id, uxrStreamId best_effort_in_stream_id, uxrObjectId participant_id, const char *client_namespace)
{
	{
			uint16_t queue_depth = orb_get_queue_size(ORB_ID(offboard_control_mode)) * 2; // use a bit larger queue size than internal
			create_data_reader(session, reliable_out_stream_id, best_effort_in_stream_id, participant_id, 0, client_namespace, "offboard_control_mode", "px4_msgs::msg::dds_::OffboardControlMode_", queue_depth);
	}
	{
			uint16_t queue_depth = orb_get_queue_size(ORB_ID(sensor_optical_flow)) * 2; // use a bit larger queue size than internal
			create_data_reader(session, reliable_out_stream_id, best_effort_in_stream_id, participant_id, 1, client_namespace, "sensor_optical_flow", "px4_msgs::msg::dds_::SensorOpticalFlow_", queue_depth);
	}
	{
			uint16_t queue_depth = orb_get_queue_size(ORB_ID(vehicle_attitude_setpoint)) * 2; // use a bit larger queue size than internal
			create_data_reader(session, reliable_out_stream_id, best_effort_in_stream_id, participant_id, 2, client_namespace, "vehicle_attitude_setpoint", "px4_msgs::msg::dds_::VehicleAttitudeSetpoint_", queue_depth);
	}
	{
			uint16_t queue_depth = orb_get_queue_size(ORB_ID(vehicle_command)) * 2; // use a bit larger queue size than internal
			create_data_reader(session, reliable_out_stream_id, best_effort_in_stream_id, participant_id, 3, client_namespace, "vehicle_command", "px4_msgs::msg::dds_::VehicleCommand_", queue_depth);
	}
	{
			uint16_t queue_depth = orb_get_queue_size(ORB_ID(vehicle_thrust_setpoint)) * 2; // use a bit larger queue size than internal
			create_data_reader(session, reliable_out_stream_id, best_effort_in_stream_id, participant_id, 4, client_namespace, "vehicle_thrust_setpoint", "px4_msgs::msg::dds_::VehicleThrustSetpoint_", queue_depth);
	}
	{
			uint16_t queue_depth = orb_get_queue_size(ORB_ID(vehicle_torque_setpoint)) * 2; // use a bit larger queue size than internal
			create_data_reader(session, reliable_out_stream_id, best_effort_in_stream_id, participant_id, 5, client_namespace, "vehicle_torque_setpoint", "px4_msgs::msg::dds_::VehicleTorqueSetpoint_", queue_depth);
	}

	uxr_set_topic_callback(session, on_topic_update, this);

	return true;
}
