// -*- C++ -*-
/*!
 * @file  servocontroller.cpp
 * @brief servo motor control component
 * @date $Date$
 *
 * $Id$
 */

#include "servocontroller.h"

// Module specification
// <rtc-template block="module_spec">
static const char* servocontroller_spec[] =
  {
    "implementation_id", "servocontroller",
    "type_name",         "servocontroller",
    "description",       "servo motor control component",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "TES",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    "conf.default.I2C_address", "8",
    "conf.default.I2C_channel", "1",
    "conf.__widget__.I2C_address", "spin",
    "conf.__widget__.I2C_channel", "radio",
    "conf.__constraints__.I2C_address", "0<=x<=255",
    "conf.__constraints__.I2C_channel", "(1,6)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
servocontroller::servocontroller(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inIn("in", m_in),
    m_outOut("out", m_out)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
servocontroller::~servocontroller()
{
}



RTC::ReturnCode_t servocontroller::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in", m_inIn);
  
  // Set OutPort buffer
  addOutPort("out", m_outOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  bindParameter("I2C_address", I2C_address, "8");
  bindParameter("I2C_channel", I2C_channel, "1");

  m_cj = NULL;

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t servocontroller::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t servocontroller::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t servocontroller::onShutdown(RTC::UniqueId ec_id)
{
  if(m_cj)
  	delete m_cj;
  return RTC::RTC_OK;
}



RTC::ReturnCode_t servocontroller::onActivated(RTC::UniqueId ec_id)
{
  if(m_cj == NULL)
  {
	m_cj = new ControlJoint(I2C_address,I2C_channel);
  }

  return RTC::RTC_OK;
}



RTC::ReturnCode_t servocontroller::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



RTC::ReturnCode_t servocontroller::onExecute(RTC::UniqueId ec_id)
{
  
  
  if(m_inIn.isNew())
  {
	m_inIn.read();
	std::vector<double> ang;
	for(int i=0;i < m_in.data.length();i++)
	{
		ang.push_back(m_in.data[i]);
	}
	m_cj->updateJointPos(ang);
  }
  return RTC::RTC_OK;
}


/*
RTC::ReturnCode_t servocontroller::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t servocontroller::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t servocontroller::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t servocontroller::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t servocontroller::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void servocontrollerInit(RTC::Manager* manager)
  {
    coil::Properties profile(servocontroller_spec);
    manager->registerFactory(profile,
                             RTC::Create<servocontroller>,
                             RTC::Delete<servocontroller>);
  }
  
};


