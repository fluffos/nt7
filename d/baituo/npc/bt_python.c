// Code of JHSH
// baituo python 白驼山蛇谷的大蛇、蟒蛇
// by maco
#include <ansi.h>

inherit SNAKE;

int auto_perform_duwu();
int auto_perform_chan();

void create()
{
        int s, p;

        s = random(40);
        p = random(3);
        set_weight(12000);

        switch( p )
        {
        case 0:
                set_name("巨蟒", ({ "ju mang", "she", "mang", "python" }) );
                set("long", "一条碗口粗细的三角头巨蟒，有两丈多长。\n");
                set("chat_msg_combat", ({
                        (: auto_perform_chan :),
                }));
                break;
        case 1:
                set_name("大蛇", ({ "da she", "she", "snake", "dashe" }) );
                set("long", "一条身长两丈，粗如人臂的大蛇，全身斑斓五色，一颗头作三角形，比人的拳头还大。\n"
                "寻常大蛇无毒，此蛇如此巨大，却是毒蛇，实在罕见。\n");
/*
        set("snake_poison", ([
                "level"  : 200,
                "perhit" : 60,
                "remain" : 100,
                "maximum": 100,
                "supply" : 5,
        ]));
*/

                set("chat_msg_combat", ({
                        (: auto_perform_duwu :),
                }));
                break;
        case 2:
                set_name("毒蟒", ({ "du mang", "she", "mang", "snake", "python"}) );
                set("long", "一条白身黑章的大蟒蛇，蟒头作三角形，头顶上高高生了一个\n"
                "凹凹凸凸的肉瘤，身长二丈，粗逾手臂。\n"
                "蟒蛇本来无毒，这条大蟒却生的如此异状，又具剧毒，实是希罕。\n");
/*
        set("snake_poison", ([
                "level"  : 200,
                "perhit" : 60,
                "remain" : 100,
                "maximum": 100,
                "supply" : 5,
        ]));
*/

                set("chat_msg_combat", ({
                        (: auto_perform_chan :),
                        (: auto_perform_duwu :),
                }));
                break;
        }

        set("age", 100);
        set("attitude", "peaceful");

        set("str", 30 + p );
        set("con", 40 + p );
        set("int", 10);
        set("dex", 30 + p );

        set("max_jing", 4000);
        set("max_qi", 4000);
        set("max_jingli", 2000);

        set("combat_exp", p*100000 + 500000);
        set("chat_chance_combat", 30);

        set_temp("apply/attack", 300 + s);
        set_temp("apply/damage", 200 + s);
        set_temp("apply/armor", 400 + s);
        set_temp("apply/parry", 300 + s);
        set_temp("apply/dodge", 260 + s);
        set("bt_snake", 1);

        setup();
}

void init()
{
        object me;
        ::init();
        me = this_object();
        add_action("convert","bian");
        add_action("do_struggle","struggle");
        add_action("do_struggle","zhengza");

        if (!me->is_fighting() && living(me) && !me->is_busy()
         && !query("no_fight", environment(me))){
                remove_call_out("hunting");
                call_out("hunting", 1, me, this_player());
        }
}

void hunting(object me, object ob)
{
    if (! objectp(me) || ! objectp(ob))
        return;

        if(random(4) != 0 && !me->is_fighting() && living(me) && !me->is_busy()
         && !query("no_fight", environment(me)) )
                set_temp("hunting",query("id", ob));

        if (present(ob, environment(me))) {
                if( !ob->is_character() && query("my_killer", ob) != query("id", me)){
                        message_vision("$N在$n旁边绕了几圈，嘶地一吐信，慢慢蜿蜒游开，似乎不感兴趣。\n", me, ob);
                        return;
                }
                else if( query_temp("hunting") && !me->is_fighting() && living(me)
                 && !me->is_busy() && !query("no_fight", environment(me))){

                        if(random(2) == 0) {
                        message("vision", HIR"你忽然闻得一阵腥风，猛见"+me->name()+"张开大口，露出獠牙，疾向"+ob->name()+"咬去！\n"NOR, environment(ob), ob);
                        tell_object(ob,HIR"你耳中忽闻嘶嘶声响，一迟疑间，蓦地腥臭迎面，"+me->name()+"猛然向你张口扑来！\n"NOR);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        kill_ob(ob);
                        delete_temp("hunting");
                        }
                        else {
                        remove_call_out("hunting");
                        call_out("hunting", 2, me, ob);
                        }
                        return;
                }

                else message_vision("$N听到$n过来的声息，立时盘曲成团，昂起了头，伸出血红的舌头，嘶嘶作声。\n", me, ob);
        }
        return;
}


void chaning(object me, object ob)
{
        int ap, dp, pp, jingli, damage;

        string *chan_msg = ({
                HIR"\n$n暗运劲力，想将缠在身上的$N崩断。但$N身子可伸可缩，只略加延伸，并不会断。\n"NOR,
                HIR"\n$N猛力缠紧，只箍得$n腰骨几欲折断。\n"NOR,
                HIR"\n$N身子一卷到$n，越收越紧，再也不放，$n渐渐给$N缠得喘不过气来。\n"NOR,
                HIR"\n$n被$N缠住，除了呻吟怒骂，再无反抗的能为。\n"NOR,
        });
        string *chan_beast_msg = ({
                HIR"\n$N猛力缠紧，不让$n有机会逃脱。\n"NOR,
                HIR"\n$N身子一卷到$n，越收越紧，再也不放，$n渐渐给$N缠得喘不过气来。\n"NOR,
                HIR"\n$n被$N缠住，慢慢失了抗拒之力，气息越来越是微弱。\n"NOR,
        });

        string *chan_snake_msg = ({
                HIR"\n$N猛力缠紧，牢牢箍住$n的七寸。\n"NOR,
                HIR"\n$N身子一卷到$n，越收越紧，再也不放，$n渐渐给$N缠得喘不过气来。\n"NOR,
                HIR"\n$N将$n紧紧缠住，慢慢施力，$n虽然不断扭动蛇身，却也无法脱困。\n"NOR,
        });
        string *chan_bird_msg = ({
                HIR"\n$N猛力缠紧，只箍得$n双翅几欲折断。\n"NOR,
                HIR"\n$n被$N缠住，吱吱乱叫，翅膀不停扑打。\n"NOR,
                HIR"\n$N愈盘愈紧，$n毛羽贲张，竭力相抗，眼见不支。\n"NOR,
        });

        string chan;
        switch(query("race", ob)){
        case "人类" :        chan = chan_msg[random(sizeof(chan_msg))];        break;
        case "飞禽" :        chan = chan_bird_msg[random(sizeof(chan_bird_msg))];        break;
        case "蛇类" :        chan = chan_snake_msg[random(sizeof(chan_snake_msg))];        break;
        case "野兽" :
        case "家畜" :        chan = chan_beast_msg[random(sizeof(chan_beast_msg))];        break;
        default:        return 0;
        }


        jingli=query("jingli", me);
        ap = jingli + random(jingli);
        pp=query("jiali", ob)+ob->query_str()*random(10)+ob->query_skill("force");
        damage = (ap - pp)/3;

        if(damage > 1000 ) damage = 1000;
        if(damage < 100 ) damage = 100;

        if(wizardp(ob))
        tell_object(ob,sprintf("ap：%d ,pp：%d ,damage：%d \n" ,ap,pp,damage));

        if(!ob) {
                delete_temp("chaning", me);
                return;
        }
        if (present(ob, environment(me))) {

                if( !query_temp("chaning", me) || !query_temp("snake_chan", ob)){
                delete_temp("chaning", me);
                delete_temp("snake_chan", ob);
                return;
        }

                if (!living(ob) ) {  //猎物昏了就咬死
                        if( query("race", ob) == "人类" )
                                message_vision(HIR"这时$n已给$N缠得奄奄一息，$N张开大口，咬住了$n，腿脚先入蛇口，慢慢的给吞至腰间，又吞至胸口。\n"NOR, me, ob);
                        else message_vision(HIR"这时$n已给$N缠得奄奄一息，$N张开大口，一口便将$n咬死。\n"NOR, me, ob);
                        ob->receive_wound("qi",(query("qi", ob)+100),"被"+me->name()+"咬死了");
                        ob->receive_damage("qi",(query("qi", ob)+100),"被"+me->name()+"咬死了");
                        delete_temp("snake_chan", ob);
                        delete_temp("chaning", me);

                        return;
                }

                else if (!ob->is_character() ) {  //猎物死了就放开
                        message_vision("$N松开身子，放开了$n，四下蜿蜒游走。\n", me, ob);
                        delete_temp("snake_chan", ob);
                        delete_temp("chaning", me);
                        return;
                }
                else {

                        if(ap < random(pp) || jingli < 500 ) {
                        message_vision("$N似乎敌不过$n的劲力，慢慢松开身子，放开了$n，四下蜿蜒游走。\n", me, ob);
                        delete_temp("snake_chan", ob);
                        delete_temp("chaning", me);
                        }
                        else {
                        message_vision(chan , me, ob);
                        ob->start_busy(3);
                        me->start_busy(2);
                        addn("jingli", -(pp/20), me);

                        addn("jingli", -damage/4, ob);
                        ob->receive_wound("qi", random(damage/10), "被"+me->name()+"缠死了");
                        ob->receive_damage("qi", damage/2, "被"+me->name()+"缠死了");

                        remove_call_out("chaning");
                        call_out("chaning", 1, me, ob);
                        }
                        return;
                }
        }

        return;
}


int convert(string arg)
{
        object me = this_player();
        object ob;

        if (arg!="snake" && arg!="she") return 0;
        if( query("family/family_name", me) != "欧阳世家" )
                return notify_fail("你不能化蛇为杖。\n");

        return notify_fail(this_object()->name()+"身子太过粗大，无法化为蛇杖。\n");
}

int do_struggle(string arg)
{
        object me, snake;
        int ap, jingli, jiali;

        me = this_player();
        snake = this_object();

        if( query_temp("chaning", snake) != query("id", me) )
                return 0;
        if( !query_temp("snake_chan", me) || !me->is_busy() )
                return 0;

        jingli=query("jingli", snake);
        jiali=query("jiali", me);
        ap = jingli + random(jingli);

        if( query_temp("struggle_snake", me)>4){
                message_vision(HIW"\n$N用力挣了一挣，想摆脱缠住身子的$n.....\n"NOR, me, snake);
                message_vision(HIR"\n不料$N身子动得太厉害，激怒了缠住了$P的$n，一口便咬住$P的咽喉！\n"NOR, me, snake);
                me->receive_wound("qi", random(ap/2), "被"+me->name()+"咬死了");
                me->receive_damage("qi", ap/2, "被"+me->name()+"咬死了");
                me->unconcious();
        }
        else {
                message_vision(HIW"\n$N用力挣了一挣，想摆脱缠住身子的$n.....\n"NOR, me, snake);
                addn("neili", -jiali, me);
                addn("jingli", -jiali*2, snake);
                addn_temp("struggle_snake", 1, me);
                remove_call_out("remove_effect");
                call_out("remove_effect", 1, me);
        }

        return 1;
}

void remove_effect(object me)
{
        delete_temp("struggle_snake", me);
}

#include "snake_perform.h"