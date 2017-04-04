/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
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
 * Author: George F. Sourabh Jain
 *                  <jainsourabh679@gmail.com>
 */
// Define an object to create a Fat-Tree topology.

#ifndef POINT_TO_POINT_FAT_TREE_HELPER_H
#define POINT_TO_POINT_FAT_TREE_HELPER_H

#include <vector>
#include <string>
#include "point-to-point-helper.h"
#include "ipv4-address-helper.h"
#include "ipv6-address-helper.h"
#include "internet-stack-helper.h"
#include "ipv4-interface-container.h"
#include "ipv6-interface-container.h"

namespace ns3 {

/**
 * \ingroup point-to-point-layout
 *
 * \brief A helper to make it easier to create a Fat-Tree topology
 * with p2p links
 */
class PointToPointFatTreeHelper
{
public:
  /**
   * Create a PointToPointFatTreeHelper in order to easily create
   * Fat-Tree Topology using p2p links
   */
   
   PointToPointFatTreeHelper (uint32_t nCore,
                               uint32_t nAggregator,
                               uint32_t nEdgeNode,
                               PointToPointHelper coreAggregatorHelper,
                               PointToPointHelper aggregatorEdgeNodeHelper);

  ~PointToPointFatTreeHelper ();

public:


  void PointToPointFatTreeHelper::InstallStack (InternetStackHelper stack)

  Ptr<Node> GetCore (uint32_t i) const;
  
  Ptr<Node> GetAggregator (uint32_t i) const;
  
  Ptr<Node> GetEdgeNode (uint32_t aggregatorNodeIndex, uint32_t i) const;
  
  Ipv4Address GetCoreIpv4Address (uint32_t i) const;
  
  Ipv4Address GetAggregatorIpv4Address (uint32_t i) const;
  
  Ipv4Address GetEdgeNodeIpv4Address (uint32_t aggregatorNodeIndex, uint32_t i) const;
  
  uint32_t coreCount () const;
  
  uint32_t aggregatorCout () const;
  
  uint32_t aggregatorEdgeNodeCount () const;
  
  void    InstallStack (InternetStackHelper stack);
  
  void      AssignIpv4Addresses (// yet to decide
                                );
  
private:

  NodeContainer                          m_nCore;
  NodeContainer                          m_nAggregator;
  std::vector <NodeContainer>            m_edge;
  
  std::vector <NetDeviceContainer>       m_coreDevicesToAggregator;
  std::vector <NetDeviceContainer>       m_aggregatorToCoreDevices;
  std::vector <NetDeviceContainer>       m_aggregatorToEdgeDevices;
  std::vector <NetDeviceContainer>       m_edgeDevice;
  
  std::vector <Ipv4InterfaceContainer>   m_coreInterfaces;
  std::vector <Ipv4InterfaceContainer>   m_aggregatorToCoreInterfaces;
  std::vector <Ipv4InterfaceContainer>   m_aggregatorToEdgeInterfaces;
  std::vector <Ipv4InterfaceContainer>   m_edgeInterface;
  
  std::vector <Ipv6InterfaceContainer>   m_coreInterfaces6;
  std::vector <Ipv6InterfaceContainer>   m_aggregatorToCoreInterfaces6;
  std::vector <Ipv6InterfaceContainer>   m_aggregatorToEdgeInterfaces6;
  std::vector <Ipv6InterfaceContainer>   m_edgeInterfaces6;

};


} // namespace ns3

#endif /* POINT_TO_POINT_FAT_TREE_H */
