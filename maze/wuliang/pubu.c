// Room: pubu.c
// By River 98/12
inherit ROOM;
void create()
{
        set("short", "大瀑布");
	set("long", @LONG
你又奔出一阵，双腿酸软，气喘吁吁，终于走出了大松林。猛听得水声响
亮，轰轰隆隆，便如潮水大至一般，抬头一看，只见西北角上犹如银河倒悬，
一条大瀑布从高崖上直泻下来。
LONG
	);
	set("exits", ([ 
	    "west" : __DIR__"songlin1", 
            "southeast" : __DIR__"shanya",
        ]));
        set("objects", ([
                __DIR__"npc/ge_guangpei" : 1,
                __DIR__"npc/gan_guanghao" : 1,
        ]));
        set("outdoors", "大理");

	setup();
}

int valid_leave(object me,string dir)
{ 
     if( dir == "southeast"
      && (present("gan guanghao", environment(me))))
         return notify_fail("干光豪对你奸笑一声：想逃，你留下命来吧。\n");
     if( dir == "southeast"
      && (present("ge guangpei", environment(me))))
         return notify_fail("葛光佩对你冷笑一声：想逃，你留下命来吧。\n");
         return ::valid_leave(me, dir);
}