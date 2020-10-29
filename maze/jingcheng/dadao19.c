#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIW"京城大道"NOR);
        set("long", @LONG
你走在紫金城大道上，感到这里的街道比比别处的开阔，洁净。可能是因为
靠近天子脚下的缘故，寻常很少有人在这里走动。可是对武林人物来说，却似乎
根本没有把这里当什么禁地，时常有不少的帮派为了扩张自己势力，在此发生械
斗，这里反而成了解决江湖恩怨的绝佳场所。
LONG
        );
        set("outdoors", "jingcheng");
        set("exits", ([
                "east"  :  __DIR__"dadao13",
                "south" :  __DIR__"dadao20",
                "west"  :  __DIR__"dadao25",
                "north":  __DIR__"dadao24",
                "southeast"  :  __DIR__"xiaoxiang4",
        ]));

        set("no_fly",1);
        setup();
        replace_program(ROOM);
}

