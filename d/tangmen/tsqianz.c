// /d/tangmen/qianzhuang.c

#include "/d/tangmen/npc/job1.h";

void create()
{
        set("short", "唐氏钱庄");
        set("long",
"蜀中唐门的钱庄，已有三多百年的历史了，信誉是一流的。老板也是\n"
"唐门中比较有威信的人担任，不是一般的人所能胜任的。而且这里的银票\n"
"全国通用，是不可多有的老字号了。\n"
);
        set("exits", ([
                "north" : __DIR__"edajie",
        ]));
        set("objects", ([
               "/d/tangmen/npc/tangq" : 1
        ]));
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        setup();
}

