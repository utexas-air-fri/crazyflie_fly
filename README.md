#Crazyflie Fly
A [ROS](http://www.ros.org/)-based suite for controlling the [Crazyflie](http://www.seeedstudio.com/depot/crazyflie-nano-quadcopter-kit-10dof-with-crazyradio-bccfk02b-p-1365.html) nano quadcopter. This suite has been developed in the Building Wide Intelligence lab of the University of Texas at Austin Computer Science department by Robert Lynch and Matt Broussard. 

##Installation

###Dependencies
This package downloads and compiles libcflie on make, which depends on GLFW. This is available in the apt repositories.
```
  sudo apt-get install libglfw-dev libglfw2 cmake
```
It is also dependent on the standard ROS packages `roscpp` and `geometry_msgs`.

###Installation Steps
Download the source code from the repository using `git clone` or another method to the `src` directory of a catkin workspace (e.g. `catkin_ws`) and compile using `catkin_make`.
```bash
$ cd ~/catkin_ws/src
$ git clone https://github.com/utexas-air-fri/crazyflie_fly.git
$ cd ~/catkin_ws
$ catkin_make
```

##crazyflie_driver
A C++ based driver for mediating traffic between ROS and the crazyflie API. This driver is based on the unofficial crazyflie C++ library [libcflie](https://github.com/fairlight1337/libcflie).

###Usage
To start the driver, run `rosrun crazyflie_fly crazyflie_driver`, or put it in a custom launch file

###Sending Commands
Once the node has started, the designated quadcopter will takeoff immediatly, since there is no automated takeoff/ landing code written into the firmware. This may be changed later.

Once taken off, commands may be published to the `cmd_vel` topic with messages of [`geometry_msgs/Twist`](http://www.ros.org/doc/api/geometry_msgs/html/msg/Twist.html) to control the pitch, roll, yaw, and altitude.
```
linear.x: move forward/backward
linear.y: move left/right
linear.z: move up/down
angular.z: turn left/right
```
