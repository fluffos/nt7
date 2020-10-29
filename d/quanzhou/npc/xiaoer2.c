#include <ansi.h>
#include <command.h>

inherit NPC;

void create()
{
        set_name("店小二", ({ "xiao er", "xiao", "waiter" }) );
        set("gender", "男性" );
        set("age", 22);
        set("long", "这位店小二正笑咪咪地忙著，还不时拿起挂在脖子上的抹布擦脸。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("rank_info/respect", "小二哥");
        setup();
        if (clonep()) keep_heart_beat();
}

void init()
{
        object ob;

        ::init();

        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        // add_action("do_drop", "drop");
}

void greeting(object ob)
{
        if ( ! ob || environment(ob) != environment() ) return;
        switch( random(2) )
        {
        case 0:
                say( CYN "店小二笑咪咪地说道：这位" + RANK_D->query_respect(ob)
                   + CYN + "，进来喝杯茶，歇歇腿吧。\n" NOR);
                break;
        case 1:
                say( CYN "店小二用脖子上的毛巾抹了抹手，说道：这位" + RANK_D->query_respect(ob)
                   + CYN + "，请进请进。\n" NOR);
                break;
        }
}

int accept_object(object me, object ob)
{

        if( query("money_id", ob) && ob->value() >= 1000 )
        {
                tell_object(me, CYN "小二一哈腰，说道：多谢您老，客官请上楼歇息。\n" NOR);
                set_temp("rent_paid", 1, me);
                return 1;
        }

        switch (random(6))
        {
        case 0:
                command("say 好！好！");
                break;
        case 1:
                command("say 不需要的东西全给我！");
                break;
        }

        if (! ob->is_character())
        {
                destruct(ob);
                return -1;
        }
        return 1;
}

void heart_beat()
{
        string start_room;
        object ob;

        if (stringp(start_room = query("startroom"))
           && find_object(start_room) == environment())
        {
                foreach (ob in all_inventory(environment()))
                {
                        if (! ob->is_character()
                           || interactive(ob)
                           || playerp(ob)
                            || query_temp("owner", ob) )
                                continue;

                        if( stringp(start_room=query("startroom", ob) )
                           && find_object(start_room) == environment())
                                continue;

                        if( query("id", ob) == "corpse" )
                                message_vision(HIC "\n$N" HIC "站起身，把$n" HIC "拎到"
                                               "门外，然后又若无其事地走了回来。\n\n"
                                               NOR, this_object(), ob);
                        else if( query("race", ob) != "野兽" )
                                message_vision(CYN "\n$N" CYN "对$n" CYN "满脸歉然地说"
                                               "道：对不住，小店已经满座了。\n" HIC "$n"
                                               HIC "听后一愣，摇了摇头，骂骂咧咧地转身"
                                               "离去。\n" NOR, this_object(), ob);
                        ob->move("/d/quanzhou/northroad1");
                }
        }
        ::heart_beat();
}

int do_drop(string arg)
{
        int i;
        object *obs;
        object ob;
        object me;

        if (! arg)
                return 0;

        me = this_player();
        if (objectp(ob = present(arg, me)) &&
            ob->is_character() && ! playerp(ob))
        {
                addn_temp("static/drop_npc", 1, me);
                if( query_temp("static/drop_npc", me)>1 && 
                    query("combat_exp", me) >= 50000 )
                {
                        message_vision(CYN "\n$N" CYN "大怒道：好你个" + RANK_D->query_rude(ob)
                                       + CYN "，还敢来添乱？\n" NOR + HIC "说罢$N" HIC "一声大"
                                       "叫，北丑顿时冲了出来，飞起两脚，将$n" HIC "和" + ob->name()
                                       + HIC "一起踢了出去。\n\n" NOR, this_object(), me);

                        ob->move("/d/quanzhou/northroad1");
                        me->move("/d/quanzhou/northroad1");
                        message("vision", HIC "只听客店处砰叮咣啷一阵轰响，便见" + me->name()
                                          + HIC "和" + ob->name() + HIC "一起飞了出来。\n"
                                          NOR, environment(me), me);

                        me->receive_damage("qi", 1);
                        ob->die();
                        me->unconcious();
                        return 1;
                }

                message_vision(CYN "\n$N" CYN "怒道：晦气，晦气！这里又不是棺材店，你搬个要死"
                               "的人进来干嘛？\n" NOR + HIC "说罢$N" HIC "一招手，顿时来了一群"
                               "彪形大汉，将$n" HIC "和" + ob->name() + HIC "一起赶了出去。\n\n"
                               NOR, this_object(), me);

                ob->move("/d/quanzhou/northroad1");
                me->move("/d/quanzhou/northroad1");
                message("vision", HIC "只听客店处传来一阵轰闹声，" + me->name() + HIC "被人赶"
                                  "了出来，随后半死不活的" + ob->name() + HIC "也被扔了出来。"
                                  "\n" NOR, environment(me), me);
                me->receive_damage("qi", 1);
                return 1;
        }

        if (! DROP_CMD->main(me, arg))
                return 0;

        if (! GET_CMD->main(this_object(), arg))
                return 1;

        obs = all_inventory(this_object());
        for (i = 0; i < sizeof(obs); i++)
                if (! obs[i]->is_character()) destruct(obs[i]);
        if (! random(5))
        {
                switch (random(4))
                {
                case 0:
                        command("say 你不要我要！");
                        break;
                case 1:
                        command("sigh"+query("id", this_player()));
                        command("say 糟蹋啊，作孽啊！");
                        break;
                case 2:
                        command("say 败家子，败家子！");
                        break;
                default:
                        command("heihei");
                        break;
                }
        }
        return 1;
}