#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",CYN"接 天 楼"NOR);
        set("long",
"这是接天楼的第一层，窗外松林蔽日，使得这里看起来十分的昏暗。\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "up" : __DIR__"lou2",
          "out": __DIR__"lou0",
        ]));
        set("no_magic", "1");

        set("objects", ([
                        __DIR__"npc/qianerbai" : 1,
                ])
        );

        setup();
}
