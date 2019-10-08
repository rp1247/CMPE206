
DocViewer
Page
of 2
Pages
/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011, 2012 Centre Tecnologic de Telecomunicacions de Catalunya 
(CTTC)
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
 *  Author: Mahima Agumbe Suresh <mahima.agumbesuresh@sjsu.edu>
 * 
 */
#include "ns3/log.h"
#include "ns3/double.h"
#include "ns3/enum.h"
#include "ns3/string.h"
#include "ns3/pointer.h"
#include "ns3/mobility-model.h"
#include <cmath>
#include "lognormal-shadowing-loss-model.h"
namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("LogNormalPropagationLossModel");
// ------------------------------------------------------------------------- //
NS_OBJECT_ENSURE_REGISTERED (LogNormalPropagationLossModel);
// TODO: Add attributes required for this model. 
// Use the LogDistancePropagationLossModel and RandomPropagationLossModel as 
//reference
// Two sample attributes are provided below for reference
TypeId
LogNormalPropagationLossModel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::LogNormalPropagationLossModel")
    .SetParent<PropagationLossModel> ()
    .SetGroupName ("Propagation")
    .AddConstructor<LogNormalPropagationLossModel> ()
    .AddAttribute ("Exponent",
                   "The exponent of the Path Loss propagation model",
                   DoubleValue (3.0),
                   MakeDoubleAccessor (&LogNormalPropagationLossModel::m_exponent),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("ReferenceDistance",
                   "The distance at which the reference loss is calculated (m)",
                   DoubleValue (1.0),
                   MakeDoubleAccessor 
(&LogNormalPropagationLossModel::m_referenceDistance),
                   MakeDoubleChecker<double> ())
    .AddAttribute("Distance",								//Added distance (d) attribute
			"Distance (d)",
			DoubleValue(4.0),
			MakeDoubleAccessor (&LogNormalPropagationLossModel::m_distance),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("ReferenceLoss",							// Added reference loss (L0) attribute
                   "Reference Loss L0",
                   DoubleValue (1.0),
                   MakeDoubleAccessor 
(&LogNormalPropagationLossModel::m_referenceLoss),
                   MakeDoubleChecker<double> ())
     .AddAttribute ("GuassianRandomVariable",							// Added Guassian random variable attribute
                   "Guassian Random Variable (X)",
                   DoubleValue (4.0),
                   MakeDoubleAccessor 
(&LogNormalPropagationLossModel::m_guassian),
                   MakeDoubleChecker<double> ())
  ;
  return tid;
}
LogNormalPropagationLossModel::LogNormalPropagationLossModel ()
{
}
void
LogNormalPropagationLossModel::SetPathLossExponent (double n)
{
  m_exponent = n;
}
void
LogNormalPropagationLossModel::SetReference (double referenceDistance, double 
referenceLoss)
{
  m_referenceDistance = referenceDistance;
  m_referenceLoss = referenceLoss;
}
double
LogNormalPropagationLossModel::GetPathLossExponent (void) const
{
  return m_exponent;
}
double
LogNormalPropagationLossModel::SetDistance (double distance)                  //Setter for distance(d), Co-ordinate of Guassian random variable (N)
{
  m_distance=distance;
}
double
LogNormalPropagationLossModel::DoCalcRxPower (double txPowerDbm,
                                                Ptr<MobilityModel> a,
                                                Ptr<MobilityModel> b) const
{
// TODO: Write your implementation of the RX power with this model
    txPowerDbm = m_referenceLoss + (10 * m_exponent * log10 (m_distance/m_referenceDistance)) + m_guassian;     // LogDistancePropagationLossModel Formula
    return txPowerDbm;
}
int64_t
LogNormalPropagationLossModel::DoAssignStreams (int64_t stream)
{
  m_randVariable->SetStream (stream);
  return 1;
}
} // namespace ns3
Annotations

