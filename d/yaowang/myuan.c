inherit ROOM;

void create()
{
        set("short", "中院");
        set("long", @LONG
这里是药王谷的内院，宽阔的院子庄严肃穆，四周的角落里
都摆放着各种各样的药罐。院子中央东北向摆放着两排石礅，
大概是药王谷给弟子讲学用的。
LONG
        );
        set("exits", ([ /* sizeof() == 3 */
  "north" : __DIR__"yitong",
  "south" : __DIR__"gd5",
  "east" : __DIR__"ssl2",
  "west" : __DIR__"ssl1",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
