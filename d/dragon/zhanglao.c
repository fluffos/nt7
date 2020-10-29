inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "长老室");
        set("long",
"[1;32m这是精灵长老所在的房间，一个白胡子的精灵族老人正坐在\n"
"窗前沉思着什么。\n"
);
        set("exits", ([ /* sizeof() == 4 */
   "west" : __DIR__"village",
   "southeast" : __DIR__"xiuxishi",
   ]));

        set("no_magic", 1);
        setup();
        replace_program(ROOM);

}
