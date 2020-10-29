#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"弓兵营"NOR);
        set("long", @LONG
这里就是「蒙古」弓兵训练大营，蒙古军历来以弓马之利而扬名，
因此蒙古军中的神箭手更是屡见不鲜，这次南征，蒙古可汗特地加调
了一匹精锐蒙古弓箭手协助作战，难怪蒙古可汗大有势在必得之架势。
LONG );

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "north" :   __DIR__"myuanmen2",
               "south" :   __DIR__"mying1",
               "west"  :   __DIR__"mying3",
               "east"  :   __DIR__"mying2",     
        ]));    

        set("objects", ([

        ]));
    
        setup();
        replace_program(ROOM);
}
