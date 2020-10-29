inherit ROOM;

void create()
{
        set("short", "小院");
        set("long", @LONG
这里是一处寂静的小院落，周围是用青竹扎就的篱笆，地上
长着嫩绿的小草，院子中央摆着一长园石桌，桌子边上有几个石
礅，石桌和石礅表面都非常光滑，好像经常有人坐在这里。
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"gd1",
  "south" : __DIR__"bridge1",
  "east" : __DIR__"lawn",
  "west" : __DIR__"well",
]));

        set("outdoors", "yaowang");

        setup();
        replace_program(ROOM);
}
