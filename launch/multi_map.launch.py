from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='multi_map_nav',
            executable='navigation_server',
            name='multi_map_nav_server',
            output='screen'
        )
    ])
