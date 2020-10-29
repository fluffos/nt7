inherit ROOM;

void create()
{
        set("short", "草地");
        set("long", @LONG
这里是一片青青的草地，边上稀稀落落的长着几根青竹，周
围的空气里散发着淡淡的草药香味。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"xiaoyuan",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
