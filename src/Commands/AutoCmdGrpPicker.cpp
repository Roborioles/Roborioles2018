// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "AutoCmdGrp.h"
#include "AutoDrive.h"
#include "AutoRotate.h"
#include "ElevatorFloor.h"
#include "ElevatorHighScale.h"
#include "ElevatorScale.h"
#include "ElevatorSwitch.h"
#include "IntakeOpenCmd.h"
#include "IntakeDrive.h"
#include "WaitCmd.h"
#include "PickeyUppy.h"
#include "AutoCmdGrpPicker.h"
#include "AutoElevatorExec.h"
#include "../Subsystems/IntakeSub.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutoCmdGrpPicker::AutoCmdGrpPicker(int selectionNum): CommandGroup() {
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

	//LEFT POSITION AUTONOMOUSES
	if(selectionNum == 1) {
		// Go for switch - left position - no override
		// (1,0) or (1,3)
		printf("Left robot, scoring left switch\n");
		AddSequential(new ElevatorSwitch());
		AddParallel(new AutoElevatorExec());
		AddSequential(new AutoDrive(13));
		AddSequential(new AutoRotate(-90, 5));
		AddSequential(new IntakeOpenCmd(true));
		AddSequential(new AutoDrive(3));
		AddSequential(new WaitCmd(0));//clears out all these autodrives
		AddSequential(new AutoDrive(-2));
		AddSequential(new ElevatorFloor());
		AddParallel(new AutoElevatorExec());
		AddSequential(new AutoRotate(90, 3));
		AddSequential(new AutoDrive(7));
		AddSequential(new AutoRotate(-120, 5));
		AddParallel(new AutoDrive(3.5));
		AddSequential(new PickeyUppy());
		if(Robot::elevator->CubeDistance() < 9) {
			AddSequential(new AutoDrive(-2));
			AddSequential(new ElevatorSwitch());
			AddParallel(new AutoElevatorExec());
			AddSequential(new AutoDrive(4));
		}
	} else if (selectionNum == 2) {
		// Go for scale - left position - all overrides may be applicable
		// (1,any)
		printf("Left robot, scoring left scale\n");
		AddSequential(new ElevatorSwitch());
		AddParallel(new AutoElevatorExec());
		AddSequential(new AutoDrive(23));
		AddSequential(new ElevatorHighScale());
		AddSequential(new AutoElevatorExec());
		AddSequential(new AutoRotate(-50, 5));
		AddSequential(new IntakeOpenCmd(true));
		AddSequential(new AutoDrive(2));
		AddSequential(new WaitCmd(0));
		AddSequential(new AutoDrive(-3));
		AddSequential(new ElevatorFloor());
		AddParallel(new AutoElevatorExec());
		AddSequential(new AutoRotate(-100, 5));
		AddParallel(new AutoDrive(7));
		AddSequential(new PickeyUppy());
		if(Robot::elevator->CubeDistance() < 9) {
			AddSequential(new AutoDrive(-2));
			AddSequential(new ElevatorSwitch());
			AddParallel(new AutoElevatorExec());
			AddSequential(new AutoDrive(3));
		}
	} else if (selectionNum == 3) {
		// SCORES
		// Scale is on the right, left position. only applicable for override 2 and 3
		// (1, 2) or (1, 3)
		printf("Left robot, scoring right scale\n");
		//down to alleyway
		AddSequential(new AutoDrive(18.25));
		AddSequential(new AutoRotate(-87, 4));
		//down the alleyway
		//AddSequential(new WaitCmd(1)); //might be meaningless if autorotate works
		AddSequential(new ElevatorSwitch());
		AddParallel(new AutoElevatorExec());
		AddSequential(new AutoDrive(18));
		AddSequential(new ElevatorHighScale());
		AddParallel(new AutoElevatorExec());
		AddSequential(new AutoRotate(90, 5));
		AddSequential(new AutoDrive(4));
		AddSequential(new IntakeOpenCmd(true));
		AddSequential(new WaitCmd(2));
		AddSequential(new AutoDrive(-3));
		//AddSequential(new ElevatorFloor());
		//AddSequential(new AutoElevatorExec()); not needed - default command takes over at the end
		//no time for pickeyuppy lol, already at time
	} else if (selectionNum == 4) {
		printf("Left robot, halting right");
		AddSequential(new AutoDrive(18.5));
		AddSequential(new AutoRotate(-90, 3));
		//AddSequential(new WaitCmd(1)); //likely meaningless if autorotate works
		AddSequential(new ElevatorSwitch());
		AddParallel(new AutoElevatorExec());
		AddSequential(new AutoDrive(11)); //stops in alleyway. better stay that way (in autonomous)
	}

	//RIGHT POSITION AUTONOMOUSES
	else if (selectionNum == 5) {
		printf("Right robot, scoring right switch\n");
		AddSequential(new ElevatorSwitch());
		AddParallel(new AutoElevatorExec());
		AddSequential(new AutoDrive(13));
		AddSequential(new AutoRotate(90, 5));
		AddSequential(new IntakeOpenCmd(true));
		AddSequential(new AutoDrive(3));
		AddSequential(new AutoDrive(-2));
		AddSequential(new ElevatorFloor());
		AddSequential(new AutoElevatorExec());
		AddSequential(new AutoRotate(-90, 4));
		AddSequential(new AutoDrive(6));
		AddSequential(new AutoRotate(120, 4));
		AddParallel(new AutoDrive(6));
		AddSequential(new PickeyUppy());
		if(Robot::elevator->CubeDistance() < 9) { //places on switch, please test + debug all of this lmao
			AddSequential(new AutoDrive(-2));
			AddSequential(new ElevatorSwitch());
			AddParallel(new AutoElevatorExec());
			AddSequential(new AutoDrive(3));
		}
	} else if (selectionNum == 6) {
		printf("Right robot, scoring right scale\n");
		AddSequential(new ElevatorSwitch());
		AddParallel(new AutoElevatorExec());
		AddSequential(new AutoDrive(23));
		AddSequential(new ElevatorHighScale());
		AddSequential(new AutoElevatorExec());
		//AddSequential(new WaitCmd(2)); //meaningless if autoelevatorexec works
		AddSequential(new AutoRotate(45, 5));
		//AddSequential(new WaitCmd(1)); //useless if rotate is okay
		AddSequential(new IntakeOpenCmd(true));
		AddSequential(new AutoDrive(2));
		AddSequential(new AutoDrive(-2.5));
		AddSequential(new ElevatorFloor());
		AddParallel(new AutoElevatorExec());
		AddSequential(new AutoRotate(105, 5));
		AddParallel(new AutoDrive(7));
		AddSequential(new PickeyUppy());
		if(Robot::elevator->CubeDistance() < 9) { //places on switch, please test + debug all of this lmao
			AddSequential(new AutoDrive(-2));
			AddSequential(new ElevatorSwitch());
			AddParallel(new AutoElevatorExec());
			AddSequential(new AutoDrive(3));
		}
	} else if (selectionNum == 7) {
		printf("Right robot, scoring left scale\n");
		AddSequential(new AutoDrive(18.25));
		//going shy, expecting lurch
		AddSequential(new AutoRotate(87, 4));
		//down the alleyway
		AddSequential(new ElevatorSwitch());
		AddParallel(new AutoElevatorExec());
		AddSequential(new AutoDrive(18));
		AddSequential(new ElevatorHighScale());
		AddParallel(new AutoElevatorExec());
		AddSequential(new AutoRotate(-90, 5));
		//up on scale, closing in and releasing
		AddSequential(new AutoDrive(4));
		AddSequential(new IntakeOpenCmd(true));
		AddSequential(new WaitCmd(2));
		AddSequential(new AutoDrive(-3));
		//AddSequential(new ElevatorFloor());
		//AddSequential(new AutoElevatorExec());
	} else if (selectionNum == 8) {
		printf("Right robot, halting left\n");
		//down to alleyway
		AddSequential(new AutoDrive(18.25));
		AddSequential(new AutoRotate(90, 5));
		//down the alleyway
		AddSequential(new ElevatorSwitch());
		AddParallel(new AutoElevatorExec());
		AddSequential(new AutoDrive(11)); //stops in alley
		}

	//MIDDLE AUTONOMOUSES
	else if (selectionNum == 9) {
		printf("Middle, going for left switch\n");
		AddSequential(new AutoDrive(4));
		AddSequential(new AutoRotate(90, 5));
		AddSequential(new AutoDrive(9));
		AddSequential(new AutoRotate(-90, 5));
		AddSequential(new ElevatorSwitch());
		AddParallel(new AutoElevatorExec());
		AddSequential(new AutoDrive(5.3));
		AddSequential(new IntakeOpenCmd(true));
		AddSequential(new WaitCmd(1));
		AddSequential(new ElevatorFloor());
		AddSequential(new AutoDrive(-3));
		AddSequential(new AutoElevatorExec());
	} else if (selectionNum == 10) {
		printf("Middle, going for right switch\n");
		AddSequential(new ElevatorSwitch());
		AddParallel(new AutoElevatorExec());
		AddSequential(new AutoDrive(9));
		AddSequential(new IntakeOpenCmd(true));
		AddSequential(new WaitCmd(2));
		AddSequential(new AutoDrive(-3));
		AddSequential(new ElevatorFloor());
		AddSequential(new AutoElevatorExec());
	}



              // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=COMMAND_DECLARATIONS
                      // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=COMMAND_DECLARATIONS
 }
