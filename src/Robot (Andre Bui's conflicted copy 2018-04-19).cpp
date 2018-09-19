/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <WPILib.h>
#include <XboxController.h>

class Robot : public frc::IterativeRobot {
public:
		Robot() {
		m_chooser.AddDefault(kAutoNameDefault, kAutoNameDefault);
		m_chooser.AddObject(kAutoNameCustom, kAutoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
		c = new Compressor(0);
		timer.Start();
		stick = new Joystick(0);
		CameraServer::GetInstance()->StartAutomaticCapture();
		HaveGameData = false;

		}


	/*
	 * This autonomous (along with the chooser code above) shows how to
	 * select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString line to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional comparisons to
	 * the
	 * if-else structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as
	 * well.
	 */
//#define DRIVE_STRAIGHT 1

	void AutonomousInit()  {
		timer.Reset();
#ifndef DRIVE_STRAIGHT
		timer.Start();
#endif
	}

	void SwitchLeft(){
		if (timer.Get() < 1.0) {
			myDrive.ArcadeDrive(0.5, 0.0);
		}
		else if (timer.Get() > 1.0 && timer.Get() < 2){
			myDrive.ArcadeDrive(0, -0.45);
		}
	   else if (timer.Get() > 2.0 && timer.Get() < 4){
			myDrive.ArcadeDrive(0.55, 0.0);
		}
	   else if (timer.Get() > 4 && timer.Get() < 5.2){
	   			myDrive.ArcadeDrive(0.0, 0.45);
	   }
	   else if (timer.Get() > 5.4 && timer.Get() < 7){
	   			myDrive.ArcadeDrive(0.55, 0.0);
	   }

		else if (timer.Get() > 7 && timer.Get() < 7.5){
			myDrive.ArcadeDrive(0.0, 0.0);
			hiNoid.Set(frc::DoubleSolenoid::Value::kForward);
		}
		else{
			myDrive.ArcadeDrive(0.0, 0.0);
			hiNoid.Set(frc::DoubleSolenoid::Value::kReverse);
		}
	}

	void SwitchRight(){
		frc::DriverStation::ReportWarning("INSIDE RIGHT SWITCH ");

		if (timer.Get() < 1.0) {
			frc::DriverStation::ReportWarning("HAVE RIGHT SWITCH 1");
					myDrive.ArcadeDrive(0.5, 0.0);
				}
				else if (timer.Get() > 1.0 && timer.Get() < 2){
					frc::DriverStation::ReportWarning("HAVE RIGHT SWITCH 2");
					myDrive.ArcadeDrive(0, 0.5);
				}
			   else if (timer.Get() > 2.0 && timer.Get() < 3.5){
					frc::DriverStation::ReportWarning("HAVE RIGHT SWITCH 3");
					myDrive.ArcadeDrive(0.55, 0.0);
				}
			   else if (timer.Get() > 3.5 && timer.Get() < 4.5){
					frc::DriverStation::ReportWarning("HAVE RIGHT SWITCH 4");
			   			myDrive.ArcadeDrive(0.0, -0.45);
			   }
			   else if (timer.Get() > 4.5 && timer.Get() < 6.5){
					frc::DriverStation::ReportWarning("HAVE RIGHT SWITCH 5");
			   			myDrive.ArcadeDrive(0.55, 0.0);
			   }

				else if (timer.Get() > 6.5 && timer.Get() < 7){
					frc::DriverStation::ReportWarning("HAVE RIGHT SWITCH 6");
					myDrive.ArcadeDrive(0.0, 0.0);
					hiNoid.Set(frc::DoubleSolenoid::Value::kForward);
				}
				else{
					frc::DriverStation::ReportWarning("HAVE RIGHT SWITCH 7");
					myDrive.ArcadeDrive(0.0, 0.0);
					hiNoid.Set(frc::DoubleSolenoid::Value::kReverse);
				}
			}



	void AutonomousPeriodic()  {

#ifndef DRIVE_STRAIGHT

		/*if (timer.Get() < 3.0) {
			myDrive.ArcadeDrive(0.5, 0.);
		} else {
			myDrive.TankDrive(0., 0.);
			if (gameData[0] == 'L') {
			hiNoid.Set(frc::DoubleSolenoid::Value::kForward);
			}
		}
		*/
		gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();

		if (!HaveGameData){
			gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();

				if (gameData.length() > 2){
					HaveGameData = true;
					timer.Start();
				} else {
					return;
				}
		}
			if (gameData[0] == 'L') {
				{
					frc::DriverStation::ReportWarning("HAVE LEFT SWITCH");
				 SwitchLeft();

				}
			}
			else if (gameData[0] == 'R'){
				{
					frc::DriverStation::ReportWarning("HAVE RIGHT SWITCH");
				 SwitchRight();


				}
			}
			else{
				// TODO Move Straight
			}
#else
		if(timer.Get() < 5.0){
			myDrive.ArcadeDrive(0.5, 0.0);
		}
#endif
	}

	void TeleopInit() {}

	void TeleopPeriodic() {
		c->SetClosedLoopControl(true);
		c->Start();
		c->GetPressureSwitchValue();

		if(stick->GetRawButton(2)){

		}
		else{

			{
		if(stick->GetRawButton(1)){
			hiNoid.Set(frc::DoubleSolenoid::Value::kForward);
			}
		else{
			hiNoid.Set(frc::DoubleSolenoid::Value::kReverse);
		}
		if(stick->GetRawButton(5)){
			inTakeL.Set(.5);
			inTakeR.Set(-.5);
		}
		else if(stick->GetRawButton(6)){
			inTakeL.Set(-.5);
			inTakeR.Set(.5);
		}
		else{
			inTakeL.Set(0);
			inTakeR.Set(0);
		}


			}
		myDrive.ArcadeDrive(-stick->GetRawAxis(1), stick->GetRawAxis(4));
		}
	}
	void TestPeriodic() {}

private:
	frc::LiveWindow& m_lw = *LiveWindow::GetInstance();
	frc::SendableChooser<std::string> m_chooser;
	const std::string kAutoNameDefault = "Default";
	const std::string kAutoNameCustom = "My Auto";

	std::string m_autoSelected;
	bool HaveGameData;
	frc::VictorSP fLeft{3};
	frc::VictorSP rLeft{1};
	frc::SpeedControllerGroup left{fLeft, rLeft};

	frc::VictorSP fRight{2};
	frc::VictorSP rRight{0};
	frc::SpeedControllerGroup right{fRight, rRight};
	frc::DifferentialDrive myDrive{left, right};

	frc::Spark inTakeL{4};
	frc::Spark inTakeR{5};

	frc::DoubleSolenoid hiNoid {0, 1};

	frc::Timer timer;

	Compressor *c;

	Joystick *stick;
	std::string gameData;
	cs::UsbCamera StartAutomaticCapture();


};

START_ROBOT_CLASS(Robot)
