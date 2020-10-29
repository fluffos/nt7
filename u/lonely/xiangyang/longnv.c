inherit NPC;

void random_move();

void create()
{
        object ob;

        set_name("小龙女", ({ "xiao longnv", "xiao", "longnv" }));
        set("gender", "女性");
        set("age", 22);
        set("long", @LONG
她一生爱穿白衣，当真如风拂玉树，雪裹琼苞，
兼之生性清冷，实当得起“冷浸溶溶月”的形
容。
LONG);
        set("attitude", "friendly");
        set("str", 21);
        set("int", 30);
        set("con", 25);
        set("dex", 26);
        set("per", 29);
        set("shen_type", 1);

        set("qi", 300000);
        set("max_qi", 300000);
        set("jing", 200000);
        set("max_jing", 200000);
        set("neili", 100000);
        set("max_neili", 100000);
        set("jiali", 300);

        set("combat_exp", 300000000);

        set_skill("force", 600);
        set_skill("suxin-jue", 600);
        set_skill("yunv-xinjing", 600);
        set_skill("sword", 600);
        set_skill("yunv-jian", 600);
        set_skill("suxin-jian", 600);
        set_skill("quanzhen-jian", 600);
        set_skill("whip", 600);
        set_skill("yinsuo-jinling", 600);
        set_skill("dodge", 600);
        set_skill("yunv-shenfa", 600);
        set_skill("parry", 600);
        set_skill("unarmed", 600);
        set_skill("meinv-quan", 600);
        set_skill("strike", 600);
        set_skill("tianluo-diwang", 600);
        set_skill("zuoyou-hubo", 600);
        set_skill("literate", 600);
        set_skill("throwing", 600);
        set_skill("yufeng-zhen", 600);
                set_skill("taishang-wangqing", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "yunv-xinjing");
        map_skill("whip", "yinsuo-jinling");
        map_skill("sword", "suxin-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("parry", "meinv-quan");
        map_skill("unarmed", "meinv-quan");
        map_skill("strike", "tianluo-diwang");
        map_skill("throwing", "yufeng-zhen");

        prepare_skill("strike", "tianluo-diwang");
        prepare_skill("unarmed", "meinv-quan");

        create_family("古墓派", 3, "弟子");


        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("chat_msg", ({ (: random_move :) }));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform strike.wang and unarmed.you") :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: perform_action, "whip.feng twice" :),
        }) );

        setup();
        if (clonep())
        {
                
                ob = new("/clone/weapon/changbian");
                ob->move(this_object());
                ob->wield();
        }
        carry_object("/clone/cloth/baipao")->wear();

}

void unconcious()
{
        object ob;

        ob = query("mate");
        if (objectp(ob))ob->die_msg();
        
        die();
}

void die_msg()
{
        command("chat 过儿 ……");
        destruct(this_object());
}

void random_move()
{
        string dir;
        string route;
        object env;

        if (query_temp("dest_now"))
        {
                destruct(this_object());
                return;
        }

        if (XYWAR_D->dest_status() == 1)
        {
                set_temp("dest_now", 1);
        }
}
