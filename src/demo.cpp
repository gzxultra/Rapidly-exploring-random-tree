/*
For class E599 Special Topics in Autonomous Robotics
ISE, Indiana University
Lantao Liu
9/21/2017
*/

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <visualization_msgs/Marker.h>
#include <sstream>
#include "node.h"
#include "tree.h"
#include "obstacle.h"
#include "workspace.h"
#include <tf/tf.h>


geometry_msgs::Point toGeoPoint(Node* node) {
    geometry_msgs::Point p;
    p.x = node->x;
    p.y = node->y;
    p.z = 0;
    return p;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "ros_demo");

    //create a ros handle (pointer) so that you can call and use it
    ros::NodeHandle n;

    //in <>, it specified the type of the message to be published
    //in (), first param: topic name; second param: size of queued messages, at least 1
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("some_chatter", 10);
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);

    //each second, ros "spins" and draws 20 frames
    ros::Rate loop_rate(60);

    int frame_count = 0;
    float f = 0.0;

    WorkSpace w = WorkSpace(0, 0, 20, 20);
    CubeObstacle *o1 = new CubeObstacle(2, 2, 2, 2);
    CubeObstacle *o2 = new CubeObstacle(15, 12, 6, 4);
    CubeObstacle *o3 = new CubeObstacle(16, 16, 2, 2);
    w.addObstacle(o1);
    w.addObstacle(o2);
    w.addObstacle(o3);

    Node *src = new Node(0, 0, 0, 1, 1);
    Node *goal = new Node(19, 19, 0, 1, 1);
    w.setSrc(src);
    w.setGoal(goal);

    Tree *t = new Tree(src);
    Node *node = NULL;
    double distance = 0;
    Node *nearestNodeOnTree = NULL;
    Node *newNode = NULL;
    bool isGoalFound = false;
    bool isPathGet = false;
    bool isPathSmooth = false;
    vector<Node*> roughPath;
    vector<Node*> smoothPath;

    while (ros::ok())
    {
        //first create a string typed (std_msgs) message
        std_msgs::String msg;

        std::stringstream ss;
        ss << "Frame index: " << frame_count;
        msg.data = ss.str();
        ROS_INFO("%s", msg.data.c_str()); //printing on screen

        //publisher publishes messages, the msg type must be consistent with definition advertise<>();
        chatter_pub.publish(msg);

        /******************** From here, we are defining and drawing two obstacles in the workspace **************************/

        // define two obstacles
        visualization_msgs::Marker obst1, obst2, obst3, srcPoint, goalPoint;

        // Set obst1 and obst2 as a Cube and Cylinder, respectively
        obst1.type = visualization_msgs::Marker::CUBE;
        obst2.type = visualization_msgs::Marker::CUBE;
        obst3.type = visualization_msgs::Marker::CUBE;
        srcPoint.type = visualization_msgs::Marker::CUBE;
        goalPoint.type = visualization_msgs::Marker::CUBE;

        // Set the frame ID and timestamp.  See the TF tutorials for information on these.
        obst1.header.frame_id = obst2.header.frame_id = obst3.header.frame_id = srcPoint.header.frame_id = goalPoint.header.frame_id = "map"; //NOTE: this should be "paired" to the frame_id entry in Rviz
        obst1.header.stamp = obst2.header.stamp = obst3.header.stamp = srcPoint.header.stamp = goalPoint.header.stamp = ros::Time::now();

        // Set the namespace and id
        obst1.ns = obst2.ns = obst3.ns = "obstacles";
        obst1.id = 0;
        obst2.id = 1;
        obst3.id = 2;

        srcPoint.ns = "source";
        srcPoint.id = 0;
        goalPoint.ns = "source";
        goalPoint.id = 1;

        // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
        obst1.action = obst2.action = obst3.action = visualization_msgs::Marker::ADD;
        srcPoint.action = goalPoint.action = visualization_msgs::Marker::ADD;

        // Set the scale of the marker
        obst1.scale.x = obst1.scale.y = obst1.scale.z = 2.0; //1x1x1 here means each side of the cube is 1m long
        obst2.scale.x = obst2.scale.y = obst2.scale.z = 2.0; //1x1x1 here means the cylinder as diameter 1m and height 1m
        obst3.scale.x = obst3.scale.y = obst3.scale.z = 2.0; //1x1x1 here means the cylinder as diameter 1m and height 1m
        srcPoint.scale.x = srcPoint.scale.y = srcPoint.scale.z = 0.5;
        goalPoint.scale.x = goalPoint.scale.y = goalPoint.scale.z = 0.5;

        srcPoint.color.r = 1.0f;
        srcPoint.color.g = 1.0f;
        // srcPoint.color.b = 0.2f;
        srcPoint.color.a = 1.0;
        srcPoint.pose.position.x = 0;
        srcPoint.pose.position.y = 0;

        // goalPoint.color.r = 0.0f;
        goalPoint.color.g = 1.0f;
        // goalPoint.color.b = 0.2f;
        goalPoint.color.a = 1.0;
        goalPoint.pose.position.x = 19;
        goalPoint.pose.position.y = 19;

        // Set the pose of the marker. since a side of the obstacle obst1 is 1m as defined above, now we place the obst1 center at (1, 2, 0.5). z-axis is height
        obst1.pose.position.x = 2;
        obst1.pose.position.y = 2;
        obst1.pose.position.z = 0.5;
        obst1.pose.orientation.x = 0.0;
        obst1.pose.orientation.y = 0.0;
        obst1.pose.orientation.z = 0.0;
        obst1.pose.orientation.w = 1.0; //(x, y, z, w) is a quaternion, ignore it here (quaternion can be converted to angle and converted back, ros can do it)

        obst2.pose.position.x = 15;
        obst2.pose.position.y = 12;
        obst2.pose.position.z = 0.5;
        obst2.pose.orientation = obst1.pose.orientation;

        obst3.pose.position.x = 16;
        obst3.pose.position.y = 16;
        obst3.pose.position.z = 0.5;
        obst3.pose.orientation = obst1.pose.orientation;

        // Set the color red, green, blue. if not set, by default the value is 0
        obst1.color.r = 0.0f;
        obst1.color.g = 1.0f;
        obst1.color.b = 0.0f;
        obst1.color.a = 1.0; //be sure to set alpha to something non-zero, otherwise it is transparent
        obst2.color = obst1.color;
        obst3.color = obst1.color;

        obst1.lifetime = obst2.lifetime = obst3.lifetime = srcPoint.lifetime = goalPoint.lifetime = ros::Duration();

        // publish these messages to ROS system
        marker_pub.publish(obst1);
        marker_pub.publish(obst2);
        marker_pub.publish(obst3);
        marker_pub.publish(srcPoint);
        marker_pub.publish(goalPoint);


        /************************* From here, we are using points, lines, to draw a tree structure *** ******************/

        //we use static here since we want to incrementally add contents in these mesgs, otherwise contents in these msgs will be cleaned in every ros spin.
        static visualization_msgs::Marker vertices, edges, pathVertices, pathEdges;

        vertices.type = visualization_msgs::Marker::POINTS;
        pathVertices.type = visualization_msgs::Marker::POINTS;
        edges.type = visualization_msgs::Marker::LINE_LIST;
        pathEdges.type = visualization_msgs::Marker::LINE_LIST;

        vertices.header.frame_id = edges.header.frame_id = pathVertices.header.frame_id = pathEdges.header.frame_id = "map";
        vertices.header.stamp = edges.header.stamp = pathVertices.header.stamp = pathEdges.header.stamp = ros::Time::now();
        vertices.ns = edges.ns = pathVertices.ns = pathEdges.ns = "vertices_and_lines";
        vertices.action = edges.action = pathVertices.action = pathEdges.action = visualization_msgs::Marker::ADD;
        vertices.pose.orientation.w = edges.pose.orientation.w = pathVertices.pose.orientation.w = pathVertices.pose.orientation.w = 1.0;

        vertices.id = 0;
        edges.id = 1;
        pathVertices.id = 2;
        pathEdges.id = 3;

        // POINTS markers use x and y scale for width/height respectively
        vertices.scale.x = 0.05;
        vertices.scale.y = 0.05;

        pathVertices.scale.x = 0.08;
        pathVertices.scale.y = 0.08;

        // LINE_STRIP/LINE_LIST markers use only the x component of scale, for the line width
        edges.scale.x = 0.02; //tune it yourself
        pathEdges.scale.x = 0.05; //tune it yourself

        // Points are green
        vertices.color.g = 1.0f;
        vertices.color.a = 1.0;

        pathVertices.color.g = 1.0f;
        pathVertices.color.a = 1.0;

        // Line list is red
        edges.color.r = 1.0;
        edges.color.a = 1.0;

        pathEdges.color.b = 1.0;
        pathEdges.color.a = 1.0;

        geometry_msgs::Point p0; // root vertex
        p0.x = p0.y = p0.z = 0;

        if (!isGoalFound) {
            int herz = 1;
            if (frame_count % herz == 0)
            {
                node = w.generateRandomValidNode(t);
                nearestNodeOnTree = t->findClosestNode(node, distance);
                newNode = t->extendNewNode(node, nearestNodeOnTree);
                if (w.isValidMoveOnWorkSpace(nearestNodeOnTree, newNode))
                {
                    t->addChild(nearestNodeOnTree, newNode);
                    // cout << "newChild Added " << newNode->serialize() << endl;
                    vertices.points.push_back(toGeoPoint(newNode));  //for drawing vertices
                    edges.points.push_back(toGeoPoint(nearestNodeOnTree)); //for drawing edges. The line list needs two points for each line
                    edges.points.push_back(toGeoPoint(newNode));

                    if (w.isCloseToTheGoal(newNode))
                    {
                        cout << "Goal Found!" << endl;
                        t->addChild(nearestNodeOnTree, goal);
                        isGoalFound = true;
                        roughPath = w.getRRTPath(t);
                        smoothPath = w.getSmoothPath(roughPath);
                    }
                }
                else
                {
                    // cout << "Not Valid!" << endl;
                }
            }
        }
        //publish msgs
        marker_pub.publish(vertices);
        marker_pub.publish(edges);

        /* Draw path */
        if (isGoalFound && !isPathGet) {
           if (!roughPath.empty()) {
               Node* node = roughPath.back();
               Node* pre = node->getParentNode();
               if (pre != NULL) {
                   pathVertices.points.push_back(toGeoPoint(node));
                   pathEdges.points.push_back(toGeoPoint(pre));
                   pathEdges.points.push_back(toGeoPoint(node));
                   roughPath.pop_back();
               }

           }
           else {
               vertices.points.clear();
               edges.points.clear();
               isPathGet = true;
           }
        }
        marker_pub.publish(pathVertices);
        marker_pub.publish(pathEdges);
        /******************** From here, we are defining and drawing a simple robot **************************/

        // a simple cube represents a robot
        static visualization_msgs::Marker rob;
        static visualization_msgs::Marker path;
        rob.type = visualization_msgs::Marker::CUBE;
        path.type = visualization_msgs::Marker::LINE_STRIP;

        rob.header.frame_id = path.header.frame_id = "map"; //NOTE: this should be "paired" to the frame_id entry in Rviz, the default setting in Rviz is "map"
        rob.header.stamp = path.header.stamp = ros::Time::now();
        rob.ns = path.ns = "rob";
        rob.id = 0;
        path.id = 1;
        rob.action = path.action = visualization_msgs::Marker::ADD;
        rob.lifetime = path.lifetime = ros::Duration();

        rob.scale.x = rob.scale.y = rob.scale.z = 0.3;

        rob.color.r = 1.0f;
        rob.color.g = 0.5f;
        rob.color.b = 0.5f;
        rob.color.a = 1.0;

        // path line strip is blue
        path.color.b = 1.0;
        path.color.a = 1.0;

        path.scale.x = 0.02;
        path.pose.orientation.w = 1.0;

        if (frame_count % 30 == 0 && isPathGet && !smoothPath.empty()) //update every 2 ROS frames
        {
            auto point = smoothPath.back();
            geometry_msgs::Point p = toGeoPoint(point);
            cout << "ROB" << p.x << '-' << p.y << endl;
            tf::Quaternion q = tf::createQuaternionFromRPY(0, 0, point->theta);
            rob.pose.position = p;
            rob.pose.orientation.w = q[3];
            path.points.push_back(p); //for drawing path, which is line strip type
            smoothPath.pop_back();
        }

        marker_pub.publish(rob);
        marker_pub.publish(path);

        /******************** To here, we finished displaying our components **************************/

        // check if there is a subscriber. Here our subscriber will be Rviz
        while (marker_pub.getNumSubscribers() < 1)
        {
            if (!ros::ok())
            {
                return 0;
            }
            ROS_WARN_ONCE("Please run Rviz in another terminal.");
            sleep(1);
        }

        //ros spins, force ROS frame to refresh/update once
        ros::spinOnce();

        loop_rate.sleep();
        ++frame_count;
    }

    return 0;
}
