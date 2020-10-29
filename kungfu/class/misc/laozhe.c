// tanglyz

#include <ansi.h>
inherit "/inherit/char/punisher"; 

void create()
{
        set_name("唐门老者", ({ "tangmen laozhe", "tangmen", "laozhe"}));
        set("long", 
"唐门世家隐退的老者，没有人知道他的姓名。\n");
        set("gender", "男性");
        set("age", 91);
        set("class", "tangmen");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 28);
        set("max_qi", 80000);
        set("max_jingli", 15000);
        set("max_douzhi", 500);
        set("douzhi", 500);
        set("neili", 40000);
        set("max_neili", 40000);
        set("yanli",200);
        set("jiali", 100);
        set("combat_exp", 50000000);
        set("level", 15);
        set("shen",3000);
        set("score", 7000);

        set_skill("force", 2000);
        set_skill("throwing", 2000);
        set_skill("dodge", 2000);
        set_skill("parry", 2000);
        set_skill("literate", 2000);
        set_skill("hand", 2000);
        set_skill("sword", 2000);
        set_skill("boyun-suowu", 2000);
        set_skill("biyun-xinfa", 2000);
        set_skill("sanku-shengong", 2000);
        set_skill("qiulin-shiye", 2000);
        set_skill("wuzhan-mei", 2000);
        set_skill("poison", 2000);
        set_skill("medical", 2000);
        set_skill("tangmen-throwing", 2000);
        set_skill("tangmen-poison", 2000);
        set_skill("tangmen-medical", 2000);        
        
        map_skill("force", "sanku-shengong");
        map_skill("throwing", "tangmen-throwing");
        map_skill("dodge", "qiulin-shiye");
        map_skill("parry", "wuzhan-mei");
        map_skill("sword", "wuzhan-mei");
        map_skill("hand", "boyun-suowu");
        map_skill("poison", "tangmen-poison");
        map_skill("medical", "tangmen-medical");
        
        prepare_skill("hand", "boyun-suowu");
        
        create_family("唐门世家", 0, "掌门");

        set_temp("apply/damage", 100);  
        set_temp("apply/unarmed_damage", 100);  
        set_temp("apply/armor", 200);          

        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/d/tangmen/obj/feidao")->wield();
        carry_object("/d/tangmen/obj/fhshi")->wield();
        carry_object("/d/tangmen/obj/tiejili")->wield();
        carry_object("/d/tangmen/obj/feidao")->wield();
        carry_object("/d/tangmen/obj/fhshi")->wield();
        carry_object("/d/tangmen/obj/tiejili")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        set_temp("handing", carry_object("/d/tangmen/obj/jili"));          
}
