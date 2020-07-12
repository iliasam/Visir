namespace VisirApp2
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

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Security", "CA2140:TransparentMethodsMustNotReferenceCriticalCodeFxCopRule")]
        public void update_from_mavlink(MavLink.Msg_mav_rotation_vector_euler message)
		{
			roll = message.roll;
			pitch = message.pitch;
			yaw = message.yaw;
			accuracy = message.accur;
			state = (byte)message.state;
		}

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Security", "CA2140:TransparentMethodsMustNotReferenceCriticalCodeFxCopRule")]
        public void update_from_mavlink(MavLink.Msg_mav_game_rotation_vector_euler message)
        {
            roll = message.roll;
            pitch = message.pitch;
            yaw = message.yaw;
            accuracy = message.accur;
            state = (byte)message.state;
        }
    }
}
