inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
这是一条用五彩的碎石子铺成幽静的小路，路边是轻轻的嫩
草，路的两旁各有一个小花坛，里面开着艳丽的花朵。西面是一
个小月门，东面是一个大空场。
LONG
        );
        set("exits", ([
  "east" : __DIR__"myuan",
  "out" : __DIR__"hqdoor",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
