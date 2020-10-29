// This program is a part of NT MudLIB

#include <ansi.h>
#include <command.h>

inherit WORM;

void random_move();
int is_boss() { return 1; }
int is_stay_in_room() { return 1; }

void fight_ob(object ob)
{
        if( is_fighting() || !query("end_time") )
                return ::fight_ob(ob);

        set_temp("end_time", time() + query("end_time"));
        return ::fight_ob(ob);
}

void create()
{
        set_name(HIG "五毒圣物" NOR, ({ "wudu shengwu", "wudu", "shengwu" }));
        set("long", HIG "这是从五毒教毒窟中逃出来的剧毒蜘蛛，约莫半人高，看起来样子十分可怕。\n" NOR);
        set("race", "野兽");
        set("age", 20 + random(100));

        set("combat_exp", 5000000);
        set("shen_type", 0);
        set("max_neili", 30000);
        set("neili", 30000);
        set("max_jing", 60000);
        set("jing", 60000);
        set("max_qi", 1200000);
        set("eff_qi", 1200000);
        set("qi", 1200000);
        set("jingli", 52000);
        set("max_jingli", 52000);
        set("attitude", "peaceful");

        set("no_clean_up", 1);

        set("str", 33);
        set("int", 33);
        set("con", 33);
        set("dex", 33);

        set_skill("unarmed", 1500);
        set_skill("sword", 1500);
        set_skill("blade", 1500);
        set_skill("parry", 1500);
        set_skill("dodge", 1500);
        set_skill("force", 1500);

        set("jiali", 100);

        setup();

        set("limbs", ({ "头部", "身体", "长腿" }));
        set("verbs", ({ "bite" }));

        set("worm_poison", ([
                "level"  : 500,
                "perhit" : 150,
                "remain" : 150,
                "maximum": 150,
                "supply" : 50,
        ]));

/*
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
*/
        //set("end_time", 300);

        set("rewards", ([
                "exp"   : 50000,
                "pot"   : 25000,
                "mar"   : 5000,
                "score" : 300,
                "gold"  : 50,
        ]));

        set("drops", ([
                "RA&RANDOM30"    :       100,   // 低级普通装备
                "RA&RANDOM40"    :       40,    // 低级普通装备
                "FI&/clone/goods/enchant-scroll" :   20,
                "FI&/clone/goods/sun"    :   20,
                "FI&/clone/goods/moon"   :   20,
                "FI&/clone/fam/quest/wudu-zhu"              :           30,
                "FI&/clone/fam/pill/sheli2"                 :           30,
                "FI&/clone/fam/pill/lingzhi2"               :           30,
                "FI&/clone/fam/pill/puti3"                  :           30,
                "FI&/clone/tessera/rune06"  :   1,
                "FI&/clone/misc/baoxiang" : 100,
        ]));
        set_temp("apply/attack", 300 + random(100));
        set_temp("apply/damage", 700 + random(100));
        set_temp("apply/armor",500 + random(200));
        set_temp("apply/defence", 500 + random(200));

        setup();
        set_temp("born_time", time());
        //if (clonep()) keep_heart_beat();
}
void init() 
{
}

int accept_fight(object ob)
{
        kill_ob(ob);
        return -1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        kill_ob(ob);
        return -1;
        return 1;
}

void heart_beat()
{
        if (query("neili") < 1 && random(40) == 1)
                set("neili", query("max_neili"));

        ::heart_beat();
}

void random_move()
{
        object env;

        if (time() - query_temp("born_time") > 1800)
        {
                env = environment(this_object());
                message_vision("$N急急忙忙的走了。\n", this_object());

                CHANNEL_D->channel_broadcast("news", HIG "听说" + HIW +
                        env->short() + "(" + LOOK_CMD->locate(base_name(env)) + ")" HIG "一带出现的" +
                        HIR + this_object()->short() + HIG "消失了。\n" NOR);

                destruct(this_object());
                return;
        }
        //::random_move();
}


varargs void die(object killer)
{
        object *obs, *obn, env;
        object me, ob;
        mapping /*drops,*/ rewards;
//      string *ks;
//      string line,key;
//      int exp,pot;
//      int i,n,times,value,rand;
        string fbname, owner;
        mapping fuben_data;
        int fuben_level, percent;
        mixed death_msg;

        me = this_object();

        //if( query("end_boss", me) || query("fight_boss", me) )
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }

        if( time() < query_temp("end_time", me) ) // 时间没有到，死亡不了
        {
                addn("jing", query("max_jing") / 10);
                addn("eff_jing", query("max_jing") / 10);
                addn("qi", query("max_qi") / 10);
                addn("eff_qi", query("max_qi") / 10);
                message_vision(HIR "\n$N" HIR "大喝一声，运用秘法，气血有所回升！\n\n" NOR, me);
                return;
        }

        if( death_msg = query("death_msg", me) ) {
                if( functionp(death_msg) )
                        evaluate(death_msg, me);
                else
                        message_vision(death_msg, me);
        }

        /* 以下部分转移到equipmentd.c中处理,因涉及到动态物品
        if( drops = query("drops") ) {
                times = ACTION_D->query_action("fuben_drop");
                if( !times ) times = 1;

                ks = keys(drops);
                for( i=0; i<sizeof(ks); i++ ) {
                        key = ks[i];
                        value = drops[ks[i]];
                        for( n=0;n<times;n++ ) {
                                rand = random(value);
                                if( !rand ) {
                                        if( ob = new(key) ) {
                                                ob->move(me, 1);
                                        }
                                }
                        }
                }
        }
        */

        fbname = FUBEN_D->query_fuben_name(me);
        owner = FUBEN_D->query_fuben_owner(me);
        if( fbname && owner ) {
                fuben_data = FUBEN_D->query_fuben_data();
                if( fuben_data[fbname]["level"] )
                        fuben_level = to_int(fuben_data[fbname]["level"]);
                if( query("clear_fuben", me) )
                        FUBEN_D->delay_clear_fuben(fbname, owner);
        }

        if( !fuben_level )
                fuben_level = query("level", me);

        if( !(rewards = query("rewards")) ) {
                ::die(killer);
                return;
        }

        if( !killer ) killer = me->query_last_damage_from();
        if( !killer ) killer = query_temp("last_damage_from");
        if( objectp(killer) ) {
                if( query("family/family_name", killer) == "五毒教")
                        set("rewards/gongxian", 300);
                env = environment(me);
                obs = pointerp(killer->query_team()) ?
                                killer->query_team() : ({ killer });
                obs = filter_array(obs, (: environment($1) == $(env) :));
                if( arrayp(obn = query_temp("damage_from")) && sizeof(obn) > 0 )
                {
                        obn -= ({ 0 });
                        obn = filter_array(obn, (: environment($1) == $(env) :));
                        obn -= obs;
                        obs += obn;
                }
                foreach( object user in obs ) {
                        if( !objectp(user) ) continue;
                        if( fuben_level ) {
                                if( query("level", user) <= fuben_level )    percent = 100;
                                /*
                                else if( query("level", user) <= fuben_level+20 ) percent = 80;
                                else if( query("level", user) <= fuben_level+30 ) percent = 50;
                                */
                                else {
                                        tell_object(user, ((killer == user)?"您":killer->name())+"杀死"+query("name")+"，但您经验与BOSS的水平相差过大，没有奖励。\n");
                                        continue;
                                }
                                rewards["percent"] = percent;
                        }
                        /*
                        else
                        {
                                if( query("combat_exp", user) > query("combat_exp")*2 ) {
                                        tell_object(user, ((killer == user)?"您":killer->name())+"杀死"+query("name")+"，但您经验与BOSS的水平相差过大，没有奖励。\n");
                                        continue;
                                }
                        }
                        */
                        GIFT_D->bonus(user, rewards);
                }
        }

        ::die(killer);
        return;
}

varargs void unconcious(object defeater)
{
        object ob;

        //if( query("end_boss") || query("fight_boss") )
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }
        die(defeater);
        return;
}