inherit ROOM;

void create()
{
        set("short", "小吃店");
        set("long", @LONG
这里是石梁边的一间小吃店，卖些简单的饮食，专门赚那些游客
的钱。
LONG );
        set("exits", ([
                "west" : __DIR__"shiliang",
        ]));

        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
        set("coor/x", -360);
        set("coor/y", -250);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}