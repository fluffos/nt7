// This program is a part of NITAN MudLIB
// memberd.c 会员精灵

// #pragma optimize
// #pragma save_binary

#ifdef DB_SAVE

#include <ansi.h>
#include <mudlib.h>
#include "/adm/etc/database.h"
#define GOODS_D         "/adm/daemons/goodsd"
#define VERSION         "V 2.0"

public int is_member(mixed ob);
public int is_valid_member(mixed ob);
public mixed db_query_member(mixed ob, string key);
public mixed db_find_member(string key, mixed data);
public varargs int db_create_member(mixed ob, int money, string from_id);
public int db_remove_member(mixed ob);
public int db_set_member(mixed ob, string key, mixed data);
public int db_add_member(mixed ob, string key, int num);
public varargs int db_pay_member(mixed ob, int money, string from_id);
public int db_transfer_member(mixed ob, mixed to, int value);
public string db_str(string x);


int clean_up() { return 1; }

protected int valid_caller()
{
#ifdef DEBUG
        return 1;
#else
        if (!previous_object() ||
            !is_root(previous_object()))
                return 0;
        else
                return 1;
#endif
}

void create()
{
        seteuid(ROOT_UID);
}

// 查询 ID 是否是冲值用户
public int is_member(mixed ob)
{
        mixed  ret;
        string id, sql;

        if (objectp(ob))
                id=query("id", ob);
        else
        if (stringp(ob))
                id = ob;
        else
                return 0;

        sql = sprintf("SELECT id FROM %s WHERE id = \"%s\"",
                      MEMBER_TABLE, id);

        ret = DATABASE_D->db_query(sql);

        if (!intp(ret))
                return 0;

        return ret;
}

public string db_str(string x)
{
	string xx;
	if(strlen(x)<8192)
	 xx=	 "'" + replace_string(x, "'", "''") + "'";
	else
	 xx=	 "'" + replace_string("已清空", "'", "''") + "'";

       return xx;
}



// 查询 ID 是否是有效会员
public int is_valid_member(mixed ob)
{
        mixed  ret;
        string id, sql;

        if (objectp(ob))
                id=query("id", ob);
        else
        if (stringp(ob))
                id = ob;
        else
                return 0;

        sql = sprintf("SELECT id FROM %s WHERE id = \"%s\" AND endtime > %d",
                      MEMBER_TABLE, id, time());

        ret = DATABASE_D->db_query(sql);

        if (!intp(ret))
                return 0;

        return ret;
}

// 会员双倍奖励时间
public int is_double_reward(object ob)
{
        int t;

        /*
        t = localtime(time())[2];

        if (is_valid_member(ob) &&
            t >= 20 && t < 24)
                return 1;
        t = localtime(time())[3];
        if (t >= 0 && t < 4)
                return 1;
        */

        if( query("time_reward/quest", ob) )
                return 1;

        return 0;
}

// 查询 ID 相关信息
public mixed db_query_member(mixed ob, string key)
{
        mixed  ret;
        string id, sql;

        if (objectp(ob))
                id=query("id", ob);
        else
        if (stringp(ob))
                id = ob;
        else
                return 0;

        if (!stringp(id)  || id  == "" ||
            !stringp(key) || key == "")
                return 0;

        sql = sprintf("SELECT %s FROM %s WHERE id = \"%s\"",
                      key, MEMBER_TABLE, id);

        ret = DATABASE_D->db_fetch_row(sql);

        if (arrayp(ret) && sizeof(ret))
                return ret[0];
        else
                return 0;
}

// 根据条件寻找会员
public mixed db_find_member(string key, mixed data)
{
        mixed  ret;
        string sql;

        if (!stringp(key) || key == "" || !data)
                return 0;

        if (intp(data))
                sql = sprintf("SELECT id FROM %s WHERE %s = %d",
                              MEMBER_TABLE, key, data);
        else if (mapp(data) || arrayp(data))
                sql = sprintf("SELECT id FROM %s WHERE %s = \"%s\"",
                              MEMBER_TABLE, key, save_variable(data));
        else if (stringp(data))
                sql = sprintf("SELECT id FROM %s WHERE %s = \"%s\"",
                              MEMBER_TABLE, key, data);
        else
                sql = sprintf("SELECT id FROM %s WHERE %s = %O",
                              MEMBER_TABLE, key, data);

        ret = DATABASE_D->db_all_query(sql);

        return ret;
}

// 创建新的会员
public varargs int db_create_member(mixed ob, int money, string from_id)
{
        mixed  ret;
        string id, sql;
        string payinfo;
        object target;

        if (!valid_caller())
                return 0;

        if (objectp(ob))
                id=query("id", ob);
        else
        if (stringp(ob))
                id = ob;
        else
                return 0;

        if (!stringp(id) || id == "")
                return 0;

        /*
        if (is_member(id))
                return 0;
        */

        if (!stringp(from_id) || from_id == "")
                payinfo = sprintf("你于 %s 冲值 %d $NT。\n", TIME_D->replace_ctime(time()), money);
        else
                payinfo = sprintf("你于 %s 收到 %s 的转帐 %d $NT。\n",
                                  TIME_D->replace_ctime(time()), from_id, money);

        sql = sprintf("INSERT INTO %s SET id = \"%s\", uid = \"%s\", money = %d, paytimes = 1, payinfo = \"%s\",
                      payvalue = %d, last_payvalue = %d, last_paytime = %d",
                      MEMBER_TABLE, id, id, money, payinfo, money, money, time());

        ret = DATABASE_D->db_query(sql);
        if (!intp(ret))
                return 0;

        if (objectp(target = find_player(id)))
        {
                tell_object(target, "\a", 0);
                tell_object(target, HIR + payinfo + NOR);
        }
        return ret;
}

// 删除会员
public int db_remove_member(mixed ob)
{
        mixed  ret;
        string id, sql;

        if (!valid_caller())
                return 0;

        if (objectp(ob))
                id=query("id", ob);
        else
        if (stringp(ob))
                id = ob;
        else
                return 0;

        if (!stringp(id) || id == "")
                return 0;

        sql = sprintf("DELETE FROM %s WHERE id = \"%s\"",
                      MEMBER_TABLE, id);
        ret = DATABASE_D->db_query(sql);

        if (!intp(ret))
                return 0;

        return ret;
}

// 设定会员属性
public int db_set_member(mixed ob, string key, mixed data)
{
        mixed  ret;
        string id, sql;

        if (!valid_caller())
                return 0;

        if (objectp(ob))
                id=query("id", ob);
        else
        if (stringp(ob))
                id = ob;
        else
                return 0;

        if (!stringp(id)  || id  == "" ||
            !stringp(key) || key == "")
                return 0;

        /*
        if (intp(data))
                sql = sprintf("UPDATE %s SET %s = %d WHERE id = \"%s\"",
                              MEMBER_TABLE, key, data, id);
        else if (mapp(data) || arrayp(data))
                sql = sprintf("UPDATE %s SET %s = \"%s\" WHERE id = \"%s\"",
                              MEMBER_TABLE, key, save_variable(data), id);
        else if (stringp(data))
                sql = sprintf("UPDATE %s SET %s = \"%s\" WHERE id = \"%s\"",
                              MEMBER_TABLE, key, data, id);
        else
                sql = sprintf("UPDATE %s SET %s = %O WHERE id = \"%s\"",
                              MEMBER_TABLE, key, data, id);

        */




        if (intp(data))
                sql = "UPDATE members SET " + key + "=" + data + " WHERE id = '" + id + "'";
        else if (mapp(data) || arrayp(data))
                sql = "UPDATE members SET " + key + "=" + db_str(save_variable(data)) + " WHERE id = '" + id + "'";
        else if (stringp(data))

           // if(strlen(data)>8192);
            //data="";
                sql = "UPDATE members SET " + key + "=" + db_str(data) + " WHERE id = '" + id + "'";

        else
                return 0;

        ret = DATABASE_D->db_query(sql);
        if (!intp(ret))
                return 0;

        return ret;
}

// 增加会员属性点
public int db_add_member(mixed ob, string key, int num)
{
        mixed  ret;
        string id, sql;

        if (!valid_caller())
                return 0;

        if (objectp(ob))
                id=query("id", ob);
        else
        if (stringp(ob))
                id = ob;
        else
                return 0;

        if (!stringp(id)  || id  == "" ||
            !stringp(key) || key == "" ||
            !intp(num)    || !num)
                return 0;

        sql = sprintf("UPDATE %s SET %s = %s + %d WHERE id = \"%s\"",
                      MEMBER_TABLE, key, key, num, id);

        ret = DATABASE_D->db_query(sql);
        if (!intp(ret))
                return 0;

        return ret;
}

// 会员卡
public varargs mixed db_fee_member(mixed ob, int day, int flag)
{
        mixed  ret;
        string id, sql;
        int    jointime, endtime;
        object user, obj;

        if (!valid_caller())
                return 0;

        if (objectp(ob))
        {
                id=query("id", ob);
                user = ob;
        }
        else
        if (stringp(ob))
        {
                id = ob;
                user = find_player(id);
        }
        else
                return 0;

        if (!user) return 0;
        BAN_D->add_welcome_user(id);

        jointime = db_query_member(id, "jointime");
        if (jointime < 1)
        {
                jointime = time();
                if (day > 90) addn("balance", 30000000, user);
                else addn("balance", 10000000, user);
        }

        if (flag)
        {
                day = 1999999999;
                obj = new("/d/room/obj/ultracard");
                obj->move(user, 1);
                obj = new("/clone/goods/noname");
                obj->move(user, 1);
        }
        else
        {
                endtime = (int)db_query_member(id, "endtime");
                if (endtime < 1 || endtime < time())
                        day = time() + day * 86400;
                else
                        day = endtime + day * 86400;
        }

        sql = sprintf("UPDATE %s SET jointime = %d, endtime = %d WHERE id = \"%s\"",
                      MEMBER_TABLE, jointime, day, id);

        ret = DATABASE_D->db_query(sql);
        if (!intp(ret))
                return 0;

        return ret;
}

// 会员冲值
public varargs int db_pay_member(mixed ob, int money, string from_id)
{
        string id, sql;
        string payinfo;
        string info;
        int paytimes, payvalue, last_payvalue;
        mixed ret;
        object target;

        if (!valid_caller())
                return 0;

        if (objectp(ob))
                id=query("id", ob);
        else
        if (stringp(ob))
                id = ob;
        else
                return 0;

        if (!stringp(id) || id == "")
                return 0;

        /*
        if (!is_member(id))
        {
                db_create_member(id, money, from_id);
                return 1;
        }
        */

        paytimes = db_query_member(id, "paytimes") + 1;
        payinfo  = db_query_member(id, "payinfo");
        if (!payinfo) payinfo = "";

        if (!stringp(from_id) || from_id == "")
                info = sprintf("你于 %s 冲值 %d $NT。\n", TIME_D->replace_ctime(time()), money);
        else
                info = sprintf("你于 %s 收到 %s 的转帐 %d $NT。\n",
                                TIME_D->replace_ctime(time()), from_id, money);

        payinfo += info;
        payvalue = db_query_member(id, "payvalue") + money;
        last_payvalue = money;
        money   += db_query_member(id, "money");
        /*
        sql = sprintf("UPDATE %s SET money = %d, paytimes = %d, payinfo = \"%s\",
                      payvalue = %d, last_payvalue = %d, last_paytime = %d WHERE id = \"%s\"",
                      MEMBER_TABLE, money, paytimes, payinfo, payvalue, last_payvalue, time(), id);
        */
        sql = "UPDATE members SET money=" + money + ", paytimes=" + paytimes + ", payinfo=" + DB_STR(payinfo) +
              ", payvalue=" + payvalue + ", last_payvalue=" + last_payvalue + ", last_paytime=" +time()+ " WHERE id= '" + id + "'";


        ret = DATABASE_D->db_query(sql);


        if (!intp(ret))
                return 0;

        if (objectp(target = find_player(id)))
        {
                tell_object(target, "\a", 0);
                tell_object(target, HIR + info + NOR);
        }

        return ret;
}

public varargs int player_pay(mixed from, int money, mixed to)
{
        mixed  ret;
        string fid, sql;

        if (!from)
                return 0;

        if (objectp(from))
                fid=query("id", from);
        else
        if (stringp(from))
                fid = from;
        else
                return 0;

        if (!stringp(fid)  || fid  == "" || !money)
                return 0;

        sql = sprintf("UPDATE %s SET money = money - %d WHERE id = \"%s\"",
                      MEMBER_TABLE, money, fid);

        ret = DATABASE_D->db_query(sql);
        if (!intp(ret))
                return 0;

        if (to)
        {
                money = money*99/100;
                if (money < 1) money = 1;
                if (MEMBER_D->is_member(to))
                        MEMBER_D->db_pay_member(to, money, fid);
                else
                        MEMBER_D->db_create_member(to, money, fid);
        }
        return ret;
}

// 会员转帐
public int db_transfer_member(mixed ob, mixed to, int value)
{
        string id, to_id, sql;
        string zhuaninfo;
        int money;
        mixed ret;
        object target;

        if (!valid_caller())
                return 0;

        if (objectp(ob))
                id=query("id", ob);
        else
        if (stringp(ob))
                id = ob;
        else
                return 0;

        if (objectp(to))
                to_id=query("id", to);
        else
        if (stringp(to))
                to_id = to;
        else
                return 0;

        if (!stringp(id) || id == "" ||
            !stringp(to_id) || to_id == "" ||
            !intp(value) || value < 1)
                return 0;

        target = UPDATE_D->global_find_player(to_id);
        if (!objectp(target))
        {
                write("没有这个玩家，请检查确认后再试！\n");
                return 0;
        }

        UPDATE_D->global_destruct_player(target, 1);

        if (!is_member(id))
        {
                write("您目前没有充值记录，也没有王者金币！\n");
                return 0;
        }


        money = db_query_member(id, "money");
        if (money < value)
        {
                write("对不起，您的王者金币数量不够！\n");
                return 0;
        }

        if (!db_set_member(ob, "money", (money - value)))
        {
                write("转帐失败，请与本站ADMIN联系！\n");
                return 0;
        }

        if (!is_member(to_id))
                db_create_member(to_id, value, id);
        else
                db_pay_member(to_id, value, id);

        zhuaninfo  = db_query_member(id, "transferinfo");
        if(!zhuaninfo)zhuaninfo="";
        zhuaninfo += sprintf("你于 %s 转帐 %d $NT给玩家 %s。\n",
                           TIME_D->replace_ctime(time()),
                           value,
                           to_id);

        db_set_member(ob, "transferinfo", zhuaninfo);
        db_add_member(ob, "transfervalue", value);
        db_add_member(ob, "transfertimes", 1);
        write(HIG "转帐成功， 您的转帐记录已写入文件，请使用 " HIR "member show zhuaninfo " HIG " 查询！ \n" NOR);
        write(HIC "您总共转帐了 " + HIY + value + HIC + " $NT , 祝您好运！\n" NOR);

        return 1;
}

public void show_member_info(mixed ob, string arg)
{
        mixed  ret, res;
        int    i;
        string id;

        if (objectp(ob))
                id=query("id", ob);
        else
        if (stringp(ob))
                id = ob;
        else
                return 0;

        switch(arg)
        {
        // 充值记录
        case "payinfo":
                if (!is_member(ob))
                {
                        write("您目前没有充值记录！\n");
                        return;
                }
                ret = db_query_member(ob, arg);
                write(BBLU + HIW "您的充值记录如下：\n\n" NOR);
                res = explode(ret, "\n");
                for (i = 0; i < sizeof(res); i++)
                        write(BBLU + HIY + res[i] + "\n" NOR);
                break;
        // 购买记录
        case "buyinfo":
                if (!is_member(ob))
                {
                        write("您目前没有购买记录！\n");
                        return;
                }
                ret = db_query_member(ob, arg);
                if (!stringp(ret) || ret == "")
                {
                     write("您目前没有购买记录！\n");
                     return;
                }
                write(BBLU + HIW "您的购买记录如下：\n\n" NOR);
                /*
                res = explode(ret, "\n");
                for (i = 0; i < sizeof(res); i++)
                        write(BBLU + HIY + res[i] + "\n" NOR);
                */
                ob->start_more(BBLU + HIY + ret + "\n" NOR);


                break;

        // 转帐记录
        case "zhuaninfo":
        case "transferinfo":
                if (!is_member(ob))
                {
                        write("您目前没有转帐记录！\n");
                        return;
                }
                //ret = db_query_member(ob, arg);
                ret = db_query_member(ob, "transferinfo");
                if (!stringp(ret) || ret == "")
                {
                     write("您目前没有转帐记录！\n");
                     return;
                }
                write(BBLU + HIW "您的转帐记录如下：\n\n" NOR);
                res = explode(ret, "\n");
                for (i = 0; i < sizeof(res); i++)
                        write(BBLU + HIY + res[i] + "\n" NOR);
                break;

        // 面板
        case "info":
                write(BBLU + HIW "\t\t       "+LOCAL_MUD_NAME()+"会员系统面板\t\t     " + VERSION + "\n" NOR);
                write(HIW "≡---------------------------------------------------------------≡\n" NOR);
                write(HIY "WELCOME TO JOIN IN THE MEMBERS OF NT AND HOPE YOU ALL GOES WELL.\n\n" NOR);

                write(sprintf(HIC "  会员代号：%-25s金币余额：%s\n" NOR,
                              id, db_query_member(ob, "money") + " $NT"));
                write(sprintf(HIC "  入会时间：%-25s有效时间：%s\n" NOR,
                              db_query_member(ob, "jointime") ?
                              TIME_D->replace_ctime(db_query_member(ob, "jointime")) : "没有入会",
                              db_query_member(ob, "endtime") > 1888888888 ?
                              "终身会员" : (db_query_member(ob, "endtime") ?
                              TIME_D->replace_ctime(db_query_member(ob, "endtime")) : "0")));
                write(sprintf(HIC "  冲值累计：%-25s充值次数：%d\n" NOR,
                              db_query_member(ob, "payvalue") + " $NT",
                              db_query_member(ob, "paytimes")));
                write(sprintf(HIC "  购买累计：%-25s购买次数：%d\n" NOR,
                              db_query_member(ob, "buyvalue") + " $NT",
                              db_query_member(ob, "buytimes")));
                write(sprintf(HIC "  转帐累计：%-25s转帐次数：%d\n" NOR,
                              db_query_member(ob, "transfervalue") + " $NT",
                              db_query_member(ob, "transfertimes")));
                write(sprintf(HIM "\n  您最后一次充值时间是               %s\n" NOR,
                              TIME_D->replace_ctime(db_query_member(ob, "last_paytime"))));
                write(sprintf(HIM "  您最后一次购买时间是               %s\n" NOR,
                              db_query_member(ob, "last_buytime") ?
                              TIME_D->replace_ctime(db_query_member(ob, "last_buytime")) : "————"));
                write(sprintf(HIM "  您最后一次购买物品是               %s(%s)\n" NOR,
                              sizeof(db_query_member(ob, "last_buyob")) ?
                              db_query_member(ob, "last_buyob") : "————",
                              db_query_member(ob, "last_buyvalue") ?
                              db_query_member(ob, "last_buyvalue") + " $NT" : "0"));

                write(HIG "\n  *请使用" HIR " member show info " HIG "          打开泥潭会员系统面板。\n" NOR);
                write(HIG "  *请使用" HIR " member show payinfo " HIG "       查看历史充值记录。\n" NOR);
                write(HIG "  *请使用" HIR " member show buyinfo " HIG "       查看购买物品记录。\n" NOR);
                write(HIG "  *请使用" HIR " member show zhuaninfo " HIG "     查看历史转帐记录。\n" NOR);
                write(HIG "  *请使用" HIR " member show goods " HIG "         查看王者商店出售的物品。\n" NOR);
                write(HIG "  *请使用" HIR " member zhuan <$NT> to <id>" HIG " 转帐金币($NT)给别的角色(ID)。\n" NOR);
                write(HIG "  *请使用" HIR " member buy <物品代号> " HIG "     购买物品。\n" NOR);
                write(HIG "  *请使用" HIR " member look <物品代号> " HIG "    查看物品。\n" NOR);
                write(HIG "  *请使用" HIR " member check <id> " HIG "         检查会员信息。\n" NOR);
                write(HIG "  *请使用" HIR " member stats " HIG "              列出所有的会员。\n" NOR);
                write(HIG "  *请使用" HIR " member ?? " HIG "                 member 指令帮助。\n\n\n" NOR);


                write(HIR "  为避免带来不必要的损失请认真阅读"+LOCAL_MUD_NAME()+"会员制度文件" HIY "(help member)\n\n" NOR);
                write(HIY "                                                 NT WIZARD GROUP\n" NOR);
                write(HIW "≡---------------------------------------------------------------≡\n" NOR);
                write(HIC"淘宝冲值链接地址: "NOR+HIR" \n"NOR);

                break;
           // 物品清单
           case "goods":
                GOODS_D->show_goods(ob);
                break;

           default:
                break;
      }

      return;
}

public mixed show_all_members(int flag)
{
        int nCount, m = 0;
        string status;
        object ob;
        string name, jointime;
        mixed members;

        members = DATABASE_D->db_all_query(sprintf("SELECT id from %s where endtime >= %d", MEMBER_TABLE, time()));


        if (!sizeof(members))
        {
                if (flag) return ({});
                write(HIG "暂无会员！\n" NOR);
                return;
        }

        if (flag) return members;

        write(HIM "以下是"+LOCAL_MUD_NAME()+"的所有会员列表：\n" NOR);
        write(HIW "≡-------------------------------------------------------------------≡\n" NOR);

        write(sprintf(HIR "%-18s%-18s%-26s%-20s\n\n" NOR,
                    "姓  名", "帐  号", "入会时间", "状  况"));

        for (nCount = 0; nCount < sizeof(members); nCount ++)
        {
                if (ob = find_player(members[nCount][0]))
                {
                        if( query("doing", ob))status=HIY"计划中"NOR;
                        else if (interactive(ob) && query_idle(ob) > 120)status = HIM "发呆" NOR;
                        else if (is_valid_member(members[nCount][0]))status = HIW "在线" NOR;
                        else status = HIR "过期" NOR;
                        name = ob->name(1);
                        jointime = TIME_D->replace_ctime(db_query_member(members[nCount][0], "jointime"));
                }
                else
                {
                        if (is_valid_member(members[nCount][0])) status = NOR + WHT "离线" NOR;
                        else status = HIR "过期" NOR;
                        name = "———";
                        jointime = "———";
                }

                write(sprintf(HIG "%-18s%-18s%-26s%-20s\n" NOR,
                           name,
                           members[nCount][0],
                           jointime,
                           status));

                m ++; // 过滤掉转帐记录文件，实际会员数

        }
        write(HIY "\n总共有 " + m + " 名注册会员。\n" NOR);
        write(HIW "≡-------------------------------------------------------------------≡\n\n" NOR);
        return 1;
}

#endif
