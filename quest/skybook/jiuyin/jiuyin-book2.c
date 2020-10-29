// By Spiderii@ty 加入天赋
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("人皮", ({ "ren pi", "pi"}));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "张");
                set("long", "一张人皮，看不出有什么特别之处。\n");
                set("treasure", 1);
                set("unique", 1);
                set("value", 0);
                set("no_give", 1);
                set("no_get", 1);
                set("no_steal", 1);
                set("no_drop", 1);
                set("material", "skin");
        }
}

void init()
{
       if(this_player()->query("quest/jiuyin2/pass")){
         set_name(HIB"九阴真经下卷"NOR, ({ "jiuyin zhenjing", "xia juan", "book"}));
         set("unit", "卷");
         set("long", "这是名震江湖之九阴真经的下卷。你可以研读以下的技能：\n"
                     "催心掌         (cuixin-zhang) \n"
                     "九阴白骨爪     (jiuyin-baiguzhua) \n"
                     "九阴银龙鞭     (yinlong-bian) \n"
         );
         add_action("do_study", "read");
       }
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

       if(! me->query("quest/jiuyin2/pass"))
          return notify_fail("你从哪里偷来的九阴真经，无法研读。\n");

       if( this_object()->query("owner") != me->query("id"))
          return notify_fail("你从哪里偷来的九阴真经，无法研读。\n");

       if( !me->query_skill("literate", 1) )
            return notify_fail("你是个文盲，先学点文化(literate)吧。\n");

       if((int)me->query("potential") < 1 )
            return notify_fail("你的潜能已经用完了，再怎么读也没用。\n");

       if((int)me->query("combat_exp") < 1000000 )
            return notify_fail("你的实战经验不足，再怎么读也没用。\n");

       if( me->query_int() < 35 )
            return notify_fail("以你目前的领悟能力，还没有办法学这个技能。\n");

       cost = 40 * ( 1 + ( 35 - (int)me->query("int"))/20 );
       if (cost < 20) cost = 20;
      
       if( me->query("neili") < cost * 2 + 300)
          return notify_fail("你的内力不够，无法领会这个技能。\n");

       me->set_temp("last_damage_from", "研读高深武功，熬尽心机累");
       switch (arg) {
         case "jiuyin-baiguzhua":
            my_skill = me->query_skill("jiuyin-baiguzhua", 1);
            if( my_skill >= 150)
                return notify_fail("你觉得这经书上所写的已经太浅了，不能学到什么东西。\n");
        //天赋“领悟大师”影响效果：  by spiderii@ty ..lsxk想法太过变态了
        if(me->query("relife/quest/lwds")){
         if(random(100) > me->query("relife/quest/lwds")*10)
            write(HIC"你经过转世重修后，领悟到了武技万变不离其宗的道理，瞬间领悟到了九阴白骨爪的精华所在。\n"NOR);
            me->set_skill("jiuyin-baiguzhua",150);
            }
            if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                return notify_fail("也许是缺乏实战经验，你对经书上面所说的东西总是无法领会。\n");
            else
                write("你研读着有关九阴白骨爪的技巧，似乎有些心得。\n");
            me->improve_skill("jiuyin-baiguzhua", ((int)me->query_skill("literate", 1)/5+1) );
            me->receive_damage("jing", cost );
            me->add("neili", -cost * 2);
            if(me->query_skill("jiuyin-baiguzhua",1) < 150)
              me->add("potential", - random(2));
            break;             
         case "cuixin-zhang":
            my_skill = me->query_skill("cuixin-zhang", 1);
            if( my_skill >= 150)
                return notify_fail("你觉得这经书上所写的已经太浅了，不能学到什么东西。\n");
        //天赋“领悟大师”影响效果：  by spiderii@ty ..lsxk想法太过变态了
        if(me->query("relife/quest/lwds")){
         if(random(100) > me->query("relife/quest/lwds")*10)
            write(HIC"你经过转世重修后，领悟到了武技万变不离其宗的道理，瞬间领悟到了催心掌的精华所在。\n"NOR);
            me->set_skill("cuixin-zhang",150);
            }
            if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                return notify_fail("也许是缺乏实战经验，你对经书上面所说的东西总是无法领会。\n");
            else
                write("你研读着有关催心掌的技巧，似乎有些心得。\n");
            me->improve_skill("cuixin-zhang", ((int)me->query_skill("literate", 1)/5+1) );
            me->receive_damage("jing", cost );
            me->add("neili", -cost * 2);
            if(me->query_skill("cuixin-zhang",1) < 150)
               me->add("potential", - random(2));
            break;
         case "yinlong-bian":
            my_skill = me->query_skill("yinlong-bian", 1);
            if( my_skill >= 150)
                return notify_fail("你觉得这经书上所写的已经太浅了，不能学到什么东西。\n");
        //天赋“领悟大师”影响效果：  by spiderii@ty ..lsxk想法太过变态了
        if(me->query("relife/quest/lwds")){
         if(random(100) > me->query("relife/quest/lwds")*10)
            write(HIC"你经过转世重修后，领悟到了武技万变不离其宗的道理，瞬间领悟到了九阴银龙鞭的精华所在。\n"NOR);
            me->set_skill("yinlong-bian",150);
            }
            if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                return notify_fail("也许是缺乏实战经验，你对经书上面所说的东西总是无法领会。\n");
            else
                write("你研读着有关九阴银龙鞭的技巧，似乎有些心得。\n");
            me->improve_skill("yinlong-bian", ((int)me->query_skill("literate", 1)/5+1) );
            me->receive_damage("jing", cost );
            me->add("neili", -cost * 2);
            if(me->query_skill("yinlong-bian",1) < 150)
               me->add("potential", - random(2));
            break;
    }
    return 1;
}

