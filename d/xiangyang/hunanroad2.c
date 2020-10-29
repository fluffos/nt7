// /d/xiangyang/hunanroad2.c

inherit ROOM;

void create()
{
        set("short", "土路");
        set("long", @LONG
你走在湘鄂交界的土路上，偶尔会有人骑着马匆匆而过。这里已
经是湖南地界，往北进入湖北境内。
LONG );
        set("outdoors", "tiezhang");

        set("exits", ([
                "northeast" : __DIR__"hunanroad1",
                "south" : __DIR__"lx",
        ]));

        set("coor/x", -3600);
        set("coor/y", -170);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}