//============================================================================
// Name        : Lp_1.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class Job
{
	int id;
	string name;
	int burst_t;
	int arrival_t;
	int waiting_t;
	int completion_t;
	int turnAround_t;
	int response_t;
	int priority;

private:
	Job()
	{
		id = 0;
		name = "";
		burst_t = 0;
		arrival_t = 0;
		waiting_t = 0;
		completion_t = 0;
		turnAround_t = 0;
		response_t = 0;
		priority = 0;
	}

	void createJob()
	{
		cout << "Enter job id :";
		cin >> id;
		cout << "Enter job name :";
		cin >> name;
		cout << "Enter arrival time :";
		cin >> arrival_t;
		cout << "Enter the burst time :";
		cin >> burst_t;
	}
	friend class Scheduler;
};

class Scheduler
{
	Job *jobs;
	int np;

public:
	Scheduler()
	{
		//		cout<<"Enter the number of jobs :";
		//		int x;
		//		cin>>x;
		//		np=x;
		//		jobs = new Job[np];
		//		for(int i=0;i<np;i++){
		//			cout<<"Enter details of "<<i+1<<" job"<<endl;
		//			jobs[i].createJob();
		//			cout<<endl;
		//		}
		np = 6;
		jobs = new Job[np];
		jobs[0].id = 1;
		jobs[0].name = "P1";
		jobs[0].arrival_t = 0;
		jobs[0].burst_t = 7;

		jobs[1].id = 2;
		jobs[1].name = "P2";
		jobs[1].arrival_t = 1;
		jobs[1].burst_t = 4;

		jobs[2].id = 3;
		jobs[2].name = "P3";
		jobs[2].arrival_t = 2;
		jobs[2].burst_t = 15;

		jobs[3].id = 4;
		jobs[3].name = "P4";
		jobs[3].arrival_t = 3;
		jobs[3].burst_t = 11;

		jobs[4].id = 5;
		jobs[4].name = "P5";
		jobs[4].arrival_t = 4;
		jobs[4].burst_t = 20;

		jobs[5].id = 6;
		jobs[5].name = "P6";
		jobs[5].arrival_t = 4;
		jobs[5].burst_t = 9;
	}

	void showJobs(Job arr[], int x)
	{
		cout << "Name\tAT\tBT\tCT\tTAT\tWT" << endl;
		for (int i = 0; i < x; i++)
		{
			cout << arr[i].name << "\t" << arr[i].arrival_t << "\t" << arr[i].burst_t << "\t" << arr[i].completion_t << "\t" << arr[i].turnAround_t << "\t" << arr[i].waiting_t << endl;
		}
	}

	void showAvg()
	{
		float avgW = 0;
		float avgTA = 0;
		for (int i = 0; i < np; i++)
		{
			avgW += jobs[i].waiting_t;
			avgTA += jobs[i].turnAround_t;
		}
		avgW = avgW / np;
		avgTA = avgTA / np;
		cout << "Average Waiting time :" << avgW << endl;
		cout << "Average Turn Around time :" << avgTA << endl;
	}

	void FCFS()
	{
		Job v[np];
		for (int i = 0; i < np; i++)
		{
			v[i] = jobs[i];
		}
		for (int i = 0; i < np - 1; i++)
		{
			int min = i;
			for (int j = i + 1; j < np; j++)
			{
				if (v[min].arrival_t > v[j].arrival_t)
				{
					min = j;
				}
			}
			Job b = v[min];
			v[min] = v[i];
			v[i] = b;
		}
		int ctime = 0;
		Job *gantt = new Job[np];
		for (int i = 0; i < np; i++)
		{
			gantt[i] = v[i];
			ctime += gantt[i].burst_t;
			gantt[i].completion_t = ctime;
			gantt[i].turnAround_t = gantt[i].completion_t - gantt[i].arrival_t;
			gantt[i].waiting_t = gantt[i].turnAround_t - gantt[i].burst_t;
		}
		showJobs(gantt, np);
		int avgW = 0;
		int avgTA = 0;
		for (int i = 0; i < np; i++)
		{
			avgW += gantt[i].waiting_t;
			avgTA += gantt[i].turnAround_t;
		}
		avgW = avgW / np;
		avgTA = avgTA / np;
		cout << "Average Waiting time :" << avgW << endl;
		cout << "Average Turn Around time :" << avgTA << endl;
	}

	void SJF()
	{
		Job *v = new Job[np];
		int totalTime = 0;
		for (int i = 0; i < np; i++)
		{
			v[i] = jobs[i];
			totalTime += v[i].burst_t;
		}
		sort(v, v + np, [](const Job &lhs, const Job &rhs)
			 { return lhs.arrival_t < rhs.arrival_t; });

		vector<string> gantt;
		cout << "Total time is :" << totalTime << endl;
		vector<Job> readyQ;
		int tp = 0;
		int timeStamp = 0;
		while (timeStamp < totalTime)
		{

			while (tp < np && v[tp].arrival_t <= timeStamp)
			{
				readyQ.push_back(v[tp]);
				tp++;
			}

			sort(readyQ.begin(), readyQ.end(), [](const Job &lhs, const Job &rhs)
				 { return lhs.burst_t < rhs.burst_t; });

			//			for(int i=0;i<readyQ.size();i++){
			//				cout<<readyQ[i].name<<"|"<<readyQ[i].burst_t<<" ";
			//			}
			if (readyQ.size() > 0)
			{
				gantt.push_back(readyQ[0].name);
				readyQ[0].burst_t--;
				if (readyQ[0].burst_t == 0)
				{
					for (int i = 0; i < np; i++)
					{
						if (jobs[i].name == readyQ[0].name)
						{
							jobs[i].completion_t = timeStamp + 1;
							jobs[i].turnAround_t = jobs[i].completion_t - jobs[i].arrival_t;
							jobs[i].waiting_t = jobs[i].turnAround_t - jobs[i].burst_t;
						}
					}
					readyQ.erase(readyQ.begin());
				}
			}
			timeStamp++;
		}

		cout << "ans is :" << endl;
		for (int i = 0; i < gantt.size(); i++)
		{
			cout << gantt[i] << " ";
		}
		cout << endl;
		showJobs(jobs, np);
		showAvg();
	}

	void RR()
	{
		cout << "Enter the time interval :";
		int interval;
		cin >> interval;

		Job *v = new Job[np];
		int totalTime = 0;
		for (int i = 0; i < np; i++)
		{
			v[i] = jobs[i];
			totalTime += v[i].burst_t;
		}
		sort(v, v + np, [](const Job &lhs, const Job &rhs)
			 { return lhs.arrival_t < rhs.arrival_t; });

		vector<string> gantt;
		cout << "Total time is :" << totalTime << endl;
		queue<Job> readyQ;
		int tp = 0;
		int timeStamp = 0;
		Job added_job;
		added_job.burst_t = 0;
		int addedburst = 0;
		while (timeStamp < totalTime)
		{

			while (tp < np && v[tp].arrival_t <= timeStamp)
			{
				readyQ.push(v[tp]);
				tp++;
			}
			if (added_job.burst_t > 0)
			{
				readyQ.push(added_job);
			}

			if (readyQ.size() > 0)
			{
				added_job = readyQ.front();
				readyQ.pop();
				gantt.push_back(added_job.name);
				if (added_job.burst_t > interval)
				{
					added_job.burst_t = added_job.burst_t - interval;
					addedburst = interval;
				}
				else
				{
					addedburst = added_job.burst_t;
					added_job.burst_t = 0;
				}

				if (added_job.burst_t == 0)
				{

					for (int i = 0; i < np; i++)
					{
						if (jobs[i].name == added_job.name)
						{
							jobs[i].completion_t = timeStamp + addedburst;
							jobs[i].turnAround_t = jobs[i].completion_t - jobs[i].arrival_t;
							jobs[i].waiting_t = jobs[i].turnAround_t - jobs[i].burst_t;
						}
					}
				}
			}
			timeStamp += addedburst;
		}

		cout << "ans is :" << endl;
		for (int i = 0; i < gantt.size(); i++)
		{
			cout << gantt[i] << " ";
		}
		cout << endl;
		showJobs(jobs, np);
		showAvg();
	}

	void Priority()
	{
		Job *v = new Job[np];
		int totalTime = 0;
		for (int i = 0; i < np; i++)
		{
			v[i] = jobs[i];
			totalTime += v[i].burst_t;
			cout << "Enter priority of " << v[i].name << " job :";
			cin >> v[i].priority;
		}

		sort(v, v + np, [](const Job &lhs, const Job &rhs)
			 { return lhs.arrival_t <= rhs.arrival_t; });
		int aj = 0;
		int timeStamp = 0;
		vector<Job> readyQ;
		Job *gantt = new Job[np];
		int ja = 0;

		while (timeStamp < totalTime)
		{
			while (aj < np && v[aj].arrival_t <= timeStamp)
			{
				readyQ.push_back(v[aj]);
				aj++;
			}

			sort(readyQ.begin(), readyQ.end(), [](const Job &lhs, const Job &rhs)
				 { return lhs.priority < rhs.priority; });

			for (int i = 0; i < readyQ.size(); i++)
			{
				cout << readyQ[i].name << "|" << readyQ[i].priority << " ";
			}
			cout << endl;

			if (readyQ.size() > 0)
			{
				gantt[ja] = readyQ[0];
				timeStamp += gantt[ja].burst_t;
				gantt[ja].completion_t = timeStamp;
				gantt[ja].turnAround_t = gantt[ja].completion_t - gantt[ja].arrival_t;
				gantt[ja].waiting_t = gantt[ja].turnAround_t - gantt[ja].burst_t;
				ja++;
				readyQ.erase(readyQ.begin());
			}
		}
		// cout<<"Out of while";
		showJobs(gantt, np);

		float avgW = 0;
		float avgTA = 0;
		for (int i = 0; i < np; i++)
		{
			avgW += gantt[i].waiting_t;
			avgTA += gantt[i].turnAround_t;
		}
		avgW = avgW / np;
		avgTA = avgTA / np;
		cout << "Average Waiting time :" << avgW << endl;
		cout << "Average Turn Around time :" << avgTA << endl;
	}
};

int main()
{
	Scheduler s1;
	s1.RR();
}
