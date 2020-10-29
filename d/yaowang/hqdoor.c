inherit ROOM;

void create()
{
        set("short", "小月门");
        set("long", @LONG
这里是过道的尽头，东面是红砖围墙，正中是一扇小月门，
门口站着两个小丫环。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "enter" : __DIR__"ssl1",
  "west" : __DIR__"tulu3",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
