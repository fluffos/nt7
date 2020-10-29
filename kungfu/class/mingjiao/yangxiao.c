// This program is a part of NT MudLIB

#include <ansi.h>

inherit NPC;
inherit F_COAGENT;
inherit F_MASTER;
inherit F_GUARDER;

#define JIAN "/clone/lonely/huanlingjian"

string ask_me();

void create()
{
        set_name("杨逍", ({"yang xiao","yang","xiao",}));
        set("long",
        "他是一位中年书生，身穿白布长袍。\n"
        "他相貌俊雅，只是双眉略向下垂，嘴边露出几条深深的皱纹，不免略带衰老凄苦\n"
        "之相。他不言不动，神色漠然，似乎心驰远方，正在想什么事情。\n"
        );

        set("title",HIG "明教" HIR "光明左使" NOR);
        set("level",11);
        set("gender", "男性");
        set("attitude", "peaceful");

        set("age", 42);
        set("shen_type", 1);
        set("per", 29);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 3500);
        set("max_jing", 1500);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 150);
        set("combat_exp", 1000000);
        set("score", 800000);

        set_skill("force", 220);
        set_skill("dodge", 220);
        set_skill("parry", 220);
        set_skill("sword", 220);
        set_skill("cuff", 220);
        set_skill("strike", 220);
        set_skill("literate", 220);

        set_skill("shenghuo-xinfa", 220);
        set_skill("lingxu-bu", 220);
        set_skill("shenghuo-bu", 220);
        set_skill("pili-quan", 220);
        set_skill("shenghuo-quan", 220);
        set_skill("guangming-zhang", 220);
        set_skill("liehuo-jian", 220);
        set_skill("xiaoyao-jian", 220);
        set_skill("martial-cognize", 220);

        map_skill("force", "shenghuo-xinfa");
        map_skill("dodge", "lingxu-bu");
        map_skill("strike", "guangming-zhang");
        map_skill("cuff", "shenghuo-quan");
        map_skill("parry", "xiaoyao-jian");
        map_skill("sword", "xiaoyao-jian");

        prepare_skill("cuff", "shenghuo-quan");
        prepare_skill("strike", "guangming-zhang");

        set("inquiry", ([
                "光明圣火阵"  : (: ask_me :),
                "明教圣火阵"  : (: ask_me :),
                "圣火阵"      : (: ask_me :),
        ]));

        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                (: command("perform sword.kuai") :),
                (: command("perform sword.qi") :),
                (: command("perform sword.fei") :),
                (: command("perform cuff.jin") :),
        }) );
        set_temp("apply/attack", 120);
        set_temp("apply/damage", 120);
        set_temp("apply/unarmed_damage", 120);
        set_temp("apply/armor", 120);

        set("inherit_title",HIG"明教"HIC"护教法王"NOR);
        create_family("明教", 34, "光明左使");
        set("master_ob",4);
        set("coagents", ({
                ([ "startroom" : "/d/mingjiao/dadian",
                   "id"        : "zhang wuji" ]),
        }));
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/mingjiao/obj/baipao")->wear();
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        /*
        case "醉里乾坤" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/pomopima-jian/zui",
                           "name"    : "醉里乾坤",
                           "sk1"     : "pomopima-jian",
                           "lv1"     : 120,
                           "force"   : 180,
                           "gongxian": 700,
                           "shen"    : 80000, ]));
                break;
        */
        case "飞剑诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xiaoyao-jian/fei",
                           "name"    : "飞剑诀",
                           "sk1"     : "xiaoyao-jian",
                           "lv1"     : 60,
                           "gongxian": 400,
                           "shen"    : 80000, ]));
                break;


        case "快剑诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xiaoyao-jian/kuai",
                           "name"    : "快剑诀",
                           "sk1"     : "xiaoyao-jian",
                           "lv1"     : 160,
                           "dodge"   : 260,
                           "gongxian": 680,
                           "shen"    : 85000, ]));
                break;


        case "奇剑诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xiaoyao-jian/qi",
                           "name"    : "奇剑诀",
                           "sk1"     : "xiaoyao-jian",
                           "lv1"     : 160,
                           "neili"   : 3000,
                           "gongxian": 780,
                           "shen"    : 88000, ]));
                break;


         case "幻灵剑" :
                return MASTER_D->give_item(me, this_object(),
                               (["item"     :  JIAN,
                                 "master"   :  1,
                                 "sk1"      :  "xiaoyao-jian",
                                 "lv1"      :  120,
                                 "shen"     :  80000 ]));
                  break;
        default:
                return 0;
        }
}


void init()
{
        object me,ob;
        me = this_object ();
        ob = this_player ();

        ::init();

        if (interactive(ob) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me, ob);
        }
}

#include "yangxiao.h"
