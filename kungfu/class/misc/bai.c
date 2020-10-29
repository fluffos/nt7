// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

#include <ansi.h>
//#include "xuanming.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

void create()
{
        set_name("百损道人", ({ "baisun daoren", "baisun", "daoren" }));
        set("gender", "男性");
        set("long", @LONG
他就是玄冥谷开山祖师百损道人，只见他百发飘忽，双眼神光四射，令人敬畏。
LONG);
        set("shen_type", -1);
        set("age", 72);
        set("str", 40);
        set("con", 38);
        set("int", 40);
        set("dex", 46);
        set("max_qi", 7400);
        set("max_jing", 3400);
        set("qi", 7400);
        set("jing", 3400);
        set("neili", 8500);
        set("max_neili", 8500);
        set("jiali", 250);
        set("level", 40);
        set("combat_exp", 3200000);

        set_skill("force", 420);
        set_skill("xuanming-shengong", 420);
        set_skill("dodge", 400);
        set_skill("lingxu-bu", 400);
        set_skill("strike", 420);
        set_skill("xuanming-zhang", 420);
        set_skill("parry", 420);
        set_skill("literate", 460);
        set_skill("martial-cognize", 320);

        map_skill("strike", "xuanming-zhang");
        map_skill("force",  "xuanming-shengong");
        map_skill("dodge",  "lingxu-bu");
        map_skill("parry",  "xuanming-zhang");

        prepare_skill("strike", "xuanming-zhang");

        create_family("玄冥谷", 1, "开山祖师");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.ying" :),
                (: perform_action, "strike.lang" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("inquiry", ([
                "鹿杖客"    :   "他是我爱徒。\n",
                "鹤笔翁"    :   "他是我师弟。\n",
        ]));

        set_temp("apply/attack", 120);
        set_temp("apply/damage", 120);
        set_temp("apply/unarmed_damage", 120);
        set_temp("apply/armor", 120);

        setup();

        carry_object("/clone/cloth/baipao")->wear();
}

void attempt_apprentice(object ob)
{
        tell_object(ob, "玄冥谷暂不开放。\n");
        return;

        //if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<-35000 )
        {
                command("say 哼，我百损道人从不和正道中人交往。");
                return;
        }

        if (ob->query_skill("minggu-xinfa", 1) < 160)
        {
                command("say 你冥谷心法火候不足，还是跟我徒儿多练习练习吧！");
                return ;
        }

        if (ob->query_skill("strike", 1) < 160)
        {
                command("say 你基本掌法修为还不够，以后如何学习我玄冥谷绝学玄冥神掌？");
                return ;
        }

        if( query("combat_exp", ob)<500000 )
        {
                command("say 你江湖经验还不足，还是去多闯荡一下吧！");
                return;
        }

        command("nod");
        command("say 好，好，老夫今日就收下你。");
        command("haha");
        command("recruit"+query("id", ob));
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "历练" :
        case "历炼" :
        case "锻炼" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "如影相随" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuanming-zhang/ying",
                           "name"    : "如影相随",
                           "sk1"     : "xuanming-zhang",
                           "lv1"     : 180,
                           "dodge"   : 150,
                           "free"    : 1,
                           // "gongxian": 420,
                           "shen"    : -38000, ]));
                break;

        case "只手遮天" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuanming-zhang/zhe",
                           "name"    : "只手遮天",
                           "sk1"     : "xuanming-zhang",
                           "lv1"     :  130,
                           "force"   :  180,
                           "free"    :  1,
                           // "gongxian":  580,
                           "shen"    : -43000, ]));
                break;

        case "惊涛骇浪" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuanming-zhang/lang",
                           "name"    : "惊涛骇浪",
                           "sk1"     : "xuanming-zhang",
                           "lv1"     : 180,
                           "sk2"     : "xuanming-shengong",
                           "lv2"     : 180,
                           "neili"   : 3000,
                           "free"    : 1,
                           // "gongxian": 1200,
                           "shen"    : -68000, ]));
                break;

        default:
                return 0;
        }
}

void unconcious()
{
        die();
}

int recognize_apprentice(object ob, string skill)
{
        if (ob->query_skill(skill, 1) >= 400)
        {
                command("say 够了！我就教你到这里吧，武功还是"
                        "要靠自己多研究才是！");
                return -1;
        }

        if( query_temp("can_learn/baisun/xuanming-zhang", ob) && 
            skill == "xuanming-zhang")
                return 1;

        if( query_temp("can_learn/baisun/xuanming-zhang", ob) && 
            skill == "strike")
                return 1;

        if( query_temp("can_learn/baisun/xuanming-zhang", ob) && 
            skill == "xuanming-shengong")
                return 1;

        if( query_temp("can_learn/baisun/xuanming-zhang", ob) && 
            skill == "force")
                return 1;

        if (skill == "xuanming-zhang")
        {
                message_vision("$N看了看$n，点点头道：玄冥神掌也没有什么难学的。\n",
                               this_object(), ob);
                set_temp("can_learn/baisun/xuanming-zhang", 1, ob);
                return 1;
        }

        command("say 我只懂得一点玄冥神掌，你可不要为难我。");
        return -1;
}
