// Room: /city/beidajie1.c
// YZC 1995/12/04 

inherit ROOM;
void create()
{
        set("short", "北大街");
        set("long", @LONG
你走在一条繁忙的街道上，看着操着南腔北调的人们行色匆匆，
许多人都往南边走去，那里有一个热闹的广场。东边是一家生意兴隆
的客栈，来自各地的人们进进出出，据说也是情人们的幽会地点。西
边是一家钱庄，可以听到叮叮当当的金银声音。
LONG );
        set("outdoors", "city");
        set("objects", ([
                CLASS_D("ouyang") + "/ouyangke" : 1,
        ]));
        set("exits", ([
                "east"  : "/d/city/kedian",
                "south" : "/d/city/guangchang",
                "west"  : "/d/city/qianzhuang",
                "north" : "/d/city/beidajie2",
        ]));

	set("coor/x", 0);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
}