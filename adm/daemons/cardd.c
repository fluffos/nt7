// This program is a part of NT MudLIB

/*
DROP TABLE IF EXISTS `cards`;
CREATE TABLE `cards` (
  `card` varchar(20) NOT NULL default '',
  `password` varchar(20) NOT NULL default '',
  `money` int(11) default '0',
  `maketime` int(11) default '0',
  `makeid` varchar(10) NOT NULL default '',
  `sale` int(2) default '0',
  `paytime` int(11) default '0',
  `payid` varchar(10) NOT NULL default '',
  PRIMARY KEY  (`card`),
  KEY `password` (`password`),
  KEY `money` (`money`),
  KEY `sale` (`sale`),
  KEY `payid` (`payid`)
) TYPE=MyISAM;
*/

#include <ansi.h>
#include "/adm/etc/database.h"

#define SN_LEN            16
public varargs int db_create_card(mixed ob, string CardSn, string CardPass, int money);

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

// 查询 CARD 相关信息
public mixed db_query_card(string CardSn, string key)
{
        mixed  res;
        string sql;

        if( !valid_caller() )
                return 0;

        if( !stringp(CardSn) || sizeof(CardSn) != 18 )
                return 0;

        if( !stringp(key) || key == "" )
                return 0;

        sql = sprintf("SELECT %s FROM %s WHERE card = \"%s\"",
                      key, CARD_TABLE, CardSn);

        res = DATABASE_D->db_fetch_row(sql);

        if (arrayp(res) && sizeof(res))
                return res[0];
        else
                return 0;
}

public mixed db_find_card(string key, mixed data)
{
        mixed ret;
        string sql;

        if( !valid_caller() )
                return 0;

        if( !stringp(key) || key == "" || !data )
                return 0;

        if (intp(data))
                sql = sprintf("SELECT card FROM %s WHERE %s = %d",
                              CARD_TABLE, key, data);
        else if (stringp(data))
                sql = sprintf("SELECT card FROM %s WHERE %s = \"%s\"",
                              CARD_TABLE, key, data);
        else
                return 0;

        ret = DATABASE_D->db_all_query(sql);

        return ret;
}

public varargs int db_create_card(mixed ob, string CardSn, string CardPass, int money)
{
        mixed  ret;
        string sql;
        string id;

        if( !valid_caller() )
                return 0;

        if( objectp(ob) )
                id = query("id", ob);
        else
        if( stringp(ob) )
                id = ob;
        else
                return 0;

        if( !stringp(id) || id == "" )
                return 0;

        sql = sprintf("INSERT INTO %s SET card = \"%s\", password = \"%s\", money = %d, makeid = \"%s\", maketime = %d",
                      CARD_TABLE, CardSn, CardPass, money, id, time());

        ret = DATABASE_D->db_query(sql);
        if( !intp(ret) )
                return 0;

        return ret;
}

public int db_make_card(object me, int amount, int ctype)
{
        string strtmpSn, strtmpPass;
        string strQZ, strPS;           //  卡号前缀，用以表示卡的类别面额
        int nCount, i;
        mixed res, ret;
        string sql;

        // 注册码组合序列
        string *codes = ({
               "A", "B", "C", "D", "E", "F", "G", "H", "I",
               "J", "K", "L", "M", "N", "O", "P", "Q", "R",
               "S", "T", "U", "V", "W", "X", "Y", "Z",
               "a", "b", "c", "d", "e", "f", "g", "h", "i",
               "j", "k", "l", "m", "n", "o", "p", "q", "r",
               "s", "t", "u", "v", "w", "x", "y", "z",
               "0", "1", "2", "3", "4", "5", "6", "7", "8",
               "9"
        });

        if( !valid_caller() )
                return 0;

        if( amount <= 0 )
                return 0;

        // 为保证数据存储没有问题，每次最多生成500个卡号
        if( amount > 500 )
        {
                write("为保证数据存储没有问题，每次最多生成500个卡号！\n");
                return 0;
        }

        if( !ctype )
        {
                write("请输入卡号种类。" HIC + "10 OR 50 OR 100" + NOR "分别代表10RMB，50RMB和100RMB面额！\n");
                return 0;
        }

        // 必须输入合法的卡号种类
        switch(ctype)
        {
        case 10:
                strQZ = "TE";
                strPS = "Te";
                break;

        case 50:
                strQZ = "FT";
                strPS = "Fi";
                break;

        case 100:
                strQZ = "HU";
                strPS = "Hu";
                break;

        default:
                write("请输入卡号种类。" HIC + "10 OR 50 OR 100" + NOR "分别代表10RMB，50RMB和100RMB面额！\n");
                return 0;
                break;
        }

        // 初始化
        strtmpSn = "";
        nCount = 0;
        res = ({});
        while(1)
        {
                // 卡号生成完毕，进行后续处理
                if( nCount >= amount )
                {
                        for (i = 0; i < sizeof(res); i+=2)
                        {
                                reset_eval_cost();
                                if( !db_create_card(me, res[i], res[i+1], ctype) )
                                {
                                        write("生成卡号时失败！\n");
                                        return 0;
                                }
                                log_file("static/cards", sprintf("Card: %s-%s，value = %d.\n", res[i], res[i+1], ctype));
                        }
                        return 1;
                }

                // 产生一个随机卡号
                strtmpSn = strQZ; // 卡号前缀
                strtmpPass = strPS;
                for(i = 0; i < SN_LEN; i ++)
                {
                        strtmpSn += codes[random(sizeof(codes))];
                        strtmpPass += codes[random(sizeof(codes))];
                }
/*
                sql = sprintf("SELECT card FROM %s WHERE card = \"%s\"",
                              CARD_TABLE, strtmpSn);
                ret = DATABASE_D->db_query(sql);
                if( ret ) continue; // 数据库已经存在
                sql = sprintf("SELECT password FROM %s WHERE password = \"%s\"",
                              CARD_TABLE, strtmpPass);
                ret = DATABASE_D->db_query(sql);
                if( ret ) continue; // 数据库已经存在
*/
                nCount ++;
                res += ({ strtmpSn, strtmpPass });
        }
}

// 设定卡号属性
public int db_set_card(string CardSn, string key, mixed data)
{
        mixed  ret;
        string sql;

        if( !valid_caller() )
                return 0;

        if( !stringp(key) || key == "" )
                return 0;

        if( intp(data) )
                sql = "UPDATE cards SET " + key + "=" + data + " WHERE card = '" + CardSn + "'";
        else if (stringp(data))
                sql = "UPDATE cards SET " + key + "=" + DB_STR(data) + " WHERE card = '" + CardSn + "'";
        else
                return 0;

        ret = DATABASE_D->db_query(sql);
        if( !intp(ret) )
                return 0;

        return ret;
}

public int db_card_pay(object me, string CardSn, string CardPass)
{
        string strQZ, pass;
        int value, money;
        mixed res, ret;
        string sql;

        if( !objectp(me) ) return -1;

        if (time() - query_temp("last_try_card_pay", me) < 5 )
        {
                write("你距离上次充值错误的时间不足5秒，请稍微再试。\n");
                return 0;
        }

        if( !CardSn || sizeof(CardSn) != SN_LEN+2 )
        {
                write("充值卡号位数错误，请确认你的充值卡号的正确性。\n");
                set_temp("last_try_card_pay", time(), me);
                return 0;
        }

        strQZ = CardSn[0..1];
        switch(strQZ)
        {
        case "TE":
                break;
        case "FT":
                break;
        case "HU":
                break;
        default:
                write("充值卡号错误，请确认你的充值卡号的正确性。\n");
                set_temp("last_try_card_pay", time(), me);
                return 0;
                break;
        }

        res = DATABASE_D->do_sql("select password, money from cards where card = '" + CardSn + "'");

        if( !arrayp(res) || !stringp(pass = res[0]) )
        {
                write("充值卡号错误，请确认你的充值卡号的正确性。\n");
                return 0;
        }

        if( CardPass != pass )
        {
                write("充值卡密码错误，请确认你的充值卡密码的正确性。\n");
                return 0;
        }

        value = res[1];

        // 活动期间
        money = value + value / 5;

        // 处理卡冲值后标记
        sql = "UPDATE cards SET sale = 1, paytime = " + time() + ", payid = " + DB_STR(query("id", me)) + " WHERE card = '" + CardSn + "'";
        ret = DATABASE_D->db_query(sql);
        if( !intp(ret) )
        {
                write(HIR "充值失败(0000)，并尽快与ADMIN联系。\n" NOR);
                return 0;
        }

        if( MEMBER_D->is_member(me) )
                MEMBER_D->db_pay_member(me, money);
        else
                MEMBER_D->db_create_member(me, money);


        tell_object(me, HIG "恭喜！王者币(NT)充值成功，充值面额" + HIR + sprintf("%d", value) +
                        HIG "元，获得 " + HIR + sprintf("%d", money) + HIG + " 王者币(NT)。\n" NOR);
        return 1;
}
