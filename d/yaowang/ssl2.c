inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
这是一条用五彩的碎石子铺成的小路静静的东面延伸，路边
是轻轻的嫩草，路的两旁各有一个小花坛，里面开着艳丽的花朵。
西面是一个大空场。北面是一排青砖瓦房。
LONG
        );
        set("exits", ([
  "north" : __DIR__"sleeproom",
  "east" : __DIR__"ssl3",
  "west" : __DIR__"myuan",
]));

        set("outdoors", "yaowang");
        setup();
}

int valid_leave(object ob,string dir)
{
        if( !wizardp(ob)
        && (dir == "north")
         && (query("family/family_name", ob) != "药王谷") )
                return notify_fail("边上窜出两个童子拦住了你的去路。\n");

        return ::valid_leave(ob,dir);
}
