// Room: wlj.c
// By River 98/12
inherit ROOM;
void create()
{
        set("short", "石板路");
	set("long", @LONG
你走在一条宽阔的石板路上。这是用一米见方的巨大石板铺设而成的，可
以并行十来个人也绝无问题。两侧是参天古柏，直耸入天，上端树冠相叠，遮
天蔽日。路的尽头，就是剑湖宫了。
LONG
	);
	set("exits", ([ 
	    "out" : __DIR__"wljmen",
	    "north" : __DIR__"jhg",
            "west" : __DIR__"xting",
            "east" : __DIR__"dting",
        ]));
        set("objects", ([
              __DIR__"npc/rong_ziju" : 1, 
        ]));
        set("outdoors", "大理");

	setup();
}

int valid_leave(object me,string dir)
{ 
     if( dir != "out"
      && (present("rong ziju", environment(me))))
         return notify_fail("容子矩上前拦住你的去路：无量剑重地，任何人不得擅自入内。\n");
         return ::valid_leave(me, dir);
}