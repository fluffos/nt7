#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",CYN"接 天 楼"NOR);
        set("long",
"这是接天楼的第三层，渐行渐高，窗外的风景不住变幻。\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "up" : __DIR__"lou4",
          "down": __DIR__"lou2",
        ]));
        set("no_magic", "1");

        set("objects", ([
                        __DIR__"npc/lisicui" : 1,
                ])
        );

        setup();
}
