inherit ROOM;

void create()
{
        set("short", "前院");
        set("long", @LONG
这里是前院的小广场，用青砖铺就的地面非常整洁。
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"gd3",
  "south" : __DIR__"gd2",
  "east" : __DIR__"yanwu",
  "west" : __DIR__"keting",
]));

        set("objects", ([
        "/kungfu/class/yaowang/jiang" : 1,
]));
        set("valid_startroom", 1);
        set("no_fight", 1);
        set("outdoors", "yaowang");
        setup();
//加个post板
}
