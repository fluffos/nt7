///d/luoyang/npc/libai.c
//redl 2014
#include <ansi.h>
inherit NPC;

void create()
{
        set_name("李白", ({ "li bai", "li", "bai"}));
        set("long", @LONG
这便是唐朝第一大诗人李太白，只见他须垂三
尺，面如冠玉，双目炯炯有神。一手持青铜爵，
一手持长剑，正在独饮。
LONG);
        set("title", "唐朝大诗人");
        set("nickname", HIW "诗仙" NOR);
        set("gender", "男性");
        set("age", 37);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 50);
        set("int", 80);
        set("con", 50);
        set("dex", 50);
        set("per", 50);
        //set("can_learn/dugu-jiujian/nothing", 1);

        set("max_qi", 12000000000);
        set("max_jing", 8000000000);
        set("max_neili", 12000000000);
        set("neili", 12000000000);
        set("jiali", 250 + random(30000));
        set("combat_exp", 10000000000);

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: exert_function, "freeze" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));

        set_skill("dodge", 800 + random(4200));
        set_skill("parry", 800 + random(4200));
        set_skill("unarmed", 800 + random(4200));
        set_skill("sword", 800 + random(4200));
        set_skill("tangshi-jian", 800 + random(4200));
        set_skill("zuiquan-sanda", 800 + random(4200));
        set_skill("zuixian-bu", 800 + random(4200));
        set_skill("force", 800 + random(4200));
        set_skill("bingxin-jue", 800 + random(4200));
        set_skill("martial-cognize", 800 + random(4200));
        //set_skill("liquor", 500);
        set_skill("calligraphy", 500);
        set_skill("literate", 32000);
        set_skill("sword-cognize", 2000 + random(5000));
        set_skill("calligraphy", 500);

        map_skill("force", "bingxin-jue");
        map_skill("dodge", "zuixian-bu");
        map_skill("parry", "tangshi-jian");
        map_skill("sword", "tangshi-jian");
        map_skill("unarmed", "zuiquan-sanda");

        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        set_temp("handing", carry_object("/kungfu/class/sky/obj/shenjiu"));
}
