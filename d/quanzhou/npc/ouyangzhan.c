// ouyangzhan.c 欧阳詹

inherit NPC;
#include <ansi.h>

void create()
{
        set_name("欧阳詹", ({ "ouyang zhan", "zhan", "ouyang" }));
        set("long",
"欧阳詹是泉州名士。\n");
        set("gender", "男性");
        set("age", 65);
        set("no_get", 1);
        set_skill("literate", 300);

        set_skill("unarmed", 80);
        set_skill("dodge", 80);
        set_skill("parry", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 80);
        set_temp("apply/damage", 20);

        set("combat_exp", 4000);
        set("shen_type", 1);
        setup();
}

int recognize_apprentice(object ob)
{
        if( !query_temp("mark/朱", ob))return 0;
        addn_temp("mark/朱", -1, ob);
        return 1;
}

int accept_object(object who, object ob)
{
//      object me = this_player();
        if( !query_temp("mark/朱", who) )
                set_temp("mark/朱", 0, who);
        if( query("money_id", ob) && ob->value() >= 1000 )
        {
                message_vision("欧阳詹同意指点$N一些读书写字的问题。\n", who);
                addn_temp("mark/朱", ob->value()/50, who);
                return 1;
        }
}