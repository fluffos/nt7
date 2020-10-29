// Room: /d/mingjiao/huangtulu2.c
// Date: Java 97/04/9

inherit ROOM;

void create()
{
        set("short", "黄土小路");
        set("long", @LONG
这里是茂密松林中的一条黄土小路。松林极密，四面都是蓝幽幽
的感觉，白白的冰雪反光耀眼。你来到一个山腰的危崖之边，前边有
一个小洞。
LONG );
        set("exits", ([
                "east"  : __DIR__"huangtulu1",
                "enter" : __DIR__"shandong",
        ]));
        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}
