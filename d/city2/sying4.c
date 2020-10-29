#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"弓兵营"NOR);
        set("long", @LONG
这里就是「大宋」弓兵训练大营，一批批的宋军神箭手从这里训
练产生，让蒙古军胆寒，两军交锋，弓箭的使用往往能出奇制胜，因
此大宋也加强了弓箭手的训练。
LONG );
        set("train", "archer");
        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "south" :   __DIR__"syuanmen2",
               "north" :   __DIR__"sying1",
        ]));    

        set("objects", ([

        ]));
    
        setup();
        replace_program(ROOM);
}
