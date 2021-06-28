// caiyao.h  采药
// sdong 08/06/98

#include <ansi.h>
#include <medical.h>

void setup_ob(object me,object victiom);
string *herbs = ({
        HERB("chuanbei"),
        HERB("fuling"),
        HERB("gouzhizi"),
        HERB("heshouwu"),
        HERB("huanglian"),
        HERB("jugeng"),
        HERB("jinyinhua"),
        HERB("shengdi"),
});

string *beasts = ({
        "/clone/beast/snake",
        "/clone/beast/bee",
        "/clone/beast/wuya",
        "/clone/beast/yetu",
        "/clone/beast/deer",
        "/clone/beast/monkey",
});


void init()
{
        object ob = this_player();
        add_action("do_search", "bo");
        add_action("do_search", "search");
        add_action("do_dig", "wa");
        add_action("do_dig", "dig");

        if (interactive(ob))
        {
                delete_temp("herb", ob);
                if( query_temp("qz/caiyao", ob) )
                        set("count",random(4));
        }
}

int do_search(string arg)
{
        object me/*,ob*/;
        int power;


        me = this_player();

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("你正忙着。\n");

        if( query_temp("herb/got", me) )
                return notify_fail("这里已经找过了，再找也找不出什么了！\n");

        if( !present("yao chu", me) )
                return notify_fail("你没有工具，无法拨开灌木山草寻找草药！\n");

        if( query("jing", me)<30 )
                return notify_fail("你太累了，先歇息一会儿吧。\n");

        addn_temp("herb/times", 1, me);
        me->receive_damage("jing", 5);
        me->start_busy(1+random(2));

        if( query("count")<1 && query_temp("herb/times", me)>30 )
                return notify_fail("你把四周的灌木杂草都翻遍了，可是没发现什么，看来这里没指望了！\n");

        message_vision("$N用药锄拨动着四周的灌木杂草，仔细地看有没有草药！\n", me);

        power=query_temp("herb/times", me)*(query("kar", me)+query("int", me)+query("str", me))/3;
        power *= query("count");

        if( power/2 + random(power/2) > 100 ) {
                set_temp("herb/found", 1, me);
                message_vision(HIG"\n$N用药锄不断的拨动着四周的山草，忽然发现杂草之中有一株特别的草！\n"NOR, me);
                return 1;
        }

        /*
          if( random(10) == 1 && query("combat_exp", me)>10000 )
          {
                ob=new(beasts[random(sizeof(beasts))]);
                ob->move(environment(me));
                message_vision(HIR"突然从草丛中惊起一只$N，它大概受了惊吓，发疯似地向$n发起进攻！\n"NOR, ob,me);

                if( query("id", ob) == "xiaobaozi")setup_ob(ob,me);
                ob->kill_ob(me);
                ob->start_busy(1+random(3));
                return 1;
          }
        */

        /*
        if( random(101) == 50 && query("combat_exp", me)>10000 )
        {
                message_vision(HIR"\n$N一不小心用力过猛，忽听嘎巴一声，药锄断为两截！\n"NOR, me);
                ob = present("yao chu", me);
                if(ob)destruct(ob);
        }*/
        return 1;
}

void setup_ob(object me,object victim)
{
//      object *inv;
        mapping skill_status;
        string *sname;
        int i, max = 0, max1/*, j*/;


        if( !query_temp("copied", me)){
                if ( mapp(skill_status = victim->query_skills()) ) {
                        skill_status = victim->query_skills();
                        sname = keys(skill_status);

                        for(i=0; i<sizeof(skill_status); i++) {
                                if ( skill_status[sname[i]] > max ) max = skill_status[sname[i]];
                        }


                        max1 = (int)max + random(max);

                        //max = (int)max*3/4 + 1 + random((int)max/4);

                        if( query("combat_exp", victim)<10000)max1/=2;
                        me->set_skill("dodge", max1);
                        me->set_skill("parry", max1 );
                        me->set_skill("force", max1);

                         set("combat_exp", query("combat_exp", victim) + random(query("combat_exp",victim)/ 10), me); 

                        set("max_qi",query("max_qi",  victim), me);
                        set("eff_qi",query("max_qi",  victim), me);
                        set("max_jing",query("max_jing",  victim), me);
                        set("eff_jing",query("max_jing",  victim), me);
                        set("qi",query("max_qi",  me), me);
                        set("jing",query("max_jing",  me), me);
                        set("jiali",query("jiali",  victim)*3/4, me);
                        if( query("max_jingli", victim)>0){
                                set("max_jingli",query("max_jingli",  victim), me);
                        }
                        else set("max_jingli", 500, me);
                        set("jingli",query("max_jingli",  me), me);

                        set("no_sing", 1, me);
                        set_temp("copied", 1, me);
                }
        }
}

int do_dig(string arg)
{
        object me, ob,herb;
        int exp;
        int pot;

        me = this_player();

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("你正忙着。\n");
        if( !(ob = present("yao chu", me)) )
                return notify_fail("你没有药锄，怎么挖？\n");

        if( query("jing", me)<25 )
                return notify_fail("你太累了，先歇息一会儿吧。\n");

        me->receive_damage("jing", 20);
        me->start_busy(1);

        if( !query_temp("herb/found", me)){
                message_vision("$N拿着药锄使劲的挖着土，忽听嘎巴一声，药锄断为两截！\n", me);
                destruct(ob);
                return 1;
        }

        addn("count", -1);
        herb = new(herbs[random(sizeof(herbs))]);
        herb->move(me, 1);
        set("player",query("id",  me), herb);

        message_vision(HIY"$N用药锄小心翼翼的把$n"+HIY"从土中起出！\n"NOR, me,herb);
        if( query_temp("qz/caiyao", me) )
        {
                exp = 100 + random( 180 );
                pot = exp/3;

                GIFT_D->work_bonus(me, ([ "exp" : exp, "pot" : pot, "gongxian" : 5+random(6),
                                          "prompt" : "你通过挖药材" ]));
        }

        message_vision(HIR"\n$N兴奋过度，把药锄一甩，忽听嘎巴一声，药锄断为两截！\n"NOR, me);
        destruct(ob);
        delete_temp("herb/found", me);
        set_temp("herb/got", 1, me);
        return 1;
}