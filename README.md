# Giacomo_Caiazzo_Homework_-
Repository dell'homework 1 del corso di Robotics Lab di Giacomo Caiazzo


## Robotics Lab - Homework 1

### Overview
This is a report of the Homework 1 of Robotics Lab course using Docker and ROS2 with RVIZ2 and Gazebo. The repo contains the steps to download the folders from github and to run the launch files for the simulations of the builded manipulator robot.

### Usage

Open the terminal, open the container and enter into the directory where you want to download the folder, then download it with:

    $ git clone "https:url_of_the_folder.com"

-------------------------------

To build the packages, enter into the ros2 workspace and build them with:

    $ colcon build

or you could build only the necessary packages using:

$ colcon build --packages-select arm_description arm_gazebo arm_control

Atfer this, we have to use the source command:

    $ source install/setup.bash

-------------------------------

Run the RVIZ2 simulation of the manipulator robot with:

    $ ros2 launch arm_description display.launch.py

or move to the src/arm_description/launch directory and run the simulation:


    $ cd src/arm_description/launch
    $ ros2 launch display.launch.py

--------------------------------

Run the Gazebo simulation of the manipulator with:

    $ ros2 launch arm_gazebo arm_world.launch.py

--------------------------------

If you want to run the simulation without the joints actuated, open the arm_world.launch.py and modify the following code lines:

      with open(urdf_arm_gazebo, 'r') as infp: ###line 26

      parameters=[robot_description_links,
                  {"use_sim_time": True}, ###line 42-43

--------------------------------

If you want to launch the gazebo simulation of the controlled arm, run the arm_gazebo.launch.py, which contains both the arm_world.launch.py and the arm_control.launch.py:

    $ ros2 launch arm_gazebo arm_gazebo.launch.py

--------------------------------


To use the camera sensor of the manipulator robot in Gazebo, launch the arm_gazebo launch file as previously described, open a new terminal on the same directory, connect the Docker container with the same image. To provide a network bridge which enables the exchange of messages between ROS 2 and Ignition Transport run:

    $ ros2 run ros_ign_bridge parameter_bridge /camera@sensor_msgs/msg/Image@gz.msgs.Image 

then, to see the camera point of view, run rqt via terminal:

    $ rqt

After this, open the Image View from "Plugins" menu -> "Image View", and select from the top-left selector the option /camera.

--------------------------------

To establish the communication between the publishers and the subscriber, launch arm_gazebo.launch.py as previously described. After this, open a new terminal on the same directory, connect the Docker container and run the controller node with:

    $ ros2 run arm_control arm_controller

then insert a vector of 4 floats separated by spaces in order to send the position command to the joints.

--------------------------------
