#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import Float32

def compass():
    pub = rospy.Publisher('heading', Float32, queue_size=10)
    rospy.init_node('compass', anonymous=True)
    rate = rospy.Rate(10) # 10hz
	rospy.loginfo("Compass ready.")
    while not rospy.is_shutdown():
        pub.publish(heading)
        rate.sleep()

if __name__ == '__main__':
    try:
        compass()
    except rospy.ROSInterruptException:
        pass