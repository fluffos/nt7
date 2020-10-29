inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在衡山山路上，四望山峰错落，林壑幽深，溪泉飞瀑，云雾
缭绕，不觉心胸大快。山路向西可以通向方广寺。东面是天柱峰。
LONG );
        set("exits", ([ 
                "eastup"    : __DIR__"tianzhu",
                "westdown"  : __DIR__"fangguangsi",
        ]));

        set("objects", ([
                __DIR__"npc/xiangke" : 2,
                __DIR__"npc/youke"    : 3,
        ]));         

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6980);
	set("coor/y", -5550);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}