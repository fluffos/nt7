#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",CYN"接 天 楼"NOR);
        set("long",
"这是接天楼的第五层，这已经是人世间难以企及的高度，从窗子往外\n"
"望去，远处万家灯火，与繁星争辉，近处山庄左近却是一片漆黑，不时传\n"
"来异样的声音。\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "up" : __DIR__"lou6",
          "down": __DIR__"lou4",
        ]));
        set("no_magic", "1");

        set("objects", ([
                        __DIR__"npc/wuliupo" : 1,
                ])
        );
       setup();
}
