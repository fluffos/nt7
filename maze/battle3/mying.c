#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蒙古大营"NOR);
        set("long", @LONG
这里就是「蒙古」军大营了，四处都是大大小小的蒙古包，北面
的一个较大的蒙古包周围都是来回巡逻的卫兵，估计应该是蒙古可汗
的帐营了。
LONG );

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */
               "north" :   __DIR__"mying1",
               "south" :   __DIR__"myuanmen1",
        ]));

        set("objects", ([

        ]));

        setup();
        replace_program(ROOM);
}

