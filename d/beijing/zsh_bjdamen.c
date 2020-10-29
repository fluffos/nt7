//zsh_bjdamen.c

#include <room.h>

inherit ROOM;

void create()
{ 
        set("short", "前门");
        set("long", @LONG
这里是紫衫会北京分会所在地。紫衫会近几年屡行侠义之事，势
力不断发展壮大，许多江湖好汉均慕名而来。
LONG );
        set("outdoors", "beijing");
        set("exits", ([
                "south"  :  "/d/beijing/zsh_bjfh",
                "north"  :  "/d/beijing/yong_3",
        ])); 
        set("objects", ([   
             "/d/beijing/npc/zsh_guard" : 2,   
            ]));
               
	set("coor/x", -2770);
	set("coor/y", 7640);
	set("coor/z", 0);
	setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "south") 
        {
           if( !query_temp("good_zsh", me) && query("bunch/bunch_name", me) != "紫衫会" )
               return notify_fail("守卫一把拦住你：“我紫衫会不欢迎外人，请回吧！”\n"); 
           else
           {
              delete_temp("good_zsh", me);
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 