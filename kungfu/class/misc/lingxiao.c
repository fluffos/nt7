#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("凌霄城隐士", ({ "yin shi", "yin", "shi" }));
        set("long",  "他就是凌霄城的高手，据说长年隐藏于山中。\n");
        set("gender", "男性");
        set("age", 55);
        set("attitude", "peaceful");
      set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("class","lingxiao");
        set("max_qi", 5800);
        set("max_jing", 3000);
        set("neili", 4500);
        set("max_neili", 4500);
        set("jiali", 180);
        set("combat_exp", 4000000);

        set_skill("force", 200);
        set_skill("xueshan-neigong", 200);
        set_skill("dodge", 200);
        set_skill("taxue-wuhen", 200);
        set_skill("cuff", 180);
        set_skill("lingxiao-quan", 180);
        set_skill("strike", 180);
        set_skill("piaoxu-zhang", 180);
        set_skill("sword", 220);
        set_skill("hanmei-jian", 220);
        set_skill("yunhe-jian", 220);
        set_skill("xueshan-jian", 220);
        set_skill("parry", 200);
        set_skill("literate", 200);
        set_skill("martial-cognize", 150);

        map_skill("force", "xueshan-neigong");
        map_skill("dodge", "taxue-wuhen");
        map_skill("cuff", "lingxiao-quan");
        map_skill("strike", "piaoxu-zhang");
        map_skill("sword", "xueshan-jian");
        map_skill("parry", "yunhe-jian");

        prepare_skill("strike", "piaoxu-zhang");
        prepare_skill("cuff", "lingxiao-quan");

        create_family("凌霄城", 0, "隐士");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hui" :),
                (: perform_action, "sword.chu" :),
                (: perform_action, "cuff.jue" :),
                (: perform_action, "strike.piao" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));


        set_temp("apply/attack", 100);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

      

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/whiterobe")->wear();
}
