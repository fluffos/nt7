// 大唐双龙传

//weishi.c 金甲卫士

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("金甲卫士", ({ "wei shi", "shi", "wei" }) );
        set("gender", "男性");
        set("age", 35);
        set("long",
"这是高丽皇宫把守宫门的卫士,身披铁甲,手拿钢刀。
他双目精光炯炯，警惕地巡视着四周的情形。\n");
        set("combat_exp", 300000+random(40000));
        set("attitude", "heroism");

        set("str", 30);
        set("max_qi", 1000);
        set("max_jing", 500);
        set("max_mana", 700);
        set("neili", 400);
        set("max_neili", 500);
        set("force_factor", 25);
        set_skill("blade", 100);
        set_skill("unarmed", 100);
        set_skill("parry", 100);
        set_skill("dodge", 100);
        set_skill("force", 100);

        setup();

        carry_object("/d/gaoli/obj/gangdao")->wield();
        carry_object("/d/gaoli/obj/armor")->wear();
}

void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) && 
                (int)ob->query_condition("killer")) {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob);
        }
}

int accept_fight(object me)
{
        message_vision("金甲卫士对$N大喝一声：你活得不耐烦了？皇宫前也敢胡闹！\n");
        me->apply_condition("killer", 100);
        kill_ob(me);
        return 1;
}

