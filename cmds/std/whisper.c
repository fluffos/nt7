// whisper.c

#include <ansi.h>

inherit F_CLEAN_UP;

int reply_whisper(object me, object who, string msg);
int ultra_whisper(object me, object who, string msg);
protected void special_bonus(object me, mixed arg);
protected void money_bonus(object me, mixed arg);

int main(object me, string arg)
{
       int r;
        string dest, msg;
        object ob;

        if (! arg)
                return notify_fail("你要对谁耳语些什么？\n");

        if (sscanf(arg, "%s about %s", dest, msg) != 2)
                if (sscanf(arg, "%s %s", dest, msg) != 2)
                        return notify_fail("你要对谁耳语些什么？\n");

        ob = present(dest, environment(me));
        if (! ob || ! ob->is_character())
                return notify_fail("你要对谁耳语？\n");

        if (me->ban_say(1))
                return 0;

        if( query("doing", me) == "scheme" )
        {
                if( query("jing", me)<100 )
                        return notify_fail("你现在的精神不济，等一会儿吧。\n");
                addn("jing", -50, me);
        }

        write(WHT "你在" + ob->name() + WHT "的耳边悄声说道：" +
              msg + "\n" NOR);
        tell_room(environment(me), me->name() + "在" + ob->name()
                + "耳边小声地说了些话。\n", ({ me, ob }));
        if (! userp(ob)) 
        {
              r = 0;
              if( query("bunch_quest", me) && query("bunch_quest/type", me) == "传口信" )
                      r = reply_whisper(me, ob, msg);
              if (! r)
                      if( (query("quest_dg", me) && query("quest_dg", me)["type"] == "传") || 
                          (query("quest_kh", me) && query("quest_kh", me)["type"] == "传") || 
                          (query("quest_hs", me) && query("quest_hs", me)["type"] == "传") || 
                          (query("quest_sn", me) && query("quest_sn", me)["type"] == "传") )
                              r = ultra_whisper(me, ob, msg);

              if (! r)
                      ob->relay_whisper(me, msg);
       }
        else
                tell_object(ob, WHT + me->name() +
                                WHT "在你的耳边悄声说道：" + msg + "\n" NOR);
        return 1;
}

int reply_whisper(object me, object who, string msg)
{
        mapping bunch_quest,b;

        int exp;
        int pot;
        int score;
        int weiwang;

        bunch_quest=query("bunch_quest", me);

        //传错人了
        if (bunch_quest["target"] != base_name(who))
                return 0;

        //传错话了
        if (msg != bunch_quest["send_msg"])
                return 0;

        message_sort("$N面色凝重，一边听着一边对$n使劲的点头：“这位" +
                     RANK_D->query_respect(me) +
                     "，多谢你把话带到！”\n", who, me);

        // 奖励
        addn("total_hatred", -2, me);
        if (query("total_hatred", me) < 0) set("total_hatred",0, me);

        exp = bunch_quest["bonus"];
        exp += random(exp/2);
        //exp+=query("combat_exp", me)/5000;
        pot = exp/(2 + random(2));
        score = 5 + random(10);
        weiwang = 5 + random(10);

        b = ([ "exp" : exp,
               "pot" : pot,
               "score" : score,
               "weiwang" : weiwang,
               "prompt": "在把口信传给" + who->name() +
                         HIG "的过程中，经过锻炼" ]);

        GIFT_D->delay_bonus(me, b);

        delete("bunch_quest", me);
        addn_temp("finish_bunch_times", 1, me);

        return 1;
}

int ultra_whisper(object me, object who, string msg)
{
        mapping quest;
        int level;
        int i;
        int exp;
        int pot;
        int score;
        int weiwang;
        int mar;
        int quest_count;
        string the_quest;
        mixed special = 0;
        mixed money = 0;

        quest=query("quest_dg", me);
        the_quest = "独孤求败";
        if (!quest || quest["type"] != "传")
        {
                quest=query("quest_kh", me);
                the_quest = "葵花太监";
        }
        if (!quest || quest["type"] != "传")
        {
                quest=query("quest_hs", me);
                the_quest = "黄裳";
        }
        if (!quest || quest["type"] != "传")
        {
                quest=query("quest_sn", me);
                the_quest = "南海神尼";
        }

        if (!quest) return 0;

        if (userp(who)) return 0;

        //传错人了
        if (quest["name"] != who->name(1))
                return 0;

        //传错话了
        if (msg != quest["answer"])
                return 0;

        message_sort("$N面色凝重，一边听着一边对$n使劲的点头：“这位" +
                     RANK_D->query_respect(me) +
                     "，多谢你把口令带到！”\n", who, me);

        // 奖励
        level = quest["level"]+1;
        if (the_quest == "独孤求败")
        {
                if( (i=query("questdg_times", me))<8)i=15-i;
                else i = 1;
        }
        if (the_quest == "葵花太监")
        {
                if( (i=query("questkh_times", me))<15)i=15-i;
                else i = 1;
        }
        if (the_quest == "南海神尼")
        {
                if( (i=query("questsn_times", me))<15)i=15-i;
                else i = 1;
        }
        if (the_quest == "黄裳")
        {
                if( (i=query("quesths_times", me))<15)i=15-i;
                else i = 1;
        }

        exp = level*100 + quest["bonus"]*5;
        exp *= 2;
        exp /= i;
        pot = exp/(2+random(2));
        score = random(exp/20);
        weiwang = random(exp/15);
        mar = 10 + random(40);

        GIFT_D->bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                              "weiwang" : weiwang, "score" : score ]), 1);

        if (the_quest == "独孤求败")
        {
                addn("questdg_times", 1, me);
                quest_count=query("questdg_times", me)%500;
#ifdef DB_SAVE
                if( MEMBER_D->is_valid_member(query("id", me)) )
                {
                        if( query("special_skill/sophistry", me) )
                        {
                        if( query("questdg_times", me) >= 20000 )
                        set("questdg_times", 0, me);
                        } else {
                        if( query("questdg_times", me) >= 10000 )
                        set("questdg_times", 0, me);
                        }
                }
                else
                {
#endif
                        if( query("questdg_times", me) >= 5000 )
                        set("questdg_times", 0, me);
#ifdef DB_SAVE
                }
#endif
                delete("quest_dg", me);
        }
        if (the_quest == "葵花太监")
        {
                addn("questkh_times", 1, me);
                quest_count=query("questkh_times", me)%500;
#ifdef DB_SAVE
                if( MEMBER_D->is_valid_member(query("id", me)) )
                {
                        if( query("special_skill/sophistry", me) )
                        {
                        if( query("questkh_times", me) >= 20000 )
                        set("questkh_times", 0, me);
                        } else {
                        if( query("questkh_times", me) >= 10000 )
                        set("questkh_times", 0, me);
                        } 
                } else
                {
#endif
                if( query("questkh_times", me) >= 5000 )
                        set("questkh_times", 0, me);
#ifdef DB_SAVE
                } 
#endif
                delete("quest_kh", me);
        }
        if (the_quest == "黄裳")
        {
                addn("quesths_times", 1, me);
                quest_count=query("quesths_times", me)%500;
#ifdef DB_SAVE
                if( MEMBER_D->is_valid_member(query("id", me)) )
                {
                        if( query("special_skill/sophistry", me) )
                        {
                        if( query("quesths_times", me) >= 20000 )
                        set("quesths_times", 0, me);
                        } else {
                        if( query("quesths_times", me) >= 10000 )
                        set("quesths_times", 0, me);
                        }
                }
                else
                {
#endif
                if( query("quesths_times", me) >= 5000 )
                        set("quesths_times", 0, me);
#ifdef DB_SAVE
                }
#endif
                delete("quest_hs", me);
        }
        if (the_quest == "南海神尼")
        {
                addn("questsn_times", 1, me);
                quest_count=query("questsn_times", me)%500;
#ifdef DB_SAVE
                if( MEMBER_D->is_valid_member(query("id", me)) )
                {
                        if( query("special_skill/sophistry", me) )
                        {
                        if( query("questsn_times", me) >= 20000 )
                        set("questsn_times", 0, me);
                        } else {
                        if( query("questsn_times", me) >= 10000 )
                        set("questsn_times", 0, me);
                        }
                }
                else
                {
#endif
                if( query("questsn_times", me) >= 5000 )
                        set("questsn_times", 0, me);
#ifdef DB_SAVE
                }
#endif
                delete("quest_sn", me);
        }

        if (quest_count == 50)
                special = 1;
        else if (quest_count == 100)
                special = "/clone/gift/puti-zi";
        else if (quest_count == 150)
                money = 1;
        else if (quest_count == 200)
                money = 1;
        else if (quest_count == 250)
                money = 1;
           else if (quest_count == 300)
                special = "/clone/gift/tianxiang";
           else if (quest_count == 350)
                special = "/clone/gift/tianxiang";
           else if (quest_count == 400)
                special = "/clone/misc/jiuzhuan";
        else if (quest_count == 450)
                special = "/clone/gift/jiuzhuan";
           else if (quest_count == 0)
                special = "/clone/gift/xuanhuang";

        if (special) special_bonus(me, special);
        if (money) money_bonus(me,money);
                            
        addn("total_hatred", -5, me);
        if (query("total_hatred", me) < 0) set("total_hatred",0, me);
        return 1;
}

protected void special_bonus(object me, mixed arg)
{
        string *ob_list = ({
                "/clone/gift/xiandan",
                "/clone/gift/shenliwan",
                "/clone/gift/unknowdan",
                "/clone/gift/xisuidan",
                "/d/item/obj/hantie",
                "/d/item/obj/wujins",
                "/d/item/obj/butian",
                "/d/item/obj/tiancs",
        });
        object ob;

        if (stringp(arg))
                ob = new(arg);
        else
                ob = new(ob_list[random(sizeof(ob_list))]);
        ob->move(me, 1);
        tell_object(me,HIM"你获得了一"+query("unit", ob)+ob->name()+
                        HIM "。\n" NOR);
}

void money_bonus(object me, mixed arg)
{
        string *ob_list = ({
                "/clone/gift/jinkuai",
                "/clone/gift/jintiao",
                "/clone/gift/xiaoyuanbao",
                "/clone/gift/dayuanbao",
                "/clone/gift/jinding",
        });
        object ob;

        if (stringp(arg))
                ob = new(arg);
        else
                ob = new(ob_list[random(sizeof(ob_list))]);

        ob->move(me,1);

        tell_object(me,HIM"你获得了一"+query("unit", ob)+ob->name()+
                        HIM "。\n" NOR);
}

int help(object me)
{
        write( @TEXT
指令格式：whisper <某人> about <讯息>

这个指令可以用来和同一房间中的人耳语，包括 NPC 在内。
其中的about可以省略。
TEXT );
        return 1;
}
