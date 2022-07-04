#include "UI.h"

UI::UI()
{
	mode = -1;
}

void UI::readInput(RoverLists& RL, LinkedQueue<Event*>& EL)
{
	int mounRover_No, polRover_No, emRover_No;
	int *mounRover_Sp = NULL, *polRover_Sp = NULL, * emRover_Sp = NULL;
	int missionsBeforeChkup;
	int mounRover_Chkup, polRover_Chkup, emRover_Chkup;
	int autoPromLimit;
	int eventsNo;
	char eventType, missionType;
	int eventDay, ID, missionLocation, daysToComplete, significance;
	ifstream input;
	input.open("Input and output files/Input.txt");
	int lineNo = 0;
	if (input.is_open())
	{
		while (!input.eof())
		{
			if (lineNo == 0) //no. of rovers of each type
			{
				input >> mounRover_No >> polRover_No >> emRover_No;
			}
			else if (lineNo == 1) //rover speeds of each M rover
			{
				mounRover_Sp = new int[mounRover_No];
				for (int i = 0; i < mounRover_No; i++)
				{
					input >> mounRover_Sp[i];
				}
			}
			else if (lineNo == 2) //rover speeds of each P rover
			{
				polRover_Sp = new int[polRover_No];
				for (int i = 0; i < polRover_No; i++)
				{
					input >> polRover_Sp[i];
				}
			}
			else if (lineNo == 3) //rover speeds of each E rover
			{
				emRover_Sp = new int[emRover_No];
				for (int i = 0; i < emRover_No; i++)
				{
					input >> emRover_Sp[i];
				}
			}
			else if (lineNo == 4) //no. of missions before checkup and the checkup durations
			{
				input >> missionsBeforeChkup >> mounRover_Chkup >> polRover_Chkup >> emRover_Chkup;
			}
			else if (lineNo == 5) //auto promotion limit
			{
				input >> autoPromLimit;
			}
			else if (lineNo == 6) //no. of events in this file
			{
				input >> eventsNo;
			}
			else //All the coming are events
			{
				input >> eventType;
				if (eventType == 'F')
				{
					input >> missionType >> eventDay >> ID >> missionLocation >> daysToComplete >> significance;

					Event* E = new FormulationEvent(eventDay, ID, missionType, missionLocation, daysToComplete, significance, autoPromLimit);
					EL.enqueue(E);
				}
				else if (eventType == 'X')
				{
					input >> eventDay >> ID;

					Event* E = new CancelEvent(eventDay, ID);
					EL.enqueue(E);
				}
				else if (eventType == 'P')
				{
					input >> eventDay >> ID;

					Event* E = new PromoteEvent(eventDay, ID);
					EL.enqueue(E);
				}
			}
			lineNo++;
		}
		input.close();
	}
	//////////////////////////////////////////// Create rover objects /////////////////////////////////////////
	int Rover_ID = 1; //random ID is assigned to rovers
	for (int i = 0; i < mounRover_No; i++)
	{
		Rover* mounRover = new Rover('M', Rover_ID++, mounRover_Chkup, mounRover_Sp[i], missionsBeforeChkup);
		RL.addtoRoverList(mounRover);
	}
	for (int i = 0; i < polRover_No; i++)
	{
		Rover* polRover = new Rover('P', Rover_ID++, polRover_Chkup, polRover_Sp[i], missionsBeforeChkup);
		RL.addtoRoverList(polRover);
	}
	for (int i = 0; i < emRover_No; i++)
	{
		Rover* emRover = new Rover('E', Rover_ID++, emRover_Chkup, emRover_Sp[i], missionsBeforeChkup);
		RL.addtoRoverList(emRover);
	}
	delete[] mounRover_Sp; //deallocations
	delete[] polRover_Sp;
	delete[] emRover_Sp;
}

int UI::getMode()
{
	cout << "Select Program Mode: \n";
	cout << "[1] Interactive Mode\n";
	cout << "[2] Step-By-Step Mode\n";
	cout << "[3] Silent Mode\n";
	cin >> mode;
	while (mode != 1 && mode != 2 && mode != 3)
	{
		cout << "Please select a valid choice\n";
		cin >> mode;
	}
	cin.ignore(); //to ignore the "enter" key pressed after the input, if we dont ignore it, 
                  //it will be read in interactive mode as if we pressed enter to display the next day
	return mode;
}

void UI::consoleOutput(MissionsList& ML, RoverLists& RL, long curDay)
{
	string enter; //to read the "enter" key pressed by the user in interactive mode
	Pair <Missions*, int> tempVar;//needed to dequeue from emergency and in excetution lists (priority lists)
	Missions* tempVar2;//needed to dequeue from mountanuous and polar mission list
	Pair <Rover*, int> tempRover; //needed to dequeue from  rover lists
	if (mode == 1 || mode == 2)
	{
		bool first = true; //to indicate whether this is the first output in the sentence or not, to place the "," correctly
		cout << "Current Day: " << curDay << endl;

		////////////////////////////////////////   waiting missions   ///////////////////////////////////////////
		cout << ML.getNumOf_WaitingMissions() << " Waiting Missions: ";
		PriorityLinkedQueue<Missions*> EMwaiting(ML.getWaitingEmergencyList());
		LinkedQueue<Missions*> MMwaiting(ML.getWaitingMountainuousList());
		LinkedQueue<Missions*> PMwaiting(ML.getWaitingPolarList());

		//Emergency
		first = true;
		cout << "[";
		while (EMwaiting.dequeue(tempVar))
		{
			if (first)
			{
				cout << tempVar.first->getID();
				first = false;
			}
			else
			{
				cout << ", " << tempVar.first->getID();
			}
		}
		cout << "] ";

		//Polar
		first = true;
		cout << "(";
		while (PMwaiting.dequeue(tempVar2))
		{
			if (first)
			{
				cout << tempVar2->getID();
				first = false;
			}
			else
			{
				cout << ", " << tempVar2->getID();
			}
		}
		cout << ") ";

		//Mountainuous
		first = true;
		cout << "{";
		while (MMwaiting.dequeue(tempVar2))
		{
			if (first)
			{
				cout << tempVar2->getID();
				first = false;
			}
			else
			{
				cout << ", " << tempVar2->getID();
			}
		}
		cout << "}\n";
	
		cout << "---------------------------------------------------------------\n";
		//////////////////////////////////   in execution missions/rovers   /////////////////////////////////////
		PriorityLinkedQueue<Missions*> inExecution(ML.getInExecutionList());
		PriorityLinkedQueue<Missions*> inExecutionTemp;
		cout << ML.getNumOf_InExecutionMissions() << " In-Execution Missions/Rovers: ";
		//Emergency
		first = true;
		cout << "[";
		while (inExecution.dequeue(tempVar))
		{
			if (tempVar.first->getType() == 'E')
			{
				if (first)
				{
					cout << tempVar.first->getID() << "/" << tempVar.first->getHelpingRover()->getID();
					first = false;
				}
				else
				{
					cout << ", " << tempVar.first->getID() << "/" << tempVar.first->getHelpingRover()->getID();
				}
			}
			inExecutionTemp.enqueue(tempVar);
		}
		cout << "] ";

		//Polar
		first = true;
		cout << "(";
		while (inExecutionTemp.dequeue(tempVar))
		{
			if (tempVar.first->getType() == 'P')
			{
				if (first)
				{
					cout << tempVar.first->getID() << "/" << tempVar.first->getHelpingRover()->getID();
					first = false;
				}
				else
				{
					cout << ", " << tempVar.first->getID() << "/" << tempVar.first->getHelpingRover()->getID();
				}
			}
			inExecution.enqueue(tempVar);
		}
		cout << ") ";

		//Mountainous
		first = true;
		cout << "{";
		while (inExecution.dequeue(tempVar))
		{
			if (tempVar.first->getType() == 'M')
			{
				if (first)
				{
					cout << tempVar.first->getID() << "/" << tempVar.first->getHelpingRover()->getID();
					first = false;
				}
				else
				{
					cout << ", " << tempVar.first->getID() << "/" << tempVar.first->getHelpingRover()->getID();
				}
			}
			//inExecutionTemp.enqueue(tempVar);
		}
		cout << "}\n";
		
		cout << "---------------------------------------------------------------\n";
		////////////////////////////////////////   available rovers   ///////////////////////////////////////////
		cout << RL.getNumOf_WaitingRovers() << " Available Rovers: ";
		PriorityLinkedQueue<Rover*> ERavailable(RL.getAvailableEmergencyList());
		PriorityLinkedQueue<Rover*> MRavailable(RL.getAvailableMountanuousList());
		PriorityLinkedQueue<Rover*> PRavailable(RL.getAvailablePolarList());
		//Emergency
		first = true;
		cout << "[";
		while (ERavailable.dequeue(tempRover))
		{
			if (first)
			{
				cout << tempRover.first->getID();
				first = false;
			}
			else
			{
				cout << ", " << tempRover.first->getID();
			}
		}
		cout << "] ";

		//Polar
		first = true;
		cout << "(";
		while (PRavailable.dequeue(tempRover))
		{
			if (first)
			{
				cout << tempRover.first->getID();
				first = false;
			}
			else
			{
				cout << ", " << tempRover.first->getID();
			}
		}
		cout << ") ";

		//Mountainuous
		first = true;
		cout << "{";
		while (MRavailable.dequeue(tempRover))
		{
			if (first)
			{
				cout << tempRover.first->getID();
				first = false;
			}
			else
			{
				cout << ", " << tempRover.first->getID();
			}
		}
		cout << "}\n";
		cout << "---------------------------------------------------------------\n";
		////////////////////////////////////////   in checkup rovers   //////////////////////////////////////////
		cout << RL.getNumOf_InCheckUpRovers() << " In-Checkup Rovers: ";
		PriorityLinkedQueue<Rover*> chkup(RL.getCheckupList());
		PriorityLinkedQueue<Rover*> chkupTemp;
		//Emergency
		first = true;
		cout << "[";
		while (chkup.dequeue(tempRover))
		{
			if (tempRover.first->getType() == 'E')
			{
				if (first)
				{
					cout << tempRover.first->getID();
					first = false;
				}
				else
				{
					cout << ", " << tempRover.first->getID();
				}
			}
			chkupTemp.enqueue(tempRover);
		}
		cout << "] ";

		//Polar
		first = true;
		cout << "(";
		while (chkupTemp.dequeue(tempRover))
		{
			if (tempRover.first->getType() == 'P')
			{
				if (first)
				{
					cout << tempRover.first->getID();
					first = false;
				}			
				else
				{
					cout << ", " << tempRover.first->getID();
				}
			}
			chkup.enqueue(tempRover);
		}
		cout << ") ";

		//Mountainuous
		first = true;
		cout << "{";
		while (chkup.dequeue(tempRover))
		{
			if (tempRover.first->getType() == 'M')
			{
				if (first)
				{
					cout << tempRover.first->getID();
					first = false;
				}
				else
				{
					cout << ", " << tempRover.first->getID();
				}
			}
			//chkupTemp.enqueue(tempRover);
		}
		cout << "}\n";
		cout << "---------------------------------------------------------------\n";
		////////////////////////////////////////   completed mission   //////////////////////////////////////////
		LinkedQueue<Missions*> Completed;
		LinkedQueue<Missions*> CompletedTemp(ML.getCompletedMissions());
		int CompOnThisDay = 0;
		while (CompletedTemp.dequeue(tempVar2))
		{
			if (tempVar2->getCD() == curDay)
			{
				CompOnThisDay++;
			}
			Completed.enqueue(tempVar2);
		}
		cout << CompOnThisDay << " Completed Missions: ";

		//Emergency
		first = true;
		cout << "[";
		while (Completed.dequeue(tempVar2))
		{
			if (tempVar2->getCD() == curDay)
			{
				if (tempVar2->getType() == 'E')
				{
					if (first)
					{
						cout << tempVar2->getID();
						first = false;
					}
					else
					{
						cout << ", " << tempVar2->getID();
					}
				}
			}
			CompletedTemp.enqueue(tempVar2);
		}
		cout << "] ";

		//Polar
		first = true;
		cout << "(";
		while (CompletedTemp.dequeue(tempVar2))
		{
			if (tempVar2->getCD() == curDay)
			{
				if (tempVar2->getType() == 'P')
				{
					if (first)
					{
						cout << tempVar2->getID();
						first = false;
					}
					else
					{
						cout << ", " << tempVar2->getID();
					}
				}
			}
			Completed.enqueue(tempVar2);
		}
		cout << ") ";

		//Mountainuous
		first = true;
		cout << "{";
		while (Completed.dequeue(tempVar2))
		{
			if (tempVar2->getCD() == curDay)
			{
				if (tempVar2->getType() == 'M')
				{
					if (first)
					{
						cout << tempVar2->getID();
						first = false;
					}
					else
					{
						cout << ", " << tempVar2->getID();
					}
				}
			}
			//CompletedTemp.enqueue(tempVar2);
		}
		cout << "}\n";


		cout << "\n---------------------------------------------------------------\n";
		cout << "---------------------------------------------------------------\n\n";

		////////////////////   waiting for the user to press enter to display the next day   ////////////////////
		if (mode == 1)
		{
			do {
				cout << "Press Enter To Continue" << endl;
				getline(cin, enter);
			} while (enter.length() != 0);
		}
		///////////////////////////////////////   waiting for 1 second   ////////////////////////////////////////
		else if (mode == 2)
		{
			chrono::seconds dura(1);
			this_thread::sleep_for(dura);
		}
		
	}
	else if (mode == 3)
	{
		cout << "Silent Mode\n";
		cout << "Simulation Starts...\n";
		cout << "Simulation ends, Output file created\n";
	}
}
