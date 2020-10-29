// donghai.c

#include <ansi.h>

int is_neili_cow() { return 1; }

inherit NPC;

void create()
{
        set_name(NOR + YEL "神雕" NOR, ({ "shen diao", "shen", "diao" }) );
        set("title", HIG "独孤无畏" NOR);
        set("gender", "男性");
        set("age", 120);
        set("long", HIY "这是独孤求败生前所养大雕，后来被「神雕大侠」杨过收养。\n"
                        "此雕天神神力，常人难敌。\n" NOR);

        set("combat_exp", 90000000);
        set("attitude", "heroism");
        set("max_neili", 100000);
        set("neili", 1000000);
        set("max_jing", 500000000);
        set("jing", 500000000);
        set("max_qi", 10000000000);
        set("eff_qi", 10000000000);
        set("qi", 10000000000);
        set("jingli", 100000000);
        set("max_jingli", 100000000);


        set_skill("unarmed", 1);
        set_skill("dodge", 1);
        set_skill("parry", 1);
        set_skill("sword", 20);
        set_skill("dugu-jiujian", 20);  
        set_skill("force", 1);

        map_skill("sword", "dugu-jiujian");
        map_skill("parry", "dugu-jiujian");

        set("str", 2);
        set("int", 1);
        set("con", 1);
        set("dex", 1);

        setup();

        carry_object("/clone/weapon/zhujian")->wield(); 
}

void unconcious()
{
        //die();
        set("max_neili", 90000000);
        set("neili", 90000000);
        set("max_jing", 90000000);
        set("jing", 90000000);
        set("max_qi", 90000000);
        set("eff_qi", 90000000);
        set("qi", 90000000);
        set("jingli", 90000000);
        set("max_jingli", 90000000);
        revive();
}

void die()
{
        //unconcious();
        full_self();
        return;
}

int receive_damage(string type, int damage, object who)
{
        object ob, weapon, armor, armor2;
        string money;
        int amount;

        string *gift = ({
                "/clone/fam/pill/puti1",
                "/clone/fam/pill/puti2",
                "/clone/fam/pill/puti3",
                "/clone/fam/pill/lingzhi1",
                "/clone/fam/pill/lingzhi2",
                "/clone/fam/pill/lingzhi3",
                "/clone/fam/pill/linghui1",
                "/clone/fam/pill/linghui2",
                "/clone/fam/pill/linghui3",
                "/clone/fam/pill/sheli1",
                "/clone/fam/pill/sheli2",
                "/clone/fam/pill/sheli3",
        });
        
        string *gift2 = ({
                "/clone/armor/heitie-kai",
                "/clone/armor/longshen-toukui",
                "/clone/armor/wuzhe-huwan",     
                "/clone/fam/item/longxue",
                "/clone/armor/yecha2",
                "/clone/armor/yin-erhuan",
        });

        string *gift3 = ({
                "/clone/weapon/qinggang-jian",
                "/clone/weapon/ningyue-dao",
                "/clone/weapon/qingtong-zhang",
                "/clone/weapon/tiemu-gun",
                "/clone/weapon/longwei-bian",           
                "/clone/weapon/pangu-gong",

                "/clone/fam/gift/con2",
                "/clone/fam/gift/dex2",
                "/clone/fam/gift/int2",
                "/clone/fam/gift/str2",

                "/clone/armor/jinsi-beixin",
                "/clone/armor/heitie-kai",
                "/clone/armor/shangu-zhixing",
                
        });

        string *gift4 = ({
                "/clone/armor/jinsi-shoutao",
                "/clone/armor/shengling-yaodai",
                "/clone/armor/chiyou-zhanpao",
                "/clone/armor/shendiao-yumao",
                "/clone/armor/yecha1",
                "/clone/armor/yinyang-erhuan",
                "/clone/armor/biyu-chai",
        });

        if (! objectp(who))return 1;
        
/*
        // 转世后无效
        if( query("reborn/times", who) )
        {
                return 1;
        }
*/
        
        
        // 强行关闭战斗信息
        set("env/combatd", 4,   who);

        // 帝王符图
        // 编号39-42
        if( MEMBER_D->is_valid_member(who) && query("quest_tuteng/start", who) ) 
        {
                int n_tt;
                object ob_tt;
        
                if (random(10000) == 1 /*&& random(100) == 1*/)
                {
                        n_tt = 39 + random(4);
                        ob_tt = new("/clone/tuteng/diwang-suipian" + sprintf("%d", n_tt));
                        if (ob_tt)
                        {
                                write(HIG "你获得了一张帝王符图碎片。\n" NOR);
                                ob_tt->move(who, 1);
                        }
                }
        }
                
        // 五十万经验到八十万经验以下可增加经验和QN
        // 随机获得一些物品
        if( query("combat_exp", who) >= 500000 && query("combat_exp", who) <= 100000000 )
        {
                if( MEMBER_D->is_valid_member(who) )
                {                       
                        who->add("combat_exp", 600+random(800));
                        // 限制POT上限2000万
                        if( query("potential", who)-query("learned_points", who)<200000000 )
                        {
                                addn("potential", 300+random(400), who);
                        }
                        if( query("experience", who)-query("learned_experience", who)<100000000 )
                        {
                                addn("experience", 60+random(80),  who);
                        }
                }
                else
                {
                        who->add("combat_exp", 300+random(400));
                        if( query("potential", who)-query("learned_points", who)<200000000 )
                        {
                                addn("potential", 150+random(200),  who);
                        }
                        if( query("experience", who)-query("learned_experience", who)<100000000 )
                        {
                                addn("experience", 30+random(40),   who);
                        }
                }               

                // 获得钱
                if (random(1000) == 1)money = "gold";
                else if (random(400) == 1)money = "silver";
                else if (random(50) == 1)money = "coin";

                if (money)
                {
                        {
                                if( money == "gold")addn("balance", 100000, who);
                                if( money == "silver")addn("balance", 15000, who);
                                if( money == "coin")addn("balance", 400, who);

                                tell_object(who, HIG "你从神雕身上获得了一些金钱。\n"NOR);
                        }                                               
                }
                // 随机获得物品
                if (random(10000) == 1 && random(3) == 1)
                {
                        ob = new(gift[random(sizeof(gift))]);

                        if (objectp(ob))
                        {
                                ob->move(who, 1);
                                tell_object(who,HIR"你从神雕身上获得了一"+query("base_unit", ob)+ob->name()+"。\n"NOR);                         
                        }
                }
                if (random(100000) == 1 && random(3) == 1)
                {
                        weapon = new(gift2[random(sizeof(gift2))]);

                        if (objectp(weapon))
                        {
                                weapon->move(who, 1);
                                tell_object(who,HIR"你从神雕身上获得了一"+query("base_unit", weapon)+weapon->name()+"。\n"NOR);                         
                        }
                }
                if (random(300000) == 1 && random(3) == 1)
                {
                        armor = new(gift3[random(sizeof(gift3))]);

                        if (objectp(armor))
                        {
                                armor->move(who, 1);
                                tell_object(who,HIR"你从神雕身上获得了一"+query("base_unit", armor)+armor->name()+"。\n"NOR);                           
                        }
                }
                if (random(500000) == 1 && random(4) == 1)
                {
                        armor2 = new(gift4[random(sizeof(gift4))]);

                        if (objectp(armor2))
                        {
                                armor2->move(who, 1);
                                tell_object(who,HIR"你从神雕身上获得了一"+query("base_unit", armor2)+armor2->name()+"。\n"NOR);                         
                        }
                }
        }       

        // 经验不符合要求也可获得奖励，但几率更低
        else
        {
                // 获得钱
                if (random(500) == 1)money = "gold";
                else if (random(200) == 1)money = "silver";
                else if (random(50) == 1)money = "coin";

                if (money)
                {
                        {
                                if( money == "gold")addn("balance", 150000, who);
                                if( money == "silver")addn("balance", 15000, who);
                                if( money == "coin")addn("balance", 400, who);

                                tell_object(who, HIG "你从神雕身上获得了一些金钱。\n"NOR);
                        }                                               
                }

                // 随机获得物品
                if (random(10000) == 1 && random(3) == 1)
                {
                        ob = new(gift[random(sizeof(gift))]);

                        if (objectp(ob))
                        {
                                ob->move(who, 1);
                                tell_object(who,HIR"你从神雕身上获得了一"+query("base_unit", ob)+ob->name()+"。\n"NOR);                         
                        }
                }
                if (random(600000) == 1 && random(4) == 1)
                {
                        weapon = new(gift2[random(sizeof(gift2))]);

                        if (objectp(weapon))
                        {
                                weapon->move(who, 1);
                                tell_object(who,HIR"你从神雕身上获得了一"+query("base_unit", weapon)+weapon->name()+"。\n"NOR); 
                        }
                }
                if (random(800000) == 1 && random(5) == 1)
                {
                        armor = new(gift3[random(sizeof(gift3))]);

                        if (objectp(armor))
                        {
                                armor->move(who, 1);
                                tell_object(who,HIR"你从神雕身上获得了一"+query("base_unit", armor)+armor->name()+"。\n"NOR);            
                        }
                }
                if (random(1000000) == 1 && random(8) == 1)
                {
                        armor2 = new(gift4[random(sizeof(gift4))]);

                        if (objectp(armor2))
                        {
                                armor2->move(who, 1);
                                tell_object(who,HIR"你从神雕身上获得了一"+query("base_unit", armor2)+armor2->name()+"。\n"NOR);   
                        }
                }       
        }

        return ::receive_damage(type, damage, who);
}

void init()
{
        set("env/combatd", 4, this_player());
}
