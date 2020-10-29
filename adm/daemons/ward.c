// Ward.c 王朝战争主控制程序
// Created by Lonely 2000.7.20
// Rewrite by Lonely@nitan3 2007/11/28


#include <ansi.h>
#include <room.h>
#include <combat.h>
#include <command.h>

#define END_TIME        1800
#define MENG_TIME       150
#define SONG_TIME       300
#define MOVE_TIME       3
#define COST_TIME       60
#define TRAIN_TIME      3
#define ASSI_TIME       180
#define RIDE_CMD        "/cmds/std/ride"
#define UNRIDE_CMD      "/cmds/std/unride"

inherit F_DBASE;

class ward_info
{
        int economy;     /* 经济国力 */
        int horses;      /* 战马数量 */
        int weapons;     /* 兵甲数量 */
        int stones;      /* 石木数量 */
        int arrows;      /* 羽箭数量 */
        int soilders;    /* 兵源数量 */
        int moneys;      /* 饷银数量 */
        int forages;     /* 粮草数量 */
        int count;       /* 将军人数 */
        object marshal;  /* 主    帅 */
        object *generals;/* 将 军 们 */
}

class ward_info song_info;
class ward_info meng_info;
nosave int have1;
nosave int have2;
nosave int start_time;
nosave int valid_check;
nosave int mg_event_id;
nosave int sc_event_id;
nosave int xl_event_id;
nosave int yd_event_id;
nosave int xh_event_id;
nosave int wc_event_id;
nosave int ap_event_id;
nosave int xt_event_id;
nosave string *ip_numbers;
public string ask_kingwar(object me);
public string join_kingwar(object ob);
public int start_kingwar(object me);
protected int check_out(object me);
protected int check_quit(object me);
protected void init_general(object me);
protected void init_player(object me);
protected void init_marshal(object me);
protected void auto_check();
protected void auto_fight();
public void auto_beat();
public void auto_move();
public void auto_cost();
public void auto_train();
varargs void do_attack(object me, object target, string zhen, string craft,
                       object env, string dir, object room);
public void attack_over(object me);
protected void remove_enemy();
protected void give_bouns();
public void fail_kingwar();
public void win_kingwar();
public void finish_kingwar();
protected void restore_status(object me);
protected void restore_kingwar();
protected void message_ward(string msg);
public int query_stones(object me);
public int query_arrows(object me);
public int expend_stones(object me, int count);
public object query_marshal() { return song_info->marshal; }
public object *query_generals() { return song_info->generals; }
public string query_continue_time() { return time_period(time() - start_time); }
public string *query_ip_numbers() { return ip_numbers; }
#include <war.h>

string *zhen1 = ({ "普通阵","鱼鳞阵","锋矢阵","鹤翼阵","偃月阵","方圆阵","雁行阵","长蛇阵","云龙阵" });
mapping zhen2 = ([
        "普通阵" : ({  0,  -5,   5,  -5,   5,  -5,   5,  -5,   5 }),
        "鱼鳞阵" : ({  5,   0,  10,  10,  -5,  10,  -5,   5, -10 }),
        "锋矢阵" : ({ -5, -10,   0,  10,   5,  -5,  10, -10,   5 }),
        "鹤翼阵" : ({  5,  10, -10,   0,  -5,  -5, -10,  10,   5 }),
        "偃月阵" : ({ -5,   5,  -5,   5,   0, -10, -10,  10,  10 }),
        "方圆阵" : ({  5, -10,   5,   5,  10,   0,  -5,  -5,  -5 }),
        "雁行阵" : ({ -5,   5, -10,  10,  10,   5,   0, -10,  -5 }),
        "长蛇阵" : ({  5,  -5,  10, -10, -10,   5,  10,   0,  -5 }),
        "云龙阵" : ({ -5,  10,  -5,  -5, -10,   5,   5,   5,   0 }),
]);
int zhen_power(string type1, string type2)
{
        int i, type2_i = 0;

        for (i = 0; i < sizeof(zhen1); i++)
        {
                if (type2 == zhen1[i])
                {
                        type2_i = i;
                        break;
                }
        }

        if (! type2_i) return 0;
        if (undefinedp(zhen2[type1])) return 0;
        if (type2_i > sizeof(zhen2[type1][type2_i]))
                return 0;

        return zhen2[type1][type2_i];
}

int clean_up() { return 1; }

/*
void remove(string euid)
{
        if (! this_player())
                return;

        if (sizeof(song_info->generals))
                error("战争精灵：目前还有玩家正在参与王朝战争，你不能摧毁战争精灵。\n");
}
*/
void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "战争精灵");
        CHANNEL_D->do_channel(this_object(), "sys", "王朝战争已经启动。");

        song_info = new(class ward_info);
        meng_info = new(class ward_info);

        meng_info->marshal = 0;
        song_info->marshal = 0;
        have1 = 0;
        have2 = 0;
        valid_check = 0;
}

void valid_inquiry()
{
        valid_check = 1;
        return;
}

int do_inquiry(object me, string arg)
{
        object ob;
        object *total;
        mixed *info;
        string str, quest;
        int i, group;

        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                tell_object(me, "现在前方没有任何战事！\n");
                return 0;
        }

        valid_inquiry();

        if (stringp(arg) && arg == "meng")
        {
                if (! valid_check && ! wizardp(me))
                {
                        tell_object(me, "你的军队目前还没有人侦探到蒙古军队的情报。\n");
                        return 0;
                }

                total = meng_info->generals;
                info = ({ meng_info->forages, meng_info->moneys,
                           meng_info->weapons, meng_info->horses,
                          meng_info->stones,  meng_info->arrows,
                          meng_info->soilders,meng_info->economy,
                          meng_info->count });
        }
        else
        {
                total = song_info->generals;
                info = ({ song_info->forages, song_info->moneys,
                          song_info->weapons, song_info->horses,
                          song_info->stones,  song_info->arrows,
                          song_info->soilders,song_info->economy,
                          song_info->count });
        }

        group = 0;
        for (i = 0; i < sizeof(total); i++)
                if (objectp(total[i]))
                        group+=query_temp("warquest/group", total[i]);

        str = (arg == "meng" ? "蒙古" : "大宋") + "目前国力及军力状况";
        str += "\n\n";
        str += HIC "≡" HIY "----------------------------------------------------" HIC "≡\n" NOR;

        str += sprintf(WHT "粮草：%-10d担\t\t    饷银：%-10d两\n" NOR, info[0], info[1]);
        str += sprintf(WHT "兵甲：%-10d件\t\t    战马：%-10d匹\n" NOR, info[2], info[3]);
        str += sprintf(WHT "石木：%-10d筐\t\t    羽箭：%-10d支\n" NOR, info[4], info[5]);
        str += sprintf(WHT "兵源：%-10d人\t\t    国力：%-10d点\n" NOR, info[6], info[7]);
        str += sprintf(WHT "将领：%-10d名\t\t    士兵：%-10d营\n" NOR, sizeof(total), group);

        str += HIC "\n目前尚可调度的将领名册如下：\n" NOR;

        for (i = 0; i < sizeof(total); i++)
        {
                if (! objectp(total[i]))
                        continue;

                ob = total[i];

                quest=query_temp("warquest/quest", ob);
                if (! quest) quest = "留守宋营，未派遣中";

                str += sprintf("%s%-" + (35+color_len(ob->short(1))) + "s 统军：%-10d营\n" NOR,
                                (ob == me ? HIC : WHT), ob->short(1),
                                query_temp("warquest/group", ob));
                str += sprintf("%s任务：%-29s 位置：%s\n", (ob == me ? NOR : NOR), quest, environment(ob)->short(1));
        }
        str += "\n\n";
        str += "战争已经进行时间 " + query_continue_time() + " \n";
        str += HIB "已阵亡将领" + chinese_number(info[8] - sizeof(total)) + "名\n" NOR;
        str += HIC "≡" HIY "----------------------------------------------------" HIC "≡\n" NOR;
        write(str);
        return 1;
}

int query_moneys()
{
        return song_info->moneys;
}

int change_moneys(int count)
{
        song_info->moneys += count;
        return 1;
}

int query_economy(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->economy;
        else
                return meng_info->economy;
}

int query_horses(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->horses;
        else
                return meng_info->horses;
}

int query_weapons(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->weapons;
        else
                return meng_info->weapons;
}

int query_stones(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->stones;
        else
                return meng_info->stones;
}

int query_arrows(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->arrows;
        else
                return meng_info->arrows;
}

int expend_stones(object me, int count)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                song_info->stones -= count;
        else
                meng_info->stones -= count;

        return 1;
}

int query_soilders(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->soilders;
        else
                return meng_info->soilders;
}

int expend_soilders(object me, int count)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                song_info->soilders -= count;
        else
                meng_info->soilders -= count;

        return 1;
}

int query_forages(object me)
{
        string party;

        party=query_temp("warquest/party", me);

        if (party == "song")
                return song_info->forages;
        else
                return meng_info->forages;
}

void init_marshal(object me)
{
        object bingfu, kaijia;

        set_temp("title", HIW"大宋兵马大元帅"NOR, me);
        set_temp("warquest/party", "song", me);
        set("eff_qi",query("max_qi",  me)+1000*query("degree_jungong", me), me);
        set("qi",query("eff_qi",  me), me);
        set_temp("warquest/train", "infantry", me);
        me->set_override("quit", (: call_other, __FILE__, "fail_kingwar" :));
        me->set_override("die", (: call_other, __FILE__, "marshal_die" :));

        if (! objectp(kaijia = present("kai jia", me)))
        {
                kaijia = new("/d/city2/song/obj/tiejia");
                kaijia->move(me);
        }

        if (! objectp(bingfu = present("bing fu", me)))
        {
                bingfu = new("/adm/npc/obj/bingfu");
                set("owner",query("id",  me), bingfu);
                bingfu->move(me);
        }

        tell_object(me, HIC "\n大人，朝中可用之兵已经所剩无几，仅此数营步兵，尚可一战，此次\n" +
                        "出征，任重道远，无奈事关我大宋国运，还望大人尽力而为，望大人\n" +
                        "早日得胜，凯旋回朝！御马监有为将军备的千里马，可助大人脚力。\n\n" NOR);

        song_info->count = 1;
        song_info->marshal = me;
        song_info->generals = ({ me });
#ifdef DB_SAVE
        if( !MEMBER_D->is_valid_member(query("id", me)) )
#endif
        ip_numbers += ({ query_ip_number(me) });
        set("kingwar_time", time(), me);
}

// set player's override functions
void init_player(object me)
{
        set_temp("warquest/party", "song", me);
        me->set_override("quit", (: call_other, __FILE__, "check_quit" :));
        me->set_override("die", (: call_other, __FILE__, "general_die" :));
        // me->set_temp("override/exert", (: call_other, __FILE__, "exert" :));

        set_temp("warquest/time", time(), me);
        me->move("/d/city2/sying1");
        tell_object(me, HIY "你定神一看，这才发现自己已经到了" +
                            environment(me)->short() + HIY "。\n");

        song_info->count++;
        song_info->generals += ({ me });
#ifdef DB_SAVE
        if( !MEMBER_D->is_valid_member(query("id", me)) )
#endif
        ip_numbers += ({ query_ip_number(me) });
}

void init_general(object me)
{
        string array1, array2, party;
        int degree, flag = 0;
        object ling, horse;

        if (me == meng_info->marshal)
                flag = 1;

        party=query_temp("warquest/party", me);
        degree=4+random(query("combat_exp", me)/5000000+1);

        if (! flag)
        {
                if (degree > 12) degree = 12;
        } else
        {
                if (degree > 16) degree = 16;
        }

        if (! arrayp(meng_info->generals) || ! sizeof(meng_info->generals))
                meng_info->generals = ({ });

        if (! arrayp(song_info->generals) || ! sizeof(song_info->generals))
                song_info->generals = ({ });

        array1 = zhen1[random(sizeof(zhen1))];
        array2 = zhen1[random(sizeof(zhen1))];

        if (party == "meng")
        {
                // 一个营的军队为2000气
                addn("eff_qi", degree*2000, me);
                set("qi",query("eff_qi",  me), me);
                set_temp("warquest/group", degree, me);
                set_temp("warquest/array", array1, me);
                set("degree_jungong", degree, me);

                if (degree > 10) set_temp("title", HIR "蒙古万夫长" NOR, me);
                else if (degree > 8) set_temp("title", HIG "蒙古军那颜" NOR, me);
                else if (degree > 5) set_temp("title", HIY "蒙古千夫长" NOR, me);
                else set_temp("title", HIC "蒙古百夫长" NOR, me);

                horse = new("/d/city2/meng/horse");
                horse->move(environment(me));
                RIDE_CMD->do_ride(me, horse);
                meng_info->soilders -= degree * 2000;
                meng_info->weapons -= degree * 4000;
                meng_info->horses -= degree * 2000;
                meng_info->generals += ({ me });
                meng_info->count++;
                return;
        } else
        if (party == "song")
        {
                set_temp("title", degree_desc[degree-4], me);
                set("degree_jungong", degree, me);
                set_temp("warquest/array", array2, me);
                ling = new("/adm/npc/obj/lingjian");
                set("owner",query("id",  me), ling);
                ling->move(me, 1);
                song_info->generals += ({ me });
                song_info->count++;
                return;
        }
}

int marshal_die()
{
        message_ward(CHINESE_D->chinese_date((time()-14*365*24*60*60)) +
                MAG "，蒙古骑兵大败宋军于襄阳！！\n" +
                "              宋军主帅 " HIR + query("name", song_info->marshal) + " ( " + query("id", song_info->marshal) + " ) " NOR +
                MAG "战死沙场，以身殉国！！\n              靖康耻犹未雪，臣子恨何时灭啊！\n" NOR);

        fail_kingwar();
        return 0;
}

string ask_kingwar(object me)
{
        //return "前线暂时没有战事，将军还是请回吧！\n";
        if (me->query_condition("junquest_fail"))
                return "大人尚是待罪之身，轻言出兵，恐性命难保啊，还是请回吧！\n";

        if( query("degree_jungong", me)<8 )
                return "大人官低位卑，如何能任一军之帅，难服人心哪？！\n";

        if (me->query_skill("craft-cognize", 1) < 120)
                return "大人并不精通兵法，如何能任一军之帅，难服人心哪？！\n";

        if (me->query_skill("array-cognize", 1) < 120)
                return "大人并不精通行兵布阵，如何能任一军之帅，难服人心哪？！\n";

/*
        if( query("kingwar_time", me)+3600>time() )
                return "大人刚征战归来不久，还是休养一段时间后再说！\n";
*/

        if (objectp(song_info->marshal))
        {
                if (me == song_info->marshal)
                        return "大人已经经军令在身了，还在这里磨蹭什么啊？！\n";
                else
                        return "现在已经有" + song_info->marshal->name(1) + "率军出征了，大人可以前去助阵。\n";
        }

        if (start_kingwar(me))
        {
                return "大人还是快点起程吧，耽误了行程可就麻烦了！\n";
        }

        return "似乎出现了点问题，你还是找巫师吧！\n";
}

// start war
int start_kingwar(object me)
{
        object marshal, general, jianjun, room;
        int i;

        ip_numbers = ({ });
        init_marshal(me);

        message_ward(CHINESE_D->chinese_date((time() - 14 * 365 * 24 * 60 * 60)) +
                MAG "蒙古可汗大举南侵，大宋派出\n " +
                ""+"兵马大元帅"+query("name", me)+MAG+"("+query("id", me)+MAG+")"+
                MAG + "，兴师北上抗敌......\n" NOR);

        room = get_object("/d/city2/syuanmen1");
        if (objectp(room))
                set("defence", 200, room);

        room = get_object("/d/city2/myuanmen1");
        if (objectp(room))
                set("defence", 999, room);

        room = get_object("/d/city2/majiu");
        room->reset();

        meng_info->economy = 1000000;
        meng_info->moneys = 10000000;
        meng_info->forages = 10000000;
        meng_info->weapons = 4000000;
        meng_info->stones = 500000;
        meng_info->horses = 2000000;
        meng_info->arrows = 500000;
        meng_info->soilders = 2000000;

        // 布置蒙古军队
        marshal = new("/d/city2/meng/kehan");
        marshal->move("/d/city2/mying1");
        set_temp("warquest/quest", "挥军南下，入侵大宋", marshal);
        meng_info->marshal = marshal;
        meng_info->count = 0;
        init_general(marshal);
        general = new("/d/city2/meng/mengj");
        general->move("/d/city2/mying1");
        set_temp("warquest/quest", "守卫蒙营，保卫可汗", general);
        init_general(general);

        for (i = 0; i < 4; i++)
        {
                general = new("/d/city2/meng/mengj");
                general->move("/d/city2/mying");
                set_temp("warquest/quest", "守卫蒙营，保护可汗", general);
                init_general(general);
                general = new("/d/city2/meng/mengj");
                general->move("/d/city2/dhunya");
                init_general(general);
                set_temp("warquest/quest", "守卫蒙营，保护可汗", general);
        }

        if( query("degree_jungong", me)>10 )
        for (i = 0; i < 2; i++)
        {
                general=new("/d/city2/meng/mengj");
                general->move("/d/city2/caoyuan");
                set_temp("warquest/quest", "守卫草原，阻止入侵", general);
                init_general(general);
        }

        if( query("degree_jungong", me)>12 )
        for (i = 0; i < 2; i++)
        {
                general = new("/d/city2/meng/mengj");
                general->move("/d/city2/myuanmen1");
                set_temp("warquest/quest", "守卫蒙营，阻止入侵", general);
                init_general(general);
        }

        // 初始化宋朝军队数据
        song_info->economy = 1200000;
        song_info->moneys = 50000000;
        song_info->forages = 240000;
        song_info->stones = 240000;
        song_info->arrows = 240000;
        song_info->horses = 60000;
        song_info->weapons = 240000;
        song_info->soilders = 120000;

        jianjun = new("/d/city2/npc/jianjun");
        jianjun->move("/d/city2/sying1");
        init_general(jianjun);
        set_temp("warquest/quest", "留守宋营，监察军事", jianjun);

        // 布置宋军
        for(i = 0; i < 4; i++)
        {
                general = new("/d/city2/song/songb");
                general->move("/d/city2/sying1");
                init_general(general);
        }

        start_time = time();
        mg_event_id = SCHEDULE_D->set_event(MENG_TIME, 1, this_object(), "continue_kingwar", "meng");
        sc_event_id = SCHEDULE_D->set_event(SONG_TIME, 1, this_object(), "continue_kingwar", "song");
        xl_event_id = SCHEDULE_D->set_event(TRAIN_TIME, 1, this_object(), "auto_train");
        yd_event_id = SCHEDULE_D->set_event(MOVE_TIME, 1, this_object(), "auto_move");
        xh_event_id = SCHEDULE_D->set_event(COST_TIME, 1, this_object(), "auto_cost");
        wc_event_id = SCHEDULE_D->set_event(END_TIME, 0, this_object(), "finish_kingwar");
        ap_event_id = SCHEDULE_D->set_event(ASSI_TIME, 1, this_object(), "check_assignment");
        xt_event_id = SCHEDULE_D->set_event(1, 1, this_object(), "auto_beat");
        // set_heart_beat(1);

        return 1;
}

string join_kingwar(object me)
{
        if (! objectp(song_info->marshal))
                return "现在前方没有战事，将军您以后再来吧！\n";

        if (me == song_info->marshal)
                return "元帅您不要开玩笑了！\n";

        if ((time() - start_time) > 1800)
                // return "现在前方战事快要结束了，将军您以后再来吧！\n";
                return "现在前方战事早就开始了，将军您以后再来吧！\n";

        if (member_array(query_ip_number(me), ip_numbers) != -1
#ifdef DB_SAVE
         && !MEMBER_D->is_valid_member(query("id", me) )
#endif
           )
                return "非会员每个IP上只可一个ID参军，将军您还是以后再来吧！\n";

        /*
        if( query("age", me)<12 )
                return "您还小，以后再来为国效力吧！\n";
        */

        if( query("combat_exp", me)<100000 )
                return "其志可嘉，但无奈手无缚鸡之力，您还是请回吧！\n";

        /*
        if( query("degree_jungong", me)<1 )
                return "您的军衔太低微了，到前方估计没什么用啊！\n";
        */

        if (member_array(me, song_info->generals) != -1)
                return "将军您已经披甲上阵了，快到前方去吧！？\n";

/*
        message_ward(CHINESE_D->chinese_date((time()-14*365*24*60*60)) + MAG "有志之士" + me->name(1) +
                MAG "奔赴前线加入了支援宋军抗击蒙古军队之列！\n" NOR);
*/

        init_player(me);

        return "将军您来的正是时候，请马上出发奔赴前线支援吧！\n";
}

// void heart_beat()
void auto_beat()
{
        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
                return;

        // 处理自动作战
        auto_fight();

        if (time() - start_time > 300)
                auto_check();
}

// check all the players who join the war
void auto_check()
{
        object *total;
        object ob;
        string room;
        object *lost;
        int i;

        room = base_name(environment(song_info->marshal));
        if (! sscanf(room, "/d/city2/%*s") &&
            ! sscanf(room, "/d/xiangyang/%*s") &&
            ! sscanf(room, "/d/wuguan/%*s"))
        {
                message_ward(CHINESE_D->chinese_date((time()-14*365*24*60*60)) + song_info->marshal->name(1) +
                        MAG "在战场上临阵脱逃，导致宋军无首领，军心涣散，被蒙古军队全线击败！\n" NOR);
                fail_kingwar();
                return;
        }

        lost = ({ });
        total = song_info->generals;
        if (arrayp(total) && sizeof(total))
        {
                total = filter_array(total, (: objectp($1) && userp($1) :));
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                song_info->generals -= ({ total[i] });
                                continue;
                        }
                        // 检查是否脱离战场
                        room = base_name(environment(total[i]));
                        if (! sscanf(room, "/d/city2/%*s") &&
                            ! sscanf(room, "/d/xiangyang/%*s") &&
                            ! sscanf(room, "/d/wuguan/%*s"))
                        {
                                message("channel:rumor",
                                        MAG "【军情】大宋：" + total[i]->name(1) +
                                        MAG "的军队在战场上临阵脱逃，宋军军心开始涣散，战斗力下降！\n" NOR, users());
                                // not in war room
                                restore_status(total[i]);
                                song_info->generals -= ({ total[i] });
                                ip_numbers -= ({ query_ip_number(total[i]) });
                                continue;
                        }
                        // 检查率领的军队(压粮没有带兵的除外)
                        if( !query_temp("warquest/escort", total[i]) &&
                            !query_temp("warquest/guard", total[i]) &&
                            query_temp("warquest/train", total[i]) &&
                            query("combat_exp", total[i])<20000000 &&
                            member_array(room, ward_place) == -1) {
                                if( query("qi", total[i])<query("max_qi", total[i]) )
                                // total[i]->query_temp("warquest/group") < 1)
                                        lost += ({ total[i] });
                        }
                }
        }

        // song_info->generals -= ({ 0 });
        // kickout the players who lost
        foreach (ob in lost)
                check_out(ob);

        return;
}

void check_assignment()
{
        object *total;

        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                SCHEDULE_D->delete_event(ap_event_id);
                return;
        }

        if (time() - start_time < 600)
                return;

        total = song_info->generals;
        total=filter_array(total,(:objectp($1) && query_temp("warquest/guard", $1) &&
                                       (sscanf(base_name(environment($1)), "/d/xiangyang/%*s") ||
                                        sscanf(base_name(environment($1)), "/d/wuguan/%*s")) :));

        if (sizeof(total) < 1)
        {
                song_info->economy -= 100000;
                if( song_info->economy < 1000000 )
                message("channel:rumor",
                        MAG "【军情】大宋：蒙古突骑兵潜进襄阳城内烧杀抢掠，急待增加守城兵力！！！\n" NOR, users());
                // message_ward(MAG "大宋兵马大元帅疏于襄阳的城防工作，蒙古骑兵在襄阳城内烧杀抢掠。\n" NOR);
        }
        return;
}

// 军队作战处理
// 分为手动控制和系统控制
void auto_fight()
{
        object *obs, ob, obb, env, room;
        object *total;
        string *dirs;
        string dir;
        string zhen, craft;
        mapping exits;
        int group, number, i, j, team;

        total = meng_info->generals;
        if (arrayp(total) && sizeof(total))
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                meng_info->generals -= ({ total[i] });
                                continue;
                        }
                        if (! living(total[i])) continue;

                        ob = total[i];
                        // 粮草及饷银短缺则出现逃兵
                        if (meng_info->moneys < 1)
                                addn("eff_qi", -1, ob);
                        if (meng_info->forages < 1)
                                addn("eff_qi", -1, ob);

                        group=(query("eff_qi", ob)-query("max_qi", ob))/2000;
                        if (group < 1) group = 1;
                        set("qi",query("eff_qi",  ob), ob);
                        set_temp("warquest/group", group, ob);

                        // 兵法辅助攻击-恢复
                        if( query_temp("warquest/recover", ob) )
                                continue;

                        // 兵法辅助攻击-混乱
                        if( query_temp("warquest/confusion", ob) )
                        {
                                set_temp("warquest/recover", 1, ob);
                                ob->start_call_out((: call_other, __FILE__, "recover_status", ob :), 10);
                                continue;
                        }

                        env = environment(ob);
                        obs = all_inventory(env);
                        zhen=query_temp("warquest/array", ob);
                        if( sizeof(obs)>0 && !query_temp("warquest/attack", ob) )
                        {
                                for (j = 0; j < sizeof(obs); j++)
                                {
                                        obb = obs[j];
                                        if (! obb->is_character() || ! living(obb) ||
                                            query("race", obb) != "人类" || obb->is_net_dead() )
                                                continue;

                                        if( query_temp("warquest/party", obb) != "meng" && !wizardp(obb) )
                                        {
                                                message_vision(HIW "$N" HIW "大声下令道：骑兵准备！一排排骑兵列出整齐的「" HIY + zhen +
                                                        HIW "」，\n阳光下的蒙古军刀闪闪发光——>" HBRED "突击" NOR HIW "！！\n" +
                                                        "$N" HIW "一声令下，万马齐鸣，蒙古骑兵开始了可怕的冲锋！！\n" NOR, ob);

                                                craft = "突击";
                                                set_temp("warquest/attack", 1, ob);
                                                ob->start_call_out((: call_other, __FILE__, "attack_over", ob :), 10);
                                                do_attack(ob, obb, zhen, craft, env);
                                                break;
                                        }
                                }
                        }

                        if( mapp(query("exits", env)) && sizeof(query("exits", env)) &&
                            !query_temp("warquest/attack", ob) )
                        {
                                exits=query("exits", env);
                                dirs = keys(exits);
                                for (j = 0; j < sizeof(dirs); j++)
                                        if (env->query_door(dirs[j], "status") & DOOR_CLOSED)
                                                dirs[j] = 0;
                                dirs -= ({ 0 });
                                if (! sizeof(dirs)) continue;
                                dir = dirs[random(sizeof(dirs))];
                                room = get_object(exits[dir]);

                                if (! objectp(room)) continue;
                                obs = all_inventory(room);
                                if (! sizeof(obs)) continue;
                                for (j = 0; j < sizeof(obs); j++)
                                {
                                        obb = obs[j];
                                        if (! obb->is_character() || ! living(obb) ||
                                            query("race", obb) != "人类" || obb->is_net_dead() )
                                                continue;

                                        if( query_temp("warquest/party", obb) != "meng" && !wizardp(obb) )
                                        {
                                                message_vision(HIC "$N" HIC "大声下令道：弓箭手准备！\n" +
                                                        "一排排利箭在阳光下闪闪发光——>" HBRED "飞射" NOR HIC "！！\n" +
                                                        "$N" HIC "一声令下，万弩齐发！\n" NOR, ob);

                                                craft = "突击";
                                                set_temp("warquest/attack", 1, ob);
                                                ob->start_call_out((: call_other, __FILE__, "attack_over", ob :), 10);
                                                do_attack(ob, obb, zhen, craft, env, dir, room);
                                                break;
                                        }
                                }
                        }
                }
        }

        total = song_info->generals;
        if (arrayp(total) && sizeof(total))
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                song_info->generals -= ({ total[i] });
                                continue;
                        }
                        if (! living(total[i])) continue;

                        ob = total[i];
                        if( query_temp("warquest/group", ob)>0 )
                        {
                                // 粮草及饷银短缺则出现逃兵
                                if (song_info->moneys < 1)
                                        addn("eff_qi", -1, ob);
                                if (song_info->forages < 1)
                                        addn("eff_qi", -1, ob);
                        }

                        group=(query("eff_qi", ob)-query("max_qi", ob))/2000;
                        if (group > 0)
                                set("qi",query("eff_qi",  ob), ob);
                        if( query_temp("warquest/group", ob)<1 )
                                delete_temp("warquest/group", ob);
                        team=query_temp("warquest/group", ob);
                        number = group - team;

                        if( number>0 && query_temp("warquest/train", ob) )
                        {
                                tell_object(ob, HIR "你训练出" HIY + chinese_number(number) + HIR "营精锐士兵补充到你的军队中！\n" NOR);
                                addn_temp("warquest/group", number, ob);
                        } else
                        if( number<0 && team>0 && !query_temp("warquest/train_begin", ob) )
                        {
                                if (abs(number) > team) number = team;
                                else number = abs(number);
                                tell_object(ob, HIW "你损失了" HIR + chinese_number(number) + HIW "营的士兵！\n" NOR);
                                addn_temp("warquest/group", -number, ob);
                        }

                        // 判断玩家是否设置为手动控制战斗
                        if( !query("env/auto_war", ob))continue;

                        zhen=query_temp("warquest/array", ob);
                        if (! zhen) zhen = "普通阵";

                        env = environment(ob);
                        // 必须有队伍才能攻击
                        if( !query_temp("warquest/attack", ob) &&
                              query_temp("warquest/group", ob)>0 &&
                            (query_temp("warquest/train", ob) == "cavalry" ||
                              query_temp("warquest/train", ob) == "archer") )
                        {
                                if( mapp(query("exits", env)) && sizeof(query("exits", env)) )
                                {
                                        exits=query("exits", env);
                                        dirs = keys(exits);
                                        for (j = 0; j < sizeof(dirs); j++)
                                                if (env->query_door(dirs[j], "status") & DOOR_CLOSED)
                                                        dirs[j] = 0;
                                        dirs -= ({ 0 });
                                        if (sizeof(dirs))
                                        {
                                                dir = dirs[random(sizeof(dirs))];
                                                room = get_object(exits[dir]);
                                                if (objectp(room))
                                                {
                                                        obs = all_inventory(room);
                                                        if (sizeof(obs) > 0)
                                                        {
                                                                for (j = 0; j < sizeof(obs); j++)
                                                                {
                                                                        obb = obs[j];
                                                                        if( !obb->is_character() || query_temp("warquest/party", obb) != "meng" )
                                                                                continue;

                                                                        if( query_temp("warquest/train", ob) == "archer" )
                                                                        {
                                                                                if( !query_temp("weapon", ob) )
                                                                                        if (! WIELD_CMD->main(ob, "bow"))
                                                                                                continue;

                                                                                craft = "骑射";
                                                                                message_vision(HIB "$N" HIB "大声下令道：神弩营列阵「" HIR + zhen +
                                                                                        HIB "」！\n一排排利箭在阳光下闪闪发光——>" HBRED + craft +
                                                                                        NOR HIB "！！\n$N" HIB "一声令下，万弩齐发！\n" NOR, ob);
                                                                        } else
                                                                        {
                                                                                craft = "突破";
                                                                                ob->move(room);
                                                                                message_vision(HIC "$N" HIC "将手中宝剑一挥，大喝道：车骑营列阵「" HIR + zhen +
                                                                                        HIC "」！\n向敌军发起冲锋——>" HBRED + craft + NOR HIC "！！\n" NOR,
                                                                                        ob, obb);
                                                                        }
                                                                        set_temp("warquest/attack", 1, ob);

                                                                        ob->start_call_out((: call_other, __FILE__, "attack_over", ob :), 10);
                                                                        do_attack(ob, obb, zhen, craft, env, dir, room);
                                                                        break;
                                                                }
                                                        }
                                                }
                                        }
                                }
                        } else
                        if( !query_temp("warquest/attack", ob) &&
                              query_temp("warquest/group", ob)>0 &&
                              query_temp("warquest/train", ob) == "infantry" )
                        {
                                obs = all_inventory(env);
                                if (sizeof(obs) > 0)
                                {
                                        for (j = 0; j < sizeof(obs); j++)
                                        {
                                                obb = obs[j];
                                                if( !obb->is_character() || query_temp("warquest/party", obb) != "meng" )
                                                        continue;

                                                craft = "奋战";
                                                message_vision(HIR "$N" HIR "大声下令道：步兵营列阵！队伍开始排出整齐的「" HIY + zhen +
                                                        HIR "」！\n在一片闪烁的刀光中，$N" HIR "指挥队伍发起了可怕的冲锋——>" HBYEL +
                                                        craft + NOR HIR "！\n" NOR, ob, obb);
                                                set_temp("warquest/attack", 1, ob);
                                                ob->start_call_out((: call_other, __FILE__, "attack_over", ob :), 10);
                                                do_attack(ob, obb, zhen, craft, env);
                                                break;
                                        }
                                }
                        }

                        if (base_name(env) == "/d/city2/myuanmen1" && ! ob->is_busy() &&
                            query_temp("warquest/party", ob) == "song" )
                                ob->command("break");
                }
        }
        return;
}

varargs void do_attack(object me, object target, string zhen, string craft,
                       object env, string dir, object room)
{
        object weapon, bow, blade, weapon2;
        object *ilist;
        int i, power;
        int damage, count = 0;
        string party;
        int points;

        if (! objectp(me))
                return;

        party=query_temp("warquest/party", me);

        // 守城兵法特殊攻击
        if (craft == "落石")
        {
                for(i=0;i<query_temp("warquest/group", me);i++ )
                {
                        if (! objectp(target))
                                break;

                        if ((party == "song" && song_info->stones < 1) ||
                            (party == "meng" && meng_info->stones < 1))
                                break;

                        if (party == "song" && song_info->stones < 2000)
                                damage = song_info->stones;
                        else
                        if (party == "meng" && meng_info->stones < 2000)
                                damage = meng_info->stones;
                        else
                                damage = 2000;

                        if (random(10) > 1)
                        {
                                message_vision(HIC "无数擂石及火油从城墙上推下来，$N"
                                        HIC "一时不备，士兵死伤不少。\n" NOR, target);
                                message_vision(HIC "$N" HIC "的士兵吆喝着将无数擂石及火油从城墙上推下去，$n"
                                        HIC "一时不备，士兵死伤不少。\n" NOR, me, target);
                                target->receive_damage("qi", damage, me);
                                target->receive_wound("qi", damage, me);
                                addn_temp("warquest/reward", 5, me);
                        } else
                        {
                                message_vision(HIC "$N" HIC "的士兵吆喝着将无数擂石及火油从城墙上推下去，$n"
                                        HIC "却早有防备，没有受到损失。\n" NOR, me, target);
                                message_vision(HIC "无数擂石及火油从城墙上推下来，$N"
                                        HIC "却早有防备，没有受到损失。\n" NOR, target);
                                addn_temp("warquest/reward", 4, me);
                        }
                        if (party == "song")
                                song_info->stones -= damage;
                        else
                                meng_info->stones -= damage;
                }
                return;
        } else
        if (craft == "射台")
        {
                for(i=0;i<query_temp("warquest/group", me);i++ )
                {
                        if (! objectp(target))
                                break;

                        if ((party == "song" && song_info->arrows < 1) ||
                            (party == "meng" && meng_info->arrows < 1))
                                break;

                        if (party == "song" && song_info->arrows < 2000)
                                damage = song_info->arrows;
                        else
                        if (party == "meng" && meng_info->arrows < 2000)
                                damage = meng_info->arrows;
                        else
                                damage = 2000;

                        if (random(10) < 9)
                        {
                                message_vision(HIC "无数羽箭从箭楼如飞蝗般射下来，$N"
                                        HIC "一时不备，士兵死伤不少。\n" NOR, target);
                                message_vision(HIC "但听一声梆子响，从箭垛后面钻出无数$N的士兵，箭如飞蝗，$n"
                                        HIC "一时不备，士兵倒下了一片。\n" NOR, me, target);

                                target->receive_damage("qi", damage, me);
                                target->receive_wound("qi", damage, me);
                                addn_temp("warquest/reward", 5, me);
                        } else
                        {
                                message_vision(HIC "无数羽箭从箭楼如飞蝗般射下来，$N"
                                        HIC "一时不备，士兵死伤不少。\n" NOR, target);
                                message_vision(HIC "但听一声梆子响，从箭垛后面钻出无数$N的士兵，箭如飞蝗，$n"
                                        HIC "却早有防备，没有受到损失。\n" NOR, me, target);
                                addn_temp("warquest/reward", 4, me);
                        }
                        if (party == "song")
                                song_info->arrows -= damage;
                        else
                                meng_info->arrows -= damage;
                }
                return;
        }

        // 阵法效果
        count=zhen_power(zhen,query_temp("warquest/array", target));
        points = COMBAT_D->skill_power(me, "parry", SKILL_USAGE_DEFENSE);

        count = points*count/100;
        count = to_int(pow(to_float(count/100), 1.0 / 3)) * 10;
        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count, me);
        addn_temp("apply/unarmed_damage", count, me);

        if( query_temp("warquest/party", me) == "meng" )
        {
                // 蒙古军队攻击
                if (! objectp(target) || ! target->is_character())
                {
                        addn_temp("apply/attack", -count, me);
                        addn_temp("apply/damage", -count, me);
                        addn_temp("apply/unarmed_damage", -count, me);
                        return;
                }

                weapon=query_temp("weapon", me);
                if (weapon) weapon->unequip();

                blade = present("wan dao", me);

                ilist = all_inventory(me);
                for (i = 0; i < sizeof(ilist); i++)
                {
                        if( query("is_bow", ilist[i]) )
                        {
                                bow = ilist[i];
                                break;
                        }
                }
                if (room && dir) weapon2 = bow;
                else weapon2 = blade;

                if (objectp(weapon2))
                        // WIELD_CMD->do_wield(me, weapon2);
                        weapon2->wield();

                for(i=0;i<query_temp("warquest/group", me);i++ )
                {
                        if (! objectp(target) || ! living(target) ||
                            target->is_net_dead()) break;

                        if (objectp(weapon2) &&
                            query("equipped", weapon2) && query("is_bow", weapon2) )
                        {
                                weapon2->do_shoot(query("id", target),me,weapon2,room,dir,1);
                                addn_temp("warquest/reward", 2, target);
                                continue;
                        }

                        if( query("qi", target)<0 ||
                            environment(me) != environment(target))
                                break;
                        /*
                        message_vision(HIC "$N" HIC "指挥的蒙古铁骑，万马奔腾，" +
                                "如狂风骤雨般朝$n" HIC "发起了冲击！！\n" NOR, me, target);
                        */

                        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                        addn_temp("warquest/reward", 2, target);
                }
                addn_temp("apply/attack", -count, me);
                addn_temp("apply/damage", -count, me);
                addn_temp("apply/unarmed_damage", -count, me);
                return;
        }

        power = 0;
        if (craft == "奋战" || craft == "突破" || craft == "骑射")
                power = points*10/100;
        else if (craft == "奋斗" || craft == "突进" || craft == "奔射")
                power = points*20/100;
        else if (craft == "奋迅" || craft == "突击" || craft == "飞射")
                power = points*30/100;

        power = to_int(pow(to_float(power/100), 1.0 / 3)) * 10;
        addn_temp("apply/attack", power, me);
        addn_temp("apply/damage", power, me);
        addn_temp("apply/unarmed_damage", power, me);

        for(i=0;i<query_temp("warquest/group", me);i++ )
        {
                if (! objectp(target)) break;

                if( query_temp("warquest/train", me) == "cavalry" ||
                    query_temp("warquest/train", me) == "infantry" )
                {
                        /*
                        message_vision(HIR "$N" HIR "指挥的三军杀声雷动，" +
                                "如狂风骤雨般朝$n发起了攻击！！\n" NOR, me, target);
                        */
                        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                        // 杀江洋大盗没有奖励
                        if( query_temp("warquest/party", target) == "meng" )
                                addn_temp("warquest/reward", 4, me);
                } else
                if( query_temp("warquest/train", me) == "archer" )
                {
                        bow=query_temp("weapon", me);
                        if( bow && query("is_bow", bow) )
                                bow->do_shoot(query("id", target),me,bow,room,dir,1);
                        // 杀江洋大盗没有奖励
                        if( query_temp("warquest/party", target) == "meng" )
                                addn_temp("warquest/reward", 4, me);
                }
        }

        if( query_temp("warquest/train", me) == "cavalry" )
        {
                message_vision(HIW "一阵冲杀过后，$N" HIW "率领着宋军骑兵如风" +
                        "一般消失了！\n" NOR, me);
                me->move(env);
        }

        addn_temp("apply/attack", -power, me);
        addn_temp("apply/damage", -power, me);
        addn_temp("apply/unarmed_damage", -power, me);

        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        addn_temp("apply/unarmed_damage", -count, me);
        return;
}

// 消除军队异常状况
// 混乱，士气低落...
void recover_status(object me)
{
        delete_temp("warquest/confusion", me);
        delete_temp("warquest/recover", me);

        return;
}

void attack_over(object me)
{
        string party;

        if (! objectp(me) || ! objectp(song_info->marshal))
                return;

        if( !(party=query_temp("warquest/party", me)) )
                return;

        if (party == "meng")
                message_vision(HIB "$N手中军刀一挥，蒙古骑兵攻势一缓，重新" +
                        "开始列阵，准备发起新一轮的冲击！！\n" NOR, me);
        else
        if (party == "song")
                message_vision(HIW "$N" HIW "手中令旗一挥，三军攻势一缓，重新" +
                        "开始列阵，准备发起新一轮的攻击！！\n" NOR, me);

        delete_temp("warquest/attack", me);

        return;
}

// 军队移动处理
void auto_move()
{
        mapping move_way;
        object *total, ob, room;
        string file;
        int i, count;

        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                SCHEDULE_D->delete_event(yd_event_id);
                return;
        }

        total = meng_info->generals;
        if (arrayp(total) && sizeof(total))
        {
                move_way = ward_way;
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                meng_info->generals -= ({ total[i] });
                                continue;
                        }

                        if (! living(total[i]))
                                continue;

                        ob = total[i];
                        if( !query_temp("warquest/move_from", ob) )
                                continue;

                        room = environment(ob);

                        // 兵法辅助攻击-陷阱
                        if( query("craft/trap", room) &&
                            query("craft/trap", room) != "meng" && random(10) )
                        {
                                // 损失一营部队
                                ob->receive_damage("qi", 2000);
                                ob->receive_wound("qi", 2000);
                                if (! ob->is_busy())
                                        ob->start_busy(2 + random(2));
                                delete("craft/trap", room);
                                message_vision(HIB "$N" HIB "率领着一支蒙古突骑兵落入陷阱，损失了部分军队！.....\n" NOR, ob);
                        }

                        file = base_name(room);
                        if (file == "/d/city2/sying1")
                        {
                                if( !query_temp("warquest/attack", ob) )
                                {
                                        message_ward(CHINESE_D->chinese_date((time() - 14*365*24*60*60)) +
                                                MAG "蒙古骑兵大败宋军于襄阳！！\n" NOR);

                                        fail_kingwar();
                                        return;
                                }
                        } else
                        if (file == "/d/city2/syuanmen1")
                        {
                                if( query("defence", room)>0 && !query_temp("warquest/break", ob) )
                                        message("channel:rumor", MAG "【军情】大宋：一名" +
                                                query_temp("title", ob)+MAG"率领的蒙古突骑兵已经攻到宋军大营，"+
                                                "宋军吃紧，急待增援！！！\n" NOR, users());

                                if( query("defence", room)>0 )
                                {
                                        message_vision("$N将手中长刀一挥。兵将蚁聚，涌至城边，一边架起云梯" +
                                                "攀越城墙，一边掘土而进。\n", ob);
                                        set_temp("warquest/break", 1, ob);
                                        ob->command("break");
                                } else
                                if( query_temp("warquest/break", ob)){
                                        message("channel:rumor", MAG "【军情】大宋：宋军大营" +
                                                MAG "被蒙古骑兵攻破，形势危急！！！\n" NOR, users());
                                        delete_temp("warquest/break", ob);
                                }

                        }

                        if (! living(ob) || ob->is_fighting() ||
                            query_temp("warquest/attack", ob) ||
                            query_temp("warquest/break", ob) ||
                                ob->is_busy()) continue;

                        if (! undefinedp(move_way[file]))
                        {
                                set_temp("warquest/move_from", file, ob);
                                GO_CMD->main(ob, move_way[file]);
                        } else
                        if( query_temp("warquest/move_from", ob) )
                                ob->move(query_temp("warquest/move_from", ob));

                        message_vision(HIB "$N" HIB "率领着一支蒙古突骑兵缓缓地朝宋军大营移动着.....\n" NOR, ob);
                        ob->start_busy(2 + random(2));
                }
        }

        total = song_info->generals;
        if (arrayp(total) && sizeof(total))
        {
                total=filter_array(total,(:objectp($1) && query_temp("warquest/purchase", $1):));
                if (! sizeof(total)) return;

                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                song_info->generals -= ({ total[i] });
                                continue;
                        }
                        if (! living(total[i]))
                                continue;

                        ob = total[i];
                        room = environment(ob);
                        file = base_name(room);

                        if( query_temp("warquest/move", ob) == "forward" )
                        {
                                move_way = forward_way;
                                if (file == "/d/xiangyang/eastgate1")
                                {
                                        //if( query_temp("warquest/purchase", ob) != "forage" )
                                        if( 1 )
                                        {
                                                if (! ob->is_busy())
                                                ob->start_busy(8 + random(8));
                                                switch(query_temp("warquest/purchase", ob) )
                                                {
                                                case "weapon" :
                                                        tell_object(ob, HIY "你率领的大军到达了襄阳城，命令部下开始购置兵器和盔甲，\n" +
                                                                        HIY "你将前线所需兵甲载上马车，又立刻开始了行军的奔程....\n" NOR);
                                                        break;
                                                case "horse"  :
                                                        tell_object(ob, HIY "你率领的大军到达了襄阳城，命令部下开始购置战马，\n" +
                                                                        HIY "你将前线所需战马全部带上，又立刻开始了行军的奔程....\n" NOR);
                                                        break;
                                                case "stone"  :
                                                        tell_object(ob, HIY "你率领的大军到达了襄阳城，命令部下开始购置石头和檑木，\n" +
                                                                        HIY "你将前线所需石木载上马车，又立刻开始了行军的奔程....\n" NOR);
                                                        break;
                                                case "arrow"  :
                                                        tell_object(ob, HIY "你率领的大军到达了襄阳城，命令部下开始购置羽箭，\n" +
                                                                        HIY "你将前线所需羽箭载上马车，又立刻开始了行军的奔程....\n" NOR);
                                                        break;
                                                case "enlist" :
                                                        tell_object(ob, HIY "你率领的大军到达了襄阳城，命令部下开始招募新兵，\n" +
                                                                        HIY "你带上所招募的新兵，又立刻开始了行军的奔程....\n" NOR);
                                                        break;
                                                case "forage" :
                                                        tell_object(ob, HIY "你率领的解粮大军终于到达了襄阳城，" +
                                                                        HIY "你将粮草载上马车，又立刻开始了行军的奔程....\n" NOR);
                                                        break;
                                                default :
                                                        break;
                                                }
                                                set_temp("warquest/move", "backward", ob);
                                                move_way = backward_way;
                                        }
                                } else
                                if (file == "/d/city2/chengmen")
                                {
                                        if (! ob->is_busy())
                                        ob->start_busy(5 + random(5));
                                        message_vision(HIY "$N" HIY "率领的解粮大军终于到达了京师汴梁，" +
                                                "$N" HIY "将粮草载上马车，又立刻开始了行军的奔程....\n" NOR, ob);
                                        set_temp("warquest/move", "backward", ob);
                                        move_way = backward_way;
                                }
                        } else
                        if( query_temp("warquest/move", ob) == "backward"){
                                move_way = backward_way;
                                if (file == "/d/city2/sying1")
                                {
                                        switch(query_temp("warquest/purchase", ob) )
                                        {
                                                case "weapon" :
                                                        message_vision(HIY "$N" HIY "率领的购置兵甲大军终于到达了襄阳军营，\n" +
                                                                "$N" HIY "的兵甲及时支援了大军的军备....\n" NOR, ob);
                                                        addn_temp("warquest/reward", 500, ob);
                                                        count = song_info->economy / 20 + random(1000);
                                                        song_info->weapons += count;
                                                        tell_object(song_info->marshal, HIY "购置兵甲的军马到了，你的军备又增加了！\n" NOR);
                                                        break;
                                                case "horse"  :
                                                        message_vision(HIY "$N" HIY "率领的购置战马大军终于到达了襄阳军营，\n" +
                                                                "$N" HIY "的羽箭及时支援了大军的军备....\n" NOR, ob);
                                                        addn_temp("warquest/reward", 500, ob);
                                                        count = song_info->economy / 40 + random(500);
                                                        song_info->horses += count;
                                                        tell_object(song_info->marshal, HIY "购置战马的军马到了，你的军备又增加了！\n" NOR);
                                                        break;
                                                case "stone"  :
                                                        message_vision(HIY "$N" HIY "率领的购置石木大军终于到达了襄阳军营，\n" +
                                                                "$N" HIY "的羽箭及时支援了大军的军备....\n" NOR, ob);
                                                        addn_temp("warquest/reward", 500, ob);
                                                        count = song_info->economy / 20 + random(1000);
                                                        song_info->stones += count;
                                                        tell_object(song_info->marshal, HIY "购置石木的军马到了，你的军备又增加了！\n" NOR);
                                                        break;
                                                case "arrow"  :
                                                        message_vision(HIY "$N" HIY "率领的购置羽箭大军终于到达了襄阳军营，\n" +
                                                                "$N" HIY "的羽箭及时支援了大军的军备....\n" NOR, ob);
                                                        addn_temp("warquest/reward", 500, ob);
                                                        count = song_info->economy / 20 + random(1000);
                                                        song_info->arrows += count;
                                                        tell_object(song_info->marshal, HIY "购置羽箭的军马到了，你的军备又增加了！\n" NOR);
                                                        break;
                                                case "enlist" :
                                                        message_vision(HIY "$N" HIY "率领的招募新兵大军终于到达了襄阳军营，\n" +
                                                                "$N" HIY "的新兵及时支援了大军的兵源....\n" NOR, ob);
                                                        addn_temp("warquest/reward", 500, ob);
                                                        count = song_info->economy / 20 + random(1000);
                                                        song_info->soilders += count;
                                                        tell_object(song_info->marshal, HIY "招募新兵的军马到了，你的新兵又增加了！\n" NOR);
                                                        break;
                                                case "forage" :
                                                        message_vision(HIY "$N" HIY "率领的解粮大军终于到达了襄阳军营，\n" +
                                                                "$N" HIY "的粮草及时支援了大军的补给....\n" NOR, ob);

                                                        addn_temp("warquest/reward", 500, ob);
                                                        count = song_info->economy / 5 + random(10000);
                                                        song_info->forages += count;
                                                        tell_object(song_info->marshal, HIY "押解粮草的军马到了，你的补给又增加了！\n" NOR);
                                                        break;
                                                default :
                                                        break;
                                        }
                                        delete_temp("warquest/purchase", ob);
                                        delete_temp("warquest/move", ob);
                                        delete_temp("warquest/move_from", ob);
                                        delete_temp("warquest/quest", ob);

                                        if (! ob->is_busy())
                                                ob->start_busy(5 + random(5));

                                        continue;
                                }
                        }
                        if (! living(ob) || ob->is_fighting() ||
                                ob->is_busy()) continue;

                        if (! undefinedp(move_way[file]))
                        {
                                set_temp("warquest/move_from", file, ob);
                                GO_CMD->main(ob, move_way[file]);
                        } else
                        if( query_temp("warquest/move_from", ob) )
                                ob->move(query_temp("warquest/move_from", ob));

/*
                        switch(query_temp("warquest/purchase", ob) )
                        {
                        case "weapon" :
                        case "horse"  :
                        case "stone"  :
                        case "arrow"  :
                                message_vision(YEL "$N率领着购置军备大队人马不分昼夜地行进着.....\n", ob);
                                break;
                        case "enlist" :
                                message_vision(YEL "$N率领着招募新兵的大队人马不分昼夜地行进着.....\n", ob);
                                break;
                        case "forage" :
                                message_vision(YEL "$N率领着押运粮草大队人马不分昼夜地行进着.....\n", ob);
                                break;
                        default :
                                break;
                        }
*/
                        if (! ob->is_busy())
                        ob->start_busy(2 + random(2));
                }
        }
        return;
}

// 处理军需物资消耗
void auto_cost()
{
        int i, count = 0;
        object *total;

        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                SCHEDULE_D->delete_event(xh_event_id);
                return;
        }

        total = meng_info->generals;
        if (arrayp(total) && sizeof(total))
        {
                if (meng_info->moneys > 0 || meng_info->forages > 0)
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                meng_info->generals -= ({ total[i] });
                                continue;
                       }

                        count=query_temp("warquest/group", total[i]);
                        if (! count) continue;

                        if (meng_info->moneys > 0)
                                meng_info->moneys -= count * 200;
                        if (meng_info->moneys < 0)
                                meng_info->moneys = 0;
                        if (meng_info->forages > 0)
                                meng_info->forages -= count * 200;
                        if (meng_info->forages < 0)
                                meng_info->forages = 0;
                }
        }

        total = song_info->generals;
        total=filter_array(total,(:objectp($1) && query_temp("warquest/group", $1):));
        if (arrayp(total) && sizeof(total))
        {
                if (song_info->moneys > 0 || song_info->forages > 0)
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                        {
                                song_info->generals -= ({ total[i] });
                                continue;
                        }

                        if( query_temp("warquest/group", total[i])<1 )
                                delete("warquest/group", total[i]);

                        count=query_temp("warquest/group", total[i]);
                        if (! count) continue;

                        if (song_info->moneys > 0)
                                song_info->moneys -= count * 200;
                        if (song_info->moneys < 0)
                                song_info->moneys = 0;
                        if (song_info->forages > 0)
                                song_info->forages -= count * 200;
                        if (song_info->forages < 0)
                                song_info->forages = 0;
                }
        }

        if (song_info->moneys < 1 && ! have1)
        {
                message("channel:rumor",
                        MAG "【军情】大宋：饷银短缺军队出现逃兵，士气下降！！\n" NOR, users());
                have1 = 1;
        }
        if (song_info->forages < 1 && ! have2)
        {
                message("channel:rumor",
                        MAG "【军情】大宋：粮草短缺军队出现逃兵，士气下降！！\n" NOR, users());
                have2 = 1;
        }

        return;
}

void auto_train()
{
        object *total;
        object ob, room;
        string type;
        int i;

        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                SCHEDULE_D->delete_event(xl_event_id);
                return;
        }

        total = song_info->generals;
        total=filter_array(total,(:objectp($1) && query_temp("warquest/train_begin", $1):));

        if (arrayp(total) && sizeof(total))
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! living(total[i])) continue;

                        ob = total[i];
                        room = environment(ob);

                        type=query_temp("warquest/train", ob);
                        if (! type)
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob, "元帅并没有分派给你训练队伍的命令！\n");
                                continue;
                        }

                        if( !room || !query("train", room )
                            || query("train", room) != type )
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob, "请你到指定的兵营里面训练新兵！\n");
                                continue;
                        }

                        if (song_info->forages < 12000)
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob,"由于粮草不足，军队新兵的训练被迫终止！\n");

                                tell_object(song_info->marshal,
                                        HIY "由于粮草不足，你的队伍被迫终止了训练！\n" NOR);
                                continue;
                        }

                        if (song_info->soilders < 200)
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob,"由于兵源不足，军队无新兵可训练！\n");
                                tell_object(song_info->marshal,
                                        HIY "由于兵源不足，你的队伍被迫终止了训练新兵！\n" NOR);
                                continue;
                        }

                        if (song_info->weapons < 400)
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob,"由于兵甲不足，军队新兵的训练被迫终止！\n");
                                tell_object(song_info->marshal,
                                        HIY "由于兵器不足，你的队伍被迫终止了训练新兵！\n" NOR);
                                continue;
                        }

                        if ((type == "archer" || type == "cavalry") &&
                            song_info->horses < 200)
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob,"由于战马不足，军队新兵的训练被迫终止！\n");
                                tell_object(song_info->marshal,
                                        HIY "由于战马不足，你的队伍被迫终止了训练新兵！\n" NOR);
                                continue;
                        }

                        if( query_temp("warquest/group", ob)>query("degree_jungong", ob) )
                        {
                                delete_temp("warquest/train_begin", ob);
                                tell_object(ob,"你带兵的能力不足，训练不了更庞大精锐的队伍了！\n");

                                tell_object(song_info->marshal,
                                        HIY "你又训练出一支的精锐部队了！\n" NOR);
                                continue;
                        }

                        if( random(query("degree_jungong", ob))>1 )
                        {
                                message_vision(HIW "$N将手中令旗一挥，新兵开始集结，" +
                                        "开始排列着不同的阵形，忽又散开，\n合时井然有序，分" +
                                        "时杂而不乱，看来$N真乃深谙用兵之道的良将啊！\n" NOR, ob);

                                addn("eff_qi", 200, ob);
                                song_info->soilders -= 200;
                                song_info->weapons -= 400;
                                if (type == "archer" || type == "cavalry")
                                        song_info->horses -= 200;
                        } else
                                message_vision(HIY "$N将手中令旗一挥，可是新兵好象乱哄哄的，" +
                                        "根本不听$N的指挥调遣，\n$N直气得吹胡子瞪眼！！！\n" NOR, ob);
                        // 粮草额外消耗
                        song_info->forages -= 20;
                }
        }
        return;
}

int check_out(object me)
{
        object ob;
//      mapping my;
        string msg;
//      string room;

        tell_object(me, HIR "\n你乘着混乱，逃回元帅大营，又饥有渴，已到半昏迷状态！\n" NOR);
        if (ob = me->query_last_damage_from())
        {
                msg = MAG + me->name(1) + MAG "的军队被" + ob->name(1) + MAG "的军队杀的全军覆没，一人逃回大营。" NOR;
        } else
                msg = MAG + me->name(1) + MAG "的军队全军覆没，一人逃回宋军大营。" NOR;

        message("channel:rumor", MAG "【军情】大宋：" + msg + "\n" NOR, users());

        me->move("/d/city2/sying1");
        message("vision", "一个黑影倏的窜了过来，随即就是“啪”的"
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
           message("channel:rumor", MAG "【军情】大宋：" + MAG + me->name(1) + "在战场上临阵脱逃。\n", users());
        restore_status(me);

        if (arrayp(song_info->generals) && sizeof(song_info->generals))
                song_info->generals -= ({ me });

        tell_object(me, "你一口气逃出了战场，来到扬州中央广场。\n");

        // continue run quit function
        me->move("/d/city/guangchang");
        message("vision", "只见" + me->name() + "慌里慌张的跑了过来。\n",
                environment(me), ({ me }));

        ip_numbers -= ({ query_ip_number(me) });
        return 1;
}

int general_die(object me)
{
        delete_temp("warquest", me);
        message_ward(CHINESE_D->chinese_date((time()-14*365*24*60*60)) +
                MAG"，宋军将领"HIR+query("name", me)+"("+query("id", me)+")"NOR+
                MAG "战死沙场，以身殉国！！\n" NOR);

        if (arrayp(song_info->generals) && sizeof(song_info->generals))
                song_info->generals -= ({ me });

        ip_numbers -= ({ query_ip_number(me) });
        return 0;
}

void fail_kingwar()
{
        object *total;
        int i;

        remove_enemy();
        message_ward(CHINESE_D->chinese_date((time() - 14*365*24*60*60)) +
                MAG "宋军被蒙古军队击败了，大宋派出使者割地求和！！\n" NOR);

        if (objectp(song_info->marshal))
        {
                restore_status(song_info->marshal);
                song_info->marshal->move("/d/city/guangchang");
                message("vision", "只见" + song_info->marshal->name() + "走了过来。\n",
                        environment(song_info->marshal), ({ song_info->marshal }));
                song_info->marshal->apply_condition("junquest_fail", 50);
        }

        total = song_info->generals;
        total = filter_array(total, (: objectp($1) && userp($1) :));
        if (arrayp(total) && sizeof(total))
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                                continue;
                        restore_status(total[i]);
                        total[i]->move("/d/city/guangchang");
                        message("vision", "只见" + total[i]->name() + "走了过来。\n",
                                environment(total[i]), ({ total[i] }));
                }
        }
        restore_kingwar();
        return;
}

void win_kingwar()
{
//      object *total;
//      int i;

        remove_enemy();
        message_ward(CHINESE_D->chinese_date((time() - 14*365*24*60*60)) +
                MAG "宋军英勇的击败了蒙古军队，迫使蒙古军队向大宋求和！\n" NOR);
        give_bouns();
        restore_kingwar();
        return;
}

void finish_kingwar()
{
        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                SCHEDULE_D->delete_event(wc_event_id);
                return;
        }

        remove_enemy();
        message_ward(CHINESE_D->chinese_date((time() - 14*365*24*60*60)) +
                MAG + "宋军经过艰苦的抵抗，使得蒙古军队久攻不下，终于撤退了！\n" NOR);
        give_bouns();
        restore_kingwar();
        return;
}

void remove_enemy()
{
        object *enemys;
        int j;

        if (arrayp(enemys = children("/d/city2/meng/kehan")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (enemys[j]->is_fighting())
                        {
                                enemys[j]->remove_all_killer();
                        }
                        tell_room(environment(enemys[j]), HIW "只见" + enemys[j]->name() +
                                  "突然哈哈大笑几声后，率领军队不见了！\n");
                        destruct(enemys[j]);
                }
        }
        if (arrayp(enemys = children("/d/city2/meng/mengj")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (enemys[j]->is_fighting())
                        {
                                enemys[j]->remove_all_killer();
                                tell_room(environment(enemys[j]), HIW "只见" + enemys[j]->name() +
                                          "突然哈哈大笑几声，迅速攻出几招，跳出战圈率领军队不见了。\n");
                        }
                        else {
                                tell_room(environment(enemys[j]), HIW "只见" + enemys[j]->name() +
                                          "突然脸色大喜，急急忙忙地率领军队不见了。\n");
                        }
                        destruct(enemys[j]);
                }
        }
        if (arrayp(enemys = children("/d/city2/meng/mengb")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (enemys[j]->is_fighting())
                        {
                                enemys[j]->remove_all_killer();
                                tell_room(environment(enemys[j]), HIW "只见" + enemys[j]->name() +
                                        "突然哈哈大笑几声，迅速攻出几招，跳出战圈率领军队不见了。\n");
                        }
                        else {
                                tell_room(environment(enemys[j]), HIW "只见" + enemys[j]->name()
                                                  + "突然脸色大喜，急急忙忙地率领军队不见了。\n");
                        }
                        destruct(enemys[j]);
                }
        }

        if (arrayp(enemys = children("/d/city2/song/songb")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (enemys[j]->is_fighting())
                        {
                                enemys[j]->remove_all_killer();
                                tell_room(environment(enemys[j]), HIW "只见" + enemys[j]->name()
                                                  + "突然面色一变，迅速攻出几招，跳出战圈率领军队不见了。\n");
                        }
                        else {
                                tell_room(environment(enemys[j]), HIW "只见" + enemys[j]->name()
                                                  + "掐值一算，突然脸色大变，急急忙忙地率领军队不见了。\n");
                        }
                        song_info->generals -= ({ enemys[j] });
                        destruct(enemys[j]);
                }
        }

        if (arrayp(enemys = children("/d/city2/npc/jianjun")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (environment(enemys[j]) && environment(enemys[j])->is_character())
                                continue;

                        destruct(enemys[j]);
                }
        }

        if (arrayp(enemys = children("/d/city2/meng/horse")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (environment(enemys[j]) && environment(enemys[j])->is_character())
                                continue;

                        destruct(enemys[j]);
                }
        }

        if (arrayp(enemys = children("/d/city2/song/horse")) && sizeof(enemys))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (environment(enemys[j]) && environment(enemys[j])->is_character())
                                continue;

                        destruct(enemys[j]);
                }
        }
        get_object("/d/city2/majiu")->reset();
        return;
}

// send message out
void message_ward(string msg)
{
        // CHANNEL_D->do_channel(this_object(), "rumor", msg);
        message("channel:rumor", MAG "【史记】" + msg + NOR, users());
}

// remove overide function
void restore_status(object me)
{
        object bingfu, lingjian, zhanma, kaijia;

        if (objectp(bingfu = present("bing fu", me)))
                destruct(bingfu);

        if (objectp(lingjian = present("ling jian", me)))
                destruct(lingjian);

        if (objectp(zhanma = present("zhan ma", me)))
                destruct(zhanma);

        if (objectp(zhanma = present("shizi ma", me)))
                destruct(zhanma);

        if (objectp(kaijia = present("kai jia", me)))
                destruct(kaijia);

        me->delete_override("quit");
        me->delete_override("die");
        delete_temp("warquest", me);
        delete_temp("title", me);
        me->remove_all_enemy(1);
        me->remove_all_killer();
        me->receive_damage("qi", 0);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("eff_qi",  me), me);
        // me->clear_condition();

        return;
}

void restore_kingwar()
{
        // set_heart_beat(0);

        if (mg_event_id)
                SCHEDULE_D->delete_event(mg_event_id);
        if (sc_event_id)
                SCHEDULE_D->delete_event(sc_event_id);
        if (xl_event_id)
                SCHEDULE_D->delete_event(xl_event_id);
        if (yd_event_id)
                SCHEDULE_D->delete_event(yd_event_id);
        if (xh_event_id)
                SCHEDULE_D->delete_event(xh_event_id);
        if (ap_event_id)
                SCHEDULE_D->delete_event(ap_event_id);
        if (wc_event_id)
                SCHEDULE_D->delete_event(wc_event_id);
        if (xt_event_id)
                SCHEDULE_D->delete_event(xt_event_id);

        meng_info->economy = 0;
        meng_info->moneys = 0;
        meng_info->forages = 0;
        meng_info->stones = 0;
        meng_info->arrows = 0;
        meng_info->horses = 0;
        meng_info->weapons = 0;
        meng_info->soilders = 0;
        meng_info->marshal = 0;
        meng_info->generals = 0;
        meng_info->count = 0;
        song_info->economy = 0;
        song_info->moneys = 0;
        song_info->forages = 0;
        song_info->stones = 0;
        song_info->arrows = 0;
        song_info->horses = 0;
        song_info->weapons = 0;
        song_info->soilders = 0;
        song_info->marshal = 0;
        song_info->generals = 0;
        song_info->count = 0;
        have1 = 0;
        have2 = 0;
        start_time = 0;
        valid_check = 0;
        return;
}

void give_bouns()
{
        int reward/*, rew*/, pot, exp, mar, jungong, i/*, j*/;
        string prompt;
//      object me;
        object *total/*, ob*/;
//      int war_times;

        total = song_info->generals;
        if (! objectp(song_info->marshal))
        {
                if (arrayp(total) && sizeof(total) > 0)
                {
                        for (i = 0; i < sizeof(total); i++)
                        {
                                if (! objectp(total[i]))
                                        continue;
                                restore_status(total[i]);
                        }
                }
                return;
        }

        //rew = song_info->marshal->query("jungong");
        reward = query_temp("warquest/reward", song_info->marshal);

        message("channel:rumor", MAG "【京城】" +
                CHINESE_D->chinese_date((time() - 14 * 365 * 24 * 60 * 60)) +
                "......\n" NOR,
                users());

        reward += 200;
        if (reward > 10000) reward = 10000;
        //if (rew > 200000) rew = 200000;
        // exp = (reward / 2 + random(reward / 2)) * (song_info->marshal->query("degree_jungong") + 1) * 10;
        exp = reward * (query("degree_jungong", song_info->marshal) + 1) * 9;
        pot = exp / 3;
        mar = pot / 3;

        jungong = exp / 1000;
#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(song_info->marshal))
                jungong *= 2;
#endif

        addn("jungong", jungong, song_info->marshal);

        prompt = "因抗蒙有功";
        GIFT_D->delay_war_bonus(song_info->marshal,
                ([ "prompt" : prompt, "exp" : exp, "pot" : pot, "mar" : mar, "gold" : 1000, "percent":200, ]));

/*
        if (random(2)) ob = new("/clone/fam/gift/int3");
        else ob = new("/clone/fam/gift/con3");
        ob->move(song_info->marshal, 1);
        if (random(2)) ob = new("/clone/fam/gift/str3");
        else ob = new("/clone/fam/gift/dex3");
        ob->move(song_info->marshal, 1);
        for (j = 0; j < 5; j++)
        {
                ob = new("/clone/goods/sun");
                ob->move(song_info->marshal, 1);
                ob = new("/clone/goods/moon");
                ob->move(song_info->marshal, 1);
        }

        ob = new("/clone/gift/puti-zi");
        ob->set_amount(2);
        ob->move(song_info->marshal, 1);
        ob = new("/clone/gift/tianxiang");
        ob->move(song_info->marshal, 1);
        ob = new("/clone/gift/jiuzhuan");
        ob->move(song_info->marshal, 1);
        ob = new("/clone/gift/xuanhuang");
        ob->move(song_info->marshal, 1);
*/

        message("channel:rumor", HIY "【京城】奉天承命，皇帝诏曰：\n" +
               "            " + song_info->marshal->name(1) + HIY "抗蒙有功，赏黄金千两，绸缎五百匹，美女十名，" +
                "记军功 " HIR + chinese_number(jungong) +
                HIY " 策，钦此！\n\n" NOR, users());

        tell_object(song_info->marshal, HIW "因抗蒙有功，你获得了 " + HIR + chinese_number(jungong) +
                          HIW " 策军功！！\n" NOR);

        restore_status(song_info->marshal);
        song_info->marshal->move("/d/city/guangchang");
        message("vision", "只见" + song_info->marshal->name() + "走了过来。\n",
                environment(song_info->marshal), ({ song_info->marshal }));

        if (arrayp(total) && sizeof(total) > 0)
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                                continue;
                        if (total[i] == song_info->marshal)
                                continue;

                        tell_object(total[i], HIR "蒙古军队撤兵了，准备班师回朝吧！\n" NOR);

                        //rew = total[i]->query("jungong");
                        reward=query_temp("warquest/reward", total[i]);
                        reward += 200;
                        if (reward < 2)
                        {
                                restore_status(total[i]);
                                continue;
                        }
                        if (reward > 10000) reward = 10000;
                        //if (rew > 200000) rew = 200000;
                        // exp = (reward / 2 + random(reward / 2)) * (total[i]->query("degree_jungong") + 1) * 10;
                        exp = reward*(query("degree_jungong", total[i])+1)*9;
                        pot = exp / 3;
                        mar = pot / 3;
                        jungong = exp / 1000;
#ifdef DB_SAVE
                        if (MEMBER_D->is_double_reward(total[i]))
                                jungong *= 2;
#endif

                        addn("jungong", jungong, total[i]);

                        GIFT_D->delay_war_bonus(total[i],
                                ([ "prompt" : prompt, "exp" : exp, "pot" : pot, "mar" : mar, "gold" : 100, "percent" : 200, ]));

/*
                        if (random(2)) ob = new("/clone/fam/gift/int3");
                        else ob = new("/clone/fam/gift/con3");
                        ob->move(total[i], 1);
                        if (random(2)) ob = new("/clone/fam/gift/str3");
                        else ob = new("/clone/fam/gift/dex3");
                        ob->move(total[i], 1);
                        for (j = 0; j < 3; j++)
                        {
                                if( random(2) )
                                        ob = new("/clone/goods/sun");
                                else
                                        ob = new("/clone/goods/moon");
                                ob->move(total[i], 1);
                        }

                       if( reward >= 2000 && time()-query_temp("warquest/time", total[i]) >= 600 )
                        {
                                ob = new("/clone/gift/puti-zi");
                                ob->set_amount(2);
                                ob->move(total[i], 1);
                                ob = new("/clone/gift/tianxiang");
                                ob->move(total[i], 1);
                                ob = new("/clone/gift/jiuzhuan");
                                ob->move(total[i], 1);
                                ob = new("/clone/gift/xuanhuang");
                                ob->move(total[i], 1);
                        }
*/

                        tell_object(total[i], HIW "因抗蒙有功，你获得了 " + HIR + chinese_number(jungong) +
                                              HIW " 策军功！！\n" NOR);

                        restore_status(total[i]);
                        total[i]->move("/d/city/guangchang");
                        message("vision", "只见" + total[i]->name() + "走了过来。\n",
                                environment(total[i]), ({ total[i] }));
                }
        }
        return;
}

int continue_kingwar(string arg)
{
        object general;
        object room;

        if (! objectp(meng_info->marshal) ||
            ! objectp(song_info->marshal))
        {
                SCHEDULE_D->delete_event(mg_event_id);
                SCHEDULE_D->delete_event(sc_event_id);
                return 0;
        }

        if (! arg) return 0;
        if (arg == "meng")
        {
                room = get_object("/d/city2/mying1");
                if (meng_info->forages > 240000 && meng_info->moneys > 240000 &&
                    meng_info->weapons > 48000 && meng_info->horses > 24000 &&
                    meng_info->soilders > 24000)
                {
                        for (int i = 0; i < 4; i++)
                        {
                                general = new("/d/city2/meng/mengb");
                                general->move(room);
                                init_general(general);
                                set_temp("warquest/quest", "攻打宋营，入侵大宋", general);
                        }
                }
        } else
        if (arg == "song")
        {
                room = get_object("/d/city2/sying1");
                if (song_info->forages > 100000 && song_info->moneys > 100000 &&
                    song_info->soilders > 24000)
                {
                        general = new("/d/city2/song/songb");
                        general->move(room);
                        init_general(general);
                        tell_object(song_info->marshal,
                                HIR "朝廷派遣支援前线的一名宋军将领到了，赶快派遣他任务吧！！！\n" NOR);
                }
        }

        return 1;
}

string do_assign(object me, string arg)
{
        object *inv;
        object ob;
        object ling, horse;
        string who, what;
        int i, count;

        if (! arg || sscanf(arg, "%s to %s", who, what) != 2)
                return "请用 paiqian sb to do sth. 来发布号令！\n";

        if (who != "all" && ! objectp(ob = present(who, environment(me))))
                return "这里没有你可以调度的这名将领！\n";

        if (who == "all" && (what != "battle" || what != "ST-chuzheng"))
                return "请用 paiqian sb to do sth. 来发布号令！\n";

        if( query_temp("warquest/party", ob) != "song" )
                return "对方不是宋军，如何供你调度？！\n";

        /*
        if( query("degree_jungong", ob)<1 )
                return "对方的统帅才能太低了，难堪大用！\n";
        */

        if (ob == me)
                return "自己命令自己？你不嫌累啊你？！\n";

        if( query("id", ob) == "jianjun" )
                return "你不可以命令大宋监军去做别的事情！\n";

        if( query("eff_qi", ob) < query("max_qi", ob) )
                return "你还是等对方养好伤再派遣任务吧。\n";

        switch(what)
        {
        case "battle":
        case "chuzheng":
                message_vision(HIR "$N略一沉思，，而后果敢的下令道：本帅决定迎战蒙古大军，\n"
                               "各位将军请即刻调派人马随同本帅出征！如有违令，军法论处！\n" NOR, me);

                inv = all_inventory(environment(me));
                for (i=sizeof(inv)-1; i>=0; i--)
                if( query_temp("warquest/group", inv[i])>0 )
                {
                        if( query_temp("warquest/purchase", inv[i]) ||
                            query_temp("warquest/guard", inv[i]) ||
                            (userp(inv[i]) && inv[i] != me))
                                continue;

                        inv[i]->set_leader(me);
                        set_temp("warquest/battle", 1, inv[i]);
                        set_temp("warquest/quest", "军队出征，迎战蒙军", inv[i]);
                }
                return "众将大声应道：末将遵命！！\n";
                break;
        case "recon": // reconnaissance
        case "zhencha" :
                if (! userp(ob))
                        return "此项任务艰巨,你只能调度玩家去完成！\n";

                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "蒙古大军攻击将至，\n命你火速前往蒙古军营侦察敌情以便本帅" +
                               "知己知彼，如有延误，军法论处！\n" NOR, me, ob);
                set_temp("title", HIY"大宋侦察营统领"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/recon", 1, ob);
                set_temp("warquest/quest", "深入蒙境，侦察敌情", ob);
                // ob->command("recon");
                break;
        case "enlist":
        case "zhaomu-xinbing" :
                /*
                if (! userp(ob))
                        return "此项任务艰巨,你只能调度玩家去完成！\n";
                */
                count = song_info->economy / 2 + 1000;
                if (song_info->moneys < count)
                        return "军中银两已经不多，不足以用来支付招募新兵的开支！\n";

                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中兵员匮乏，\n命你火速率部，赶去襄阳城内招募新兵" +
                               "至军中，如有延误，军法论处！\n" NOR, me, ob);
                set_temp("title", HIY"大宋军备营统领"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/purchase", "enlist", ob);
                set_temp("warquest/quest", "招募新兵，补充兵源", ob);
                song_info->moneys -= count;
                ob->command("stock");
                break;
        case "stock-weapon":
        case "gouzhi-bingjia" :
                /*
                if (! userp(ob))
                        return "此项任务艰巨,你只能调度玩家去完成！\n";
                */
                count = song_info->economy / 2 + 1000;
                if (song_info->moneys < count)
                        return "军中银两已经不多，不足以用来支付购置兵甲的开支！\n";

                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中兵器和盔甲匮乏，\n命你火速率部，赶去襄阳城内采购兵器和盔甲" +
                               "至军中，如有延误，军法论处！\n" NOR, me, ob);
                set_temp("title", HIY"大宋军备营统领"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/purchase", "weapon", ob);
                set_temp("warquest/quest", "购置兵甲，补充军备", ob);
                song_info->moneys -= count;
                ob->command("stock");
                break;
        case "stock-arrow":
        case "gouzhi-yujian" :
                /*
                if (! userp(ob))
                        return "此项任务艰巨,你只能调度玩家去完成！\n";
                */
                count = song_info->economy / 2 + 1000;
                if (song_info->moneys < count)
                        return "军中银两已经不多，不足以用来支付购置羽箭的开支！\n";

                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军营箭楼羽箭匮乏，\n命你火速率部，赶去襄阳城内采购羽箭" +
                               "至军中，如有延误，军法论处！\n" NOR, me, ob);
                set_temp("title", HIY"大宋军备营统领"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/purchase", "arrow", ob);
                set_temp("warquest/quest", "购置羽箭，补充军备", ob);
                song_info->moneys -= count;
                ob->command("stock");
                break;
        case "stock-horse":
        case "gouzhi-zhanma" :
                /*
                if (! userp(ob))
                        return "此项任务艰巨,你只能调度玩家去完成！\n";
                */
                count = song_info->economy / 2 + 1000;
                if (song_info->moneys < count)
                        return "军中银两已经不多，不足以用来支付购置战马的开支！\n";

                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中战马匮乏，\n命你火速率部，赶去襄阳城内采购战马" +
                               "至军中，如有延误，军法论处！\n" NOR, me, ob);
                set_temp("title", HIY"大宋军备营统领"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/purchase", "horse", ob);
                set_temp("warquest/quest", "购置战马，补充军备", ob);
                song_info->moneys -= count;
                ob->command("stock");
                break;
        case "stock-stone":
        case "gouzhi-shimu" :
                /*
                if (! userp(ob))
                        return "此项任务艰巨,你只能调度玩家去完成！\n";
                */
                count = song_info->economy / 2 + 1000;
                if (song_info->moneys < count)
                        return "军中银两已经不多，不足以用来支付购置石木的开支！\n";

                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中滚石和檑木匮乏，\n命你火速率部，赶去襄阳城内采购石头和木材" +
                               "至军中，如有延误，军法论处！\n" NOR, me, ob);
                set_temp("title", HIY"大宋军备营统领"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/purchase", "stone", ob);
                set_temp("warquest/quest", "购置石木，补充军备", ob);
                song_info->moneys -= count;
                ob->command("stock");
                break;
        case "guard-xiangyang":
        case "shouwei-xiangyang" :
                if (! userp(ob))
                        return "此项任务艰巨,你只能调度玩家去完成！\n";
                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来蒙古骑兵常骚扰我大宋襄阳城，\n命你火速率部，赶去襄阳驻守城池" +
                               "，如有延误，军法论处！\n" NOR, me, ob);
                set_temp("title", HIY"大宋后防营统领"NOR, ob);
                /*
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                */
                set_temp("warquest/guard", 1, ob);
                set_temp("warquest/quest", "守卫襄阳，稳固后方", ob);
                // ob->command("guard");
                ob->move("/d/wuguan/guofu_dating");
                break;
        case "yayun-liangcao":
        case "escort-forage" :
                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中粮草匮乏，\n命你火速率部，在半月内将京师供应之粮草押解" +
                               "至军中，如有延误，军法论处！\n" NOR, me, ob);

                set_temp("title", HIY"大宋军备营统领"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/purchase", "forage", ob);
                set_temp("warquest/quest", "押运粮草，补充军备", ob);
                ob->command("stock");
                break;

        case "xunlian-qibing":
        case "train-cavalry":
                if( query_temp("warquest/train", ob )
                 && query_temp("warquest/train", ob) != "cavalry" )
                        return "对方已经另有他职了，请重新选派将领吧！\n";

                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中几无能战之师，\n命你加紧训练一支精锐骑兵，以备不时之需，" +
                               "不得有误！\n" NOR, me, ob);

                set_temp("title", HIR"大宋车骑营统领"NOR, ob);
                if (! present("zhan ma", ob))
                {
                        UNRIDE_CMD->main(ob);
                        horse = new("/d/city2/song/horse");
                        if (horse->move(environment(ob)))
                                RIDE_CMD->do_ride(ob, horse);
                        else destruct(horse);
                }
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/train", "cavalry", ob);
                set_temp("warquest/quest", "训练骑兵，作战准备", ob);
                ob->command("drill");
                break;

        case "train-infantry":
        case "xunlian-bubing":
                if( query_temp("warquest/train", ob )
                 && query_temp("warquest/train", ob) != "infantry" )
                        return "对方已经另有他职了，请重新选派将领吧！\n";

                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中几无能战之师，\n命你加紧训练一支精锐步兵，以备不时之需，" +
                               "不得有误！\n" NOR, me, ob);
                set_temp("title", HIW"大宋步兵营统领"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/train", "infantry", ob);
                set_temp("warquest/quest", "训练步兵，作战准备", ob);
                ob->command("drill");
                break;

        case "train-archer":
        case "xunlian-gongnu":
                if( query_temp("warquest/train", ob )
                 && query_temp("warquest/train", ob) != "archer" )
                        return "对方已经另有他职了，请重新选派将领吧！\n";

                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中几无能战之师，\n命你加紧训练一支精锐弓箭手，以备不时之需，" +
                               "不得有误！\n" NOR, me, ob);
                set_temp("title", HIB"大宋神弩营统领"NOR, ob);

                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }

                set_temp("warquest/train", "archer", ob);
                set_temp("warquest/quest", "训练弓兵，作战准备", ob);
                ob->command("drill");
                break;

        default:
                return "身为一军之帅，请不要滥用你的军权！\n";
        }

        return query("name", ob) + "大声应道：末将遵命！！\n";
}