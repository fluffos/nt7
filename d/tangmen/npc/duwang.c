//duwang.c

inherit NPC;
#include <ansi.h>

void create()
{
        set_name("千年毒王", ({ "duwang", "wang" }) );
        set("race", "野兽");
        set("age", random(10));
        set("long", "它看起来更象是一只老鼠，但是浑身却没有一根毛，又和青蛙一般光滑。\n");
        set("attitude", "peaceful");
        set("str", 20);
        set("cor", 20);
        set("limbs", ({ "头部", "身体", "七寸", "尾巴" }) );
        set("verbs", ({ "bite" }) );

        set("combat_exp", 100000+random(100000));

        set_temp("apply/attack", 50+random(10));
        set_temp("apply/damage", 50+random(10));
        set_temp("apply/armor", 30+random(10));
        set_temp("apply/defence",40+random(10));
        setup();
}

void init()
{
        object me,ob;
        ::init();
        if ( interactive(me = this_player()) && living(this_object()) )
        {
                       remove_call_out("kill_ob");
                       call_out("kill_ob", 1, me);
        }
}

int hit_ob(object me, object ob, int damage)
{
        if( query("combat_exp", ob)>500000)return 1;
        if( random(damage)>query_temp("apply/armor", ob) && ob->query_condition("snake_poison")<20 )
        {
                ob->apply_condition("snake_poison", 100);
                tell_object(ob, HIG "你觉得一阵麻木的感觉自被咬中的地方慢慢传遍全身！\n" NOR );
        }
}

void die()
{
        object ob;
        message_vision("$N倒在地上，死了！\n", this_object());
//        ob = new("/d/shenlong/obj/shedan");
//        ob->move(environment(this_object()));
//        ob = new("/d/baituo/obj/shepi");
//        ob->move(environment(this_object()));
        destruct(this_object());
}