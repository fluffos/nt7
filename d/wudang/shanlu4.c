inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在登山的路径上，路的左右各有一条大铁链，象两条长蛇向
山上山下蜿蜒爬去。满眼是乔木夹道，如行于绿幕中。
LONG );
        set("exits", ([
                "northdown": __DIR__"shanlu3",
                "southup"  : __DIR__"taiziyan",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -350);
        set("coor/y", -300);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}