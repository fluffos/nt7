// Room: /city/datiepu.c
// sun
inherit ROOM;

void create()
{
        set("short", "打铁铺");
        set("long", @LONG
这是一家简陋的打铁铺，中心摆着一个火炉，炉火把四周照得一
片通红，一走进去就感到浑身火热。墙角堆满了已完工和未完工的菜
刀、铁锤、铁棍、匕首、盔甲等物。一位铁匠满头大汗挥舞着铁锤，
专心致志地在打铁。
LONG );

        set("exits", ([
                "south" : "/d/city/wofang",
                "north" : "/d/city/dongdajie2",
        ]));
        set("objects", ([
                 "/d/city/npc/smith": 1,]));

	set("coor/x", 20);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{

        if( query_temp("smith_times", me) && dir == "north" )
                return notify_fail("你已经答应帮铁匠打铁了，不要到处乱跑。\n");

        if( !query_temp("smith_times", me) && dir == "south" )
                return notify_fail("不要在别人家里乱蹿！\n");

        return ::valid_leave(me, dir);
}