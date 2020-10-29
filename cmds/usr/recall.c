// recall.c
// created by lonely@nitan2

#include <ansi.h>
inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
        string file;
        string str;
        object ob;
        object dtling;
 
        if (! environment(me)) 
                return 0; 

        if (! arg || (arg != "back" && arg != "dt" && 
            arg != "home" && sscanf(arg, "%s %s", arg, str) != 2))
                return help(me);
                               
        if (me->is_busy())
                return notify_fail("你正忙著呢。\n");

        if (me->is_fighting())
                return notify_fail("你现在正在战斗！\n"); 

        if (me->is_ghost()) 
                return notify_fail("等你还了阳再说吧。\n"); 
                
        if (me->is_in_prison())   
                return notify_fail("你正在做牢呢。\n");

        if( query("doing", me) )
                return notify_fail("你还想干什么？！\n");
                
        if( query("no_magic", environment(me)) )
                return notify_fail("你发现这里不可以进行空间穿越！\n"); 
        
        if (arg == "back" || arg == "home" || arg == "dt")
        {
                if( query_temp("warquest/party", me) )
                        return notify_fail("你还想在战争中使用？！\n");

                if (present("biao huo", me))
                        return notify_fail("你身上带著镖银，不能施展！\n");

                if( sscanf(base_name(environment(me)), "/d/register/%*s") )
                        return notify_fail("你还没有出生呢，不能施展！\n");

                if( sscanf(base_name(environment(me)), "/d/newbie/%*s") )
                        return notify_fail("你在古村中，不能施展！\n");
                
                if( arg == "back" )
                        file = "/d/city/kedian";
                else if( arg == "dt" ) {
                                dtling = query_temp("handing", me);
                                if (!dtling || query("dt_value", dtling)!=3)
                                        return notify_fail("你手里没有拿(hand)着玉质的洞天仙府令！\n");
                                if (sscanf(base_name(environment(me)),"/d/dongtian/%*s"))
                                        return notify_fail("你不能从一个洞天里跳到另一个洞天！\n");
                                file = replace_string(base_name( dtling ), "lingpai3", "") + "houshan";
                }
                else
                        file = query("private_room/entry", me);
                
                if( !file ) return notify_fail("你还没有住房呢！\n");
                
                if (base_name(environment(me)) == file)
                        return notify_fail("你已经在这里了。\n");
                        
                if (! get_object(file))
                        return notify_fail("你感觉到似乎有什么不对劲！\n");

                message("vision", NOR + me->name() + "举起" + ((arg == "dt") ? (query("name", dtling) + NOR) : "右手") + 
                                "在面前极速画了一个圆，竟划破了面前的"
                        "空间，\n只见圆内的空间真空将" + me->name() + "给吸了进去。\n" + NOR,
                        environment(me), ({me}));
                
                tell_object(me, "你从某个角落空间裂缝中钻出。\n");

                me->move(file);
                message("vision", me->name() + "从某个角落空间裂缝中钻出。\n",
                        environment(me), ({me}));

                                if (arg == "dt" && !random(6)) {
                                        message_vision(append_color(NOR "$N" NOR "手里的$n" NOR "喀喇一声碎裂散掉了...\n\n" NOR, HIY), me, dtling);
                                        destruct(dtling);
                                }

                MYGIFT_D->check_mygift(me, "newbie_mygift/recall");
                return 1;
        }
                                       
        else return help(me);
        return 1;
}

int help(object me)
{
 write(@HELP
指令格式 : recall back | home | dt
回到扬州客店的指令为 < recall back >。
回到住房的指令为 < recall home >。
回到洞天的指令为 < recall dt >。
HELP
    );
    return 1;
}




