// xiaofei.c

inherit NPC;
#include <ansi.h>
void create()
{
        set_name("萧飞", ({ "xiao fei", "xiao" }));
        set("title","金牛武馆教习");
        set("long", "萧教头是武馆的新来教习，但他的弟子也有在江湖出头的了。\n");
        set("gender", "男性");
        set("age", 35);

        set_skill("dodge", 80);
        set_skill("force", 80);
        set_skill("parry", 80);
        set_skill("finger", 80);
        set_skill("throwing", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 80);
        set_temp("apply/damage", 20);

        set("combat_exp", 400000);
        set("shen_type", 1);
        setup();

}

int recognize_apprentice(object ob)
{
        if( !query_temp("marks/jinniu_paied", ob) == 1)return 0;
        return 1;
}