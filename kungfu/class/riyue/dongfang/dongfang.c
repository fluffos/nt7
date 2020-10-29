#include <ansi.h>
#include <command.h>
#include "/kungfu/skill/eff_msg.h";

inherit NPC;
inherit F_MASTER;

mixed ask_kuihua();
mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();

int p, j;

void create()
{
        object ob;
	set_name(HIR "东方不败" NOR, ({ "dongfang bubai", "dongfang", "bubai" }));
	set("long", " 她就是东方不败，看起来不男不女，样子却甚为妖媚。\n");
	set("gender", "无性");
	set("age", 30);
	set("shen_type", -1);
	set("str", 51);
	set("int", 39);
	set("con", 50);
	set("dex", 62);
	
	set("max_qi", 10000);
	set("max_jing", 10000);
    set("max_jingli", 10000);
    set("jingli", 10000);
	set("max_neili", 12000);
	set("neili", 12000);
	set("jiali", 550);
	set("combat_exp", 5000000);
	set("score", 1200000);

	set_skill("force", 450);
    set_skill("parry", 450);
    set_skill("dodge", 450);
    set_skill("sword", 450);
    set_skill("unarmed", 450);
    set_skill("literate", 350);
    set_skill("martial-cognize", 400);
    set_skill("kuihua-mogong", 450);

	map_skill("force", "kuihua-mogong");
	map_skill("dodge", "kuihua-mogong");
	map_skill("unarmed", "kuihua-mogong");
	map_skill("sword", "kuihua-mogong");
        map_skill("parry", "kuihua-mogong");

	prepare_skill("unarmed", "kuihua-mogong");

	create_family("日月神教", 2, "弟子");

        set("inquiry", ([
                "杨莲亭"    :    "莲弟 ……\n",
                "任我行"    :    "哼 ……，我当初真该杀了他。\n",
                "葵花魔功"  :    (: ask_kuihua :),
                "无声无息"  :    (: ask_skill1 :),
                "无穷无尽"  :    (: ask_skill2 :),
                "无边无际"  :    (: ask_skill3 :),
                "无法无天"  :    (: ask_skill4 :),
                "毁天灭地"  :    (: ask_skill5 :),
		"分身化影"  :    (: ask_skill6 :),
                
        ]));

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "dodge.sheng" :),
		(: perform_action, "sword.bian" :),
		(: perform_action, "sword.tian" :),
		(: perform_action, "sword.qiong" :),
		(: perform_action, "sword.zhenwu" :),
                (: perform_action, "dodge.sheng" :),
                (: perform_action, "unarmed.bian" :),
                (: perform_action, "unarmed.tian" :),
                (: perform_action, "unarmed.qiong" :),
                (: perform_action, "sword.hui" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
		(: exert_function, "shield" :),
		(: exert_function, "roar" :),
	}) );

	setup();

        if (clonep())
        {
                     ob = find_object("/clone/lonely/book/kuihua-jianpu"); 
                     if (! ob) ob = load_object("/clone/lonely/book/kuihua-jianpu");
      
                     if (! environment(ob) && random(20) == 1) 
                             ob->move(this_object()); 
        }

        carry_object(__DIR__"zhen")->wield();
        carry_object(__DIR__"changpao")->wear();
}

mixed ask_kuihua()
{
        object ob = this_object();
        object me = this_player();
        int lv = me->query_skill("pixie-jian", 1);

        if( query_temp("teach_kh", me) )
        {
            command("shake");
            
            return 1;
        }
        
        if( query("gender", me) != "无性" && !query("special_skill/guimai", me) )
        {
             command("heng");
             ob->kill_ob(me);
             return 1;
        }

	if (me->query_skill("kuihua-mogong", 1))
	{
		command("heng");
		return 1;
	}
	
        if (lv < 300)
        {
             if (me->query_skill("pixie-jian", 1))
             {
                     command("say 下去好好练习，别来烦我！");
                     return 1;
             }
             command("say 滚开！就凭你也配问这个？！");
             return 1;
        }

        command("nod");
        command("heihei");
        command("say 好吧，我就传你葵花魔功，你可小心了！");
        tell_object(me, HIG "\n东方不败猛然尖啸一声，声音激荡刺耳，令人心驰神摇。你觉得胸口一震，一口鲜血喷出。\n" NOR);
        tell_object(me, HIC "然而你却无法捕捉到东方不败的动向！\n" NOR);

        set_temp("teach_kh", 1, me);

        if( query("qi", me)<2000 )
        {
              me->unconcious();
              delete_temp("teach_kh", me);
              return 1;              
        }
        
        me->receive_wound("qi",query("qi", me)/2);
        addn("neili", -(2000-lv), me);
        me->start_busy(2 + random(2));
        p=query("qi", me)*100/query("max_qi", me);
        tell_object(me, "(你" + eff_status_msg(p) + ")\n\n");
   
        j = 0;
    
    	me->start_busy(60);
    	
        remove_call_out("teach_kuihua");
        call_out("teach_kuihua", 2, me, lv);
        
        return 1;        
}

void teach_kuihua(object me, int lv)
{
        int sz;
	int qi;
	
        string* teach_words = ({
        HIG "忽然间东方不败身法陡然加快，呼啸着在你周围旋转，你感觉胸闷气短。\n" NOR,
        HIG "霎那间一道银光闪过，东方不败手中银针顿时化分为万千幻影，缠绕在你周围，你渐渐觉得头晕目眩。\n" NOR,
        HIG "渐渐地，东方不败身法越来越快，已化身为无数她的身影，东方不败尖啸一声，从不同的角度向你袭来。\n" NOR,
        HIG "东方不败长袖一拂，一道银光划过，猛然间在你眼前一亮，你顿觉得胸口刺痛无比。\n" NOR,
        });

        if (environment(me) != environment(this_object())
            || ! environment(me))
              return;

        sz = sizeof(teach_words);

        tell_object(me, teach_words[random(sz)]);
        tell_object(me, HIC "然而你却无法捕捉到东方不败的动向！\n" NOR);
        
	qi = 1400 - lv;
	if (qi < 100)qi = 100;
	
        if( query("qi", me) <= (1400-lv) )
        {
               me->unconcious();
               delete_temp("teach_kh", me);
               return;
        }

        me->receive_wound("qi", qi);
        addn("neili", -(1600-lv), me);
        p=query("qi", me)*100/query("max_qi", me);
        tell_object(me, "( 你" + eff_status_msg(p) + ")\n\n");
        j ++;

        // 能学葵花魔功了
        if (j >= 6 + random(2))
        {
              message_sort(HIW "东方不败尖啸一声，又回到了原地，似乎从未离开过。\n" NOR, me);

              message_sort(HIW "东方不败再未有任何言语，只是玩弄着自己的指甲 ……\n" NOR, me);

              if (random(10) > 7)return;
              
              write(HIM "你仔细回味刚才那惊心动魄的一幕，回想东方不败施展的各种招式，猛然间你一声长叹，"
                        "心中疑虑顿然消除 ……\n" NOR);
              if (me->can_improve_skill("force"))
                    me->improve_skill("force", 1500000);
              if (me->can_improve_skill("dodge"))
                    me->improve_skill("dodge", 1500000);
              if (me->can_improve_skill("parry"))
                    me->improve_skill("parry", 1500000);
              me->improve_skill("martial-cognize", 1500000);

	      me->set_skill("pixie-jian", 0);
              me->delete_skill("pixie-jian");
              delete_temp("teach_kh", me);

              if( query("can_perform/pixie-jian/po", me) )
                       set("can_perform/kuihua-mogong/qiong", 1, me);
              me->set_skill("kuihua-mogong", 200 + (lv - 300) / 2 );
              tell_object(me, HIG "你学会了「葵花魔功」！\n" NOR);
              
              me->save();
              
              me->interrupt_me(me);
              
              return;
        }

        remove_call_out("teach_kuihua");
        call_out("teach_kuihua", 3, me, lv);
                       
}

mixed ask_skill1()
{
        object me = this_player();
        
        if( query("gender", me) != "无性" && !query("special_skill/guimai", me) )
        {
               command("heng");
               this_object()->kill_ob(me);
               return 1;
        }
        if( query("can_perform/kuihua-mogong/sheng", me) )
        {
               command("say 我不是已经传了你这招吗？怎么又来问我！");
               return 1;
        }
        command("nod");
        command("heihei");
        tell_object(me, HIR "\n东方不败身子忽进忽退，身形诡秘异常，在你身边飘忽不定，不久又回到了原地。\n");
        command("say 看清楚了？！");
        if (me->can_improve_skill("dodge"))
              me->improve_skill("dodge", 1500000);
        if (me->can_improve_skill("kuihua-mogong"))
              me->improve_skill("kuihua-mogong", 1500000);
        me->improve_skill("martial-cognize", 1500000);

        set("can_perform/kuihua-mogong/sheng", 1, me);
        tell_object(me, HIG "你学会了「无声无息」。\n");

        return 1;
}

mixed ask_skill2()
{       
        object me = this_player();
        
        if( query("gender", me) != "无性" && !query("special_skill/guimai", me) )
        {
               command("heng");
               this_object()->kill_ob(me);
               return 1;
        }
        if( query("can_perform/kuihua-mogong/qiong", me) )
        {
               command("say 我不是已经传了你这招吗？怎么又来问我！");
               return 1;
        }
        if (me->query_skill("kuihua-mogong", 1) < 250)
        {
               command("say 你葵花魔功还不够娴熟，还不快下去多加练习。");
               return 1;
        }
      
        command("heihei");
        tell_object(me, HIR "\n东方不败尖啸一声，猛然进步欺前，一招竟直袭向虚空，速度之快，令人称奇。\n" NOR);
        command("say 看清楚了？！");
        command("say 这招精要在于快、准、狠，对于实战经验较低的人可能会一招使其毙命！");
        command("say 你下去一定要勤加练习。");

        if (me->can_improve_skill("force"))
              me->improve_skill("force", 1500000);
        if (me->can_improve_skill("kuihua-mogong"))
              me->improve_skill("kuihua-mogong", 1500000);
        me->improve_skill("martial-cognize", 1500000);

        set("can_perform/kuihua-mogong/qiong", 1, me);
        tell_object(me, HIG "你学会了「无穷无尽」。\n");

        return 1;
}

mixed ask_skill3()
{
        object me = this_player();
        
        if( query("gender", me) != "无性" && !query("special_skill/guimai", me) )
        {
               command("heng");
               this_object()->kill_ob(me);
               return 1;
        }
        if( query("can_perform/pixie-jian/po", me) )
        {
               command("say 下去好好练习吧，没事别来烦我！");
               return 1;
        }
        if (me->query_skill("kuihua-mogong", 1) < 260)
        {
               command("say 你葵花魔功还不够娴熟，还不快下去多加练习。");
               return 1;
        }      
        command("heihei");
        tell_object(me, HIR "\n东方不败一声尖啸，身体猛然旋转不定，霎那间似乎有千万根银针，齐齐卷向虚空 ……\n" NOR);
        command("say 这招威力巨大，能伤对方丹元，使其短期内不能施展任何外功！");
        command("say 你下去一定要勤加练习。");

        if (me->can_improve_skill("force"))
              me->improve_skill("force", 1500000);
        if (me->can_improve_skill("kuihua-mogong"))
              me->improve_skill("kuihua-mogong", 1500000);
        me->improve_skill("martial-cognize", 1500000);

        set("can_perform/pixie-jian/po", 1, me);
        tell_object(me, HIG "你学会了「无边无际」。\n");

        return 1;

}

mixed ask_skill4()
{
        object me = this_player();
        
        if( query("gender", me) != "无性" && !query("special_skill/guimai", me) )
        {
               command("heng");
               this_object()->kill_ob(me);
               return 1;
        }
        if( query("can_perform/kuihua-mogong/tian", me) )
        {
               command("say 我不是已经传了你这招吗？怎么又来问我！");
               return 1;
        }
        if (me->query_skill("kuihua-mogong", 1) < 220)
        {
               command("say 你葵花魔功还不够娴熟，还不快下去多加练习。");
               return 1;
        }      
        command("heihei");
        command("say 看好了！");
        tell_object(me, HIR "\n东方不败默运葵花魔功，身形变得奇快无比，接连从不同的方位向虚空攻出数招！\n" NOR);
        command("say 这招以快取胜，以快制敌。");
        command("say 你下去一定要勤加练习。");

        if (me->can_improve_skill("force"))
              me->improve_skill("force", 1500000);
        if (me->can_improve_skill("kuihua-mogong"))
              me->improve_skill("kuihua-mogong", 1500000);
        me->improve_skill("martial-cognize", 1500000);

        set("can_perform/kuihua-mogong/tian", 1, me);
        tell_object(me, HIG "你学会了「无法无天」。\n");

        return 1;
}


mixed ask_skill5()
{
        object me = this_player();
        string msg;

        if( query("gender", me) != "无性" && !query("special_skill/guimai", me) )
        {
               command("heng");
               this_object()->kill_ob(me);
               return 1;
        }
        if( query("can_perform/kuihua-mogong/hui2", me) )
        {
               command("say 我不是已经传了你这招吗？怎么又来问我！");
               return 1;
        }
        if (me->query_skill("kuihua-mogong", 1) < 320)
        {
               command("say 你葵花魔功还不够娴熟，还不快下去多加练习。");
               return 1;
        }
        if( query("max_neili", me)<4000 )
        {
               command("say 你内力修为还不足，还不快下去多加修炼。");
               return 1;
        }

        // 未学会毁天式，第一次学习
        if( !query("can_perform/kuihua-mogong/hui", me) )
        {
               command("heihei");
               msg = HIW "东方不败对$N" HIW "说道：好，既然这样我就传你葵花魔功最高境「毁天灭地」！"
                     "毁天灭地分两招，第一招「毁天式」，第二招「灭地诀」，必须要将这两招学全方能领"
                     "悟出「毁天灭地」！现在我先传你第一招「毁天式」，待你下去将此招运用得熟练了我"
                     "再传你「灭地诀」。你只要在战斗中使用 " HIR "perform sword.hui" HIW " 并且打中"
                     "对方，该招的熟练度就会提升！\n" NOR;

               message_sort(msg, me);
               tell_object(me, HIM "东方不败将「毁天式」的口诀告诉了你！\n" NOR);
               command("say 下去好好练习吧！");
               tell_object(me, HIG "你学会了「毁天式」。\n" NOR);
               set("can_perform/kuihua-mogong/hui", 1, me);
               if (me->can_improve_skill("force"))
                    me->improve_skill("force", 1500000);
               if (me->can_improve_skill("kuihua-mogong"))
                    me->improve_skill("kuihua-mogong", 1500000);
               me->improve_skill("martial-cognize", 1500000);
               
               return 1;
               
        }
        else // 准备学习灭地诀
        {
               if( query("can_perform/kuihua-mogong/hui1", me)<200 )
               {
                      command("shake");
                      command("say 你还是先将「毁天式」运用熟练了再来吧！");
                      return 1;
               }
               command("nod");
               msg = HIW "东方不败对$N" HIW "说道：不错，不错！你「毁天式」已经运用得很熟练了，该是"
                     "你学习「灭地诀」的时候了，你可看好了。猛然间东方不败身形一晃，已没了踪迹，刹"
                     "那间，你只觉得地动山摇，风起云涌，正犹豫间，东方不败已蹿至你身后，轻轻地拍了"
                     "拍你的头。\n" NOR;

               message_sort(msg, me);
               command("say 明白了？");
               command("say 下去好好练习吧！");
               tell_object(me, HIG "你学会了「灭地诀」。\n" NOR);
               set("can_perform/kuihua-mogong/hui2", 1, me);
               if (me->can_improve_skill("force"))
                    me->improve_skill("force", 1500000);
               if (me->can_improve_skill("kuihua-mogong"))
                    me->improve_skill("kuihua-mogong", 1500000);
               me->improve_skill("martial-cognize", 1500000);
               
               return 1;
        }
}

mixed ask_skill6()
{
        object me = this_player();
        
        if( query("gender", me) != "无性" && !query("special_skill/guimai", me) )
        {
               command("heng");
               this_object()->kill_ob(me);
               return 1;
        }
        if( query("can_perform/kuihua-mogong/fenshen", me) )
        {
               command("say 我不是已经传了你这招吗？怎么又来问我！");
               return 1;
        }
        if (me->query_skill("kuihua-mogong", 1) < 460)
        {
               command("say 你葵花魔功还不够娴熟，还不快下去多加练习。");
               return 1;
        }
 	if( query("max_neili", me)<6000 )
	{
                command("say 你内力修为不够，无法领会此招。\n");
		return 1;
	}
        command("heihei");
        command("say 看好了！");
        tell_object(me, HIR "\n东方不败冷笑一声，幻化出无数的身影，令你眼花缭乱，不明方向。\n" NOR);
        command("say 明白了？");

        if (me->can_improve_skill("force"))
              me->improve_skill("force", 1500000);
        if (me->can_improve_skill("dodge"))
              me->improve_skill("dodge", 1500000);
        if (me->can_improve_skill("kuihua-mogong"))
              me->improve_skill("kuihua-mogong", 1500000);
        me->improve_skill("martial-cognize", 1500000);

        set("can_perform/kuihua-mogong/fenshen", 1, me);
        tell_object(me, HIG "你学会了「分身化影」。\n");

        return 1;
}

void unconcious()
{
        ::die();
}