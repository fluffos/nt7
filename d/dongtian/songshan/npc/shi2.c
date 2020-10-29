// This program is a part of NITAN MudLIB 
// redl 2013/9

#include <ansi.h>

inherit NPC;

int level_up()
{
        int tmp, lv;
        message_vision(append_color(HIY + "\n$N从地上慢慢爬了起来。\n\n" + NOR, HIY), this_object());
        if (query("level") < 199) addn("level", 1);
        lv = query("level");
//      set("title", HIC + chinese_number(lv) + "级" + NOR);    
        set("str", 20 + random(lv) + lv / 2);
        set("con", 20 + random(lv) + lv / 2);
        set("dex", 20 + random(lv) + lv / 2);
        set("int", 20 + random(lv) + lv / 2);
        set("combat_exp", 100000000 * lv * lv);
        set_skill("martial-cognize",   100 + (random(lv) + lv / 2) * 40);
        set_skill("count",   100 + (random(lv) + lv / 2) * 25);
        set_skill("force",   100 + (random(lv) + lv / 2) * 50); 
        set_skill("unarmed", 100 + (random(lv) + lv / 2) * 50);
        set_skill("dodge",   100 + (random(lv) + lv / 2) * 50);
        set_skill("parry",   100 + (random(lv) + lv / 2) * 50);
        set_skill("yinyang-shiertian",   100 + (random(lv) + lv / 2) * 50);
        map_skill("force", "yinyang-shiertian");
        map_skill("unarmed", "yinyang-shiertian");
        map_skill("dodge", "yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");
        prepare_skill("unarmed", "yinyang-shiertian");
        tmp = 25000000000 * lv * lv / 2;
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
        command("jiali max");
        return 1;
}

void create()
{
        set_name(WHT "石魔像" NOR, ({ "shi moxiang", "moxiang", "shi" }) );
        set("gender", "男性" );
        set("age", 66);
        set("long",     NOR "练功的傀儡石魔像，它拥有各类宝石凝聚而成的不死之身。\n" HIR "(支持到１０００亿经验)\n" NOR );
        set("shen_type", 0);
        
        setup();
        set("level", 100);
        level_up();
}

/*
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
}*/

        string *gift = ({
                "/clone/tessera/diamond",
                "/clone/tessera/emerald",
                "/clone/tessera/sapphire",
                "/clone/tessera/ruby",
                "/clone/tessera/topaz",
        });


//varargs void receive_damage(string type, int n)
int receive_damage(string type, int damage, object who)
{
        object ob, room;
        int exp;
        
        room = environment();

        if (who && room && objectp(who) && environment(who)==room && 
                query_temp("dongtian/liangongfang/shi_time", room) < time() && 
                query("combat_exp", who) < 100000000000)
        {
                set_temp("dongtian/liangongfang/shi_time", time() + 1 + random(2), room);//房间里每2~3秒只有1人能得利, 每小时1kw左右，仅经验
                        exp = (4 + query("zhen_type", room)) * (250 + 3 * query("level", who) + who->query_kar());
                        exp = exp + random(exp / 5) + query("level") * 2;
                        who->add("combat_exp", exp);  
                        addn("dongtian/liangongfang/gift/exp/shi2", exp, who);
                        message_vision(NOR + HIG + "<击中>$N" + NOR + HIG + "获得奖励经验" + HIY + chinese_number(exp) + HIG + "点。\n" + NOR, who);
         
                // 随机获得物品
                if (random(1500) == 1)
                {
                        ob = new(gift[random(sizeof(gift))]);
                        if (objectp(ob))
                        {
                                ob->move(who, 1);
                                tell_object(who, HIR "你从" + name() + NOR + HIR + "身上敲下了一" + query("base_unit", ob) + ob->name() + "。\n" NOR);                            
                        }
                }
        }
        return 1;
}

varargs void unconcious()
{
//      if (objectp(query_last_damage_from())) {
//              message_vision(append_color(YEL + "\n$N：<杀死>" + "...\n\n" + NOR, YEL), query_last_damage_from());
//      }
//      message_vision(append_color(YEL + "\n$N晕倒了...\n\n" + NOR, YEL), this_object());
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




