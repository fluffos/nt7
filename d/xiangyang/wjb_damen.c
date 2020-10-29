inherit ROOM;

void create()
{ 
        set("short", "无极帮门前");
        set("long", @LONG
这里是无极帮襄阳总部的大门前面，无极帮的这个大厅只是发布
任务的所在，即使如此，这座建筑也造的风格迥然，让人一眼看上去，
就觉得气势不凡。
LONG );
        set("outdoors", "xiangyang");
        set("exits", ([
                "south" :  __DIR__"xiaorong1",
                "north" :  __DIR__"wjb_dating",
        ])); 
        set("objects", ([   
                __DIR__"npc/wjb-guard" : 2,   
        ]));
               
        set("coor/x", -7780);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "north") 
        {
           if( !query_temp("good_wjb", me) && query("bunch/bunch_name", me) != "无极帮" )
               return notify_fail("守卫一把拦住你，朗声喝道：我无极帮怎由闲杂人等随便进出。\n"); 
           else
           {
              delete_temp("good_wjb", me);
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 