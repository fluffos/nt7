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
            "east" : "d/xiangyang/caodi6",
            "southwest" : __DIR__"hunanroad2",
        ]));

        set("coor/x", -3590);
        set("coor/y", -160);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}