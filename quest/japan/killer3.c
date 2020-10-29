// /job/japan/killer1.c
// by akuma 8:40 PM 8/3/2003

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("东瀛武士", ({ "dongying wushi", "dongyin", "wushi", "shi" }));
        set("gender", "男性");
        set("long", "　　来自于东瀛的武官，烧杀劫略无恶不作。\n");
        set("age", random(18) + 10);
        set("str", 20 + random(10));
        set("int", 20 + random(10));
        set("con", 20 + random(10));
        set("dex", 20 + random(10));
        create_family("武士道", 4, "武士");
        // shifu("东瀛武官");
        set("chat_chance_combat", 4);
        set("chat_msg_combat", ({
                (: perform_action, "blade.slash" :),
                (: perform_action, "cuff.dao" :),
        }));
        setup();
        // if ( random(5) > 1 ) carry_object(BINGQI_D("blade"))->wield();
        //carry_object(MISC_D("cloth"))->wear();
        //carry_object(ARMOR_D("armor"))->wear();
        //carry_object(MISC_D("kuzi"))->wear();
        //carry_object(ARMOR_D("udwear/underwear"))->wear();
        add_money("silver", random(20) + 10);
        this_object()->start_call_out( (: call_other, this_object(), "dest", this_object() :), 300);
}

void init()
{
        object me, ob;

        ::init();
        ob = this_object();

        if( interactive(me=this_player()) && query_temp("job/fleet", me) && query("target", ob) == query("id", me)){
                message_vision(HIR "$N对$n说道：「グイス，プタ！」\n" NOR, ob, me);
                ob->kill_ob(me);
                me->fight_ob(ob);
                me->start_busy(1);
        }
}

int do_clone()
{
        int number;
        object ob = this_object();

        number=query("max", ob);
        if ( number < 1 ) number = 300;
        
        /*
        ob->set_skill("cuff", number);
        ob->set_skill("dodge", number);
        ob->set_skill("force", number);
        ob->set_skill("parry", number);
        ob->set_skill("blade", number);
        ob->set_skill("kongshou-dao", number);
        ob->set_skill("renshu", number);
        ob->set_skill("wushi-dao", number);
        ob->map_skill("cuff","kongshou-dao");
        ob->map_skill("dodge","kongshou-dao");
        ob->map_skill("force","renshu");
        ob->map_skill("parry","kongshou-dao");
        ob->map_skill("blade","wushi-dao");
        prepare_skill("cuff", "kongshou-dao");
        */
        return 1;
}

void dest()
{
        object me = this_object();

        if ( !me ) return;

        message_vision("$N急急忙忙离开了。\n", me);
        destruct(me);
}
