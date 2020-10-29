// This program is a part of NITAN MudLIB 
// redl 2014
// 宝物
#include <weapon.h>
#include <ansi.h>
#include <combat.h>
inherit F_NOCLONE;

inherit BLADE;
inherit F_SSERVER;

int query_autoload() { return 0; }
int is_artifacts() { return 1; }

int reset_wield()
{
        object own;
        string msg;
        
        own = query("owner_ob");
        if (!own || (query_temp("flag_hslj", own) && query_temp("flag_hslj", own) < 5)) {
                destruct(this_object()); 
                return 0;
        }
        if (environment()==own && query("name")==query("bak_name")) return 1;
        msg = NOR + HIY + "\n$N"  + NOR + HIY +  "轻拍刀鞘，";
        if (query("name")!=query("bak_name")) {
                delete("no_wield");
                msg += query("name") + NOR + HIY + "一个激灵，聚合成";
                set_name(NOR HIB "天魔" HIM "化" HIR "血" NOR YEL "刀" NOR , ({ "huaxue dao", "dao" }));
        }
        msg += query("name") + NOR + HIY + "跳回$N" + NOR + HIY + "身上。\n" + NOR;
        this_object()->move(own, 1);
        message_vision(msg , own);
        if (!playerp(own)) this_object()->wield();
        return 1;
}

void create()
{
                int lv = random(6)+10;
                set_name(NOR HIB "天魔" HIM "化" HIR "血" NOR YEL "刀" NOR , ({ "huaxue dao", "dao" }));
                set("bak_name", query("name"));
        set("long", HIC "刀光如血，阴狠奇毒。\n  持有者" HIR "越杀越烈" HIC "无止境，并能增强自己的抗打击力。\n  此物自动认主，不毁不灭，乃南疆红木岭天狗崖的红发老祖镇山之宝。\n" HIK "(下线丢失，无法保存)\n" NOR);
        set_weight(5000);
                set("unit", "柄");
                set("value", 100);
                set("material", "no name");
                set("material_file", "/clone/goods/noname");
                set("max_consistence", 200);
                set("consistence", 200);
                
//                set("no_give", 1);
//                set("no_drop", 1);
//                set("no_get", 1);
//                set("no_uget", 1);
                set("no_steal", 1);
                set("no_sell", 1);
                set("no_beg", 1);
                set("no_put", 1);
                set("no_store", 1);
                set("no_pawn", 1);
                //set("maze_item", 1);//不能give
                set("unique", 1);//已避免分解
                                set("quality_level", 6);
                                
                                set("wield_msg", NOR CYN "$N" NOR CYN "一抹刀鞘，$n" NOR CYN "带着"+NOR+RED+"血光"+NOR+CYN+"跃到$N" NOR CYN "手中。\n" NOR); 
                                set("unwield_msg", NOR CYN "$N" NOR CYN "随手一按，$n" NOR CYN "插回$N" NOR CYN "的腰间刀鞘里。\n" NOR); 
                
                //set("weapon_prop/kar", lv);
                set("weapon_prop/add_skill", 125 + lv);
                set("weapon_prop/add_damage", 25 + lv);
                set("weapon_prop/ap_power", 20 + lv);
                set("weapon_prop/avoid_busy", 10 + lv);
                set("weapon_prop/reduce_busy", 10 + lv);
                set("weapon_prop/reduce_damage", lv);
                                set("ob_lv", lv);
                                
                init_blade(4000 + lv * 60);
                                set_heart_beat(4);
                        setup();
}        

void heart_beat()
{
        object me;
        object *obs, ob, room, owner, enemy;
        int damage, i, ap, dp, kn, kn2;
        string snum, msg;
        
        //if (!environment()) return;
        if (!reset_wield()) return;
        me = this_object();
        owner = environment();
        if (!owner || !owner->is_character() || !query("equipped") || 
                 !(room = environment(owner)) || !room->is_room()) {
                        return;
        }
        if (!owner->is_fighting())
                        return;
//      if (owner->is_busy())
//                      return;
        obs = owner->query_enemy();     
        
        if (arrayp(obs) && sizeof(obs)) {
                ap = query("level", owner) * query("level", owner);
                damage = damage_power(owner, "force") / 3 + damage_power(owner, "blade");
                damage *= (query("jiali", owner)+100) / 100 * query("ob_lv");
                damage /= 15;
                kn2 = query("artifacts/thxdao/kill_num", owner);
                damage += damage * (kn2 + 1) / 15000;
                kn = 1;
                if (kn2 > 100) kn += 1;
                if (kn2 > 1000) kn += 1;
                if (kn2 > 10000) kn += 1;
                if (kn2 > 100000) kn += 1;
                if (kn2 > 1000000) kn += 1;
                if (kn2 > 10000000) kn += 1;
                if (kn2 > 100000000) kn += 1;
                snum = chinese_number(kn2 / 100 * 100);//整百显示
        for (i = 0; i < (1 + kn); i++)
        {
                if (!arrayp(obs) || !sizeof(obs)) break;
                        enemy = obs[random(sizeof(obs))];
                        if (!enemy || !living(enemy) || environment(enemy)!=room) continue;
            dp = query("level", enemy);
                        if( random(ap) + ap / 2 > dp ) 
                {
          if (playerp(enemy)) {
             enemy->receive_damage("qi", damage / 200, owner); 
             enemy->receive_wound("qi", damage / 400, owner); 
          } else {
                        enemy->receive_damage("qi", damage, owner);
                        enemy->receive_wound("qi", damage / 2, owner);
          }
                        if( !enemy->is_busy() )
                                enemy->start_busy(2);
                                                message_vision(NOR + HIY "\n$N" + NOR + HIY + "手中的" + BLINK + query("name") + NOR + HIY + "斜劈，"+ snum + "条"+
                                                                                NOR + BLINK + RED+"血炼幽魂"+NOR + HIY+"隐现，影影绰绰围住$n"+NOR + HIY+"嚎叫扑咬。\n" NOR, owner, enemy);
                                                message_vision(HIW "( $N" + NOR + HIW + "手中的" + query("name") + NOR + HIW + "对" +
                                        query("name", enemy)+ NOR + HIW"造成"+
                                        damage + "点伤害，" +
                                        (damage / 2) + "点创伤。)\n" NOR, owner);
                        COMBAT_D->report_status(enemy);
                        if (query("eff_qi", enemy) < 1 ) {
                                addn("artifacts/thxdao/kill_num", 1, owner);
                                                        set_temp("die_reason", NOR + "被" + query("name", owner) + "用天魔化血刀砍死了" + NOR, enemy);
                                                enemy->die();
                                                        message_vision(NOR + HIG "\n" + BLINK + query("name") + NOR + HIG + "反哺一匹血光，扩充了$N"+NOR + HIG+"的精血脉络。\n" NOR, owner);
                                                        addn("eff_jing", ap, owner);//可超上限
                                                        addn("eff_qi", ap * 2, owner);//可超上限
                        }
                }
        }
        }
}


