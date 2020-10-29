// zhike.c 灵虚

#include <ansi.h>
//#include "daozhang.h"
inherit NPC;
//inherit F_MASTER;

void create()
{
        set_name("灵虚道长", ({ "lingxu daozhang", "lingxu", "daozhang" }));
        set("long", "他是武当山的知客道长，是宋远桥的弟子。守在山门迎接香客。\n");
        set("gender", "男性");
        set("nickname", "知客道长");
        set("age", 30);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "taoist");
        set("no_get", 1);
        set("no_steal",1);
        set("owner","mud_os");
        set("quest_no_guard",1);

        set("str", 20);
        set("int", 20);
        set("con", 25);
        set("dex", 20);

        set("max_qi", 800);
        set("max_jing", 400);
        set("neili", 500);
        set("max_neili", 500);

        set("combat_exp", 7500);
        set("score", 1000);

        set_skill("force", 80);
        set_skill("yinyun-ziqi", 40);
        set_skill("dodge", 80);
        set_skill("strike", 40);
        set_skill("wudang-zhang", 40);
        set_skill("parry", 80);
        set_skill("sword", 80);
        set_skill("wudang-jian", 80);
        set_skill("taoism", 20);

        map_skill("parry", "wudang-jian");
        map_skill("sword", "wudang-jian");
        map_skill("strike", "wudang-zhang");

        prepare_skill("strike", "wudang-zhang");

        set("chat_chance",2);
        set("chat_msg", ({
                 "灵虚道长说道：我武当地灵人杰，香火鼎盛，普天下的人都来朝拜敬香。\n",
                 "灵虚道长说道：玄岳门乃武当出入门户，我等一定要精心守卫(volunteer)，不可丝毫懈殆。\n"
                 "灵虚道长说道：香火练制不易，不能随便与人，虔诚奉献者方能得之。\n",
                 "灵虚道长说道：我武当地灵人杰，香火鼎盛，普天下的人都来朝拜敬香。\n",
                 "灵虚道长说道：听说山门前的松林里有异果，有砍树的道士进去找，就再也没有出来。\n",
        }));

        set("inquiry", ([
                "香火" : "香火练制不易，不能随便与人，虔诚奉献者方能得之。",
                "进香" : "进香？童言无忌！童言无忌！要说敬香才是！",
                "敬香" : "殿堂的香火能绵延不断，都因为我武当弟子和山外香客及时敬奉。",
                "虔诚奉献" : "虔诚奉献就是主动多捐献香火钱，多作义工。",
                "敬奉" : "虔诚奉献就是主动多捐献香火钱，多作义工。",
                "松林" : "武当松林在山门前面。",
                "柏林" : "武当柏林就在遇真宫后。",
                "name" : "我是武当的知客道长，负责守卫山门。",
                "here" : "这里是武当的玄岳门，一直南上就可到紫霄宫。",
                "rumors" : "听说山门前的松林里有异果，不知是真是假。"
                "可是有砍树的道士进去找，就再也没有出来。\n",
                "守卫" : "我这里的工作就是守卫(volunteer)山门，每次守一天。\n",
                "工作" : "我这里的工作就是守卫(volunteer)山门，每次守一天。\n",
                "干活" : "我这里的工作就是守卫(volunteer)山门，每次守一天。\n",
        ]));
        create_family("武当派", 3, "弟子");

        setup();
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"dao-cloth")->wear();
        carry_object(CLOTH_DIR"dao-shoe")->wear();
}

void init()
{
        object me = this_player();
        ::init();
        if (environment() != load_object("/d/wudang/xuanyuegate") ) return;

        add_action("do_volunteer","volunteer");

        if( !is_fighting() && living(this_object()))
        {
                if(interactive(me))
                {
                        remove_call_out("greeting");
                        call_out("greeting", 1, me);
                }
        }
}

void greeting(object ob)
{
        mapping myfam;
        if (environment(this_object())!=environment(ob))
        return;
        myfam=query("family", ob);
        if ( myfam && myfam["family_name"] == "武当派" )
                command("say这位道"+((query("gender", ob) == "女性")?"姑":"兄")+"辛苦了！");
        else if( query("title", ob) == "武当道童" )
                say("灵虚道长对"+ob->name()+"说道：这位"+RANK_D->query_respect(ob)+"还要继续努力啊！\n");
        else if( query("shen", ob)>-100 )
                say("灵虚道长作了个揖道：这位" + RANK_D->query_respect(ob) + "请了，欢迎来到武当山！\n");
        else        say("灵虚道长「唰」抽出长剑：这位" + RANK_D->query_respect(ob) + "满脸杀气，如果不是来武当敬香就请回吧！\n");
}

int do_volunteer()
{
        object me = this_player();
        object *ob;
        object *obs;
//      int i;

        if( query_temp("in_guard", me) )
                return notify_fail("知客道长对你说：你专心守好山门，别想打两份工。\n");

        if( query("family/family_name", me) != "武当派" )
        {
                message_vision("知客道长大喝一声：作为别派的弟子，我怎么放心你呢？！\n", me);
                return 1;
        }

        if( query("short", environment(this_object())) != "玄岳门" )
        {
                message_vision("哎呀，我怎么在这里呀，等我先回去。\n", me);
                return 1;
        }

        if( query("combat_exp", me) >= 400000 )
         {
                message_vision("知客道长一揖道：怎敢烦劳壮士做这粗活。\n", me);
                return 1;
        }

        ob = all_inventory(environment(me));
        obs = filter_array(ob,
                           (: interactive($1) &&
                           $1 != $(me) &&
                           query_temp("in_guard", $1) && 
                           environment($1) :));

        if (sizeof(obs) > 3)
                return notify_fail("知客道长对你说：已经有不少人守山门了，你一会再来吧。\n");

        tell_room(environment(me),query("name", me)+"开始在武当山门值守。\n");
        set("qi", 30000);
        set("jing", 30000);
        set_temp("in_guard", 1, me);

        // remove_call_out("end_guard");
        call_out("end_guard", 150, me);
        // remove_call_out("clone_meng");
        call_out("clone_meng", 30, me);
        return 1;
}

void clone_meng(object me)
{
        object ob;
        int maxskill;
        int maxexp;
        int maxqi;

        if (! me) return;

        if( !query_temp("in_guard", me) )
                return;

        maxskill = me->query_skill("force", 1);
        maxqi=query("eff_qi", me);
        maxexp=query("combat_exp", me);

        if( query("short", environment(me)) != "玄岳门" )
        {
                tell_object(me,"你在武当山门值守走开，失败。\n");
                call_out("end_guard", 0, me);
                return;
        }

        tell_room(environment(me), "山下突然冲上来一伙蒙面大汉。\n");

        ob = new("/d/wudang/npc/mengmian.c");
        if (! me->is_ghost())
        {
                ob->move(environment(me));
        }
        set("combat_exp", maxexp, ob);
        if (maxskill > 5 && maxexp > 50000)
        {
                ob->set_skill("kuang-jian", maxskill*2/3);
                ob->set_skill("sword", maxskill*2/3);
                ob->set_skill("parry", maxskill*2/3);
                ob->set_skill("unarmed", maxskill*1/2);
                ob->set_skill("dodge", maxskill*2/3);
        } else
        {
                ob->set_skill("kuang-jian", 5);
                ob->set_skill("sword", 5);
                ob->set_skill("parry", 5);
                ob->set_skill("unarmed", 5);
                ob->set_skill("dodge", 5);
        }
        set("qi", maxqi, ob);
        set("volunteer_owner",query("id",  me), ob);

        set("title", HIR"蒙面大汉"NOR, ob);
        ob->kill_ob(me);
        message_vision(HIR "\n$N对着$n大叫一声，杀啊!。\n" NOR, ob, me);
        tell_room(environment(me), "山下突然冲上来一伙蒙面大汉。\n");

        ob = new("/d/wudang/npc/mengmian.c");
        if (! me->is_ghost())
        {
                ob->move(environment(me));
        }

        set("combat_exp", maxexp, ob);
        if (maxskill > 5 && maxexp > 50000)
        {
                ob->set_skill("kuang-jian", maxskill);
                ob->set_skill("sword", maxskill);
                ob->set_skill("parry", maxskill);
                ob->set_skill("unarmed", maxskill);
                ob->set_skill("dodge", maxskill);
        } else
        {
                ob->set_skill("kuang-jian", 5);
                ob->set_skill("sword", 5);
                ob->set_skill("parry", 5);
                ob->set_skill("unarmed", 5);
                ob->set_skill("dodge", 5);
         }
        set("qi", maxqi, ob);
        set("volunteer_owner",query("id",  me), ob);

        set("title", HIR"蒙面大汉"NOR, ob);
        ob->kill_ob(me);
        me->kill_ob(ob);
        message_vision(HIR "\n$N对着$n大叫一声，杀啊!。\n" NOR, ob, me);

        call_out("clone_meng", 100, me);
}

void end_guard(object me)
{
        object *enemys;
        int i;
        if (! me) return;

        remove_call_out("clone_meng");
        if( !query_temp("in_guard", me))return ;

        delete_temp("in_guard", me);

        if( query("short", environment(me)) == "玄岳门" )
        {
                addn("family/gongji", random(8)+4, me);
                addn("combat_exp", random(220)+120, me);
                if( query("potential", me)>me->query_potential_limit() )
                        addn("potential", 1, me);
                else
                        addn("potential", random(50)+80, me);

                tell_room(environment(me),query("name", me)+"在武当山门值守期已满。\n");
                tell_object(me, "你在武当山门值守期已满。\n");
        } else
        {
                tell_room(environment(me),query("name", me)+"在武当山门值守走开，失败。\n");
                tell_object(me, "你在武当山门值守走开，失败。\n");
        }
        enemys = children("/d/wudang/npc/mengmian");
        enemys = filter_array(enemys, (: query("volunteer_owner", $1) == $(query("id",me)) :));
        if (sizeof(enemys) > 0)
        {
                for (i = 0; i < sizeof(enemys); i++)
                {
                        if (enemys[i]->is_fighting())
                        {
                                enemys[i]->remove_all_killer();
                                tell_room(environment(enemys[i]), HIW "只见" + enemys[i]->name()
                                        + "突然面色一变，迅速攻出几招，跳出战圈转身逃了。\n");
                        }
                        else {
                                tell_room(environment(enemys[i]), HIW "只见" + enemys[i]->name()
                                        + "掐值一算，突然脸色大变，急急忙忙地逃走了。\n");
                        }
                        destruct(enemys[i]);
                }
        }
}

void die()
{
        object *me, *enemys;
        int i;

        me = all_inventory(environment());

        for (i = 0; i < sizeof(me); i ++)
                delete_temp("in_guard", me[i]);

        enemys = children("/d/wudang/npc/mengmian");
        if (sizeof(enemys) > 0)
        {
                for (i = 0; i < sizeof(enemys); i++)
                {
                        if (enemys[i]->is_fighting())
                        {
                                enemys[i]->remove_all_killer();
                                tell_room(environment(enemys[i]), HIW "只见" + enemys[i]->name()
                                        + "突然面色一变，迅速攻出几招，跳出战圈转身逃了。\n");
                        }
                        else {
                                tell_room(environment(enemys[i]), HIW "只见" + enemys[i]->name()
                                        + "掐值一算，突然脸色大变，急急忙忙地逃走了。\n");
                        }
                        destruct(enemys[i]);
                }
        }
        ::die();
}

int accept_object(object who, object ob)
{
        object obn/*, wage*/;
//      int i,j;
//      string *wanted;
        if( query("money_id", ob) && ob->value() >= 100*query("age", who) )
        {
                if( (query("family/family_name", who)) == "武当派" )
                        tell_object(who,"灵虚道长哈哈一笑：既然道"+((query("gender", who) == "女性")?"姑":"兄")+"如此诚心向道，我这有新制香火一枝，请拿去贡奉吧。\n");
                else
                        tell_object(who, "灵虚道长哈哈一笑：既然施主如此诚心向道，我这有新制香火一枝，请施主拿去贡奉吧。\n");
                obn = new("/d/wudang/obj/incense");
                obn->move(who);
                return 1;
        }
        else
                if( query("money_id", ob) )
                {
                        if( (query("family/family_name", who)) == "武当派" )
                                tell_object(who,"灵虚道长对你赞叹道：武当山香火鼎盛，全靠象道"+((query("gender", who) == "女性")?"姑":"兄")+"你这样捐献香火啊！\n");
                        else
                                tell_object(who, "灵虚道长对你赞叹道：武当山香火鼎盛，全靠象您这样的虔诚香客啊！\n");
                        return 1;
                }
        return 0;
}