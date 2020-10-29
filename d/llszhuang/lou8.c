#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",CYN"接 天 楼"NOR);
        set("long",
"这是接天楼的第八层，来到了这里，就已经脱离了凡俗尘世，来吧，\n"
"醉心于这天地之间最完美无暇的交接吧，让尘世的一切烦恼远离而去吧。\n"
"此刻，你就如同天地之间一只沙鸥，心灵自由地盘旋飞翔。\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "up" : __DIR__"lou9",
          "down": __DIR__"lou7",
        ]));
        set("no_magic", "1");

        set("objects", ([
            __DIR__"npc/kuangren1" : 1,
                ])
        );

        setup();
}

