#include "laneManager.h"

laneManager::laneManager(){
	laneOccupied.fill(false);
	ChangeLanes.fill(false);
}

bool laneManager::IsLineFree(int Line) const{
	return !laneOccupied[Line];
}

void laneManager::SetLineOccupied(int Line){
	laneOccupied[Line] = true;
}

void laneManager::FreeLine(int Line){
	laneOccupied[Line] = false;
}

int laneManager::GetFreeLine() const {
	for (int i = 0; i < 3; i++) {
		if (!laneOccupied[i]) {
			return i;
		}
	}
	return -1;
}

bool laneManager::IsCanChangeLine(int Line) const{
	return !ChangeLanes[Line];
}

void laneManager::SetLineNonChangable(int Line){
	ChangeLanes[Line] = true;
}

void laneManager::SetLineChangable(int Line){
	ChangeLanes[Line] = false;
}


void laneManager::Reset(){
	laneOccupied.fill(false);
	ChangeLanes.fill(false);
}
