// This program is a part of NITAN MudLIB 
// redl 2015/2
#include <ansi.h> 
#include <room.h> 
inherit ROOM; 
void create()
{
        set("short", "天神走廊");
        set("long", 
"这条长廊优雅精致，盘龙小柱顶着一个个的盖子，连接着各个去处，一\n"
"个个的盖子上面都是一幅精美的画卷，从盘古开天，到封神之战，让人走在\n"
"这长廊之上，也能感受上古之战的地裂天崩。\n"
);
                set("exits",([ /* sizeof() == 1 */
                                "down" : "/u/redl/teleport/teleport",
                        "east" : "/u/lonely/workroom",
                          "south" : "/u/mud/workroom", 
                        "northwest" : __DIR__"workroom",
                ]));

      /*  set("no_fight",1);         
        set("no_steal",1);
        set("no_beg",1);         
        set("no_flyto", 1);*/
        set("no_drift", 1);
        setup();
}

int discmds() 
{ 
        tell_object(this_player(), "你不能在这里做这个动作。\n");  
        return -1;  
} 


void init()
{
        object me = this_player();
        
                        if (wiz_level(me) < 2) 
                                add_action("discmds", ({  
                                        "ride", "stab", /*"save", "ansuan", "touxi", 
                                        "steal", "cast", "conjure", "array", "fight", "hit",   
                                        "surrender", "exert", "team",  
                                        "array", "battle", "accept", "swear",*/
                        }));  
                

}

int valid_leave(object me, string dir)
{
        object room, *inv;
        int countp;
        
        if (wiz_level(me) < 2 && dir!="down") 
                {
                        tell_object(me, NOR "那不是你可以进去的地方。\n" NOR);  
                        return -1;      
                }
        
        return ::valid_leave(me, dir);
}

