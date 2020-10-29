inherit ROOM;

void create()
{
        set("short",  "长江岸边" );
        set("long", @LONG
这里是长江北岸，江水在你身边哗哗的流淌，不时可以看见有山
木从上游漂来，在水中打了个圈，向下游漂去。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "northup" : __DIR__"chibi3",
                "west" : __DIR__"chibi5",                
        ]));
        set("coor/x", -350);
        set("coor/y", -230);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
} 