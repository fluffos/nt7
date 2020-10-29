//hcfdian.c

#include "/d/tangmen/npc/job1.h";

void create()
{
        set("short", "药铺");
        set("long",
"这是回春堂在唐门镇的药铺，一股浓浓的药味让你几欲窒息，由此可\n"
"知这儿的药是绝对正宗。但唐门人为什么没有开个药店呢，原因很简单：\n"
"唐门的药是不卖的，只有唐门弟子才能亨用的。伙计站在柜台后招呼着顾客。\n"
);
        set("objects", ([
                "/d/city/npc/huoji" : 1,
        ]));
        set("exits", ([
                 "east" : __DIR__"ndajie",
        ]));
        set("no_clean_up", 0);
        setup();
}
