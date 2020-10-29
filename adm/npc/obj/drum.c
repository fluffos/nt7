// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

#include <ansi.h>

inherit ITEM;
void de_group(object *fighters);
void checking(object ob1, object ob2);
int  att_fight(object ob1, object ob2);
void recover(object ob);
int  sort_user(object ob1, object ob2);
string clear_title(string arg);
void add_title(object me, string arg);
void init_player(object me);
void restore_status(object me);
void auto_check();
int  check_quit(object me);
int  check_out(object me);
int give_money(object *players,object *fighters);
void message_competition(string msg);
nosave object *total = ({ });

#define LUNJIAN         "/d/huashan/lunjian"
#define ENTRY_ROOM      "/adm/npc/huashanjueding"
#define FIRST           "/clone/medal/lunjian_xunzhang1"
#define SECOND          "/clone/medal/lunjian_xunzhang2"
#define THIRD           "/clone/medal/lunjian_xunzhang3"
#define FOURTH          "/clone/fam/max/zhenyu"
#define FIFTH           "/clone/fam/max/longjia"

void create()
{
        seteuid(ROOT_UID);
        set_name(HIR "武林英雄鼓" NOR, ({ "drum" }) );
        set_weight(5000000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "只");
                set("no_get", 1);
                set("long", "这是一只牛皮制成的巨鼓，武林人士在华山论剑时敲响(knock)它开始比武。\n");
        }
}

int init()
{
        add_action("do_knock", "knock");
}

int do_knock(string arg)
{
        object ob, me, *env, *fighters;
        int i, j;
        string msg;

        me = this_player();
        ob = environment(me);
        if (! arg || arg != "drum")    return notify_fail("你要敲什么？\n");

        if (query("is_drum_knocked"))
                return notify_fail("比武大会已经开始了，不必再击鼓了。\n");

        if (! wizardp(me) && query("id", me)!="lazy cat")
                return notify_fail("现在召开比武大会，必需由巫师击鼓。\n");

        env = all_inventory(ob);
        j = 0;
        fighters = ({ });
        for (i = 0; i < sizeof(env); i++)
        {
                if (! playerp(env[i]) || wizardp(env[i]))
                        continue;
                /*
                if( query("mud_age", env[i])<86400*2 )
                        continue;
                */
                if (wizardp(me))
                        set("title", clear_title(query("title", env[i])), env[i]);

                fighters += ({ env[i] });
                j++;
        }
        if (j < 4)
{
if (query("id", me)=="lazy cat") me->command("say 喵喵喵，人数不够，取消比武。");
                return notify_fail("到场人数太少了，你还是先多召集几个玩家吧。\n");
}

        // message_vision(BOLD "\n\n\t$N敲响了华山绝顶比武场上的大鼓，鼓声咚咚，令人热血沸腾。\n\n" NOR, me);
        msg=BOLD"\n\n\t"+query("name", me)+"敲响了华山绝顶比武场上的大鼓，鼓声咚咚，令人热血沸腾。\n\n"NOR;
        message("channel:news", msg, users());

        if ((wizardp(me) && wiz_level(me) >= 4) || query("id", me)=="lazy cat")
                set("drum_knocked",query("name", me));
        else
                delete("drum_knocked");
        set("is_drum_knocked", 1);
        delete("round");
        delete("loop");
        delete("exits", environment(this_object()));
        give_money(env, fighters);
        return 1;
}

// By Lonely for override
void init_player(object me)
{
        me->set_override("unconcious", (: call_other, __FILE__, "check_out" :));
        me->set_override("die", (: call_other, __FILE__, "check_out" :));
        me->set_override("quit", (: call_other, __FILE__, "check_quit" :));
        me->clear_condition();
        set_temp("in_pkd", 1, me);
}

void restore_status(object me)
{
        me->delete_override("unconcious");
        me->delete_override("die");
        me->delete_override("quit");
        me->remove_all_enemy(1);
        me->remove_all_killer();
        me->clear_weak();
        me->clear_condition();
        delete_temp("block_msg/all", me);
        delete_temp("in_pkd", me);
}

// overide function of lost(die/unconcious)
int check_out(object me)
{
        object ob;
        mapping my;
        string msg;

        my = me->query_entire_dbase();
        my["eff_qi"] = my["max_qi"];
        my["eff_jing"] = my["max_jing"];
        my["jingli"] = my["max_jingli"];
        my["qi"] = 1;
        my["jing"] = 1;
        my["jingli"] = 1;

        tell_object(me, HIR "\n你觉得眼前一阵模糊...这下完了！\n" NOR);
        if (ob = me->query_last_damage_from())
        {
                msg = "听说" + me->name(1) + "惨遭" + ob->name(1) + "的毒手，被一脚踢下擂台。";
        } else
                msg = "听说" + me->name(1) + "运气不佳，本领有限、已经惨遭淘汰。";
        message_competition(msg);

        restore_status(me);
        total -= ({ me });
        me->move(ENTRY_ROOM);
        message("vision", "一个黑影倏的窜了出来，随即就是“啪”的"
                "一声，就见" + me->name() +"摔倒了地上，一副半死不"
                "活的样子。\n", environment(me), ({ me }));
        tell_object(me, "半昏半迷中，你觉得被人拎了起来，又"
                    "重重的摔倒了地上。\n");
        if (! living(me))
                me->revive();
        return 1;
}

// overide function of quit
int check_quit(object me)
{
        message_competition("听说" + me->name(1) +
                            "临阵脱逃，溜走了。");
        restore_status(me);
        if (arrayp(total))
                total -= ({ me });
        tell_object(me, "你决定弃权，逃了下去。\n");

        // continue run quit function
        me->move(ENTRY_ROOM);
        message("vision", "只见" + me->name() + "脸色非常难看的跑了下来。\n",
                environment(me), ({ me }));
        return 1;
}

void message_competition(string msg)
{
        CHANNEL_D->channel_broadcast("rumor", msg);
}

void heart_beat()
{
        if (sizeof(total))
                auto_check();
}

// check the players who join the competition
void auto_check()
{
        object ob;
        string room;
        object *lost;
        int i;

        lost = ({ });
        for (i = 0; i < sizeof(total); i++)
        {
                if (! objectp(total[i]))
                        continue;
                room = base_name(environment(total[i]));
                if (! sscanf(room, "/d/huashan/lunj%*s") &&
                    ! sscanf(room, "/adm/npc/%*s"))
                {
                        // not in pk room
                        restore_status(total[i]);
                        delete("total_hatred", total[i]);
                        total[i] = 0;
                        continue;
                }
                if( query("qi", total[i])<1 || query("jing", total[i])<1 )
                        lost += ({ total[i] });
        }

        // kickout the players who lost competition
        foreach (ob in lost)
                check_out(ob);

        total -= ({ 0 });
}

int sort_user(object ob1, object ob2)
{
        if( query("combat_exp", ob1)<query("combat_exp", ob2) )
                return 1;
        else return -1;
}

int sort_winner(object ob1,object ob2)
{
        mapping arena = query("arena");
        if (! ob1 && ! ob2) return 0;
        if (! ob1) return 1;
        if (! ob2) return -1;
        if( (arena[ob1] == arena[ob2]) && (query("combat_exp", ob1)>query("combat_exp", ob2)) )
                return -1;
        if (arena[ob1] > arena[ob2])
                return -1;
        else return 1;
}

void de_group(object *fighters)
{
        int i, j, k;
        string msg, file, overmsg;
        object *list, no1, no2, no3, no4, no5;
        mapping arena;
        object room = environment();

        if (sizeof(fighters) <= 1)       return;
        for (i = 0; i < 100; i++)
                if (query("group" + i)) delete("group" + i);
        //while (query("group" + i)) delete("group" + i);

        if (sizeof(fighters) < 8)
        {
                if (query("loop"))
                {
                        file = "seperator\n";
                        arena = query("arena");
                        list = sort_array(keys(arena), "sort_winner", this_object());
                        i = 0;
                        for (i; i < sizeof(list); i++)
                        if (! undefinedp(list[i]))
                        {
                                no1 = list[i];
                                break;
                        }
                        i++;
                        for (i; i < sizeof(list); i++)
                        if (! undefinedp(list[i]))
                        {
                                no2 = list[i];
                                break;
                        }
                        i++;
                        for (i; i < sizeof(list); i++)
                        if (! undefinedp(list[i]))
                        {
                                no3 = list[i];
                                break;
                        }
                        i++;
                        for (i; i < sizeof(list); i++)
                        if (! undefinedp(list[i]))
                        {
                                no4 = list[i];
                                break;
                        }
                        i++;
                        for (i; i < sizeof(list); i++)
                        if (! undefinedp(list[i]))
                        {
                                no5 = list[i];
                                break;
                        }

                        if (no1)
                        {
                                overmsg = HIW "\n\n本次武林比武大会的结果:\n" + HIM + "          第一名是" +
                                        query("name", no1)+"("+query("id", no1)+")。\n"NOR;
                                message("channel:news", overmsg, users());
                                file+=query("name", no1)+"("+query("id", no1)+")\n";
                        }
                        if (no2)
                        {
                                overmsg = HIR "          第二名是" +
                                        query("name", no2)+"("+query("id", no2)+")。\n"NOR;
                                message("channel:news", overmsg, users());
                                file+=query("name", no2)+"("+query("id", no2)+")\n";
                        }
                        if (no3)
                        {
                                overmsg = HIY "          第三名是" +
                                        query("name", no3)+"("+query("id", no3)+")。\n"NOR;
                                message("channel:news", overmsg, users());
                                file+=query("name", no3)+"("+query("id", no3)+")\n";
                        }
                        if (no4)
                        {
                                overmsg = HIY "          第四名是" +
                                        query("name", no4)+"("+query("id", no4)+")。\n"NOR;
                                message("channel:news", overmsg, users());
                                file+=query("name", no4)+"("+query("id", no4)+")\n";
                        }
                        if (no5)
                        {
                                overmsg = HIY "          第五名是" +
                                        query("name", no5)+"("+query("id", no5)+")。\n"NOR;
                                message("channel:news", overmsg, users());
                                file+=query("name", no5)+"("+query("id", no5)+")\n";
                        }

                        if (stringp(query("drum_knocked")))
                        {
                                log_file("static/lunjian", file);
                                if (no1)
                                {
                                        addn("experience", 5000, no1);

                                        new(FIRST)->move(no1);
#ifdef DB_SAVE
                                        if (MEMBER_D->is_member(no1))
                                                MEMBER_D->db_pay_member(no1, 120);
                                        else
                                                MEMBER_D->db_create_member(no1, 120);
#endif
                                        if( query("combat/PKS", no1)>10 )
                                                addn("combat/PKS", -10, no1);
                                        else delete("combat/PKS", no1);
                                        
                                        HISTORY_D->add_history("华山论剑", query("id", no1), sprintf("论剑组 %s(%s)，年龄 %d、等级 %d，荣获天地第一\n", 
                                                query("name", no1), query("id", no1), query("age", no1), query("level",no1)));     
                                }
                                if (no2)
                                {
                                        addn("experience", 4000, no2);

                                        new(SECOND)->move(no2);
#ifdef DB_SAVE
                                        if (MEMBER_D->is_member(no2))
                                                MEMBER_D->db_pay_member(no2, 100);
                                        else
                                                MEMBER_D->db_create_member(no2, 100);
#endif
                                        if( query("combat/PKS", no1)>7 )
                                                addn("combat/PKS", -7, no1);
                                        else delete("combat/PKS", no1);
                                        
                                        HISTORY_D->add_history("华山论剑", query("id", no2), sprintf("论剑组 %s(%s)，年龄 %d、等级 %d，荣获天地第二\n", 
                                                query("name", no2), query("id", no2), query("age", no2), query("level",no2)));     
                                }
                                if (no3)
                                {
                                        addn("experience", 3000, no3);

                                        new(THIRD)->move(no3);
#ifdef DB_SAVE
                                        if (MEMBER_D->is_member(no3))
                                                MEMBER_D->db_pay_member(no3, 80);
                                        else
                                                MEMBER_D->db_create_member(no3, 80);
#endif
                                        if( query("combat/PKS", no1)>5 )
                                                addn("combat/PKS", -5, no1);
                                        else delete("combat/PKS", no1);
                                        
                                        HISTORY_D->add_history("华山论剑", query("id", no3), sprintf("论剑组 %s(%s)，年龄 %d、等级 %d，荣获天地第三\n", 
                                                query("name", no3), query("id", no3), query("age", no3), query("level",no3)));     
                                }
                                if (no4)
                                {
                                        addn("experience", 2000, no4);

                                        new(FOURTH)->move(no4);
                                        new(FOURTH)->move(no4);
                                        new(FOURTH)->move(no4);
#ifdef DB_SAVE
                                        if (MEMBER_D->is_member(no4))
                                                MEMBER_D->db_pay_member(no4, 60);
                                        else
                                                MEMBER_D->db_create_member(no4, 60);
#endif
                                        if( query("combat/PKS", no4)>3 )
                                                addn("combat/PKS", -3, no4);
                                        else delete("combat/PKS", no4);
                                }
                                if (no5)
                                {
                                        addn("experience", 1000, no5);

                                        new(FIFTH)->move(no5);
                                        new(FIFTH)->move(no5);
                                        new(FIFTH)->move(no5);
#ifdef DB_SAVE
                                        if (MEMBER_D->is_member(no5))
                                                MEMBER_D->db_pay_member(no5, 40);
                                        else
                                                MEMBER_D->db_create_member(no5, 40);
#endif
                                        if( query("combat/PKS", no5)>1 )
                                                addn("combat/PKS", -1, no5);
                                        else delete("combat/PKS", no5);
                                }
                        }

                        delete("drum_knocked");
                        delete("lunshu");
                        set("exits/southdown","/d/huashan/houzhiwangyu", environment());
                        delete("is_drum_knocked");
                        set_heart_beat(0);
                        return;
                }
                set("loop", 1);
                msg = BOLD "\n\n比武大会第" + chinese_number((int)query("lunshu") + 1) + "轮(循环赛)赛程：\n\n" NOR;
                k = 0;
                for (i = 0; i < sizeof(fighters); i++)
                {
                        for (j = i; j < (sizeof(fighters) - 1); j++, k++)
                        {
                                set("group" + k, ([ fighters[i]:fighters[j+1] ]));
                                msg+=(query("name", fighters[i])+HIY+"--V.S.--"+NOR+
                                        (string)query("name", fighters[j+1]) + (k%3 == 2 ? "\n\n":"\t"));
                        }
                        if (objectp(fighters[i]))
                        {
                                if (sizeof(arena))
                                        arena += ([ fighters[i] : 0 ]);
                                else
                                        arena = ([ fighters[i] : 0 ]);
                        }
                }
        } else
        {
                msg = BOLD "\n\n比武大会第" + chinese_number((int)query("lunshu")+  1) + "轮(淘汰赛)赛程：\n\n" NOR;
                set("loop", 0);
                list = sort_array(fighters, "sort_user", this_object());
                for (i = 0; i < sizeof(list); i++)
                {
                        if (sizeof(arena))
                                arena += ([ list[i] : 0 ]);
                        else
                                arena = ([ list[i] : 0 ]);

                }
                i = 0;
                if (sizeof(list)%2)
                {
                        i = 1;
                        msg+=HIY+(query("name", list[0])+"------(此轮免战)\t"NOR);
                        set("group0", ([ list[0]: 0 ]));

                }
                if( i == 1 )
                        for (i; i <= (sizeof(list)) / 2; i++)
                        {
                                set("group" + i, ([list[i] : list[sizeof(list)/2 + i]]));
                                msg+=(query("name", list[i])+HIC+"--V.S.--"+NOR+
                                        (string)query("name", list[sizeof(list)/2+i]) + (i%3 == 2 ? "\n\n":"\t"));
                        }
                else
                        for (i; i < (sizeof(list)) / 2; i++)
                        {
                                set("group" + i, ([list[i] : list[sizeof(list)/2 + i]]));
                                msg+=(query("name", list[i])+HIC+"--V.S.--"+NOR+
                                        (string)query("name", list[sizeof(list)/2+i]) + (i%3 == 2 ? "\n\n":"\t"));
                        }
        }
        msg += "\n";
        set("item_desc/paizi", msg, room);
        tell_room(room, msg);
        set("round", 0);
        set("arena", arena);
        remove_call_out("start_fight");
        call_out("start_fight", 5);
}

int filter_user(object ob1, object ob2)
{
        mapping arena = query("arena");
        return (int)arena[ob1];
}

void start_fight()
{
        int round = query("round");
        mapping fighters, arena = query("arena");
        object room = environment();
        object ob1, ob2, *list;

        if (mapp(fighters = query("group" + round)))
        {
                if (sizeof(keys(fighters)))
                        ob1 = keys(fighters)[0];
                if (ob1)
                        ob2 = fighters[ob1];
                else if (sizeof(values(fighters)))
                        ob2 = values(fighters)[0];
                round ++;
                set("round", round);
                if (ob1 && ! ob2)
                {
                        arena[ob1] += 1;
                        tell_room(room, BOLD "\n第" + chinese_number((int)query("lunshu")+1) + "轮第" +
                                chinese_number(round) + "回合：  " +
                                query("name", ob1)+"("+query("id", ob1)+")"+HIY+"---------免战!\n"NOR);
                        remove_call_out("start_fight");
                        call_out("start_fight", 1);
                        return;
                }
                if (ob2 && ! ob1)
                {
                        arena[ob2] += 1;
                        tell_room(room, BOLD "\n第" + chinese_number((int)query("lunshu")+1) + "轮第" +
                                chinese_number(round) + "回合：  " +
                                query("name", ob2)+"("+query("id", ob2)+")"+HIY+"---------免战!\n"NOR);
                        remove_call_out("start_fight");
                        call_out("start_fight", 1);
                        return;
                }
                if (! ob1 && ! ob2)
                {
                        tell_room(room, BOLD "\n第" + chinese_number((int)query("lunshu")+1) + "轮第" +
                                chinese_number(round) + "回合：  " +
                                HIY + "-----------SKIP----------\n" NOR);
                        remove_call_out("start_fight");
                        call_out("start_fight", 1);
                        return;
                }
                tell_room(room, BOLD "\n第" + chinese_number((int)query("lunshu")+1) + "轮第" +
                        chinese_number(round) + "回合：  " +
                        query("name", ob1)+"("+query("id", ob1)+")"+HIY+"---V.S.---"+NOR+BOLD+
                        query("name", ob2)+"("+query("id", ob2)+")\n"NOR);
                if (! room = find_object(LUNJIAN))
                        room = load_object(LUNJIAN);
                recover(ob1);
                recover(ob2);
                message_vision(HIW "\n$N和$n施展轻功,双双跃上擂台。\n\n" NOR, ob1, ob2);

                if (! arrayp(total))
                        total = ({ ob1 });
                else
                if (member_array(ob1, total) == -1)
                        total += ({ ob1 });
                ob1->move(room);
                init_player(ob1);
                set_heart_beat(1);

                if (! arrayp(total))
                        total = ({ ob2 });
                else
                if (member_array(ob2, total) == -1)
                        total += ({ ob2 });
                ob2->move(room);
                init_player(ob2);
                //set_heart_beat(1);

                message("vision", HIW "\n" + ob1->name() + "和" + ob2->name() + "一前一后，跃了上来。\n\n" NOR,
                        room, ({ob1, ob2}));
                set("time", 3);
                remove_call_out("att_fight");
                call_out("att_fight", 2, ob1, ob2);
        } else
        {
                tell_room(room, HIW "比武大会第" + chinese_number((int)query("lunshu")+1) + "轮比赛结束。\n" NOR);
                set("item_desc/paizi", "现在还没开始比赛呢！", environment());
                addn("lunshu", 1);
                list = filter_array(keys(query("arena")), "filter_user", this_object());
                de_group(list);
        }
}


void checking(object ob1, object ob2)
{
        object winner, room;
        mapping arena;
        if (! room = find_object(LUNJIAN))
                room = load_object(LUNJIAN);
        if (ob1 && ob2)
        if (present(ob1, room) && present(ob2, room))
        {
                remove_call_out("checking");
                call_out("checking", 1, ob1, ob2);
                if (! ob1->is_killing(ob2)) ob1->kill_ob(ob2);
                if (! ob2->is_killing(ob1)) ob2->kill_ob(ob1);
                return ;
        }
        if (! ob1 && ! ob2)
                tell_room(environment(), BOLD "由于双方弃权,继续下一轮比赛。\n" NOR);
        else if (ob1 && (! ob2 || ! present(ob2, room)))
        {
                winner = ob1;
                message("vision", HIC + ob1->name() + "哈哈大笑几声，跳了下去。\n" NOR, room, ({ob1}));
        } else if (! ob1 || ! present(ob1, room))
        {
                winner = ob2;
                message("vision", HIC + ob2->name() + "哈哈大笑几声，跳了下去。\n" NOR, room, ({ob2}));
        } else
                tell_room(environment(), BOLD "由于双方弃权,继续下一轮比赛。\n" NOR);
        if (winner)
        {
                arena = query("arena");
                arena[winner] += 1;
                if (ob1)
                {
                        restore_status(ob1);
                        total -= ({ ob1 });

                        ob1->move(environment());
                        delete("total_hatred", ob1);
                        if (! living(ob1))
                                ob1->revive();
                }
                if (ob2)
                {
                        restore_status(ob2);
                        total -= ({ ob2 });

                        ob2->move(environment());
                        delete("total_hatred", ob2);
                        if (! living(ob2))
                                ob2->revive();
                }
                message_vision(HIC "$N哈哈大笑，从擂台上跳了下来。\n" NOR, winner);
                tell_room(environment(),BOLD"这一回合的结果是："+query("name", winner)+"胜。\n"NOR);
                total = ({ });
                recover(ob1);
                recover(ob2);
                set("arena", arena);
        }
        remove_call_out("start_fight");
        call_out("start_fight", 5);
}
int att_fight(object ob1, object ob2)
{
        object room;
        if (! ob1 || ! ob2)
        {
                remove_call_out("start_fight");
                call_out("start_fight", 5);
                return 1;
        }
        if (! room = find_object(LUNJIAN))
                room = load_object(LUNJIAN);
        if (present(ob1, room) && present(ob2, room))
        {
                if (! ob1->is_killing(ob2) || ! ob2->is_killing(ob1))
                {
                        if (query("time"))
                        {
                                tell_object(ob1,"\t\t" + HIR + "===" + CHINESE_D->chinese_number(query("time")) + "===\n\n" + NOR);
                                tell_object(ob2,"\t\t" + HIR + "===" + CHINESE_D->chinese_number(query("time")) + "===\n\n" + NOR);
                                addn("time", -1);
                                call_out("att_fight", 5, ob1, ob2);
                                return 1;
                        }
                        tell_room(room, HIY "\t-------  开     始  -------\n\n" NOR);
                        message_vision("\n$N对著$n喝道：「" + RANK_D->query_rude(ob2) + "！今日不是你死就是我活！」\n\n", ob1, ob2);
                }
                if (! ob1->is_killing(ob2)) ob1->kill_ob(ob2);
                if (! ob2->is_killing(ob1)) ob2->kill_ob(ob1);
        }
        remove_call_out("checking");
        call_out("checking", 1, ob1, ob2);
        return 1;
}
void recover(object me)
{
        if (! me)    return;
        if (! living(me)) me->revive();
                set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);
        if( query("neili", me)<query("max_neili", me) )
                set("neili",query("max_neili",  me), me);
        if( query("jingli", me)<query("max_jingli", me) )
                set("jingli",query("max_jingli",  me), me);
        set("food", me->max_food_capacity(), me);
        set("water", me->max_water_capacity(), me);
        me->clear_condition();
}

string clear_title(string arg)
{
        if (! arg) return "";
        if ((strsrch(arg, "本月天下第一") >= 0)
        ||  (strsrch(arg, "本月天下第二") >= 0)
        ||  (strsrch(arg, "本月天下第三") >= 0))
        {
                arg = replace_string(arg, HIY "本月天下第一" NOR, "");
                arg = replace_string(arg, HIY "本月天下第二" NOR, "");
                arg = replace_string(arg, HIY "本月天下第三" NOR, "");
        }
        return arg;
}

void add_title(object me,string arg)
{
        string title;
        title=HIY+arg+NOR+clear_title(query("title", me));
        set("title", title, me);
}

int give_money(object *players,object *fighters)
{
        if (query("drum_knocked"))
        {
                message("vision", query("drum_knocked") + "笑嘻嘻地对大伙说到：哈哈，哈哈，多谢捧场！\n",
                        environment());
                foreach (object user in players)
                {
                        if (! objectp(user) || ! playerp(user) ) continue;
                        if (user && ! wizardp(user) && (environment() == environment(user)))
                        {
                                new("/clone/money/thousand-gold")->move(user);
                                new("/clone/money/thousand-gold")->move(user);
         new("/u/redl/npc/obj/penny")->move(user); 
         new("/u/redl/npc/obj/penny")->move(user); 
         new("/clone/goods/tianshi-charm")->move(user); 
                        }
                }
                message("vision", query("drum_knocked") + "给参赛的江湖英雄一些礼物：“小小意思，笑纳，笑纳。”\n",
                        environment());
        }
        de_group(fighters);
        return 1;
}
