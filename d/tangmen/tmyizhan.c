#include <room.h>
inherit TRANS_ROOM; 

void create()
{
        set("short", "唐门驿站");
        set("long",
"这是一间用木板从大木棚隔出的一间小房，装饰的还算不错，一个笑\n"
"嘻嘻的伙计站在那里，见你进来连忙上来招呼，柜台侧面有一个大门，门\n"
"虚掩着，里面传来马的嘶鸣声，如果你想坐车，就看看(paizi)吧。\n"
);

        set("valid_startroom", 1);

        set("exits", ([
                 "east" : __DIR__"bdajie1",
        ]));
        set("objects", ([
                "/d/tangmen/npc/tmxer" : 1,
        ]));

        set("area", "唐门");
        set("che_id", "tmmache");

        setup();
}
