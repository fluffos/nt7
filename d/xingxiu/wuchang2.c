inherit ROOM;

void create()
{
        set("short", "山间平地");
        set("long", @LONG
山间平地，地上是嫩绿的小草，周围布了几棵桦树，山边有一眼
清泉。草地上树着几个星宿老怪当年从少林寺偷来的木人，用来供星
宿弟子练功所用。东西边紧邻着另一个练功场。
LONG );
        set("resource/water", 1);
        set("objects", ([
                __DIR__"obj/yangrou" : 3,
        ]));
        set("exits", ([
                "east" : __DIR__"xxroad6",
                "west" : __DIR__"wuchang3",
        ]));
        set("outdoors", "xingxiu");
        set("for_family", "星宿派");
        setup();
        replace_program(ROOM);
}