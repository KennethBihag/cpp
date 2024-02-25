#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::sort;
using std::vector;

static bool meetingComp(const vector<int> &a, const vector<int> &b);
static void printMeetings(const vector<vector<int>> &meetings);
static void printWhoKnows(const vector<int> &knowers);
static void spread(vector<vector<int>> &meetings, vector<int> &knowers);
static void spread(vector<int> &knowers, const int newPerson);
static bool exists(const vector<int> &vec, const int val);
static bool exists(const vector<int> &vec, const vector<int> &val, int *firstMatch);

vector<int> findAllPeople(int n, vector<vector<int>> &meetings, int firstPerson)
{
	vector<int> knowers{0, firstPerson};
	sort(meetings.begin(), meetings.end(), meetingComp);
	vector<vector<int>> meetingsSameTime;
	for (auto i : meetings)
	{
		static int t = i[2];
	UPDATE_MEETINGS_SAME_T:
		if (t == i[2])
		{
			meetingsSameTime.push_back(i);
		}
		else
		{
			spread(meetingsSameTime, knowers);
			meetingsSameTime.clear();
			t = i[2];
			goto UPDATE_MEETINGS_SAME_T;
		}
	}
	spread(meetingsSameTime, knowers);
	printWhoKnows(knowers);
	return knowers;
}

static bool meetingComp(const vector<int> &a, const vector<int> &b)
{
	return a[2] < b[2];
}

void printMeetings(const vector<vector<int>> &meetings)
{
	for (auto i : meetings)
	{
		cout << '\t';
		cout << i[0] << " meets with " << i[1] << " on " << i[2] << '\n';
	}
}

static void printWhoKnows(const vector<int> &knowers)
{
	cout << "Those who know:";
	for (auto i : knowers)
		cout << ' ' << i;
	cout << '\n';
}

static void spread(vector<vector<int>> &meetings, vector<int> &knowers)
{
REPEAT:
	bool done = true;
	vector<vector<int>> tmpMeetings(meetings);
	for (auto &i : tmpMeetings)
	{
		std::vector<int> pair(i.begin(), i.end() - 1);
		int intrsctn = INT32_MAX;
		if (exists(pair, knowers, &intrsctn))
		{
			if (pair[0] != intrsctn)
			{
				if (!exists(knowers, pair[0]))
					knowers.push_back(pair[0]);
			}
			else
			{
				if (!exists(knowers, pair[1]))
					knowers.push_back(pair[1]);
			}
			done = false;
			auto newEnd = std::remove(meetings.begin(), meetings.end(), i);
			meetings.erase(newEnd);
		}
	}
	if (!done)
		goto REPEAT;
	return;
}

static void spread(vector<int> &knowers, const int newPerson)
{
}

static bool exists(const vector<int> &vec, const int val)
{
	vector<int>::const_iterator ptr =
		std::find(vec.begin(), vec.end(), val);
	return ptr != vec.end();
}

static bool exists(const vector<int> &vec, const vector<int> &val, int *firstMatch)
{
	for (auto i : val)
	{
		if (exists(vec, i))
		{
			*firstMatch = i;
			return true;
		}
	}
	return false;
}