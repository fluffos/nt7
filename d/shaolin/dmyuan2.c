// Room: /d/shaolin/dmyuan2.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "达摩院二楼");
        set("long", @LONG
这是一座古朴的殿堂。西首的墙上挂满了各类武功图谱，不少白
须白眉的老僧们正端坐在图谱画轴之前，似乎在苦苦思索。南北山墙
是高及屋顶的大书架，走近细看，它们是各门各派的武功秘笈，屋正
中摆着几张矮几诃和几个团，几位老僧正在入定中。
LONG );
        set("exits", ([
                "down" : __DIR__"dmyuan",
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/xuan-bei" : 1,
                "/clone/book/xisuijing" : 1,
                __DIR__"npc/xiao-bei" : 1,
        ]));
        set("no_magic", 1);
        setup();
}

int valid_leave(object me, string dir)
{
        if (present("xisui jing", me))
                return notify_fail("本寺最高心法不见了，你怎敢就走？\n");
        return 1;
}
