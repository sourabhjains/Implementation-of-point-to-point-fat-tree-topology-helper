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
 * Author: Sourabh Jain
 *         <jainsourabh679@gmail.com>
 */

// Implement an object to create a Fat-Tree topology.

#include <cmath>
#include <iostream>
#include <sstream>

// ns3 includes
#include "ns3/log.h"
#include "ns3/point-to-point-dumbbell.h"
#include "ns3/constant-position-mobility-model.h"

#include "ns3/node-list.h"
#include "ns3/point-to-point-net-device.h"
#include "ns3/vector.h"
#include "ns3/ipv6-address-generator.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("PointToPointFatTreeHelper");

  PointToPointFatTreeHelper::PointToPointFatTreeHelper (uint32_t nCore,
                               uint32_t nAggregator,
                               uint32_t nEdgeNode,
                               PointToPointHelper coreAggregatorHelper,
                               PointToPointHelper aggregatorEdgeNodeHelper)
  {
    
  }
  
  PointToPointFatTreeHelper::~PointToPointFatTreeHelper()
  {
  }
  
  Ptr<Node> PointToPointFatTreeHelper::GetCore (uint32_t i) const
  {
  
  }
  
  Ptr<Node> PointToPointFatTreeHelper::GetAggregator (uint32_t i) const
  {
  
  }
  
  ptr<Node> PointToPointFatTreeHelper::GetEdgeNode (uint32_t aggregatorNodeIndex, uint32_t i) const
  {
  
  }
  
  Ipv4Address PointToPointFatTreeHelper::GetCoreIpv4Address (uint32_t i) const
  {
  
  }
  
  Ipv4Address PointToPointFatTreeHelper::GetAggregatorIpv4Address (uint32_t i) const
  {
  
  }
  
  Ipv4Address PointToPointFatTreeHelper::GetEdgeNodeIpv4Address (uint32_t aggregatorNodeIndex, uint32_t i) const
  {
  
  }
  
  
  
  


} // namespace ns3
