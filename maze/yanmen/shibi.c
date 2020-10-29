// Create by lonely@NT
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "石壁"NOR);
        set("long", @LONG
这里快到「大宋」军营驻扎地了，远远地可以看见大营内飞扬的尘土，不
时有几匹快马飞奔进出，你正欲再看，忽然嗖地一枚冷箭从你头上飞过，还是
赶快离开的好。
LONG
);

        set("no_fly", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "south" :   __DIR__"shance",
               "north" :   __DIR__"luanshi8",
        ]));    

        set("objects", ([

        ]));
    
        setup();
}

int valid_leave(object me, string dir)
{
          if (!userp(me))         return ::valid_leave(me, dir);
        if ( dir == "north" )
        return notify_fail("带头大哥一下挡在你面前，"+HIW"白眼"NOR+"一翻：在这里呆着，不要轻举乱动！\n");
        return 1;
}

