inherit ROOM;

void create()
{
        set("short", "小竹桥");
        set("long", @LONG
这是一座青竹小桥，清澈见底的溪水从桥下流过，对岸是一
排竹子扎成的篱笆，两只小鸟落在上面歌唱，来到这里让人有一
种超然脱俗的感觉。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"xiaoyuan",
  "south" : __DIR__"door",
]));

        set("outdoors", "yaowang");

        setup();
        replace_program(ROOM);
}
