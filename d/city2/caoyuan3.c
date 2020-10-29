inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "大草原");
        set("long", @LONG
这里就是蒙古大草原了，蒙古军营就在不远初了，你似乎可以听
到蒙古军队的马蹄声，你不禁放慢了脚步，尽量隐蔽大军的行踪，试
图偷偷接近蒙古军的军营。
LONG );
        set("outdoors", "xiangyang");
        set("no_magic",1);

        set("exits", ([
                    "west"  : __DIR__"caoyuan2",
                    "north"  : __DIR__"caoyuan4", 
        ]));

        setup();
} 
