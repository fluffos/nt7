// longnv.c 白衣少女
// by April 01/09/26

#include <ansi.h>
inherit NPC;
int ask_aoyao();

void create()
{
        object bj;

        set_name("白衣少女", ({ "baiyi girl", "girl"}));
        set("long", 
                "她披著一袭轻纱般的白衣，面容秀美绝俗。\n");
        set("gender", "女性");
        set("age", 26);
        set("attitude", "peaceful");
        set("shen_type", 1);

        set("str", 20);
        set("int", 25);
        set("con", 25);
        set("dex", 30);

        set("max_qi", 4000);
        set("max_jing", 5500);
        set("jiali", 200);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jingli",4000);
        set("eff_jingli",4000);
        set("max_jingli",4000);

        set("combat_exp", 500000);
        set("score", 5000);

        set_skill("force", 150);
        set_skill("yunv-jian", 150);
        set_skill("cuff", 150);
        set_skill("meinv-quan", 150);
        set_skill("sword", 150);
        set_skill("yunv-jian", 150);
        set_skill("finger", 150);
        set_skill("parry", 150);
        set_skill("dodge", 150);
        set_skill("yunv-shenfa", 150);
        set_skill("qufeng",150);
        set_skill("parry",150);
        set_skill("suxin-jue",150);
        set_skill("zuoyou-hubo",150);
        set_skill("throwing",150);
        set_skill("whip",150);
        set_skill("jueqing-bian",150);
        // set_skill("finger",150);
        // set_skill("suhan-zhi",150);

        map_skill("force", "yunv-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("cuff", "meinv-quan");
        map_skill("parry", "yunv-jian");
        map_skill("sword", "yunv-jian");

        prepare_skill("cuff", "meinv-quan");

        create_family("古墓派", 5, "弟子");

    set("chat_chance_combat", 50);

        set("inquiry", ([
            "配药" : (: ask_aoyao :),
            "炼药" : (: ask_aoyao :),
            "制药" : (: ask_aoyao :),
            "熬药" : (: ask_aoyao :),
        ]));

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/gumu/npc/obj/white_silk")->wear();
        
}

void init()
{
        object ob;

        ::init();
        return;
}

int ask_aoyao()
{
        object me = this_player();
        message_vision(query("name")+"向$N解释道：\n",me);
        message_vision("你先将盖子打开[open lip]，然后加入所需的药材[add **** in lu]\n",me);
        message_vision("记着适量倒一些玉蜂蜜[pour mi]，这是我古墓圣药的药引。再扣好盖子[close lip]\n",me);
        message_vision("把炭盆点燃[burn coal]，等炉火旺起来了。就可以熬药了[aoyao]。\n",me);
        message_vision("熬药时要随时控制火候，还要不停搅拌，很累人的。药熬好了之后，\n",me);
        message_vision("记得先灭了火[mie huo]再取药[qu yao]，以免被烫伤。\n",me);
        return 1;
}