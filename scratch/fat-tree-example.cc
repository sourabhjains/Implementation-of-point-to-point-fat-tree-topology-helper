/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2017 NITK Surathkal
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors: Viyom Mittal <viyommittal@gmail.com>
 *          Vivek Jain <jain.vivek.anand@gmail.com>
 *          Sourabh Jain <sourabhjain560@outlook.com>
 *          Mohit P. Tahiliani <tahiliani@nitk.edu.in>
 *
 */

#include <iostream>

#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/point-to-point-layout-module.h"
#include "ns3/traffic-control-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FatTree");

/**
* This program is used to test the functionality of FatTree topology
*/
int main (int argc, char *argv[])
{
  //double stopTime = 100;                                            // Universal stop time
  //std::string pcapFileName = "fat-tre";                         // Name of pcap file to be generated
  //uint16_t port = 50000;                                        // Port number used by applications

  uint32_t    nCore = 3;                                        // Number of core nodes
  uint32_t    nAggregator = 4;                                  // Number of nodes on right side of bottleneck
  uint32_t    nEdge = 3;                                         // Number of edge nodes
  uint32_t    maxWindowSize = 2000;                             // TCP Maximum window size. Default = 2000 bytes
  bool isWindowScalingEnabled = false;                          // To enable / disable the window scaling option
  std::string aggregatorToCoreRate = "5Mbps";                   // Bandwidth of link between core and aggregator nodes
  std::string aggregatorToCoreDelay = "2ms";                    // Propagation dealy of link between core and aggregator nodes
  std::string aggregatorToEdgeRate = "10Mbps";                  // Bandwidth of link between edge and aggregator nodes
  std::string aggregatorToEdgeDelay = "10ms";                   // Propagation dealy of link between edge and aggregator nodes
  std::string tcpVariant = "ns3::TcpYeah";                      // TCP Flavour to be used. Default = TcpYeah

  /**
  * Setting Seed Value for generating random number
  */
  SeedManager::SetRun (11223344);

  /**
  * Creating a random number value generator variable
  */
  Ptr<UniformRandomVariable> uv = CreateObject<UniformRandomVariable> ();

  /**
  * Setting the TCP window size to be used
  * Setting the window scaling option
  * Setting TCP variant to be used
  */
  
      std::cout << "Hello0" << std::endl;
  Config::SetDefault ("ns3::TcpSocketBase::MaxWindowSize", UintegerValue (maxWindowSize));
  Config::SetDefault ("ns3::TcpSocketBase::WindowScaling", BooleanValue (isWindowScalingEnabled));
  Config::SetDefault ("ns3::TcpL4Protocol::SocketType", StringValue (tcpVariant));

  /**
  * Creating point to point channel for bottleneck
  * Setting the date rate of the bottleneck link
  * Setting the propagation dealy of bottleneck link
  */
  PointToPointHelper aggregatorToCore;
  aggregatorToCore.SetDeviceAttribute  ("DataRate", StringValue (aggregatorToCoreRate));
  aggregatorToCore.SetChannelAttribute ("Delay", StringValue (aggregatorToCoreDelay));

  /**
  * Creating point to point channel for edge links
  * Setting the date rate of the edge links
  * Setting the propagation dealy of edge links
  */
  PointToPointHelper aggregatorToEdge;
  aggregatorToEdge.SetDeviceAttribute    ("DataRate", StringValue (aggregatorToEdgeRate));
  aggregatorToEdge.SetChannelAttribute   ("Delay", StringValue (aggregatorToEdgeDelay));
  
        std::cout << "Hello0.1" << std::endl;

  /**
  * Creating dumbbell topology which uses point to point channel for edge links and bottleneck using PointToPointDumbbellHelper
  */
  PointToPointFatTreeHelper d (nCore, nAggregator, nEdge, aggregatorToCore, aggregatorToEdge);

  /**
  * Installing Interstack in all nodes
  */
  InternetStackHelper stack;
  d.InstallStack (stack);

//  /**
//  * Installing queue disc on bottleneck queues. In this case, PfifoFastQueueDisc is installed
//  */
//  TrafficControlHelper tchBottleneck;
//  tchBottleneck.SetRootQueueDisc ("ns3::PfifoFastQueueDisc");
//  tchBottleneck.Install (d.GetLeft ()->GetDevice (0));
//  tchBottleneck.Install (d.GetRight ()->GetDevice (0));

//  /**
//  * Creating network and assigning IPs to respective nodes in that network
//  */
//  d.AssignIpv4Addresses (Ipv4AddressHelper ("10.1.1.0", "255.255.255.0"),
//                         Ipv4AddressHelper ("10.1.2.0", "255.255.255.0"),
//                         Ipv4AddressHelper ("10.1.3.0", "255.255.255.0"));

//  for (uint16_t i = 0; i < nLeftLeaf; i++)
//    {
//      /**
//      * Configuring sender application
//      * Installing  application on left side nodes
//      * Starting the application on left side node randomly between 0 second to 0.1 seconds
//      */
//      AddressValue remoteAddress (InetSocketAddress (d.GetRightIpv4Address (i), port));
//      BulkSendHelper tcpSender ("ns3::TcpSocketFactory", Address ());
//      tcpSender.SetAttribute ("Remote", remoteAddress);
//      tcpSender.SetAttribute ("SendSize", UintegerValue (1000));
//      ApplicationContainer senderApp = tcpSender.Install (d.GetLeft (i));
//      senderApp.Start (Seconds (uv->GetValue (0.0, 0.1)));
//      senderApp.Stop (Seconds (stopTime - 1));

//      /**
//      * Configuring receiver application
//      * Installing packet sink application on right side nodes
//      * Starting the application at 0 second and stoping it at stopTime
//      */
//      Address tcpReceiverLocalAddress (InetSocketAddress (Ipv4Address::GetAny (), port));
//      PacketSinkHelper tcpReceiver ("ns3::TcpSocketFactory", tcpReceiverLocalAddress);
//      tcpReceiver.SetAttribute ("Protocol", TypeIdValue (TcpSocketFactory::GetTypeId ()));
//      ApplicationContainer receiverApp = tcpReceiver.Install (d.GetRight (i));
//      receiverApp.Start (Seconds (0));
//      receiverApp.Stop (Seconds (stopTime));
//    }

//  /**
//  *  Enabling Pcap for point to point bottleneck channel to generate Pcap file
//  */
//  pointToPointRouter.EnablePcap (pcapFileName, NodeContainer (d.GetLeft ()), false);

//  /**
//  * Initializing routing table on the nodes
//  */
//  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
