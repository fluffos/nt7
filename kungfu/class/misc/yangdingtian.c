// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// zhangwuji.c

#include <ansi.h>
inherit "/inherit/char/punisher"; 

void create()
{
        seteuid(getuid());
        set_name("阳顶天", ({ "yang dingtian", "yang", "dingtian" }));
        set("long", @LONG
明教三十三代教主，一身武功非常了得。
LONG );
        set("title",HIG "明教" HIM " 教主" NOR);
        set("gender", "男性");
        set("age", 20);
        set("no_get", 1);
        set("shen_type",1);
        set("attitude", "friendly");
        set("class", "fighter");

        set("str", 33);
        set("int", 35);
        set("con", 38);
        set("dex", 33);

        set("qi", 58000);
        set("max_qi", 58000);
        set("jing", 27000);
        set("max_jing", 27000);
        set("neili", 80000);
        set("max_neili", 80000);
        set("jiali", 120);
        set("level", 50);
        set("combat_exp", 69000000);
        set("score", 455000);
        set("book_count", 1);
    
        set_skill("force", 2500);
        set_skill("unarmed", 2500);
        set_skill("dodge", 2500);
        set_skill("parry", 2500);
        set_skill("cuff", 2500);
        set_skill("sword", 2500);
        set_skill("blade", 2500);
        set_skill("strike", 2500);
        set_skill("claw", 2500);
        set_skill("throwing", 2500);
        // set_skill("duoming-jinhua", 2500);
        set_skill("jiuyang-shengong", 2500);
        set_skill("shenghuo-shengong", 2500);
        set_skill("qingfu-shenfa", 2500);     
        set_skill("qiankun-danuoyi", 2500);
        set_skill("qishang-quan", 2500);
        set_skill("taiji-quan", 2500);
        set_skill("taiji-jian", 2500);
        set_skill("taiji-dao", 2500);
        set_skill("lieyan-dao", 2500);
        set_skill("liehuo-jian", 2500);  
        // set_skill("yingzhua-shou", 2500);   
        // set_skill("hanbing-mianzhang", 2500);   
        set_skill("shenghuo-ling", 2500);
        set_skill("medical", 2500);
        set_skill("literate", 2500);          
        set_skill("martial-cognize", 2500);      

        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "qingfu-shenfa");
        map_skill("unarmed", "jiuyang-shengong");
        map_skill("cuff", "qishang-quan");
        map_skill("sword","shenghuo-ling");
        map_skill("parry","qiankun-danuoyi");
        map_skill("blade","taiji-dao");
        // map_skill("claw", "yingzhua-shou");
        // map_skill("throwing", "duoming-jinhua");
        // map_skill("strike", "hanbing-mianzhang");
        
        prepare_skill("cuff", "qishang-quan");

        create_family("明教", 33, "教主");


        set("chat_chance_combat", 120); 
        set("chat_msg_combat", ({
                (: command("perform sword.hua") :),
                (: command("perform sword.xi") :),
                (: command("perform sword.lian") :),
                (: command("perform sword.can") :),
                (: command("perform cuff.shang") :),
                (: command("perform cuff.fei") :),
                (: command("yun shield") :),
                (: command("yun powerup") :),
                (: command("yun recover") :),
        }) );
        
        set_temp("apply/attack", 180);
        set_temp("apply/damage", 180);
        set_temp("apply/unarmed_damage", 180);
        set_temp("apply/armor", 180);

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/gangjian")->wield();
        // carry_object("/clone/book/shenghuo-ling");
        add_money("silver",70);
}
