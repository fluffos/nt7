// fengjiang.c 玉蜂浆
// By Lgg,1998.9

#include <ansi.h>
inherit ITEM;

int decayed = 0;
void create()
{
        set_name("玉蜂浆", ({"jiang", "feng jiang"}));
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一瓶用玉蜂巢捣成的浆。\n");
                set("unit", "瓶");
                set("value", 30);
                set("only_do_effect", 1); 
                set("can_fulan",1);
        }
}

int do_effect(object me)
{
        set("jing",query("max_jing",  me), me);
        message_vision(HIY"$N服下了一瓶玉蜂浆，那玉蜂浆非常的甘甜，实在是好吃。\n"NOR,me);
        if (me->query_condition("yufengdu") > 0)
        {
                me->clear_condition("yufengdu");
                tell_object(me,HIY "你感觉体内的蜂毒已慢慢消去。\n" NOR, me);
        }
        destruct(this_object());
        return 1;
}
 void decay(int phase) 
{
        string msg;
        object env;
        env = environment();
        decayed = phase;
        set("on_fulan",1);
        set("value",0);
        set("food_remaining",0);
        switch(phase)
        {
                case 1:
                        msg =  name(1) + "开始变质了，发出一股难闻的馊味。\n";
                        set("old_name",name(1));
                        set_name("变质的" + query("old_name"),({ query("id") }));
                        call_out("decay", 120, phase + 1);
                        break;
                case 2:
                        msg = name(1) + "开始腐烂了，上面长出许多绿毛，发出难闻的臭味。\n";
                        set_name("腐烂的" + query("old_name"),({ query("id") }));
                        call_out("decay", 60, phase + 1);
                        break;
                case 3:
                        msg = "一阵风吹过，把" + name(1) + "化成灰吹散了。\n";
                        if( env )
                                all_inventory(this_object())->move(env);
                        tell_room(env, msg);
                        destruct(this_object());
                        return;
        }
        while (env && env->is_character())
                env = environment(env);
        if (env) tell_room(env, msg); 
}