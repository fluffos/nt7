// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include "lingjiu.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("裘婆婆", ({ "qiu popo", "qiu", "popo" }));
        set("long",
            "她是"+HIC"「灵鹫宫」"NOR+"九天九部中赤天部的首领.\n"+
            "她跟随童姥多年, 出生入死,饱经风霜。\n");
        
        set("title", "缥缈缝灵鹫宫");
        set("nickname", HIC "赤天部首领" NOR);
        set("gender", "女性");
        set("age", 60);
        set("shen_type",0);
        set("attitude", "peaceful");

        set("per", 21);
        set("class", "scholar");
        set("str", 20);
        set("int", 25);
        set("con", 30);
        set("dex", 30);

        set("qi", 1300);
        set("max_qi", 1300);
        set("jing", 500);
        set("max_jing", 500);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 80);
        set("level", 8);        
        set("combat_exp", 700000);
        
        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("hand",100);
        set_skill("strike", 100);
        set_skill("sword",100);

        set_skill("zhemei-shou",80);
        set_skill("liuyang-zhang",80);
        set_skill("yueying-wubu",80);
        set_skill("xiaowuxiang", 70);
        set_skill("tianyu-qijian", 70);

        map_skill("force", "xiaowuxiang");
        map_skill("strike","liuyang-zhang");
        map_skill("dodge", "yueying-wubu");
        map_skill("hand", "zhemei-shou");
        map_skill("parry", "liuyang-zhang");
           map_skill("sword", "tianyu-qijian");

        prepare_skill("strike","liuyang-zhang");
        prepare_skill("hand","zhemei-shou");
        
        create_family("灵鹫宫", 2, "首领");

        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: perform_action, "strike.zhong" :),
                (: perform_action, "hand.duo" :),
                (: perform_action, "sword.san" :),
                (: command("unwield jian") :),
                (: command("wield jian") :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
                (: command("unwield jian") :),
                (: command("wield jian") :),
            }) );
        set("master_ob",2);
        setup();
         carry_object("/clone/weapon/changjian")->wield();
         carry_object("/d/lingjiu/obj/qingyi")->wear();
        carry_object("/d/lingjiu/obj/doupeng")->wear();
        carry_object("/d/lingjiu/obj/jiudai");
        add_money("silver",25);
}
/*
void init()
{
        object me, ob;
        mapping fam;

        ::init();
        ob = this_player();
        me = this_object();
        
        if (interactive(ob) 
         && !query("no_fight", environment(ob) )
         && ((fam=query("family", ob)) && fam["family_name"] != "灵鹫宫") )
        {
                if( !query_temp("warned", ob) )
                {
                        command("say 尊主有令：外人不得进入灵鹫宫，速速离开！");
                        set_temp("warned", 1, ob);
                } else 
                if( query_temp("stay", ob)<5 )
                        addn_temp("stay", 1, ob);
                else 
                {
                        command("say 大胆狂徒，竟敢擅闯灵鹫宫！！！\n");
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob); 
                }
        }
}
*/
void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;
                
        if( query("gender", ob) == "女性" )
        {
                message_vision("冯婆婆垂目沉思片刻, 说道：“好吧, 我就收下你了。”\n",ob);
                command("recruit "+query("id", ob));
                if( query("class", ob) != "dancer" )
                        set("class", "dancer", ob);
                return;
        } else
        {
                message_vision("冯婆婆瞪着你看了半天,说道：“本宫只收女弟子！”\n",ob);
                return;
        }
}
