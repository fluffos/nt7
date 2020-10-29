// 有机缘的话，梦回古村，重新得到下述skill的奥义 ，成为天下无敌的组合技能
inherit NPC;
inherit F_MASTER;

#include <ansi.h>

void create()
{
        set_name("武伯", ({ "wu bo", "wu", "bo" }) );
        //set("nickname", HIY "新手福星" NOR);
        set("title", HIC "武术教练" NOR);
        set("gender", "男性");
        set("age", 30);
        set("long", "这是古村的武术教练，你可以拜他为师（bai wuqing zi）学习武功。\n");
        set("attitude", "peaceful");

        set("str", 26);
        set("con", 30);
        set("int", 24);
        set("dex", 30);

        set("max_qi", 883400);
        set("max_jing", 881700);
        set("neili", 882800);
        set("max_neili", 882800);

        set("combat_exp", 1500000);
        set("score", 5000000);

        set_skill("sword", 30);
        set_skill("unarmed", 30);
        set_skill("blade", 30);
        set_skill("force", 30);
        set_skill("dodge", 30);
        set_skill("parry", 30);
        set_skill("mieshenquan", 30);
        set_skill("tianjian", 30);
        set_skill("juedao", 30);
        set_skill("xiaoyaobu", 30);
        set_skill("zhanshenjue", 30);
        set_skill("literate", 50);
        set_skill("martial-cognize", 50);

        map_skill("unarmed", "mieshenquan");
        map_skill("sword", "tianjian");
        map_skill("blade", "juedao");
        map_skill("parry", "tianjian");
        map_skill("force", "zhanshenjue");
        map_skill("dodge", "xiaoyaobu");

        set_temp("apply/damage", 100);
        set_temp("apply/armor", 100);

        set("inquiry", ([
               "老村长"   :  "他是我尊师，有什么帮助就找他。\n",
               "花伯"     :  "他是我师兄，你要出村就找他！\n",
        ]));

        create_family("古村", 1, "弟子");
        set("no_pk", 1);
	setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{

        /*
        if( query("newbie_quest/leixing", ob) != "baishi" )
        {
             command("shake");
             command("say 没有我尊师老村长的允许，我可不敢收你为徒！");
             return;
        }
        */  
              
        if( query("family", ob) )
        {
             command("yi");
             command("say 你师傅是谁？");
             return;
        }

        command("say 好吧，我就收下你了。");
        command("recruit "+query("id", ob));

        ob->save();

        return;
}

void init()
{
        tell_object(this_player(), HIG "拜师请使用指令 bai 师傅ID(bai wu bo)。\n" NOR);
        tell_object(this_player(), HIY "查看师傅技能请使用 skills 师傅ID(skills wu bo)。\n" NOR);
}

void unconcious()
{
        die();
}
