// This program is a part of NITAN MudLIB

#include <ansi.h>
#include "mojiao.h"

inherit NPC;
inherit F_MASTER;
//inherit F_QUESTER;

void create()
{
         set_name("白天羽", ({"bai tianyu", "bai", "tianyu"}));
        set("title", "魔教教主 "+HIR"万胜刀魔"NOR);
        
        set("gender", "男性");
        set("age", 60);
        set("shen_type", -1);
        
      set("long","
一位慈祥的老者，一身素布白袍，腰畔的一把刀很是奇特，刀身弯弯，柄处刻有
〖小楼一夜听春雨〗七个字。\n");
        set("attitude", "peaceful");

        set("per", 21);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 20000);
        set("max_qi", 20000);
        set("jing", 10000);
        set("max_jing", 10000);
        set("neili", 130000);
        set("max_neili", 130000);
        set("jiali", 3000);

        set("combat_exp", 350000000);
        set("score", 0);
        set_skill("force", 800);
        set_skill("moshen-xinfa", 800);
        set_skill("chiyou-kuangzhanjue", 800);
        set_skill("dodge", 800);
        set_skill("moshen-bufa", 800);
        set_skill("jiutian-xiaoyaobu", 800);
        set_skill("strike", 800);
        set_skill("moshen-zhangfa", 800);
        set_skill("cuff", 800);
        set_skill("moshen-quanfa", 800);
        set_skill("sword", 800);
        set_skill("moshen-jianfa", 800);
        set_skill("blade", 800);
        set_skill("moshen-daofa", 800);
        set_skill("moon-blade", 800);
        set_skill("parry", 800);
        set_skill("literate", 800);
        set_skill("medical", 800);
        set_skill("mojiao-medical", 800);
        set_skill("motun-tianxia", 800);
        set_skill("martial-cognize", 800);

        map_skill("force", "chiyou-kuangzhanjue");
        map_skill("dodge", "jiutian-xiaoyaobu");
        map_skill("strike", "moshen-zhangfa");
        map_skill("cuff", "moshen-quanfa");
        map_skill("sword", "moshen-jianfa");
        map_skill("blade", "moon-blade");
        map_skill("parry", "moon-blade");

        prepare_skill("strike", "moshen-zhangfa");


        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.ting" :),
                (: perform_action, "blade.yue" :),
                (: exert_function, "recover" :),
        }) );

        
        create_family("魔教", 1, "教主");
  

        set_temp("apply/attack", 280);
        set_temp("apply/damage", 280);
        set_temp("apply/unarmed_damage", 280);
        set_temp("apply/armor", 280);
                        
        set("master_ob", 5);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/kungfu/class/mojiao/obj/blade")->wield();
        add_money("silver",70);
}

void attempt_apprentice(object ob)
{
        if( query("family/family_name", ob) != "魔教" )
         {
                 command("say 你和我素无渊源，我为什么要教你武功？");
                 return;
                }
        if (! permit_recruit(ob))  return;
        if( query("combat_exp", ob)<2000000 )
        {
                command("你武功太差了，就别给我魔教丢脸了。");
                 return;
               }

        if ((int)ob->query_skill("moshen-xinfa", 1) < 400) 

        {
                command("say 本教的内功心法你还没练好，还要多下苦功才行！");
                return;
        }
      
        command("recruit "+query("id", ob));
}

int accept_ask(object me, string topic)
{
          switch (topic)
        {
        case "当时明月在" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/moon-blade/yue",
                           "name"    : "当时明月在",
                           "sk1"     : "moon-blade",
                           "lv1"     : 300,
                           "dodge"   : 300,
                           "gongxian": 1000,
                           "shen"    : -50000, ]));
                break;

        case "小楼一夜听春雨" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/moon-blade/ting",
                           "name"    : "小楼一夜听春雨",
                           "sk1"     : "moon-blade",
                           "lv1"     : 300,
                           "dodge"   : 300,
                           "gongxian": 1000,
                           "shen"    : -50000, ]));
                break;

        case "刀至上，至上刀" :
                  return MASTER_D->teach_pfm(me, this_object(),
                          ([ "perform" : "can_perform/moon-blade/dao",
                             "name"    : "刀至上，至上刀",
                             "sk1"     : "moon-blade",
                             "lv1"     : 400,
                             "dodge"   : 400,
                             "gongxian": 1000,
                             "shen"    : -50000, ]));
                  break;
        default:
                return 0;
        }

}