#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "macrofunctions.h"

#define GRAPH_SIZE 100

typedef struct time_t{
	int begin;
	int end;
} Time;

typedef struct team_t {
	int offset;
	Time time[2 + 1];
} Team;

Team team[100];

int teamSize;
int visited[100];

int toggle(int v) {
	if (v == 1) return 2;
	if (v == 2) return 1;
}

int conflict[100][100];
int conflictSize;

bool visitTime(int t, int offset);

void bipartiteMatch(void)
{
	int i;
	FOR(i, teamSize) {
		team[i].offset = 0;
	}
	int j;
	FOR(i, teamSize) {
		//PRT("Check team %d: \n", i);

		FILL_ARRAY(visited, teamSize, 0);
		/*FOR(j, teamSize) {
		PRT("team %d: offset %d\n", j, team[j].offset);
		}PRTLN;*/
		if (visitTime(i, 1)) {

			team[i].offset = 1;
		}
		else{
			//PRT("\n\nt%d go second check\n", i);
			FILL_ARRAY(visited, teamSize, 0);
			if (visitTime(i, 2)) {

				team[i].offset = 2;
			}
			else {
				team[i].offset = -1;
				PRT("IMPOSIBBLE\n");
				return;
			}
		}
	}

	FOR(i, teamSize) {
		PRT("team %d, offset: %d, ", i, team[i].offset);
		PRT("time: %d - %d\n", team[i].time[team[i].offset].begin, team[i].time[team[i].offset].end);
	}
	PRTLN; PRTLN;

}

bool visitTime(int t, int offset)
{
	if (visited[t] == 1) return false;
	visited[t] = 1;

	int s1 = (t - 1) * 2 + offset;
	int i;
	FORDEC(i, teamSize, 1) {
		if (i == t) continue;
		if (team[i].offset == 0) continue;

		int s2 = (i - 1) * 2 + team[i].offset;
		if (conflict[s1][s2] == 1) {
			//PRT("Conflict: t%d offset%d  - %d offset%d\n", t, offset, i, team[i].offset);
			if (visitTime(i, toggle(team[i].offset))) {
				//PRT("Conflict release: %d offset%d\n",i, toggle(team[i].offset));
				team[i].offset = toggle(team[i].offset);
			}
			else {
				//PRT("t%d offset%d  - %d offset%d false\n", t, offset, i, toggle(team[i].offset));
				return false;
			}
		}
	}
	return true;
}

int isConflict(int t1, int t1Offset, int t2, int t2Offset)
{
	Time *ti, *tj;
	ti = &team[t1].time[t1Offset];
	tj = &team[t2].time[t2Offset];

	if (tj->begin >= ti->begin && tj->begin < ti->end) {
		return true;
	}
	else if (tj->end > ti->begin && tj->end <= ti->end) {
		return true;
	}
	else {
		return false;
	}
}

int main()
{
	freopen("17_bipartiteSchedule_input.txt", "r", stdin);

	int loopCnt, loop;
	scanf("%d", &loopCnt);

	int size;
	int i, j;
	FOR(loop, loopCnt) {
		scanf("%d", &size);
		teamSize = size;
		conflictSize = size * 2;

		FOR(i, teamSize) {
			FOR(j, 2) {
				scanf("%d", &team[i].time[j].begin);
				scanf("%d", &team[i].time[j].end);
			}
		}

		int s, si, sj;
		Time *ti, *tj;
		int tioffset, tjoffset;
		FOR(i, teamSize) {
			FOR(j, teamSize) {
				if (i == j) {
					s = (i - 1) * 2;
					conflict[s + 1][s + 1] = 0;
					conflict[s + 1][s + 2] = 0;
					conflict[s + 2][s + 1] = 0;
					conflict[s + 2][s + 2] = 0;
				}
				else {
					si = (i - 1) * 2;
					sj = (j - 1) * 2;
					conflict[si + 1][sj + 1] = isConflict(i, 1, j, 1);
					conflict[si + 1][sj + 2] = isConflict(i, 1, j, 2);
					conflict[si + 2][sj + 1] = isConflict(i, 2, j, 1);
					conflict[si + 2][sj + 2] = isConflict(i, 2, j, 2);
				}
			}
		}

		PRT("Test #%d. Team size: %d\n", loop, teamSize);
		PRT("time table:\n");
		FOR(i, teamSize) {
			FOR(j, 2) {
				PRTD(team[i].time[j].begin);
				PRTD(team[i].time[j].end);
			}
			PRTLN;
		}PRTLN;
		PRT("time conflict table:\n");
		FOR(i, conflictSize) {
			FOR(j, conflictSize) {
				PRTD(conflict[i][j]);
			}
			PRTLN;
		}PRTLN;
		PRT("scheduling result:\n");
		bipartiteMatch();
		PRTLN; PRTLN;
	}

	_getch();
	return 0;

}

