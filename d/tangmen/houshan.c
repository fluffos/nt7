//houshan.c                四川唐门—后山

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "后山");
        set("long",
"这里是莲云阁后山。这里阴森恐怖，四周密林丛生，连日光也被遮住\n"
"，地上树影斑驳，林中好象有无数凶狠的目光注视着你，可能随时会扑上\n"
"来杀死你，赶快离开这里吧！\n"
);
        set("exits", ([
                        "northdown" : __DIR__"shanshi1",
                        "westdown" : __DIR__"exiaolu2",
                        "eastup" : __DIR__"shandao1",
                        "southdown" : __DIR__"shanshi6",
        ]));
        set("area", "tangmen");
        set("outdoors", "tangmen");
        setup();
        replace_program(ROOM);
}