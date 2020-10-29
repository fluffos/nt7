#include <room.h>

inherit ROOM;

void create()
{ 
        set("short", "大  门");
        set("long", @LONG
这里是侠义盟襄阳总部的大门，一面大旗迎风招展，上书『锄恶
务尽』四个大字。
LONG );
        set("outdoors", "yangzhou");
        set("exits", ([
                "west" :  __DIR__"jiekou2",
                "north" : __DIR__"xym_dating",
        ])); 
        set("objects", ([   
             __DIR__"npc/xym_guard" : 2,   
            ]));
               
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
