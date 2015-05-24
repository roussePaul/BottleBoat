#!/usr/bin/env python3
# license removed for brevity

from i2clibraries import i2c_hmc5883l
import rospy
from std_msgs.msg import Float32

def compass():

    pub = rospy.Publisher('heading', Float32, queue_size=10)
    rospy.init_node('compass', anonymous=True)
    rate = rospy.Rate(10) # 10hz

	hmc5883l = i2c_hmc5883l.i2c_hmc5883l(1)
	hmc5883l.setContinuousMode()
	hmc5883l.setDeclination(9,54)
	rospy.loginfo("Compass ready.")
    
    while not rospy.is_shutdown():
		(degress, minutes) = hmc5883l.getHeading()
        pub.publish(degress)
        rate.sleep()

if __name__ == '__main__':
    try:
        compass()
    except rospy.ROSInterruptException:
        pass