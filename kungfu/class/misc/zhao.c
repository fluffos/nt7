// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>

inherit NPC;

void smart_fight();
string do_flee();

void create()   
{
        object weapon;

        set_name("赵飞柳", ({ "zhao feiliu","boss","zhao"}) );
        set("gender", "男性" );
        set("nickname",BLU"阎王伞"NOR);
        set("title","血雨门");
        set("class","legend");
        set("age",77);
        set("start_room", "/d/city/dongmen");

        set("long","一个青衣白发的老人，一个人独行在山道间，手里撑着柄油纸伞。嘴角带
着丝神秘而诡谲的微笑，天上乌云密布，细雨纷纷，滴滴落在老人手上的
油纸伞上。\n");

        set("gender", "男性" );
        set("agi",70);
        set("gold",30);
        set("real_boss",1);
        set("boss",1);  // immune to some rascal skill and ghostcurse.
                                                // busy resist but not immune.

        set("attitude","friendly");
    
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: smart_fight() :),
             }) );

        set("combat_exp", 71000000000); // L110
        set_temp("apply/armor",8000);
        
        set_skill("force", 4000);
        set_skill("taixuan-gong",4000);
        set_skill("dodge", 4000);
        set_skill("lingbo-weibu",4000);
        set_skill("unarmed", 4000);
        set_skill("luohan-quan",4000);
        set_skill("parry", 4000);       

        map_skill("force", "taixuan-gong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("unarmed", "luohan-quan");    // 想打落我武器的就来吧..
                
        set("max_qi",90000000000);
        set("max_jing",70000000000);
        
        setup();

        weapon=new("/clone/weapon/sword");
        weapon->set_name(YEL"油纸伞"NOR, ({ "umbrella" }) );
        set("long","油纸伞(Umbrella)。\n",weapon);
        set("value",0,weapon);
        weapon->wield();

        weapon=new("/clone/cloth/cloth");
        weapon->set_name(CYN"血雨青衣"NOR, ({ "cloth" }) );
        set("long","血雨青衣(Cloth)。\n", weapon);
        set("value",0,weapon);
        weapon->wear();
                
        set("drop/fixed_amount",1);
        set("drop/fixed_drop", ({               // L80-90 books

        }));
                
        set("drop/bg",0);
        set("drop/common",100);
        set("drop/rare",0);     
        set("drop/amount",3);
        set("drop/common_drop",({

        }) );
        set("drop/rare_drop",({

        }) );
        
}

void die()
{
        object who = query_max_damage_from();
        object lotus;
        
        if (random(2)) {
                //lotus = new(AREA_XINJIANG"obj/lotus");
                //if (lotus) lotus->move(this_object());
        }

        if (!objectp(who))
                who = query_temp("last_damage_from");
                
        if (objectp(who))
               BUFF_D->generate_drop_item(this_object(),who);

        ::die();
        return;
}

void smart_fight()
{
        object ob;
        mapping data, buff;
        object target,*enemy;
        int f,i;
        
        enemy=query_enemy();
        
        if (!random(3))
        {
                for (i=0;i<sizeof(enemy);i++) {
                        if (objectp(ob = enemy[i])) {
                                if (BUFF_D->check_buff(ob,"lowresist"))        continue;
                                message_vision(BCYN WHT"\n破世阴雩\n"NOR,this_object());
                                message_vision(HIB"\n赵飞柳的伞突然一收，满天的黑云聚起，忽然间一声霹雳，"NOR,this_object());   
                                message_vision(HIB"闪电自云层击下，照亮了阴翳的天际。\n"NOR,this_object());
                                data =
                                        ([
                                                "reduce_damage" : -20,
                                        ]);
                                buff =
                                        ([
                                                "caster":this_object(),
                                                "target":ob,
                                                "name":"天魔无相·破世阴雩",
                                                "type": "lowresist",
                                                "attr": "curse",
                                                "buff_data" : data,
                                                "time":60,
                                                "buff_msg":HIB"$N"HIB"心头剧振，眼前一阵眩晕。\n"NOR,
                                        ]);
                                BUFF_D->buffup(buff);
                                break;
                        }
                }       
        }
                
        if (!random(3))
        {
                for (i=0;i<sizeof(enemy);i++) {
                        if (objectp(ob = enemy[i])) {
                                if (BUFF_D->check_buff(ob,"cursedflesh"))      continue;
                                message_vision(BBLU HIW"\n空魂异血\n"NOR,this_object());
                                data =
                                        ([
                                                "defense" : -2000,
                                        ]);
                                buff =
                                ([
                                        "caster":this_object(),
                                        "target":  ob,
                                        "type": "cursedflesh",
                                        "attr":  "curse",
                                        "name": "破邪心经·空魂异血",
                                        "time": 30,
                                        "buff_msg":HIC"\n$n"HIC"面上浮现出青蓝之色，喷出一团腥臭的烟气。\n"HIB"$N"HIB"猝不及防，吸进一口毒雾，登时摇摇欲坠．．．\n\n"NOR,
                                ]);
                                BUFF_D->buffup(buff);
                                break;
                        }
                }       
        }

        target = select_opponent();
        add_temp("apply/attack",25000);
        add_temp("apply/damage",400000000);
        add_temp("apply/unarmed_damage",400000000);
        message_vision(BRED WHT"\n伤痕措手\n"NOR,this_object());
        message_vision(HIB"赵大先生的伞一撑，人影已如鬼魅般贴近$n，五指向$n背上抓去！"NOR,"抓伤！"HIR"$n的背上被抓得鲜血淋漓．．．\n"NOR, this_object());
        COMBAT_D->do_attack(this_object(),target,0,3);
        COMBAT_D->do_attack(this_object(),target,0,3);
        COMBAT_D->do_attack(this_object(),target,0,3);
        add_temp("apply/attack",-25000);
        add_temp("apply/damage",-400000000);
        add_temp("apply/unarmed_damage",-400000000);
        
        if (!BUFF_D->check_buff(target,"armorup"))
        {
                data =
                        ([
                                "armor" : -10000,
                        ]);
                buff =
                        ([
                                "caster":this_object(),
                                "target":target,
                                "name":"天魔无相·伤痕措手",
                                "type": "armorup",
                                "attr": "curse",
                                "buff_data" : data,
                                "time":   60,
                                "buff_msg":" "NOR,
                        ]);
                        BUFF_D->buffup(buff);
        }

        return;
}


mixed valid_damage(object victim,object attacker,int damage)
{
        mapping data = ([]);
        object thr;
        if (!thr = query_temp("weapon", attacker))
                return 0;

        data["msg"] = CYN"赵飞柳手里的油纸伞风车般旋转起来，突然间已化成一道光圈。\n只听叮、叮、叮一连串急响，"+thr->name()+CYN"已在一瞬间被震飞。\n"NOR;
        data["damage"] = -damage;
        return data;
}

