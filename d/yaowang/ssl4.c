inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
这是一条用五彩的碎石子铺成的小路静静的东面延伸，路边
是轻轻的嫩草，路的两旁各有一个小花坛，里面开着艳丽的花朵。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "east" : __DIR__"jiaomen",
  "west" : __DIR__"ssl3",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
