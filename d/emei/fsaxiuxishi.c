#include <room.h>
inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
这是福寿庵接待峨嵋女侠们的休息室，峨嵋女弟子回山之前通常
在此借宿一宿，好备足体力上山。房内摆有一张桌，靠墙设有几张木
床。
LONG );
        set("exits", ([
                "south" : __DIR__"fsazhaitang",
        ]));
        create_door("south", "门", "north", DOOR_CLOSED);
        set("sleep_room", 1);
        set("no_fight", 1);
        set("no_clean_up", 0);
        set("coor/x", -450);
        set("coor/y", -230);
        set("coor/z", 70);
        set("coor/x", -450);
        set("coor/y", -230);
        set("coor/z", 70);
        setup();
}
