#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",CYN"接 天 楼"NOR);
        set("long",
"这是接天楼的第二层，楼的内壁上全是精美的壁画，可你现在肯定没\n"
"有功夫欣赏。。\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "up" : __DIR__"lou3",
          "down": __DIR__"lou1",
        ]));
        set("no_magic", "1");

        set("objects", ([
                        __DIR__"npc/sunsanhui" : 1,
                ])
        );

        setup();
}
