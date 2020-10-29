inherit NPC;
string ask_tea();
void create()
{
        set_name("小侍童",({"xiao shitong","xiao","shitong"}));
               set("long", "他是一名十来岁大的小侍童，长得眉清目秀。\n");
        set("gender", "男性");
        set("age", 10+random(6));
        set("attitude", "friendly");
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);        
        set("score", 500);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}
