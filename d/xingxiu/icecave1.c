// Code of ShenZhou
// Ryu, 5/10/97
// wsky 2000

#include "ansi.h"
#include <room.h>


inherit ROOM;

private int blow_result(object victim);
int blow();
int do_dig();


void create()
{
        set("short", "冰洞");
        set("long", @LONG
进到冰洞里面，那洞顶上紧紧垂挂着冰锥(icicle)，长短不齐，
粗细不一；洞底下冰树丛生，千姿万态。穿行洞内，好似进了光怪陆
离的神话世界。
LONG );

         set("item_desc",([
                "icicle" : "这些冰锥长短不一，在火折照耀下散发出晶莹的光泽，你很想弹(flick)几根下来玩玩。\n",
        ]));

       set("exits", ([
                "west" : "/d/xingxiu/icecave2",
        ]));
        set("cost", 2);
        set("icicle", 100);
        set("bing_can", 7);

        setup();
}

void init()
{
        add_action("do_flick", "flick");
        add_action("do_flick", "tan");
//      add_action("do_lingwu", "lingwu");
        add_action("do_dig", "dig");
        remove_call_out("blow");
        call_out("blow",4 + random(3) );
}

int do_dig()
{
        remove_call_out("blow");
        call_out("blow",1 );
        return 1;
}


int do_flick(string arg) {
        object me;
        me = this_player();

        if( !arg || arg=="" )
                return 0;

        if (me->query_busy())
                return notify_fail("你正忙着呢。\n");

        if (query("icicle") < 1)
                return notify_fail("这里的冰锥你都够不着了。\n");

        if( query("jing", me)<30 || query("jingli", me)<30 )
                return notify_fail("你的精神不能集中。\n");

        if( arg=="icicle")
        {
        me->receive_damage("jing", 15); 
        me->receive_damage("qi", 15);
        addn("icicle", -1);
        message_vision("$N轻轻地用手指弹断了一根冰锥。\n", me);
        if (random(me->query_skill("feixing-shu", 1)) > 30){
        me->improve_skill("feixing-shu",query("int", me));

        message_vision("$N弹飞出去的冰锥撞断了另一根冰锥，乒乒乓乓乱响。\n", me);
        tell_object(me, "你似乎领悟了一层飞星术的技能。\n");
        if (me->query_skill("feixing-shu", 1) > 100)
        me->receive_damage("jing", 15);
        if (me->query_skill("feixing-shu", 1) > 150)
        me->receive_damage("jing", 15);
        }
/*
        if (query("icicle") < 1){
        remove_call_out("renew_up");
        call_out("renew_up", 100+random(200));
        }
*/
        return 1;
        }
}

int blow()
{
        object *inv = all_inventory(find_object("/d/xingxiu/icecave1"));
        object ob, me= this_player();
        int i;

        if( !this_player() || !environment(this_player()) )  return 1;
        if( base_name(environment(this_player())) !="/d/xingxiu/icecave1") return 1;

        message_vision( HIC"\n露水从洞顶流下来，慢慢地结成了冰锥。\n"NOR, this_player() );

        for ( i=0 ; i < sizeof(inv); i++)
        {
                if( query("race", inv[i]) == "人类" )
                {
                        blow_result(inv[i]);
                }
        }


        remove_call_out("blow");
        call_out( "blow",4 + random(6) );
        return 1;

}


private int blow_result(object victim)
{
        object me, fighter, room;
        int skill, exp;
        mapping fam;
        
        fam=query("family", this_player());
        me = this_player();
        room = this_object();
        exp=query("combat_exp", me);

        if( random(50)<1 && !me->is_fighting() && fam["family_name"] =="星宿派")
        {

             message_vision(HIR"$N只听见一声怒喝，从黑暗角落中钻出一人，向$N攻来。\n"NOR,me);
             fighter = new(CLASS_D("generate") + "/xxnpc.c");
             NPC_D->set_from_me(fighter, me, 110 + random(20));
             fighter->addn_temp("apply/attack",fighter->query_skill("force")*
                                             1/ 15);
             fighter->addn_temp("apply/dodge",fighter->query_skill("force")*
                                             1/ 15);
             fighter->addn_temp("apply/parry",fighter->query_skill("force")*
                                             1/ 15);
             addn_temp("apply/damage", 5+1*7, fighter);
             addn_temp("apply/unarmed_damage", 5+1*7, fighter);
             addn_temp("apply/armor", 10+1*15, fighter);
             set("player",query("id",  me), fighter);

             fighter->move(room); 
             if( !fighter->is_killing(me) ) fighter->kill_ob(me);    
        }


        if( random(victim->query_skill("force"))>45 && query("neili", victim)>20 && victim->query_skill("feixing-shu",1)>100 )
        {
                message_vision( WHT"\n$N运功抵御寒流，同时望着洞顶的冰锥，研析着暗器地奥妙！\n"NOR, victim );
                if(query("icicle")<100) addn("icicle", 1+random(6));
                addn("neili", -random(40), victim);
                victim->improve_skill("feixing-shu",query("int", me));
        }
        else
        {
                message_vision( RED"\n$N打了个冷颤！\n"NOR, victim );
                victim->receive_damage("qi", random(50));
                if(query("icicle")<100) addn("icicle", 1+random(3));
        }


        return 1;
}


/*

void renew_up()
{
        set("icicle", 100);
}
*/