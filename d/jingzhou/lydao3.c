inherit ROOM;

void create()
{
        set("short", "林荫道");
        set("long", @LONG
这是一条安静的林荫道，地上铺着奇奇怪怪五颜六色的石子，向
东西两头延伸。东面是一条林荫道。径直通南大街。西边好像有一眼
温泉。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "east" : __DIR__"lydao4",
                "westdown" : __DIR__"wenquan",
        ]));
        set("coor/x", -7120);
	set("coor/y", -2070);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}