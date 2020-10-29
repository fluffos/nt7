// This program is a part of NITAN MudLIB 
// redl 2012/12/1 
///clone/medicine/guiyuan.c
//解决新人追问在南贤后无法full，和task面对上古妖王的危险

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(CYN "临" HIK "寂" NOR CYN "归元丹" NOR, ({"guiyuan dan", "dan", "guiyuan", "linji"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "炼自沈芝毓传授的救命神丹，效果奇妙无比（可以预先服用有备无患）。\n");
                set("base_unit", "颗");
                set("base_value", 80000);
                set("base_weight", 200);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ 
                                    "dangui"   : 3,
                                    "lurong"   : 3,
                                    "yjhua"    : 3,
                                    "honghua"  : 2,
                                    "taoxian"  : 1,
                                    "zzfen"    : 3,
                                    "dahuang"   : 2,
                                    "moyao"    : 2,
                                    "heshouwu" : 3,
                                    "renshen"  : 5,
                                    "shengdi"  : 3 ]),
                        "neili" : 1500,
                        "jing"  : 350,
                        "time"  : 15,
                        "min_level" : 400,
                        "medical" : 600,
                        //"alchemy" : 1900,
                        "liandan-shu" : 800,
                ]));
        }
        setup();
}

void call_full(object me)
{
    mapping my;

    addn("call_time", -1);
    if (query("call_time")<1) {
        write(YEL + "你藏在舌下的" + name() + NOR + YEL + "已经悄悄融化了...\n" + NOR);
        add_amount(-1); 
        if (query_amount() < 1) destruct(this_object()); 
        return;
    }
    
    addn("jingli", -(3+random(3)), me);//消耗3~5精力维持
    if (query("jingli", me)<100) {
        write(YEL + "你精力不济，咬碎了藏在舌下的" + name() + NOR + YEL + "...\n" + NOR);
        add_amount(-1); 
        if (query_amount() < 1) destruct(this_object()); 
        return;
    }
    
    if (environment(this_object())!=me) {//drop或者give,sell等
        tell_object(me, YEL + "你放弃的" + name() + NOR + YEL + "已经悄悄融化了...\n" + NOR );
        add_amount(-1); 
        if (query_amount() < 1) destruct(this_object()); 
        return;
        }
    
        my = me->query_entire_dbase();
        if (my["jing"]<my["max_jing"]/4 || my["qi"]<my["max_qi"]/4) {
                my["jing"]   = my["eff_jing"]   = my["max_jing"]; 
                my["qi"]     = my["eff_qi"]     = my["max_qi"]; 
                if (my["neili"]<my["max_neili"]/2) my["neili"] = my["max_neili"] /2;//只补50%内力，不补精力
                message_vision(HIG + "$N" + HIG + "咬舌一声轻叱，吞下一颗"+NOR+name()+HIG+"，气定神闲之极。\n" + NOR, me);
        add_amount(-1); 
        if (query_amount() < 1) destruct(this_object()); 
        return;
    }
        call_out("call_full", 1, me);
        return;
}

int do_effect(object me)
{
                int t = time()-query_temp("last_eat/guiyuan", me);
        if( t < 240 )
        {
                write("你刚服用过临寂归元丹，需"+chinese_number( 240 -t)+"秒以后才能再次服用。\n");
                return 1;
        }
        if (query("jingli", me)<500) {
                        write(YEL + "你精力不济，无法服用" + name() + NOR + YEL + "...\n" + NOR);
                return 1;
        }

        set_temp("last_eat/guiyuan", time(), me);

        me->start_busy(3);
        message_vision(YEL + "$N" + YEL + "将一颗" + name() + NOR + YEL "取出来轻轻放进嘴里，悄悄含在舌下。\n" + NOR, me);
                       
        remove_call_out("call_full");
        set("call_time", 190 + random(10));
        call_out("call_full", 1, me);
        return 1;
}

