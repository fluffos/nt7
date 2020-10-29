// Copyright (C) 2005, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// invent.c

#include <ansi.h>
#include <command.h>
#define SKILL_MODEL_UNARMED    "/clone/meskill/skill_model_unarmed.h"
#define SKILL_MODEL_WEAPON     "/clone/meskill/skill_model_weapon.h"
#define SKILL_MODEL_DEFAULT    "/clone/meskill/skill_model_default.h"
#define  SYN "\""
#define  SYC ".c"
#define  NEED_LVL   6000

#define  DEBUG

inherit F_CLEAN_UP;

mapping valid_types = ([
        "unarmed":      "拳脚",
        "sword":        "剑法",
        // "arrow":        "箭法",
        "axe":          "斧法",
        "blade":        "刀法",
        "staff":        "杖法",
        "hammer":       "锤法",
        "club" :        "棍法",
        // "dodge":        "轻功",
        // "force":        "内功",
        "whip":         "鞭法",
        "finger":       "指法",
        "hand":         "手法",
        "cuff":         "拳法",
        "claw":         "爪法",
        "strike":       "掌法",
]);

mapping type_name = ([
        "unarmed":      "拳",
        "sword":        "剑",
        "arrow":        "箭",
        "axe":          "斧",
        "blade":        "刀",
        "staff":        "杖",
        "hammer":       "锤",
        "club" :        "棍",
        "dodge":        "轻功",
        "whip":         "鞭",
        "finger":       "指",
        "hand":         "手",
        "cuff":         "拳",
        "claw":         "爪",
        "strike":       "掌",
]);


string *weapon_types = ({
        "sword", "arrow", "axe",
        "blade", "staff", "hammer",
        "club", "whip" , "spin",
});

string *msga = ({ 
        "冥冥之中，$N突然发现",
        "$N绞尽脑汁，似乎觉得",
        "$N灵台一片清明，想起",
        "$N苦思以前练功时的点点滴滴，似乎想起",
        "突然，$N脑海灵光一现，发现",
        "$N反复比划，发现",
});

string *msgb = ({ 
        "似有相通之处，不禁心中一亮。",
        "颇有一一印证之功，随手演练，似有所悟。",
        "似乎可以合而为一，顿时心内一阵狂喜！",
        "可以相互取长补短，开辟一种全新的境界。",
        "如果连续使出，似乎可以将威力发挥至极限。",
        "如果详加修正，可以相互弥补个中不足，创造出更完美的招式。"
});

string *banned_name = ({
        "你", "你", "我", "他", "她", "它",
        "爸", "爷", "　", "妈",
        "屎", "尿", "粪",
});

string *spe_skill_level = ({
        "100", "110", "120", "130", "140", "150", "160", "180", "200", 
});
                      
string get_skill_name(object me, string skill);
int    skill_t_number(string e_name);
void   finish_write_skill(object ob, string skill);
mixed  write_skill_book(object me, string skill_c_name, string skill_e_name);
        
void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object  weapon, where;
        mapping skills_map;
        string  msg, invent_skill, *skills, *mut_skills = ({});
        string  *invent;
        int     mut_level, i;
        
        seteuid(getuid());
        where = environment(me);
        
        if (! wizardp(me) && ! MEMBER_D->is_valid_member(query("id", me))) 
                return notify_fail("只有会员才可以自创任何武功。\n");

        if( !arg ) {
                mapping invent_skills;

                if( !mapp(invent_skills=query("invent", me)) )
                        return notify_fail("你目前还没有自创任何武功。\n");
                
                msg = WHT "你目前共有 " HIC + chinese_number(sizeof(invent_skills)) + NOR WHT " 种自创武功：\n";
                invent = keys(invent_skills);
                
                for( i = 0; i < sizeof(invent); i++ )
                {
                        msg += CYN "\n〖" HIC + to_chinese(invent[i]) + CYN "〗：" HIY +
                               to_chinese(invent_skills[invent[i]]) +
                               CYN "(" HIY + invent_skills[invent[i]] + CYN ")\n";
                }
                
                tell_object(me, msg);

                return 1;
        }

        if( arg == "?" ) {
               msg = "以下是可以自创的技能种类：\n";

               skills = sort_array(keys(valid_types), (: strcmp :) );
               for (i = 0; i < sizeof(skills); i++)
                        msg += sprintf("  %s (%s)\n", valid_types[skills[i]], skills[i]);
                tell_object(me, msg);

                return 1;
        } else {
                string meskill;
                object sbook;
                
                if( sscanf(arg, "%s d", arg) == 1 ) {                        
                        if( !(meskill=query("invent/"+arg, me)) )
                                return notify_fail("没有这种自创武功，请确认输入的基本武功英文名称。\n");

                        tell_object(me, HIR "你删除了自创武功" + to_chinese(meskill) + "(" + meskill + ")。\n" NOR);                                                
                        SKILLS_D->remove_skill_from_skills(me, meskill); 

                        CHINESE_D->remove_translate(meskill);                        
                        rm( SKILL_D(meskill) + SYC );                        
                        rmtree( SKILL_D(meskill) + "/" );
                        me->delete_skill(meskill);
                        delete("invent/"+arg, me);
                        if( !mapp(query("invent", me)) || 
                            sizeof(query("invent", me))<1 )
                                delete("invent", me);
                        if( sbook = find_object("/data/book/"+meskill) )
                                destruct(sbook);
                        rm("/data/book/"+meskill+SYC);
                        return 1;
                } else
                if( sscanf(arg, "%s ?", arg) == 1 ) {         
                        mixed  *meskills;                                       
                        
                        if( !(meskill=query("invent/"+arg, me)) )
                                return notify_fail("没有这种自创武功，请确认输入的基本武功英文名称。\n");
                        
                        meskills = SKILL_D(meskill)->query_actions();
                        msg =  HIW "自创武功" + to_chinese(meskill) + "的详细情况如下:\n" NOR;
                        msg += WHT "--------------------------------------------------\n" NOR;
                        msg += HIY "武功总招数：" + chinese_number(skill_t_number(meskill)) + "招\n" NOR;
                                                
                        for( i = 0; i < sizeof(meskills); i++ ) {
                                msg += WHT "招式" + chinese_number(i + 1) + "名称：" + 
                                       meskills[i]["skill_name"] + "\n" NOR;
                                msg += CYN "招式" + chinese_number(i + 1) + "描述：" + 
                                       meskills[i]["action"] + "\n" NOR;
                                msg += CYN "招式" + chinese_number(i + 1) + "攻击：" + 
                                       meskills[i]["attack"] + "\n" NOR;
                                msg += CYN "招式" + chinese_number(i + 1) + "伤害：" + 
                                       meskills[i]["damage"] + "\n" NOR;
                                msg += CYN "附加" + chinese_number(i + 1) + "伤害：" + 
                                       meskills[i]["force"] + "\n" NOR;
                                msg += CYN "招式" + chinese_number(i + 1) + "躲闪：" + 
                                       meskills[i]["dodge"] + "\n" NOR;
                                msg += CYN "招式" + chinese_number(i + 1) + "招架：" + 
                                       meskills[i]["parry"] + "\n" NOR;
                        }
                        msg += WHT "--------------------------------------------------\n" NOR;

                        tell_object(me, msg);
                        return 1; 
                }
                                
        }
           
        if( undefinedp(valid_types[arg]) ) {
                mapping invents;
                string  *invent_skills;

                if( !mapp(invents=query("invent", me)) )
                        return notify_fail("没有这个技能种类，用 invent ? 可以查看有哪些种类。\n");
                
                invent_skills = keys(invents);

                foreach(string str in invent_skills) {
                        if( invents[str] == arg ) {
                                arg = str;
                                invent_skill = invents[str];
                                break;
                        }
                }

                if( !invent_skill )
                        return notify_fail("没有这个技能种类，用 invent ? 可以查看有哪些种类。\n");
        } else {
                if( stringp(invent_skill=query("invent/"+arg, me)) )
                        return notify_fail("你已经自创了一套" + to_chinese(invent_skill) + 
                                           "，如果要继续为这套武功创造招式，请用invent <已创武功>\n");
        } 

        if( me->is_busy() )
                return notify_fail("你还是先忙完手头的事再说吧！\n");         

        if( query("pigging", where) )
                return notify_fail("你还是专心拱猪吧！\n");
                
        if( !query("no_fight", where) )
                return notify_fail("在这里闭关？不太安全吧？\n");

        if( !query("sleep_room", where) )
                return notify_fail("你得找一个能够休息的地方闭关。\n");
                
        if( !ultrap(me) )
                return notify_fail("你还没有到大宗师的境界，还是好好学习锻炼吧。\n");

        if( query("yuanshen_level", me)<100 )
                return notify_fail("你还没有到元神不灭境界，还是好好学习锻炼吧。\n");

        if( query("potential", me)-query("learned_points", me)<1000000 )
                return notify_fail("你的潜能不够，没法闭关修行。\n");

        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("你现在的气太少了，无法静心闭关。\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("你现在的精太少了，无法静心闭关。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你觉得内力颇有不足，看来目前还难以"
                                   "进行长时间的闭关修炼。\n");

        if( query("neili", me)*100/query("max_neili", me)<90 )
                return notify_fail("你现在的内力太少了，无法静心闭关。\n");
                
        // if( !mapp(skills_map = me->query_skillc() ) || sizeof(skills_map) < 1 )
        if( !mapp(skills_map = me->query_skills() ) || sizeof(skills_map) < 1 )
                return notify_fail("你还是先去学点功夫再来吧。\n");

        if( undefinedp(skills_map[arg]) || skills_map[arg] < 1 )
                return notify_fail("你连基本的" + valid_types[arg] + "都不会，从何谈起？\n");

        if( skills_map[arg] < NEED_LVL )
                return notify_fail("你还是打好" + valid_types[arg] + "的基本功吧。\n");

        if( objectp(weapon=query_temp("weapon", me))){

                if( member_array(arg, weapon_types) == -1 && arg != "dodge" )
                        return notify_fail("你必须空手才能自创" + valid_types[arg] + "。\n");

                if( member_array(arg,weapon_types) != -1 && query("skill_type", weapon) != arg )
                        return notify_fail("你所使用的武器不对，无法自创" + valid_types[arg] + "。\n");
        } else if( member_array(arg, weapon_types) != -1 )
                        return notify_fail("你必须拿起武器才能开始自创" + valid_types[arg] + "。\n");

        skills = keys(skills_map);

        foreach( string sk_tmp in skills ) {
                if( SKILL_D(sk_tmp)->valid_enable(arg) ) {
                        mut_skills += ({ sk_tmp });
                }
        }

        if( sizeof(mut_skills) < 4 )
                return notify_fail("你的" + valid_types[arg] + "修为还不够广博，再去多学习学习！\n");

        mut_skills = filter_array(mut_skills, (: $(skills_map)[$1] >= NEED_LVL :));
        
        if( sizeof(mut_skills) < 4 )
                return notify_fail("你在" + valid_types[arg] + "方面的修为还不够高深。\n");

        mut_level = 0;
        foreach( string sk_tmp in mut_skills ) 
                mut_level += skills_map[sk_tmp];
        
        mut_level /= sizeof(mut_skills);
        mut_level -= NEED_LVL;
                        
        delete_temp("invent", me);
        
        if( stringp(invent_skill) )
        {
                set_temp("invent/spe_skill/skill_z_number", skill_t_number(invent_skill)+1, me);
                if (skill_t_number(invent_skill) + 1 >= 10)
                        return notify_fail("你的" + to_chinese(invent_skill) + 
                                           "招式已经到了极限，无法再自创新招式。\n");
                
                message_vision("$N盘膝坐下，开始苦思冥想，专心的自创" + to_chinese(invent_skill) + "。\n", me);              
        }
        else    message_vision("$N盘膝坐下，开始苦思冥想，专心的自创一种" + valid_types[arg] + "。\n", me);

        set_temp("invent/skill", arg, me);
        set_temp("invent/spe_skill/skill", arg, me);
        set_temp("invent/mut_skills", mut_skills, me);
        set_temp("invent/mut_level", mut_level, me);
        
        if( stringp(invent_skill) )
                set_temp("invent/invent_skill", invent_skill, me);
        
        me->set_short_desc("正在全神贯注地自创" + valid_types[arg] + "。");

        me->start_busy(bind((:call_other, __FILE__, "inventing" :), me),
                       bind((:call_other, __FILE__, "halt_inventing" :), me));

        CHANNEL_D->do_channel(this_object(), "rumor",
                              sprintf("%s(%s)开始闭关自创%s。\n",
                              me->name(1),query("id", me),stringp(invent_skill)?
                              (to_chinese(invent_skill) + "新招式") : valid_types[arg]));
        return 1;
}


int inventing(object me)
{
        int     max, i;
        string  pot;
        string  skill, *mut_skills, *skills_tmp, skills,
                skill_name, msg = "", *msgs = ({});
        mapping temp, s_skill;
        
        temp = me->query_entire_temp_dbase();
        s_skill = temp["invent"]["spe_skill"];
        
        pot=query("potential", me);
        if( pot <= query("learned_points", me) )
        {
                tell_object(me, "你的潜能耗尽，却一无所获，失望地站了。\n");
                message_vision("$N睁开双目，缓缓吐了一口气，站了起来。\n", me);
                me->set_short_desc(0);
                return 0;
        }

        if( me->add("learned_points",5000+random(10000))>pot )
                set("learned_points", pot, me);

        if( random(5) != 0) return 1;

        skill=query_temp("invent/skill", me);
        mut_skills=query_temp("invent/mut_skills", me);

        if( random(20000)<query("int", me)){
                string *chinese_skills = ({});

                foreach(string mut_skill in mut_skills) {
                        chinese_skills += ({ to_chinese(mut_skill)});
                }
                
                if( stringp(skills=query_temp("invent/invent_skill", me)) )
                {
                        s_skill["skill_e_name"] = skills;
                        s_skill["skill_c_name"] = to_chinese(skills);                        
                                                
                        message_sort("猛然间$N脑中略过种种招式，将" + 
                                sprintf( HIG"%s" NOR "以及" HIG "%s"NOR, 
                                implode(chinese_skills[0..sizeof(chinese_skills)-2], NOR "、" HIG), 
                                chinese_skills[sizeof(chinese_skills)-1])
                                + "这" + chinese_number(sizeof(mut_skills)) + "种武功的招式合而为"
                                "一作为" + to_chinese(skills) + "的新招式。\n", me);
                        
                        me->clear_written();                                   
                        tell_object(me, HIC "\n\n请给" + to_chinese(skills) + "新招式起个名字(例如: " NOR HIY "悠哉" NOR HIC "):" NOR);          
                        me->set_short_desc(0);                        
                        
                        input_to( "get_z_c_name", me );
                        return 0;
                }       
                message_sort("猛然间$N脑中略过种种招式，将" + 
                                sprintf( HIG"%s" NOR "以及" HIG "%s"NOR, 
                                implode(chinese_skills[0..sizeof(chinese_skills)-2], NOR "、" HIG), 
                                chinese_skills[sizeof(chinese_skills)-1])
                                + "这" + chinese_number(sizeof(mut_skills)) + "种武功合而为一。\n", me);

                me->clear_written();
                tell_object(me, HIW"\n\n\n你自创出了一套" + valid_types[skill] + "。\n"NOR
                                "你可以为这套" + valid_types[skill] + "取一个名字\n\n"
                                HIY"格式："HIC"<英文名> <中文名>\n\n"NOR
                                "如输入：wuyou 无忧\n"
                                "系统会产生一种无忧"HIR + type_name[skill] + NOR "(wuyou-"
                                HIR + skill + NOR")的" + valid_types[skill] + "\n"
                                HIW"勿用骚扰性或不雅的名字，否则将会被删除。\n"NOR
                                "请输入：");
                me->set_short_desc(0);                       
                input_to( "input_skill_name", me );
                return 0;
        }

        skills_tmp = copy(mut_skills);

        max = 2 + random(sizeof(mut_skills)-2);
        if ( max > 5 ) max = 5;

        if( max < sizeof(mut_skills) ) {
                for( i = max; i < sizeof(mut_skills); i++ ) {
                        skills_tmp -= ({ skills_tmp[random(sizeof(skills_tmp))] });
                }
        }

        foreach( string sk_tmp in skills_tmp ) {
                msgs += ({ get_skill_name(me, sk_tmp) });
        }

        msg = msga[random(sizeof(msga))] + sprintf("%s" NOR "以及%s", 
              implode(msgs[0..sizeof(msgs)-2], NOR "、"), msgs[sizeof(msgs)-1])
              + NOR + msgb[random(sizeof(msgb))] + "\n"NOR;

        message_sort(msg, me);

        return 1;
}

int halt_inventing(object me)
{
        me->set_short_desc(0);
        delete_temp("invent", me);
        tell_object(me, "你中止了自创。\n");
        message_vision(HIY "$N" HIY "起身站立，神情充满了失望。\n\n" NOR, me);
        return 1;
}

string get_skill_name(object me, string skill)
{
        mapping actions;
        string  skill_name, action;
        int     a, b;

        if( !find_object(SKILL_D(skill)) && !load_object(SKILL_D(skill)) )
                return HIG + to_chinese(skill);

        if( !mapp(actions=SKILL_D(skill)->query_action(me,query_temp("weapon", me))) )
                return HIG + to_chinese(skill);

        if( !undefinedp(actions["skill_name"]) )
                return HIG + actions["skill_name"];

        if( undefinedp(actions["action"]) )
                return HIG + to_chinese(skill);

        action = actions["action"];

        if( strsrch(action, "「") != -1 && strsrch(action, "」") != -1 ) {
                a = strsrch(action, "「");
                b = strsrch(action, "」");
                skill_name = action[a..b+1];
                return HIG + to_chinese(skill) + NOR + (random(2)?"的一招"YEL:"中的"YEL) + skill_name + NOR;
        } else if( strsrch(action, "【") != -1 && strsrch(action, "】") != -1 ) {
                a = strsrch(action, "【");
                b = strsrch(action, "】");
                skill_name = action[a..b+1];
                return HIG + to_chinese(skill) + NOR + (random(2)?"的一招"YEL:"中的"YEL) + skill_name + NOR;
        } else if( strsrch(action, "“") != -1 && strsrch(action, "”") != -1 ) {
                a = strsrch(action, "“");
                b = strsrch(action, "”");
                skill_name = action[a..b+1];
                return HIG + to_chinese(skill) + NOR + (random(2)?"的一招"YEL:"中的"YEL) + skill_name + NOR;
        } else return HIG + to_chinese(skill);
}

int skill_t_number(string e_name)
{
        /*
        string *list;
        int    i, flag, total_z_number;

        if( !SKILL_D(e_name)->is_invent_skill() )
                return 0;
                
        list = explode(read_file(SKILL_D(e_name) + SYC), "\n");

        for( i = sizeof(list) - 1; i > 0; i-- )
        {
                if (! stringp(list[i])) continue;
                if (sscanf(list[i], "// ZHAOSHI : %d", total_z_number) == 1)
                {
                        flag = 1;
                        break;
                }
        }
        
        if( !flag )
        {
                write(HIR "可能出现异常了，请找巫师帮助解决。\n" NOR);  
                return 0;    
        }
                
        return total_z_number;
        */
        return sizeof(SKILL_D(e_name)->query_actions());
}

void input_skill_name(string arg, object me)
{
        string  c_name, e_name, skill;
        int     i;
        object  invent;
        mapping temp, s_skill;
        
        temp = me->query_entire_temp_dbase();
        s_skill = temp["invent"]["spe_skill"];
               
        if( sscanf(arg, "%s %s", arg, c_name) != 2 )
        {
                tell_object(me, "对不起，请用：<英文名> <中文名> 的格式输入。\n请重新输入：");
                input_to((: input_skill_name :), me);
                return;
        }
        
        if ((strlen(arg) < 3) || (strlen(arg) > 10))
        {
                tell_object(me, "对不起，英文名必须是 3 到 10 个英文字母。\n请重新输入：");
                input_to((: input_skill_name :), me);
                return;
        }

        while (i--)
        {
                if (arg[i] < 'a' || arg[i] > 'z' )
                {
                        tell_object(me, "对不起，英文名只能用英文字母。\n请重新输入：");
                        input_to((: input_skill_name :), me);
                        return;
                }
        }
        
        skill = temp["invent"]["skill"];
        arg = arg + "-" + skill;
        e_name = arg;

        if( file_size(SKILL_D(arg) + SYC) > 0 
         || get_object(SKILL_D(arg)) 
         || arg != to_chinese(arg) ) {
                        tell_object(me, "对不起，已经有("+ e_name +")这种武功存在。\n请重新输入：");
                        input_to((: input_skill_name :), me);
                        return;
        }

        if( c_name && query_temp("big5", me) )
                c_name = LANGUAGE_D->toGB(c_name);
                
        if( !is_chinese(c_name) ) {
                        tell_object(me, "对不起，请用【中文】做中文名。\n请重新输入：");
                        input_to((: input_skill_name :), me);
                        return;
        }

        if (member_array(c_name, banned_name) % 2 == 0)
        {
                tell_object(me, "对不起，这种名称会造成其他人的困扰。\n请重新输入：");
                input_to((: input_skill_name :), me);
                return;
        }

        if( strlen(c_name) > 20 ) {
                tell_object(me, "对不起，您设置的中文名太长，请选一个精湛一点的名字。\n请重新输入：");
                input_to((: input_skill_name :), me);
                return;
        }

        c_name += type_name[skill];
        s_skill["skill_e_name"] = e_name;
        s_skill["skill_c_name"] = c_name;
        
        if( CHINESE_D->find_skill(c_name) ) {
                        tell_object(me, "对不起，已经有[" + c_name + "]这种武功存在。\n请重新输入：");
                        input_to((: input_skill_name :), me);
                        return;
        }


        tell_object(me, HIW"\n\n\n您成功的自创出了" HIG + c_name + "(" + e_name + ")" HIW "这套" + valid_types[skill]
                                 + NOR "\n您可以为这个武功添加一段描述！\n"
                                 "----------------------------------------------------------------\n\n"
                                 + sort_msg("如：" + c_name + "是创自" + me->name(1) + "的绝世" + valid_types[skill] + 
                                            "，招式勇往直前，大开大阖，以勇猛霸道而著称，当初江湖十大掌门"
                                            "围攻" + me->name(1) + "的时候，情势万分危机，" + me->name(1)
                                            + "在千钧一发之际使出这套武功，顿时风云变色，化险为夷……\n\n")
                                 + "----------------------------------------------------------------\n\n"
                                 + "请输入：");
        me->edit(bind((: call_other, __FILE__, "describe_done", me, skill, e_name, c_name :), me));
}

void describe_done(object me, string skill, string e_name, string c_name, string msg)
{
        mapping temp, s_skill;
        
        temp = me->query_entire_temp_dbase();
        s_skill = temp["invent"]["spe_skill"];
        
        if( !stringp( msg ) || msg == "" )
                tell_object(me, "您放弃为这套武功添加描述！\n");
        else {
                if( strlen(msg) > 1000 ) {
                        tell_object(me, "您设定的描述太长了，请设定一个精简的描述。\n");
                        me->edit(bind((: call_other, __FILE__, "describe_done", me, skill, e_name, c_name :), me));
                        return;
                }
        }
        
        s_skill["skill_result"] = msg; 
        s_skill["skill_z_number"] = 1;
        
        tell_object(me, HIC "\n\n请给" + c_name + "招式起个名字(例如: " NOR HIY "悠哉" NOR HIC "):" NOR);         
        input_to( "get_z_c_name", me );
}

void skill_init_header(object me, string e_name)
{
        string  header;
        mapping temp, s_skill;
        
        temp = me->query_entire_temp_dbase();
        s_skill = temp["invent"]["spe_skill"];
        e_name += SYC;
        
        header =  "// This is player's own skill (Write by Lonely@nt2)\n";
        header += "// Create by "+query("name", me)+"("+capitalize(geteuid(me))+") at "+ctime(time())+"\n";
        header += "// " + s_skill["skill_c_name"] + "(" + e_name + ")\n";
        header += @HEADER

#include <ansi.h>
inherit SKILL;        
                
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
HEADER;
        
        write_file(SKILL_D(e_name), header, 1);
}

void get_z_c_name(string yn, object ob)
{
        mapping temp, s_skill;
        
        temp = ob->query_entire_temp_dbase();
        s_skill = temp["invent"]["spe_skill"];

        if( yn && query_temp("big5", ob) )
                yn = LANGUAGE_D->toGB(yn);
                                
        if( yn == "" ) {
                tell_object(ob, HIC "\n\n请给" + s_skill["skill_c_name"] + "招式起个名字(例如: " NOR HIY "悠哉" NOR HIC "):" NOR);   
                input_to( (: get_z_c_name :), ob );
                return;
        }

        switch( yn[0] ) {
        case 'E':
        case 'Q':
                delete_temp("invent", ob);
                tell_object(ob, "你决定放弃自创武功。\n");
                return;
        }

        if( !is_chinese(yn) ) {
                tell_object(ob, "招式名称：");
                input_to( (: get_z_c_name :), ob );
                return;
        }
        
        s_skill["skill_name"] = yn;

        tell_object(ob, HIR "\n注意问题: $N 代表你 $n 代表敌人 $l 代表攻击部位 $w 代表你的武器 \n" NOR);
        tell_object(ob, BLINK WHT "例如:(拳脚类)\n" NOR);
        tell_object(ob, "$N两臂紧伸，腿脚尖点地，一式「同归黄泉」，死死的包住$n往半空中自旋而上\n\n");
        tell_object(ob, BLINK WHT "又例如:(带武器类)\n" NOR); 
        tell_object(ob, "$N纵身一跃，手握$w,顿时一招「斜阳竖月」对准$n的某部位斜斜刺出一剑\n\n");
        tell_object(ob, "招式描述：");

        input_to("get_z_c_action", ob);

}

void get_z_c_action(string yn, object ob)
{
        string  skill_type;
        mapping temp, s_skill;
        
        temp = ob->query_entire_temp_dbase();
        s_skill = temp["invent"]["spe_skill"];
 
        if( yn && query_temp("big5", ob) )
                yn = LANGUAGE_D->toGB(yn);
                        
        if (yn == "") 
        {
                tell_object(ob, HIR "\n注意问题: $N 代表你 $n 代表敌人 $l 代表攻击部位 $w 代表你的武器 \n" NOR);
                tell_object(ob, BLINK WHT "例如:(拳脚类)\n" NOR);
                tell_object(ob, "\t$N两臂紧伸，腿脚尖点地，一式「同归黄泉」，死死的包住$n往半空中自旋而上\n\n");
                tell_object(ob, BLINK WHT "又例如:(带武器类)\n" NOR); 
                tell_object(ob, "\t$N纵身一跃，手握$w,顿时一招「斜阳竖月」对准$n的某部位斜斜刺出一剑\n\n");
                tell_object(ob, "招式描述：");
                input_to((: get_z_c_action :), ob);
                return;
        }
        
        // 退出自创
        switch(yn[0])
        {
        case 'e':
        case 'q':
                delete_temp("invent", ob);
                tell_object(ob, "你决定放弃自创武功招式。\n");
                return;
        }
                       
        skill_type = temp["invent"]["skill"];
        
        s_skill["action"] = color_filter(yn);
        s_skill["action"] = replace_string(s_skill["action"], " ", "");
        s_skill["action"] = replace_string(s_skill["action"], "\"", "");
        s_skill["action"] = replace_string(s_skill["action"], "你", "$N");
        s_skill["action"] = replace_string(s_skill["action"], "老猫", "$n");               
        s_skill["action"] = replace_string(s_skill["action"], "某部位", "$l");              

        if ( member_array(skill_type, weapon_types) != -1 )
                s_skill["action"] = replace_string(s_skill["action"], "武器", "$w");
                
       // 自创武工的威力由武修、人物等级、智商决定
        s_skill["attack"]=query("level", ob)/15+query("int", ob)+
                            sizeof(query_temp("invent/mut_skills", ob))*5+
                            query_temp("invent/mut_level", ob)/10+
                            ob->query_skill("martial-cognize", 1) / 20 - 100;
        if (s_skill["attack"] > 260) s_skill["attack"] = 260;
        s_skill["damage"]=query("level", ob)/15+query("str", ob)+
                            sizeof(query_temp("invent/mut_skills", ob))*5+
                            query_temp("invent/mut_level", ob)/10+
                            ob->query_skill("martial-cognize", 1) / 20 - 100;
        if (s_skill["damage"] > 260) s_skill["damage"] = 260;
        s_skill["force"]=query("level", ob)/15+query("con", ob)+
                            sizeof(query_temp("invent/mut_skills", ob))*5+
                            query_temp("invent/mut_level", ob)/10+
                            ob->query_skill("martial-cognize", 1) / 20 - 100;
        if (s_skill["force"] > 260) s_skill["force"] = 260;
        s_skill["dodge"]=query("level", ob)/15+query("dex", ob)+
                            sizeof(query_temp("invent/mut_skills", ob))*5+
                            query_temp("invent/mut_level", ob)/10+
                            ob->query_skill("martial-cognize", 1) / 20 - 100;
        if (s_skill["dodge"] > 260) s_skill["dodge"] = 260;
        s_skill["parry"]=query("level", ob)/15+query("con", ob)+
                            sizeof(query_temp("invent/mut_skills", ob))*5+
                            query_temp("invent/mut_level", ob)/10+
                            ob->query_skill("martial-cognize", 1) / 20 - 100;
        if (s_skill["parry"] > 260) s_skill["parry"] = 260;
        
        switch(skill_type){
        case "unarmed":
                s_skill["damage_type"] = "瘀伤";
                break;
        case "sword":
        case "spin":
                s_skill["damage_type"] = "刺伤";
                break;
        case "blade":
                s_skill["damage_type"] = "割伤";
                break;
        case "strike":
                s_skill["damage_type"] = "内伤";
                break;
        default:
                s_skill["damage_type"] = "瘀伤";
                break;
        }                             
        s_skill["lvl"] = spe_skill_level[s_skill["skill_z_number"] - 1];                                
        
        if (s_skill["skill_z_number"] == 1)                        
                tell_object(ob, HIR "\n你自创了一套" + s_skill["skill_c_name"] + "(" + s_skill["skill_e_name"] + ")\n" NOR
                                HIY "武功类型：" NOR HIC + valid_types[skill_type] + "\n" NOR
                                HIY "武功描述：\n" NOR HIC + s_skill["skill_result"] + "\n" NOR
                                HIY "首招名称：" NOR HIC + s_skill["skill_name"] + "\n" NOR
                                HIY "首招描述：" NOR HIC + s_skill["action"] + "\n" NOR
                                HIY "首招攻击：" NOR HIC + s_skill["attack"] + "\n" NOR
                                HIY "首招伤害：" NOR HIC + s_skill["damage"] + "\n" NOR
                                HIY "附加伤害：" NOR HIC + s_skill["force"] + "\n" NOR
                                HIY "首招招架：" NOR HIC + s_skill["parry"] + "\n" NOR
                                HIY "首招躲闪：" NOR HIC + s_skill["dodge"] + "\n" NOR
                                HIR "你确定吗？(Y/N)" NOR);
        else
                tell_object(ob, HIR "你自创了一套" + s_skill["skill_c_name"] + "(" + s_skill["skill_e_name"] + 
                                HIR ")的第" + chinese_number(s_skill["skill_z_number"]) + "招\n" NOR
                                HIY "此招名称：" NOR HIC + s_skill["skill_name"] + "\n" NOR
                                HIY "此招描述：" NOR HIC + s_skill["action"] + "\n" NOR
                                HIY "此招攻击：" NOR HIC + s_skill["attack"] + "\n" NOR
                                HIY "此招伤害：" NOR HIC + s_skill["damage"] + "\n" NOR
                                HIY "附加伤害：" NOR HIC + s_skill["force"] + "\n" NOR
                                HIY "此招招架：" NOR HIC + s_skill["parry"] + "\n" NOR
                                HIY "此招躲闪：" NOR HIC + s_skill["dodge"] + "\n" NOR
                                HIR "你确定吗？(Y/N)" NOR); 

        input_to("decide_input", ob, skill_type, s_skill["skill_e_name"], s_skill["skill_c_name"]);
}

void decide_input(string arg, object me, string skill, string e_name, string c_name)
{
        object  ob, book;
        mapping temp, s_skill;
        
        temp = me->query_entire_temp_dbase();
        s_skill = temp["invent"]["spe_skill"];
                
        if( arg == "y" || arg == "Y" ) {
                if( s_skill["skill_z_number"] == 1 ) {
                        if( objectp( ob = get_object(SKILL_D(e_name)) ) ) {
                                delete_temp("invent", me);
                                tell_object(me, "BUG！请联系巫师！\n");
                                return;
                        }
                
                        finish_write_skill(me, e_name);

                        log_file("invent", sprintf("%s(%s) %s(%s): %d (%s)\n",
                                           query("name", me),
                                           query("id", me),
                                           c_name,
                                           e_name,
                                           s_skill["skill_z_number"],
                                           ctime(time())));

                        if( get_object(SKILL_D(e_name)) ) {
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                        sprintf("%s(%s)将生平所学的" + chinese_number(sizeof(query_temp("invent/mut_skills", me)))
                                                + "套" + valid_types[skill] + "合而为一，自创出一套绝世的" NOR HIW
                                                + "《" + c_name + "》" NOR HIM "，从此进入"
                                                + valid_types[skill] + "的全新境界 。" NOR,
                                                me->name(1),query("id", me)));
                                me->force_me("chat*admire2"+query("id", me));
                        
                                CHINESE_D->add_translate(e_name, c_name);                        
                                        
                                set("invent/"+skill, e_name, me);
                                me->set_skill(e_name, 100);
                                delete_temp("invent", me);
                                book = write_skill_book(me, c_name, e_name);
                                book->move(me, 1);
                                tell_object(me, HIM "你将绝世武学" + c_name + "记录在薄绢上！\n" NOR);
                                me->save();
                        }

                } else {
                        if( !objectp( ob = get_object(SKILL_D(e_name)) ) ) {
                                delete_temp("invent", me);
                                tell_object(me, "BUG！请联系巫师！\n");
                                return;
                        }                        
                        destruct(ob);
                        finish_write_skill(me, e_name);
                        get_object(SKILL_D(e_name));
                        log_file("invent", sprintf("%s(%s) %s(%s): %d (%s)\n",
                                           query("name", me),
                                           query("id", me),
                                           c_name,
                                           e_name,
                                           s_skill["skill_z_number"],
                                           ctime(time())));
                                           
                        CHANNEL_D->do_channel(this_object(), "rumor",
                                           sprintf("%s(%s)将生平所学融合吸收，为" NOR HIW + "《" + c_name + "》" NOR
                                           HIM "创出新的招式" NOR HIC + "《" + s_skill["skill_name"] + "》" NOR + HIM "。" , 
                                           me->name(1),query("id", me)));
                                                
                        me->force_me("chat*admire2"+query("id", me));
                        delete_temp("invent", me);
                        me->save();
                } 


        } else {
                if( s_skill["skill_z_number"] == 1 ) {
                        tell_object(me, HIW"请重新输入！"
                                        HIY"格式："HIC"<英文名> <中文名>\n\n"NOR
                                        "如输入：wuyou 无忧\n"
                                        "系统会产生一种无忧"HIR + type_name[skill] + NOR "(wuyou-"
                                        HIR + skill + NOR")的剑法\n"
                                        HIW"勿用骚扰性或不雅的名字\n"NOR
                                        "请输入：");
                        input_to("input_skill_name", me, skill);
                } else {
                        tell_object(me, HIC "\n\n请给" + c_name + "新招式起个名字(例如: " NOR HIY "悠哉" NOR HIC "):" NOR);          
                        input_to( "get_z_c_name", me ); 
                }                       
        }
}

void finish_write_skill(object ob, string skill)
{
        mapping temp, s_skill;
        string  action;
        string  file, *list;
        string  content;
        int     total_z_number, i, flag;
        string  *list2;
        string  header2;
        string  result;
        string  skill_type;        
        string  dir;
        
        temp = ob->query_entire_temp_dbase();
        s_skill = temp["invent"]["spe_skill"];
        skill_type = temp["invent"]["skill"];
        header2 = "";
        result = "";
        content = "";
        action = "";  

        if( s_skill["skill_z_number"] == 1 )
                skill_init_header(ob, skill);      
          
        action += "\n([      " + SYN + 
                  "action" + SYN + " : " + SYN + s_skill["action"] + SYN + ",\n\t" + SYN + 
                  "attack" + SYN + " : " +  s_skill["attack"] + ",\n\t" + SYN + 
                  "damage" + SYN + " : " +  s_skill["damage"] + ",\n\t" + SYN + 
                  "force" + SYN + " : " +  s_skill["force"] + ",\n\t" + SYN +
                  "dodge" + SYN + " : " + s_skill["dodge"] + ",\n\t" + SYN + 
                  "parry" + SYN + " : " + s_skill["parry"] + ",\n\t" + SYN + 
                  "lvl" + SYN + " : " + s_skill["lvl"] + ",\n\t" + SYN + 
                  "damage_type" + SYN + " : " + SYN + s_skill["damage_type"] + SYN + ",\n\t" + SYN + 
                  "skill_name" + SYN + " : " + SYN + s_skill["skill_name"] + SYN +
                  "\n ])," +
                  "\n// ZHAOSHI : " + s_skill["skill_z_number"];
        action += "\n});\n";

        file = read_file(SKILL_D(skill + SYC));
        if( (int)file != 0 )
                list = explode(file, "\n");

        if( skill_type == "unarmed" 
                || skill_type == "strike"
                || skill_type == "finger" )
                header2 = read_file(SKILL_MODEL_UNARMED);
        else if( skill_type=="sword" 
                || skill_type == "blade"
                || skill_type=="spear"
                || skill_type=="hammer"
                || skill_type=="whip" )
                header2 = read_file(SKILL_MODEL_WEAPON);
        else 
                header2 = read_file(SKILL_MODEL_DEFAULT);

        list2 = explode(header2, "\n");
        for( i = 0; i < sizeof(list2); i++ ) {
                list2[i]= replace_string(list2[i], "SKILL_EN_NAME", 
                          SYN + skill + SYN);
                list2[i]= replace_string(list2[i], "SKILL_CH_NAME", 
                          SYN + s_skill["skill_c_name"] + SYN);
                list2[i]= replace_string(list2[i], "SKILL_BASE_NAME", 
                          SYN + skill_type + SYN);
        }
        
        result += implode(list2, "\n");

        for( i = sizeof(list) - 1; i > 0; i-- ) {
                if (! stringp(list[i])) continue;
                if (sscanf(list[i], "// ZHAOSHI : %d", total_z_number) == 1)
                {
                        flag = 1;
                        break;
                }
        }
        
        if( !flag )
        {
                tell_object(ob, HIR "可能出现异常了，请找巫师帮助解决。\n" NOR);  
                return;    
        }

        content =  implode(list[0..i-1], "\n");
        content += "\n// ZHAOSHI : " + (string)total_z_number;
        content += action;
        write_file(SKILL_D(skill) + SYC, content, 1);        
        write_file(SKILL_D(skill) + SYC, "\n" + result);
        
        if( stringp(s_skill["skill_result"]) ) {
                s_skill["skill_result"] = replace_string(s_skill["skill_result"], "\n", "");
                s_skill["skill_result"] = sort_msg(s_skill["skill_result"]);
        
                content = @CODE
string query_description()
{
CODE;
                content += "\treturn\n \"" + s_skill["skill_result"] + "\" ; \n}\n";
        
                write_file(SKILL_D(skill) + SYC, "\n" + content); 
        }       
        /*
        dir = SKILL_D(skill) + "/";
        mkdir(dir);
        */
        
        SKILLS_D->add_skill_into_skills(skill, s_skill); 
        return;
}

mixed write_skill_book(object me, string skill_c_name, string skill_e_name)
{
        string file, content;
        object ob;
        
        content = @BOOK
#include <ansi.h> 

inherit BOOK;
inherit F_NOCLONE;

void create()
{
BOOK;
        content += sprintf("\tset_name(\"「%s」\", ({ \"%s book\" }));\n", skill_c_name, skill_e_name);
        content += @BOOK
        set_weight(500);
        /*
        if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "本");
BOOK;
        content += sprintf("\t\tset(\"long\", \"这是一本用薄绢写成的书。上书：“%s”。\\n书上署名%s(%s)。\\n\");\n",
                          skill_c_name,query("name", me),query("id", me));
        content += @BOOK
                set("value", 1);
                set("auto_load", 1);
                set("material", "silk");
                set("skill", ([
BOOK;
        content += sprintf("\t\t\t\"name\": \"%s\",\n", skill_e_name);
        content += @BOOK
                        "exp_required": 100000,
                        "jing_cost" :  40,
                        "difficulty": 100,
                        "max_skill" :  199,
                        "min_skill" :  0
                ]) );
        }
        setup();
        check_clone();
}
BOOK;
        file = "/data/book/" + skill_e_name + ".c";
        assure_file(file); 
        write_file(file, content, 1);           
        catch(call_other(file, "???"));
        ob = find_object(file);
        return ob;
}

        
int help(object me)
{
        write(@HELP
                                         
指令格式: invent                查看自己自创武功的情况
          invent ?              查看目前可以自创的武功种类
          invent <基本武功>     自创一种武功
          invent <已创武功>     继续自创一种武功的招式
          invent <基本武功> ?   查看该基本武功的已创武功
          invent <基本武功> d   删除该基本武功的已创武功

历来武林中堪称一代宗师者，均是于武学上总结己之所学，并能
融会各家之所长，开创武林中先河者。武学虽然可能源于一脉，
但各人所学加之经历之不同，却对同一事物有不同领悟。如此，
武林才变得如今般绚丽多彩。然而，开辟武林中的新溪经并非易
事，需要耗费无数心血及精力才有可能独树一帜，成先人所未曾
想。 

HELP );
        return 1;
}
