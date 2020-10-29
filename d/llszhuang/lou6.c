#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",CYN"接 天 楼"NOR);
        set("long",
"这是接天楼的第六层，夜风袭人，在这琼楼玉宇之上，便是内功深厚\n"
"之人，也不免有些高处不胜寒之感。\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "up" : __DIR__"lou7",
          "down": __DIR__"lou5",
        ]));
        set("no_magic", "1");

        set("objects", ([
                        __DIR__"npc/zhengqimie" : 1,
                ])
        );

        setup();
}
