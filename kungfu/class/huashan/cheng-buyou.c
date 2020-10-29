// This program is a part of NITAN MudLIB
// cheng-buyou.c  成不忧

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

mixed learn_kuangfeng();

void create()
{
        set_name("成不忧", ({ "cheng buyou", "cheng" }) );
        set("gender", "男性");
        set("class", "swordsman");
        set("title", "华山剑宗第十三代弟子");
        set("age", 41);
        set("long", "一个白净面皮的矮子，眼神却异常锐利。\n");
        set("attitude", "peaceful");
        set("str", 26);
        set("int", 24);
        set("con", 23);
        set("dex", 27);
        set("max_qi", 5800);
        set("max_jing", 2400);
        set("neili", 6600);
        set("max_neili", 6600);
        set("jiali", 120);
        set("level", 20);
        set("combat_exp", 3000000);
        set("shen_type", -1);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.long" :),
                (: perform_action, "sword.xian" :),
                (: perform_action, "strike.piao" :),
                (: perform_action, "cuff.song" :),
                (: exert_function, "recover" :),
        }) );

        set_skill("unarmed", 240);
        set_skill("cuff", 240);
        set_skill("strike", 240);
        set_skill("hunyuan-zhang", 240);
        set_skill("sword", 280);
        set_skill("force", 200);
        set_skill("parry", 280);
        set_skill("dodge", 240);
        set_skill("literate", 150);
        set_skill("huashan-sword", 280);
        set_skill("huashan-quan", 240);
        set_skill("kuangfeng-jian", 380);
        set_skill("huashan-neigong", 200);
        set_skill("poyu-quan", 200);
        set_skill("huashan-shenfa", 240);
        set_skill("martial-cognize", 220);

        map_skill("sword", "huashan-sword");
        map_skill("parry", "huashan-sword");
        map_skill("force", "huashan-neigong");
        map_skill("strike", "hunyuan-zhang");
        map_skill("unarmed", "huashan-quan");
        map_skill("cuff", "poyu-quan");
        map_skill("dodge", "huashan-shenfa");

        prepare_skill("strike", "hunyuan-zhang");
        prepare_skill("cuff", "poyu-quan");

        create_family("华山剑宗", 13, "弟子");

        set("inquiry", ([
                "岳不群"         : "哼，手下败将还敢自称什么君子剑！\n",
                "夺命连环三仙剑" : "如果你想学的话可以找我封师哥。\n",
                "剑宗"           : "我就是华山剑宗传人！\n",
                "狂风快剑"       : (: learn_kuangfeng :),
        ]));

        set_temp("apply/attack", 220);
        set_temp("apply/defense", 220);
        set_temp("apply/damage", 200);
        set_temp("apply/unarmed_damage", 200);

        set("master_ob",3);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob=this_player()) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (!ob) return;
        if( !ob->query_family() || query("family/master_id", ob) != "yuebuqun" )
              say ("成不忧说：这位" + RANK_D->query_respect(ob) + "，来投我剑宗吧。\n");
        else
        {
              message_vision("成不忧一见$N就大怒：我最讨厌伪君子的徒弟了。\n", ob);
              this_object()->kill_ob(ob);
        }
        return;
}

void attempt_apprentice(object ob)
{
        command("say 老夫从不收徒，你找我封师兄好了。");
}

int accept_ask(object me, string topic)
{
        if( query("family/family_name", me) != "华山剑宗" )
                return 0;

        switch (topic)
        {
        case "天外飞龙" :
                if( query("max_neili", me)>100000 || me->query_skill("force")>1000 )
                {
                      command("shake");
                      command("say 我剑宗以剑术为主，气为次！你的内功修为已入了气宗歧途，再不能修炼剑宗剑术。");
                      return 1;
                }
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huashan-sword/long",
                           "name"    : "天外飞龙",
                           "sk1"     : "huashan-sword",
                           "gongxian": 700,
                           "lv1"     : 150,
                           "force"   : 150, ]));
                break;

        case "风扫落叶" :
                if( query("max_neili", me)>200000 || me->query_skill("force")>1000 )
                {
                      command("shake");
                      command("say 我剑宗以剑术为主，气为次！你的内功修为已入了气宗歧途，再不能修炼剑宗剑术。");
                      return 1;
                }
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuangfeng-jian/sao",
                           "name"    : "风扫落叶",
                           "sk1"     : "kuangfeng-jian",
                           "lv1"     : 100,
                           "gongxian": 600,
                           "sk2"     : "dodge",
                           "lv2"     : 100, ]));
                break;

        case "天外狂龙" :
                if( query("max_neili", me)>200000 || me->query_skill("force")>1000 )
                {
                      command("shake");
                      command("say 我剑宗以剑术为主，气为次！你的内功修为已入了气宗歧途，再不能修炼剑宗剑术。");
                      return 1;
                }
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuangfeng-jian/kuang",
                           "name"    : "天外狂龙",
                           "sk1"     : "kuangfeng-jian",
                           "lv1"     : 100,
                           "gongxian": 800,
                           "sk2"     : "dodge",
                           "lv2"     : 100, ]));
                break;

        default:
                return 0;
        }
}

mixed learn_kuangfeng()
{
        object me = this_player();
        int lv;

        if( query("family/family_name", me) != "华山剑宗" )
                return "你我毫无瓜葛，何出此言？\n";

   if( me->query_skill("kuangfeng-jian",1) || query("mark_kuangfeng-jian", me) )
                return "我该教的都已经教你了，剩下的就靠你勤加练习了！\n";

        if( query("max_neili", me)>200000 || me->query_skill("force")>1000 )
        {
                command("shake");
                command("say 我剑宗以剑术为主，气为次！你的内功修为已入了气宗歧途，再不能修炼剑宗剑术。");
                command("say 你还是请回吧！");
                return 1;
        }

        if (me->query_skill("sword", 1) < 120)
              return "你基本剑法修为不足，无法学习狂风快剑！\n";

        if (me->query_skill("dodge") < 180)
              return "你轻功修为不足，无法学习狂风快剑！\n";

        command("nod");
        command("say 既然这样老夫就将狂风快剑传与你，你可看好了！");
        message_vision(HIC "$N" HIC "将「狂风快剑」从头到尾给$n" HIC "演示了一遍！\n" NOR,
                       this_object(), me);
        command("haha");
        tell_object(me, HIG "你学会了「狂风快剑」！\n" NOR);
     set("mark_kuangfeng-jian", 1, me);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("dodge"))
                me->improve_skill("dodge", 1500000);
        me->improve_skill("martial-cognize", 1500000);

        command("say 领会了多少就看你的悟性了，剩下的就靠你自己下去练习！");

        if( (lv=query("int", me)) <= 30 )
               me->set_skill("kuangfeng-jian", lv);
        else
               me->set_skill("kuangfeng-jian", 30 + (lv - 30) * 2);

        return 1;

}

/*
void unconcious()
{
        die();
}
*/
