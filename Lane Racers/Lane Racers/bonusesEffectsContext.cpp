#include "bonusesEffectsContext.h"
bonusesEffectsContext::bonusesEffectsContext(){

}

void bonusesEffectsContext::update(){	// ����������
	if (SlowDown && SlowDownTimer.getElapsedTime().asSeconds() >= SlowDownDur) {
		SlowDownMultiplier = 1.f;
		SlowDown = false;
	}

	// �������� �����
	if (DoubleScore && DoubleScoreTimer.getElapsedTime().asSeconds() >= DoubleScoreDur)
		DoubleScore = false;

	// ���
	if (hasShield && ShieldTimer.getElapsedTime().asSeconds() >= ShieldDur) {
		hasShield = false;
		ShieldJustEnded = true;
	}
}

vector<bonusesEffectsContext::ActiveBonusInfo> bonusesEffectsContext::GetActiveBonuses() const {
	vector<ActiveBonusInfo> ActiveBonuses;
	if (IsSlowDownActive())
		ActiveBonuses.push_back(ActiveBonusInfo{ BonusType::SlowBoost, SlowDownDur - GetSlowDownTimer(), SlowDownDur });
	if (IsShieldActive())
		ActiveBonuses.push_back(ActiveBonusInfo{ BonusType::ShieldBoost, ShieldDur - GetShieldTimer(), ShieldDur });
	if (IsDoubleScoreActive())
		ActiveBonuses.push_back(ActiveBonusInfo{ BonusType::ScoreBoost, DoubleScoreDur - GetDoubleScoreTimer(), DoubleScoreDur });

	return ActiveBonuses;
}

void bonusesEffectsContext::Reset() {
	// ���������� 
	SlowDown = false;
	SlowDownMultiplier = 1.f;

	// ���
	ShieldJustEnded = false;
	hasShield = false;

	// �������� �����
	DoubleScore = false;
}

// ����������
void bonusesEffectsContext::SetSlowDown(){
	SlowDownMultiplier = 0.4f;
	SlowDown = true;
	SlowDownTimer.restart();
}

bool bonusesEffectsContext::IsSlowDownActive() const{
	return SlowDown;
}

float bonusesEffectsContext::GetSlowDownMultiplier() const{
	return SlowDownMultiplier;
}

float bonusesEffectsContext::GetSlowDownTimer() const{
	return SlowDownTimer.getElapsedTime().asSeconds();
}

// ���
void bonusesEffectsContext::SetShield(){
	ShieldTimer.restart();
	hasShield = true;
}

bool bonusesEffectsContext::IsShieldActive() const{
	return hasShield;
}

bool bonusesEffectsContext::IsShieldJustEnded() const{
	return ShieldJustEnded;
}

void bonusesEffectsContext::ResetShieldJustEnded() {
	ShieldJustEnded = false;
}

float bonusesEffectsContext::GetShieldTimer() const{
	return ShieldTimer.getElapsedTime().asSeconds();
}

// �������� �����
void bonusesEffectsContext::SetDoubleScore(){
	DoubleScoreTimer.restart();
	DoubleScore = true;
}

bool bonusesEffectsContext::IsDoubleScoreActive() const{
	return DoubleScore;
}

float bonusesEffectsContext::GetDoubleScoreTimer() const{
	return DoubleScoreTimer.getElapsedTime().asSeconds();
}

