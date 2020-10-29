// Written by Lonely@ChinaMUD.cn
// study.c

#include <skill.h>
#include <command.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object where = environment(me);
        object ob;
        string zhao_name, book_name;
        mixed sname;
        string *args;
        string *fams;
        mapping skill, needs;
        string *need_sk;
        mixed need_lvl;
        int my_skill, cost, times, i;
        int lvl, neili_cost, t1, t2, t3, t4;
        int c, r;
        int t = time();

        if( !arg )
                return notify_fail("你要读什么？\n");

        if( query("pigging", where) )
                return notify_fail("你还是专心拱猪吧！\n");

        if( me->is_busy() )
                return notify_fail(BUSY_MESSAGE); 
        
        if( t == query_temp("time/study", me) )
                return notify_fail("你刚刚才读过书（如果你要连续读书，可以指明读书的次数）。\n");
        
        if( me->is_fighting() )
                return notify_fail("你无法在战斗中专心下来研读新知！\n");

        if( !arg || (i = sizeof(args = explode(arg, " "))) < 1)
                return notify_fail("指令格式：study|du <书籍> <次数>\n");

        i--;
        if( i >= 1 && sscanf(args[i], "%d", times) && times)
                i--;
        else
                times = 1;
        if( args[i] == "with" && i >= 1 )
                i--;
        book_name = implode(args[0..i], " ");

        c=200+me->query_all_buff("study_times");

        if( query("special_skill/wisdom", me) )
                c += 800;
                
        if( times < 1 || times > c)
                return notify_fail("读书次数最少一次，最多也"
                                   "不能超过" + chinese_number(c) + "次。\n");

        if( !objectp(ob = present(book_name, me)) )
                return notify_fail("没这本书可读啊？\n");

        if( !mapp(skill=query("skill", ob)) )
                return notify_fail("你无法从这样东西学到任何东西。\n");

        if( !me->query_skill("literate", 1) )
                return notify_fail("你是个文盲，先学点文化(literate)吧。\n");

        if( query("no_fight", environment(me)) && 
            //(query("doing", me) != "scheme" || this_player(1)) )
            (query("doing", me) != "scheme") )
                return notify_fail("你无法在这个地方安心读书。\n");

        message("vision", me->name() + "正专心地研读" + ob->name() +
                "。\n", environment(me), me);

        if( query("combat_exp", me)<skill["exp_required"]){
                write("你的实战经验不足，再怎么读也没用。\n");
                return 1;
        }

        if( !undefinedp(skill["family_name"]) ) {
                fams = query("reborn/fams", me);
                if( !me->query_family() || (me->query_family() != skill["family_name"] && 
                    (!arrayp(fams) || member_array(skill["family_name"], fams) == -1)) )
                {
                        write("你对" + skill["family_name"] + "的练功心法不了解，再怎么读也没用。\n");
                        return 1;
                }
        }

        if( skill["difficulty"] - (int)me->query_int() > 0 )
                return notify_fail("以你目前的能力，还没有办法学这个技能，你还是多学点文化吧。\n");
             
        cost = skill["jing_cost"] + skill["jing_cost"] 
                * (skill["difficulty"] - (int)me->query_int())/12;
        if( cost < 1 ) cost = 1;

        if( mapp(needs=query("skill/need", ob))){
                foreach( need_sk in keys(needs) ) {
                        // check all skills
                        need_lvl = needs[need_sk];
                        if( functionp(need_lvl) )
                                need_lvl = evaluate(need_lvl);
                        else
                        if( !intp(need_lvl) )
                                need_lvl = 0;

                        if( me->query_skill(need_sk, 1) < need_lvl )
                                // not reach the line
                                return notify_fail("你研读了一会儿，发现如果不通晓" +
                                                   to_chinese(need_sk) +
                                                   "的话，恐怕难以领会上面的含义。\n");
                        // check next skill
                }
        }

        sname=query("skill/name", ob);
        if( functionp(sname) )
                sname = evaluate(sname, ob);  
        if( !stringp(sname) ) 
                return notify_fail("你无法从上面学习到任何东西。\n");

        notify_fail("以你目前的能力，还没有办法学这个技能。\n");
        if( !SKILL_D(sname)->valid_learn(me) )
                return 0;

        if( !XUE_CMD->can_learn(me, sname) )
                return 0;

        if( me->query_skill(sname, 1) > skill["max_skill"] )
                return notify_fail("你研读了一会儿，但是发现"
                                   "上面所说的对你而言都太浅"
                                   "了，没有学到任何东西。\n");

        if( me->query_skill(sname, 1) < skill["min_skill"] )
                return notify_fail("你研读了一会儿，但是却发现"
                                   "你对这门技能的理解还太浅"
                                   "，结果毫无收获。\n");

        if( !me->query_skill(sname, 1) )
                me->set_skill(sname, 0);

        my_skill = me->query_skill(sname, 1);
        if( !me->can_improve_skill(sname) ) {
                return notify_fail("也许是缺乏实战经验，你对" +
                                   ob->name() + "上面所说的"
                                   "东西总是无法领会。\n");
        }

        set_temp("time/study", t, me);
        r = (int)me->query_skill("literate", 1) / 2 + 1;
        r+=r*me->query_all_buff("study_effect")/100;
        if( query("time_reward/study", me) )
                r += r * 50 / 100; 
                
        t1=query("jing", me)/cost;
        t2 = times - t1;
        if( t2 > 0 ) {
                lvl = me->query_skill("force");
                if( lvl <= 0 ) lvl = 1;

                neili_cost =  cost * 60 / lvl;
                if( query("breakup", me) )
                        neili_cost = neili_cost * 7 / 10;

                if( neili_cost < 20 ) neili_cost = 20;

                if( query("neili", me) >= neili_cost*t2){
                        t4 = times;
                        addn("neili", -neili_cost*t2, me);
                } else {
                        t3=query("neili", me)/neili_cost;
                        t4 = t1 + t3;
                        if( t4 == 0 ) {
                               write("你现在太累了，结果一行也没有看下去。\n");
                                return 1;
                        }

                        set("neili", 0, me);
                }
        } else
                t4 = times;

        if( times > t1 )
                me->receive_damage("jing", cost * t1);
        else
                me->receive_damage("jing", cost * times);

        if( query("env/auto_regenerate", me) )
                SKILL_D("force/regenerate")->exert(me, me);

        me->improve_skill(sname, r * t4);

        if( zhao_name = SKILL_D(sname)->query_skill_name(my_skill) )
                write(sprintf("你研读了" + chinese_number(t4) +
                      "行有关%s的技巧，对「%s」这一招似乎有些心得。\n",
                      to_chinese(sname), zhao_name));
        else
                write(sprintf("你研读了"+chinese_number(t4) +
                      "行有关%s的技巧，似乎有点心得。\n",
                      to_chinese(sname)));

        if( t4 < times )
                write("你现在已经过于疲倦，无法继续研读新知。\n");

        return 1;
}

int help(object me)
{
        write( @HELP
指令格式: study|du <物品名称> [次数]
          study|du <物品名称> with [次数]

这个指令使你可以通过阅读秘笈或其他物品自学某些技巧, 但前提
是: 你不能是个『文盲』。并且你不能在不能战斗的地方读书。

see also : learn
HELP );
        return 1;
}
