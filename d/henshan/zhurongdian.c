#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "祝融殿");
        set("long", @LONG
祝融殿，又名老圣殿，祠火神祝融。花岗石砌墙，铁瓦覆顶，殿
宇凌空傲雪，巍然屹立在衡山绝顶。殿门的石楹上刻着有「[1；37m寅宾日出，
峻极于天[2；37；0m」的字样，远远看去字峰雄浑而有力。殿上还立有「[1；31m圣德重
华[2；37；0m」的楣额。
LONG );
        set("exits", ([
                "southdown"  : __DIR__"wangritai",
                "northdown"  : __DIR__"wangyuetai",
                "westup"     : __DIR__"shanlu003",
                "east"       : __DIR__"changlang",
        ]));

        set("objects", ([
                CLASS_D("henshan") + "/mi" : 1,
                CLASS_D("henshan") + "/first" : 1,
                __DIR__"npc/dizi1"   : 4,
                __DIR__"npc/xiangke" : 2,
        ]));
        set("no_clean_up", 0);
	set("coor/x", -6930);
	set("coor/y", -5490);
	set("coor/z", 40);
	setup();

        "/clone/board/henshan_b"->foo();
}

int valid_leave(object me, string dir)
{
        object guard;

        if (dir == "northdown" || dir == "southdown"
           || ! objectp(guard = present("mi weiyi", this_object())))
                return ::valid_leave(me, dir);

        return guard->permit_pass(me, dir);
}
