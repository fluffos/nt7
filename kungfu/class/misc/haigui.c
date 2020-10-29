// donghai.c

#include <ansi.h>

int is_neili_cow() { return 1; }

inherit BOSS;

string get_long();

void create()
{
        set_name(NOR + YEL "万年海龟" NOR, ({ "hero of chelonian", "chelonian", "hero" }) );
        set("title", HIM "练功法宝" NOR);
        set("gender", "男性");
        set("age", 88888);
        set("long", get_long());

        set("combat_exp", 90000000);
        set("shen_type", 0);
        set("attitude", "heroism");
        set("max_neili", 90000000);
        set("neili", 90000000);
        set("max_jing", 90000000);
        set("jing", 90000000);
        set("max_qi", 90000000);
        set("eff_qi", 90000000);
        set("qi", 90000000);
        set("jingli", 90000000);
        set("max_jingli", 90000000);

        set("str", 1);
        set("int", 30);
        set("con", 1);
        set("dex", 1);
        set("jiali", 0);

        set("clear_fuben", 1);

        setup();
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
        set("max_neili", 90000000);
        set("max_jing", 90000000);
        set("max_jingli", 90000000);
        set("jingli", 90000000);
        full_self();
        return;
}

string get_long()
{

                string msg;

                msg =  "\n" NOR + YEL
"打不死的万年英雄海龟，适合用来实验武功或暴力发泄！\n" HIC
"先天悟性：1\n"
"先天根骨：30\n"
"先天身法：1\n"
"先天臂力：1\n"
"加   力： 0\n"
"危险程度：微小\n" HIG
"可使用指令 crave <信息> 在海龟背上进行雕刻！\n\n" HIR 
"但见万年海龟背上密密麻麻刻满了很多文字。\n\n" NOR;

        return msg;
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
                "/clone/weapon/qinggang-jian",
                "/clone/weapon/ningyue-dao",
                "/clone/weapon/qingtong-zhang",
                "/clone/weapon/tiemu-gun",
                "/clone/weapon/longwei-bian",
                "/clone/weapon/pangu-gong",
                "/clone/armor/yin-erhuan",
        });

        string *gift3 = ({
                "/clone/armor/tie-shoutao",
                "/clone/armor/shenwu-xiangquan",
                "/clone/armor/gangtie-kai",
                "/clone/armor/zhanshen-toukui",
        });     

        string *gift4 = ({
                "/clone/armor/wushi-pifeng",
                "/clone/armor/feima-xue",
                "/clone/armor/yecha2",
                "/clone/armor/zijinhua-erhuan",
                "/clone/armor/xingyue-erhuan",
        });

        if (! objectp(who))return 1;

/*
        // 转世后无效
        if (query("reborn/times", who))
        {
                return 1;
        }
*/
        
        set("env/combatd", 4, who);
        
        
                // 帝王符图
                // 编号36-38
                if( MEMBER_D->is_valid_member(who) && query("quest_tuteng/start", who) ) 
                {
                        int n_tt;
                        object ob_tt;
        
                        if (random(10000) == 1 /*&& random(100) == 1*/)
                        {
                                n_tt = 36 + random(3);
                                ob_tt = new("/clone/tuteng/diwang-suipian" + sprintf("%d", n_tt));
                                if (ob_tt)
                                {
                                        write(HIG "你获得了一张帝王符图碎片。\n" NOR);
                                        ob_tt->move(who, 1);
                                }
                        }
                }
                        
        // 十万经验以下可增加经验和QN
        // 随机获得一些物品
        if (query("combat_exp", who) <= 50000000)
        {
                if (MEMBER_D->is_valid_member(who))
                {
                        who->add("combat_exp", 600 + random(800));
                        if( query("potential", who)-query("learned_points", who)<200000000 )
                        addn("potential", 300 + random(400), who);
                        if( query("experience", who)-query("learned_experience", who)<100000000 )
                        addn("experience", 60 + random(80), who);
                }
                else
                {
                        who->add("combat_exp", 300 + random(400));  
                        if( query("potential", who)-query("learned_points", who)<200000000 )
                        addn("potential", 150 + random(200), who);
                        if( query("experience", who)-query("learned_experience", who)<100000000 )
                        addn("experience", 30 + random(40), who);
                }
                // 获得钱
                if (random(200) == 1)money = "gold";
                else if (random(100) == 1)money = "silver";
                else if (random(30) == 1)money = "coin";

                if (money)
                {
                        {
                                if( money == "gold")addn("balance", 10000, who);
                                if( money == "silver")addn("balance", 1500, who);
                                if( money == "coin")addn("balance", 40, who);

                                tell_object(who, HIG "你从万年海龟身上获得了一些金钱。\n" NOR);
                        }                                               
                }       
                // 随机获得物品
                if (random(10000) == 1 && random(3) == 1)
                {
                        ob = new(gift[random(sizeof(gift))]);

                        if (objectp(ob))
                        {
                                ob->move(who, 1);
                                tell_object(who, HIR "你从万年海龟身上获得了一" + query("base_unit", ob) + ob->name() + "。\n" NOR);                            
                        }
                }
                if (random(100000) == 1 && random(3) == 1)
                {
                        weapon = new(gift2[random(sizeof(gift2))]);

                        if (objectp(weapon))
                        {
                                weapon->move(who, 1);
                                tell_object(who, HIR "你从万年海龟身上获得了一" + query("base_unit", weapon) + weapon->name() + "。\n" NOR);                            
                        }
                }
                if (random(300000) == 1 && random(4) == 1)
                {
                        armor = new(gift3[random(sizeof(gift3))]);

                        if (objectp(armor))
                        {
                                armor->move(who, 1);
                                tell_object(who, HIR "你从万年海龟身上获得了一" + query("base_unit", armor) + armor->name() + "。\n" NOR);                              
                        }
                }
                if (random(500000) == 1 && random(4) == 1)
                {
                        armor2 = new(gift4[random(sizeof(gift4))]);

                        if (objectp(armor2))
                        {
                                armor2->move(who, 1);
                                tell_object(who, HIR "你从万年海龟身上获得了一" + query("base_unit", armor2) + armor2->name() + "。\n" NOR);                            
                        }
                }
        }       

                
        return ::receive_damage(type, damage, who);
        
}
