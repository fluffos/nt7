#include <room.h>
inherit ROOM;

void create()
{
        set("short", "斋堂");
        set("long", @LONG
这里便是峨嵋福寿庵的斋堂。福寿庵本不大，但由于经常接待其
他庵的弟子，斋堂倒也不小。只见厅内摆满了长长的餐桌和长凳，几
位小师太正来回忙碌着布置素斋。桌上摆了几盆豆腐，花生，青菜以
及素鸭等美味素食。北面有一扇门。
LONG );
        set("exits", ([
                "east"  : __DIR__"lingwenge",
                "north" : __DIR__"fsaxiuxishi",
        ]));
        create_door("north", "门", "south", DOOR_CLOSED);
        set("no_clean_up", 0);
        set("coor/x", -450);
        set("coor/y", -240);
        set("coor/z", 70);
        setup();
}
