inherit ROOM;

void create()
{
        set("short", "无极帮门前");
        set("long", @LONG
这里是无极帮杭州分部的大门前面，无极帮的这个大厅只是发布
任务的所在，即使如此，这座建筑也造的风格迥然，让人一眼看上去，
就觉得气势不凡。
LONG );
        set("outdoors", "hangzhou");
        set("exits", ([
                "east" :  __DIR__"road12",
                "west" :  __DIR__"wjb_hzdt",
        ]));
        set("objects", ([
                __DIR__"npc/wjb-guard" : 2,
        ]));

	set("coor/x", 820);
	set("coor/y", -2060);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (objectp(present("shou wei", environment(me))) && dir == "west")
        {
           if( !query_temp("good_wjb1", me) && query("bunch/bunch_name", me) != "无极帮" )
               return notify_fail("守卫一把拦住你，朗声喝道：我无极帮怎由闲杂人等随便进出。\n");
           else
           {
              delete_temp("good_wjb1", me);
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir);
}