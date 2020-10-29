#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "辕门外"NOR);
        set("long", @LONG
这里就是「蒙古」军营驻扎地了，远远地可以看见大营内飞扬的
尘土，不时有几匹快马飞奔进出，你正欲再看，忽然嗖地一枚冷箭从
你头上飞过，还是赶快离开的好。
LONG );

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "south" :   __DIR__"mying4",
        ]));    

        set("objects", ([

        ]));
    
        setup();
        replace_program(ROOM);
}
