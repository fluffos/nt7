// Room: wangjianglou.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "望江楼");
        set("long", @LONG
望江楼又名崇丽阁。下两层四角，上两层八角，朱柱琉瓦，翘角
飞甍，雕梁画栋，登临其上，远眺府南河，清风扑面，舟火穿梭，实
为胜景。楼的周遭，翠竹千茎朝天，每当雨雾氤氲，轻烟笼翠，竹籁
鸟音，动人心魄。楼前薛涛井，传说因为薛涛漂洗一种红色诗笺而流
芳千古： 无波古井因涛重，有色遗笺举世珍。这也是这一才女的传世
的唯一遗泽。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "northwest"  : __DIR__"eastroad3",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15190);
	set("coor/y", -1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}