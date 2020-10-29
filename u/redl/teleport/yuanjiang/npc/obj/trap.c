// This program is a part of NITAN MudLIB 
// redl 2015/10
#include <ansi.h>
inherit ITEM;

void create() 
{ 
              set_name(NOR HIB "陷阱"NOR, ({"trap A"}) ); 
                        set_weight(100000000000);
                set("long", NOR "这是金船里的陷阱，叫人防不胜防，头疼不已。\n" NOR);
                set("unit", "个");
                set("value", 1);
                set("no_uget", 1);
                set("no_drop", 1);
                set("no_give", 1);
                set("no_sell", 1);
                set("no_get", 1);
                set("no_steal", 1);
                set("no_beg", 1);
                set("no_put", 1);
                set("no_store", 1);
                set("unique", 1);
                set("no_pawn", 1);
              setup(); 
} 

void do_trap1(object me)
{
        int dmg = 300000 + random(100000);
        if (!environment(me) || environment(me)!=environment(this_object()))    return;
        message_vision( NOR + HIB ".陷阱." HIK "嘣地一跳，一阵牛毛细针射在$N的身上流血不止。\n" NOR, me);
        me->receive_damage("qi",dmg,this_object());
        me->receive_wound("qi",dmg/2,this_object());
        COMBAT_D->report_status(me);
        if( !me->is_busy() ) me->start_busy(random(4)+1);
        call_out("do_trap1", random(3) + 1, me);
}
void do_trap2(object me)
{
        int dmg = 150000 + random(50000);
        if (!environment(me) || environment(me)!=environment(this_object()))    return;
        message_vision( NOR + HIB ".陷阱." HIK "嘣地一跳，一阵刺鼻气味熏得$N掩鼻欲呕。\n" NOR, me);
        me->receive_damage("jing",dmg,this_object());
        me->receive_wound("jing",dmg/2,this_object());
        COMBAT_D->report_status(me);
        if( !me->is_busy() ) me->start_busy(random(4)+1);
        call_out("do_trap2", random(3) + 1, me);
}
void do_trap3(object me)
{
        int dmg = 150000 + random(50000);
        if (!environment(me) || environment(me)!=environment(this_object()))    return;
        message_vision( NOR + HIB ".陷阱." HIK "嘣地一跳，地板上伸出一排铁签刺穿了$N的脚掌。\n" NOR, me);
        if( !me->is_busy() ) me->start_busy(random(6)+12);
        call_out("do_trap3", random(36) + 1, me);
}
void do_trap4(object me)
{
        int dmg = 150000 + random(50000);
        if (!environment(me) || environment(me)!=environment(this_object()))    return;
        message_vision( NOR + HIB ".陷阱." HIK "嘣地一跳，墙上一根铁管喷出一阵玄霜，把$N冻了起来。\n" NOR, me);
        me->set_freeze(45, 0);
        if( !me->is_busy() ) me->start_busy(random(4)+1);
        call_out("do_trap4", random(3) + 1, me);
}

void init()
{
        object me = this_player();
        if (!playerp(me)) return;
                switch(random(4)) {
                        case 0:
                                do_trap1(me);
                                break;
                        case 1:
                                do_trap2(me);
                                break;
                        case 2:
                                do_trap3(me);
                                break;
                        case 3:
                                do_trap4(me);
                                break;
                }
}


