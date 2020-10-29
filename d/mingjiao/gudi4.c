// Room: /d/mingjiao/gudi4.c

inherit ROOM;

void create()
{
        set("short", "昆仑仙境");
        set("long", @LONG
放开脚步向前急奔，直奔了两里有馀，才遇一座高峰阻路。放眼
四望，旦见翠谷四周高山环绕，似乎亘古以来从未有人迹到过。四面
雪峰插云，险峻陡绝计无法攀援而入。
LONG );
        set("outdoors", "mingjiao");
        set("exits", ([
                "north" : __DIR__"gudi3",
        ]));
        set("objects", ([
                __DIR__"npc/monkey" : 2,
                __DIR__"npc/bigmonkey" : 1,
        ]));
        setup();
        replace_program(ROOM);
}