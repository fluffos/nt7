#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",CYN"接 天 楼"NOR);
        set("long",
"这是接天楼的极顶，在这最接近虚空的地方，一场最绚烂的决战正在\n"
"进行！一位是名震天下数十年的魔师，一位是已成为传奇的覆雨剑。他们\n"
"的决战已经远远超出了生死胜负，达到了另外一个层面。他们的身形似动\n"
"实静，举手投足间莫不隐隐蕴含着天地间的至法。\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "down": __DIR__"lou8",
        ]));
        set("no_magic", "1");

        set("objects", ([
               __DIR__"npc/kuangren1" : 2,
               __DIR__"npc/edward" : 1,
        ]));

        setup();
}
