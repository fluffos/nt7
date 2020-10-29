inherit ROOM;

void create()
{
        set("short", "石子小路");
        set("long", @LONG
这是一条用小石子铺成的小路，路边开着让人叫不上名字的
小紫花。东面是一片苗圃，随风吹来阵阵奇怪的味道，西面不远
是一所小茅草屋。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"maowu",
  "east" : __DIR__"yaopu1",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
