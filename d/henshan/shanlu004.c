inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在衡山山路上，四望山峰错落，林壑幽深，溪泉飞瀑，云雾
缭绕，不觉心胸大快。这里已经隐隐看到祝融峰了。 
LONG );
        set("exits", ([ 
                "eastdown" : __DIR__"shanlu003",
                "westup"   : __DIR__"zhurongfeng",         
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6950);
	set("coor/y", -5490);
	set("coor/z", 60);
	setup();
        replace_program(ROOM);
}