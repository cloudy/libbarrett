/*
 * kinematics_base.h
 *
 *  Created on: Jan 15, 2010
 *      Author: dc
 */

#ifndef BARRETT_SYSTEMS_KINEMATICS_BASE_H_
#define BARRETT_SYSTEMS_KINEMATICS_BASE_H_


#include <libconfig.h++>

#include <barrett/detail/ca_macro.h>
#include <barrett/systems/units.h>
#include <barrett/systems/math/kinematics.h>
#include <barrett/systems/abstract/system.h>


namespace barrett {
namespace systems {


template<size_t DOF>
class KinematicsInput {  // not a System in order to avoid diamond inheritance
// IO
public:	System::Input<const math::Kinematics<DOF>*> kinInput;


public:
	explicit KinematicsInput(System* parentSys) :
		kinInput(parentSys) {}

private:
	DISALLOW_COPY_AND_ASSIGN(KinematicsInput);
};


template<size_t DOF>
class KinematicsBase : public System {
// IO
public:		Input<typename units::JointPositions<DOF>::type> jpInput;
public:		Input<typename units::JointVelocities<DOF>::type> jvInput;
public:		Output<const math::Kinematics<DOF>*> kinOutput;
protected:	typename Output<const math::Kinematics<DOF>*>::Value* kinOutputValue;


public:
	explicit KinematicsBase(const libconfig::Setting& setting) :
		jpInput(this), jvInput(this),
		kinOutput(this, &kinOutputValue), kin(setting) {}
	virtual ~KinematicsBase() {}

protected:
	virtual void operate() {
		kin.eval(jpInput.getValue(), jvInput.getValue());
		kinOutputValue->setValue(&kin);
	}

	math::Kinematics<DOF> kin;

private:
	DISALLOW_COPY_AND_ASSIGN(KinematicsBase);
};


}
}


#endif /* BARRETT_SYSTEMS_KINEMATICS_BASE_H_ */