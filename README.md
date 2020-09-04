# COCK-AND-BALL
self driving wagon with manipulator

## Project initialization with CLion
in project level directory
```shell script
source /opt/ros/$(ROS_DISTRO)/setup.zsh
```
or
```shell script
source /opt/ros/$(ROS_DISTRO)/setup.bash
```
then call clion from terminal (it is usually under ~/.local/share/JetBrains/... directory)
```shell script
# for me it is simply:
clion
```
and then load cmake project from 
```shell script
./cbt_ws/src/CMakeLists.txt
```

## Project structure
Every node should be subclassed from one of abstract_nodes
