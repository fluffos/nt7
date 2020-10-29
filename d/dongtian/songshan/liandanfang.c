// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h> 
inherit __DIR__"normal.c"; 

void create()
{
        set("short", "炼丹房");
        set("long", 
"这是炼丹房，四周堆放着炼丹的药材，一个流光溢彩的炼丹炉耸立在中\n"
"央，炉身盘绕着九条金龙，吞吐着汩汩氤氲药香。房间里弥漫着一股散不尽\n"
"的淡青色烟雾，长时间的丹药炼制已经让这个房间充满了神秘的色彩。\n"
);
                //set("outdoors", "dongtian");
                set("exits",([ /* sizeof() == 1 */
                        "south" : __DIR__"yaopu",
                ]));

        set("objects", ([ 
                __DIR__"npc/yaotong" : 1,
                "/clone/misc/zhujingchan" : (!random(4) ? 1 : 0),
                "/clone/medicine/jiuhua" : random(2),
                "/clone/medicine/sanhuang" : random(2),
                "/clone/medicine/shengsheng" : random(2),
                "/clone/medicine/tianmo" : random(2),
        ])); 

        set("no_steal",1);
        set("no_beg",1);         
                set("no_rideto", 1);
                set("no_flyto", 1);
        set("no_drift", 1);
        set("no_sleep_room", 1); 
        set("max_carry_user" ,3);
        
        setup();
}

void init()
{
        set("zhen_type", query("zhen_type", get_object(__DIR__"guangchang")));
        set("max_carry_user", 3 + query("zhen_type") / 2);
        
        ::init();
}



