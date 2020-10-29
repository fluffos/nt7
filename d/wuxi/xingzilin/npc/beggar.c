// This program is a part of NITAN MudLIB 
// redl 2012/11/1 
#include <ansi.h>
#include "../cnpc.h"

inherit NPC;

void create()
{
        set_name(NOR "无名老乞丐" NOR, ({ "old beggar","beggar" }) );
        set("gender", "男性");
        set("age", 80);
        set("long", NOR"    这是一个神秘的老乞丐，不知道为什么悄悄躲在这山洞里。"NOR);
        set("attitude", "peaceful");
        set("str", 50);
        set("con", 30);
        set("int", 24);
        set("dex", 30);
        set("per", 13);

        set("chat_chance", 3);
        set("chat_msg", ({
                CYN"老乞丐狠狠地道：该死的四大恶人，投靠一品堂助纣为虐。\n"NOR ,
                CYN"老乞丐自傲说道：丐帮为中原第一大帮，岂能向一品堂伏低。\n"NOR ,
                CYN"老乞丐喃喃念道：今丐帮已檄告天下各路英豪，重金悬赏四大恶人的头颅。\n"NOR ,
                CYN"老乞丐微笑着说：凡获恶人首级一枚者，皆可于我这里兑换奖励。\n"NOR ,
        }) );

        set("combat_exp", 10000000);

        setup();

}

int accept_object(object me, object obj)
{
        int amount,exp;
        
        if( !query("xzz/headlv", obj) )
        {
                tell_object(me,CYN "老乞丐摇了摇头，对你说道：我只要恶人首级。\n" NOR); 
                return 0;
        }
        
        if( query("level", me) < 10)
        {
                tell_object(me,CYN "老乞丐奇怪地看了你一眼说：凭你这本事也能拿下四大恶人？\n" NOR); 
                return 0;
        }
        
        exp = GIVEHEAD_GIFT_EXP;

        if (function_exists("query_amount",obj))
                amount = obj->query_amount();
        else 
                amount = 1;

        exp *= amount;


                if( query("level", me) <= 30 ) //1000w+ exp后方可获得正常奖励，方便森林副本后接本任务
        {
                }
                else if( query("level", me) <= 60 )
                {
                        exp /= 2;
                }
                else if( query("level", me) <= 100 )//放宽此处，小小刺激培养大米来割头，和小规模冲突
                {
                        exp /= 4;
                }
                else //中后期的练功id，已经完全看不上这100点了
                {
                        exp = 100;
                }

                        exp = invert_reborngiftd(me, exp);

        GIFT_D->work_bonus(me, ([ "exp" : exp, "pot" : exp/5, "mar" : exp/16, "score" : exp/100 ]));//pot奖励不可太多，造成乱选乱学skill

        destruct(obj);
        return 1;
}

