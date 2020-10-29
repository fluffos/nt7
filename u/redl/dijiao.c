// This program is a part of NITAN MudLIB 
// redl 2012/4
#include <ansi.h> 
#include <room.h> 
inherit ROOM; 

void create() 
{ 
                set("short", "地窖"); 
                set("long", 
                                                        "这里阴凉透气，是保鲜食品和储藏美酒的好地方。\n"
                ); 
                                
                                set("objects", ([ 
                                        "/clone/food/baijiu" : 1, 
                                        "/clone/food/guihua-jiudai" : 1, 
                                        "/clone/food/huadiao-jiudai" : 1, 
                                        "/clone/food/jiunang" : 1, 
                                        "/clone/food/niupi-jiudai" : 1, 
                                        "/clone/food/dishes/cup" : 1, 
                                        "/clone/medicine/nostrum/shenyangjiu" : 1, 
                                        "/d/huanggong/obj/nverhong" : 1, 
                                        "/d/penglai/obj/qingmeijiu" : 1, 
                                        "/d/xiakedao/obj/hulu1" : 1, 
                                        "/d/yuanyue/obj/bottle" : 1, 
                                        "/d/city/npc/obj/zui" : 1, 
                                        "/d/xingxiu/npc/obj/hu" : 1, 
                                        "/d/yueyang/npc/obj/guishejiu" : 1, 
                                        //"/kungfu/class/sky/obj/shenjiu" : 1, 
                                        "/clone/food/xianzhi" : 4, 
                                        "/clone/food/zongzi" : 1, 
                                        "/clone/food/zhima" : 1, 
                                        "/clone/food/xueli" : 1, 
                                        "/clone/food/xiehuang" : 1, 
                                        "/clone/food/kaoya" : 1, 
                                        "/clone/food/kaoji" : 1, 
                                        "/clone/food/grape" : 1, 
                                        "/clone/food/furong-huagu" : 1, 
                                        "/clone/food/basi-shanyao" : 1, 
                                        "/d/tangmen/obj/jiangnr" : 1, 
                                        "/clone/food/candy" : 8, 
                                ])); 

                set("exits", ([ /* sizeof() == */ 
                        "up" : __DIR__"cangku",
                ])); 

                set("no_rideto", 1);
                set("no_flyto", 1);
                setup(); 
} 


void init()
{
        object me = this_player();
        if (!query_temp("can_enterredlroom", me) && query("id", me) != "redl" && query("couple/couple_id", me) != "redl")
        {
                        message_vision(YEL "一股微风吹过，把$N吹到了室外。\n" NOR, me);
                        me->move(__DIR__"cangku");
                        return;
        }
}




