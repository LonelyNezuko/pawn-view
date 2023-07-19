function phoneCef_cnn_event(playerid, event[], args[]) {
    if(!isLauncher(playerid))return false
    if(!openedData[playerid][openPhone])return false

    if(getString(event, "client::phone:cnn:choice")) phoneCef_cnnList(playerid)
    else if(getString(event, "client::phone:cnn:cancel")) {
        if(playerAds[playerid] != -1) {
            new invSlot = phoneCefData[playerid][phoneCef_invSlot]
            if(invSlot == -1
                || !inventoryIsPhone(invData[playerid][invModel][invSlot]))return phoneCefClose(playerid)

            phoneCefData[playerid][phoneCef_simCost] = invData[playerid][invSimCost][invSlot] += playerAdsCost[playerid]
            
            removeAds(playerid)
            cef_emit_event(playerid, "ui::phone:cnn:error", CEFSTR("Вы успешно отозвали свое объявление"))
        }

        cef_emit_event(playerid, "ui::phone:cnn:block", CEFINT(0))
    }
    else if(getString(event, "client::phone:cnn")) {
        new frac, text[144]
        sscanf(args, "p<;>ds[144]", frac, text)

        if(!isValidFraction(frac)
            || fracData[frac][frType] != FRACTION_TYPE_CNN) {
            
            cef_emit_event(playerid, "ui::phone:cnn:cnn", CEFSTR(""))
            cef_emit_event(playerid, "ui::phone:cnn:cnnID", CEFINT(-1))
            cef_emit_event(playerid, "ui::phone:cnn:price", CEFINT(0))

            return cef_emit_event(playerid, "ui::phone:cnn:error", CEFSTR("Выбранное СМИ не найдено"))
        }
        if(fracData[frac][frClosed]) {
            cef_emit_event(playerid, "ui::phone:cnn:cnn", CEFSTR(""))
            cef_emit_event(playerid, "ui::phone:cnn:cnnID", CEFINT(-1))
            cef_emit_event(playerid, "ui::phone:cnn:price", CEFINT(0))

            return cef_emit_event(playerid, "ui::phone:cnn:error", CEFSTR("Выбранное СМИ закрыто"))
        }

        if(strlen(text) < 10)return cef_emit_event(playerid, "ui::phone:cnn:error", CEFSTR("Минимум 10 символов"))
        if(phoneCefData[playerid][phoneCef_simCost] < fracData[frac][frPrices][1] * strlen(text))return cef_emit_event(playerid, "ui::phone:cnn:error", CEFSTR("У Вас не хватает средств на сим карте"))

        new invSlot = phoneCefData[playerid][phoneCef_invSlot]
        if(invSlot == -1
            || !inventoryIsPhone(invData[playerid][invModel][invSlot]))return phoneCefClose(playerid)

        new adid = addAds(playerid, frac, text, phoneCefData[playerid][phoneCef_sim])
        if(adid == -1)return cef_emit_event(playerid, "ui::phone:cnn:error", CEFSTR("Данное СМИ загружено объявлениями. <br />Выберите другое"))

        playerSendNotify(playerid, "success", "Вы успешно подали объявление в СМИ '%s'. Номер объявления: %d", fracData[frac][frName], adid)
        chat(playerid, color_grey, "Текст объявления: %s", text)

        playerAds[playerid] = adid
        playerAdsFrac[playerid] = frac
        playerAdsCost[playerid] = fracData[frac][frPrices][1] * strlen(text)

        phoneCefData[playerid][phoneCef_simCost] = invData[playerid][invSimCost][invSlot] -= fracData[frac][frPrices][1] * strlen(text)
        cef_emit_event(playerid, "ui::phone:cnn:block", CEFINT(1))
    }
}