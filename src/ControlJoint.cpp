#include <unistd.h>
#include "ControlJoint.h"


const double PI = 3.141592;





ControlJoint::ControlJoint(char address,int channel)
{
	
	

	
	
	mraa_init();
	
	i2c = mraa_i2c_init(channel);
	mraa_i2c_address(i2c,address);


	
	

	
}

ControlJoint::~ControlJoint()
{
	
	mraa_deinit();
}


bool ControlJoint::updateJointPos(std::vector<double> motorPos)
{
	
	

	
	uint8_t *data = new uint8_t[motorPos.size()+1];
	data[0] = motorPos.size();

	for(int i=0;i < motorPos.size();i++)
	{
		double ang = motorPos[i]*180/PI;
		data[i+1] = (int)ang;
		if(data[i+1] > 180)
		{
			data[i+1] = 180;
		}
		else if(data[i+1] < 0)
		{
			data[i+1] = 0;
		}
	}
	mraa_i2c_write(i2c,data,motorPos.size()+1);
	delete data;
	return true;
}





