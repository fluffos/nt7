// jiulou.c

#include "/d/tangmen/npc/job1.h";

void create()
{
        set("short", "唐门酒楼");
        set("long",
"这是唐家镇有名的酒楼可以说是无人不知，无人不晓。所有人到此，\n"
"都要来这儿一醉方休，不醉不归。据说对人的身体某些方面有好处，不过\n"
"没有确定是不是的，因为醉过的人都是笑而不答。但你可以试一试啊。楼\n"
"下布置简易，楼上是雅座。老板就在上面啊。不知有没有福气见见她啊！\n"
"见到她，说不定有什么好处啊！\n"
);
        set("exits", ([
                "south" : __DIR__"xdajie",
                // "up"    : __DIR__"jiulou2",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer2" : 1,
        ]));
        set("no_fight", 1);
        set("resource/water", 1);
        set("no_steal", 1);
        setup();
}
