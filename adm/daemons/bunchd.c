// This program is a part of NITAN MudLIB
// bunchd.c
/*
【帮派荣誉点的功能】
帮派荣誉点是一种消耗点数，仅通过特殊活动获取。通过bunch指令可以随时查
询本帮派的荣誉点数。帮主可通过消耗荣誉点数换取以下特殊功能之一：

帮派荣誉点可以通过 group quest 获得

全帮双倍经验2小时，消耗X点帮派荣誉点。
全帮双倍潜能2小时，消耗X点帮派荣誉点。
全帮双倍体会2小时，消耗X点帮派荣誉点。
全帮研究效率增加20%持续3小时，消耗X点帮派荣誉点。
全帮汲取效率增加20%持续3小时，消耗X点帮派荣誉点。
全帮冥思效率增加20%持续3小时，消耗X点帮派荣誉点。
*/

#include <ansi.h>

// #pragma optimize
// #pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

// 帮派声望最大是10亿
#define MAX_BUNCH_FAME         1000000000

// 每个帮派最多有100个仇人
#define MAX_HATRED_PERSON       100

// 当仇人超过的时候每次移除多少个
#define HATREDP_REMOVED         10
#define BUNCH_HOME              "/data/bunch/"
#define RM_CMD                  "/cmds/wiz/rm"
#define CP_CMD                  "/cmds/wiz/cp"

mapping bunch_fame;
mapping last_bunch_fame;

// area's base_name & short
mapping area_fame;

// 帮派对仇人仇恨度的排序
private int sort_hatred(string id1, string id2, mapping hatred);
public mixed manage_areas();
public void dismiss_bunch(string fname);
public mixed query_all_areas() { return area_fame; }
public int end_bunch_war(string wname, string lname, int gold);
public int war_stop_time(string fname);
public int bunch_is_league(mixed ob1, mixed ob2);
void add_bunch_honors(string bname, int honors);

nosave string *npc_bunch = ({
        "黑白道",
        "修罗门",
        "小刀会",
        "侠义盟",
        "无极帮",
        "紫衫会",
});

nosave string *bad_weather = ({
        "受干旱的影响，$N亏空",
        "由于暴雨袭击，$N收成跌了",
        "$N遭到了倭寇的袭击，被劫",
        "官府加重对$N的征税，$N亏空",
        "疾病在$N肆虐，损失惨重",
        "龙卷风袭卷了$N，结果造成巨大损失",
        "$N发生暴动，人员伤亡惨重，损失",
        "$N突发地震，人员伤亡惨重，花费巨大",
});

nosave mapping citys = ([
        "bj"  : "北京城",
        "yz"  : "扬州城",
        "ca"  : "长安城",
        "cd"  : "成都城",
        "sz"  : "苏州城",
        "hz"  : "杭州城",
        "xy"  : "襄阳城",
        "dl"  : "大理城",
]);

// start
#define BATTLE_TIME             1800
#define BATTLE_JOIN_TIME        300
#define LEAVE_ROOM              "/d/city/wumiao"

int battle_times = 0;
nosave int battle_open_flag = 0;
nosave int battle_start_flag = 0;
nosave int battle_time_countdown = 0;
nosave int battle_start_time = 0;

nosave object *total = ({});
mixed *bunch_topten = ({});

int check_out(object me);

int is_battle_open()
{
        return battle_open_flag;
}

int is_battle_start()
{
        return battle_start_flag;
}

void topten_bunch_add(string bunch_name)
{
//      int n;
//      string t;

        ++battle_times;
        bunch_topten += ({
                ([
                        "bunch_name" :  bunch_name,
                        "time"       :  time(),
                ]),
        });

        save();
}
// 返回最近第几场取胜的帮派名称
string query_bunch_topten(int n)
{
        mapping data;

        if( !sizeof(bunch_topten) ) return "精意山庄";
        data = bunch_topten[sizeof(bunch_topten)-n];
        return data["bunch_name"];
}

int is_top_bunch(object me)
{
        string bname;

        if( !(bname = query("bunch/bunch_name", me)) )
                return 0;

        return bname == query_bunch_topten(1);
}

void restore_status(object me)
{
        mapping my, cnd;
        string *ks;
        string where;
        int i;

        me->delete_override("unconcious");
        me->delete_override("die");
        me->delete_override("quit");
        delete_temp("override/receive_damage", me);
        me->remove_all_enemy(1);
        me->remove_all_killer();
        me->clear_condition();
        me->receive_damage("qi", 0);
        me->apply_killer(query_temp("backup/killer", me));
        me->apply_want(query_temp("backup/want", me));

        cnd=query("backup/condition", me);
        delete("backup/condition", me);
        delete_temp("block_msg/all", me);
        delete_temp("in_pkd", me);

        my = me->query_entire_dbase();
        if( my["qi"] < 1 )       my["qi"] = 1;
        if( my["eff_qi"] < 1 )   my["eff_qi"] = 1;
        if( my["jing"] < 1 )     my["jing"] = 1;
        if( my["eff_jing"] < 1 ) my["eff_jing"] = 1;

        if( stringp(where = query_temp("battle/leave_room", me)) )
                me->move(where);
        else
                me->move(LEAVE_ROOM);

        delete_temp("battle", me);

        if( !mapp(cnd) ) return;
        ks = keys(cnd);
        for( i = 0; i < sizeof(ks); i++ )
            me->apply_condition(ks[i], cnd[ks[i]]);
}

void init_player(object me)
{
        int i;
        object *obs;

        tell_object(me, HIY "你眼前忽然一花...\n" NOR);
        me->set_override("unconcious", (: call_other, __FILE__, "check_out" :));
        me->set_override("die", (: call_other, __FILE__, "check_out" :));
        me->set_override("quit", (: call_other, __FILE__, "check_quit" :));
        //set_temp("override/receive_damage", (:call_other,__FILE__,"receive_damage":), me);
        set_temp("backup/killer", me->query_killer(), me);
        set_temp("backup/want", me->query_want(), me);
        set_temp("in_pkd", 1, me);

        set("backup/condition", me->query_condition(), me);
        me->clear_condition();

        obs = all_inventory(me);
        for( i=0; i<sizeof(obs); i++ )
        {
                if( query("id", obs[i]) == "mian ju" )
                        obs[i]->move();
        }

        if( !arrayp(total) )
                total = ({ me });
        else
        if( member_array(me, total) == -1 )
                total += ({ me });

        me->move("/maze/binghuodao/haitan"+(1+random(2)));
}

// 参与战争
void join_battle(object me)
{
//      string where;
//      mapping cnd;
//      string id = me->query_id(1);

        /*
        if( battle_start_flag )
                return tell_object(me, "战场已经开启，报名终止。\n");
        */

        if( me->is_busy() )
                return tell_object(me, BUSY_MESSAGE);

        if( me->is_fighting() )
                return tell_object(me, "你目前正在战斗中，还是先处理目前的对手再说吧。\n");

        if( me->query_condition("killer") )
                return tell_object(me, "官府正在通缉你，你还敢在这儿抛头露面？\n");

        if( !battle_open_flag )
                return tell_object(me, "战争没有发出集结，目前无法报名。\n");

        if( me->is_ghost() )
                return tell_object(me, "等你还阳后，再报名吧。\n");

        init_player(me);

        CHANNEL_D->channel_broadcast("war", "目前共有 "+sizeof(total)+
                                            " 位玩家报名参与"HIY"第"HIG+chinese_number(battle_times+1)+HIY"届帮派争夺战。"NOR);

}

void stop_battle()
{
        object ob;
//      object player;

        set_heart_beat(0);

        foreach( ob in total )
        {
                if( !objectp(ob) )
                        continue;

                //ob->remove_all_killer();
                ob->remove_all_enemy(1);
                restore_status(ob);
                tell_object(ob, "你被传离战场...\n");
        }

        total = allocate(0);
        battle_open_flag = 0;
        battle_start_flag = 0;
        battle_time_countdown = 0;
}

public void win_battle(object me, string bunch_name)
{
        stop_battle();

        CHANNEL_D->channel_broadcast("news", HIY + "恭喜帮派【" + bunch_name + "】获得了第" + HIG +
                              chinese_number(battle_times+1) + HIY "届帮派争夺战的胜利！\n" NOR);
        CHANNEL_D->channel_broadcast("news", HIY + "本届帮派争夺战中，" + me->name() + HIY + "(" + me->query_id(1) +
                              ")居功至伟，获得了丰厚的奖励！\n" NOR);
        CHANNEL_D->channel_broadcast("news", HIY + "帮派" + bunch_name + "所有人员在接下来二十四小时内拥有冰火岛历练独家所有权！\n" NOR);

        tell_object(me, HIY "你在本届帮战中成为最后的夺旗者，获得了二百万经验、二百万潜能和二百万实战体会奖励！\n" NOR);
        addn("combat_exp", 2000000, me);
        addn("potential", 2000000, me);
        addn("experience", 2000000, me);

        topten_bunch_add(bunch_name);
        add_bunch_honors(bunch_name, 1000);
        set_heart_beat(1800 + random(30));
}

// 某战场开始接受报名 TIME_D 调用
void start_join()
{
        string *dirs;
        object ob;
        int i;

        CHANNEL_D->channel_broadcast("war", HIY"荣耀"NOR YEL"之战"HIR"发出战争集结，即将在 "+(BATTLE_JOIN_TIME/60)+
                                            " 分钟后发动"HIY"第"HIG+chinese_number(battle_times+1)+HIY"届帮派争夺战，"HIR"请准备加入战役(help bunch_war)。\n"NOR);

        total = ({});
        battle_open_flag = 1;

        battle_start_time = BATTLE_JOIN_TIME;

        set_heart_beat(1);

        dirs = get_dir("/maze/binghuodao/");
        for( i = 0; i < sizeof(dirs); i++ )
        {
                if( file_size("/maze/binghuodao/"+dirs[i]) == -2 ) continue;
                ob = find_object("/maze/binghuodao/"+dirs[i]);
                if( objectp(ob) ) destruct(ob);
        }
        //tell_object(users(), "\a");
}

void start_battle()
{
        // object *all_player = ({ });
        object ob;
//      object player;
//      string where;
//      int i;

        if( sizeof(total) < 5 )
        {
                set_heart_beat(1800);
                total = allocate(0);
                battle_open_flag = 0;
                battle_start_time = 0;
                CHANNEL_D->channel_broadcast("war", "报名参与"HIY"第"HIG+chinese_number(battle_times+1)+HIY"届帮派争夺战"HIR"的玩家不足 5 人，取消本次战役。");
                return;
        }

        CHANNEL_D->channel_broadcast("war", "开始出征！共计 "+sizeof(total)+
                                            " 位玩家参与"HIY"第"HIG+chinese_number(battle_times+1)+HIY"届帮派争夺战，"HIR"计时 "+(BATTLE_TIME/60)+" 分钟结束。");

        ob = new("/maze/binghuodao/npc/xiexun");
        ob->move("/maze/binghuodao/jitan");

        battle_start_flag = 1;
        battle_time_countdown = BATTLE_TIME;
}

public int query_bunch_battle(object me)
{
        string str;
        int i,n,t;

        str = "";

        str += HIG "\n当前天下第一帮：" + HIY + query_bunch_topten(1) + NOR;
        str += HIG "\n当前帮战的状态：";
        str += battle_start_flag ? HIR "当前帮战进行中。" NOR : (battle_start_time > 0 ? HIY "帮战准备中，即将开始。" NOR :"当前帮战未进行。");
        str += "\n";
        str += battle_start_flag ? HIR "当前帮战还剩余" + time_period(battle_time_countdown) + "结束。" NOR : "";
        str += "\n";

        str += HIG "\n最近十届帮派争夺战获胜帮派：\n" NOR;
        str += sprintf("%-15s%-15s%-40s\n", "届数", "帮派", "胜利日期");
        str += "----------------------------------------------------------\n";

        if( n = sizeof(bunch_topten) )
        {
                // 显示最近10届
                if( n > 10 )
                        t = n - 10;
                else
                        t = 0;

                for( i = t; i < n; i ++ )
                {
                        if( me->query_bunch() == bunch_topten[i]["bunch_name"] )
                        {
                                str += sprintf(HIG "%-15d%-15s%-40s\n" NOR,
                                                i + 1,
                                                bunch_topten[i]["bunch_name"],
                                                TIME_D->replace_ctime(atoi(bunch_topten[i]["time"])));
                        }
                        else
                        {
                                str += sprintf("%-15d%-15s%-40s\n",
                                                i + 1,
                                                bunch_topten[i]["bunch_name"],
                                                TIME_D->replace_ctime(atoi(bunch_topten[i]["time"])));
                        }
                }
        }
        str += "----------------------------------------------------------\n";
        str+= HIG "绿色代表你当前所在帮派。\n" NOR;
        tell_object(me, str);
        return 1;
}

void auto_check()
{
        object ob;
//      string msg;
        string room;
        object *lost;
        int i;

        lost = ({ });
        for (i = 0; i < sizeof(total); i++)
        {
                if( !objectp(total[i]))
                        continue;
                room = base_name(environment(total[i]));
                if( !sscanf(room, "/maze/binghuodao%*s") )
                {
                        // not in pk room
                        restore_status(total[i]);
                        total[i] = 0;
                        continue;
                }
                if( query("qi", total[i])<1 || query("jing", total[i])<1 )
                        lost += ({ total[i] });
        }

        foreach (ob in lost)
                check_out(ob);

        total -= ({ 0 });
}

int check_out(object me)
{
        object ob;
        mapping my;
        string msg;
        string room;

        room = base_name(environment(me));
        if( !sscanf(room, "/maze/binghuodao%*s") )
        {
                // not in battle room
                total -= ({ me });
                return 0;
        }

        my = me->query_entire_dbase();
        my["eff_qi"] = my["max_qi"];
        my["eff_jing"] = my["max_jing"];
        my["qi"] = 1;
        my["jing"] = 1;

        tell_object(me, HIR "\n你觉得眼前一阵模糊...这下完了！\n" NOR);
        if( ob = me->query_last_damage_from() )
        {
                msg = me->name(1) + "惨遭" + ob->name(1) + "的毒手，被无情ＰＫ。";
        } else
                 msg = me->name(1) + "运气不佳，本领有限、已经惨遭ＰＫ。";

        message("vision", msg, environment(me), ({ me }));

        restore_status(me);
        total -= ({ me });

        message("vision", "一个黑影倏的窜了出来，随即就是“啪”的"
                "一声，就见" + me->name() +"摔倒了地上，一副半死不"
                "活的样子。\n", environment(me), ({ me }));
        tell_object(me, "半昏半迷中，你觉得被人拎了起来，又"
                "重重的摔倒了地上。\n");

        if( !living(me) )
                me->revive();

        return 1;
}
// end

void create()
{
//      mapping data;
        string *all_bang;
        string bang;

        seteuid(getuid());
        set("channel_id", HIY "帮派通告" NOR);
        restore();
        set_heart_beat(1800);
        // 转移到timed.c中调用
        //SCHEDULE_D->set_event(7200, 1, this_object(), "manage_areas");

        if (! mapp(bunch_fame)) bunch_fame = ([ ]);
        if (! mapp(area_fame)) area_fame = ([ ]);
        all_bang = keys(bunch_fame) - ({ 0 });
        if( sizeof(all_bang) )
        foreach (bang in all_bang)
                delete(bang+"/efficient");
}

void remove()
{
        save();
}
// 要在 CMDS:REBOOT 里面加上调用
public void mud_shutdown()
{
        save();
}

// 心跳：维护帮派的通常信息
void heart_beat()
{
        int t;
        int last;
        string *all_fam;
        string fam;

        t = time();
        last = query("last_check");
        if ((t / 86400) != (last / 86400))
        {
                // 天数发生了变化：复制帮派的名望信息
                all_fam = keys(bunch_fame) - ({ 0 });
                last_bunch_fame = ([ ]);

                foreach (fam in all_fam)
                        last_bunch_fame[fam] = bunch_fame[fam];
        }
        set("last_check", t);
        /*
        all_fam = keys(bunch_fame) - ({ 0 });
        foreach (fam in all_fam)
        {
                if (query(fam + "/war_endtime") &&
                    time() > query(fam + "/war_endtime"))
                        war_stop_time(fam);
        }
        */

        if( battle_start_time > 0 )
        {
                switch(--battle_start_time)
                {
                        case 0:
                                start_battle();
                                break;
                        case 60:
                        case 120:
                        case 180:
                        case 300:
                        case 600:
                        case 900:
                                CHANNEL_D->channel_broadcast("war", HIY"荣耀"NOR YEL"之战"HIR"发出战争集结，即将在 "+(battle_start_time/60)+
                                            " 分钟后发动"HIY"第"HIG+chinese_number(battle_times+1)+HIY"届帮派争夺战，"HIR"请准备加入战役(help bunch_war)。"NOR);
                                break;
                }

                return;
        }

        if( !battle_start_flag )
                return;

        if( --battle_time_countdown <= 0 )
        {
                CHANNEL_D->do_channel(this_object(), "news", HIM "很遗憾，本届天下第一帮争夺战在由于超时而结束了!\n" NOR);
                stop_battle();
                return;
        }

        if( sizeof(total) )
                auto_check();

        if( battle_time_countdown == 60 || battle_time_countdown == 180 )
                CHANNEL_D->channel_broadcast("war", HIR"战"NOR RED"争"HIR"："+HIY"第"HIG+chinese_number(battle_times+1)+
                                                    HIY"届帮派争夺战"HIR"即将在 "+(battle_time_countdown/60)+" 分钟后结束..."NOR);
}

public mixed manage_areas()
{
        string  bunch_name, bad_area, *item, *all_area,
                *all_bunch, *lost, str;
        object  room, player, npc;
        int     weiwang, jizhi, kaifa, zhongcheng, count, i;
        int     area_money, bad_money, rest_money, npc_money, cost;
        mapping data = ([ ]);

        all_area = keys(area_fame) - ({ 0 });

        if (! arrayp(all_area) || ! sizeof(all_area))
                return;

        if (random(sizeof(all_area)) > 10)
        {
                bad_area = all_area[random(sizeof(all_area))];

                if (undefinedp(area_fame[bad_area]["ziyuan"]))
                        bad_area = "";
        }
        else
                bad_area = "";

        foreach (string area in all_area)
        {
                reset_eval_cost();

                bunch_name = area_fame[area]["bunch_name"];

                if (bunch_name == "独立中")
                        continue;

                if (! (room = get_object(area)))
                        continue;

                // 盘点时候帮派 NPC 不在时候则无收入
                if (undefinedp(area_fame[area]["npc_id"]) ||
                    ! objectp(npc = present(area_fame[area]["npc_id"], room)))
                        continue;

                if (! mapp(query(bunch_name)))
                {
                        message("channel:rumor", HIM"【泥潭帮会】由于帮派瓦解，" +
                                query("short", room)+"宣布脱离帮会"+"「"+bunch_name+
                                "」" + "的控制！\n" NOR, users());

                        delete("bunch", npc);
                        area_fame[area]["bunch_name"] = "独立中";
                        continue;
                }

                if (area_fame[area]["money"] < -1000000 ||
                    query(bunch_name + "/money") < -100000000)
                {
                        message("channel:rumor", HIM"【泥潭帮会】由于经营不善，" +
                                query("short", room)+"宣布脱离帮会"+"「"+bunch_name+
                                "」" + "的控制！\n" NOR, users());

                        // 调整帮派威望
                        weiwang = bunch_fame[bunch_name];
                        weiwang -= 1000;
                        if (weiwang < 0) weiwang = 0;
                        bunch_fame[bunch_name] = weiwang;

                        delete("bunch", npc);
                        area_fame[area]["bunch_name"] = "独立中";
                        continue;
                }

                zhongcheng = area_fame[area]["zhongcheng"];
                if (! intp(zhongcheng) || zhongcheng < 10)
                        zhongcheng = 10;

                zhongcheng -= random(2);

                if (zhongcheng >= 100)
                        zhongcheng = 100;

                set("bunch/zhongcheng", zhongcheng<10?10:zhongcheng, npc);
                area_fame[area]["zhongcheng"] = (zhongcheng < 10 ? 10 : zhongcheng);

                jizhi = area_fame[area]["jizhi"];
                kaifa = area_fame[area]["kaifa"];
                jizhi += random(2);
                kaifa -= random(2);

                area_money = area_fame[area]["money"];
                if (! stringp(area_money) && ! intp(area_money))
                        area_money = 0;

                if (! intp(jizhi) || jizhi < 6)
                        jizhi = 6;
                else if (jizhi > 60)
                        jizhi = 60;

                if (! intp(kaifa) || kaifa < 20)
                        kaifa = 20;
                else if (kaifa > 100)
                        kaifa = 100;

                area_fame[area]["kaifa"] = kaifa;
                area_fame[area]["jizhi"] = jizhi;

                if (area == bad_area)
                {
                        if (jizhi && kaifa < 80)
                        {
                                bad_money = kaifa * jizhi * 100000;

                                area_money -= bad_money;
                        } else
                        { // 开发度高的，一般来说自然灾害影响不大
                                bad_area = "";
                                area_money += (kaifa / 2) * (jizhi / 2) * 10000;
                        }
                } else
                        area_money += (kaifa / 2) * (jizhi / 2) * 20000;


                rest_money = area_money - 1000000;
                if (rest_money < 0)
                        rest_money = 0;

                area_fame[area]["money"] = area_money - rest_money;
                area_fame[area]["last_money"] = rest_money;

                data[bunch_name] += rest_money;
        }

        all_bunch = keys(bunch_fame);

        if (! arrayp(all_bunch) || ! sizeof(all_bunch))
                return;

        lost = ({ });
        foreach (string bunch in all_bunch)
        {
                reset_eval_cost();

                npc_money = query(bunch + "/npc_money");
                set(bunch + "/last_npc_money", npc_money);
                set(bunch + "/npc_money", 0);

                set(bunch + "/last_area_money", data[bunch]);

                data[bunch] += npc_money;
                if (data[bunch] < 0) data[bunch] = 0;

                data[bunch] /= 2;

#ifndef LONELY_IMPROVED
                if (query(bunch + "/money") < 2000000000)
#endif
                        addn(bunch + "/money", data[bunch]);

                cost = 200 * (sizeof(BUNCH_D->query_bunch_areas(bunch)) * 2 +
                              sizeof(query(bunch + "/member")));

                addn(bunch + "/money", -cost);
                data[bunch] /= 2;

                addn(bunch + "/bangzhu_money", data[bunch]);
                set(bunch + "/last_bangzhu_money", data[bunch]);

                if (query(bunch + "/money") < -100000000)
                {
                        message("channel:rumor", HIW "【泥潭帮会】由于帮派资产长期严重亏损，帮会「" +
                                                 bunch + "」无法维持日常开支，土崩瓦解了！\n" NOR, users());
                        lost += ({ bunch });
                        map_delete(data, bunch);
                }
        }

        if (arrayp(lost) && sizeof(lost) > 0)
        {
                foreach (bunch_name in lost)
                        dismiss_bunch(bunch_name);
        }
        lost = ({ });

        if (! arrayp(users()) || ! sizeof(users()))
                return;

        // give all online player banghui's money
        item = keys(data);

        for (i = 0; i < sizeof(item); i++)
        {
                reset_eval_cost();

                count = 0;

                foreach (player in users())
                {
                        reset_eval_cost();

                        if (! playerp(player)) continue;

                        if( !query("bunch/bunch_name", player) ||
                            query("bunch/bunch_name", player) != item[i] )
                                continue;

                        count++;
                }

                if (count == 0) count = 1;
                data[item[i]] /= count;
        }

        foreach (player in users())
        {
                reset_eval_cost();

                if (! playerp(player)) continue;

                if( !query("bunch/bunch_name", player))continue;

                if( !data[query("bunch/bunch_name", player)])continue;

                tell_object(player,HIG"帮派「"+query("bunch/bunch_name", player)+"」"+"发饷，你的存款增加了"+
                                    MONEY_D->money_str(data[query("bunch/bunch_name", player)])+"！\n"NOR);

#ifndef LONELY_IMPROVED
                if( query("balance", player)>2000000000 )
                        tell_object(player, RED "你在钱庄的钱已达到二十万两黄金，快点花吧！\n" NOR);
                else
#endif
                        addn("balance", data[query("bunch/bunch_name", player)], player);
        }

        if (bad_area == "")
                message("channel:rumor", HIM "【帮派】某人：各地盘收入良好，请各位帮主速来钱庄转帐！\n" NOR,
                        users());
        else
        {
                str = bad_weather[random(sizeof(bad_weather))];
                str = replace_string(str, "$N", bad_area);

                message("channel:rumor", HIM "【帮派】某人：" + str +
                                         MONEY_D->money_str(bad_money) + "！\n" NOR, users());
        }
        save();
}

// 返回帮派声望：如果参数为空，返回mapping类型，包含了所有同
// 盟的声望；如果参数是人物， 则返回该人物所在的那个帮派的声
// 望；如果参数是帮派，则返回该帮派的声望。
public mixed query_bunch_fame(mixed ob)
{
        string fname;

        if (stringp(ob))
                return bunch_fame[ob];

        if (objectp(ob))
        {
                if( stringp(fname=query("bunch/bunch_name", ob)) )
                        return bunch_fame[fname];
                else
                        return 0;
        }

        return bunch_fame;
}

// 查询昨天的帮派名望信息
public mapping query_all_last_bunch_fame()
{
        if (! mapp(last_bunch_fame))
                // 没有昨天的信息，返回今天的
                return bunch_fame;

        // 返回昨天的帮派声望信息
        return last_bunch_fame;
}

// 查询帮派的仇恨信息：输入的ob可以是帮派的名字，也可是
// 中的人物。
public mapping query_bunch_hatred(mixed ob)
{
        mapping hatred;
        string fname;

        if (objectp(ob))
                fname=query("bunch/bunch_name", ob);
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || ! mapp(hatred = query(fname + "/hatred")))
                return 0;

        return hatred;
}

// 变化帮派声望：输入的ob可以是帮派的名字，也可是帮派中的人物。
public void add_bunch_fame(mixed ob, int n)
{
        int new_fame;
        string fname;

        if (objectp(ob))
                fname=query("bunch/bunch_name", ob);
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || undefinedp(query(fname + "/member")))
                return;

        // 计算新的帮派声望
        new_fame = bunch_fame[fname] + n;
        if (new_fame < 0) new_fame = 0;
        if (new_fame > MAX_BUNCH_FAME)
                new_fame = MAX_BUNCH_FAME;
        bunch_fame[fname] = new_fame;
}

// 帮派间仇杀
public void bunch_kill(object killer, object victim)
{
        int kexp;
        int vexp;
        string vfam;
        string kfam;
        string kid;
        int fame_delta;
        mapping hatred;
        mixed *d;

        // 只有玩家之间的仇杀才计算在内
        if (! objectp(killer) || ! playerp(killer) ||
            ! objectp(victim) || ! playerp(victim))
                return;

        // 巫师之间的比划可不能算数
        if (wizardp(killer) || wizardp(victim))
                return;

        // 查看这两个玩家所处的帮派
        kfam=query("bunch/bunch_name", killer);
        vfam=query("bunch/bunch_name", victim);

        if (! stringp(kfam) && ! stringp(vfam))
                // 都不在帮派内，不必继续了
                return;

        kexp=query("combat_exp", killer);
        vexp=query("combat_exp", victim);

        if (kfam == vfam)
        {
                if( !killer->is_killing(query("id", victim)) )
                        // 失手所杀，不予理会
                        return;

                // 帮派内残杀？不与理会，直接扣除帮派和个人1/10威望。
                add_bunch_fame(kfam, -bunch_fame[kfam] / 10);
                addn("weiwang", -query("weiwang", killer)/10, killer);
                return;
        } else
        if (bunch_is_league(kfam, vfam))
        {
                if( !killer->is_killing(query("id", victim)) )
                        // 失手所杀，不予理会
                        return;
                // 同盟帮派内残杀？直接扣除帮派和个人1/20威望。
                add_bunch_fame(kfam, -bunch_fame[kfam] / 20);
                addn("weiwang", -query("weiwang", killer)/20, killer);
                return;
        }

        if (kexp < vexp*3 && vexp >= 100000)
        {
                // 杀手的经验不是远远的大于对方，并且被杀的
                // 人有一定的经验，这将导致帮派声望的降低。
                fame_delta=vexp+query("score", killer)*2+
                             query("weiwang", killer)*10;
                fame_delta /= 1000;
        } else
                // 对手经验太少，或是差距太大，不影响声望
                fame_delta = 0;

        // 查看杀手所在的帮派是否仇恨死者：如果仇恨，则能够
        // 带动声望的变化。
        if (stringp(kfam))
        {
                string path;

                path=kfam+"/hatred/"+query("id", victim);
                d = query(path);
                if (arrayp(d) && sizeof(d) >= 2 && intp(d[1]))
                {
                        // 仇恨死者，帮派获得额外的声望
                        if (d[1] > 2000)
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                        "听说" + killer->name(1) + "击毙了" +
                                        victim->name(1) + "，为" +
                                        kfam + "出了一口恶气。");
                        fame_delta += d[1] / 3;

                        // 对此人的仇恨降低(降低的要比增加的要多)，
                        // 具体可以看fame_delta 与仇恨度公司的差异
                        d[1] -= fame_delta;
                        if (d[1] <= 0)
                                delete(path);
                        else
                                set(path, d);
                }
        }

        // 调整两个帮派的声望
        add_bunch_fame(killer,  fame_delta);
        add_bunch_fame(victim, -fame_delta);

        // 统计该杀手对本门的残害程度
        if (! stringp(vfam))
                return;

        // 仇恨程度和声望的变化都是在一个数量级上(K经验)，但
        // 是仇恨程度低于声望的变化。
        vexp = vexp/1000 + 1;
        if (vexp > 5000)
                vexp = (vexp - 5000) / 16 + 2000;
        else
        if (vexp > 1000)
                vexp = (vexp - 1000) / 4 + 1000;

        kid=query("id", killer);
        if (! mapp(hatred = query(vfam + "/hatred")))
        {
                set(vfam + "/hatred/" + kid,
                    ({ killer->name(), vexp }));
                return;
        }

        // 每个帮派最多记录若干个仇人
        if (! undefinedp(d = hatred[kid]))
        {
                if (! arrayp(d) || sizeof(d) < 2 ||
                    ! intp(d[1]) || ! stringp(d[0]))
                {
                        // 这个ID的数据出了故障
                        d = 0;
                }
        } else
        if (sizeof(hatred) >= MAX_HATRED_PERSON)
        {
                string *ids;
                int i;

                // 过滤去掉一些人，为什么不去掉一个？这是为
                // 了防止过滤频繁的进行过滤操作。
                ids = sort_array(keys(hatred),
                                 (: sort_hatred :), hatred);
                for (i = 0; i < sizeof(ids) && i < HATREDP_REMOVED; i++)
                        map_delete(hatred, ids[i]);
        }

        if (! arrayp(d))
                d = ({ killer->name(1), vexp });
        else
        {
                d[0] = killer->name(1);
                d[1] += vexp;
        }

        // 记录这个人的信息
        hatred[kid] = d;
}

// 去掉所有帮派对某个人的仇恨信息
public void remove_hatred(string id)
{
        mixed dbase, bunch, hatred;
        string fam;

        if (! mapp(dbase = query_entire_dbase()))
                // 现在还没有仇恨信息
                return;

        // 查阅所有的
        foreach (fam in keys(dbase))
        {
                reset_eval_cost();

                if (! mapp(bunch = dbase[fam]))
                        continue;

                if (mapp(hatred = bunch["hatred"]))
                        // 去掉该帮派对某人的仇恨信息
                        map_delete(hatred, id);

                if (! mapp(hatred) || sizeof(hatred) < 1)
                        // 这个帮派已经没有仇恨信息
                        map_delete(bunch, "hatred");
        }

        save();
}

public mixed valid_new_build(object ob, string id, string name)
{
        object env;

        if (! env = environment(ob))
                return "好象出现了点问题，请和巫师联系！\n";

        if (! env->is_create_bunch_room())
                return "这里不可以用来建设帮派总坛，请另选地点。\n";

        if (env->query_room_id(id) || env->query_room_name(name))
                return "这里已经有个房间使用了这个代号了。\n";

        if (file_size(BUNCH_HOME + id + "/center.c") > 0)
                return "已经有别的帮派使用了这个ID代号了。\n";
        // ......
        return 0;
}

// 查看是否可以创建这个
public mixed valid_new_bunch(string fname)
{
        if (query(fname + "/member"))
                return "人家早就有叫这个的啦，你就别凑热闹了。\n";

        if (member_array(fname, npc_bunch) != -1)
                return "江湖上早有这个现成的帮派，你还想做什么？\n";

        if (! undefinedp(FAMILY_D->query_family_fame(fname))
                || ! undefinedp(LEAGUE_D->query_league_fame(fname)))
                return "江湖上已经有" + fname + "了，你还想做什么？\n";

        return 0;
}

// 创建帮派
public void create_bunch(string fname, string id, string type, int base, object *obs)
{
        mapping data;
        string master, zone, entry, center, quester;
        object ob, env, creater;
        string code, city, position;

        bunch_fame[fname] = base;
        if (! mapp(last_bunch_fame))
                last_bunch_fame = ([ fname : base ]);
        else
                last_bunch_fame[fname] = base;

        foreach (ob in obs)
        {
                data = ([ "time"  : time(),
                          "bunch_name"  : fname,
                          "bunch_id"  : id,
                          "type"  : type  ]);

                if (ob->is_team_leader())
                {
                        creater = ob;
                        master=query("id", ob);
                        position = base_name(env = environment(ob));
                        zone = domain_file(position);

                        data += ([ "level" : 7,
                                   "title" : "帮主" ]);
                } else
                {
                        data += ([ "level" : 6,
                                   "title" : "元老" ]);
                }

                set("bunch", data, ob);

                ob->save();
        }

        quester = BUNCH_HOME + id + "/npc/quester.c";
        assure_file(quester);

        switch(zone)
        {
                case "beijing": city = "bj"; break;
                case "city": city = "yz";  break;
                case "changan": city = "ca"; break;
                case "city3": city = "cd"; break;
                case "suzhou": city = "sz"; break;
                case "hangzhou": city = "hz"; break;
                case "xiangyang": city = "xy"; break;
                case "dali": city = "dl"; break;
                default: city = "yz"; break;
        }

        code = @CODE
// Create by BUNCH_D written by Lonely
// quester.c

#include <ansi.h>
inherit NPC;
CODE;
        code += "#define PLACE          \"" + city + "\"\n";
        code += "#define TYPE           \"" + type + "\"\n";
        code += "#define WAIT_TIME      60\n\n";

        if (type == "bad")
        {
                code += sprintf("mapping bunch_bad = ([\n\t\"bunch_name\" : \"%s\",\n\t\"id\" : \"%s\",\n\t" +
                                "\"place\" : \"%s\",\n\t\"boss\" : \"%s\",\n\t\"place_name\" : \"%s\",\n\t" +
                                "\"type\"  : \"%s\",\n\t]);\n", fname, id,
                                city, creater->name(), citys[city], type);
        } else
        {
                code += sprintf("mapping bunch_good = ([\n\t\"bunch_name\" : \"%s\",\n\t\"id\" : \"%s\",\n\t" +
                                "\"place\" : \"%s\",\n\t\"boss\" : \"%s\",\n\t\"place_name\" : \"%s\",\n\t" +
                                "\"type\"  : \"%s\",\n\t]);\n", fname, id,
                                city, creater->name(), citys[city], type);
        }
        code += @CODE

void create()
{
        set_name("任务使者", ({ "quester" }));
        set("gender", "男性");
        set("age", 23);
        set("long", "他是一个长得很英俊的男子，看上去风流倜傥。\n");
CODE;
        if (type == "bad")
        {
                code += @CODE
        set("bunch/bunch_name", bunch_bad["bunch_name"]);
        set("shen_type", -1);
CODE;
        } else
        {
                code += @CODE
        set("bunch/bunch_name", bunch_good["bunch_name"]);
        set("shen_type", 1);
CODE;
        }
        code += @CODE
        set("per", 29);
        set("combat_exp", 1000000);

        set("attitude", "peaceful");

        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 2);
}

CODE;
        if (type == "bad")
                code += "#include <boss_bad.h>\n";
        else
                code += "#include <boss_good.h>\n";

        write_file(quester, code, 1);

        center = BUNCH_HOME + id + "/center.c";
        assure_file(center);

        code = @CODE
// Create by BUNCH_D written by Lonely
// center.c

#include <ansi.h>
#include <room.h>
inherit ROOM;
CODE;
        code += "#define PLACE   \"" + city + "\"\n";
        code += "#define TYPE    \"" + type + "\"\n";

        code += @CODE

// int is_bunch_room() { return 1; }
int sort_by_id(mapping quest1, mapping quest2);

void create()
{
CODE;
        code += sprintf("\tset(\"short\", \"%s总坛\");\n", fname);

        code += sprintf("\tset(\"long\", \"房间的墙上有一块牌子(paizi)。加入帮派" +
                        "%s的玩家，可以在这里选择任务去完成。\\n\");\n", fname);

        code += "\tset(\"objects\", ([\n\t\t__DIR__\"npc/quester\" : 1,\n\t]));\n";
        code += "\tset(\"exits\", ([\n\t\t\"south\" : __DIR__\"room9\", \n\t]));\n";
        code += "\n\tsetup();\n}\n\n";
        // code += "\treplace_program(ROOM);\n}\n";
        code += sprintf("#include <bang_%s.h>\n", type);

        write_file(center, code, 1);

        entry = BUNCH_HOME + id + "/entry.c";
        assure_file(entry);

        code = @CODE
// Create by BUNCH_D written by Lonely
// entry.c

#include <ansi.h>
#include <room.h>
inherit ROOM;

int is_bunch_room() { return 1; }

void create()
{
        set("short", "空房间 - 请使用 cshort 来编辑标题");
        set("long", "这是一间什么也没有的空房间，请利用 clong 来编辑房间叙述。\n");

        set("exits", ([
                "north" : __DIR__"room0",
CODE;
        code += sprintf("\t\t\"out\" : \"%s\", \n\t]));\n", base_name(env));
        code += "\n\tsetup();\n}\n\n";

        write_file(entry, code, 1);

        env->create_room(fname, id, entry);
        DATABASE_D->db_remove_item(base_name(env));
        DATABASE_D->db_create_item(env, env->save_dbase_data());
        env->save();
        CP_CMD->copy_dir("/d/room/bunch/", BUNCH_HOME + id + "/");

        message("vision",creater->name()+"找了一堆工人来在"+query("short", env)+
                "敲敲打打的，建造出一些房间。\n", env);

        data = ([
                "bunch_id"      : id,                // 帮派代号
                "bunch_name"    : fname,             // 帮派名称
                "time"          : time(),            // 帮派成立时间
                "master"        : master,            // 帮派帮主
                "color"         : NOR,               // 帮派颜色
                "money"         : 10000000,          // 帮派资金
                "member"        : obs->query_id(0),  // 帮派成员
                "type"          : type,              // 帮派正邪
                "tax"           : 5,                 // 帮派税率
                "alert"         : 0,                 // 帮派警戒(1~4)
                "league"        : ({}),              // 帮派同盟
                "char_status"   : 0,                 // 帮派人材
                "weapon_status" : 0,                 // 帮派武器
                "char_money"    : 0,                 // 投资在人材的金额
                "weapon_money"  : 0,                 // 投资在武器的金额
                "senior"        : obs->query_id(0),  // 元老（不可提升）
                "room_position" : position,          // 帮派所在文件路径
                "room_entry"    : entry,             // 帮派入口文件路径
                "room_name"     : fname,             // 帮派入口处房间名
                "room_id"       : id,                // 帮派入口房间代码
                "room_zone"     : zone,              // 帮派所在位置区域
                "war_target"    : "NULL",            // 帮派战争敌对帮派
                "war_kill"      : 0,                 // 战争杀死对手数量
                "war_endtime"   : 0,                 // 帮派战争结束时间
                "war_win"       : 0,                 // 帮派战争胜利次数
                "war_lose"      : 0,                 // 帮派战争失败次数
        ]);
        set(fname, data);

        save();
}

// 解散帮派
public void dismiss_bunch(string fname)
{
        string *ids;
        string id, dir, pos;
        object ob, npc, room;

        // 清除名望信息
        map_delete(bunch_fame, fname);
        if (mapp(last_bunch_fame)) map_delete(last_bunch_fame, fname);

        // 清除帮派中的所有玩家的相关信息
        ids = query(fname + "/member");
        dir = query(fname + "/room_id");
        pos = query(fname + "/room_position");

        if (arrayp(ids))
        {
                // 帮派中还有玩家，清除他们的信息
                foreach (id in ids)
                {
                        // 处理中
                        reset_eval_cost();
                        UPDATE_D->clear_user_data(id, "bunch");
                }
        }

        ids = BUNCH_D->query_bunch_areas(fname);

        if (arrayp(ids))
        {
                // 帮派中还有地盘，清除他们的信息
                foreach (id in ids)
                {
                        // 处理中
                        reset_eval_cost();
                        area_fame[id]["bunch_name"] = "独立中";

                        ob = get_object(id);
                        if (! ob) continue;

                        if (objectp(npc = present(area_fame[id]["npc_id"], ob)))
                                delete("bunch", npc);
                }
        }

        RM_CMD->rm_dir(BUNCH_HOME + dir);

        if (stringp(pos))
        {
                room = get_object(pos);
                if (objectp(room))
                {
                        message("vision", "突然几个童子飞也似"
                                  "的冲了过来，手里操着各种家伙"
                                  "，嚷嚷道：闪开！都闪开！\n",
                                  room);
                        room->destroy_room(dir);
                        room->save();
                }
        }

        // 清除帮派的所有信息
        delete(fname);
        save();
}

// 查询帮派中的弟兄
public string *query_bunch_members(mixed ob)
{
        string *member;
        string fname;

        if (objectp(ob))
                fname=query("bunch/bunch_name", ob);
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || ! arrayp(member = query(fname + "/member")))
                return 0;

        return member;
}

// 查询帮派中的地盘
public string *query_bunch_areas(mixed ob)
{
        string *areas, *aname;
        string fname, afile;

        if (objectp(ob))
                fname=query("bunch/bunch_name", ob);
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        aname = keys(area_fame);
        areas = ({ });
        foreach (afile in aname)
        {
                if (area_fame[afile]["bunch_name"] == fname)
                        areas += ({ afile });
        }

        return areas;
}

public string *query_bunch_league(mixed ob)
{
        string *member;
        string fname;

        if (objectp(ob))
                fname=query("bunch/bunch_name", ob);
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || ! arrayp(member = query(fname + "/league")))
                return 0;

        return member;
}

// 查询地盘的信息
public mixed query_area_info(string afile, string info)
{
        if (! stringp(afile) || ! stringp(info))
                return 0;

        if (! mapp(area_fame) || ! sizeof(area_fame))
                return 0;

        if (undefinedp(area_fame[afile]))
                return 0;

        if (info == "dbase")
                return area_fame[afile];

        return area_fame[afile][info];
}

// 查询帮派的信息
public mixed query_bunch_info(string fname, string info)
{
        if (stringp(fname) && stringp(info))
        {
                if (info == "dbase")
                        return query(fname);

                return query(fname + "/" + info);
        }
        else
                return 0;
}

// 在帮派中变动其他参数，例如帮派资产、帮主等。
public void add_bunch_info(string fname, string info, mixed n)
{
        if (! mapp(query(fname)))
                return;

        if (intp(n))
                addn(fname + "/" + info, n);
        else
        if (stringp(n))
                set(fname + "/" + info, n);
        else
                set(fname + "/" + info, n);
}

// 改变地盘中的参数值
public void add_area_info(string afile, string info, mixed value)
{
        if (undefinedp(area_fame[afile]))
                return;

        if (intp(value))
                area_fame[afile][info] += value;
        else
        if (stringp(value))
                area_fame[afile][info] = value;
        else
                area_fame[afile][info] = value;
}

public void set_area_info(string afile, string info, mixed value)
{
        if (undefinedp(area_fame[afile]))
                return;

        area_fame[afile][info] = value;
}

public void remove_area_from_areas(string area_file)
{
        map_delete(area_fame, area_file);
}

// 从帮派中去掉一个人
public varargs void remove_member_from_bunch(mixed fname, string id)
{
        mapping bunch;
        string *member;
        string *areas;
        string area;
        object room, npc;
        string dir, pos;

        if (objectp(fname))
        {
                // fname is user object
                id=query("id", fname);
                if( !stringp(fname=query("bunch/bunch_name", fname)) )
                        return;
        } else
        if (! stringp(fname))
                // or fname must be a bunch name
                return;

        if (! mapp(bunch = query(fname)) ||
            ! arrayp(member = bunch["member"]))
                // no such bunch or no member in the
                return 0;

        member -= ({ id, 0 });
        if (sizeof(member) < 1)
        {
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "听说" + fname + "人才凋零，昔日帮众尽皆散去，从此江湖再无此帮派了。");

                map_delete(bunch_fame, fname);
                if (mapp(last_bunch_fame)) map_delete(last_bunch_fame, fname);

                dir = query(fname + "/room_id");
                pos = query(fname + "/room_position");
                areas = BUNCH_D->query_bunch_areas(fname);

                if (arrayp(areas))
                {
                        // 帮派中还有地盘，清除他们的信息
                        foreach (area in areas)
                        {
                                // 处理中
                                reset_eval_cost();
                                area_fame[area]["bunch_name"] = "独立中";

                                room = get_object(area);
                                if (! room) continue;

                                if (objectp(npc = present(area_fame[area]["npc_id"], room)))
                                        delete("bunch/bunch_name", npc);
                        }
                }

                RM_CMD->rm_dir(BUNCH_HOME + dir);

                if (stringp(pos))
                {
                        room = get_object(pos);
                        if (objectp(room))
                        {
                                message("vision", "突然几个童子飞也似"
                                        "的冲了过来，手里操着各种家伙"
                                        "，嚷嚷道：闪开！都闪开！\n",
                                        room);
                                room->destroy_room(dir);
                                room->save();
                        }
                }

                delete(fname);
        } else
                bunch["member"] = member;
}

// 在帮派中增加一个人
public void add_member_into_bunch(string fname, string id)
{
        string *member;

        if (! arrayp(member = query(fname + "/member")))
                return 0;

        if (member_array(id, member) != -1)
                return 0;

        member += ({ id });
        set(fname + "/member", member);
        save();
}

// 增加地盘到帮派控制中
public void add_area_into_bunch(string fname, string afile, string aname, object ob)
{
        string bname;
        mapping data;
        string *areas;

        areas = keys(area_fame);
        if (member_array(afile, areas) == -1)
        {
                data = ([
                        "area_name"  : aname,
                        "bunch_name" : fname,
                        "npc_id":query("id", ob),
                        "npc_name":query("name", ob),
                        "kaifa"      : 10,
                        "zijin"      : 10,
                        "zhongcheng" : 10,
                        "money"      : 0,
                        "last_money" : 0,
                ]);

                area_fame[afile] = data;
        } else
        {
                bname = area_fame[afile]["bunch_name"];
                if (bname != "独立中")
                        message("channel:rumor",  HIM "【帮派】某人：" + aname +
                                "宣布脱离帮派「" + bname + "」的控制！\n" NOR, users());
                area_fame[afile]["bunch_name"] = fname;
                area_fame[afile]["zhongcheng"] = 10;
        }

        set("bunch/bunch_name", fname, ob);
        set("bunch/zhongcheng", 10, ob);
        set("bunch/max_zhongcheng", 100, ob);

        message("channel:rumor",HIM"【帮派】某人："+query("name", ob)+
                "加入帮派「" + fname + "」！\n" NOR, users());

        message("channel:rumor", HIM "【帮派】某人：" + aname +
                "被帮派「" + fname + "」吞并！\n" NOR, users());

        return;
}

// 查询两个帮派是否为同盟
public int bunch_is_league(mixed ob1, mixed ob2)
{
        string *lea;
        string bun1, bun2;

        if (stringp(ob1)) bun1 = ob1;
        else
        if (objectp(ob1))
                bun1=query("bunch/bunch_name", ob1);

        if (stringp(ob2)) bun2 = ob2;
        else
        if (objectp(ob2))
                bun2=query("bunch/bunch_name", ob2);

        if (! stringp(bun1) || ! stringp(bun2))
                return 0;

        lea = query(bun1 + "/league");

        if (! arrayp(lea) || sizeof(lea) < 1)
                return 0;

        foreach (string bun in lea)
                if (bun = bun2)
                        return 1;

        return 0;
}

// 增加一个同盟帮派
public int add_league_into_bunch(mixed ob1, mixed ob2)
{
        string *lea;
        string bun1, bun2;

        if (stringp(ob1)) bun1 = ob1;
        else
        if (objectp(ob1))
                bun1=query("bunch/bunch_name", ob1);

        if (stringp(ob2)) bun2 = ob2;
        else
        if (objectp(ob2))
                bun2=query("bunch/bunch_name", ob2);

        if (! stringp(bun1) || ! stringp(bun2))
                return 0;

        lea = query(bun1 + "/league");

        if (! arrayp(lea))
                lea = ({ bun2 });
        else
        if (member_array(bun2, lea) == -1)
                lea += ({ bun2 });

        set(bun1 + "/league", lea);

        lea = query(bun2 + "/league");

        if (! arrayp(lea))
                lea = ({ bun1 });
        else
        if (member_array(bun1, lea) == -1)
                lea += ({ bun1 });

        set(bun2 + "/league", lea);

        return 1;
}

// 移除一个同盟帮派
public int remove_league_from_bunch(mixed ob1, mixed ob2)
{
        string *lea;
        string bun1, bun2;

        if (stringp(ob1)) bun1 = ob1;
        else
        if (objectp(ob1))
                bun1=query("bunch/bunch_name", ob1);

        if (stringp(ob2)) bun2 = ob2;
        else
        if (objectp(ob2))
                bun2=query("bunch/bunch_name", ob2);

        if (! stringp(bun1) || ! stringp(bun2))
                return 0;

        lea = query(bun1 + "/league");

        if (! arrayp(lea) || sizeof(lea) < 1)
                return 0;

        if (member_array(bun2, lea) == -1)
                return 0;

        lea -= ({ bun2 });

        set(bun1 + "/league", lea);

        lea = query(bun2 + "/league");

        if (! arrayp(lea) || sizeof(lea) < 1)
                return 0;

        if (member_array(bun1, lea) == -1)
                return 0;

        lea -= ({ bun1 });

        set(bun2 + "/league", lea);

        return 1;
}

// 宣布战争
public int announce_war_start(string fname, string bname)
{
        message("channel:rumor", HIR "\n\t轰动武林～～惊动万教～～\n\t"
                HIC + fname + HIR "与" HIM + bname + HIR "的帮派矛盾激化，开始全面开战……\n" NOR, users());

        set(fname + "/war_target", bname);
        set(bname + "/war_target", fname);
        set(fname + "/war_endtime", time() + 3600);
        set(bname + "/war_endtime", time() + 3600);

        return 1;
}

public int war_stop_time(string fname)  // 第一种停止模式-时间到
{
        int kill_1, kill_2, money;
        string bname, wname, lname;

        bname = query_bunch_info(fname, "war_target");

        kill_1 = query_bunch_info(fname, "war_kill");
        kill_2 = query_bunch_info(bname, "war_kill");

        if (kill_1 > kill_2)
        {
                wname = fname;
                lname = bname;
                money = kill_1 * 10000 + 100000;
        }
        else
        if (kill_1 < kill_2)
        {
                wname = bname;
                lname = fname;
                money = kill_2 * 10000 + 100000;
        }
        else
        {
                message("channel:rumor", HIR "\n\t轰动武林～～惊动万教～～\n\t"
                        HIC + fname + HIR "与" HIM + bname + HIR "的帮派对决终于结束……\n\t"
                        HIC + fname + HIR "总共杀掉" HIM + bname + HIG " " + CHINESE_D->chinese_number(kill_1) + HIR "位帮众，\n\t"
                        HIM + bname + HIC "总共杀掉" HIC + fname + HIG " " + CHINESE_D->chinese_number(kill_2) + HIR "位帮众，\n\t"
                        HIR + "双方皆死伤惨重，故以平手作收。\n" NOR, users());

                end_bunch_war(bname, fname, 0);

                return 1;
        }

        message("channel:rumor", HIR "\n\t轰动武林～～惊动万教～～\n\t"
                HIC + wname + HIR "与" HIM + lname + HIR "的帮派对决终于结束……\n\t"
                HIC + wname + HIR "总共杀掉" HIM + lname + HIG " " + CHINESE_D->chinese_number(kill_1) + HIR "位帮众，\n\t"
                HIM + lname + HIC "总共杀掉" HIC + wname + HIG " " + CHINESE_D->chinese_number(kill_2) + HIR "位帮众，\n\t"
                HIM + lname + HIC "战败，必须赔偿" HIC + wname + HIY " " +
                CHINESE_D->chinese_number(money) + HIR "两黄金。\n" NOR, users());

                end_bunch_war(wname, lname, money);

                return 1;
}

public int war_stop_kill(string fname)   // 第二种停止模式..帮主被作掉......
{
        string bname, master;
        int number, money;

        bname = query_bunch_info(fname, "war_target");
        master = query_bunch_info(fname, "master");
        number = query_bunch_info(bname, "war_kill");
        money = number * 1000 + 100000;

        message("channel:rumor", HIC "\t号外!!号外!!轰动武林的" + HIG + bname + HIC "和" HIG + fname + HIC "的帮派对决总于有了结果了!!!!\n"
                HIG "       " + bname + HIC "杀掉了" HIG + fname + HIC "帮派帮主:" HIG + master + HIC "\n" +
                "\t一时之间" + HIG + fname + HIC + "因为帮主被做掉，以致军心大乱!!!一路败退!!!\n" + HIC +
                "\t最后判定::" + HIG + fname + HIC + "必须要付出" + CHINESE_D->chinese_number(money) + "两的赔偿金!!!\n" NOR, users());


        end_bunch_war(bname, fname, money);
        return 1;
}

public int war_stop_money(string lname, int money)   // 第三种停止模式..求和......
{
        string wname, master;

        wname = query_bunch_info(lname, "war_target");
        master = query_bunch_info(lname, "master");

        message("channel:rumor", HIC "\t号外!!号外!!轰动武林的" + HIG + wname + HIC "和" + HIG + lname + HIC + "的帮派对决总于有了结果了!!!!\n" + HIG +
         "   " + wname + HIC + "愿接受" + HIG + lname + HIC + "的帮主" + HIG + master + HIC + "求和!!!双方同意结束战斗状态!!!\n" + HIC +
         "\t最后" + HIG + lname + HIC + "愿给予" + HIG + wname + HIC + "共" + CHINESE_D->chinese_number(money) + "两的求和金!!!\n" NOR, users());

        end_bunch_war(wname, lname, money);

        return 1;
}

public int end_bunch_war(string wname, string lname, int gold)
{
        if (! query(wname + "/member") ||
            ! query(lname + "/member"))
                return 0;

        if (intp(gold) && gold > 0)
        {
                addn(wname + "/war_win", 1);
                addn(lname + "/war_lose", 1);
                addn(wname + "/money", gold);
                addn(lname + "/money", -gold);
        }

        set(wname + "/war_kill", 0);
        set(lname + "/war_kill", 0);
        set(wname + "/war_endtime", 0);
        set(lname + "/war_endtime", 0);
        set(wname + "/war_target", "NULL");
        set(lname + "/war_target", "NULL");

        save();
        return 1;
}

// 增加帮派荣誉点
void add_bunch_honors(string bname, int honors)
{
        addn(bname + "/honors", honors);
        save();
}

int query_bunch_honors(string bname)
{
        return query(bname + "/honors");
}

// 外部调用高效练功
int query_bunch_efficient(string bname, string arg)
{
        int t;
        if( !bname ) return 0;
        t = query(bname + "/efficient/" + arg);
        if( !t ) return 0;
        t -= time();
        if( t < 0 ) return 0;
        return t;
}

void set_bunch_efficient(string bname, string arg, int time)
{
        set(bname + "/efficient/" + arg, time()+time);
        SCHEDULE_D->set_event(time, 0, this_object(), "remove_bunch_efficient", bname, arg);
        save();
}

void remove_bunch_efficient(string bname, string arg)
{
        delete(bname + "/efficient/" + arg);
        save();
}

// 排序：升序
private int sort_hatred(string id1, string id2, mapping hatred)
{
        mixed *d1, *d2;

        if (! arrayp(d1 = hatred[id1]) || sizeof(d1) < 2 || ! intp(d1[1]))
                return -1;

        if (! arrayp(d2 = hatred[id2]) || sizeof(d2) < 2 || ! intp(d2[1]))
                return 1;

        return d1[1] - d2[1];
}

public string query_save_file() { return DATA_DIR "bunchd"; }
