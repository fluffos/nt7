// 大唐双龙传
//guanjia.c 
 
inherit NPC;

void create()
{
        set_name("管家", ({ "guan jia", "guanjia" }));
        set("age", 48);
        set("gender", "男性");
        set("long","这是金府的大管家,里里外外的事大部分由他做主./n");
        set("attitude", "peaceful");
   set("str", 20);
        set("combat_exp", 200000);
   set("max_qi", 1400);
   set("max_mana", 1200);
   set("max_jing", 1400);
   set("max_neili", 1200);
   set("neili", 200);
   set("force_factor", 100);
        set_skill("unarmed", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("force", 100);

        setup();
        carry_object("/d/gaoli/obj/pao2")->wear();
}
