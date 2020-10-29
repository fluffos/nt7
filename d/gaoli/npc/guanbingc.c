// 大唐双龙传

//官兵


inherit NPC;

#include <ansi.h>

void create()
{
        set_name(HIY"官兵"NOR, ({ "guan bing", "bing"}) );
        set("gender", "男性");
        set("age", 35);
        set("long","这是高丽衙门的官兵，总管高丽的治安。\n");
        set("combat_exp", 300000+random(40000));
        set("attitude", "heroism");
        set("str", 30);
        set("max_qi", 1000);
        set("max_jing", 500);
        set("max_gin", 700);
        set("neili", 400);
        set("max_neili", 500);
        set("force_factor", 25);
        set_skill("blade", 300);
        set_skill("unarmed", 100);
        set_skill("parry", 100);
        set_skill("dodge", 100);
        set_skill("force", 100);

        setup();

        carry_object("/d/gaoli/obj/gangdao")->wield();
        carry_object("/d/gaoli/obj/armor")->wear();
}

