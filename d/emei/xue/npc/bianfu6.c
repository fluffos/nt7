//redl 2014
inherit "/maze/binghuodao/npc/bhd_npc.c";
#include <ansi.h>

#define LV 6

int is_quarry(){return 1;}
int is_not_hunting(){return 1;}

void create()
{
        set_name(HIR "吸血" NOR WHT "银蝠" NOR, ({ "xixue bianfu", "xixue", "bianfu" }));

           set("shen", -1000);
        set("age", 10 + LV);
        set("str", 350 + LV * 35);
        set("dex", 1000 + LV * 100);
        set("max_qi", 100000 * LV * LV * 3);
        set("max_ging", 100000 * LV * LV * 3);
        set("eff_jing", 50000 * LV * LV * 3);
        set("max_jing", 50000 * LV * LV * 3);
        set("max_neili", 250000 * LV * LV);
        set("neili", 250000 * LV * LV);
        set("jingli", 100000 * LV * LV);
        set("max_jingli", 100000 * LV * LV);
        set("jingli", 100000 * LV * LV);
        set("eff_jingli", 100000 * LV * LV);
        set("combat_exp", 5000000 * LV * LV * 3);
        set("jiali", 1000 * LV + random(1000 * LV / 2)); 

        set_temp("apply/parry", 350 + LV * LV * 35);
        set_temp("apply/dodge", 2000 + LV * LV * 200);
        set_temp("apply/dex", 200 + LV * LV * 20);
        set_temp("apply/attack", 2000 + LV * LV * 300);
        set_temp("apply/defense", 180 + LV * LV * 20);
        set_temp("apply/unarmed_damage", 3580 + LV * LV * 400);
        set_temp("apply/damage", 3000 + LV * LV * 300);
        set_temp("apply/armor", 380 + LV * LV * 40);

        set_skill("count", 500 + random(500) + LV * LV * 80);
        set_skill("dodge", 200 + random(200) + LV * LV * 50);
        set_skill("qingfu-shenfa", 200 + random(200) + LV * LV * 50);
        map_skill("dodge", "qingfu-shenfa"); 
        set_skill("force", 200 + random(200) + LV * LV * 50);
        set_skill("xuanming-shengong", 200 + random(200) + LV * LV * 50);
        map_skill("force", "xuanming-shengong"); 
        set_skill("claw", 200 + random(200) + LV * LV * 50);
        set_skill("ningxue-shenzhao", 200 + random(200) + LV * LV * 50);
        map_skill("claw", "ningxue-shenzhao"); 
        set_skill("parry", 200 + random(200) + LV * LV * 50);
        map_skill("parry", "ningxue-shenzhao"); 
        prepare_skill("claw", "ningxue-shenzhao");  

        set("auto_perform", 1);
/*        set("chat_chance_combat", 120); 
        set("chat_msg_combat", ({ 
                (: perform_action, "claw.ji" :), 
        }) ); */

        set("gift/exp", 320 + (LV * 240));
        set("gift/pot", 80 + (LV * 60));
        set("gift/mar", 20 + (LV * 15));

        set("oblist", ([
                "/clone/medal/yongshi_xunzhang" :1,
        ]));
        
        //金蝙蝠要破怪体

        setup();
}

void init()
{
        // 随机攻击玩家
        if (userp(this_player()) && !query("env/invisible", this_player()) && !random(4))
        {
                tell_object(this_player(), query("name", this_object()) + NOR CYN "桀桀怪笑，化为一道银色劲装的青年向你扑来...\n" NOR);
                if (random(2)) this_player()->start_busy(2);
                kill_ob(this_player());
        }
}

mixed hit_ob(object me, object ob, int damage)
{
        string  msg;

        ob->receive_damage("qi", damage);
        ob->receive_damage("jing", damage/2);
        addn("neili", -damage/4, ob);

        if( !random(3) )
        {
            addn("eff_qi", damage * 10, me); 
            addn("qi", damage * 10, me); 
            addn("eff_jing", damage * 5, me); 
            addn("jing", damage * 5, me); 
            addn("jingli", damage * 2, me); 
            msg = HIR "$n" HIR "觉得伤口有些发麻，鲜血潺潺流进蝙蝠的嘴里。\n" NOR;
        }
        return msg;
}
