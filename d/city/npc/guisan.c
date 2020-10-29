// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit NPC;

int ask_tianmo();

void create()
{
        set_name("鬼三", ({ "gui san", "san", "gui" }));
        set("gender", "男性");
        set("age", 65);
        set("long", HIB"他就是神秘的鬼三。\n"NOR);
        set("combat_exp", 30000);
        set("shen_type", -1000);
        set("max_neili", 500);
        set("neili", 500);
        set_skill("force", 40);
        set("per",7);
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        set("inquiry", ([
                "天魔诀" : (: ask_tianmo:),
        ]) );
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 15);
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}
int ask_tianmo()
{
        command("say 嘿嘿,没想到啊,你小小年龄既然也知道《天魔诀》的事，好，只要小兄弟帮我找回\n         我的传家宝"HIG"寒玉萧(hanyu xiao)"CYN"老夫就带你去打天魔诀!\n"NOR);
        set_temp("search", 1, this_player());
        return 1;
}
int accept_object(object me, object obj)
{
         if( query("id", obj) == "hanyu xiao" )
        {
                command("bow"+query("id", me));
                command("say 哈哈，好好好，老夫这就带你去找《天魔诀》。");
                set_temp("search", 0, me);
                call_out("create_exit",1); 
                return 1;
        }
}

void create_exit() 
{ 
        object where,ob; 
        ob=this_object(); 
        where = environment(ob); 
        write("鬼三掀起墙上的画，揭起小木板，露出一个长方大洞。\n\n", ); 
        set("exits/enter", "/d/city/didao", where);
} 
