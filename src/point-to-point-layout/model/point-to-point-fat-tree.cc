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
#include "ns3/point-to-point-fat-tree.h"
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
    m_nCore.Create(nCore);
    m_nAggregator.Create(nAggregator);

    for(uint32_t i = 0; i < nAggregator; i++)
    {
        NodeContainer edgeNodes;
        NetDeviceContainer aggregatorDevices, edgeDevices;
        edgeNodes.Create (nEdgeNode);
        for(uint32_t j = 0; j < nEdgeNode; j++)
        {
          NetDeviceContainer c1 = aggregatorEdgeNodeHelper.Install (m_nAggregator.Get (i),
                                                                       edgeNodes.Get (j));
          aggregatorDevices.Add (c1.Get (0));
          edgeDevices.Add (c1.Get (1));
        }
        m_aggregatorToEdgeDevices.push_back (aggregatorDevices);
        m_edgeToAggregatorDevices.push_back (edgeDevices);
        m_edge.push_back(edgeNodes);
    }
    
    for(uint32_t i = 0; i < nCore; i++)
    {
      NetDeviceContainer coreDevices;
      m_coreToAggregatorDevices.push_back (coreDevices);
    }
    
    for(uint32_t i = 0; i < nAggregator; i++)
    {
      NetDeviceContainer aggregatorDevices;
      m_aggregatorToCoreDevices.push_back (aggregatorDevices);
    }
    
    for(uint32_t i = 0; i < nCore; i++)
    {
      for(uint32_t j = 0; j < nAggregator; j++)
      {
        NetDeviceContainer c1 = coreAggregatorHelper.Install (m_nCore.Get(i), m_nAggregator.Get(j));
        m_coreToAggregatorDevices[i].Add (c1.Get (0));
        m_aggregatorToCoreDevices[j].Add (c1.Get (1));
      }
    }
  }
  
  PointToPointFatTreeHelper::~PointToPointFatTreeHelper()
  {
  }
  
void
PointToPointFatTreeHelper::InstallStack (InternetStackHelper stack)
{
  stack.Install (m_nCore);
  stack.Install (m_nAggregator);

  for (uint32_t i = 0; i < m_edge.size (); ++i)
    {
      NodeContainer edgeI = m_edge[i];
      stack.Install (edgeI);
    }
}

void PointToPointFatTreeHelper::AssignIpv4Addresses (Ipv4AddressHelper coreToAggregatorIp,
                                                     Ipv4AddressHelper aggregatorToEdgeIp)
{
  for(uint32_t i = 0; i < AggregatorCount (); i++)
  {
    Ipv4InterfaceContainer aggregatorToEdgeInterfaces, edgeInterfaces;
    for(uint32_t j = 0; j < AggregatorEdgeNodeCount (); j++)
    {
      NetDeviceContainer ndc;
      ndc.Add (m_aggregatorToEdgeDevices[i].Get (i));
      ndc.Add (m_edgeToAggregatorDevices[i].Get (j));
      Ipv4InterfaceContainer ifc = aggregatorToEdgeIp.Assign (ndc);
      aggregatorToEdgeInterfaces.Add (ifc.Get (0));
      edgeInterfaces.Add (ifc.Get (0));
      aggregatorToEdgeIp.NewNetwork ();
    }
    m_aggregatorToEdgeInterfaces.push_back (aggregatorToEdgeInterfaces);
    m_edgeInterfaces.push_back (edgeInterfaces);
  }
  
  for(uint32_t i = 0; i < CoreCount (); i++)
  {
    Ipv4InterfaceContainer coreInterfaces;
    m_coreInterfaces.push_back (coreInterfaces);
  }
  
  for(uint32_t i = 0; i < AggregatorCount (); i++)
  {
    Ipv4InterfaceContainer aggregatorToCoreInterfaces;
    m_aggregatorToCoreInterfaces.push_back (aggregatorToCoreInterfaces);
  }
  
  for(uint32_t i = 0; i < CoreCount (); i++)
  {
    for(uint32_t j = 0; j < AggregatorCount (); j++)
    {
      NetDeviceContainer ndc;
      ndc.Add (m_coreToAggregatorDevices[i].Get (j));
      ndc.Add (m_aggregatorToCoreDevices[j].Get (i));
      Ipv4InterfaceContainer ifc = aggregatorToEdgeIp.Assign (ndc);
      m_coreInterfaces[i].Add (ifc.Get (0));
      m_aggregatorToCoreInterfaces[j].Add (ifc.Get(1));
      coreToAggregatorIp.NewNetwork ();
    }
  }
  
  
  
}

  Ptr<Node> PointToPointFatTreeHelper::GetCore (uint32_t i) const
  {
    return m_nCore.Get (i);
  }
  
  Ptr<Node> PointToPointFatTreeHelper::GetAggregator (uint32_t i) const
  {
    return m_nAggregator.Get (i);
  }
  
  Ptr<Node> PointToPointFatTreeHelper::GetEdgeNode (uint32_t aggregatorNodeIndex, uint32_t i) const
  {
    return m_edge[aggregatorNodeIndex].Get (i);
  }
  
  Ptr<NetDevice> PointToPointFatTreeHelper::GetCoreToAggregatorNetDevice (uint32_t coreIndex, uint32_t aggregatorIndex) const
  {
    return m_coreToAggregatorDevices[coreIndex].Get (aggregatorIndex);
  }
  
  Ptr<NetDevice> PointToPointFatTreeHelper::GetAggregatorToCoreNetDevice (uint32_t aggregatorIndex, uint32_t coreIndex) const
  {
    return m_aggregatorToCoreDevices[aggregatorIndex].Get (coreIndex);
  }
  
  Ptr<NetDevice> PointToPointFatTreeHelper::GetAggregatorToEdgeNetDevice (uint32_t aggregatorIndex, uint32_t edgeIndex) const
  {
    return m_aggregatorToEdgeDevices[aggregatorIndex].Get (edgeIndex);
  }
  
  Ptr<NetDevice> PointToPointFatTreeHelper::GetEdgeToAggregatorNetDevice (uint32_t edgeIndex, uint32_t aggregatorIndex) const
  {
    return m_edgeToAggregatorDevices[edgeIndex].Get (aggregatorIndex);
  }
  
  Ipv4Address PointToPointFatTreeHelper::GetCoreToAggregatorIpv4Address (uint32_t coreIndex, uint32_t aggregatorIndex) const
  {
    return m_coreInterfaces[coreIndex].GetAddress(aggregatorIndex);
  }
  
  Ipv4Address PointToPointFatTreeHelper::GetAggregatorToCoreIpv4Address (uint32_t aggregatorIndex, uint32_t coreIndex) const
  {
    return m_aggregatorToCoreInterfaces[aggregatorIndex].GetAddress(coreIndex);
  }
  
  Ipv4Address PointToPointFatTreeHelper::GetAggregatorToEdgeIpv4Address (uint32_t aggregatorIndex, uint32_t edgeIndex) const
  {
    return m_aggregatorToCoreInterfaces[aggregatorIndex].GetAddress(edgeIndex);
  }
  
  Ipv4Address PointToPointFatTreeHelper::GetEdgeToAggregatorIpv4Address (uint32_t coreIndex, uint32_t aggregatorIndex) const
  {
    return m_coreInterfaces[coreIndex].GetAddress(aggregatorIndex);
  }
  
  uint32_t  PointToPointFatTreeHelper::CoreCount () const
  {
    return m_nCore.GetN ();
  }
  
  uint32_t  PointToPointFatTreeHelper::AggregatorCount () const
  {
    return m_nAggregator.GetN ();
  }
  
  uint32_t PointToPointFatTreeHelper::AggregatorEdgeNodeCount () const
  {
    return m_edge[0].GetN ();
  }
} // namespace ns3
