// This program is a part of NITAN MudLIB 
// redl 2013/9

#include <ansi.h>

inherit NPC;

int level_up()
{
        int tmp, lv, lvc;
        object me = this_object();
                int rnd;
                object ob, *obs;
                string obname;
                
        message_vision(append_color(HIY + "\n数道黑气从地底升起缠绕在$N身上，$N体型又增大了一些。\n\n" + NOR, HIY), me);

        addn("level", 1);
        lv = query("level");
//      set("title", HIC + chinese_number(lv) + "级" + NOR);    
                set("jiali", lv * 5);
        set("str", 20 + random(lv) + lv / 2);
        set("con", 20 + random(lv) + lv / 2);
        set("dex", 20 + random(lv) + lv / 2);
        set("int", 20 + random(lv) + lv / 2);
        set("combat_exp", 100000000 * lv * lv);
        if (lv > 99) {
                set_skill("count", 1000 + lv * (1 + random(3)));
                set_skill("martial-cognize", 300 + (random(lv) + lv / 2) * 65);
        }
        set_skill("force",   300 + (random(lv) + lv / 2) * 150); 
        set_skill("unarmed", 300 + (random(lv) + lv / 2) * 150);
        set_skill("dodge",   300 + (random(lv) + lv / 2) * 150);
        set_skill("parry",   300 + (random(lv) + lv / 2) * 150);
        set_skill("jiuyin-shengong",   300 + (random(lv) + lv / 2) * 150);
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
        this_object()->clear_condition();
        this_object()->stop_busy();

        this_object()->clear_weak();
        this_object()->start_busy(1);

        obs = this_object()->query_enemy();
        if (sizeof(obs)) {
                foreach (ob in obs)  { 
                        lvc += query("level", ob);
                }
        }
        if ( lvc && 
                query("bouns_time") < time() && 
                random(3) && 
                ((lv - (int)pow(lvc, 1.5) / 4) > 0) ) {         
                set("bouns_time", time() + 10);
        ob = new("/d/dongtian/obj/wanxiangbook");
                set("no_open_msg", 1, ob);
                rnd = ob->do_open(query("id", ob));
        if (!ob->move(environment()))
                        destruct(ob); 
                else
                {
                //      set("who_get/id", query("id", me), ob);
                //      set("who_get/time", time() + 30, ob);
                        obname = query("name", ob);
                        message_vision(append_color(
                                NOR + CYN + (random(2) ? "哐啷" : "噹地") + (random(2) ? "~ " : "，") + NOR + CYN + "$n" + (random(2) ? "掉" : "落") + 
                                (random(2) ? "下" : "出") + obname + NOR + CYN + (random(2) ? ".." : "...") + "\n" NOR, CYN), me, this_object());
                        if (rnd < 1000 || query("channel_time") < time()) {
                                CHANNEL_D->channel_broadcast("dt", sort_msg(NOR + HIW + "传说有人在福地" + query("short", environment()) + HIW + "发现了" + NOR + obname + HIW "。\n" + NOR, 64));
                                set("channel_time", time() + 120);
                        }
                }
        }
        
        return 1;
}

void create()
{
        set_name(HIK "铁魔像" NOR, ({ "tie moxiang", "moxiang", "tie" }) );
        set("gender", "男性" );
        set("age", 99);
        set("long",     NOR "测试伤害和死亡的傀儡铁魔像，它拥有成长能力。\n" HIR "(你如果太菜，则可能死亡)\n" NOR );
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


