#include <room.h>

inherit ROOM;

void create()
{ 
        set("short","侠义盟门前");
        set("long", @LONG
这里是侠义盟长安总舵的大门，一面大旗迎风招展，上书『锄恶
务尽』四个大字。
LONG );
        set("outdoors", "yangzhou");
        set("exits", ([
                "south" :  __DIR__"dongan-dadao",
                "north" : __DIR__"xym_dating",
        ])); 
        set("objects", ([   
             __DIR__"npc/xym_guard" : 2,   
            ]));
               
        set("coor/x", -10690);
	set("coor/y", 1940);
	set("coor/z", 0);
	setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "north") 
        {
           if( !query_temp("good_xym1", me) && query("bunch/bunch_name", me) != "侠义盟" )
               return notify_fail("守卫一把拦住你，朗声喝道：我侠义盟怎由闲杂人等随便进出。\n"); 
           else
           {
              delete_temp("good_xym1", me);
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 