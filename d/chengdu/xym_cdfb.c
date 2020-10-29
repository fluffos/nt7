#include <room.h>

inherit ROOM;

void create()
{ 
        set("short", "侠义盟前");
        set("long", @LONG
这里是侠义盟成都分部的大门前面，侠义盟的成都分部地理位置
极好，掩映在青山碧水之间。这是一幢别具风格的建筑，让人觉得一
股正气浩存于天地之间。          
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
                "west" :  __DIR__"eastroad3",
                "east" : __DIR__"xym_cddt",
        ])); 
        set("objects", ([   
             __DIR__"npc/xym-guard" : 2,   
            ]));
               
        set("coor/x", -15190);
	set("coor/y", -1840);
	set("coor/z", 0);
	setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "east") 
        {
           if( !query_temp("good_xym2", me) && query("bunch/bunch_name", me) != "侠义盟" )
               return notify_fail("守卫一把拦住你，朗声喝道：我侠义盟怎由闲杂人等随便进出。\n"); 
           else
           {
              delete_temp("good_xym2", me);
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 