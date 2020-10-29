// emei-jiuyin.c 
#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIG"九阴真经速成篇"NOR, ({ "jiuyin sucheng", "book"}));
        set_weight(5);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "卷");
                set("long", "这是名震江湖之九阴真经的速成篇。你可以研读以下的技能：\n"
                            "九阴身法       (jiuyin-shenfa) \n"
                            "九阴真功       (jiuyin-zhengong) \n"
                            "道德经         (daode-jing) \n"
                            "催心掌         (cuixin-zhang) \n"
                            "九阴银龙鞭     (yinlong-bian) \n"
                            "九阴白骨爪     (jiuyin-baiguzhua) \n"
                );
                set("treasure", 1);
                set("unique", 1);
                set("value", 0);
                set("material", "paper");
                set("no_drop", 1);
                set("no_give", 1);
                set("no_get", 1);
                set("no_steal", 1);
        }
}

void init()
{
       add_action("do_study",({"study", "du", "read"}));
}

int do_study(string arg)
{
       int cost, my_skill;
       object me=this_player();
       object where = environment(me);

       if (!arg) return notify_fail("你要读什么？\n");

       if (me->is_busy())
            return notify_fail("你现在正忙着呢。\n");

       if(where->query("sleep_room")|| where->query("no_fight"))
          return notify_fail("这里你不能读书。\n");

       if( me->is_fighting() )
            return notify_fail("你无法在战斗中专心下来研读新知！\n");

       if( !me->query_skill("literate", 1) )
            return notify_fail("你是个文盲，先学点文化(literate)吧。\n");

       if(! me->query("quest/jiuyin2/pass"))
          return notify_fail("你从哪里偷来的九阴真经，无法研读。\n");

       if( this_object()->query("owner") != me->query("id"))
          return notify_fail("你从哪里偷来的九阴真经，无法研读。\n");

       if( (int)me->query("potential") < 1 )
            return notify_fail("你的潜能已经用完了，再怎么读也没用。\n");

       if( (int)me->query("combat_exp") < 1000000 )
            return notify_fail("你的实战经验不足，再怎么读也没用。\n");

       if( me->query_int(1) < 35 )
            return notify_fail("以你目前的领悟能力，还没有办法学这个技能。\n");

       cost = 40 * ( 1 + ( 35 - (int)me->query("int"))/20 );
       if (cost < 20) cost = 20;
       me->set_temp("last_damage_from", "研读高深武功，熬尽心机累");
      
       if( me->query("neili") < cost * 2 + 300)
           return notify_fail("你的内力不够，无法领会这个技能。\n");

       switch (arg) {
         case "jiuyin-baiguzhua":
            my_skill = me->query_skill("jiuyin-baiguzhua", 1);
            if( my_skill >= 180)
                return notify_fail("你觉得这经书上所写的已经太浅了，不能学到什么东西。\n");
            if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                return notify_fail("也许是缺乏实战经验，你对经书上面所说的东西总是无法领会。\n");
            else write("你研读着有关九阴白骨爪的技巧，似乎有些心得。\n");
            me->improve_skill("jiuyin-baiguzhua", ((int)me->query_skill("literate", 1)/5+1) );
            me->receive_damage("jing", cost );
            me->add("neili", -cost * 2);
            me->add("potential", - random(2));
            break;             
         case "cuixin-zhang":
            my_skill = me->query_skill("cuixin-zhang", 1);
            if( my_skill >= 180)
                return notify_fail("你觉得这经书上所写的已经太浅了，不能学到什么东西。\n");
            if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                return notify_fail("也许是缺乏实战经验，你对经书上面所说的东西总是无法领会。\n");
            else write("你研读着有关催心掌的技巧，似乎有些心得。\n");
            me->improve_skill("cuixin-zhang", ((int)me->query_skill("literate", 1)/5+1) );
            me->add("neili", -cost * 2);
            me->receive_damage("jing", cost );
            me->add("potential", - random(2));
            break;
         case "jiuyin-shenfa":
            my_skill = me->query_skill("jiuyin-shenfa", 1);
            if( my_skill >= 180)
                return notify_fail("你觉得这经书上所写的已经太浅了，不能学到什么东西。\n");
            if( my_skill >= me->query_skill("daode-jing",1))
                return notify_fail("你的道德经太浅，不能学到什么东西。\n");
            else
            if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                return notify_fail("也许是缺乏实战经验，你对经书上面所说的东西总是无法领会。\n");
            else write("你研读着有关九阴身法的技巧，似乎有些心得。\n");
            me->improve_skill("jiuyin-shenfa", ((int)me->query_skill("literate", 1)/5+1) );
            me->add("neili", -cost * 2);
            me->receive_damage("jing", cost );
            me->add("potential", - random(2));
            break;
         case "jiuyin-zhengong":
            my_skill = me->query_skill("jiuyin-zhengong", 1);
            if( my_skill >= 180)
                return notify_fail("你觉得这经书上所写的已经太浅了，不能学到什么东西。\n");
            if( my_skill >= me->query_skill("daode-jing",1))
                return notify_fail("你的道德经太浅，不能学到什么东西。\n");
            else
            if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                return notify_fail("也许是缺乏实战经验，你对经书上面所说的东西总是无法领会。\n");
            else write("你研读着有关九阴真功的技巧，似乎有些心得。\n");
            me->improve_skill("jiuyin-zhengong", ((int)me->query_skill("literate", 1)/5+1) );
            me->add("neili", -cost * 2);
            me->receive_damage("jing", cost );
            me->add("potential", - random(2));
            break;
         case "yinlong-bian":
            my_skill = me->query_skill("yinlong-bian", 1);
            if( my_skill >= 180)
                return notify_fail("你觉得这经书上所写的已经太浅了，不能学到什么东西。\n");
            if( my_skill >= me->query_skill("daode-jing",1))
                return notify_fail("你的道德经太浅，不能学到什么东西。\n");
            else
            if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                return notify_fail("也许是缺乏实战经验，你对经书上面所说的东西总是无法领会。\n");
            else write("你研读着有关九阴银龙鞭的技巧，似乎有些心得。\n");
            me->improve_skill("yinlong-bian", ((int)me->query_skill("literate", 1)/5+1) );
            me->add("neili", -cost * 2);
            me->receive_damage("jing", cost );
            me->add("potential", - random(2));
            break;
         case "daode-jing":
            my_skill = me->query_skill("daode-jing", 1);
            if( my_skill >= 180)
                return notify_fail("你觉得这经书上所写的已经太浅了，不能学到什么东西。\n");
            write("你研读着道德经，似乎有些心得。\n");
            me->improve_skill("daode-jing", ((int)me->query_skill("literate", 1)/5+5) );
            me->receive_damage("jing", cost );
            me->add("potential", - random(2));
            break;
       }
       return 1;
}

