#!/usr/bin/env python
# license removed for brevity

import hmc5883l
import rospy
from std_msgs.msg import Float32

def handle_compass():

	pub = rospy.Publisher('heading', Float32, queue_size=10)
	rospy.init_node('compass', anonymous=True)
	rate = rospy.Rate(3) # 3hz

	compass = hmc5883l.hmc5883l(gauss = 4.7, declination = (-2,5))

	rospy.loginfo("Compass ready.")
	
	while not rospy.is_shutdown():
		degress = compass.degrees(compass.heading())
		pub.publish(degress[0])
		rate.sleep()

if __name__ == '__main__':
	try:
		handle_compass()
	except rospy.ROSInterruptException:
		pass
