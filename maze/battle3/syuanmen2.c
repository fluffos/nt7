#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "辕门外"NOR);
        set("long", @LONG
这里就是「大宋」军营驻扎地了，远远地可以看见一面大旗，上
面书着一个斗大的隶书「宋」字，再走近些就到军营了，寻常人还是
不要靠近的好，省得被当成细作捉起来。
LONG );

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "north" :   __DIR__"sying4",
               "west"  :   __DIR__"yidao",
        ]));    

        set("objects", ([

        ]));
    
        setup();
        replace_program(ROOM);
}
