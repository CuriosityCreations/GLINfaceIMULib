#include "RTIMUGravityCal.h"
#include "RTIMUSettings.h"

using namespace std;

RTIMUGravityCal::RTIMUGravityCal(){
   reset();

}


void RTIMUGravityCal::reset(){

    m_firsttime = true;
    m_accel = RTVector3();
    m_gravity = RTQuaternion();

}


void RTIMUGravityCal::newIMUData(RTIMU_DATA& data, const RTIMUSettings *settings){

    m_accel = data.accel;
    

}


RTVector3 RTIMUGravityCal::getAccel()
{
   
    RTVector3 accel;

    accel.setX(m_accel.x());
    accel.setY(m_accel.y());
    accel.setZ(m_accel.z());

    return accel;
}


double RTIMUGravityCal::getGsense()
{
   
    RTVector3 gravity = getAccel();

    double G = sqrt(gravity.x()*gravity.x() + gravity.y()*gravity.y() + gravity.z()*gravity.z());

    return G;
}



/*void RTIMUGravityCal::setGravityQuaternion(){
    double G = GetGravity();
    m_gravity.setScalar(0);
    m_gravity.setX(0);
    m_gravity.setY(0);
    m_gravity.setZ(G);
}*/


/*RTVector3 RTIMUGravityCal::getAccelResiduals(){
	RTQuaternion rotatedGravity;
    RTQuaternion fusedConjugate;
    RTQuaternion fusionQPose;
    RTQuaternion qTemp;
    RTVector3 residuals;

    //  do gravity rotation and subtraction
    setGravityQuaternion();

    // create the conjugate of the pose
    fusionQPose = m_fusion->getfusionQPose();
    fusedConjugate = fusionQPose.conjugate();

    // update curent gravity quaternion
    //setGravityQuaternion();

    // now do the rotation - takes two steps with qTemp as the intermediate variable
    qTemp = m_gravity * fusionQPose;
    rotatedGravity = fusedConjugate * qTemp;

	
    // now adjust the measured accel and change the signs to make sense
    residuals.setX(-(m_accel.x() - rotatedGravity.x()));
    residuals.setY(-(m_accel.y() - rotatedGravity.y()));
    residuals.setZ(-(m_accel.z() - rotatedGravity.z()));


    return residuals;
}*/

/*RTVector3 RTIMUGravityCal::WorldAccelResiduals(){
	RTQuaternion worldaccel;
    RTQuaternion qTemp;
    RTQuaternion fusionQPose;
    RTQuaternion Qresiduals;
    RTQuaternion fusedConjugate;
	
    RTVector3 residuals = getAccelResiduals();
    RTVector3 worldresiduals;

	fusionQPose = m_fusion->getfusionQPose();
    fusedConjugate = fusionQPose.conjugate();
	
    Qresiduals.setScalar(0);
    Qresiduals.setX(residuals.x());
    Qresiduals.setY(residuals.y());
    Qresiduals.setZ(residuals.z());

    //--Rotate the accel direction to world
    qTemp = Qresiduals * fusionQPose;
    worldaccel = fusedConjugate * qTemp;
	
    worldresiduals.setX(worldaccel.x());
    worldresiduals.setY(worldaccel.y());
    worldresiduals.setZ(worldaccel.z());

    return worldresiduals;
}*/
