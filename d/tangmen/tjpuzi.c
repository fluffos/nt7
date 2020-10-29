// tangjiapuzi.c 

#include <ansi.h>;
#include "/d/tangmen/npc/job1.h";

void create()
{
        set("short", "唐家铺子");
        set("long",
"这是唐门世家的杂货铺，大箱小箱堆满了一地，都是一些日常用品。\n"
"唐掌柜正精神抖擞地注意着过往行人。据说这儿是唐门的一个情报点，有\n"
"许多重要的情报是从这儿出去的。门口挂着一个幌子（sign）。\n"
);
        set("item_desc", ([
                "sign": HIY"    唐       誉\n"
                           "    家       满\n"
                           "    铺       蜀\n"
                           "    子       中\n\n"NOR,
        ]));
        set("exits", ([
                "south" : __DIR__"edajie",
        ]));
        set("objects", ([
                __DIR__"npc/tangzg": 1,
        ]));
        set("no_clean_up", 1);
        setup();
}
