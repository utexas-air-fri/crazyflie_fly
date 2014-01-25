#include <stdio.h>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "cflie/CCrazyflie.h"

CCrazyRadio *crRadio;
CCrazyflie *cflieCopter;

void twistCallback(const geometry_msgs::Twist::ConstPtr& msg) {	
	cflieCopter->cycle();
	cout << (msg->linear.z * 10000) + 40000 << endl;
	if(msg->linear.z == 1)
		cflieCopter->setThrust(60000);
	else if(msg->linear.z == -1)
		cflieCopter->setThrust(35000);
	else
		cflieCopter->setThrust(40000);

	cflieCopter->setRoll(-20.0f * msg->linear.y);
	cflieCopter->setPitch(20.0f * msg->linear.x);
	cflieCopter->setYaw(-180.0 * msg->angular.z);
}

int main(int argc, char** argv) {

	ros::init(argc, argv, "crazyflie");
	ros::NodeHandle n;

	crRadio = new CCrazyRadio("radio://0/10/250K");

	if(crRadio->startRadio()) {
		cflieCopter = new CCrazyflie(crRadio);
		cflieCopter->setSendSetpoints(true);
		
		ros::Subscriber sub = n.subscribe("cmd_vel", 1000, twistCallback);

		ros::Rate loop_rate(10);

		ros::spin();
	
		delete cflieCopter;
	
	} else {
		cerr << "Could not connect to dongle. Did you plug it in?" << endl;
	}

	delete crRadio;

	return 0;

}
