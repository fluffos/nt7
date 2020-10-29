#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",CYN"接 天 楼"NOR);
        set("long",
"前方是一座高若叁十来丈，座落在树木苍苍的小平顶山上九层的高楼\n"
"，其台基边缘有雕刻精细的荷叶净瓶石栏杆，周围出廊，与附近的山庄楼\n"
"台相连起来，俨然一体。这些楼阁亭台规模弘整、布局相连，形成了一个\n"
"庞大的建筑组。人处其内，有种迷失了个人的渺小感觉．\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "east" : __DIR__"dynamic/jiuqu9",
          "enter": __DIR__"lou1",
          "west": __DIR__"shishi",
        ]));
        set("no_magic", "1");

        set("objects", ([
                        __DIR__"npc/zhaoyishang" : 1,
                ])
        );

        setup();
}
