inherit ROOM;

void create()
{
        set("short", "石子小路");
        set("long", @LONG
这是一条用紫色和绿色小石子铺成的小路，看着让人格外的
不舒服。南面是一片秘密的小树林，北面不远是一排小篱笆。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"yz_door",
  "south" : __DIR__"xiaodao7",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
