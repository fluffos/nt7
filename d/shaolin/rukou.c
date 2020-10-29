// Room: /d/shaolin/rukou.c
// Date: YZC 96/02/06

inherit ROOM;

void create()
{
        set("short", "五行洞入口");
        set("long", @LONG
这里是五行洞的入口。四面黑沉沉的，巨石削凿成的墙壁上镶嵌
了几颗鹅蛋大小的珠子，放出蒙蒙的黄光。就是这样，也只能照射到
几丈远的地方。地上湿漉漉的，脚边不时会踢到断裂的枯骨，发出的
脆响声在甬道内回响，使你从心底里冒出一股凌凌的寒意。四周歧路
重重，迷茫难辨。你不知道该往哪里迈步。
LONG );
        set("exits", ([
                "south" : __DIR__"wuxing"+random(5),
                "north" : __DIR__"andao1",
        ]));
        set("no_clean_up", 0);
        set("objects",([
                "/d/shaolin/npc/ad-laoshu" : 4,
        ]));
        setup();
        replace_program(ROOM);
}
