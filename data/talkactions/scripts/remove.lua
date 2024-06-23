function onSay(cid, words, param)
	local amount = 1
	param = tonumber(param)
	if(param) then
		amount = tonumber(param)
	end

	local tmp = {}
	local toPos = getPlayerLookPos(cid)
	toPos.stackpos = STACKPOS_TOP_MOVEABLE_ITEM_OR_CREATURE
	tmp = getThingFromPos(toPos)
	if(tmp.uid ~= 0) then
		if(isCreature(tmp.uid) == TRUE) then
			doRemoveCreature(tmp.uid)
		else
			doRemoveItem(tmp.uid, amount)
		end

		doSendMagicEffect(toPos, CONST_ME_MAGIC_RED)
		return TRUE
	end

	toPos.stackpos = STACKPOS_TOP_FIELD
	tmp = getThingFromPos(toPos)
	if(tmp.uid ~= 0) then
		doRemoveItem(tmp.uid, amount)
		doSendMagicEffect(toPos, CONST_ME_MAGIC_RED)
		return TRUE
	end

	toPos.stackpos = STACKPOS_TOP_CREATURE
	tmp = getThingFromPos(toPos)
	if(tmp.uid ~= 0) then
		doRemoveCreature(tmp.uid)
		doSendMagicEffect(toPos, CONST_ME_MAGIC_RED)
		return TRUE
	end

	local limit = 1
	if(getPlayerAccess(cid) >= 5) then
		limit = 0
	end

	for i = 5, limit, -1 do
		toPos.stackpos = i
		tmp = getThingFromPos(toPos)
		if(tmp.uid ~= 0) then
			if(isCreature(tmp.uid) == TRUE) then
				doRemoveCreature(tmp.uid)
			else
				doRemoveItem(tmp.uid, amount)
			end

			doSendMagicEffect(toPos, CONST_ME_MAGIC_RED)
			return TRUE
		end
	end

	doSendMagicEffect(getCreaturePosition(cid), CONST_ME_POFF)
	return FALSE
end
