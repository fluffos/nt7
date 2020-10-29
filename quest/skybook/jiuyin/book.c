#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW"九阴真经"NOR, ({ "jiuyin zhenjing", "book"}));
        set_weight(1000);
        if( clonep())
               set_default_object(__FILE__);
        else {
               set("unit", "本");
               set("long", HIC"这是名震江湖之九阴真经。你可以研读以下的技能：\n"
                           HIM"九阴真功     (jiuyin-zhengong) 九阴身法    (jiuyin-shenfa) \n"
                           HIB"九阴神爪     (jiuyin-shenzhua) 九阴神掌    (jiuyin-shenzhang) \n"
                           HIY"玄阴剑法     (xuanyin-jian)    九阴银龙鞭  (yinlong-bian) \n"
                           HIG"大伏魔拳法   (dafumo-quanfa)   道德经      (daode-jing)\n"NOR
               );
               set("value", 0);
               set("unique", 1);
               set("treasure", 1);
               set("material", "paper");
               set("no_drop", 1);
               set("no_give", 1);
               set("no_get", 1);
               set("no_steal", 1);
        }
}

void init()
{
        add_action("do_study", "read" );
}

int do_study(string arg)
{
        int cost, my_skill;
        object me=this_player();
        object where = environment(me);

        if (!arg) return notify_fail("你要读什么？\n");

        if ( me->is_busy())
             return notify_fail("你现在正忙着呢。\n");

        if (where->query("sleep_room") || where->query("no_fight"))
             return notify_fail("这里你不能读书。\n");

        if( me->is_fighting())
             return notify_fail("你无法在战斗中专心下来研读新知！\n");

        if(! me->query("quest/jiuyin1/owner"))
          return notify_fail("你从哪里偷来的九阴真经，无法研读。\n");

        if( this_object()->query("owner") != me->query("id"))
          return notify_fail("你从哪里偷来的九阴真经，无法研读。\n");

        if( !me->query_skill("literate", 1) )
             return notify_fail("你是个文盲，先学点文化(literate)吧。\n");

        if( (int)me->query("potential") < 1 )
             return notify_fail("你的潜能已经用完了，再怎么读也没用。\n");

        if( (int)me->query("combat_exp") < 1000000 )
             return notify_fail("你的实战经验不足，再怎么读也没用。\n");

        if( me->query_int() < 40 )
             return notify_fail("以你目前的领悟能力，还没有办法学这个技能。\n");

        cost = 40 * ( 1 + ( 35 - (int)me->query("int"))/20 );
        if (cost < 20) cost = 20;

        if( me->query("neili") < cost * 2 + 300)
          return notify_fail("你的内力不够，无法领会这个技能。\n");
        me->set_temp("last_damage_from", "研读高深武功，熬尽心机累");

        switch (arg){
         case "jiuyin-zhengong":
              my_skill = me->query_skill("jiuyin-zhengong", 1);
              if( my_skill >= 220)
                 return notify_fail("你觉得这经书上所写的已经太浅了，不能学到什么东西。\n"); else
              if( my_skill >= me->query_skill("daode-jing",1))
                 return notify_fail("你的道德经太浅，不能学到什么东西。\n"); 
              if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                 return notify_fail("也许是缺乏实战经验，你对经书上面所说的东西总是无法领会。\n");
              else
                 write("你研读着九阴真功，似乎有些心得。\n");
              me->improve_skill("jiuyin-zhengong", ((int)me->query_skill("literate", 1)/5+1) );
              me->receive_damage("jing", cost );
              me->add("neili", -cost * 2);
              me->add("potential", - random(2));
              break;             
         case "jiuyin-shenfa":
              my_skill = me->query_skill("jiuyin-shenfa", 1);
              if( my_skill >= 200)
                 return notify_fail("你觉得这经书上所写的已经太浅了，不能学到什么东西。\n");
              if( my_skill >= me->query_skill("daode-jing",1))
                 return notify_fail("你的道德经太浅，不能学到什么东西。\n"); 
              if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                 return notify_fail("也许是缺乏实战经验，你对经书上面所说的东西总是无法领会。\n");
              else
                 write("你研读着有关九阴身法的技巧，似乎有些心得。\n");
              me->improve_skill("jiuyin-shenfa", ((int)me->query_skill("literate", 1)/5+1) );
              me->receive_damage("jing", cost );
              me->add("neili", -cost * 2);
              me->add("potential", - random(2));
              break;
         case "jiuyin-shenzhua":
              my_skill = me->query_skill("jiuyin-shenzhua", 1);
              if( my_skill >= 200)
                 return notify_fail("你觉得这经书上所写的已经太浅了，不能学到什么东西。\n");
              if( my_skill >= me->query_skill("daode-jing",1))
                 return notify_fail("你的道德经太浅，不能学到什么东西。\n");
              else if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                 return notify_fail("也许是缺乏实战经验，你对经书上面所说的东西总是无法领会。\n");
              else write("你研读着有关九阴神爪的技巧，似乎有些心得。\n");
              me->improve_skill("jiuyin-shenzhua", ((int)me->query_skill("literate", 1)/5+1) );
              me->receive_damage("jing", cost );
              me->add("neili", -cost * 2);
              me->add("potential", - random(2));
              break;             
         case "jiuyin-shenzhang":
              my_skill = me->query_skill("jiuyin-shenzhang", 1);
              if( my_skill >= 200)
                 return notify_fail("你觉得这经书上所写的已经太浅了，不能学到什么东西。\n"); else
              if( my_skill >= me->query_skill("daode-jing",1))
                 return notify_fail("你的道德经太浅，不能学到什么东西。\n"); 
              if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                 return notify_fail("也许是缺乏实战经验，你对经书上面所说的东西总是无法领会。\n");
              else write("你研读着有关九阴神掌的技巧，似乎有些心得。\n");
              me->improve_skill("jiuyin-shenzhang", ((int)me->query_skill("literate", 1)/5+1) );
              me->receive_damage("jing", cost );
              me->add("neili", -cost * 2);
              me->add("potential", - random(2));
              break;             
         case "dafumo-quan":
              my_skill = me->query_skill("dafumo-quan", 1);
              if( my_skill >= 200)
                 return notify_fail("你觉得这经书上所写的已经太浅了，不能学到什么东西。\n"); else
              if( my_skill >= me->query_skill("daode-jing",1))
                 return notify_fail("你的道德经太浅，不能学到什么东西。\n");
              if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                 return notify_fail("也许是缺乏实战经验，你对经书上面所说的东西总是无法领会。\n");
              else write("你研读着有关大伏魔拳法的技巧，似乎有些心得。\n");
              me->improve_skill("dafumo-quan", ((int)me->query_skill("literate", 1)/5+1) );
              me->receive_damage("jing", cost );
              me->add("neili", -cost * 2);
              me->add("potential", - random(2));
              break;             

         case "xuanyin-jian":
              my_skill = me->query_skill("xuanyin-jian", 1);
              if( my_skill >= 200)
                 return notify_fail("你觉得这经书上所写的已经太浅了，不能学到什么东西。\n"); else
              if( my_skill >= me->query_skill("daode-jing",1))
                 return notify_fail("你的道德经太浅，不能学到什么东西。\n");
              if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                 return notify_fail("也许是缺乏实战经验，你对经书上面所说的东西总是无法领会。\n");
              else write("你研读着有关玄阴剑法的技巧，似乎有些心得。\n");
              me->improve_skill("xuanyin-jian", ((int)me->query_skill("literate", 1)/5+1) );
              me->receive_damage("jing", cost );
              me->add("neili", -cost * 2);
              me->add("potential", - random(2));
              break;             
         case "yinlong-bian":
              my_skill = me->query_skill("yinlong-bian", 1);
              if( my_skill >= 200)
                 return notify_fail("你觉得这经书上所写的已经太浅了，不能学到什么东西。\n"); else
              if( my_skill >= me->query_skill("daode-jing",1))
                 return notify_fail("你的道德经太浅，不能学到什么东西。\n");
              if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                 return notify_fail("也许是缺乏实战经验，你对经书上面所说的东西总是无法领会。\n");
              else write("你研读着有关九阴银龙鞭的技巧，似乎有些心得。\n");
              me->improve_skill("yinlong-bian", ((int)me->query_skill("literate", 1)/5+1) );
              me->receive_damage("jing", cost );
              me->add("neili", -cost * 2);
              me->add("potential", - random(2));
              break;             
         case "daode-jing":
              my_skill = me->query_skill("daode-jing", 1);
          write("你研读着道德经，似乎有些心得。\n");
          me->improve_skill("daode-jing", ((int)me->query_skill("literate", 1)/5+5) );
          me->receive_damage("jing", cost );
          if(me->query_skill("daode-jing",1)>150)
               me->add("potential", - random(2));
          if(me->query_skill("daode-jing",1)>200)
               me->add("potential", - random(2));
          if(me->query_skill("daode-jing",1)>250)
               me->add("potential", - random(3));
          if(me->query_skill("daode-jing",1)>300)
               me->add("potential", - random(3));
         break;             
        }
        return 1;
} 
