// Room: xiaojing.c
// By River 98/12
inherit ROOM;
void create()
{
        set("short", "谷中小径");
        set("long", @LONG
你走在谷中的一条小径上，这里十分荒僻，头顶有一些不知名的小鸟在跳
来跳去，四周丛林密布，鲜花绿草若隐若现。
LONG
        );
        set("exits", ([
            "north" : __DIR__"caodi",
            "south" : __DIR__"guzhong",
        ]));
        
        set("outdoors", "大理");

        setup();
}