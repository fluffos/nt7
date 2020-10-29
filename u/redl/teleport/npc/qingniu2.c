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


int is_home(string where)
{
        if (strsrch(where, "dongtian") != -1)
                return 0;
        return 1;
}

int random_move()
{
        mapping exits;
        string *dirs, direction, to_go_place;
        object env; 
        string *list=query("slots");

                if (!query("can_move")) return 0;
        if( !mapp(exits=query("exits", environment())))return 0;
        if (this_object()->is_fighting()) return 0;
        dirs = keys (exits);
        direction = dirs[random(sizeof(dirs))];
        if (strsrch(direction, "west") != -1 || 
                (query("rnd_stp") > 8)
                ) {
                delete("rnd_stp");      
                env = environment(this_object());
                to_go_place=query("exits/"+direction, env);
            if (!is_home(to_go_place)) return 0;
                command("go " + direction);
                if (!list || !sizeof(list)) {
                        list = ({env->short()});
                                CHANNEL_D->channel_broadcast("rumor", "据传老子的追随者们已经离开了" + env->short() + "。");
                } else if (member_array(env->short(), list)==-1) {
                        list += ({env->short()});
                                CHANNEL_D->channel_broadcast("rumor", "据传老子的追随者们已经离开了" + env->short() + "。");
                }
                set("slots", list);
        }
        addn("rnd_stp", 1);
        return 1;
}   


void create()
{
        set_name(HIG "大青牛" NOR, ({ "qing niu", "qing", "niu" }));
        set("title", CYN "圣人坐骑" NOR);
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

        set("max_jing", 1000 * 2000);
        set("jing", query("max_jing"));
        set("max_qi", 1000 * 2000);
        set("qi", query("max_qi"));
        set("shadow_hp", 1000 * 2000);

        set("auto_perform", 1);
                set_heart_beat(1);

                set("chat_chance", 16);
        set("chat_msg", ({
                (: random_move :),
        }));
        
        setup();
}
        
int receive_damage(string type, int n, object who) 
{ 
        object ob;
        string unit;
        n = n / 100000000;
        if (!who) return;
        if (!userp(who) && !objectp(who=(query("owner")))) return;
        if (!who || !userp(who)) return;
        if (n > 1000) n = 1000;
        if (query_temp("qingniu2/time", who) < time() && random(3000) < n) {
                set_temp("qingniu2/time", time(), who);
                if (!random(100)) ob = new("/d/dongtian/obj/wanxiangbook");
                else if (!random(18)) ob = new("/clone/medicine/yuqingwan");
                else ob = new("/clone/gift/jiuzhuan");
                if (objectp(ob))
                {
                        unit = query("base_unit", ob);
                        if (!unit) unit = query("unit", ob);
                        ob->move(who, 1);
                        tell_object(who, HIW "你从" + name() + NOR + HIW + "身上敲下了一" + unit + ob->name() + "。\n" NOR);                            
                }
        }
        addn("shadow_hp", -n);
        if (query("shadow_hp")<0) {
                set("killer", who);
        }
        return ::receive_damage(type, n , who);
} 
      
int receive_wound(string type, int n) 
{ 
     return;
} 
      
int accept_kill(object who)
{
        object *t;
        set("enemy_player", who);
        this_object()->kill_ob(who);
        who->kill_ob(this_object());
        if (t && sizeof(t)) {
                t -= ({ 0 }); 
                foreach (object tob in t) 
                        tob->kill_ob(who);
        }
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
                int num, radd;
        enemy = query("killer");                        
                if (objectp(enemy) && 
                        environment(this_object()) == environment(enemy)) {
                        message_vision(HIW "\n$N" HIW "抓住牛角，跳上牛背冲着$n" HIW "的脑门一巴掌，干掉了$n" HIW "。\n\n" NOR, enemy, this_object());
                        radd = 10000 + random(query("level", enemy) * query("level", enemy));
                        addn("drug_addjingli", radd, enemy);
                tell_object(enemy, HIC "你翻阅" HIY "《太上灵宝老子化胡妙经》" HIC "，精力上限额外增加" HIY + chinese_number(radd) + HIC "点。\n" NOR);
                        return ::die(enemy);
                }
                
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") )
        {
                ob = previous_object(4);
                if (userp(ob) && environment(this_object()) == environment(ob))
                        this_object()->receive_damage("qi", 800, ob);
            return;
        }

        if (!objectp(enemy)) return;
    return ::die(killer);
}

void unconcious()
{
     object ob,me = this_object();
     if(!objectp(ob)) ob = me->query_last_damage_from();
     if(!objectp(ob)) ob = query_temp("last_damage_from",me);
     die(ob);
}

void start_move()
{
        set("can_move", 1);
}

