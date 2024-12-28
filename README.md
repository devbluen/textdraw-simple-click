# 🫧 Textdraw Simple Click
This include will streamline your modding and creation of textdraw clicks, eliminating the need for hooks or ALS. With this small change, the clicks will be 200% faster and more efficient, thereby reducing CPU usage and improving your server's responsiveness.

# 📃 Usage example
## Registering the clicks, see example below
```pawn
stock CreateTextdraw(playerid) {

    // A simple example of textdraw creation, just to illustrate SetClick.
    new PlayerText:id = CreatePlayerTextDraw(playerid, 0.0, 0.0, "LD_SPAC:white") // or box, whatever
    PlayerTextDrawSetSelectable(playerid, id, true);

    PlayerTextDrawSetClick(playerid, "ClickLogin", id);
    SelectTextDraw(playerid, -1);
}

PlayerTextDrawClick:ClickLogin(playerid, params) {

    // your code
    return true;
}
```

## Now a click registration with parameters (can be used with loops, for example, inventory slots, etc.)
```pawn
stock CreateTextdraw(playerid) {

    // A simple example of textdraw creation, just to illustrate SetClick.
    new PlayerText:inventario_slot[3];
    
    inventario_slot[0] = CreatePlayerTextDraw(playerid, 0.0, 0.0, "LD_SPAC:white")
    PlayerTextDrawSetSelectable(playerid, inventario_slot[0], true);

    inventario_slot[1] = CreatePlayerTextDraw(playerid, 0.0, 0.0, "LD_SPAC:white")
    PlayerTextDrawSetSelectable(playerid, inventario_slot[1], true);

    inventario_slot[2] = CreatePlayerTextDraw(playerid, 0.0, 0.0, "LD_SPAC:white")
    PlayerTextDrawSetSelectable(playerid, inventario_slot[2], true);

    for(new i = 0; i < sizeof inventario_slot; i++)
        PlayerTextDrawSetClick(playerid, "InventorySlot", inventario_slot[i], i);

    SelectTextDraw(playerid, -1);
}

PlayerTextDrawClick:InventorySlot(playerid, slot_inventory) {

    // your code
    return true;
}
```

# 🔨 Results
In tests I conducted, the clicks became extremely more responsive and faster because the code doesn't need to search for the correct PlayerText to run the code. If you encounter any problems, please open an issue so I can assist you. 😊
