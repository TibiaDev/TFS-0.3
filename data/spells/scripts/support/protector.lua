local combat = createCombatObject()
setCombatParam(combat, COMBAT_PARAM_EFFECT, CONST_ME_MAGIC_BLUE)
setCombatParam(combat, COMBAT_PARAM_AGGRESSIVE, 0)

local condition = createConditionObject(CONDITION_ATTRIBUTES)
setConditionParam(condition, CONDITION_PARAM_TICKS, 10000)
setConditionParam(condition, CONDITION_PARAM_SKILL_SHIELDPERCENT, 220)
setConditionParam(condition, CONDITION_PARAM_BUFF, TRUE)
setCombatCondition(combat, condition)

local disable = createConditionObject(CONDITION_DISABLE_ATTACK)
setConditionParam(disable, CONDITION_PARAM_TICKS, 10000)

local exhaust = createConditionObject(CONDITION_EXHAUST_COMBAT)
setConditionParam(exhaust, CONDITION_PARAM_TICKS, 10000)

function onCastSpell(cid, var)
	doAddCondition(cid, disable)
	doAddCondition(cid, exhaust)
	return doCombat(cid, combat, var)
end
