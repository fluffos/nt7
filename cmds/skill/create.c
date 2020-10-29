// Copyright (C) 2005, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// 需要玩家输入主要为以下四个部分
// c_name(e_name) 绝招档名和绝招名称
// pfm_attack_msg 绝招发招描述
// pfm_succeed_msg 绝招打中描述
// pfm_fail_msg 绝招失误描述

#include <ansi.h>
#include <command.h>
#define  SYN "\""
#define  SYC ".c"
#define  NEED_LVL   1600

#define  PERFORM_MODEL_LIAN  "/clone/meskill/perform_model_lian.h"
#define  PERFORM_MODEL_DAN   "/clone/meskill/perform_model_dan.h"
#define  PERFORM_MODEL_HUN   "/clone/meskill/perform_model_hun.h"

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
        "whip":         "鞭法",
        "finger":       "指法",
        "hand":         "手法",
        "cuff":         "拳法",
        "claw":         "爪法",
        "strike":       "掌法",
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
        "似乎可以融合贯通，顿时心内一阵狂喜！",
        "可以相互取长补短，开辟一种全新的境界。",
        "如果连续使出，似乎可以将威力发挥至极限。",
        "如果详加修正，可以相互弥补个中不足，创造出更完美的绝招。"
});

string *banned_name = ({
        "你", "你", "我", "他", "她", "它",
        "爸", "爷", "　", "妈",
        "屎", "尿", "粪",
});

string get_skill_name(object me, string skill);

void get_perform_model(string arg, object me, string base_skill, string skill);
void get_perform_name(string arg, object me, string base_skill, string skill, string model);
void get_perform_msg1(object me, string base_skill, string skill, string model, string c_name, string e_name, string msg);
void get_perform_msg2(object me, string base_skill, string skill, string model, string c_name, string e_name, string pfm_attack_msg, string msg);
void get_perform_msg3(object me, string base_skill, string skill, string model, string c_name, string e_name, string pfm_attack_msg, string pfm_succeed_msg, string msg);
void decide_input_perform(string arg, object me, string base_skill, string skill, string model, string c_name, string e_name, string pfm_attack_msg, string pfm_succeed_msg, string pfm_fail_msg);
void finish_write_perform(object me, string base_skill, string skill, string model, string c_name, string e_name, string pfm_attack_msg, string pfm_succeed_msg, string pfm_fail_msg);

int main(object me, string arg)
{
        mapping creates;
        string  skill, perform, base_skill;
        string  *types, *performs, *skills;
        object  weapon, where;
        mapping skills_map;
        string  msg, dir, *mut_skills = ({});
        int     i, j;
        int     flag = 0;
        
        seteuid(getuid());
        where = environment(me);
        
        if (! wizardp(me) && ! MEMBER_D->is_valid_member(query("id", me))) 
                return notify_fail("只有会员才可以自创任何绝招。\n");

        if( !arg ) {
                if( !mapp(creates=query("create", me)) )
                        return notify_fail("你目前还没有任何自创绝招。\n");
                        
                skills = keys(creates);   
 
                msg = WHT "你目前共自创的武功绝招情况如下：\n" NOR;               
                for( i = 0; i < sizeof(skills); i++ ) {  
                        msg += HIC "\n" + skills[i] + " ：";          
                        performs = keys(creates[skills[i]]);
                        for( j = 0; j < sizeof(performs); j++ ) {
                                msg += performs[j];
                                msg += (j == (sizeof(performs) -1) ? NOR :  WHT " - " HIC);
                        }
                }
                
                msg += "\n\n";
                tell_object(me, msg);

                return 1;
        }

        if( sscanf(arg, "%s %s d", skill, perform) == 2 ) {                        
                object ob;
                if( !query("create/"+skill, me) )
                        return notify_fail("没有自创这种武功绝招，请确认输入的武功英文名称。\n");
                
                if( !query("create/"+skill+"/"+perform, me) )
                        return notify_fail("没有自创这种武功绝招，请确认输入的绝招英文名称。\n");
                
                tell_object(me, HIR "你删除了自创" + to_chinese(skill) + "绝招" + to_chinese(perform) + "(" + perform + ")。\n" NOR);                                                
                CHINESE_D->remove_translate(perform);                        
                dir = SKILL_D(skill);
                if (dir[strlen(dir) - 1] != '/')
                        dir += "/";              
                if (SKILL_D(skill)->valid_enable("force"))
                        dir += "perform/";                             
                if (ob = get_object(dir + perform + SYC))
                        destruct(ob);
                rm( dir + perform + SYC );                        
                delete("can_perform/"+skill+"/"+perform, me);
                delete("create/"+skill+"/"+perform, me);
                if( !mapp(query("create/"+skill, me)) || 
                        sizeof(query("create/"+skill, me))<1 )
                        delete("create/"+skill, me);
                        
                if( !mapp(query("create", me)) || 
                        sizeof(query("create", me))<1 )
                        delete("create", me);
                        return 1;
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

        if( query("lgt/upd", me)<600 )
                return notify_fail("你还没有登上过灵感塔600层，还是好好努力修炼吧。\n");

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

        if( !mapp(skills_map = me->query_skills() ) || sizeof(skills_map) < 1 )
                return notify_fail("你还是先去学点功夫再来吧。\n");

        if( undefinedp(skills_map[arg]) || skills_map[arg] < 1 )
                return notify_fail("你连基本的" + to_chinese(arg) + "都不会，从何谈起？\n");

        if( me->query_skill("martial-cognize", 1) < NEED_LVL )
                return notify_fail("你的武学修养的修为还不够高深。\n");

        if( skills_map[arg] < NEED_LVL )
                return notify_fail("你的" + to_chinese(arg) + "的修为还不够高深。\n");
                                
        if( SKILL_D(arg)->type() != "martial" )
                return notify_fail("你无法为这种武功创造绝招。\n");

        dir = SKILL_D(arg) + "/";

        // if( file_size(dir) != -2 )
        //        return notify_fail("你无法为这种武功创造绝招。\n");
                        
        /*
        if( SKILL_D(arg)->is_invent_skill() ) {
                if( query("jieti/times", me)<2 )
                        return notify_fail("你目前还无法为这种自创武功创造绝招。\n"); 
        }  
        */
 
        types = keys(valid_types);        
        for( i = 0; i < sizeof(types); i++ ) 
        {
                if( SKILL_D(arg)->valid_enable(types[i]) ) 
                        continue;
                        
                types[i] = 0;
        }
        
        types -= ({ 0 });
        
        // if( sizeof(types) != 1 )
        if( sizeof(types) < 1)
                return notify_fail("你目前还无法为这种自创武功创造绝招。\n"); 
               
        base_skill = types[0];
        skill = arg;
        
        if( objectp(weapon=query_temp("weapon", me))){
                if( member_array(base_skill, weapon_types) == -1 ) {
                        if (sizeof(types) == 1)
                                return notify_fail("你必须空手才能自创" + to_chinese(skill) + "的绝招。\n");
                        else {
                                for (i = 1; i < sizeof(types); i++) {
                                        base_skill = types[i];
                                        if( member_array(base_skill, weapon_types) != -1 ) {
                                                flag = 1; // 可拿兵器
                                                break;
                                        }
                                }
                                if( flag != 1 ) return notify_fail("你必须空手才能自创" + to_chinese(skill) + "的绝招。\n");
                        }
                }
                if( member_array(base_skill, weapon_types) != -1 ) {
                        if( query("skill_type", weapon) != base_skill){
                                if (sizeof(types) == 1)
                                        return notify_fail("你所使用的武器不对，无法自创" + to_chinese(skill) + "的绝招。\n");
                                else {
                                        for (i = 1; i < sizeof(types); i++) {
                                                base_skill = types[i];  
                                                if( query("skill_type", weapon) == base_skill){
                                                        flag = 2;
                                                        break;
                                                }
                                        }
                                        if( flag != 2 )
                                                return notify_fail("你所使用的武器不对，无法自创" + to_chinese(skill) + "的绝招。\n");
                                }
                        }
                }
                        
        } else 
        if( member_array(base_skill, weapon_types) != -1 ) {
                if (sizeof(types) == 1)
                        return notify_fail("你必须拿起武器才能开始自创" + to_chinese(skill) + "的绝招。\n");
                else {
                        for (i = 1; i < sizeof(types); i++) {
                                base_skill = types[i]; 
                                if( member_array(base_skill, weapon_types) == -1 ) {
                                        flag = 3;
                                        break;
                                }
                        }
                        if( flag != 3 ) return notify_fail("你必须拿起武器才能开始自创" + to_chinese(skill) + "的绝招。\n");
                }
        }                                

        skills = keys(skills_map);

        foreach( string sk_tmp in skills ) {
                if( SKILL_D(sk_tmp)->valid_enable(base_skill) ) {
                        mut_skills += ({ sk_tmp });
                }
        }

        if( sizeof(mut_skills) < 3 )
                return notify_fail("你的" + valid_types[base_skill] + "修为还不够广博，再去多学习学习！\n");

        mut_skills = filter_array(mut_skills, (: $(skills_map)[$1] >= NEED_LVL :));

        if( sizeof(mut_skills) < 3 )
                return notify_fail("你在" + valid_types[base_skill] + "方面的修为还不够高深。\n");
        
        if( sizeof(query("create/"+skill, me)) >= 3 )
                return notify_fail("你的" + to_chinese(skill) + 
                                   "绝招数量已经到了极限，无法再自创新绝招。\n");
        delete_temp("create", me);
                                
                
        message_vision("$N盘膝坐下，开始苦思冥想，专心的自创" + to_chinese(skill) + "绝招。\n", me);              

        set_temp("create/skill", skill, me);
        set_temp("create/base_skill", base_skill, me);
        set_temp("create/mut_skills", mut_skills, me);
        
        me->set_short_desc("正在全神贯注地自创" + to_chinese(skill) + "绝招。");

        me->start_busy(bind((:call_other, __FILE__, "inventing" :), me),
                       bind((:call_other, __FILE__, "halt_inventing" :), me));

        CHANNEL_D->do_channel(this_object(), "rumor",
                              sprintf("%s(%s)开始闭关自创%s。\n",
                              me->name(1),query("id", me),to_chinese(skill)+"新绝招"));
        return 1;
}

int inventing(object me)
{
        int     max, i;
        string  pot;
        string  base_skill, skill, *mut_skills, *skills_tmp,
                msg = "", *msgs = ({});
        
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

        skill=query_temp("create/skill", me);
        base_skill=query_temp("create/base_skill", me);
        mut_skills=query_temp("create/mut_skills", me);

        if( random(20000)<query("int", me)){
                string *chinese_skills = ({});

                foreach(string mut_skill in mut_skills) {
                        chinese_skills += ({ to_chinese(mut_skill)});
                }
                
                message_sort("猛然间$N脑中略过种种招式，融合" + 
                                sprintf( HIG"%s" NOR "以及" HIG "%s"NOR, 
                                implode(chinese_skills[0..sizeof(chinese_skills)-2], NOR "、" HIG), 
                                chinese_skills[sizeof(chinese_skills)-1])
                                + "这" + chinese_number(sizeof(mut_skills)) + "种武功之精髓为"
                                + to_chinese(skill) + "创出新的绝招\n", me);

                me->clear_written();
                me->set_short_desc(0);   
                delete_temp("create", me);
                tell_object(me, HIW "\n任何时候输入 ~q 则可终止自创绝招。\n" NOR);
                tell_object(me, HIW "\n\n你正在为" + to_chinese(skill) + "自创新的绝招。\n" NOR
                                "你可以为这个绝招选择创建以下类型\n\n" NOR);                
                tell_object(me, "\t1> 创建一个为连招的绝招\n");
                tell_object(me, "\t2> 创建一个为单招的绝招\n");
                tell_object(me, "\t3> 创建一个为混合招的绝招\n");                   
                tell_object(me, "\t3> 请重新选择1-3：");       
                    
                input_to( (: get_perform_model :), me, base_skill, skill );
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

        foreach(string sk_tmp in skills_tmp) {
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
        delete_temp("create", me);
        tell_object(me, HIG "你中止了自创绝招。\n" NOR);
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

void get_perform_model(string arg, object me, string base_skill, string skill)
{
        string model;
        int n;
        
        if( arg == "" || arg == "~q" )
        {
                tell_object(me, "你放弃了自创绝招。\n"); 
                return;
        }
                
        n = to_int(atoi(arg));
        if (n < 1 || n > 3)
        {
                tell_object(me, "对不起，您只能选择1-3，按下回车直接选择连照。\n\n");
                tell_object(me, "\t1> 创建一个为连招的绝招\n");
                tell_object(me, "\t2> 创建一个为单招的绝招\n");
                tell_object(me, "\t3> 创建一个为混合招的绝招\n");   
                tell_object(me, "\t3> 请重新选择1-3：");       
                input_to((: get_perform_model :), me, base_skill, skill);
                return;
        }
        
         switch(n)
        {
        case 1:
                model = "连招型";
                break;
        case 2:
                model = "单招型";
                break;
        case 3:
                model = "混合招型";
                break;
        }

        tell_object(me, HIW "\n\n\n你正在为" + to_chinese(skill) + "自创出了" + model + "的绝招。\n" NOR
                        "你可以为这个绝招取一个名字\n\n"
                        HIY "格式：" HIC "<英文名> <中文名>\n\n" NOR
                        HIW "勿用骚扰性或不雅的名字，否则将会被删除。\n" NOR
                        "请输入：");
        input_to( (: get_perform_name :), me, base_skill, skill, model );
}

void get_perform_name(string arg, object me, string base_skill, string skill, string model)
{
        string  c_name, e_name, file;
        int     i;
                       
        if( arg == "" || arg == "~q" )
        {
                tell_object(me, "你放弃了自创绝招。\n"); 
                return;
        }

        if( sscanf(arg, "%s %s", arg, c_name) != 2 )
        {
                tell_object(me, "对不起，请用：<英文名> <中文名> 的格式输入。\n请重新输入：");
                input_to((: get_perform_name :), me, base_skill, skill, model);
                return;
        }
        
        if ((strlen(arg) < 3) || (strlen(arg) > 10))
        {
                tell_object(me, "对不起，英文名必须是 3 到 10 个英文字母。\n请重新输入：");
                input_to((: get_perform_name :), me, base_skill, skill, model);
                return;
        }

        while (i--)
        {
                if (arg[i] < 'a' || arg[i] > 'z' )
                {
                        tell_object(me, "对不起，英文名只能用英文字母。\n请重新输入：");
                        input_to((: get_perform_name :), me, base_skill, skill, model);
                        return;
                }
        }
        
        e_name = arg;

        file = SKILL_D(skill);
        if( file[strlen(file) - 1] != '/' )
                file += "/";               
        if( SKILL_D(skill)->valid_enable("force") )
                file += "perform/";                       
        file += e_name;
        if( file_size(file + SYC) > 0 || get_object(file) ) {
                        tell_object(me, "对不起，已经有("+ arg +")这种绝招文件存在。\n请重新输入：");
                        input_to((: get_perform_name :), me, base_skill, skill, model);
                        return;
        }

        if( c_name && query_temp("big5", me) )
                c_name = LANGUAGE_D->toGB(c_name);
                
        if( !is_chinese(c_name) ) {
                        tell_object(me, "对不起，请用【中文】做中文名。\n请重新输入：");
                        input_to((: get_perform_name :), me, base_skill, skill, model);
                        return;
        }

        if (member_array(c_name, banned_name) % 2 == 0)
        {
                tell_object(me, "对不起，这种名称会造成其他人的困扰。\n请重新输入：");
                input_to((: get_perform_name :), me, base_skill, skill, model);
                return;
        }

        if( strlen(c_name) > 20 ) {
                tell_object(me, "对不起，您设置的中文名太长，请选一个精湛一点的名字。\n请重新输入：");
                input_to((: get_perform_name :), me, base_skill, skill, model);
                return;
        }
        
        tell_object(me, HIW "\n\n\n您成功为" + to_chinese(skill) + "新绝招设置好绝招名" 
                        HIW + c_name + "(" + e_name + ")" HIW "。\n" NOR);
                        
        tell_object(me, HIC "\n注意问题: $N 代表你 $n 代表敌人 $w 代表你的武器 \n\n" NOR);
        tell_object(me, HIC "例如：(拳脚类) \n" NOR);
        tell_object(me, HIM "$N" HIM "一声怒嚎，将战神心经提运极至，双拳顿时携着雷霆万钧之势猛贯向$n" HIM "。\n" NOR);
        tell_object(me, HIC "例如：(武器类)\n" NOR); 
        tell_object(me, HIM "$N" HIM "手中$w寒气逼人，刀身撕裂空气，片片雪花飘落，刀未至气先及，$n" HIM "眉毛都蒙上了薄薄白霜！\n\n" NOR);
        tell_object(me, HIC "请输入发招时描述：（长度不超过200个汉字）\n" NOR);                         
        me->edit(bind((: call_other, __FILE__, "get_perform_msg1", me, base_skill, skill, model, c_name, e_name :), me));
}

void get_perform_msg1(object me, string base_skill, string skill, string model, string c_name, string e_name, string msg)
{
        string pfm_attack_msg;
                        
        if( !stringp( msg ) || msg == "" ) {
                tell_object(me, "这套武功绝招不可以没有绝招描述！\n");
                me->edit(bind((: call_other, __FILE__, "get_perform_msg1", me, base_skill, skill, model, c_name, e_name :), me));
                return;
        }
        else {
                if( strlen(msg) > 400 ) {
                        tell_object(me, "您设定的描述太长了，请设定一个精简的描述。\n");
                        me->edit(bind((: call_other, __FILE__, "get_perform_msg1", me, base_skill, skill, model, c_name, e_name :), me));
                        return;
                }
        }

        msg = replace_string(msg, "\"", "");
        msg = replace_string(msg, "\n", "");
        msg = replace_string(msg, "$w", "武器");
        msg = replace_string(msg, "你", "$N");
        msg = filter_color(msg);
                     
        pfm_attack_msg = msg;
                              
        tell_object(me, HIC "\nOK\n" NOR); 
        tell_object(me, HIC "\n注意问题: $N 代表你 $n 代表敌人 $w 代表你的武器 \n\n" NOR);
        tell_object(me, HIC "例如：(拳脚类) \n" NOR);
        tell_object(me, HIM "结果$n" HIM "闪避不及，$N" HIM "的拳力掌劲顿时透体而入，口中鲜血狂喷，连退数步。\n" NOR);
        tell_object(me, HIC "例如：(武器类)\n" NOR); 
        tell_object(me, HIM "只见$n" HIM "一声惨叫，胸口给劈开一个巨大的口子，鲜血汹涌喷出！\n\n" NOR);
        tell_object(me, HIC "请输入绝招打中时描述：（长度不超过100个汉字）\n" NOR);    
        me->edit(bind((: call_other, __FILE__, "get_perform_msg2", me, base_skill, skill, model, c_name, e_name, pfm_attack_msg :), me));
}

void get_perform_msg2(object me, string base_skill, string skill, string model, string c_name, string e_name, string pfm_attack_msg, string msg)
{
        string pfm_succeed_msg;
        
        if( !stringp( msg ) || msg == "" ) {
                tell_object(me, "这套武功绝招不可以没有绝招描述！\n");
                me->edit(bind((: call_other, __FILE__, "get_perform_msg2", me, base_skill, skill, model, c_name, e_name, pfm_attack_msg :), me));
                return;
        }
        else {
                if( strlen(msg) > 200 ) {
                        tell_object(me, "您设定的描述太长了，请设定一个精简的描述。\n");
                        me->edit(bind((: call_other, __FILE__, "get_perform_msg2", me, base_skill, skill, model, c_name, e_name, pfm_attack_msg :), me));
                        return;
                }
        }
 
        msg = replace_string(msg, "\"", "");
        msg = replace_string(msg, "\n", "");
        msg = replace_string(msg, "$w", "武器");
        msg = replace_string(msg, "你", "$N");
        msg = filter_color(msg);
               
        pfm_succeed_msg = msg;
                              
        tell_object(me, HIC "\nOK\n" NOR);   
        tell_object(me, HIC "\n注意问题: $P 代表你 $p 代表敌人 $w 代表你的武器 \n" NOR);
        tell_object(me, HIC "例如：(拳脚类) \n" NOR);
        tell_object(me, HIM "可是$p" HIM "识破了$P" HIM "这一招，斜斜一跃避开。\n" NOR);
        tell_object(me, HIC "例如：(武器类)\n" NOR); 
        tell_object(me, HIM "$p" HIM "见势不妙，抽身急退，险险避过$P" HIM "的这记杀招，尘土飞扬中，地上裂开了一道大口子！\n\n" NOR);        
        tell_object(me, HIC "请输入绝招失误时描述：（长度不超过100个汉字）\n" NOR);   
        me->edit(bind((: call_other, __FILE__, "get_perform_msg3", me, base_skill, skill, model, c_name, e_name, pfm_attack_msg, pfm_succeed_msg :), me));
}

void get_perform_msg3(object me, string base_skill, string skill, string model, string c_name, string e_name, string pfm_attack_msg, string pfm_succeed_msg, string msg)
{
        string pfm_fail_msg;
        
        if( !stringp( msg ) || msg == "" ) {
                tell_object(me, "这套武功绝招不可以没有绝招描述！\n");
                me->edit(bind((: call_other, __FILE__, "get_perform_msg3", me, base_skill, skill, model, c_name, e_name, pfm_attack_msg, pfm_succeed_msg :), me));
                return;
        }
        else {
                if( strlen(msg) > 200 ) {
                        tell_object(me, "您设定的描述太长了，请设定一个精简的描述。\n");
                        me->edit(bind((: call_other, __FILE__, "get_perform_msg3", me, base_skill, skill, model, c_name, e_name, pfm_attack_msg, pfm_succeed_msg :), me));
                        return;
                }
        }

        msg = replace_string(msg, "\"", "");
        msg = replace_string(msg, "\n", "");
        msg = replace_string(msg, "$w", "武器");
        msg = replace_string(msg, "你", "$N");
        msg = filter_color(msg);
                
        pfm_fail_msg = msg;                            
        
        tell_object(me, HIW "\n你成功的为" + to_chinese(skill) + "新创的绝招设置以下相关信息。\n\n" NOR
                        HIC "绝招类型：" NOR HIC + model + "\n" NOR
                        HIC "中文名称：" NOR HIC + c_name + "\n" NOR
                        HIC "英文名称：" NOR HIC + e_name + "\n" NOR
                        HIC "发招描述：" NOR HIC + pfm_attack_msg + "\n" NOR
                        HIC "打中描述：" NOR HIC + pfm_succeed_msg + "\n" NOR
                        HIC "失误描述：" NOR HIC + pfm_fail_msg + "\n" NOR
                        HIW "你确定吗？(Y/N)" NOR);
                                
        input_to( (: decide_input_perform :), me, base_skill, skill, model, c_name, e_name, pfm_attack_msg, pfm_succeed_msg, pfm_fail_msg );
}

void decide_input_perform(string arg, object me, string base_skill, string skill, string model, string c_name, 
                          string e_name, string pfm_attack_msg, string pfm_succeed_msg, string pfm_fail_msg)
{
        object ob;
        string dir;
                
        if( arg == "y" || arg == "Y" ) {
                if( objectp( ob = get_object(SKILL_D(skill) + "/" + e_name) ) ) {
                        tell_object(me, "BUG！请联系巫师！\n");
                        return;
                }
                finish_write_perform(me, base_skill, skill, model, c_name, e_name, pfm_attack_msg, pfm_succeed_msg, pfm_fail_msg);

                log_file("create", sprintf("%s(%s) create %s's perform %s(%s) (%s)\n",
                                           query("name", me),
                                           query("id", me),
                                           skill,
                                           c_name,
                                           e_name,
                                           ctime(time())));
                
                dir = SKILL_D(skill);
                if (dir[strlen(dir) - 1] != '/')
                        dir += "/";
                
                if (SKILL_D(skill)->valid_enable("force"))
                        dir += "perform/";
                
                if( get_object(dir + e_name) ) {
                        CHANNEL_D->do_channel(this_object(), "rumor",
                                           sprintf("%s(%s)将生平所学融合吸收，为" NOR HIW + "《" + to_chinese(skill) + "》" NOR
                                           HIM "创出新的绝招" NOR HIC + "《" + c_name + "》" NOR + HIM "。" , 
                                           me->name(1),query("id", me)));
                        
                        me->force_me("chat*admire2"+query("id", me));
                        
                        CHINESE_D->add_translate(e_name, c_name);                        
                                        
                        set("create/"+skill, 1, get_object(SKILLS_D));
                        set("create/"+skill+"/"+e_name, 1, me);
                        set("can_perform/"+skill+"/"+e_name, 1, me);
                        me->save();
                }

        } else {
                tell_object(me, HIW "\n\n\n你为" + to_chinese(skill) + "自创出了新的绝招。\n" NOR
                                "你可以重新选择为这个绝招选择创建以下类型\n\n" NOR);      
                tell_object(me, "\t1> 创建一个为连招的绝招\n");
                tell_object(me, "\t2> 创建一个为单招的绝招\n");
                tell_object(me, "\t3> 创建一个为混合招的绝招\n");   
                tell_object(me, "\t3> 请重新选择1-3：");       
 
                input_to((: get_perform_model :), me, base_skill, skill);
        }                       
}

void finish_write_perform(object me, string base_skill, string skill, string model, string c_name, 
                          string e_name, string pfm_attack_msg, string pfm_succeed_msg, string pfm_fail_msg)
{
        string result, header1, header2;
        string dir;
        
        result  = "";
        header1 = "";
        header2 = "";
     
        header1 += "// This is player's own perform (Write by Lonely@nt2)\n";
        header1 += "// Create by "+query("name", me)+"("+capitalize(geteuid(me))+") at "+ctime(time())+"\n";
        header1 += "// " + c_name + "(" + e_name + ")\n"; 

        if( model == "连招型" ) 
                header2 = read_file(PERFORM_MODEL_LIAN);
        else if( model == "单招型" )
                header2 = read_file(PERFORM_MODEL_DAN);
        else
                header2 = read_file(PERFORM_MODEL_HUN);          
 
        header2 = replace_string(header2, "<绝招名>", c_name);
        header2 = replace_string(header2, "<PFM发招描述>", pfm_attack_msg); 
        header2 = replace_string(header2, "<PFM打中描述>", pfm_succeed_msg); 
        header2 = replace_string(header2, "<PFM失误描述>", pfm_fail_msg);
        header2 = replace_string(header2, "E_NAME", e_name);
        header2 = replace_string(header2, "BASE_SKILL", base_skill);
        header2 = replace_string(header2, "SKILL", skill);
        
        result = header1 + header2;
        
        dir = SKILL_D(skill);
        if (dir[strlen(dir) - 1] != '/')
                dir += "/";
                
        if (SKILL_D(skill)->valid_enable("force"))
                dir += "perform/";
                
        assure_file(dir); 
        write_file(dir + e_name + SYC, result, 1);
        write(HIC "绝招创建成功，以后请使用 " + HIY "perform " + e_name +  HIC " 使用该绝招。\n" NOR );
}

int help(object me)
{
        write(@HELP
                                         
指令格式: create                           查看自己自创武功绝招的情况
          create <武功名称>                为该武功自创新的绝招
          create <武功名称> <绝招名称> d   删除该武功的已创武功之绝招

HELP );
        return 1;
}
