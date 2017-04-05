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
 * Author:          Sourabh Jain
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
   *
   * \param nCore number core nodes in the Fat-tree topology
   *
   * \param nAggregator number aggregator nodes in the Fat-tree topology
   *
   * \param nEdgeNode number of aggregator at each aggregator.
   *
   * \param coreAggregatorHelper PointToPointHelper used to install the links
   *                   between core nodes and aggregator nodes
   *
   * \param aggregatorEdgeNodeHelper PointToPointHelper used to install the links
   *                       between aggregator nodes and edge nodes
   */
   PointToPointFatTreeHelper (uint32_t nCore,
                              uint32_t nAggregator,
                              uint32_t nEdgeNode,
                              PointToPointHelper coreAggregatorHelper,
                              PointToPointHelper aggregatorEdgeNodeHelper);

  ~PointToPointFatTreeHelper ();

public:

  /**
   * \returns pointer to the i'th core node
   * \param i node number
   */
  Ptr<Node> GetCore (uint32_t i) const;
  
  /**
   * \returns pointer to the i'th aggregator node
   * \param i node number
   */
  Ptr<Node> GetAggregator (uint32_t i) const;

   /**
   * \returns pointer to the i'th edge node of aggregator node at aggregatorIndex 
   */
  Ptr<Node> GetEdgeNode (uint32_t aggregatorIndex, uint32_t i) const;
  /**
   * \returns NetDevice of i'th core that connects to j'th aggregator node
   * \param coreIndex core node number
   * \param aggregatorIndex aggregator node number
   */
  Ptr<NetDevice> GetCoreToAggregatorNetDevice (uint32_t coreIndex, uint32_t aggregatorIndex) const;
  
  /**
   * \returns NetDevice of i'th aggregator that connects to j'th core node
   * \param aggregatorIndex aggregator node number
   * \param coreIndex core node number
   */
  Ptr<NetDevice> GetAggregatorToCoreNetDevice (uint32_t aggregatorIndex, uint32_t coreIndex) const;

  /**
   * \returns NetDevice of i'th aggregator that connects to j'th edge node
   * \param aggregatorIndex aggregator node number
   * \param edgeIndex edge node number
   */
  Ptr<NetDevice> GetAggregatorToEdgeNetDevice (uint32_t aggregatorIndex, uint32_t edgeIndex) const;

  /**
   * \returns NetDevice of i'th edge that connects to j'th aggregator node
   * \param edgeIndex edge node number
   * \param aggregatorIndex aggregator node number
   */
  Ptr<NetDevice> GetEdgeToAggregatorNetDevice (uint32_t edgeIndex, uint32_t aggregatorNodeIndex) const;

  /**
   * \returns an Ipv4Address of the i'th core node connected with j'th aggregator node
   * \param coreIndex core node number
   * \param aggregatorIndex aggregator node number
   */
  Ipv4Address GetCoreToAggregatorIpv4Address (uint32_t coreIndex, uint32_t aggregatorIndex) const;

  /**
   * \returns an Ipv4Address of the i'th aggregator node connected with j'th code node
   * \param aggregatorIndex aggregator node number
   * \param coreIndex core node number
   */
  Ipv4Address GetAggregatorToCoreIpv4Address (uint32_t aggregatorNodeIndex, uint32_t coreIndex) const;

  /**
   * \returns an Ipv4Address of the i'th aggregator node connected with j'th edge node
   * \param aggregatorIndex aggregator node number
   * \param edgeIndex edge node number
   */
  Ipv4Address GetAggregatorToEdgeIpv4Address (uint32_t aggregatorIndex, uint32_t edgeIndex) const;

  /**
   * \returns an Ipv4Address of the i'th edge node connected with j'th aggregator node
   * \param edgeIndex edge node number
   * \param aggregatorIndex aggregator node number
   */
  Ipv4Address GetEdgeToAggregatorIpv4Address (uint32_t edgeIndex, uint32_t aggregatorNodeIndex) const;

  /**
   * \returns the number of core nodes in the network
   */
  uint32_t CoreCount () const;

  /**
   * \returns the number of aggregator nodes in the network
   */
  uint32_t AggregatorCount () const;

  /**
   * \returns the number of edge nodes connected with an aggregator nodes in the network
   */
  uint32_t AggregatorEdgeNodeCount () const;
  
  /**
   * \param stack an InternetStackHelper which is used to install
   *        stack on every node in the Fat-tree
   */
  void    InstallStack (InternetStackHelper stack);

  /**
   *
   * \param coreToAggregatorIp Ipv4AddressHelper to assign Ipv4 addresses to the
   *                      interfaces between core and aggregator nodes
   *
   * \param aggregatorToEdgeInterfaces Ipv4AddressHelper to assign Ipv4 addresses to the
   *                    interfaces between aggregator and edge nodes
   */
  void      AssignIpv4Addresses (Ipv4AddressHelper coreToAggregatorIp,
                                 Ipv4AddressHelper aggregatorToEdgeIp);
                                 
  NodeContainer                          m_nCore;                           //!< Core nodes
  NodeContainer                          m_nAggregator;                     //!< Aggregate Nodes
  std::vector <NodeContainer>            m_edge;                            //!< Edge nodes
  
  std::vector <NetDeviceContainer>       m_coreToAggregatorDevices;         //!< core-aggregator nodes NetDevice
  std::vector <NetDeviceContainer>       m_aggregatorToCoreDevices;         //!< aggregator-core nodes NetDevice
  std::vector <NetDeviceContainer>       m_aggregatorToEdgeDevices;         //!< aggregator-edge nodes NetDevice
  std::vector <NetDeviceContainer>       m_edgeToAggregatorDevices;         //!< edge-aggregator nodes NetDevice
  
  std::vector <Ipv4InterfaceContainer>   m_coreInterfaces;                  //!< core-aggregator interfaces (IPv4)
  std::vector <Ipv4InterfaceContainer>   m_aggregatorToCoreInterfaces;      //!< aggregator-core interfaces (IPv4)
  std::vector <Ipv4InterfaceContainer>   m_aggregatorToEdgeInterfaces;      //!< aggregator-edge interfaces (IPv4)
  std::vector <Ipv4InterfaceContainer>   m_edgeInterfaces;                  //!< edge-aggregator interfaces (IPv4)

};


} // namespace ns3

#endif /* POINT_TO_POINT_FAT_TREE_H */
