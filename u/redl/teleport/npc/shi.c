// This program is a part of NITAN MudLIB 
// redl 2013/9

#include <ansi.h>

inherit NPC;

int level_up()
{
        int tmp, lv;
        message_vision(append_color(HIY + "\n$N从地上慢慢爬了起来。\n\n" + NOR, HIY), this_object());
        if (query("level") < 1) addn("level", 1);
        lv = query("level");
//      set("title", HIC + chinese_number(lv) + "级" + NOR);    
        set("str", 20 + random(lv) + lv / 2);
        set("con", 20 + random(lv) + lv / 2);
        set("dex", 20 + random(lv) + lv / 2);
        set("int", 20 + random(lv) + lv / 2);
        set("combat_exp", 100000000 * lv * lv);
        set_skill("force",   100 + (random(lv) + lv / 2) * 50); 
        set_skill("unarmed", 100 + (random(lv) + lv / 2) * 50);
        set_skill("dodge",   100 + (random(lv) + lv / 2) * 50);
        set_skill("parry",   100 + (random(lv) + lv / 2) * 50);
        set_skill("jiuyin-shengong",   100 + (random(lv) + lv / 2) * 50);
        map_skill("force", "jiuyin-shengong");
        map_skill("unarmed", "jiuyin-shengong");
        map_skill("dodge", "jiuyin-shengong");
        map_skill("parry", "jiuyin-shengong");
        prepare_skill("unarmed", "jiuyin-shengong");
        tmp = 100000000 * lv * lv / 2;
        set("max_qi", tmp);
        set("eff_qi", tmp);
        set("qi", tmp);
        set("max_jing", tmp);
        set("eff_jing", tmp);
        set("jing", tmp);
        tmp /= 10;
        set("max_jingli", tmp);
        set("eff_jingli", tmp);
        set("jingli", tmp);
        set("max_neili", tmp);
        set("neili", tmp);
        this_object()->reset_action(); 
        
        return 1;
}

void create()
{
        set_name(WHT "石魔像" NOR, ({ "shi moxiang", "moxiang", "shi" }) );
        set("gender", "男性" );
        set("age", 66);
        set("long",     NOR "测试伤害和死亡的傀儡石魔像，它拥有不死之身。\n" HIR "(你如果太菜，则可能死亡)\n" NOR );
        set("shen_type", 0);
        
        setup();
        set("level", 0);
        level_up();
}


int accept_fight(object ob)
{
        return -1;
        
}

int accept_kill(object ob)
{
        return -1;
}

int accept_hit(object ob)
{
        return 1;
}


varargs void receive_damage(string type, int n)
{
        object me = this_player();
        message_vision(append_color(YEL + "\n$N：<" + type + ">" + sprintf("%d", n) + "...\n\n" + NOR, YEL), me);
        return;
}

varargs void unconcious()
{
//      if (objectp(query_last_damage_from())) {
//              message_vision(append_color(YEL + "\n$N：<杀死>" + "...\n\n" + NOR, YEL), query_last_damage_from());
//      }
        message_vision(append_color(YEL + "\n$N晕倒了...\n\n" + NOR, YEL), this_object());
    die(query_last_damage_from());
        return;
}

varargs void die(object killer)
{
//      if (objectp(killer)) {
//              message_vision(append_color(YEL + "\n$N：<杀死>" + "...\n\n" + NOR, YEL), killer);
//      }
        message_vision(append_color(YEL + "\n$N散架了...\n\n" + NOR, YEL), this_object());
        level_up();
        return;
}




