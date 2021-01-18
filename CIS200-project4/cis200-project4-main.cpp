#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
#include"Job.h"
#include"PriorityQ.h"
//#include "Processor.h"

/*
Author: Muhaddatha Abdulghani
Creation date: 4/11/19
Modification date: 4/21/19
File: Project4-MuhaddathaA.cpp
Purpose: The purpose of this file is to implement the priority with
ranndomly generated jobs
*/
//Global variables
int jobNumberA = 0, jobNumberB = 0, jobNumberC = 0, jobNumberD = 0,
totalJobNumber = 0;
int processorIdleTime = 0, jobsInterrupted = 0;
bool jobComplete = false, jobInterrupted = false, moveOntoNextJob = true;
int numberOfJobsCompleted = 0, generatorTime = 0, timesQueueSizeReported =
0, combinedQueueSize = 0, timeUnitsProcessorRan = 0;
float combinedTimeInQueue = 0, averageQuesize = 0;
priorityQ queue;
std::fstream logFile;
//prototype
job jobGenerator();
class Processor {
private:
	bool processorIdle = true;
public:
	Processor() {
	}
	/*
	Author: Muhaddatha Abdulghani
	precondition: a job is passed to the function to be processed
	postcondition: none
	description: A ob is processed fully or partially depending on the
	arrival of a high priority job
	*/
	void process(job &jobToProcess, job nextDJob, int& universalTimes,
		bool &jobInterruptedBoolian, bool &JobIsComplete) {
		if (nextDJob.jobType == 'D' && nextDJob.arrivalTime ==
			universalTimes && jobToProcess.jobType != 'D') {
			logFile << universalTimes << ") " << "Arrival job D : Overall job " << nextDJob.jobNumber << ", Job D " <<
				nextDJob.jobTypeNumber <<
				", Processing time " <<
				nextDJob.processingTime << "; Interrupted Job " << jobToProcess.jobType <<
				" arrival time: "
				<< jobToProcess.arrivalTime << ",Interrupted jobs number : " << jobsInterrupted << ", New high priority job goes into processor, "
				<< " Job " << jobToProcess.jobType << "with arrival time : " << jobToProcess.arrivalTime << ", job type number "
				<< jobToProcess.jobTypeNumber << " added to queue with processing time "
				<< jobToProcess.processingTime << ";"
				<< std::endl;
			if (debugging) {
				std::cout << "Current time: " <<
					universalTimes << std::endl;
				std::cout << "Job interrupted: " <<
					jobToProcess.jobType << " " << jobToProcess.arrivalTime << " " <<
					"Processing time left: " << jobToProcess.processingTime << std::endl;
			}
			jobInterruptedBoolian = true;
			JobIsComplete = false;
			return;
		}
		if (jobToProcess.processingTime == 0) {
			combinedTimeInQueue = (universalTimes -
				jobToProcess.arrivalTime) + combinedTimeInQueue;
			logFile << universalTimes << ") Completed job" << jobToProcess.jobType << " arrival time : " << jobToProcess.arrivalTime
				<< ", Over all job number: " << jobToProcess.jobNumber <<
				", job type number: " <<
				jobToProcess.jobTypeNumber << ", processing time: " <<
				jobToProcess.processingTime << std::endl;
			JobIsComplete = true;
			jobInterruptedBoolian = false;//try
			processorIdle = true;
			//add to wait time
			//IdleTime = true;
			return;
		}
		processorIdle = false;
		logFile << universalTimes << ") Processing job " <<
			jobToProcess.jobType << "(" << jobToProcess.arrivalTime << ") Overall job number " << jobToProcess.jobNumber << " with job number " <<
			jobToProcess.jobTypeNumber << " processing time: "
			<< jobToProcess.processingTime << std::endl;
		jobToProcess.processingTime--;
		if (debugging) {
			std::cout << "Current time: " <<
				universalTimes << " Processing job: " << jobToProcess.jobType << " " <<
				jobToProcess.arrivalTime << " " << jobToProcess.processingTime <<
				std::endl;
		}
		universalTimes++;
		//jobWaiTime = jobWaiTime + (jobToProcess.arrivalTime - universalTime);
	}
	/*
	Author: Muhaddatha Abdulghani
	precondition: none
	postcondition: return of a boolian
	description: This method checks if the processor is idle or not
	*/
	bool isProcessorIdle() const {
		return processorIdle;
	}
};
int main() {
	logFile.open("logFile.txt");
	Processor processor1;
	Processor processor2;
	std::fstream eventFile;
	eventFile.open("eventFile.txt");
	srand(time(0));
	int universalTime = 0;
	for (int i = 0; i < 500; i++) {
		job newJob = jobGenerator();
		//newJob.arrivalTime = newJob.arrivalTime;
		if (newJob.jobType != 'E') {
			queue.enqueue(newJob);
		}
	}
	//writing to file
	logFile << "Prefill stage - Queue size: " << totalJobNumber <<
		std::endl;
	logFile << "Prefill stage - Number of job A arrived: " << jobNumberA
		<< std::endl;
	logFile << "Prefill stage - Number of job B arrived: " << jobNumberB
		<< std::endl;
	logFile << "Prefill stage - Number of job C arrived: " << jobNumberC
		<< std::endl;
	logFile << "Prefill stage - Number of job D arrived: " << jobNumberD
		<< std::endl << std::endl;
	std::cout << "Pre fill stage (500 units)" << std::endl;
	std::cout << "Prefill stage - Queue size: " << totalJobNumber <<
		std::endl;
	std::cout << "Prefill stage - Number of job A arrived: " <<
		jobNumberA << std::endl;
	std::cout << "Prefill stage - Number of job B arrived: " <<
		jobNumberB << std::endl;
	std::cout << "Prefill stage - Number of job C arrived: " <<
		jobNumberC << std::endl;
	std::cout << "Prefill stage - Number of job D arrived: " <<
		jobNumberD << std::endl << std::endl;
	//queue.print();
	std::cout << "Queuesize is reported every 101 time unit " <<
		std::endl;
	job jobToProcess; //= queue.dequeue();
	// universalTime = 0;
	int maxQueueSize = queue.getQueueSize();
	while (universalTime < 9500) {// && !queue.isEmpty()) {
		if (universalTime % 101 == 0) {
			std::cout << "Queue size at time " <<
				universalTime << ": " << queue.getQueueSize() << std::endl;
			combinedQueueSize = combinedQueueSize +
				queue.getQueueSize();
			//std::cout << "Queue size reported: " << queue.getQueueSize() << std::endl;//std::cout << "combined queueSize: " <<combinedQueueSize << std::endl;
			timesQueueSizeReported++;
			if (queue.getQueueSize() > maxQueueSize) {
				//std::cout << "Max queue size: " <<
				maxQueueSize;
				maxQueueSize = queue.getQueueSize();
			}
		}
		job arrivingJob = jobGenerator();
		if (debugging) {
			std::cout << "Job arrived #" <<
				arrivingJob.jobNumber << " :" << arrivingJob.jobType << " " <<
				arrivingJob.arrivalTime << " " << arrivingJob.processingTime << std::endl;
		}
		if (arrivingJob.jobType != 'E') {
			//arrivingJob.arrivalTime =
			arrivingJob.arrivalTime + universalTime;
			//std::cout << "New job arrived at time " << universalTime << " job " << arrivingJob.jobType << " overall job number "<< arrivingJob.jobNumber << ", job type number " <<arrivingJob.jobTypeNumber << ", with processing time: "
			//<< arrivingJob.processingTime << "entered queue." << std::endl;
				queue.enqueue(arrivingJob);
		}
		if (queue.peekNextDJob().jobType == 'D' &&
			queue.peekNextDJob().arrivalTime == universalTime) {
			queue.moveHighPriorityToFront();
			if (debugging) {
				std::cout << "Moved high priority job to front of queue at time " << universalTime << std::endl;
			}
		}
		if (moveOntoNextJob) {
			jobToProcess = queue.dequeue();
			moveOntoNextJob = false;
		}
		if (jobToProcess.arrivalTime <= universalTime) {
			if (jobToProcess.jobType == 'E') {
				std::cout << "Borke while loop" <<
					std::endl;
				break;
			}
			processor1.process(jobToProcess,
				queue.peek(), universalTime, jobInterrupted, jobComplete);
			if (jobInterrupted == true) {
				if (debugging) {
					std::cout << "Job interrupted!" << std::endl;
				}
				queue.putBackInQueue(jobToProcess);
				//puts the low priority job back in the queue
					jobsInterrupted++;
				jobInterrupted = false;
				jobToProcess = queue.dequeue();
				while (jobToProcess.processingTime > 0)
				{
					processor1.process(jobToProcess, queue.peek(), universalTime,
						jobInterrupted, jobComplete);
					if
						(queue.peekNextDJob().jobType == 'D' && queue.peekNextDJob().arrivalTime
							== universalTime) {
						queue.moveHighPriorityToFront();
						if (debugging) {
							std::cout
								<< "Moved high priority job to front of queue at time " << universalTime
								<< std::endl;
						}
					}
					universalTime++;
				}
				moveOntoNextJob = true;
				numberOfJobsCompleted++;
				//jobToProcess = queue.dequeue();
				//moveOntoNextJob = true;
			}
			else if (jobComplete == true) {
				numberOfJobsCompleted++;
				jobComplete = false;
				moveOntoNextJob = true;
			}
		}
		if (processor1.isProcessorIdle() &&
			jobToProcess.arrivalTime > universalTime) {
			if (queue.isEmpty()) {
				logFile << universalTime << ") Queue is empty - Processor idle" << std::endl;
			}
			else {
				logFile << universalTime << ") Processor is idle" << std::endl;
			}
			if (debugging) {
				std::cout << "Processor idle at time: "
					<< universalTime << std::endl;
			}
			processorIdleTime++;
			//moveOntoNextJob = true;//changed from false to true
				universalTime++;
		}
		else if (processor1.isProcessorIdle() == false) {
			//std::cout << "Processor busy - ";
		}
		//std::cout << "Current time: " << universalTime <<std::endl;
		//universalTime++;
	}
	//logFile.close();
	//logFile.open("processorLogFile.txt", std::ios::app);
	timeUnitsProcessorRan = universalTime - processorIdleTime;
	//logFile.close();
	//logFile.open("logFile.txt", std::ios::app);
	logFile << std::endl << std::endl;
	logFile << "--------------------Metrics-----------------" <<
		std::endl;
	logFile << "Average queue size: " << (combinedQueueSize /
		timesQueueSizeReported) << std::endl;
	logFile << "Average time in queue: " << (combinedTimeInQueue /
		totalJobNumber) << std::endl;
	logFile << "Processor idle time: " << processorIdleTime <<
		std::endl;
	logFile << "Totoal number of jobs arrived: " << jobNumberA +
		jobNumberB + jobNumberC + jobNumberD << std::endl;
	logFile << "Total job As arrived: " << jobNumberA << std::endl;
	logFile << "Total job Bs arrived: " << jobNumberB << std::endl;
	logFile << "Total job Cs arrived: " << jobNumberC << std::endl;
	logFile << "Total job Ds arrived: " << jobNumberD << std::endl;
	logFile << "Maximum jobs in queue: " << maxQueueSize << std::endl;
	logFile << "Number of jobs interrupted: " << jobsInterrupted <<
		std::endl;
	logFile << "Number of jobs completed: " << numberOfJobsCompleted <<
		std::endl;
	logFile << "Total time units processor spent processing: " <<
		timeUnitsProcessorRan << std::endl;
	//logFile << "Queue size: " << queue.getQueueSize() << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "--------------------Metrics-----------------" <<
		std::endl;
	std::cout << "Average queue size: " << (combinedQueueSize /
		timesQueueSizeReported) << std::endl;
	std::cout << "Average time in queue: " << (combinedTimeInQueue /
		totalJobNumber) << std::endl;
	std::cout << "Processor idle time: " << processorIdleTime <<
		std::endl;
	std::cout << "Totoal number of jobs arrived: " << jobNumberA +
		jobNumberB + jobNumberC + jobNumberD << std::endl;
	std::cout << "Total job As arrived: " << jobNumberA << std::endl;
	std::cout << "Total job Bs arrived: " << jobNumberB << std::endl;
	std::cout << "Total job Cs arrived: " << jobNumberC << std::endl;
	std::cout << "Total job Ds arrived: " << jobNumberD << std::endl;
	std::cout << "Maximum jobs in queue: " << maxQueueSize << std::endl;
	std::cout << "Number of jobs interrupted: " << jobsInterrupted <<
		std::endl;
	std::cout << "Number of jobs completed: " << numberOfJobsCompleted
		<< std::endl;
	std::cout << "Total time units processor spent processing: " <<
		timeUnitsProcessorRan << std::endl;
	queue.~priorityQ();
	//logFile.clear();
	logFile.close();
	system("pause");
	return 0;
}
/*
Author: Muhaddatha Abdulghani
precondition: none
postcondition: return of a job
description: This function creates a random job and returns it
*/
job jobGenerator() {
	char jobTypes[5] = { 'A', 'B', 'C', 'D', 'E' };
	int randomJobTypeIndex = rand() % 5;
	job randomJob;
	if (jobTypes[randomJobTypeIndex] == 'A') {
		jobNumberA++;
		totalJobNumber++;
		randomJob = { 'A', generatorTime + (4 + rand() % 3) , (1
		+ (rand() % 3)), jobNumberA, totalJobNumber };
		//clockTimeA =+ randomJob.arrivalTime;
	}
	else if (jobTypes[randomJobTypeIndex] == 'B') {
		jobNumberB++;
		totalJobNumber++;
		randomJob = { 'B', generatorTime + (9 + rand() % 2), (6 +
		(rand() % 4)), jobNumberB, totalJobNumber };
		//clockTimeB =+ randomJob.arrivalTime;
	}
	else if (jobTypes[randomJobTypeIndex] == 'C') {
		jobNumberC++;
		totalJobNumber++;
		randomJob = { 'C', generatorTime + (24 + rand() % 2), (11
		+ (rand() % 4)), jobNumberC, totalJobNumber };
		//clockTimeC =+ randomJob.arrivalTime;
	}
	else if (jobTypes[randomJobTypeIndex] == 'D') {
		jobNumberD++;
		totalJobNumber++;
		randomJob = { 'D', generatorTime + (25 + rand() % 10), (8
		+ (rand() % 4)), jobNumberD, totalJobNumber };
		// clockTimeD = +randomJob.arrivalTime;
	}
	else {
		randomJob = { 'E', 0, 0, 0, 0 };
		//std::cout << "Empty job created." << std::endl;
	}
	if (randomJob.jobType != 'E') {
		generatorTime = generatorTime + (rand() % 15);
	}
	return randomJob;
}