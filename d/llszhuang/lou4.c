#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",CYN"接 天 楼"NOR);
        set("long",
"这是接天楼的第四层，窗外夜幕低垂，星光点点，在这大雪後的纯美\n"
"世界上舞跃闪烁，像在为俯仰着道诸般一切的接天楼上正在发生的盛事，\n"
"奏起了寂静伟大的乐章。\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "up" : __DIR__"lou5",
          "down": __DIR__"lou3",
        ]));
        set("no_magic", "1");

        set("objects", ([
                        __DIR__"npc/zhouwushu" : 1,
                ])
        );

        setup();
}
