// Written by Lonely@ChinaMUD.cn
// learn.c

#include <ansi.h>
#include <skill.h>

inherit F_CLEAN_UP;

int can_learn(object me, string skill);

string *reject_msg = ({
        "说道：您太客气了，这怎么敢当？\n",
        "像是受宠若惊一样，说道：请教？这怎么敢当？\n",
        "笑着说道：您见笑了，我这点雕虫小技怎够资格指点您什么？\n",
});

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object where = environment(me);
        string *args;
//      string *fams;
        string skill, teacher/*, master*/, skill_name;
        object ob;
        mixed flag;
        int master_skill, my_skill, jing_cost, times, i;
        int lvl, neili_cost, t1, t2, t3, t4/*, exp*/;
        int rand;
        int diff;
        int c;
        int r;
        int n;
        int t = time();
        int vip_level;

        if( query("pigging", where) )
                return notify_fail("你还是专心拱猪吧！\n");

        if( me->is_busy() )
                return notify_fail(BUSY_MESSAGE);

        if( t == query_temp("time/learn", me) )
                return notify_fail("你刚刚才学习过（如果你要连续学习，可以指明学习的次数）。\n");

        if( !arg || (i = sizeof(args = explode(arg, " "))) < 2 )
                return notify_fail("指令格式：learn|xue <某人> <技能> <次数>\n");

        i--;
        if( i >= 2 && sscanf(args[i], "%d", times) && times )
                i--;
        else
                times = 1;
        skill = args[i--];
        if( args[i] == "about" && i >= 1 )
                i--;
        teacher = implode(args[0..i], " ");

        c=200+me->query_all_buff("learn_times");
        if( query("special_skill/clever", me) ) 
                c += 50;

        if( query("special_skill/wisdom", me) )
                c += 800;

        if( n = ACTION_D->query_action("xuexi_times") )
                c *= n;

        if( times < 1 || times > c )
                return notify_fail("学习次数最少一次，最多也不能超过" + chinese_number(c) +"次。\n");

        if( me->is_fighting() )
                return notify_fail("临阵磨枪？来不及啦。\n");

        if( !(ob = present(teacher, environment(me))) || !ob->is_character() )
                return notify_fail("你要向谁求教？\n");

        if( !living(ob) )
                return notify_fail("嗯……你得先把" + ob->name() +
                                   "弄醒再说。\n");

        if( !me->is_apprentice_of(ob) || ob->is_boss() || !ob->can_learn_from() ||
            playerp(ob) || ob->is_first() || ob->is_baby() ) {
                switch( ob->recognize_apprentice(me, skill) ) {
                case 0:
                        return notify_fail(CYN + ob ->name() + CYN +
                                           reject_msg[random(sizeof(reject_msg))]
                                           + NOR);
                case -1:
                        return 1;
                }
        }

        if( !master_skill = ob->query_skill(skill, 1) )
                return notify_fail("这项技能你恐怕必须找别人学了。\n");

        if( ob->is_fighting() )
                return notify_fail(ob->name() + "忙着料理别人，没空理你耶。\n");

        flag = query("no_teach/"+skill, ob);
        if( functionp(flag) ) 
                flag = evaluate(flag, ob);  
        if( stringp(flag) ) {
                message_vision(CYN "$N" CYN "摇摇头，说道：" + flag + "\n" NOR, ob);
                return 1;
        } else if( intp(flag) && flag ) {
                if( flag != -1 )
                        // show the messaeg if the result was not -1
                        write(CYN + ob->name() + CYN "说道：对不起，" +
                              to_chinese(skill) + "可不能随便传授。\n" NOR);
                return 1;
        }

        if( /*me->is_apprentice_of(ob) &&*/
            SKILL_D(skill)->type() == "martial" &&
            me->query_skill(skill, 1) >= SKILL_D(skill)->valid_learn_level() ) {
                write(ob->name() + "说：嗯.... 你的" + to_chinese(skill) +
                      "功力已经是非同凡响了，我就不再教你，你自己多研究吧。\n");
                return 1;
        }

        my_skill = me->query_skillo(skill, 1);
        if( my_skill >= master_skill )
                return notify_fail("这项技能你的程度已经不输你师父了。\n");

        if( my_skill >= (master_skill-query("betrayer/times", me)*20) )
                return notify_fail(CYN + ob->name() + CYN "皱了皱眉头，不禁想"
                                   "起你过去的叛师经历。\n" NOR);

        if( !can_learn(me, skill) )
                return 0;

        notify_fail("依你目前的能力，没有办法学习这种技能。\n");
        if( !SKILL_D(skill)->valid_learn(me) ) return 0;

        jing_cost = 150 / (int)me->query_int() + 1;
        if( !my_skill ) {
                jing_cost *= 2;
                me->set_skill(skill, 0);
        }

        if( (query("potential", me)-query("learned_points", me))<times )
                return notify_fail("你的潜能不够学习这么多次了。\n");

        if( SKILL_D(skill)->is_fmsk() && query("family/gongji", me) < times )
                return notify_fail("你的门派贡献点数不够学习这么多次了。\n");

        write(sprintf(HIC "你开始向%s请教" + chinese_number(times) +
                      "句有关「%s」的疑问。\n" NOR,
                      ob->name(),
                      to_chinese(skill)));

        if( query("env/no_teach", ob)){
                write("但是" + ob->name() + "现在并不准备回答你的问题。\n");
                return 1;
        }

        tell_object(ob, sprintf("%s向你请教有关「%s」的问题。\n",
                    me->name(), to_chinese(skill)));

        if( !me->can_improve_skill(skill) ) {
                write("也许是缺乏实战经验，你对" +
                      ob->name() + "的回答总是无法领会。\n");
                return 1;
        }

        set_temp("time/learn", t, me);

        t1=query("jing", me)/jing_cost;
        t2 = times - t1;
        if( t2 > 0 ) {
                lvl = me->query_skill("force");
                if( lvl <= 0 ) lvl = 1;

                neili_cost =  jing_cost * 60 / lvl;
                if( query("breakup", me) )
                        neili_cost = neili_cost * 7 / 10;

                if( neili_cost < 20 ) neili_cost = 20;

                if( query("neili", me) >= neili_cost*t2){
                        t4 = times;
                        addn("neili", -neili_cost*t2, me);
                }
                else {
                        t3=query("neili", me)/neili_cost;
                        t4 = t1 + t3;
                        if( t4 == 0 ) {
                                write("然而你今天太累了，无法再进行任何学习了。\n");
                                return 1;
                        }

                        set("neili", 0, me);
                }
        } else
                t4 = times;

        if( times > t1 )
                me->receive_damage("jing", jing_cost * t1);
        else
                me->receive_damage("jing", jing_cost * times);

        if( query("env/auto_regenerate", me) )
                SKILL_D("force/regenerate")->exert(me, me);

        addn("learned_points", t4, me);
        if( SKILL_D(skill)->is_fmsk() )
                addn("family/gongji", -t4, me);
        rand = me->query_int() + my_skill / 5;
        rand *= 5;

        if( intp(r=me->query_all_buff("learn_effect")) )
                rand += rand * r / 100;

        if( query("time_reward/study", me) )
                rand += rand * 50 / 100;

        if( query("special_skill/wisdom", me) )
                rand += rand * 50 / 100;

        vip_level = me->query_viplevel();
        if( vip_level < 1 )
                ;
        else if( vip_level < 2 )
                rand += rand * 10 / 100;
        else if( vip_level < 3 )
                rand += rand * 30 / 100;
        else if( vip_level < 4 )
                rand += rand * 60 / 100;
        else if( vip_level < 5 )
                rand += rand;
        else if( vip_level < 6 )
                rand += rand * 150 / 100;
        else if( vip_level < 7 )
                rand += rand * 2;
        else
                rand += rand * 3;
                
        diff = SKILLS_D->query_skill_difficult(skill);
        if( !diff ) diff = SKILL_D(skill)->difficult_level();
        rand /= (diff + 1);

        // me->improve_skill(skill, 4 + random(rand));
        me->improve_skill(skill, t4 * (4 + rand));

        if( skill_name = SKILL_D(skill)->query_skill_name(my_skill) )
                write(sprintf("你听了%s的指导，对「%s」"
                              "这一招似乎有些心得。\n",
                              ob->name(), skill_name));
        else
                write(sprintf("你听了%s的指导，似乎有些"
                              "心得。\n", ob->name()));

        if( t4 > 0 && t4 < times )
                write("但是你今天太累了，学习了" + chinese_number(t4) +
                      "次以后只好先停下来。\n");

        return 1;
}

int can_learn(object me, string skill)
{
        string skill_name;
        mapping skills;
//      string mskill;
//      int tmp;
//      int i;
        
        /*
        if( stringp(mskill = SKILL_D(skill)->main_skill()) &&
            mskill != skill &&
            me->query_skill(mskill, 1) > 0 )
                return notify_fail("你现在没有必要再单独学习" + to_chinese(skill) + "了。\n");
        */
        skills = me->query_skills();
        if( !mapp(skills) )
                return 1;

        if( !SKILL_D(skill)->valid_enable("force") ||
             SKILL_D(skill)->valid_force("*") )
                return 1;

        foreach (skill_name in keys(skills) ) {
                if( file_size(SKILL_D(skill_name) + ".c") == -1 ) {
                        // No such skill
                        continue;
                }

                if( !SKILL_D(skill_name)->valid_enable("force") ||
                     skill_name == skill )
                        continue;

                if( !SKILL_D(skill_name)->valid_force(skill) )
                        return notify_fail(HIR "你发现自身所学的" HIY +
                                           to_chinese(skill_name) + HIR
                                           "和" HIY + to_chinese(skill) +
                                           HIR "冲突不已，根本没办法并"
                                           "存。\n" NOR);
        }

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : learn|xue <某人> [about] <技能> <次数>

这个指令可以让你向别人请教有关某一种技能的疑难问题，当然，你请教的对象在这
项技能上的造诣必须比你高，而你经由这种方式学习得来的技能也不可能高於你所请
教的人，然而因为这种学习方式相当於一种「经验的传承」，因此学习可以说是熟悉
一种新技能最快的方法。

此外学习也需要消耗一些精力，而消耗的精力跟你自己、与你学习对象的悟性有关。

其他相关指令 : apprentice, practice, skills, study
HELP
        );
        return 1;
}