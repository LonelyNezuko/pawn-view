function mFactoryUpdateCarPlaceText(id)
{
	new statusName[][30] = { "Покрасить", "Установить 4 колеса", "Установить двигатель", "Установить стекла", "Установить 2 бампера", "Установить фары", "Установить глушитель", "-" }

	format(_string, 512, "Каркас будущего транспорта\n\
		{ffffff}Что делать: {3e98d0}%s", statusName[carPlace[id][carPlaceType]])

	for(new i = 0; i < 4; i ++) if(IsValidDynamic3DTextLabel(carPlace[id][carPlaceCountText][i])) DestroyDynamic3DTextLabel(carPlace[id][carPlaceCountText][i])

	if(carPlace[id][carPlaceType] == MFACTORY_CARPLACE_TYPE_UPLOAD)
	{
		DestroyDynamic3DTextLabel(carPlace[id][carPlaceText])

		new Float: objPos[3]
		for(new i = 0; i < 20; i ++)
		{
			if(!IsValidDynamicObject(carPlace[id][carPlaceObjects][i])) continue

			GetDynamicObjectPos(carPlace[id][carPlaceObjects][i], objPos[0], objPos[1], objPos[2])

			objPos[0] += carPlace[id][carPlaceMoveObjectCount][0]
			objPos[1] += carPlace[id][carPlaceMoveObjectCount][1]

			MoveDynamicObject(carPlace[id][carPlaceObjects][i], objPos[0], objPos[1], objPos[2], 2.5)
		}

		SetTimerEx("@_mFactoryUpdateCarPlacetReset", 16000, false, "d", id)
		return false
	}

	switch(carPlace[id][carPlaceType])
	{
		case MFACTORY_CARPLACE_TYPE_COLOR: format(_string, 512, "%s\n\n{afafaf}Процесс: %.1f%% из 100%", _string, carPlace[id][carPlaceCount])
		case MFACTORY_CARPLACE_TYPE_WHEEL:
		{
			strcat(_string, "\n")
			new wheelNames[][30] = { "Переднее правое", "Переднее левое", "Заднее левое", "Заднее правое" }

			for(new i = 0; i < 4; i ++)
			{
				if(carPlace[id][carPlaceInstalledWheel][i] != INVALID_PLAYER_ID)
				{
					new userid = carPlace[id][carPlaceInstalledWheel][i]
					if(!isLogged(userid)
						|| otherData[userid][oJobStatus] != JOB_ID_FACTORY_MOTOR
						|| otherData[userid][oJobData] != 2
						|| otherData[userid][oJobCount] != 2)
					{
						carPlace[id][carPlaceInstalledWheel][i] = INVALID_PLAYER_ID
						return mFactoryUpdateCarPlaceText(id)
					}

					format(_string, 1024, "%s\n{afafaf}%s колесо: {dee548}Устанавливает %s [%d]", _string, wheelNames[i], returnPlayerName(userid), userid)
				}
				else
				{
					if(!carPlace[id][carPlaceCountData][i]) carPlace[id][carPlaceCountText][i] = CreateDynamic3DTextLabel("Нажмите ALT, чтобы установить колесо", 0xAFAFAFFF, carPlaceWheelPos[id][i][0], carPlaceWheelPos[id][i][1], carPlaceWheelPos[id][i][2] - 0.5, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0)
					format(_string, 1024, "%s\n{afafaf}%s колесо: %s", _string, wheelNames[i], carPlace[id][carPlaceCountData][i] ? "{3fd1a0}Установлено" : "Неустановлено")
				}
			}
		}
		case MFACTORY_CARPLACE_TYPE_ENGINE, MFACTORY_CARPLACE_TYPE_WINDOW, MFACTORY_CARPLACE_TYPE_SILENCE:
		{
			if(carPlace[id][carPlaceInstalled] != INVALID_PLAYER_ID)
			{
				new userid = carPlace[id][carPlaceInstalled]
				if(!isLogged(userid)
					|| otherData[userid][oJobStatus] != JOB_ID_FACTORY_MOTOR
					|| otherData[userid][oJobData] != 2
					|| otherData[userid][oJobCount] != 2)
				{
					carPlace[id][carPlaceInstalled] = INVALID_PLAYER_ID
					return mFactoryUpdateCarPlaceText(id)
				}

				switch(carPlace[id][carPlaceType])
				{
					case MFACTORY_CARPLACE_TYPE_ENGINE: format(_string, 512, "%s\n\n{afafaf}Двигатель: {dee548}Устанавливает %s [%d]", _string, returnPlayerName(userid), userid)
					case MFACTORY_CARPLACE_TYPE_WINDOW: format(_string, 512, "%s\n\n{afafaf}Стекла: {dee548}Устанавливает %s [%d]", _string, returnPlayerName(userid), userid)
					case MFACTORY_CARPLACE_TYPE_SILENCE: format(_string, 512, "%s\n\n{afafaf}Глушитель: {dee548}Устанавливает %s [%d]", _string, returnPlayerName(userid), userid)
				}
			}

			switch(carPlace[id][carPlaceType])
			{
				case MFACTORY_CARPLACE_TYPE_ENGINE: carPlace[id][carPlaceCountText][0] = CreateDynamic3DTextLabel("Нажмите ALT, чтобы установить двигатель", 0xAFAFAFFF, carPlaceEnginePos[id][0], carPlaceEnginePos[id][1], carPlaceEnginePos[id][2] - 0.5, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0)
				case MFACTORY_CARPLACE_TYPE_WINDOW: carPlace[id][carPlaceCountText][0] = CreateDynamic3DTextLabel("Нажмите ALT, чтобы установить стекла", 0xAFAFAFFF, carPlaceEnginePos[id][0], carPlaceEnginePos[id][1], carPlaceEnginePos[id][2] - 0.5, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0)
				case MFACTORY_CARPLACE_TYPE_SILENCE: carPlace[id][carPlaceCountText][0] = CreateDynamic3DTextLabel("Нажмите ALT, чтобы установить глушитель", 0xAFAFAFFF, carPlaceBumperPos[id][1][0], carPlaceBumperPos[id][1][1], carPlaceBumperPos[id][1][2] - 0.5, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0)
			}
		}
		case MFACTORY_CARPLACE_TYPE_BUMPER:
		{
			strcat(_string, "\n")
			new wheelNames[][30] = { "Передний", "Задний" }

			for(new i = 0; i < 2; i ++)
			{
				if(carPlace[id][carPlaceInstalledWheel][i] != INVALID_PLAYER_ID)
				{
					new userid = carPlace[id][carPlaceInstalledWheel][i]
					if(!isLogged(userid)
						|| otherData[userid][oJobStatus] != JOB_ID_FACTORY_MOTOR
						|| otherData[userid][oJobData] != 2
						|| otherData[userid][oJobCount] != 2)
					{
						carPlace[id][carPlaceInstalledWheel][i] = INVALID_PLAYER_ID
						return mFactoryUpdateCarPlaceText(id)
					}

					format(_string, 1024, "%s\n{afafaf}%s бампер: {dee548}Устанавливает %s [%d]", _string, wheelNames[i], returnPlayerName(userid), userid)
				}
				else
				{
					if(!carPlace[id][carPlaceCountData][i]) carPlace[id][carPlaceCountText][i] = CreateDynamic3DTextLabel("Нажмите ALT, чтобы установить бампер", 0xAFAFAFFF, carPlaceBumperPos[id][i][0], carPlaceBumperPos[id][i][1], carPlaceBumperPos[id][i][2] - 0.5, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0)
					format(_string, 1024, "%s\n{afafaf}%s бампер: %s", _string, wheelNames[i], carPlace[id][carPlaceCountData][i] ? "{3fd1a0}Установлен" : "Неустановлен")
				}
			}
		}
		case MFACTORY_CARPLACE_TYPE_LIGHT:
		{
			strcat(_string, "\n")
			new wheelNames[][30] = { "Передние", "Задние" }

			for(new i = 0; i < 2; i ++)
			{
				if(carPlace[id][carPlaceInstalledWheel][i] != INVALID_PLAYER_ID)
				{
					new userid = carPlace[id][carPlaceInstalledWheel][i]
					if(!isLogged(userid)
						|| otherData[userid][oJobStatus] != JOB_ID_FACTORY_MOTOR
						|| otherData[userid][oJobData] != 2
						|| otherData[userid][oJobCount] != 2)
					{
						carPlace[id][carPlaceInstalledWheel][i] = INVALID_PLAYER_ID
						return mFactoryUpdateCarPlaceText(id)
					}

					format(_string, 1024, "%s\n{afafaf}%s фары: {dee548}Устанавливает %s [%d]", _string, wheelNames[i], returnPlayerName(userid), userid)
				}
				else
				{
					if(!carPlace[id][carPlaceCountData][i]) carPlace[id][carPlaceCountText][i] = CreateDynamic3DTextLabel("Нажмите ALT, чтобы установить фары", 0xAFAFAFFF, carPlaceBumperPos[id][i][0], carPlaceBumperPos[id][i][1], carPlaceBumperPos[id][i][2] - 0.5, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0)
					format(_string, 1024, "%s\n{afafaf}%s фары: %s", _string, wheelNames[i], carPlace[id][carPlaceCountData][i] ? "{3fd1a0}Установлены" : "Неустановлены")
				}
			}
		}
	}

	UpdateDynamic3DTextLabelText(carPlace[id][carPlaceText], 0x3e98d0FF, _string)
}