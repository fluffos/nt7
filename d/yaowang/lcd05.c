inherit ROOM;

void create()
{
        set("short", "石板路");
        set("long", @LONG
这是一条青石板铺的小路，路的两旁还各有一道低矮的石栏
杆，外面是轻轻的嫩草地。
LONG
        );
        set("outdoors", "yaowang");
        set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"lcd06",
  "east" : __DIR__"lcd04",
]));

        setup();
        replace_program(ROOM);
}
