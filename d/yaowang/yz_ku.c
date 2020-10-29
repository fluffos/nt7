inherit ROOM;

void create()
{
        set("short", "药材库");
        set("long", @LONG
这是一间巨大的瓦房，房子里被直到屋顶的大木架子占满了，
一股难闻的气味让人浑身不舒服，门口的竹椅上坐着一位中年人。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"yz_xiaoyuan",
]));

        set("objects", ([
        "/kungfu/class/yaowang/murong" : 1,
]));
        setup();
        replace_program(ROOM);
}
