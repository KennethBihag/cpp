#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::sort;
using std::vector;

static bool meetingComp(const vector<int> &a, const vector<int> &b)
{
	return a[2] < b[2];
}

static void printMeetings(const vector<vector<int>> &meetings);
static void printWhoKnows(const vector<int> &knowers);
static void spread(vector<int>& knowers, const vector<int>& meeting);
vector<int> findAllPeople(int n, vector<vector<int>> &meetings, int firstPerson)
{
	vector<int> knowers{0, firstPerson};
	sort(meetings.begin(), meetings.end(), meetingComp);
	for (auto i : meetings)
		spread(knowers, i);
	printWhoKnows(knowers);
	return knowers;
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

static void spread(vector<int>& knowers, const vector<int>& meeting)
{
	vector<int>::iterator ptr =
		std::find(knowers.begin(), knowers.end(), meeting[0]);
	if (ptr != knowers.end())
	{
		auto ptr2 = std::find(knowers.begin(),knowers.end(), meeting[1]);
		if(ptr2 != knowers.end())
			return;
		knowers.push_back(meeting[1]);
		return;
	}
	ptr = std::find(knowers.begin(),knowers.end(), meeting[1]);
	if(ptr != knowers.end())
		knowers.push_back(meeting[0]);
	return;
}