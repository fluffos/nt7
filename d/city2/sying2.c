#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"步军大营"NOR);
        set("long", @LONG
这里就是「大宋」步军大营，营内刀光耀眼，剑甲林立，大宋的
步军为了对付蒙古人的骑兵，不惜花重金聘请江湖高手教习步兵地堂
刀绝技，一片片刀光卷地而过，让人惊叹不已。
LONG );
        set("train", "infantry");
        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "east" :   __DIR__"sying1",
        ]));    

        set("objects", ([

        ]));
    
        setup();
        replace_program(ROOM);
}
