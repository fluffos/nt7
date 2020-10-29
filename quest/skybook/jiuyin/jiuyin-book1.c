// By Spiderii@ty 天赋系统
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIC"九阴真经上卷"NOR, ({ "jiuyin zhenjing", "shang juan", "book"}));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "卷");
                set("long","这是名震江湖之九阴真经的上卷。你可以研读以下的技能：\n"+
                           "道德经    (daode-jing) \n"
                           "九阴真功  (jiuyin-zhengong) \n"
                           "九阴身法  (jiuyin-shenfa) \n"
                           "玄阴剑法  (xuanyin-jian) \n"
                );
                set("treasure", 1);
                set("unique", 1);
                set("value", 0);
                set("material", "skin");
                set("no_drop", 1);
                set("no_give", 1);
                set("no_get", 1);
                set("no_steal", 1);
        }
}

void init()
{
       add_action("do_study", "read");
       add_action("do_unite", "he");
}

int do_unite(string arg)
{
	object me = this_player();
	object ob;
	if( arg ) return 0;
	if((present("shang juan", me)) && (present("xia juan", me))){
		if(me->query_skill("jiuyin-zhengong", 1) < 200
		 || me->query_skill("jiuyin-shenfa", 1) < 150
		 || me->query_skill("xuanyin-jian", 1) < 150 )
			return notify_fail("你还是将此卷读熟后再合并九阴真经上、下卷吧。\n");
		message_vision(HIY"$N将九阴真经上、下卷互相对照，重新抄录了整本九阴真经。\n"NOR,me);
		ob = new(__DIR__"book");
		ob->set("owner",me->query("id"));
		if(!me->query("quest/jiuyin1/owner"))
			log_file("quest/jiuyin",
				sprintf("%s(%s)将九阴真经上、下卷互相对照，抄录了整本九阴真经。\n",
					me->name(1),
					capitalize(getuid(me))
				),me
			);
		me->set("quest/jiuyin1/owner", 1);
		ob->move(me);
		ob =  present("xia juan", me);
		destruct(ob);
		ob =  present("shang juan", me);
		destruct(ob);
		return 1;
      }
      else
		return notify_fail("你需要上、下卷才能互相对照、参考。\n");
}

int do_study(string arg)
{
      int cost, my_skill;
      object me=this_player();
      object where = environment(me);

      if (!arg) return notify_fail("你要读什么？\n");

      if(me->is_busy())
          return notify_fail("你现在正忙着呢。\n");

      if(where->query("sleep_room")|| where->query("no_fight"))
          return notify_fail("这里你不能读书。\n");

      if( me->is_fighting() )
          return notify_fail("你无法在战斗中专心下来研读新知！\n");

      if(! me->query("quest/jiuyin1/pass"))
          return notify_fail("你从哪里偷来的九阴真经，无法研读。\n");

      if( this_object()->query("owner") != me->query("id"))
          return notify_fail("你从哪里偷来的九阴真经，无法研读。\n");

      if( !me->query_skill("literate", 1) )
          return notify_fail("你是个文盲，先学点文化(literate)吧。\n");

      if((int)me->query("potential") < 1 )
          return notify_fail("你的潜能已经用完了，再怎么读也没用。\n");

      if((int)me->query("combat_exp") < 1000000 )
          return notify_fail("你的实战经验不足，再怎么读也没用。\n");

      if( me->query_int() < 40 )
          return notify_fail("以你目前的领悟能力，还没有办法学这个技能。\n");

      cost = 40 * ( 1 + ( 35 - (int)me->query("int"))/20 );
      if (cost < 20) cost = 20;
      
      if( me->query("neili") < cost * 2 + 300)
          return notify_fail("你的内力不够，无法领会这个技能。\n");

      me->set_temp("last_damage_from", "研读高深武功，熬尽心机累");
      switch (arg) {
        case "jiuyin-zhengong":
          my_skill = me->query_skill("jiuyin-zhengong", 1);
          if( my_skill >= 200)
              return notify_fail("你觉得这经书上所写的已经太浅了，不能学到什么东西。\n");
          if( my_skill >= me->query_skill("daode-jing",1))
              return notify_fail("你道德经太浅，不能学到什么东西。\n");
          if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
              return notify_fail("也许是缺乏实战经验，你对经书上面所说的东西总是无法领会。\n");
          else
              write("你研读着有关九阴真功的技巧，似乎有些心得。\n");
        //天赋“领悟大师”影响效果：  by spiderii@ty ..lsxk想法太过变态了
        if(me->query("relife/quest/lwds")){
         if(random(100) > me->query("relife/quest/lwds")*10)
            write(HIC"你经过转世重修后，领悟到了武技万变不离其宗的道理，瞬间领悟到了九阴真功的精华所在。\n"NOR);
            me->set_skill("jiuyin-zhengong",200);
            }
          me->improve_skill("jiuyin-zhengong", ((int)me->query_skill("literate", 1)/5 + 1));
          me->receive_damage("jing", cost );
          me->add("neili", -cost * 2);
          if(me->query_skill("jiuyin-zhengong",1) < 200)
               me->add("potential", - random(2));
          break;             
        case "jiuyin-shenfa":
          my_skill = me->query_skill("jiuyin-shenfa", 1);
          if( my_skill >= 150)
              return notify_fail("你觉得这经书上所写的已经太浅了，不能学到什么东西。\n");
          if( my_skill >= me->query_skill("daode-jing",1))
              return notify_fail("你道德经太浅，不能学到什么东西。\n");
          if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
              return notify_fail("也许是缺乏实战经验，你对经书上面所说的东西总是无法领会。\n");
          else
              write("你研读着有关九阴身法的技巧，似乎有些心得。\n");
        //天赋“领悟大师”影响效果：  by spiderii@ty ..lsxk想法太过变态了
        if(me->query("relife/quest/lwds")){
         if(random(100) > me->query("relife/quest/lwds")*10)
            write(HIC"你经过转世重修后，领悟到了武技万变不离其宗的道理，瞬间领悟到了九阴身法的精华所在。\n"NOR);
            me->set_skill("jiuyin-shenfa",150);
            }
          me->improve_skill("jiuyin-shenfa", ((int)me->query_skill("literate", 1)/5+1));
          me->receive_damage("jing", cost );
          me->add("neili", -cost * 2);
          if(me->query_skill("jiuyin-shenfa",1) < 150)
               me->add("potential", - random(2));
          break;
        case "xuanyin-jian":
          my_skill = me->query_skill("xuanyin-jian", 1);
          if( my_skill >= 150)
              return notify_fail("你觉得这经书上所写的已经太浅了，不能学到什么东西。\n");
          if( my_skill >= me->query_skill("daode-jing",1))
              return notify_fail("你道德经太浅，不能学到什么东西。\n");
          if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
              return notify_fail("也许是缺乏实战经验，你对经书上面所说的东西总是无法领会。\n");
          else
              write("你研读着有关玄阴剑法的技巧，似乎有些心得。\n");
        //天赋“领悟大师”影响效果：  by spiderii@ty ..lsxk想法太过变态了
        if(me->query("relife/quest/lwds")){
         if(random(100) > me->query("relife/quest/lwds")*10)
            write(HIC"你经过转世重修后，领悟到了武技万变不离其宗的道理，瞬间领悟到了玄阴剑法的精华所在。\n"NOR);
            me->set_skill("xuanyin-jian",150);
            }

          me->improve_skill("xuanyin-jian", ((int)me->query_skill("literate", 1)/5+1));
          me->receive_damage("jing", cost );
          me->add("neili", -cost * 2);
          if(me->query_skill("xuanyin-jian",1) < 150)
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

