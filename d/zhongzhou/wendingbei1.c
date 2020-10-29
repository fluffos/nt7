inherit ROOM;

void create()
{
        set("short", "文定北街");
        set("long", @LONG
这是中州文定北街，宽敞的街道看的人不竟心情一畅。街
道的东面有一座酒楼，因离街不远，里面划拳喝酒声音历历在
耳。听的在耳你也不觉想去痛饮一杯。西面有条小巷。
LONG);
        set("outdoors", "zhongzhou");

        set("exits", ([
                "east" : __DIR__"yinghao",
                "south" : __DIR__"shizhongxin",
                "west" : __DIR__"xiaoxiang",
                "north" : __DIR__"wendingbei2",
        ]));

        set("objects", ([
                __DIR__"npc/xianren" : 1,
                __DIR__"npc/kid1": 1,
        ]));

        set("coor/x", -9040);
	set("coor/y", -990);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}