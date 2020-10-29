//Room: biaoju-dayuan.c

inherit ROOM;

void create()
{
        set("short", "河洛镖局大院");
        set("long", @LONG
院子里面堆放着十几辆用草席盖着的空镖车，草席上积满了雪，
东面的屋檐下，斜插着一面酱色镶金边的镖旗，被风吹得蜡蜡作响，
使人几乎分辨不出用金线绣在那上面的是老虎，还是狮子。大院里不
时镖师进出。
LONG );
        set("exits", ([
                "north" : "/d/changan/biaoju-damen",
                "south" : "/d/changan/biaoju-dating",
        ]));
        set("objects", ([
                "/d/changan/npc/biaotou" : 1,
                "/d/changan/npc/tang" : 2,
        ]) );
    
        set("outdoors", "changan");
        set("coor/x", -10700);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
}