#include "JudgementDerived.h"
#include "EnemyBase.h"
//‘Ò‹@”»’èˆ—
bool IdleJudgement::Judgement()
{
	//–³ğŒ‚ÅTRUE
	return true;
}

//’ÇÕ”»’èˆ—
bool PursuitJudgement::Judgement()
{
	//‚à‚µUŒ‚‚³‚ê‚Ä‚¢‚½–‚ª‚ ‚é‚È‚ç
	if (owner->GetOldDamageFlg())return true;
	//õ“G“à‚É‚¢‚ê‚Îtrue‚ğ•Ô‚·
	if (owner->SearchTarget(owner->GetSearchL()))
	{
		return true;
	}
	return false;
}

//UŒ‚”»’èˆ—
bool AttackJudgement::Judgement()
{
	if (owner->SearchTarget(owner->GetAttackL()))
	{
		return true;
	}
	return false;
}
//ƒ_ƒ[ƒW”»’èˆ—
bool DamageJudgement::Judgement()
{
	return owner->GetDamageFlg();
}

//€–S”»’èˆ—
bool DeadJudgement::Judgement()
{
	return owner->GetDeadFlg();
}

//‰ñ“]UŒ‚”»’èˆ—
bool BossRollAttackJudgement::Judgement()
{
	return true;
}