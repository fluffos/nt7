#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIR "【轮回司】" NOR);
        set("long", HIR @LONG

                 轮        回        司

    这里阴阳交汇之处，周围一片黑暗，只有一阵阵氤氲之气从下方涌出。

LONG NOR );

        set("sleep_room", 1);

        set("sky", 1);
        // 在此演练lunhui-sword
        set("lunhui", 1);
        set("valid_startroom", 1);
        setup();
}
