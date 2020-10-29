#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIY"可汗帐营"NOR);
        set("long", @LONG
这里就是「蒙古」可汗的帐营，两边分立着众将领军士，蒙古可
汗亲自领兵南征，在这里商讨谋划进军的策略，帐外不时传来军马的
嘶鸣声，那是蒙古骑兵在进行操练，看来这次南征的准备已非一日。
LONG );
        set("no_cleanup",1);

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "south" :   __DIR__"mying",
               "north" :   __DIR__"mying4",
        ]));    

        set("objects", ([

        ]));
    
        setup();
        replace_program(ROOM);
}
