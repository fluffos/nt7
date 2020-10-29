inherit ROOM;

void create()
{
        set("short", "后山");
        set("long", @LONG
这是一间巨大的瓦房，房子里被直到屋顶的大木架子占满了，
树堆上坐着一位老人。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"ycl9",
]));

        set("objects", ([
        "/kungfu/class/yaowang/shiwanchen" : 1,
]));
        setup();
        replace_program(ROOM);
}
