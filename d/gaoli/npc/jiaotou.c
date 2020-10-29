// 大唐双龙传
//jiaotou.c 
 
inherit NPC;

void create()
{
        set_name("教头", ({ "jiaotou" }));
        set("age", 28+random(10));
        set("gender", "男性");
        set("attitude", "peaceful");
   set("str", 20);
        set("combat_exp", 18000);
   set("max_qi", 600);
   set("max_mana", 400);
   set("max_jing", 600);
   set("max_neili", 400);
   set("neili", 400);
   set("force_factor", 20);
        set_skill("unarmed", 110);
        set_skill("dodge", 110);
        set_skill("parry", 110);
        set_skill("blade", 110);
        set_skill("force", 110);

        setup();
        carry_object("/d/gaoli/obj/cloth")->wear();
}
