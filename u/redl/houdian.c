// This program is a part of NITAN MudLIB 
// redl 2013/5
#include <ansi.h> 
#include <room.h> 
inherit ROOM; 


string look_picture(object me)
{
        if (query("redl/gethomerune", me)<3) {
                add_action("do_kou", "kou");
        return HIC "\n"
        
NOR MAG"╭♀︿☆╮"RED" ╭★︿♂╮" "\n"
NOR MAG"{/ ． ．\\}"RED" {/ ． ．\\}" "\n"
NOR MAG" ( (oo) ) "RED"  ( (oo) )" "\n"
NOR MAG" ︶︶︶︶ "RED"  ︶︶︶︶" "\n"

"\n" NOR "你发现画上的两头猪似乎可以抠(kou)动...\n" NOR;
        } else {
        return HIC "\n"
        
NOR MAG"╭♀︿☆╮"RED" ╭★︿♂╮" "\n"
NOR MAG"{/ ． ．\\}"RED" {/ ． ．\\}" "\n"
NOR MAG" ( (oo) ) "RED"  ( (oo) )" "\n"
NOR MAG" ︶︶︶︶ "RED"  ︶︶︶︶" "\n" NOR;
                }
}


void create()
{
        set("short", "后殿");
        set("long", 
"这里是化乐天后殿，正中壁龛上供着一副"CYN"画"NOR"。两旁墙上镶嵌了各十二\n"
"颗夜明珠，珠子状如牛眼，伸缩浮沉不定，大放光华，犹如传说中的定海\n"
"神珠。整个殿内青烟缭绕，异香扑鼻。\n"
);
//         set("outdoors", "chengdu");
        set("exits",([ /* sizeof() == 1 */
                "north" : __DIR__"private_room/houyuan",
                "south" : __DIR__"private_room/dadian",
                "east"   : __DIR__"cangku",
                                "west"   : __DIR__"prison",
        ]));

        set("item_desc", ([
                "画": (: look_picture :),
                "hua": (: look_picture :),
                "picture": (: look_picture :),
        ]) );

                set("no_rideto", 1);
                set("no_flyto", 1);
        
        setup();
}

int do_kou()
{
        object me = this_player();
        
        if (!query_temp("can_enterredlroom", me) && query("id", me) != "redl" && query("couple/couple_id", me) != "redl") return notify_fail("傀儡将军对着你嘿嘿嘿奸笑了几声。\n");
        
        if (me->is_busy()) {
                tell_object(me, "你先忙完手里的事再说吧！\n");
                return 1;
        }
        me->start_busy(1);
        
        set_temp("has_kouredlpig", random(2), me);
        
        message_vision(NOR "$N伸出食指和中指，缓缓插进" +((query_temp("has_kouredlpig", me) ? MAG+"紫猪"+NOR : RED+"红猪"+NOR))+ "的两个鼻孔里抠了抠。\n" NOR, me);
        
        if ( !query_temp("has_kouredl", me) && !random(12) ) {
                message_vision(YEL "只见画上的" +((query_temp("has_kouredlpig", me) ? MAG+"紫猪"+NOR : RED+"红猪"+NOR))+ YEL + "舒服地打了个喷嚏，噼里啪啦一堆珠宝喷在$N脸上。\n" NOR, me);
                if (random(2)) new("/clone/tessera/fdiamond")->move(me);
                if (random(2)) new("/clone/tessera/femerald")->move(me);
                if (random(2)) new("/clone/tessera/fsapphire")->move(me);
                if (random(2)) new("/clone/tessera/fruby")->move(me);
                if (random(2)) new("/clone/tessera/ftopaz")->move(me);
                set_temp("has_kouredl", 1, me);//不quit后第二次再获邀请来这里，是不能再有效果的了       
                addn("redl/gethomerune", 1, me);
                message_vision(CYN + (query_temp("has_kouredlpig", me) ? MAG+"紫猪"+NOR : RED+"红猪"+NOR) + CYN + "对著$N眨眨眼，一副「干得好！！」的神情。\n" + NOR, me);
                message_vision(CYN + (!query_temp("has_kouredlpig", me) ? MAG+"紫猪"+NOR : RED+"红猪"+NOR) + CYN + "看都不看$N一眼，哼了一声，高高的把头扬了起来。\n" + NOR, me);
        }
        return 1;
}


