// Room: /d/city/yizhan.c

inherit ROOM;

void create()
{
        set("short", "驿站");
        set("long", @LONG
这是高丽驿站，战时负责传送和前线里的往来公文。因为暂时还不
开放给百姓使用，所以没什么可参观的。不过这里高丽弟子平时休息的
地方。面前的桌子上放了几个打糕，还有几碗清水。
LONG
        );

        set("exits", ([
                "south" : __DIR__"qinglong-2",
        ]));
        
    set("no_fight",1);
        set("resource/water",1);
        setup();
        replace_program(ROOM);
}

