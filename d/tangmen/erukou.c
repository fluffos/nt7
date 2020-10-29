//erukou.c  by Lonely

#include <room.h>

inherit ROOM;

void create()
{        
        set("short", "东较武场入口");
        set("long",
"这是唐门的东较武场入口。门口上面块一金漆牌匾，“东较武场”几\n"
"个大字写得孔武有力，气势逼人，仿佛是几件随时可以横空而出的暗器，\n"
"记载了唐门战史的辉煌。这里的东面，是东较武场的看台，西面是一条青\n"
"石小路。\n"
);        
        set("no_steal", "1");
        set("no_fight", "1");
        set("exits", ([
                "east" : __DIR__"ekantai2",
                "west" : __DIR__"nzlangn1",
        ]));
        setup();
        replace_program(ROOM);
}