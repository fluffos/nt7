// This program is a part of NITAN MudLIB
// Written by Lonely@nitan.org

#include <ansi.h>

// #pragma optimize
// #pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

#define ATTACK          0
#define DODGE           1
#define PARRY           2
#define DAMAGE          3
#define FORCE2          4
#define DIFFICULT       5
#define RANK            6
#define ATTRIBUTE       7
#define EFFECT          8
#define MAX_POINT       360
#define LV1_POINT       100
#define LV2_POINT       150
#define LV3_POINT       200

#define SKILL_FILE      CONFIG_DIR "skill_combat"
#define SKILLMIX_FILE   CONFIG_DIR "skill_mix"
#define DAZHAOMIX_FILE  CONFIG_DIR "dazhao_mix"

// (scores / users - score / user) / 200
#define TO_EFFECT(x, y, a, b)      ((y / 200) < 20 ? 20 - b : (y / 200) - b) + (x / y - a / b) / 100

nosave mapping add_skills = ([ ]);
nosave mapping rdc_skills = ([ ]);
mapping all_skills = ([ ]);
mapping all_record = ([ ]);
mapping initial_skills = ([ ]);
class mix {
string name;            // 技能组合名称
string dodge;           // 技能组合轻功
string parry;           // 技能组合招架
string force;           // 技能组合内功
mapping need;           // 技能特效条件
mapping stats;          // 技能组合效果
}
class mix *all_mixs = ({ });
class dazhaomix {
string name;
string p1;
string p2;
string p3;
string p4;
mapping need;
mapping stats;
int func;
}
class dazhaomix *all_dazhaomixs = ({ });

// initialization,initializtion
public void add_id_into_skills(object me);
public void remove_id_from_skills(object me);
public void remove_id_from_abandon(object me, string sname);
public void add_skill_into_skills(string sname, mapping p);
public void remove_skill_from_skills(object me, string sname);
public varargs void query_skill_power(object me, string arg);
public mixed skill_query_power(string skill);
public int query_skill_difficult(string skill);
public int enforce_power(object me, int enforce);
public int attack_power(object me, string skill);
public int defense_power(object me, string skill);
public int damage_power(object me, string skill);
public string skillmix_stats(object me);
protected void manage_skill();
protected void load_skill();
protected void load_skillmix();
class mix find_skillmix(object me);
protected mapping trans_data(string mark);
public mixed query_all_mixs() { return all_mixs; }
protected void disable_skillmix(object me);
varargs void enable_skillmix(object me, mapping stats, mapping need);
public void check_skillmix(object me, int flag);
public string query_save_file() { return DATA_DIR "skillsd"; }

nosave string *all_poison = ({
        "xx_poison", "corpse_poison", "fire_poison", "freezing",
});

string *kungfu1 = ({ "sword","blade","unarmed","claw","finger","strike","cuff","hand","whip","staff","club","hammer" });
mapping kungfu2 = ([
        "sword"   :  ({ 0,      -5,      10,     10,     10,      10,      10,   10,   -10,   -10,    -10,    -10, }),
        "blade"   :  ({ 5,       0,      10,     10,     10,      10,      10,   10,   -10,   -10,    -10,    -10, }),
        "unarmed" :  ({-10,     -10,     0,      5,      0,       0,       0,   -5,    10,    10,     10,     10, }),
        "claw"    :  ({-10,     -10,     -5,     0,      5,       0,       0,    0,    10,    10,     10,     10, }),
        "finger"  :  ({-10,     -10,     0,     -5,      0,       5,       0,    0,    10,    10,     10,     10, }),
        "strike"  :  ({-10,     -10,     0,      0,     -5,       0,       5,    0,    10,    10,     10,     10, }),
        "cuff"    :  ({-10,     -10,     0,      0,      0,      -5,       0,    5,    10,    10,     10,     10, }),
        "hand"    :  ({-10,     -10,     5,      0,      0,       0,      -5,    0,    10,    10,     10,     10, }),
        "whip"    :  ({10,      10,    -10,    -10,    -10,     -10,     -10,  -10,     0,     5,      0,     -5, }),
        "staff"   :  ({10,      10,    -10,    -10,    -10,     -10,     -10,  -10,    -5,     0,      5,      0, }),
        "club"    :  ({10,      10,    -10,    -10,    -10,     -10,     -10,  -10,     0,     -5,     0,      5, }),
        "hammer"  :  ({10,      10,    -10,    -10,    -10,     -10,     -10,  -10,     5,     0,     -5,      0, }),
]);
int kungfu_restraint_effect(string type1, string type2)
{
        int i, type2_i = 0;

        for (i = 0; i < sizeof(kungfu1); i++)
        {
                if (type2 == kungfu1[i])
                {
                        type2_i = i;
                        break;
                }
        }

        if (! type2_i) return 0;
        if (undefinedp(kungfu2[type1])) return 0;
        if (type2_i > sizeof(kungfu2[type1][type2_i]))
                return 0;

        return kungfu2[type1][type2_i];
}

nosave mapping family_name = ([
        "shaolin"  : "少林",
        "wudang"   : "武当",
        "gaibang"  : "丐帮",
        "quanzhen" : "全真",
        "huashan"  : "华山",
        "duan"     : "段氏",
        "murong"   : "慕容",
        "xueshan"  : "雪山",
        "lingjiu"  : "灵鹫",
        "emei"     : "峨嵋",
        "taohua"   : "桃花",
        "shenlong" : "神龙",
        "gumu"     : "古墓",
        "xingxiu"  : "星宿",
        "xiaoyao"  : "逍遥",
        "xuedao"   : "血刀",
        "ouyang"   : "欧阳",
        "hu"       : "胡家",
        "mingjiao" : "明教",
        "tang"     : "唐门",
        "riyue"    : "日月",
        "mojiao"   : "魔教",
        "taishan"  : "泰山",
        "songshan" : "嵩山",
        "hengshan" : "衡山",
        "henshan"  : "恒山",
        "qingcheng": "青城",
        "lingxiao" : "凌霄",
        "tiezhang" : "铁掌",
        "honghua"  : "红花",
        "yunlong"  : "云龙",
        "wudu"     : "五毒",
        "kunlun"   : "昆仑",
]);

void create()
{
        seteuid(getuid());
        restore();

        if( !mapp(all_skills) ||
            sizeof(all_skills) < 1 )
                load_skill();

        if (! (all_mixs) || sizeof(all_mixs) < 1 )
                load_skillmix();

        SCHEDULE_D->set_event(3600, 1, this_object(), "manage_skill");
        SCHEDULE_D->set_event(300, 1, this_object(), "broadcast_news");
}

void load_skill()
{
        string *tmp;
        string file;
        string line;
        string *arg, *skl;
        string skill, rank, attribute;
        int attack, dodge, parry, damage, force, difficult;

        file = read_file(SKILL_FILE);
        if( !stringp(file) ) return;

        // 去掉"\r"保证和MSDOS的文件格式兼容
        file = replace_string(file, "\r", "");

        tmp = explode(file, "\n");
        foreach( line in tmp )
        {
                reset_eval_cost();
                // 去掉行首的空格
                while( strlen(line) && line[0] == ' ' ) line = line[1..<1];
                if( line[0] == '#' )
                        // 注释
                        continue;

                if( line[0] == '&' )
                {
                        // 被系统注释的
                        line = line[1..<1];
                        while( strlen(line) && line[0] == ' ' ) line = line[1..<1];
                }

                if( !strlen(line) )
                        continue;

                arg = explode(line, "/");
                if( sizeof(arg) < 9 )
                {
                        log_file("static/skill", sprintf("%s\n", line));
                        break;
                }
                skill = arg[0];
                arg -= ({ arg[0] });
                if( file_size(SKILL_D(skill) + ".c") < 0 )
                {
                        log_file("static/skill", sprintf("%s\n", line));
                        break;
                }

                attack = atoi(arg[ATTACK]);
                dodge = atoi(arg[DODGE]);
                parry = atoi(arg[PARRY]);
                damage = atoi(arg[DAMAGE]);
                force = atoi(arg[FORCE2]);
                difficult = atoi(arg[DIFFICULT]);
                rank = arg[RANK];
                attribute = arg[ATTRIBUTE];

                skl = ({ attack, dodge, parry, damage, force, difficult, rank, attribute, 0 });

                if( ! mapp(all_skills) || sizeof(all_skills) < 1 )
                        all_skills = allocate_mapping(0);
                all_skills[skill] = skl;

                initial_skills[skill] = skl;
        }
}

void load_skillmix()
{
        string file, num, mark;
        mapping temp_stats;
        class mix temp;

        file = read_file(SKILLMIX_FILE);
        if( !stringp(file) ) return;

        file = replace_string(file, "\r", "");
        all_mixs = ({ });

        while ( sscanf(file, "%*s<S%s>%s</S%s>%s", num, mark, num, file) > 3 )
        {
                temp = new(class mix);
                temp_stats = trans_data(mark);
                temp->name = temp_stats["name"];
                temp->dodge = temp_stats["dodge"];
                temp->parry = temp_stats["parry"];
                temp->force = temp_stats["force"];
                temp->need  = temp_stats["need"];
                temp->stats = temp_stats["stats"];

                all_mixs += ({ temp });
        }
}

class mix find_skillmix(object me)
{
        class mix temp;
        int i, n;
        mapping map;

        temp = new(class mix);

        if (! all_mixs || ! (n=sizeof(all_mixs)))
                return temp;

        map = me->query_skill_map();
        if (! mapp(map) || sizeof(map) == 0)
                return temp;

        if (undefinedp(map["dodge"]) ||
            undefinedp(map["parry"]) ||
            undefinedp(map["force"]))
                return temp;

        temp->dodge = map["dodge"];
        temp->parry = map["parry"];
        temp->force = map["force"];

        for (i=0; i<sizeof(all_mixs); i++)
        {
                if (all_mixs[i]->dodge == temp->dodge &&
                    all_mixs[i]->parry == temp->parry &&
                    all_mixs[i]->force == temp->force)
                {
                        temp->name  = all_mixs[i]->name;
                        temp->need  = all_mixs[i]->need;
                        temp->stats = all_mixs[i]->stats;
                        break;
                }
        }
        return temp;
}

public string skillmix_stats(object me)
{
        class mix temp;
        mapping stats, need;
        int i;
        string *keys_stats, *keys_need;
        string msg, str;
        int len = 0;

        msg = "";

        temp = find_skillmix(me);

        if( !temp->stats )
                return msg;


        msg += "\n\n\n\n\n\n";
        msg += sprintf(NOR HIW "┏--------------------┓\n" NOR);
        msg += sprintf(NOR HIW "┃轻功->%-14s" NOR HIW "┃\n" NOR, to_chinese(temp->dodge));
        msg += sprintf(NOR HIW "┃招架->%-14s" NOR HIW "┃\n" NOR, to_chinese(temp->parry));
        msg += sprintf(NOR HIW "┃内功->%-14s" NOR HIW "┃\n" NOR, to_chinese(temp->force));

        need = temp->need;
        keys_need = keys(need);
        for (i=0;i<sizeof(keys_need);i++)
                msg += sprintf(NOR HIW "┃其他->%-14s" NOR HIW "┃\n" NOR,
                               need[keys_need[i]] + to_chinese(keys_need[i]));

        msg += sprintf(NOR HIW "┗--------------------┛\n" NOR);
        msg += sprintf(" %-22s\n" NOR, trans_color(temp->name, 3));
        msg += sprintf(NOR HIC "┏--------------------┓" NOR "\n" );

        stats = temp->stats;
        keys_stats = keys(stats);
        for (i=0;i<sizeof(keys_stats);i++)
        {
                str = EQUIPMENT_D->chinese(keys_stats[i], stats[keys_stats[i]]);
#ifndef LONELY_IMPROVED
                len = color_len(str);
#endif
                msg += sprintf(NOR HIC "┃" NOR "%-" + (20 + len) + "s" NOR HIC "┃" NOR "\n", str);
        }
        msg += sprintf(NOR HIC "┗--------------------┛" NOR "\n");

        return msg;
}

void load_dazhaomix()
{
        string file, num, mark;
        mapping temp_stats;
        class dazhaomix temp;

        file = read_file(DAZHAOMIX_FILE);
        if( !stringp(file) ) return;

        file = replace_string(file, "\r", "");
        all_dazhaomixs = ({ });

        while ( sscanf(file, "%*s<S%s>%s</S%s>%s", num, mark, num, file) > 3 )
        {
                temp = new(class dazhaomix);
                temp_stats = trans_data(mark);
                temp->name = temp_stats["name"];
                temp->p1 = temp_stats["p1"];
                temp->p2 = temp_stats["p2"];
                temp->p3 = temp_stats["p3"];
                temp->p4 = temp_stats["p4"];
                temp->need  = temp_stats["need"];
                temp->stats = temp_stats["stats"];
                temp->func = temp_stats["func"];

                all_dazhaomixs += ({ temp });
        }
}

class dazhaomix find_dazhaomix(object me)
{
        class dazhaomix temp;
        int i, n;
        string *apply;

        temp = new(class dazhaomix);

        if (! all_dazhaomixs || ! (n=sizeof(all_dazhaomixs)))
                return temp;

        apply = query_temp("last_perform", me);

        if( (n = sizeof(apply)) < 2 ) return temp;

        temp->p1 = apply[<1];
        temp->p2 = apply[<2];
        if( n > 2 ) temp->p3 = apply[<3];
        if( n > 3 ) temp->p4 = apply[<4];

        for (i=0; i<sizeof(all_dazhaomixs); i++)
        {
                if( all_dazhaomixs[i]->p1 == temp->p1 &&
                    all_dazhaomixs[i]->p2 == temp->p2 &&
                    all_dazhaomixs[i]->p3 == temp->p3 &&
                    all_dazhaomixs[i]->p4 == temp->p4 )
                {
                        temp->name  = all_dazhaomixs[i]->name;
                        temp->need  = all_dazhaomixs[i]->need;
                        temp->stats = all_dazhaomixs[i]->stats;
                        temp->func  = all_dazhaomixs[i]->func;
                        break;
                }
        }
        return temp;
}

void manage_skill()
{
        int t;
        int last;
        int user, users, score, scores, effect, effect2;
        string *value;
        string *record;
        string *sname, *ids;
        string skill, rank, attribute;
        int attack, dodge, parry, damage, force, difficult;

        t = time();
        last = query("last_check");
        if( (t / 86400) != (last / 86400) )
        {
                sname = keys(initial_skills);
                users = 0;
                scores = 0;

                foreach( skill in sname )
                {
                        reset_eval_cost();
                        if( !query(skill) )
                        {
                                if( !undefinedp(all_record[skill]) )
                                        map_delete(all_record, skill);
                                continue;
                        }

                        ids = keys(query(skill));
                        user = sizeof(ids);
                        users += user;
                        score = 0;
                        foreach(string id in ids)
                                score += query(skill + "/" + id);
                        scores += score;

                        record = ({ user, score });

                        all_record[skill] = record;

                }
                DEBUG_CHANNEL(sprintf("scores is %d, users is %d.\n", scores, users));

                if( !rdc_skills ) rdc_skills = ([]);
                if( !add_skills ) add_skills = ([]);

                foreach( skill in sname )
                {
                        reset_eval_cost();
                        if( undefinedp(all_record[skill]) )
                        {
                                //if( !undefinedp(all_skills[skill]) )
                                //        all_skills[skill] = initial_skills[skill];
                                continue;
                        }
                        if( !scores || ! users || !all_record[skill][1] ||
                            !all_record[skill][0] )
                                continue;

                        effect = TO_EFFECT(scores, users, all_record[skill][1], all_record[skill][0]);
                        if( all_record[skill][0] < 2 ) effect += 5;
                        else if( all_record[skill][0] < 3 ) effect += 3;
                        else if( all_record[skill][0] < 4 ) effect += 1;
                        if( effect > 50 ) effect = 50;
                        if( effect < -50 ) effect = -50;

                        if( query("create/" + skill) )
                                effect += 5;

                        if( effect < 0 && (
                            all_skills[skill][ATTRIBUTE] == "shaolin" ||
                            all_skills[skill][ATTRIBUTE] == "wudang" ||
                            all_skills[skill][ATTRIBUTE] == "public") )
                                effect = 0;

                        all_record[skill] += ({ effect });

                        //DEBUG_CHANNEL(sprintf("%O\n", all_skills[skill]));
                        if( sizeof(all_skills[skill]) < 9 ) effect2 = 0;
                        else effect2 = all_skills[skill][EFFECT];
                        if( effect == effect2 ) continue; // 没有变化

                        effect2 = effect - effect2;

                        attack = all_skills[skill][ATTACK] ?
                                 all_skills[skill][ATTACK] + effect2 : 0;
                        damage = all_skills[skill][DAMAGE] ?
                                 all_skills[skill][DAMAGE] + effect2 : 0;
                        dodge = all_skills[skill][DODGE] ?
                                all_skills[skill][DODGE] + effect2 : 0;
                        parry = all_skills[skill][PARRY] ?
                                all_skills[skill][PARRY] + effect2 : 0;
                        force = all_skills[skill][FORCE2] ?
                                all_skills[skill][FORCE2] + effect2 : 0;
                        difficult = all_skills[skill][DIFFICULT];
                        rank = all_skills[skill][RANK];
                        attribute = all_skills[skill][ATTRIBUTE];

                        value = ({ attack, dodge, parry, damage, force, difficult, rank, attribute, effect });

                        if( effect2 < 0  )
                                rdc_skills[skill] = copy(value);
                        else
                                add_skills[skill] = copy(value);

                        all_skills[skill] = copy(value);
                }
        }
        set("last_check", t);
        save();
}

int sort_skill(string f1, string f2, int n)
{
        return all_skills[f2][n] - all_skills[f1][n];
}

varargs void query_skill_power(object me, string arg)
{
        string str1, str2, msg;
        string *skl;
        string *sname;
        int flag1, flag2, flag3, flag4;
        int i, delta;
        mixed n;

        msg = WHT "目前江湖上所有武功各种参数值如下\n\n" NOR;
        msg += "----------------------------------------------------------------------------------\n";
        msg += BBLU HIW "技能名称                      命中  躲闪  招架  伤害  内功  难度  级别  门派  调整\n" NOR;
        msg += "----------------------------------------------------------------------------------\n";

        if( stringp(arg) && ! undefinedp(all_skills[arg]) )
        {
                n = 0;
                sname = ({ arg });
        }
        else
        {
                flag1 = 0;
                flag2 = 0;
                flag3 = 0;
                flag4 = 0;

                if( !arg ) n = 0;
                else
                {
                        switch(arg)
                        {
                        case "attack"   :
                        case "攻击"     : n = 0; break;
                        case "dodge"    :
                        case "躲闪"     : n = 1; break;
                        case "parry"    :
                        case "招架"     : n = 2; break;
                        case "damage"   :
                        case "伤害"     : n = 3; break;
                        case "force"    :
                        case "内功"     : n = 4; break;
                        case "difficult":
                        case "难度"     : n = 5; break;
                        case "ultimate" :
                        case "expert"   :
                        case "advance"  :
                        case "normal"   : n = 0; flag1 = 1; break;
                        case "public"   :
                        case "shaolin"  :
                        case "wudang"   :
                        case "gaibang"  :
                        case "quanzhen" :
                        case "huashan"  :
                        case "duan"     :
                        case "murong"   :
                        case "xueshan"  :
                        case "lingjiu"  :
                        case "emei"     :
                        case "taohua"   :
                        case "shenlong" :
                        case "gumu"     :
                        case "xingxiu"  :
                        case "xiaoyao"  :
                        case "xuedao"   :
                        case "ouyang"   :
                        case "hu"       :
                        case "mojiao"   :
                        case "mingjiao" :
                        case "tang"     :
                        case "riyue"    :
                        case "taishan"  :
                        case "songshan" :
                        case "hengshan" :
                        case "henshan"  :
                        case "qingcheng":
                        case "lingxiao" :
                        case "tiezhang" :
                        case "honghua"  :
                        case "yunlong"  :
                        case "wudu"     :
                        case "kunlun"   :
                        case "private"  : n = 0; flag2 = 1; break;
                        case "family"   : n = 0; flag3 = 1; break;
                        default         : n = 0; flag4 = 1; break;
                        }
                }
                sname = keys(all_skills) - ({ 0 });
                if( flag1 )
                        sname = filter_array(sname, (: $(all_skills)[$1][RANK] == $(arg) :));
                if( flag2 )
                        sname = filter_array(sname, (: $(all_skills)[$1][ATTRIBUTE] == $(arg) :));
                if( flag3 )
                        sname = filter_array(sname, (: $(all_skills)[$1][ATTRIBUTE] != "public" &&
                                                       $(all_skills)[$1][ATTRIBUTE] != "private" :));
                if( flag4 )
                        sname = filter_array(sname, (: SKILL_D($1)->valid_enable($(arg)) :));
        }
        sname = sort_array(sname, (: sort_skill :), n);
        for( i = 0; i < sizeof(sname); i++ )
        {
                skl = all_skills[sname[i]];

                if( !undefinedp(all_record[sname[i]]) )
                        delta = all_record[sname[i]][2];
                else
                        delta = 0;

                if( skl[RANK] == "ultimate" )
                        str1 = "终极";
                else
                if( skl[RANK] == "expert" )
                        str1 = "超级";
                else
                if( skl[RANK] == "advance" )
                        str1 = "高级";
                else
                        str1 = "普通";

                if( skl[ATTRIBUTE] == "public" )
                        str2 = "公共";
                else
                if( skl[ATTRIBUTE] == "private" )
                        str2 = "自创";
                else
                        str2 = family_name[skl[ATTRIBUTE]];

                msg += sprintf( HIC "%-30s" NOR, to_chinese(sname[i]) + "(" + sname[i] + ")" );
                msg += sprintf( HIC "%-6d%-6d%-6d%-6d%-6d%-6d" HIY "%-6s" HIM "%-6s" NOR,
                                skl[ATTACK], skl[DODGE], skl[PARRY], skl[DAMAGE],
                                skl[FORCE2], skl[DIFFICULT], str1, str2 );

                msg += sprintf("(%s%2d%s)\n",
                                (delta > 0) ? HIY "+" :
                                (delta < 0) ? HIR "-" : WHT "+",
                                 abs(delta), NOR);
        }
        msg += "----------------------------------------------------------------------------------\n";
        me->start_more(msg);
}

mixed skill_query_power(string skill)
{
        if( !skill ) return 0;
        if( !undefinedp(all_skills[skill]) )
                return all_skills[skill];
        else
                return 0;
}

int query_skill_difficult(string skill)
{
        if( !undefinedp(all_skills[skill]) )
                return all_skills[skill][DIFFICULT];
        else
                return 0;
}

int query_neili_improve(string skill, int level)
{
        int improve;

        if( !undefinedp(all_skills[skill]) )
                improve = all_skills[skill][FORCE2];
        else
                improve = 50;

        return level/10*level/10*improve/20;
}

int enforce_power(object me, int enforce)
{
        int value, damage, scale;
        int max_enforce;
        string map_skill;
        string rank;

        if( !objectp(me) ) return 0;

        if( !stringp(map_skill = me->query_skill_mapped("force")) )
                return 0;

        if( !undefinedp(all_skills[map_skill]) )
        {
                value = all_skills[map_skill][FORCE2];
                rank = all_skills[map_skill][RANK];

                if( rank == "ultimate" )
                        scale = 12;
                else
                if( rank == "expert" )
                        scale = 16;
                else
                if( rank == "advance" )
                        scale = 18;
        }

        if( !value ) value = 100;
        if( !scale ) scale = 20;

        max_enforce = me->query_skill("force") / 2;
        //if (enforce > max_enforce) enforce = max_enforce;

        damage =(me->query_skill("force", 1) / 2 +
                 me->query_skill(map_skill, 1)) * value / scale *
                 enforce / max_enforce;

        if( me->query_weak() ) damage /= 2;

        damage += random(damage / 5);
        return damage;
}

void add_id_into_skills(object me)
{
        mapping skills;
        string id, sname;
        string *sk;

        if( wizardp(me) ) return;

        id=query("id", me);

        if( !mapp(skills = me->query_skills()) ||
            sizeof(skills) < 1 )
                return;

        sk = keys(skills);

        foreach( sname in sk )
        {
                if( SKILL_D(sname)->type() != "martial" )
                        continue;

                if( undefinedp(initial_skills[sname]) )
                        continue;

                if( !query(sname + "/" + id) && skills[sname] < 1000 )
                        continue;

                if( query(sname + "/" + id) && skills[sname] < 1000 )
                {
                        delete(sname + "/" + id);
                        if( !sizeof(query(sname)) )
                                delete(sname);
                        continue;
                }

                set(sname + "/" + id, skills[sname]);
        }
        save();
}

void remove_id_from_skills(object me)
{
        mapping skills;
        string id, sname;
        string *sk;

        if( wizardp(me) ) return;

        id=query("id", me);

        if( !mapp(skills = me->query_skills()) ||
            sizeof(skills) < 1 )
                return;

        sk = keys(skills);

        foreach( sname in sk )
        {
                   if( file_size(SKILL_D(sname)+".c") < 0 ) continue;
                if( SKILL_D(sname)->type() != "martial" )
                        continue;

                if( SKILL_D(sname)->is_invent_skill() )
                        remove_skill_from_skills(me, sname);

                /*
                if( undefinedp(initial_skills[sname] )
                        continue;
                */

                if( !query(sname + "/" + id) )
                        continue;

                delete(sname + "/" + id);
                if( !sizeof(query(sname)) )
                        delete(sname);
        }

        save();
}

void remove_id_from_abandon(object me, string sname)
{
        if( SKILL_D(sname)->type() != "martial" )
                return;

        if( SKILL_D(sname)->is_invent_skill() )
                remove_skill_from_skills(me, sname);

        if( !query(sname+"/"+query("id", me)) )
                return;

        delete(sname+"/"+query("id", me));
        if( !sizeof(query(sname)) )
                delete(sname);

        save();
}

void change_skill_power(string skill, int n, mixed p)
{
        string *sk;
        int attack, dodge, parry, damage, force, diffi, effect;
        string rank, attr;

        if( undefinedp(all_skills[skill]) )
                return;

        if( n > 8 || n < 0 ) return;

        sk = all_skills[skill];
        sk[n] = p;

        attack = (int)sk[ATTACK];
        dodge  = (int)sk[DODGE];
        parry  = (int)sk[PARRY];
        damage = (int)sk[DAMAGE];
        force  = (int)sk[FORCE2];
        diffi  = (int)sk[DIFFICULT];
        rank   = (string)sk[RANK];
        attr   = (string)sk[ATTRIBUTE];
        effect = (int)sk[EFFECT];

        all_skills[skill] = ({ attack, dodge, parry, damage, force, diffi, rank, attr, effect });

        save();
        return;
}

void upgrade_skill_power(string skill)
{
        string *sk;
        int attack, dodge, parry, damage, force, diffi, effect;
        int is_force_skill, is_dodge_skill, is_parry_skill, is_throwing_skill;
        int is_dodge_skill2;
        string rank, attr;

        if( undefinedp(all_skills[skill]) )
                return;

        sk = all_skills[skill];
        attack = (int)sk[ATTACK];
        dodge  = (int)sk[DODGE];
        parry  = (int)sk[PARRY];
        damage = (int)sk[DAMAGE];
        force  = (int)sk[FORCE2];
        diffi  = (int)sk[DIFFICULT];
        rank   = (string)sk[RANK];
        attr   = (string)sk[ATTRIBUTE];
        effect = (int)sk[EFFECT];

        if( attack >= MAX_POINT && dodge >= MAX_POINT && force >= MAX_POINT &&
            damage >= MAX_POINT && parry >= MAX_POINT )
        {
                DEBUG_CHANNEL(sprintf("%s : attack = %d, dodge = %d, parry = %d, damage = %d, force = %d\n",
                        skill, attack, dodge, parry, damage, force));
                return;
        }

        is_throwing_skill = SKILL_D(skill)->valid_enable("throwing");
        is_force_skill = SKILL_D(skill)->valid_enable("force");
        is_dodge_skill = SKILL_D(skill)->valid_enable("dodge") && (! is_force_skill);
        is_dodge_skill2= SKILL_D(skill)->valid_enable("dodge");
        //is_parry_skill = SKILL_D(skill)->valid_enable("parry") && (! is_force_skill);
        is_parry_skill = SKILL_D(skill)->valid_enable("parry");

        //DEBUG_CHANNEL(sprintf("%s : throwing is %d, force is %d, dodge is %d, dodge2 is %d, parry is %d\n",
                 //       skill, is_throwing_skill, is_force_skill, is_dodge_skill, is_dodge_skill2, is_parry_skill));

        // 特殊招架技能
        if( skill == "qiankun-danuoyi" || skill == "douzhuan-xingyi" || skill == "jingang-buhuaiti" ||
            skill == "moshen-zhenshen" || skill == "jinguan-yusuo" )
        {
                if( parry < MAX_POINT )
                {
                         parry += 1;
                         diffi += 1;
                }
                else
                if( damage < LV1_POINT )
                {
                        damage += 10;
                        diffi  += 1;
                }
                else
                if( damage < LV2_POINT )
                {
                        damage += 5;
                        diffi  += 1;
                }
                else
                if( damage < LV3_POINT )
                {
                        damage += 3;
                        diffi  += 1;
                }
                else
                if( damage < MAX_POINT )
                {
                        damage += 1;
                        diffi  += 1;
                }
                all_skills[skill] = ({ attack, dodge, parry, damage, force, diffi, rank, attr, effect });

                save();
                return;
        }

        // 全能类型技能（四大宗师技能等）
        if( is_force_skill && is_dodge_skill2 && is_parry_skill )
        {
                switch(random(5))
                {
                case 0 :
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV1_POINT )
                        {
                                parry += 10;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV2_POINT )
                        {
                                parry += 5;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV3_POINT )
                        {
                                parry += 3;
                                diffi  += 1;
                        }
                        else
                        if( parry < MAX_POINT )
                        {
                                parry += 1;
                                diffi += 1;
                        }
                        else
                        if( dodge < LV1_POINT )
                        {
                                dodge += 10;
                                diffi  += 1;
                        }
                        else
                        if( dodge < LV2_POINT )
                        {
                                dodge += 5;
                                diffi  += 1;
                        }
                        else
                        if( dodge < LV3_POINT )
                        {
                                dodge += 3;
                                diffi  += 1;
                        }
                        else
                        if( dodge < MAX_POINT )
                        {
                                dodge += 1;
                                diffi += 1;
                        }
                        else
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi += 1;
                        }
                        else
                        if( force < LV1_POINT )
                        {
                                force += 10;
                                diffi  += 1;
                        }
                        else
                        if( force < LV2_POINT )
                        {
                                force += 5;
                                diffi  += 1;
                        }
                        else
                        if( force < LV3_POINT )
                        {
                                force += 3;
                                diffi  += 1;
                        }
                        else
                        if( force < MAX_POINT )
                        {
                                force += 1;
                                diffi += 1;
                        }
                        break;
                case 1 :
                        if( parry < LV1_POINT )
                        {
                                parry += 10;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV2_POINT )
                        {
                                parry += 5;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV3_POINT )
                        {
                                parry += 3;
                                diffi  += 1;
                        }
                        else
                        if( parry < MAX_POINT )
                        {
                                parry += 1;
                                diffi += 1;
                        }
                        else
                        if( dodge < LV1_POINT )
                        {
                                dodge += 10;
                                diffi  += 1;
                        }
                        else
                        if( dodge < LV2_POINT )
                        {
                                dodge += 5;
                                diffi  += 1;
                        }
                        else
                        if( dodge < LV3_POINT )
                        {
                                dodge += 3;
                                diffi  += 1;
                        }
                        else
                        if( dodge < MAX_POINT )
                        {
                                dodge += 1;
                                diffi += 1;
                        }
                        else
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi += 1;
                        }
                        else
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        else
                        if( force < LV1_POINT )
                        {
                                force += 10;
                                diffi  += 1;
                        }
                        else
                        if( force < LV2_POINT )
                        {
                                force += 5;
                                diffi  += 1;
                        }
                        else
                        if( force < LV3_POINT )
                        {
                                force += 3;
                                diffi  += 1;
                        }
                        else
                        if( force < MAX_POINT )
                        {
                                force += 1;
                                diffi += 1;
                        }
                        break;
                case 2 :
                        if( dodge < LV1_POINT )
                        {
                                dodge += 10;
                                diffi  += 1;
                        }
                        else
                        if( dodge < LV2_POINT )
                        {
                                dodge += 5;
                                diffi  += 1;
                        }
                        else
                        if( dodge < LV3_POINT )
                        {
                                dodge += 3;
                                diffi  += 1;
                        }
                        else
                        if( dodge < MAX_POINT )
                        {
                                dodge += 1;
                                diffi += 1;
                        }
                        else
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi += 1;
                        }
                        else
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV1_POINT )
                        {
                                parry += 10;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV2_POINT )
                        {
                                parry += 5;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV3_POINT )
                        {
                                parry += 3;
                                diffi  += 1;
                        }
                        else
                        if( parry < MAX_POINT )
                        {
                                parry += 1;
                                diffi += 1;
                        }
                        else
                        if( force < LV1_POINT )
                        {
                                force += 10;
                                diffi  += 1;
                        }
                        else
                        if( force < LV2_POINT )
                        {
                                force += 5;
                                diffi  += 1;
                        }
                        else
                        if( force < LV3_POINT )
                        {
                                force += 3;
                                diffi  += 1;
                        }
                        else
                        if( force < MAX_POINT )
                        {
                                force += 1;
                                diffi += 1;
                        }
                        break;
                case 3 :
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi += 1;
                        }
                        else
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV1_POINT )
                        {
                                parry += 10;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV2_POINT )
                        {
                                parry += 5;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV3_POINT )
                        {
                                parry += 3;
                                diffi  += 1;
                        }
                        else
                        if( parry < MAX_POINT )
                        {
                                parry += 1;
                                diffi += 1;
                        }
                        else
                        if( dodge < LV1_POINT )
                        {
                                dodge += 10;
                                diffi  += 1;
                        }
                        else
                        if( dodge < LV2_POINT )
                        {
                                dodge += 5;
                                diffi  += 1;
                        }
                        else
                        if( dodge < LV3_POINT )
                        {
                                dodge += 3;
                                diffi  += 1;
                        }
                        else
                        if( dodge < MAX_POINT )
                        {
                                dodge += 1;
                                diffi += 1;
                        }
                        else
                        if( force < LV1_POINT )
                        {
                                force += 10;
                                diffi  += 1;
                        }
                        else
                        if( force < LV2_POINT )
                        {
                                force += 5;
                                diffi  += 1;
                        }
                        else
                        if( force < LV3_POINT )
                        {
                                force += 3;
                                diffi  += 1;
                        }
                        else
                        if( force < MAX_POINT )
                        {
                                force += 1;
                                diffi += 1;
                        }
                        break;
                default :
                        if( force < LV1_POINT )
                        {
                                force += 10;
                                diffi  += 1;
                        }
                        else
                        if( force < LV2_POINT )
                        {
                                force += 5;
                                diffi  += 1;
                        }
                        else
                        if( force < LV3_POINT )
                        {
                                force += 3;
                                diffi  += 1;
                        }
                        else
                        if( force < MAX_POINT )
                        {
                                force += 1;
                                diffi += 1;
                        }
                        else
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV1_POINT )
                        {
                                parry += 10;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV2_POINT )
                        {
                                parry += 5;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV3_POINT )
                        {
                                parry += 3;
                                diffi  += 1;
                        }
                        else
                        if( parry < MAX_POINT )
                        {
                                parry += 1;
                                diffi += 1;
                        }
                        else
                        if( dodge < LV1_POINT )
                        {
                                dodge += 10;
                                diffi  += 1;
                        }
                        else
                        if( dodge < LV2_POINT )
                        {
                                dodge += 5;
                                diffi  += 1;
                        }
                        else
                        if( dodge < LV3_POINT )
                        {
                                dodge += 3;
                                diffi  += 1;
                        }
                        else
                        if( dodge < MAX_POINT )
                        {
                                dodge += 1;
                                diffi += 1;
                        }
                        else
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi += 1;
                        }
                        break;
                }
                all_skills[skill] = ({ attack, dodge, parry, damage, force, diffi, rank, attr, effect });

                save();
                return;
        }

        // 内功、攻击、招架
        if( is_force_skill && is_parry_skill )
        {
                switch(random(4))
                {
                case 0 :
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV1_POINT )
                        {
                                parry += 10;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV2_POINT )
                        {
                                parry += 5;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV3_POINT )
                        {
                                parry += 3;
                                diffi  += 1;
                        }
                        else
                        if( parry < MAX_POINT )
                        {
                                parry += 1;
                                diffi += 1;
                        }
                        else
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi += 1;
                        }
                        else
                        if( force < LV1_POINT )
                        {
                                force += 10;
                                diffi  += 1;
                        }
                        else
                        if( force < LV2_POINT )
                        {
                                force += 5;
                                diffi  += 1;
                        }
                        else
                        if( force < LV3_POINT )
                        {
                                force += 3;
                                diffi  += 1;
                        }
                        else
                        if( force < MAX_POINT )
                        {
                                force += 1;
                                diffi += 1;
                        }
                        break;
                case 1 :
                        if( parry < LV1_POINT )
                        {
                                parry += 10;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV2_POINT )
                        {
                                parry += 5;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV3_POINT )
                        {
                                parry += 3;
                                diffi  += 1;
                        }
                        else
                        if( parry < MAX_POINT )
                        {
                                parry += 1;
                                diffi += 1;
                        }
                        else
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi += 1;
                        }
                        else
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        else
                        if( force < LV1_POINT )
                        {
                                force += 10;
                                diffi  += 1;
                        }
                        else
                        if( force < LV2_POINT )
                        {
                                force += 5;
                                diffi  += 1;
                        }
                        else
                        if( force < LV3_POINT )
                        {
                                force += 3;
                                diffi  += 1;
                        }
                        else
                        if( force < MAX_POINT )
                        {
                                force += 1;
                                diffi += 1;
                        }
                        break;
                case 2 :
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi += 1;
                        }
                        else
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV1_POINT )
                        {
                                parry += 10;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV2_POINT )
                        {
                                parry += 5;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV3_POINT )
                        {
                                parry += 3;
                                diffi  += 1;
                        }
                        else
                        if( parry < MAX_POINT )
                        {
                                parry += 1;
                                diffi += 1;
                        }
                        else
                        if( force < LV1_POINT )
                        {
                                force += 10;
                                diffi  += 1;
                        }
                        else
                        if( force < LV2_POINT )
                        {
                                force += 5;
                                diffi  += 1;
                        }
                        else
                        if( force < LV3_POINT )
                        {
                                force += 3;
                                diffi  += 1;
                        }
                        else
                        if( force < MAX_POINT )
                        {
                                force += 1;
                                diffi += 1;
                        }
                        break;
                default :
                        if( force < LV1_POINT )
                        {
                                force += 10;
                                diffi  += 1;
                        }
                        else
                        if( force < LV2_POINT )
                        {
                                force += 5;
                                diffi  += 1;
                        }
                        else
                        if( force < LV3_POINT )
                        {
                                force += 3;
                                diffi  += 1;
                        }
                        else
                        if( force < MAX_POINT )
                        {
                                force += 1;
                                diffi += 1;
                        }
                        else
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV1_POINT )
                        {
                                parry += 10;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV2_POINT )
                        {
                                parry += 5;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV3_POINT )
                        {
                                parry += 3;
                                diffi  += 1;
                        }
                        else
                        if( parry < MAX_POINT )
                        {
                                parry += 1;
                                diffi += 1;
                        }
                        else
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi += 1;
                        }
                        break;
                }
                all_skills[skill] = ({ attack, dodge, parry, damage, force, diffi, rank, attr, effect });
                save();
                return;
        }

        // 内功
        if( is_force_skill )
        {
                if( force < LV1_POINT )
                {
                        force += 10;
                        diffi  += 1;
                }
                else
                if( force < LV2_POINT )
                {
                        force += 5;
                        diffi  += 1;
                }
                else
                if( force < LV3_POINT )
                {
                        force += 3;
                        diffi  += 1;
                }
                else
                if( force < MAX_POINT )
                {
                        force += 1;
                        diffi += 1;
                }
                all_skills[skill] = ({ attack, dodge, parry, damage, force, diffi, rank, attr, effect });
                save();
                return;
        }

        // 暗器、招架（tanzhi-shentong）
        if( is_throwing_skill && is_parry_skill )
        {
                switch(random(3))
                {
                case 0 :
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV1_POINT )
                        {
                                parry += 10;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV2_POINT )
                        {
                                parry += 5;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV3_POINT )
                        {
                                parry += 3;
                                diffi  += 1;
                        }
                        else
                        if( parry < MAX_POINT )
                        {
                                parry += 1;
                                diffi += 1;
                        }
                        break;
                case 1 :
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV1_POINT )
                        {
                                parry += 10;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV2_POINT )
                        {
                                parry += 5;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV3_POINT )
                        {
                                parry += 3;
                                diffi  += 1;
                        }
                        else
                        if( parry < MAX_POINT )
                        {
                                parry += 1;
                                diffi += 1;
                        }
                        else
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        break;
                default :
                        if( parry < LV1_POINT )
                        {
                                parry += 10;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV2_POINT )
                        {
                                parry += 5;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV3_POINT )
                        {
                                parry += 3;
                                diffi  += 1;
                        }
                        else
                        if( parry < MAX_POINT )
                        {
                                parry += 1;
                                diffi += 1;
                        }
                        else
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        break;
                }
                all_skills[skill] = ({ attack, dodge, parry, damage, force, diffi, rank, attr, effect });

                save();
                return;
        }

        // 暗器
        if( is_throwing_skill )
        {
                switch(random(2))
                {
                case 0 :
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi  += 1;
                        }
                        break;
                default :
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        break;
                }
                all_skills[skill] = ({ attack, dodge, parry, damage, force, diffi, rank, attr, effect });

                save();
                return;
        }

        // 轻功、招架、攻击（pixie-jian）
        if( is_dodge_skill && is_parry_skill )
        {
                switch(random(4))
                {
                case 0 :
                        if( dodge < LV1_POINT )
                        {
                                dodge += 10;
                                diffi  += 1;
                        }
                        else
                        if( dodge < LV2_POINT )
                        {
                                dodge += 5;
                                diffi  += 1;
                        }
                        else
                        if( dodge < LV3_POINT )
                        {
                                dodge += 3;
                                diffi  += 1;
                        }
                        else
                        if( dodge < MAX_POINT )
                        {
                                dodge += 1;
                                diffi += 1;
                        }
                        else
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV1_POINT )
                        {
                                parry += 10;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV2_POINT )
                        {
                                parry += 5;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV3_POINT )
                        {
                                parry += 3;
                                diffi  += 1;
                        }
                        else
                        if( parry < MAX_POINT )
                        {
                                parry += 1;
                                diffi += 1;
                        }
                        else
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi += 1;
                        }
                        break;
                case 1 :
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV1_POINT )
                        {
                                parry += 10;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV2_POINT )
                        {
                                parry += 5;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV3_POINT )
                        {
                                parry += 3;
                                diffi  += 1;
                        }
                        else
                        if( parry < MAX_POINT )
                        {
                                parry += 1;
                                diffi += 1;
                        }
                        else
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi += 1;
                        }
                        else
                        if( dodge < LV1_POINT )
                        {
                                dodge += 10;
                                diffi  += 1;
                        }
                        else
                        if( dodge < LV2_POINT )
                        {
                                dodge += 5;
                                diffi  += 1;
                        }
                        else
                        if( dodge < LV3_POINT )
                        {
                                dodge += 3;
                                diffi  += 1;
                        }
                        else
                        if( dodge < MAX_POINT )
                        {
                                dodge += 1;
                                diffi += 1;
                        }
                        break;
                case 2 :
                        if( parry < LV1_POINT )
                        {
                                parry += 10;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV2_POINT )
                        {
                                parry += 5;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV3_POINT )
                        {
                                parry += 3;
                                diffi  += 1;
                        }
                        else
                        if( parry < MAX_POINT )
                        {
                                parry += 1;
                                diffi += 1;
                        }
                        else
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi += 1;
                        }
                        else
                        if( dodge < LV1_POINT )
                        {
                                dodge += 10;
                                diffi  += 1;
                        }
                        else
                        if( dodge < LV2_POINT )
                        {
                                dodge += 5;
                                diffi  += 1;
                        }
                        else
                        if( dodge < LV3_POINT )
                        {
                                dodge += 3;
                                diffi  += 1;
                        }
                        else
                        if( dodge < MAX_POINT )
                        {
                                dodge += 1;
                                diffi += 1;
                        }
                        else
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        break;
                default :
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi  += 1;
                        }
                        else
                        if( dodge < LV1_POINT )
                        {
                                dodge += 10;
                                diffi  += 1;
                        }
                        else
                        if( dodge < LV2_POINT )
                        {
                                dodge += 5;
                                diffi  += 1;
                        }
                        else
                        if( dodge < LV3_POINT )
                        {
                                dodge += 3;
                                diffi  += 1;
                        }
                        else
                        if( dodge < MAX_POINT )
                        {
                                dodge += 1;
                                diffi += 1;
                        }
                        else
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV1_POINT )
                        {
                                parry += 10;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV2_POINT )
                        {
                                parry += 5;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV3_POINT )
                        {
                                parry += 3;
                                diffi  += 1;
                        }
                        else
                        if( parry < MAX_POINT )
                        {
                                parry += 1;
                                diffi += 1;
                        }
                        break;
                }
                all_skills[skill] = ({ attack, dodge, parry, damage, 0, diffi, rank, attr, effect });

                save();
                return;
        }

        // 轻功
        if( is_dodge_skill )
        {
                if( dodge < LV1_POINT )
                {
                        dodge += 10;
                        diffi  += 1;
                }
                else
                if( dodge < LV2_POINT )
                {
                        dodge += 5;
                        diffi  += 1;
                }
                else
                if( dodge < LV3_POINT )
                {
                        dodge += 3;
                        diffi  += 1;
                }
                else
                if( dodge < MAX_POINT )
                {
                        dodge += 1;
                        diffi += 1;
                }
                all_skills[skill] = ({ attack, dodge, parry, damage, force, diffi, rank, attr, effect });

                save();
                return;
        }

        // 攻击、招架
        if( is_parry_skill )
        {
                switch(random(3))
                {
                case 0 :
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV1_POINT )
                        {
                                parry += 10;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV2_POINT )
                        {
                                parry += 5;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV3_POINT )
                        {
                                parry += 3;
                                diffi  += 1;
                        }
                        else
                        if( parry < MAX_POINT )
                        {
                                parry += 1;
                                diffi += 1;
                        }
                        else
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi += 1;
                        }
                        break;
                case 1 :
                        if( parry < LV1_POINT )
                        {
                                parry += 10;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV2_POINT )
                        {
                                parry += 5;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV3_POINT )
                        {
                                parry += 3;
                                diffi  += 1;
                        }
                        else
                        if( parry < MAX_POINT )
                        {
                                parry += 1;
                                diffi += 1;
                        }
                        else
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi += 1;
                        }
                        else
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        break;
                default :
                        if( damage < LV1_POINT )
                        {
                                damage += 10;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV2_POINT )
                        {
                                damage += 5;
                                diffi  += 1;
                        }
                        else
                        if( damage < LV3_POINT )
                        {
                                damage += 3;
                                diffi  += 1;
                        }
                        else
                        if( damage < MAX_POINT )
                        {
                                damage += 1;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV1_POINT )
                        {
                                attack += 10;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV2_POINT )
                        {
                                attack += 5;
                                diffi  += 1;
                        }
                        else
                        if( attack < LV3_POINT )
                        {
                                attack += 3;
                                diffi  += 1;
                        }
                        else
                        if( attack < MAX_POINT )
                        {
                                attack += 1;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV1_POINT )
                        {
                                parry += 10;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV2_POINT )
                        {
                                parry += 5;
                                diffi  += 1;
                        }
                        else
                        if( parry < LV3_POINT )
                        {
                                parry += 3;
                                diffi  += 1;
                        }
                        else
                        if( parry < MAX_POINT )
                        {
                                parry += 1;
                                diffi += 1;
                        }
                        break;
                }
                all_skills[skill] = ({ attack, dodge, parry, damage, force, diffi, rank, attr, effect });
                save();
                return;
        }

        all_skills[skill] = ({ attack, dodge, parry, damage, force, diffi, rank, attr, effect });
        save();
        return;
}

void add_skill_into_skills(string sname, mapping p)
{
        string *sk;
        string rank, att;
        int attack, dodge, parry, damage, force, diffi, effect;

        if( SKILL_D(sname)->type() != "martial" )
                return;

        if( undefinedp(all_skills[sname]) )
        {
                if( !undefinedp(p["rank"]) )
                        rank = p["rank"];
                else
                        rank = "expert";

                if( !undefinedp(p["attribute"]) )
                        att = p["attribute"];
                else
                        att = "private";

                if( att == "private" )
                        force = 0;
                else
                if( !undefinedp(p["force"]) )
                        force = p["force"];
                else
                        force = 0;

                if( !undefinedp(p["difficult"]) )
                        diffi = p["difficult"];
                else
                        diffi = 1200;

                if( !undefinedp(p["effect"]) )
                        effect = p["effect"];
                else
                        effect = 0;

                sk = ({ p["attack"], p["dodge"], p["parry"], p["damage"], force,
                        diffi, rank, att, effect });

                all_skills[sname] = sk;

                save();
                return;
        }

        sk = all_skills[sname];
        attack = (int)sk[ATTACK];
        dodge  = (int)sk[DODGE];
        parry  = (int)sk[PARRY];
        damage = (int)sk[DAMAGE];
        force  = (int)sk[FORCE2];
        diffi  = (int)sk[DIFFICULT];
        effect = (int)sk[EFFECT];

        if( !undefinedp(p["attack"]) && p["attack"] > attack )
                attack = p["attack"];
        if( !undefinedp(p["dodge"]) && p["dodge"] > dodge )
                dodge = p["dodge"];
        if( !undefinedp(p["parry"]) && p["parry"] > parry )
                parry = p["parry"];
        if( !undefinedp(p["damage"]) && p["damage"] > damage )
                damage = p["damage"];
        if( !undefinedp(p["force"]) && p["force"] > force )
                force = p["force"];
        if( !undefinedp(p["difficult"]) && p["difficult"] > diffi )
                diffi = p["difficult"];
        if( !undefinedp(p["rank"]) )
                rank = p["rank"];
        else
                rank = sk[RANK];

        all_skills[sname] = ({ attack, dodge, parry, damage, force,
                diffi, rank, sk[ATTRIBUTE], effect });

        save();
}

void remove_skill_from_skills(object me, string sname)
{
        if( file_size(SKILL_D(sname) + ".c") < 0 )
                return;

        if( SKILL_D(sname)->type() != "martial" )
                return;

        if( query(sname+"/"+query("id", me)) )
                delete(sname+"/"+query("id", me));

        if( !sizeof(query(sname)) )
                delete(sname);

        // if( SKILL_D(sname)->is_invent_skill() )
                map_delete(all_skills, sname);

        save();
}

int attack_power(object me, string skill)
{
        int i, value, ap, scale, tmp;
        string map_skill;
        string rank;
//      object ob;
        int delta;

        if( !objectp(me) ) return 0;
/*
        // nt7 取消转世
        ob = query_temp("last_opponent", me);
        if( objectp(ob) && me->is_fighting(ob) )
                ;
        else
                ob = 0;
*/
        if( !stringp(map_skill = me->query_skill_mapped(skill)) )
        {
                ap = me->query_skill(skill, 1) / 2 +
                     me->query_skill("martial-cognize", 1) +
                     query("level", me)*46;

                ap += me->query_all_buff("attack");

                ap = ap * 10;

/*
                if( objectp(ob) )
                        ap += ap *
                              (query("reborn/times", me) - query("reborn/times", ob))*20/100;
*/
                if( /*objectp(ob) && */(tmp = me->query_all_buff("ap_power")) ) {
                        //tmp = tmp * (100 - query("reborm/times", ob)*10)/100;
                        ap += ap * tmp/100;
                }

                // talent 加成
                if( skill == "sword" )
                {
                        delta = ABILITY_D->check_ability(me, "powerup_sword", 2);
                        if( delta ) ap += ap*delta/100;
                }
                else if( skill == "blade" )
                {
                        delta = ABILITY_D->check_ability(me, "powerup_blade", 2);
                        if( delta ) ap += ap*delta/100;
                }
                else if( skill == "unarmed" )
                {
                        delta = ABILITY_D->check_ability(me, "powerup_unarmed", 2);
                        if( delta ) ap += ap*delta/100;
                }
                else if( skill == "throwing" )
                {
                        delta = ABILITY_D->check_ability(me, "powerup_throwing", 2);
                        if( delta ) ap += ap*delta/100;
                }

                if( me->query_weak() ) ap /= 2;
                if( me->query_freeze() ) ap = ap * 2 / 3;
                if( query_temp("use_hubo", me) )
                {
                        // 命中不应该降低
                        // ap = ap * 2/3;
                        delta = ABILITY_D->check_ability(me, "ap_power-hubo");
                        if( delta ) ap += ap*delta/100;
                }

                return ap;
        }

        if( !undefinedp(all_skills[map_skill]) )
        {
                value = all_skills[map_skill][ATTACK];
                rank = all_skills[map_skill][RANK];

                if( rank == "ultimate" )
                        scale = 40;
                else
                if( rank == "expert" )
                        scale = 60;
                else
                if( rank == "advance" )
                        scale = 90;
        }

        if( !value ) value = 100;
        if( !scale ) scale = 100;

        ap =(me->query_skill(skill, 1) / 2 +
             me->query_skill(map_skill, 1)) * value / scale +
             me->query_skill("martial-cognize", 1) +
             query("level", me)*46;

        ap += me->query_all_buff("attack");

        // 提高技能等级的作用
        ap = ap * 10;

/*
        if( objectp(ob) )
                ap += ap *
                      (query("reborn/times", me) - query("reborn/times", ob))*10/100;
*/
        if( /*objectp(ob) && */(tmp = me->query_all_buff("ap_power")) ) {
                //tmp = tmp * (100 - query("reborm/times", ob)*10)/100;
                ap += ap * tmp/100;
        }

        // talent 加成
        if( skill == "sword" )
        {
                delta = ABILITY_D->check_ability(me, "powerup_sword", 2);
                if( delta ) ap += ap*delta/100;
        }
        else if( skill == "blade" )
        {
                delta = ABILITY_D->check_ability(me, "powerup_blade", 2);
                if( delta ) ap += ap*delta/100;
        }
        else if( skill == "unarmed" )
        {
                delta = ABILITY_D->check_ability(me, "powerup_unarmed", 2);
                if( delta ) ap += ap*delta/100;
        }
        else if( skill == "throwing" )
        {
                delta = ABILITY_D->check_ability(me, "powerup_throwing", 2);
                if( delta ) ap += ap*delta/100;
        }

        if( me->query_weak() ) ap /= 2;
        if( me->query_freeze() ) ap = ap * 2 / 3;

        if( query_temp("use_hubo", me) )
        {
               //ap = ap*2/3;
                delta = ABILITY_D->check_ability(me, "ap_power-hubo");
                if( delta ) ap += ap*delta/100;
        }

        for( i = 0; i < sizeof(all_poison); i++ )
                if( me->query_condition(all_poison[i]) )
                {
                        ap = ap * 2 / 3;
                        break;
                }

        return ap;
}

int defense_power(object me, string skill)
{
        int i, value, dp, scale, tmp;
        string map_skill;
        string rank;
//      object ob;
        int delta;

        if( !objectp(me) ) return 0;

/*
        ob = query_temp("last_opponent", me);
        if( objectp(ob) && me->is_fighting(ob) )
                ;
        else
                ob = 0;
*/
        if( !stringp(map_skill = me->query_skill_mapped(skill)) )
        {
                dp = me->query_skill(skill, 1) / 2 +
                     me->query_skill("martial-cognize", 1) +
                     query("level", me)*46;

                dp += me->query_all_buff("defense");

                dp = dp * 10;

                /* 攻击计算时候已经加入转世比较，防御时候就没有必要再次比较
                if( objectp(ob) )
                        dp += dp *
                              (query("reborn/times", me) - query("reborn/times", ob))*20/100;
                */
                if( /*objectp(ob) && */(tmp = me->query_all_buff("dp_power")) ) {
                        //tmp = tmp * (100 - query("reborm/times", ob)*10)/100;
                        dp += dp * tmp/100;
                }

                if( me->query_weak() ) dp /= 2;
                if( me->query_freeze() ) dp /= 10;

                if( me->in_array() ) dp *= 2; // 阵法

                return dp;
        }

        switch( skill )
        {
        case "parry" :
                if( !undefinedp(all_skills[map_skill]) )
                        value = all_skills[map_skill][PARRY];
                break;
        case "dodge" :
                if( !undefinedp(all_skills[map_skill]) )
                        value = all_skills[map_skill][DODGE];
                break;
        case "force" :
                if( !undefinedp(all_skills[map_skill]) )
                        value = all_skills[map_skill][FORCE2];
                break;
        default:
                break;
        }

        if( !undefinedp(all_skills[map_skill]) )
        {
                rank = all_skills[map_skill][RANK];

                if( rank == "ultimate" )
                        scale = 40;
                else
                if( rank == "expert" )
                        scale = 60;
                else
                if( rank == "advance" )
                        scale = 90;
        }

        if( !value ) value = 100;
        if( !scale ) scale = 100;

        dp =(me->query_skill(skill, 1) / 2 +
             me->query_skill(map_skill, 1)) * value / scale +
             me->query_skill("martial-cognize", 1) +
             query("level", me)*46;

        dp += me->query_all_buff("defense");

        dp = dp * 10;

        /* 攻击计算时候已经加入转世比较，防御时候就没有必要再次比较
        if( objectp(ob) )
                dp += dp *
                      (query("reborn/times", me) - query("reborn/times", ob))*20/100;
        */

        if( /*objectp(ob) && */(tmp = me->query_all_buff("dp_power")) ) {
                //tmp = tmp * (100 - query("reborm/times", ob)*10)/100;
                dp += dp * tmp/100;
        }

        // 门派AB加防御能力
        delta = ABILITY_D->check_ability(me, "dodgeup-"+map_skill);
        if( !delta ) delta = ABILITY_D->check_ability(me, "parryup-"+map_skill);
        if(  delta ) dp += dp*delta/100;

        if( me->query_weak() ) dp /= 2;
        if( me->query_freeze() ) dp /= 10; // 冰冻状况

        if( me->in_array() ) dp *= 2; // 阵法

        for( i = 0; i < sizeof(all_poison); i++ )
                if( me->query_condition(all_poison[i]) )
                {
                        dp = dp * 2 / 3;
                        break;
                }

        return dp;
}

int damage_power(object me, string skill)
{
        int i, value, damage, scale, tmp;
        string map_skill;
        string rank;
//      object ob;
        int delta;

        if( !objectp(me) ) return 0;
/*
        if( objectp(ob) && me->is_fighting(ob) )
                ;
        else
                ob = 0;
*/
        if( !stringp(map_skill = me->query_skill_mapped(skill)) )
        {
                damage = me->query_skill(skill, 1) / 2 +
                         me->query_skill("martial-cognize", 1) +
                         query("level", me)*46;
/*
                if( objectp(ob) )
                        damage += damage *
                                  (query("reborn/times", me) - query("reborn/times", ob))*20/100;
*/
                if( /*objectp(ob) && */(tmp = me->query_all_buff("da_power")) ) {
                        //tmp = tmp * (100 - query("reborm/times", ob)*10)/100;
                        damage += damage * tmp/100;
                }

                // talent 加成
                if( skill == "sword" )
                {
                        delta = ABILITY_D->check_ability(me, "powerup_sword", 2);
                        if( delta ) damage += damage*delta/100;
                }
                else if( skill == "blade" )
                {
                        delta = ABILITY_D->check_ability(me, "powerup_blade", 2);
                        if( delta ) damage += damage*delta/100;
                }
                else if( skill == "unarmed" )
                {
                        delta = ABILITY_D->check_ability(me, "powerup_unarmed", 2);
                        if( delta ) damage += damage*delta/100;
                }
                else if( skill == "throwing" )
                {
                        delta = ABILITY_D->check_ability(me, "powerup_throwing", 2);
                        if( delta ) damage += damage*delta/100;
                }

                if( me->query_weak() ) damage /= 2;
                if( me->query_freeze() ) damage = damage * 2 / 3;

                if( query_temp("use_hubo", me))damage=damage*2/3;

                damage += random(damage / 5);
                return damage;
        }

        if( !undefinedp(all_skills[map_skill]) )
        {
                value = all_skills[map_skill][DAMAGE];
                rank = all_skills[map_skill][RANK];

                if( rank == "ultimate" )
                        scale = 40;
                else
                if( rank == "expert" )
                        scale = 60;
                else
                if( rank == "advance" )
                        scale = 90;
        }

        if( !value ) value = 100;
        if( !scale ) scale = 100;

        damage =(me->query_skill(skill, 1) / 2 +
                 me->query_skill(map_skill, 1)) * value / scale +
                 me->query_skill("martial-cognize", 1) +
                 query("level", me)*46;
/*
        if( objectp(ob) )
                damage += damage *
                          (query("reborn/times", me) - query("reborn/times", ob))*20/100;
*/
        if( /*objectp(ob) && */(tmp = me->query_all_buff("da_power")) ) {
                //tmp = tmp * (100 - query("reborm/times", ob)*10)/100;
                damage += damage * tmp/100;
        }

        // talent 加成
        if( skill == "sword" )
        {
                delta = ABILITY_D->check_ability(me, "powerup_sword", 2);
                if( delta ) damage += damage*delta/100;
        }
        else if( skill == "blade" )
        {
                delta = ABILITY_D->check_ability(me, "powerup_blade", 2);
                if( delta ) damage += damage*delta/100;
        }
        else if( skill == "unarmed" )
        {
                delta = ABILITY_D->check_ability(me, "powerup_unarmed", 2);
                if( delta ) damage += damage*delta/100;
        }
        else if( skill == "throwing" )
        {
                delta = ABILITY_D->check_ability(me, "powerup_throwing", 2);
                if( delta ) damage += damage*delta/100;
        }

        if( me->query_weak() ) damage /= 2;
        if( me->query_freeze() ) damage = damage * 2 / 3;

        if( query_temp("use_hubo", me) )
                damage = damage * 2 / 3;

        for( i = 0; i < sizeof(all_poison); i++ )
                if( me->query_condition(all_poison[i]) )
                {
                        damage = damage * 2 / 3;
                        break;
                }

        return damage;
}

mapping trans_data(string mark)
{
        int     i;
        mixed   temp_value;
        string  temp_str;
        string  *temp_arr, *temp_val;
        string  temp_key, key;
        mapping temp_stats;
        mapping temp_map;

        temp_stats = ([ ]);
        // 开始解析
        while (sscanf(mark, "%*s<%s>%s</%s>%s", key, temp_str, key, mark) > 3)
        {
                temp_map = ([ ]);
                temp_arr = explode(temp_str, "\n");
                if (sizeof(temp_arr) < 2)
                {
                        if (atoi(temp_str))
                                temp_stats[key] = atoi(temp_str);
                        else
                                temp_stats[key] = temp_str;

                } else
                {
                        for (i = 0; i < sizeof(temp_arr); i++)
                        {
                                temp_arr[i] = replace_string(temp_arr[i], " ", "");
                                if (sscanf(temp_arr[i], "%s:%d", temp_key, temp_value) != 2)
                                        sscanf(temp_arr[i], "%s:%s", temp_key, temp_value);

                                // 解析VALUE
                                if (stringp(temp_value) && strsrch(temp_value, '/') != -1)
                                {
                                        temp_val = explode(temp_value, "/");
                                        temp_value = ({ });
                                        for (i = 0; i <sizeof(temp_val); i++)
                                                if (atoi(temp_val[i]))
                                                        temp_value += atoi(temp_val[i]);
                                                else
                                                        temp_value += temp_val[i];
                                }
                                // 解析KEY
                                if (stringp(temp_key) && strsrch(temp_key, '/') != -1)
                                        _set( temp_map, explode(temp_key, "/"), temp_value );
                                else
                                        temp_map[temp_key] = temp_value;
                        }
                        temp_stats[key] = temp_map;
                }
        }

        if ( !undefinedp(temp_stats["name"]) )
                temp_stats["name"] = trans_color(temp_stats["name"], 3);

        if ( !undefinedp(temp_stats["long"]) )
                temp_stats["long"] += "\n";

        return temp_stats;
}

void disable_skillmix(object me)
{
//      mapping stats,applied_prop;
//      string *apply;
//      int i,flag;

        if( !query("skillmix", me) )
                return;
        /*
        stats=copy(query("skillmix", me));
        apply = keys(stats);
        if ( sizeof(apply) )
        {
                if( !mapp(query_temp("apply", me)) )
                        applied_prop = ([]);
                else
                        applied_prop=query_temp("apply", me);
                for(i = 0; i<sizeof(apply); i++)
                {
                        if (apply[i] == "int" || apply[i] == "str" ||
                            apply[i] == "con" || apply[i] == "add_skill" ||
                            apply[i] == "max_qi" || apply[i] == "max_jing")
                                flag = 1;

                        applied_prop[apply[i]] -= stats[apply[i]];
                }

                set_temp("apply", applied_prop, me);
                if (flag) CHAR_D->setup_char(me);
        }
        */
        delete("skillmix", me);
        me->reset_buff_cache();
}

varargs void enable_skillmix(object me, mapping stats, mapping need)
{
//      mapping applied_prop;
        string *apply;
        int i/*, flag*/;

        if (! mapp(stats) || ! sizeof(stats))
                return;

        if (mapp(need) && sizeof(need))
        {
                apply = keys(need);
                for(i = 0; i<sizeof(apply); i++)
                        if (me->query_skill(apply[i], 1) < need[apply[i]])
                                return;
        }
        /*
        apply = keys(stats);
        if ( sizeof(apply) )
        {
                if( !mapp(query_temp("apply", me)) )
                        applied_prop = ([]);
                else
                        applied_prop=query_temp("apply", me);
                for(i = 0; i<sizeof(apply); i++)
                {
                        if (apply[i] == "int" || apply[i] == "str" ||
                            apply[i] == "con" || apply[i] == "add_skill" ||
                            apply[i] == "max_qi" || apply[i] == "max_jing")
                                flag = 1;

                        if( undefinedp(applied_prop[apply[i]]) )
                                applied_prop[apply[i]] = stats[apply[i]];
                        else
                                applied_prop[apply[i]] += stats[apply[i]];
                }
                set_temp("apply", applied_prop, me);
                if (flag) CHAR_D->setup_char(me);
        }
        */

        set("skillmix", stats, me);
        me->reset_buff_cache();
}

public void check_skillmix(object me, int flag)
{
        class mix temp;
        mixed stats;

        if (! flag)
        {
                disable_skillmix(me);
                return;
        }
        temp = find_skillmix(me);
        if (flag)
        {
                if (! temp->stats)
                {
                       disable_skillmix(me);
                       return;
                }
        }
        if (flag == 2)
        {
                if( !query("skillmix", me) )
                {
                       enable_skillmix(me, temp->stats, temp->need);
                       return;
                }
                stats=query("skillmix", me);
                if (! mapping_eqv(temp->stats, stats))
                {
                        disable_skillmix(me);
                        enable_skillmix(me, temp->stats, temp->need);
                }
        }
}

void broadcast_news()
{
        object *obs, ob;
        string *key;
        string skill;
//      mixed value;

        if( !rdc_skills ) rdc_skills = ([]);
        if( !add_skills ) add_skills = ([]);

        if( sizeof(rdc_skills) > 0 )
        {
                key = keys(rdc_skills);
                skill = key[random(sizeof(key))];
                // manage_skill 处理数值
                //value = copy(rdc_skills[skill]);
                //all_skills[skill] = value;
                map_delete(rdc_skills, skill);

                obs = filter_array(users(), (: ultrap($1) &&
                                   $1->query_skill($(skill), 1) > 400 &&
                                   query("doing", $1):));
                if( sizeof(obs) )
                {
                        ob = obs[random(sizeof(obs))];
                        ob->add_skill(skill, 10 + random(6));
                        tell_object(ob, HIM "你脑中突然灵光一闪，你对" +
                                        to_chinese(skill) + "有了更深的领悟！\n" NOR);
                }
                else
                        ob = 0;

                CHANNEL_D->channel_broadcast("news",
                                        "武学大宗师" + (ob ? ob->name(1) : "无名老人") + "闭关修行研究" +
                                        to_chinese(skill) + "，终于悟出其破解之术，并广为流传。");
        }

        if( sizeof(add_skills) > 0 )
        {
                key = keys(add_skills);
                skill = key[random(sizeof(key))];
                // manage_skill 处理数值
                //value = copy(add_skills[skill]);
                //all_skills[skill] = value;
                map_delete(add_skills, skill);

                obs = filter_array(users(), (: ultrap($1) &&
                                   $1->query_skill($(skill), 1) > 400 &&
                                   query("doing", $1):));
                if( sizeof(obs) )
                {
                        ob = obs[random(sizeof(obs))];
                        ob->add_skill(skill, 10 + random(6));
                        tell_object(ob, HIM "你脑中突然灵光一闪，你对" +
                                        to_chinese(skill) + "有了更深的领悟！\n" NOR);
                }
                else
                        ob = 0;

                CHANNEL_D->channel_broadcast("news",
                                        "武学大宗师" + (ob ? ob->name(1) : "无名老人") + "闭关修行研究" +
                                        to_chinese(skill) + "，终于完善其破绽之处，并广为流传。");
        }
        save();
}

void remove()
{
        save();
}

public void mud_shutdown()
{
        save();
}

public void check_dazhaomix(object me)
{
        class dazhaomix temp;
        mapping need;
        string *apply;
        mixed stats;
        int i, func;

        temp = find_dazhaomix(me);
        need = temp->need;

        if( mapp(need) && sizeof(need) )
        {
                apply = keys(need);
                for(i = 0; i<sizeof(apply); i++)
                        if (me->query_skill(apply[i], 1) < need[apply[i]])
                                return;
        }
        stats = temp->stats;
        if( mapp(need) && sizeof(need) )
        {
                apply = keys(need);
                for(i = 0; i<sizeof(apply); i++)
                        set_temp("bonus/"+apply[i], need[apply[i]], me);
        }
        if( temp->func )
        {
                func = temp->func;
                set_temp("bonus/func", func, me);
        }
}

string do_dazhaofunc(int flag)
{
}

string do_dazhaomix(object me, object target, int damage)
{
        int func;
        string msg = "";
        if( func = query_temp("bonus/func", me) )
                msg += do_dazhaofunc(func);

        delete_temp("bonus", me);
        return msg;
}

int valid_perform(object me, string file)
{
        string sskill, pfname;
        string *dirs;

        dirs = explode(file, "/");
        sskill = dirs[2];

        //pfname = dirs[<1][0..<3];
        pfname = dirs[<1];

        if( userp(me) && !wizardp(me) &&
            !SKILL_D(sskill)->is_invent_skill() &&
            !file->is_player_perform() &&
            !query("can_perform/"+sskill+"/"+pfname, me) /*&&
            !me->query_skill("douzhuan-xingyi") &&
            !me->query_skill("qiankun-danuoyi")*/ )
        {
                tell_object(me, "你还没有受过高人指点，无法施展。\n");
                return 0;
        }

        check_dazhaomix(me); // 检查并激活绝招组合特效
        return 1;
}

#define SKI_BLK 100

int skill_summary(object me, string skill, int level)
{
        mapping ski_lst = ([]);
        string ski,msg,file_skill;
        string *ski_term;
        int i, record;
        int file_level;
        int grade;
        msg = "/cmds/skill/skills"->skill_level(SKILL_D(skill)->type(),level);
        ski = sprintf("%s+%d",skill,level);

        record = 0;

        if( wizardp(me) ) return 1;
        if( skill == "zhengqi-jue" || skill == "tianmo-jue" ) return 1;

        // If we are not making to SKI_BLK, just return true
        if( SKILL_D(skill)->type() == "knowledge" )
                grade = SKI_BLK*2;
        else    grade = SKI_BLK;
        if( level%grade ) return 1;

        ski_lst = DB_D->query_data("skill_list");
        if( !mapp(ski_lst) || sizeof(ski_lst) < 1 )
        {
                ski_lst = ([]);
                ski_lst[ski] = 1;
                CHANNEL_D->channel_broadcast(
                        "news", sprintf("%s(%s)的%s已经达到了"+msg+NOR+YEL"的境界（古今武林第一人）。",
                                        query("name", me),query("id", me),to_chinese(skill)));

               /*
                HISTORY_D->add_history("技能等级排名", query("id", me), sprintf("%s %d 级，年龄 %d 排名: 1.\n",
                                        to_chinese(skill), level, query("age", me)));
               */

                record = 1;
        }
        else
        {
                ski_term=keys(ski_lst);
                for( i=0;i<sizeof(ski_term);i++ )
                {
                        sscanf( ski_term[i],"%s+%d",file_skill,file_level );
                        if( skill == file_skill )
                        {
                                if (level>file_level)
                                {
                                        map_delete(ski_lst,ski_term[i]);
                                        ski_lst[ski]=1;
                                        CHANNEL_D->channel_broadcast(
                                                "news",sprintf("%s(%s)的%s已经达到了"+msg+NOR+YEL"的境界（当今武林第一人）。",
                                                                query("name", me),query("id", me),to_chinese(skill)));

                                        /*
                                        HISTORY_D->add_history("技能等级排名", query("id", me), sprintf("%s %d 级，年龄 %d 排名: 1.\n",
                                                                to_chinese(skill), level, query("age", me)));
                                        */
                                        record = 1;
                                }

                                if (level==file_level)
                                {
                                        ski_lst[ski_term[i]] +=1;
                                        CHANNEL_D->channel_broadcast(
                                                "news",sprintf("%s(%s)的%s已经达到了"+msg+NOR+YEL"的境界（当今武林第%s人）。",
                                                                query("name", me),query("id", me),to_chinese(skill), chinese_number(ski_lst[ski_term[i]])));
                                        record = 1;
                                }

                                if (level<file_level)
                                {
                                        CHANNEL_D->channel_broadcast(
                                              "ad",sprintf("%s(%s)"HIK"的%s已经达到了"+msg+NOR+HIK"的境界。",
                                                                query("name", me),query("id", me),to_chinese(skill)));
                                        record = 2;
                                }
                        }
                }
                if (!record)
                {
                        CHANNEL_D->channel_broadcast(
                                "news",sprintf("%s(%s)的%s已经达到了"+msg+NOR+YEL"的境界（自古武林第一人）。",
                                                query("name", me),query("id", me),to_chinese(skill)));
                        ski_lst[ski] = 1;
               /*
                        HISTORY_D->add_history("技能等级排名", query("id", me), sprintf("%s %d 级，年龄 %d 排名: 1.\n",
                                                to_chinese(skill), level, query("age", me)));
               */
                        record = 1;
                }
        }
        DB_D->set_data("skill_list", ski_lst);
        return 1;
}
