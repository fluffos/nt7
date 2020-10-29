#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "荆州衙门");
        set("long", @LONG
一座大厦，朱红的大门，门上钉着碗口大的铜钉，门外两盏大灯笼，
一盏写着“荆州府正堂”，另一盏写着“凌府”。这里是荆州衙门大门
所在，衙门的两扇朱木大门紧紧关闭着。『肃静』『回避』的牌子分放
两头石狮子的旁边。前面有一个大鼓，显然是供小民鸣冤用的。几名衙
役在门前巡逻。
LONG );
        set("region", "jingzhou");
        set("exits", ([
                "south" : __DIR__"ymzhengting",
                "north" : __DIR__"xidajie1",
        ]));
        set("objects", ([
                __DIR__"obj/lion" : 2,
                __DIR__"npc/yayi" : 4,
        ]));

        set("coor/x", -7110);
	set("coor/y", -2060);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "south" &&
           objectp(present("ya yi", environment(me))))
                return notify_fail(CYN "衙役齐声喝道：威……武……\n" NOR);
        return ::valid_leave(me, dir);
}