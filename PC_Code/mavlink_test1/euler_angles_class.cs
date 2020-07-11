using System;
using MavLink;
using System.Numerics;

namespace mavlink_test1
{
	/// <summary>
	/// Description of euler_angles_class.
	/// </summary>
	public class euler_angles_class
	{
		public float roll;
		public float pitch;
		public float yaw;
		public float accuracy;
		public byte state;

        const float RADIANS_TO_DEGREES_MULTIPLIER = 57.29578f;

        public euler_angles_class()
		{
		}
		
		public void update_from_mavlink(MavLink.Msg_mav_rotation_vector_euler message)
		{
			roll = message.roll;
			pitch = message.pitch;
			yaw = message.yaw;
			accuracy = message.accur;
			state = (byte)message.state;
		}

        public void update_from_mavlink(MavLink.Msg_mav_game_rotation_vector_euler message)
        {
            roll = message.roll;
            pitch = message.pitch;
            yaw = message.yaw;
            accuracy = message.accur;
            state = (byte)message.state;
        }

        public void update_from_quaternion(Quaternion raw_quaternion)
        {
            float x = raw_quaternion.X;
            float y = raw_quaternion.Y;
            float z = raw_quaternion.Z;
            float w = raw_quaternion.W;

            
            yaw = (float)Math.Atan2(x * y + w * z, (w * w + x * x) - 0.5f) * RADIANS_TO_DEGREES_MULTIPLIER;
            roll = -(float)Math.Asin(2.0f * (x * z - w * y)) * RADIANS_TO_DEGREES_MULTIPLIER;
            pitch = (float)Math.Atan2(w * x + y * z, (w * w + z * z) - 0.5f) * RADIANS_TO_DEGREES_MULTIPLIER;

            accuracy = 0;
            state = 0;
        }

    }
}
