inherit ROOM;

void create()
{
        set("short", "林荫道");
        set("long", @LONG
这是一条安静的林荫道，地上铺着奇奇怪怪五颜六色的石子，向
南北两头延伸。西面是高大的荆州城墙。南边好像有一眼温泉。
LONG );
        set("outdoors", "jingzhou");
        set("objects", ([
                  "/d/kaifeng/npc/qigai" : 1,
        ]));        
        set("exits", ([
                "north" : __DIR__"lydao1",
                "southdown" : __DIR__"wenquan",
        ]));
        set("coor/x", -7130);
	set("coor/y", -2060);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}