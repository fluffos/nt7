//zsh_dldamen.c

#include <room.h>

inherit ROOM;

void create()
{ 
        set("short", "前门");
        set("long", @LONG
这里是紫衫会大理分会所在地。紫衫会近几年侠义之举得到江湖
上众多正派人士的称赞，而邪派之人则终日惶惶。许多江湖好汉均慕
名而来，紫衫会的势力因之而得以不断发展壮大。
LONG );
        set("outdoors", "dali");
        set("exits", ([    
                "south"  :  "/d/dali/zsh_dlfh",
                "east"   :  "/d/dali/dahejiewest",
        ])); 
        set("objects", ([   
             "/d/suzhou/npc/zsh_guard" : 2,   
            ]));
               
	set("coor/x", -19150);
	set("coor/y", -6900);
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