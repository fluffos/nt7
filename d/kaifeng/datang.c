inherit ROOM;

void create()
{
        set("short", "开封府大堂");
        set("long", @LONG
两排的衙役站立两边，再旁边是龙头，虎头，狗头三把铡刀，白
亮的锋刃令人寒毛直竖。台桌后高挂『明镜高悬』的匾额。上了大堂，
无事也胆寒，东面出去就是街道。
LONG );
        set("objects", ([
                __DIR__"npc/baozheng" : 1,
        ]));

        set("exits", ([
                  "east" : __DIR__"kaifeng",
        ]));

	set("coor/x", -5060);
	set("coor/y", 2150);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}