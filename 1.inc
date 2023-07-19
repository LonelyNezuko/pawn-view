function fractionSave(id, bool: isAsync = false)
{
	if(!isValidFraction(id))return false

	new radID = -1
	if(fracData[id][frRadio] != -1)
	{
		if(!isValidRadio(fracData[id][frRadio], 1)) fracData[id][frRadio] = -1
		else radID = radioData[fracData[id][frRadio]][radioID]
	}

	mysql_format(dbhandle, _query, sizeof _query, "update fractions set frName = '%s', frLeader = %d, frLeaderName = '%s', frSpawnPos = '%f,%f,%f,%f,%d', \
		frMaxRanks = %d, \
		frGovText = '%e,%e,%e', frBank = %d, \
		frDeliveryPos = '%f,%f,%f', frMats = %d, frProds = %d, frArmyFactoryPos = '%f,%f,%f,%d,%d', frWarehousePos = '%f,%f,%f, %d,%d', frWarehouseAccess = '%d,%d', \
		frEnterPos = '%f,%f,%f,%f, %d,%d', frExitPos = '%f,%f,%f,%f, %d', frHospitalObjectName = '%s', frAllEditFrac = %d, \
		frMap = %d, frClosed = %d, frMatsOrder = '%d,%d', frCNNTags = '%s', frCNNEatherAccess = '%d,%d', frWarTime = %d, frGovRanks = '%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d', \
		frRadio = %d, frClosedCNN = %d, frClosedCNNName = '%s', frColor = %d, \
		frArmyHeal = '%f,%f,%f', frArmyHealSpawn = '%f,%f,%f,%f' where frID = %d",
		fracData[id][frName], fracData[id][frLeader], fracData[id][frLeaderName],
		fracData[id][frSpawnPos][0], fracData[id][frSpawnPos][1], fracData[id][frSpawnPos][2], fracData[id][frSpawnPos][3], fracData[id][frSpawnInt],
		fracData[id][frMaxRanks], fracData[id][frGovText_1], fracData[id][frGovText_2], fracData[id][frGovText_3],
		fracData[id][frBank],
		fracData[id][frDeliveryPos][0], fracData[id][frDeliveryPos][1], fracData[id][frDeliveryPos][2],
		fracData[id][frMats], fracData[id][frProds],
		fracData[id][frArmyFactoryPos][0], fracData[id][frArmyFactoryPos][1], fracData[id][frArmyFactoryPos][2], fracData[id][frArmyFactoryPosVW], fracData[id][frArmyFactoryPosInt],
		fracData[id][frWarehousePos][0], fracData[id][frWarehousePos][1], fracData[id][frWarehousePos][2], fracData[id][frWarehouseVW], fracData[id][frWarehouseInt],
		fracData[id][frWarehouseAccess][0], fracData[id][frWarehouseAccess][1],
		fracData[id][frEnterPos][0],  fracData[id][frEnterPos][1],  fracData[id][frEnterPos][2], fracData[id][frEnterPos][3], fracData[id][frEnterVW], fracData[id][frEnterInt],
		fracData[id][frExitPos][0],  fracData[id][frExitPos][1],  fracData[id][frExitPos][2], fracData[id][frExitPos][3], fracData[id][frExitInt],
		hospitalObjectName[id], fracData[id][frAllEditFrac],
		fracData[id][frMap], fracData[id][frClosed],
		fracData[id][frMatsOrder], fracData[id][frMatsOrderPrice], fracData[id][frCNNTags], fracData[id][frCNNEatherAccess][0], fracData[id][frCNNEatherAccess][1], fracData[id][frWarTime],
		fracData[id][frGovRanks][0],  fracData[id][frGovRanks][1],  fracData[id][frGovRanks][2], fracData[id][frGovRanks][3], fracData[id][frGovRanks][4], fracData[id][frGovRanks][5], fracData[id][frGovRanks][6],  fracData[id][frGovRanks][7],  fracData[id][frGovRanks][8], fracData[id][frGovRanks][9], fracData[id][frGovRanks][10], fracData[id][frGovRanks][11],
		fracData[id][frGovRanks][12],  fracData[id][frGovRanks][13],  fracData[id][frGovRanks][14], fracData[id][frGovRanks][15], fracData[id][frGovRanks][16], fracData[id][frGovRanks][17], fracData[id][frGovRanks][18],  fracData[id][frGovRanks][19],  fracData[id][frGovRanks][20], fracData[id][frGovRanks][21], fracData[id][frGovRanks][22], fracData[id][frGovRanks][23],
		fracData[id][frGovRanks][24], fracData[id][frGovRanks][25], fracData[id][frGovRanks][26], fracData[id][frGovRanks][27],  fracData[id][frGovRanks][28],  fracData[id][frGovRanks][29], fracData[id][frGovRanks][30], fracData[id][frGovRanks][31], fracData[id][frGovRanks][32], fracData[id][frGovRanks][33], fracData[id][frGovRanks][34], fracData[id][frGovRanks][35],
		fracData[id][frGovRanks][36], fracData[id][frGovRanks][37], fracData[id][frGovRanks][38], fracData[id][frGovRanks][39], fracData[id][frGovRanks][40],
		fracData[id][frGovRanks][41], fracData[id][frGovRanks][42], fracData[id][frGovRanks][43], fracData[id][frGovRanks][44],
		radID, fracData[id][frClosedCNN], fracData[id][frClosedCNNName], fracData[id][frColor],
		fracData[id][frArmyHeal][0], fracData[id][frArmyHeal][1], fracData[id][frArmyHeal][2], fracData[id][frArmyHealSpawn][0], fracData[id][frArmyHealSpawn][1], fracData[id][frArmyHealSpawn][2], fracData[id][frArmyHealSpawn][3],
		fracData[id][frID])

	if(!isAsync) mysql_pquery(dbhandle, _query)
	else mysql_query(dbhandle, _query)

	mysql_format(dbhandle, _query, sizeof _query, "update fractions set frRanksName = '%s", fracRankNames[id][0])
	for(new i = 1; i < MAX_FRACTION_RANKS; i ++) mysql_format(dbhandle, _query, sizeof _query, "%s,%s", _query, fracRankNames[id][i])

	mysql_format(dbhandle, _query, sizeof _query, "%s', frSalary = '%d", _query, fracData[id][frSalary][0])
	for(new i = 1; i < MAX_FRACTION_RANKS; i ++) mysql_format(dbhandle, _query, sizeof _query, "%s,%d", _query, fracData[id][frSalary][i])
	mysql_format(dbhandle, _query, sizeof _query, "%s' where frID = %d", _query, fracData[id][frID])

	if(!isAsync) mysql_pquery(dbhandle, _query)
	else mysql_query(dbhandle, _query)

	mysql_format(dbhandle, _query, sizeof _query, "update fractions set frCommands = '%s-%d", fracCommandsName[id][0], fracCommandsRank[id][0])
	for(new i = 1; i < MAX_FRACTION_COMMANDS; i ++) mysql_format(dbhandle, _query, sizeof _query, "%s,%s-%d", _query, fracCommandsName[id][i], fracCommandsRank[id][i])
	mysql_format(dbhandle, _query, sizeof _query, "%s' where frID = %d", _query, fracData[id][frID])

	if(!isAsync) mysql_pquery(dbhandle, _query)
	else mysql_query(dbhandle, _query)

	mysql_format(dbhandle, _query, sizeof _query, "update fractions set frSkins = '%d", fracData[id][frSkins][0])
	for(new i = 1; i < MAX_FRACTION_SKINS; i ++) mysql_format(dbhandle, _query, sizeof _query, "%s,%d", _query, fracData[id][frSkins][i])

	mysql_format(dbhandle, _query, sizeof _query, "%s' where frID = %d", _query, fracData[id][frID])
	
	if(!isAsync) mysql_pquery(dbhandle, _query)
	else mysql_query(dbhandle, _query)

	mysql_format(dbhandle, _query, sizeof _query, "update fractions set frVehs = '%d", fracData[id][frVehs][0])
	for(new i = 1; i < MAX_FRACTION_VEHS; i ++) mysql_format(dbhandle, _query, sizeof _query, "%s,%d", _query, fracData[id][frVehs][i])

	mysql_format(dbhandle, _query, sizeof _query, "%s' where frID = %d", _query, fracData[id][frID])
	
	if(!isAsync) mysql_pquery(dbhandle, _query)
	else mysql_query(dbhandle, _query)


	mysql_format(dbhandle, _query, sizeof _query, "update fractions set frInv = '%d", fracData[id][frInv][0])
	for(new i = 1; i < MAX_INVENTORY_ITEMS; i ++) mysql_format(dbhandle, _query, sizeof _query, "%s,%d", _query, fracData[id][frInv][i])

	mysql_format(dbhandle, _query, sizeof _query, "%s', frInvCustom = '%d", _query, fracData[id][frInvCustom][0])
	for(new i = 1; i < MAX_INVENTORY_ITEMS; i ++) mysql_format(dbhandle, _query, sizeof _query, "%s,%d", _query, fracData[id][frInvCustom][i])

	mysql_format(dbhandle, _query, sizeof _query, "%s', frInvQuantity = '%d", _query, fracData[id][frInvQuantity][0])
	for(new i = 1; i < MAX_INVENTORY_ITEMS; i ++) mysql_format(dbhandle, _query, sizeof _query, "%s,%d", _query, fracData[id][frInvQuantity][i])

	mysql_format(dbhandle, _query, sizeof _query, "%s', frInvSimCost = '%d", _query, fracData[id][frInvSimCost][0])
	for(new i = 1; i < MAX_INVENTORY_ITEMS; i ++) mysql_format(dbhandle, _query, sizeof _query, "%s,%d", _query, fracData[id][frInvSimCost][i])

	mysql_format(dbhandle, _query, sizeof _query, "%s' where frID = %d", _query, fracData[id][frID])
	
	if(!isAsync) mysql_pquery(dbhandle, _query)
	else mysql_query(dbhandle, _query)

	mysql_format(dbhandle, _query, sizeof _query, "update fractions set frPrices = '%d", fracData[id][frPrices][0])
	for(new i = 1; i < MAX_FRACTION_PRICES; i ++) mysql_format(dbhandle, _query, sizeof _query, "%s,%d", _query, fracData[id][frPrices][i])

	mysql_format(dbhandle, _query, sizeof _query, "%s' where frID = %d", _query, fracData[id][frID])
	
	if(!isAsync) mysql_pquery(dbhandle, _query)
	else mysql_query(dbhandle, _query)

	mysql_format(dbhandle, _query, sizeof _query, "update fractions set frWeapons = '%d", fracData[id][frWeapons][0])
	for(new i = 1; i < MAX_FRACTION_WEAPONS; i ++) mysql_format(dbhandle, _query, sizeof _query, "%s,%d", _query, fracData[id][frWeapons][i])

	mysql_format(dbhandle, _query, sizeof _query, "%s', frWeaponsAccess = '%d", _query, fracData[id][frWeaponsAccess][0])
	for(new i = 1; i < MAX_FRACTION_WEAPONS; i ++) mysql_format(dbhandle, _query, sizeof _query, "%s,%d", _query, fracData[id][frWeaponsAccess][i])

	mysql_format(dbhandle, _query, sizeof _query, "%s' where frID = %d", _query, fracData[id][frID])
	
	if(!isAsync) mysql_pquery(dbhandle, _query)
	else mysql_query(dbhandle, _query)

	return true
}