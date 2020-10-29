inherit BOSS;
#include <ansi.h>
int big_blowing();
void create()
{
        set_name(HIR"烈火孽龙"NOR, ({ "fire dragon king", "dragon king", "dragon" }) );
        set("race", "野兽");
        set("gender", "雄性");
        set("age", 200);
        set("long",
"这是一条全身赤红，吸天地之间的火气而长大的孽龙！
它全身散发着赤红色的火焰。\n");

        set("str", 248);
        set("con", 252);
        set("dex", 222);

        set_skill("dodge", 2999);
        set_skill("force", 2999);
        set_skill("unarmed", 2999);
        set_skill("parry", 2999);
        set("max_qi", 20000000);
        set("max_jing", 9999999);
        set("max_neili", 90001000);
        set("neili", 90001000);
        set("jiali", 900000);
        set("attitude", "aggressive");
        set("limbs", ({ "头部", "身体", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("death_msg", "$N化作一缕清风而去。\n");
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: big_blowing :)
        }) );

        set("combat_exp", 901100000+random(600110000));
        set("bellicosity", 30000 );
        set("level", 100);

        set_temp("apply/attack", 3000+random(3000));
        set_temp("apply/unarmed_damage",3000+random(3000));
        set_temp("apply/armor", 3000+random(3000));
        set_temp("apply/add_weak", 70);
        set_temp("apply/reduce_damage", 90);
        set_temp("apply/reduce_busy", 40);
        set_temp("apply/add_busy", 15);

        set("rewards", ([
                "exp"   : 150000,
                "pot"   : 60000,
                "mar"   : 18000,
                "score" : 600,
                "gold"  : 100,
        ]));
        set("drops", ([
                "MO&A3000"       :       3,
                "MO&A3001"       :       3,
                "MO&A3002"       :       3,
                "MO&A3003"       :       3,
                "MO&A3004"       :       3,
                "MO&A3005"       :       1,
                "MO&A3006"       :       1,
                "FI&/clone/tessera/rune24"   :           1,
                "FI&/clone/tessera/rune25"   :           1,
                "FI&/clone/tongren/tongren"+(1+random(2))   :           1,
        ]));

        setup();
        carry_object("/clone/money/gold")->set_amount(200);
}
int big_blowing()
{
        message_vision( HIR "\n\n烈火孽龙深深地吸入一口气，全身转为鲜红的火色，整个龙腹胀大了几倍！！\n\n" NOR,
                        this_object());
        call_out("hurting", 1);


        return 1;
}

int hurting()
{
        int i;
        int dam;
        object *inv;
        message_vision( HIR "\n\n烈火孽龙吐出一股炽可焚金的火焰．．整个天地似乎都被燃烧着！！！\n\n",this_object());
        inv = all_inventory(environment(this_object()));
        for(i=sizeof(inv)-1; i>=0; i--)
        if( living(inv[i]))
        if( inv[i] != this_object())
        {
                dam = 100000+random(100000);
                inv[i]->receive_wound("qi",dam, this_object());
                inv[i]->receive_wound("jing",dam/2, this_object());
                inv[i]->affect_by("poison",
                                  ([ "level" : 1500,
                                     "id":query("id", this_object()),
                                     "name" : "烈火孽龙的火毒",
                                     "duration" : 200 ]));
                tell_object(inv[i], HIG "你中了烈火孽龙的火毒。\n");
                COMBAT_D->report_status(inv[i],1);
        }
        return 1;
}

void die()
{
        object obj, env;
        object killer;
        object ob, me;
        int exp;
        int userexp;
        int i;

        me = this_object();

        if (objectp(ob = previous_object(0)) &&
            sscanf(base_name(ob), "/kungfu/skill/%*s"))
        {
                me->full_self();
                addn_temp("apply/attack", 3000+random(3000));
                addn_temp("apply/unarmed_damage",3000+random(3000));
                addn_temp("apply/armor", 3000+random(3000));
                return;
        }

        if (! query("have_reborn"))
        {
                set("have_reborn", 1);
                me->full_self();
                return;
        }
                env = environment(this_object());
        if (objectp(killer=this_object()->query_last_damage_from()))
        {
                userexp=query("combat_exp", killer);
                exp=(query("literate", killer)*4)+random(10000)+40000+userexp/60000;
                if (exp > 100000) exp = 100000;

                if( !query_temp("m_success/孽龙", killer) )
                {
                        set_temp("m_success/孽龙", 1, killer);
                        addn("combat_exp", exp, killer);
                        addn("potential", 50000, killer);
                        message("channel:chat",HBMAG"【精灵神界】"+query("name", killer)+"成功地杀死了恶龙，解开了封印!得到无数经验和潜能及宝石.\n"NOR,users());

                message_vision(MAG "一道红光从天而降，照耀着$N。\n" NOR, killer);
                message_vision(HIR "一团火焰猛地升腾，一个声音说道：谢谢你们解开了第七个封印，这些宝石就作为谢礼吧！！！\n" NOR, this_object());

                for (i = 0; i < 7; i++)
                {
                        obj = new("/clone/tessera/rune2" + random(9));
                        obj->move(env, 1);
                }
                if (! random(5))
                {
                        obj = new("/clone/goods/tianshi-charm");
                        obj->move(env, 1);
                }

                if (! random(3))
                {
                        obj = new("/clone/herb/drug"+(1+random(10)));
                        obj->move(env, 1);
                }

                message_vision(HIY "红光退去，你突然发现地上有很多东西在闪闪发光。\n" NOR, this_object());
                }
        }
        set("exits/north", "/d/city/wumiao", env);
/*
        message_vision("$N化作一缕清风而去。\n", this_object());
        destruct(this_object());
*/
        return ::die();
}

void unconcious()
{
        object ob;

        if (objectp(ob = previous_object(0)) &&
            sscanf(base_name(ob), "/kungfu/skill/%*s"))
        {
                this_object()->full_self();
                return;
        }

        die();
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        int damage;

        damage = 100000 + random(100000);
        damage -= damage*ob->query_all_buff("reduce_fire")/100;
        if (damage < 10000) damage = 10000;
        ob->receive_damage("qi", damage, me);
        ob->receive_wound("qi", damage, me);
        set("neili",query("max_neili",  me), me);
        return HIR "$N" HIR "“吼”的一声吐出一鼓火焰，登时令$n"
               HIR "感觉犹如整个天地似乎都被燃烧着。\n" NOR;
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
}
