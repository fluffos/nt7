// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h> 
inherit __DIR__"normal.c"; 

int clean_up() { return 1;}

mapping valid_types = ([
        "unarmed":      "拳脚",
        "sword":        "剑法",
//        "arrow":        "箭法",
        "axe":          "斧法",
        "blade":        "刀法",
        "staff":        "杖法",
        "hammer":       "锤法",
        "club" :        "棍法",
        "spear":        "枪法",
        "throwing":     "暗器",
        "force":        "内功",
        "parry":        "招架",
        "dodge":        "轻功",
        "magic":        "法术",
        "whip":         "鞭法",
        "dagger":       "短兵",
        "finger":       "指法",
        "hand":         "手法",
        "cuff":         "拳法",
        "claw":         "爪法",
        "strike":       "掌法",
//        "medical":      "医术",
//        "poison":       "毒技",
//        "cooking":      "厨艺",
//        "chuixiao-jifa" : "吹萧",
//        "guzheng-jifa"  : "古筝",
//        "tanqin-jifa"   : "弹琴",
//        "array"         : "阵法",
//        "taoism"        : "道学心法",
]);

int query_yanjiutimes(object me)//获取研究次数，/cmds/skill/research.c
{
        int n, c;
        object where = environment(me);

        c=200+me->query_all_buff("research_times");
        if( query("special_skill/clever", me) ) 
                c += 50;
        // 转世技能增加研究次数
        if( query("special_skill/wisdom", me) )
                c += 800;
        if( query("special_skill/musha", me) )
                c += c * 50 / 100;
        if( me->query_skill("huitong-tianxia", 1) > 500 )
                c += c * 20 / 100 + 10;
        // 奇筋异骨提高研究次数2倍
        if( query("special_skill/qijin", me) )
                c *= 2;
        if( objectp(where) && query("penglai", where) )
                c *= 2;
        if( objectp(where) && query("dongtianfudi", where) )//洞天福地
                c += query("dongtianfudi", where);
        if( n = ACTION_D->query_action("yanjiu_times") )
                c *= n;
                set_temp("dongtianfudi/xiulian/yanjiu_times", c, me);
                return c;
}

int query_lianxitimes(object me)//获取lian次数，/cmds/skill/practice.c
{
        int n, c;
        object where = environment(me);
        c=200+me->query_all_buff("practice_times");
        if( query("special_skill/wisdom", me) )
                c += 500;
        if( objectp(where) && query("dongtianfudi", where) )//洞天福地
                c += query("dongtianfudi", where);
        if( n = ACTION_D->query_action("lianxi_times") )
                c *= n;
                set_temp("dongtianfudi/xiulian/lianxi_times", c, me);
                return c;
}

string query_canyanjiuskills(object me)// enable.c
{
        mapping map;
        string *types, *skill;
        string msg = "";
        string *skyj = ({});
        string *sklx = ({});
        string *sklxb = ({});
        
        int i, modify;
        
                                msg += HIG + "  当前福地加成后，" + sprintf("研究次数:(%d)，", query_yanjiutimes(me)) + sprintf("练习次数:(%d)。\n", query_lianxitimes(me)) + NOR;

                map = me->query_skill_map();
                if (! mapp(map) || sizeof(map) == 0) {
                        return msg + "  但孩儿没有激发(enable)任何特殊武功。\n" + NOR; 
                }

                skill = keys(valid_types);
                msg += HIG + "  激发着的武功:\n" + NOR;
                for (i = 0; i < sizeof(skill); i++)
                {
                        if (undefinedp(map[skill[i]]))
                                continue;

                        if (! me->query_skill(skill[i]))
                                continue;

                        msg += sprintf("  %-20s： %-20s\n" + NOR, 
                                to_chinese(skill[i]) + "(" + skill[i] + ")",  
                                undefinedp(map[skill[i]]) ? "无" : to_chinese(map[skill[i]]) + "(" + map[skill[i]] + ")");
                        skyj += ({skill[i]});
                        if ( !undefinedp(map[skill[i]]) && 
                                SKILL_D(map[skill[i]])->valid_learn(me) 
                                ) {
                                sklx += ({map[skill[i]]});
                                sklxb += ({skill[i]});
                                }
                }
                set_temp("dongtianfudi/xiulian/yanjiu", skyj, me);
                set_temp("dongtianfudi/xiulian/lianxi", sklxb, me);
                i = sizeof(skyj);
                if (i) msg += HIG + "  大概能研究的:\n  " + NOR;
                while(i--) {
                        msg += to_chinese(skyj[i]);
                        if (i) {
                                if (i % 5 == 0) msg +="\n  ";
                                else msg += "、";
                        }
                }
                i = sizeof(sklx);
                if (i) msg += HIG + "\n  大概能练习的:\n  " + NOR;
                while(i--) {
                        msg += to_chinese(sklx[i]);
                        if (i) {
                                if (i % 5 == 0) msg +="\n  ";
                                else msg += "、";
                        }
                }
                msg += "\n" + NOR;
                //write(msg);
                                set_temp("dongtianfudi/xiulian/start_flag", 1, me);
        return msg;     
}

int do_start_baodu(object me)
{
        mapping my, map;
        string msg;
        int i;
        string sk, *sks;
        //halt
        me->command("halt");
        //恢复气血
        my = me->query_entire_dbase();
        my["jing"]   = my["eff_jing"]   = my["max_jing"]; 
        my["jingli"] = my["eff_jingli"] = my["max_jingli"]; 
        my["qi"]     = my["eff_qi"]     = my["max_qi"]; 
        my["neili"]  = my["max_neili"];
        my["food"]   = me->max_food_capacity();
        my["water"]  = me->max_water_capacity();
        me->clear_condition();
        me->clear_weak();
        //判断停止环境
        if (base_name(environment(me))!=base_name(this_object())) {
                delete_temp("dongtianfudi/xiulian/start_flag", me);
                return 1;
        }
        //研究练习
        sks = query_temp("dongtianfudi/xiulian/yanjiu", me);
        i = sizeof(sks);
        if (i) {
                sk = sks[random(i)];
                if (query_temp("dongtianfudi/xiulian/yanjiu_skill", me)) sk = query_temp("dongtianfudi/xiulian/yanjiu_skill", me);
                else sk = sks[random(i)];
                i = query_temp("dongtianfudi/xiulian/yanjiu_times", me);
                me->command(sprintf("yanjiu %s %d", sk, i));
                msg = sprintf("研究「%s」%s次，", to_chinese(sk), chinese_number(i));
        }
        sks = query_temp("dongtianfudi/xiulian/lianxi", me);
        i = sizeof(sks);
        if (i) {
                sk = sks[random(i)];
                i = query_temp("dongtianfudi/xiulian/lianxi_times", me);
                me->command(sprintf("lian %s %d", sk, i));
                map = me->query_skill_map();
                if (mapp(map) && sizeof(map) && !undefinedp(map[sk])) {
                        msg += sprintf("练习「%s」%s次。", to_chinese(map[sk]), chinese_number(i));
                }
        }
        me->command(sprintf("whisper %s %s", query("parents/father", me), msg));
        me->command(sprintf("whisper %s %s", query("parents/mother", me), msg));
        call_out("do_start_baodu", 1, me);
}

int do_yj(string arg)
{
        int lvl;
        string babyid;
        object baby, me = this_player();
        
        if (!babyid=query("couple/child_id", me))
        {
                tell_object(me, NOR "你确定你有孩子？\n" NOR); 
                return 1;
        }
      baby = present(babyid, this_object());
        if( !baby || !objectp(baby) || base_name(baby)!="/clone/user/baby" )
        {
                tell_object(me, NOR "你的孩子不在这里。\n" NOR); 
                return 1;
        }
        if (!arg || arg=="") {
                tell_object(me, NOR "你想指定孩子去研究什么技能？\n" NOR);
                return 1;
        }
        if (! (lvl = baby->query_skill(arg, 1))) {
                tell_object(me, NOR "你的孩子还不会这技能。\n" NOR);
                return 1;
        }
        if ((string) SKILL_D(arg)->type() == "knowledge") {
                tell_object(me, NOR "这项技能只能通过学习提高。\n" NOR);
                return 1;
        }
        if (lvl < 180) {
                tell_object(me, NOR "你的孩子对这技能的掌握程度不够。\n" NOR);
                return 1;
        }
        set_temp("dongtianfudi/xiulian/yanjiu_skill", arg, baby);
        return 1;
}

void create()
{
        set("short", "鹰咀崖");
        set("long", 
"这里是抱犊山顶巨石上的一块小坪地，周围生长了数棵高大的雪\n"
"松。登高远眺去，四面八方云绕雾锁，旭日金光攒射在整座山崖上，\n"
"宛如人间福地。只见有些武林世家的公子小姐，此时正盘膝坐于各处\n"
"专心修炼。\n"
);
                set("outdoors", "yangzhou");
                set("exits",([ /* sizeof() == 1 */
                        "west" : __DIR__"baodu3",
                ]));

        //set("no_dazuo",1);
        //set("no_kill",1);
        //set("no_fight",1);
        set("no_steal",1);
        set("no_beg",1);         
                set("no_rideto", 1);
                set("no_flyto", 1);
                //set("no_magic", 1); 
        set("no_sleep_room", 1); 
//        set("no_get", 1);
        set("no_user_kill", 1);
        set("no_user_yanjiu", 1);
//        set("max_carry_user" ,5);
//        set("max_carry_exit" ,"out");
                set("dongtianfudi", 3000);
        
        setup();
}

void init()
{
        string msg;
        object obf, obm;
        object me = this_player();
        
        if (playerp(me)) add_action("do_yj", "yj");
        
        if (objectp(me) && 
                me->is_character() &&
                base_name(me)=="/clone/user/baby") {
                if (query_temp("dongtianfudi/xiulian/start_flag", me)) return;//已经进行
                delete_temp("dongtianfudi/xiulian/yanjiu_skill", me);//删除指定研究
                obf = present(query("parents/father", me), this_object());
                obm = present(query("parents/mother", me), this_object());
                if (
                        (!obf || !objectp(obf) || !obf->is_character() || !playerp(obf)) &&
                        (!obm || !objectp(obm) || !obm->is_character() || !playerp(obm))
                        ) return;
                
                msg = query_canyanjiuskills(me);
                if (!query_temp("dongtianfudi/xiulian/start_flag", me)) return;//没有可利用的sk
                
                if (obf && objectp(obf) && obf->is_character() && playerp(obf)) {
                        tell_object(obf, HIG + "\n" + me->name() + "(" + query("id", me) + ")" + HIG + 
                        "悄悄告诉你：\n" + msg + HIG + "  孩儿定当刻苦修炼，决不会辜负爹爹期望。\n   " + HIK + "(要指定研究技能请用<yj skillname>)\n\n" + NOR); 
                }
                if (obm && objectp(obm) && obm->is_character() && playerp(obm)) {
                        tell_object(obm, HIG + "\n" + me->name() + "(" + query("id", me) + ")" + HIG + 
                        "悄悄告诉你：\n" + msg + HIG + "  孩儿定当刻苦修炼，决不会辜负娘亲期望。\n   " + HIK + "(要指定研究技能请用<yj skillname>)\n\n" + NOR); 
                }
                me->command( sprintf("addoil %s", query("id", me)) );
                call_out("do_start_baodu", 10, me);
        }
        else
                return ::init();
                
}


