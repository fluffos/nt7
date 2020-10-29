// bangzhong.c

#include <ansi.h>;
inherit NPC;

string *duo = ({ "仁", "义", "礼", "智", "信", "勇" });
void create()
{
        int level;
        level = random(7)+1;
        set_name("丐帮弟子", ({ "gaibang dizi", "gangbang", "dizi" }));
        set("long", "这是位衣着破烂的丐帮弟子，眉目间透出股英气。\n");
        set("title", "丐帮"+chinese_number(level)+"袋弟子");
        set("gender", "男性");
        set("age", 15+level*5);
        set("attitude", "peaceful");
        set("class", "beggar");
        set("beggarlvl", 7);
        set("str", 23);
        set("int", 22);
        set("con", 18);
        set("dex", 25);

        set("max_qi", 2000*level);
        set("qi", 2000*level);
        set("max_jing", 1000*level);
        set("jing", 1000*level);
        set("neili", 1500*level);
        set("max_neili", 1500*level);
        set("jiali", 100*level);

        set("combat_exp", 3000 * level * level);

        set_skill("force", level*100);
        set_skill("huntian-qigong", level*100);
        set_skill("hand", level*100);
        set_skill("suohou-hand", level*100);
        set_skill("blade", level*100);
        set_skill("liuhe-blade", level*100);
        set_skill("dodge", level*100);
        set_skill("xiaoyaoyou", level*100);
        set_skill("parry", 700);
        set_skill("begging", 70);

        map_skill("force", "huntian-qigong");
        map_skill("blade", "liuhe-blade");
        map_skill("hand", "suohou-hand");
        map_skill("parry", "suohou-hand");
        map_skill("dodge", "xiaoyaoyou");
        prepare_skill("hand", "suohou-hand");

        set("auto_perform", 1);

        //set("party/party_name", HIC"丐帮"NOR);
        //set("party/rank", GRN+"大"+duo[random(6)]+"分舵"HIY+chinese_number(level)+"袋弟子"NOR);
        //set("party/level", level);
        create_family("丐帮", 20, "弟子");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object(WEAPON_DIR"gangdao")->wield();
}

