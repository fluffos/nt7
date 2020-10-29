// This program is a part of NT MudLIB

inherit NPC;
inherit F_MASTER;

#include <ansi.h>

void create()
{
        set_name("郭襄", ({ "guo xiang", "guo", "xiang"}));
        set("long", @LONG
她就是峨嵋派的开山祖师郭襄，乃「北侠」郭
靖的二女儿，人称「小东邪」。
LONG);
        set("title", "峨嵋派开山祖师");
        set("nickname", HIY "小东邪" NOR);
        set("gender", "女性");
        set("age", 21);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "bonze");

        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("max_qi", 7000);
        set("max_jing", 6000);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 250);
        set("combat_exp", 5000000);

        set_skill("persuading", 440);
        set_skill("throwing", 460);
        set_skill("force", 420);
        set_skill("emei-xinfa", 460);
        set_skill("emei-jiuyang", 420);
        set_skill("linji-zhuang", 420);
        set_skill("dodge", 400);
        set_skill("zhutian-bu", 400);
        set_skill("finger", 400);
        set_skill("tiangang-zhi", 400);
        set_skill("hand", 400);
        set_skill("jieshou-jiushi", 300);
        set_skill("strike", 420);
        set_skill("jinding-zhang", 400);
        set_skill("piaoxue-zhang", 420);
        // set_skill("sixiang-zhang", 300);
        set_skill("sword", 420);
        set_skill("huifeng-jian", 420);
        set_skill("emei-jian", 300);
        set_skill("blade", 400);
        set_skill("yanxing-dao", 400);
        set_skill("parry", 400);
        set_skill("martial-cognize", 300);
        set_skill("literate", 480);
        set_skill("mahayana", 400);
        set_skill("buddhism", 400);
	set_skill("jingxin", 600);

        map_skill("force", "emei-jiuyang");
        map_skill("dodge", "zhutian-bu");
        map_skill("finger", "tiangang-zhi");
        map_skill("hand", "jieshou-jiushi");
        map_skill("strike", "piaoxue-zhang");
        map_skill("sword", "huifeng-jian");
        map_skill("blade", "yanxing-dao");
        map_skill("parry", "jinding-zhang");

        prepare_skill("strike", "piaoxue-zhang");

        create_family("峨嵋派", 0, "开山祖师");
        set("chat_chance", 10);
        set("chat_msg", ({
                "郭襄低声吟道：「问世间，情是何物，直教生死相许？」\n",
                "郭襄低声吟道：「天南地北双飞客，老翅几回寒暑？」\n",
                "郭襄低声吟道：「欢乐趣，离别苦，就中更有痴儿女。」\n",
                "郭襄低声吟道：「君应有语，渺万里层云，千山暮雪，只影向谁去？」\n",
                "郭襄低声吟道：「横汾路，寂寞当年箫鼓。荒烟依旧平楚。」\n",
                "郭襄低声吟道：「招魂些何嗟及，山鬼自啼风雨。」\n",
                "郭襄低声吟道：「天也妒，未信与，莺儿燕子俱黄土。」\n",
                "郭襄低声吟道：「千秋万古，为留待骚人，狂歌痛饮，来访雁丘处。」\n",
        }) );
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.yun" :),
                (: perform_action, "strike.zhao" :),
                (: exert_function, "recover" :),
                (: exert_function, "shield" :),
                (: exert_function, "powerup" :),
        }));

        setup();

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

         carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"female-cloth")->wear();
        carry_object(CLOTH_DIR"female-shoe")->wear();
        carry_object(__DIR__"obj/donkey");
}

void attempt_apprentice(object ob)
{
        command("say 我不收徒，你还是找别人吧。");
        return;
}
