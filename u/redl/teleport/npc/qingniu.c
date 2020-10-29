//开始阅读文件：/kungfu/class/misc/houwang.c
//redl 2015/5
#include <ansi.h>
inherit NPC;

int is_niuren() { return 1;}

void heart_beat()
{
        object me = this_object();
        me->stop_busy();
        return ::heart_beat();
}


void create()
{
        set_name("青牛", ({ "qing niu", "qing", "niu" }));
        set("race", "野兽");
        set("age", 48);
        set("long", "这是一只野蛮的畜生，四蹄健壮牛角狰狞。\n");
        set("rank_info/rude", "畜生");
        set("rank_info/respect", "老牛");
        set("combat_exp", 5000000000);
        set("attitude", "heroism");
        set("str", 8000);
        set("int", 5);
        set("con", 8000);
        set("dex", 30);

        set("max_jing", 10000 * 50);
        set("jing", query("max_jing"));
        set("max_qi", 10000 * 100);
        set("qi", query("max_qi"));

        set("auto_perform", 1);
                set_heart_beat(1);
        setup();

//              carry_object("/d/emei/obj/pantao");
}

int accept_kill(object who)
{
        set("enemy_player", who);
        this_object()->kill_ob(who);
        who->kill_ob(this_object());
    return 1;//::accept_kill(who); 
}

int accept_fight(object who)
{
        return accept_kill(who); 
}

int accept_ansuan(object who)
{
        return 0; 
}

int accept_hit(object who)
{
        return accept_kill(who); 
}

void die(object killer)
{
        string prop, name;
        mapping data;
        object *obs, ob, where;
                object *enemies, *enemies2, enemy, enemy2;
                int num;

        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") )
        {
                return;
        }

    return ::die(killer);
}

void unconcious()
{
     object ob,me = this_object();
     if(!objectp(ob)) ob = me->query_last_damage_from();
     if(!objectp(ob)) ob = query_temp("last_damage_from",me);
     die(ob);
}
