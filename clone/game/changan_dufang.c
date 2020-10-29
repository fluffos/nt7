//Created by RoomEditer on 02-1-3.
//by bravo
// naihe 05-12-3 0:22 完全重写(只是沿原来的文件名及地理位置而已)，添加赌大小功能，使之成为真正赌场。
// naihe 05-12-3 17:01 调整豹子赔率，增加数据存取功能及更详细的分析 log.
// 由于 sz /d/ 下文件没有 save_object() 权，故更改此文件为 /clone/room/changan_dufang.c
// naihe 05-12-6 8:41 加上彩金功能。
// naihe 05-12-14 16:42 最终完善。
// naihe 05-12-18 10:15 降低手续费用由百分率改为千分率，可选择余地更多。

#include <ansi.h>
inherit ROOM;
inherit F_SAVE;
#include <ctime_format_func.h>    // 某些MUD里没有这个函数：ctime_format()，把它写成：return ctime(time()); 即可。
//#include <set_del_color_func.h> // 某些MUD里没有这两个 s_efun:  setcolor(), delcolor().

#define     DUFANG_VERSION                  "V1.2 (2005.12.18)"

// ----------------- defines -----------------------
#define     DUFANG_LOG_FILE                 "duchang/changan_dufang"     // log dir 下。
#define     LOG_ON          1               // 开启时则进行 log_file() 操作。主要是记录 mewiz 操作记录。
#define     DUFANG_SAVE_FILE    DATA_DIR +  "duchang/changan_dufang"
#define     SAVE_ON         1               // 开启时则进行 save_object() 操作。
                                            // 本文件数据记录位置
#define     SYSTEM_WIZ_ID   "$lonely$"       // 允许使用 <mewiz reward 数字> 指令给系统加入奖金。
#define     SYSTEM_EAT_P    3               // 系统吃钱设置是否开启。这是一个千分率。
                                            // 非零时，每局都要“吃掉”一定的押注额，不计入返还记录中。
#define     WAIT_TIME       20              // 押注后等待开局的时间(等待多人押注)
#define     GOGO_WAIT_TIME  3               // 准备开局后要等待几秒才能用 gogo 加速开奖。
#define     DEF_PERCENT     95              // 正常时的默认赔率，这是赢的部分。如 bet 100 即纯赚 100*DEF_PERCENT/100
#define     BAOZI_PERCENT   3000            // 豹子的固定赔率。规则同上。
#define     ADD_PERCENT     2               // 当大、小、单、双连续开出时，连续开出的项其赔率会上涨。这是幅度。
#define     LOST_PERCENT    2               // 同上，隔得越久未开的项其赔率会下跌，这是幅度。
#define     MAX_DF_PLAYER   10              // 最多 10 位玩家同时投注。 定义为 0 时不限制。

//    #######  彩金方面的设置 #######
#define     JACKPOT_ON      1               // 是否开启彩金奖励。 0 不开启。
#define     JACKPOT_RANDOM  5               // 如果 !random(这个数) 并符合条件(赢入足够的钱)的话就会开启彩金
#define     JACKPOT_LIMIT   20000           // 彩金限制，系统要赢入多少金才会开启彩金。不过，也可能以较低概率开启彩金。
#define     JACKPOT_MAX     2000            // 彩金最多
#define     JACKPOT_MIN     200             // 彩金最少
//    ###############################

#define     BIG_STR         HIG"大"NOR      // 可以在这里改一下颜色。只是描述而已。
#define     SMALL_STR       HIC"小"NOR
#define     SINGLE_STR      HIY"单"NOR
#define     DOUBLE_STR      HIM"双"NOR
#define     BAOZI_STR       HIR"豹子"NOR

// ---------------- game vars (save) ----------------
int times_flag = 1;
int BetOn = 1;                              // 允许押注
mapping game_info = ([
    "comp_da"       : 0,
    "comp_xiao"     : 0,
    "comp_dan"      : 0,
    "comp_shuang"   : 0,
    "percent_da"    : DEF_PERCENT,
    "percent_xiao"  : DEF_PERCENT,
    "percent_dan"   : DEF_PERCENT,
    "percent_shuang": DEF_PERCENT,
    "percent_baozi" : BAOZI_PERCENT,        // 可以押豹子，固定赔率。
    "last_msg_dx"   : "",
    "last_msg_ds"   : "",
]);
mapping log_info = ([
    "total_bet" : 0,
    "total_pay" : 0,
    "total_bet_g" : 0,
    "total_pay_g" : 0,
    "system_reward_g": 0,   // 系统额外奖励的，由 mewiz 指令及特定巫师设置。
    "system_eat"  : 0,      // 系统吃掉的……
    "system_eat_g": 0,
]);
// ---------------- game vars (no save) --------------
nosave int GameStat = 0;
nosave int valid_gogo_time;
nosave int this_bet = 0;
nosave int jackpot = 0;
nosave int jp_num = 0;
nosave int jp_bingo = 0;
nosave int t1;
nosave int t2;
nosave int t3;
nosave int total;
nosave mapping type_str = ([
    "da"        :       BIG_STR,
    "xiao"      :       SMALL_STR,
    "dan"       :       SINGLE_STR,
    "shuang"    :       DOUBLE_STR,
    "baozi"     :       BAOZI_STR,
]);
nosave mapping type_opp = ([
    "da"        :       "xiao",
    "xiao"      :       "da",
    "dan"       :       "shuang",
    "shuang"    :       "dan",
    "baozi"     :       "baozi",
]);
nosave mapping bet_info = ([ ]);
nosave mapping bet_info_jp = ([ ]);
nosave string *df_player = ({ });
// -------------- function list -----------------------
        int     query_system_win    ();
        string  system_info_msg     ();
        string  look_bugao          ();
        string  query_now_long      ();
        string  query_now_long2     ();

        string  check_beted_str     ( string id );
protected int     do_chk              ( string arg );
protected int     do_bet              ( string arg );
protected int     do_mewiz            ( string arg );
protected int     do_gogo             ();
protected void    finish_bingo_check  ();
protected void    new_game            ();
protected void    game_start          ( int stat );
protected string  check_percent_str   ();
// ----------------------------------------------------


// ####################################################
// #################  以下开始正式部分 ################
// ####################################################
// 保持房间不被系统 clean_up()
void reset()
{
    ::reset();
    set("no_clean_up", 1 );
}

// 存储文件位置
string query_save_file()
{
    if( !SAVE_ON )
        return 0;
    return DUFANG_SAVE_FILE;
}

// 获得 id 的押注表的字串
string check_beted_str( string id )
{
    string msg;
    msg = "";
    if( bet_info[ id + "-baozi" ] )
        msg += "本局押  "+BAOZI_STR+"：" + bet_info[ id + "-baozi" ] + "\n";
    if( bet_info[ id + "-da" ] )
        msg += "本局押  "+BIG_STR+"：" + bet_info[ id + "-da" ] + "\n";
    if( bet_info[ id + "-xiao" ] )
        msg += "本局押  "+SMALL_STR+"：" + bet_info[ id + "-xiao" ] + "\n";
    if( bet_info[ id + "-dan" ] )
        msg += "本局押  "+SINGLE_STR+"：" + bet_info[ id + "-dan" ] + "\n";
    if( bet_info[ id + "-shuang" ] )
        msg += "本局押  "+DOUBLE_STR+"：" + bet_info[ id + "-shuang" ] + "\n";
    if( msg != "" )
        msg = "以下是本局 "+id+" 的押注：\n" + msg;
    return msg;
}

// 支付奖金等。
protected void finish_bingo_check()
{
    object *inv, ob;
    string id;
    int bet, bingo;

    inv = all_inventory( this_object() );
    if( !sizeof( inv ) )
        return;
    if( jp_bingo && jackpot > 0 )
    {
        tell_room( this_object(), BLINK+HIM"中了幸运奖金！！！本局幸运奖金每位最高派彩 "+jackpot+" (coin)，有押注押中的玩家都能获得红利！\n"NOR);
    }
    foreach( ob in inv )
    {
        if( !userp(ob) || !living(ob) )
            continue;
        id=query("id", ob);
        if( (bet=bet_info[ id + "-" + game_info["opened1"]]) > 0 )     // 押大小中了(或豹子中了)。
        {
            bet *= 100;     // 转成 coin
            // 防止溢出，低赔率时直接计算，高赔率时先除后乘。
            if( game_info["percent_"+game_info["opened1"]] <= 500 )
                bingo = bet + (bet * game_info[ "percent_" + game_info[ "opened1"] ] / 100);    // 计算应得奖金
            else
                bingo = bet + (bet / 100 * game_info[ "percent_" + game_info[ "opened1"] ]);
            addn("balance", bingo, ob);//支付
            log_info[ "total_pay" ] += bingo;   // 记录
            message_vision( "$N押下 "+(bet/100)+" 两白银买 "+type_str[game_info["opened1"]]+" ，获得奖金"
                +MONEY_D->money_str( bingo-bet )+"(钱庄自动转帐，本金同时返还)。\n", ob );      // 报告
            if( undefinedp( bet_info_jp[id] ) )
                bet_info_jp[ id ] = bet/100;    // 转回 silver
            else
                bet_info_jp[ id ] += bet/100;    // 转回 silver
        }
        if( (bet=bet_info[ id + "-" + game_info["opened2"]]) > 0 )     // 押单双中了。
        {
            bet *= 100;     // 转成 coin
            // 防止溢出，低赔率时直接计算，高赔率时先除后乘。
            if( game_info["percent_"+game_info["opened2"]] < 300 )
                bingo = bet + (bet * game_info[ "percent_" + game_info[ "opened2"] ] / 100);    // 计算应得奖金
            else
                bingo = bet + (bet / 100 * game_info[ "percent_" + game_info[ "opened2"] ]);
            addn("balance", bingo, ob);//支付
            log_info[ "total_pay" ] += bingo;   // 记录
            message_vision( "$N押下 "+(bet/100)+" 两白银买 "+type_str[game_info["opened2"]]+" ，获得奖金"
                +MONEY_D->money_str( bingo-bet )+"(钱庄自动转帐，本金同时返还)。\n", ob );      // 报告
            if( undefinedp( bet_info_jp[id] ) )
                bet_info_jp[ id ] = bet/100;    // 转回 silver
            else
                bet_info_jp[ id ] += bet/100;    // 转回 silver
        }
    }
    // 统计彩金问题
    if( jp_bingo && jackpot > 0 )
    {
        if( !sizeof( bet_info_jp ) )
        {
            tell_room( this_object(), HIM"不过很可惜，本局游戏无人押中，彩金无人获得！\n"NOR );
        }
        else
        {
            string *key, t;
            int percent;
            key = keys( bet_info_jp );
            foreach( t in key )
            {
                if( !(ob = find_player(t)) || environment(ob) != this_object() )
                    continue;
                bet = bet_info_jp[ t ];             // 该玩家总 bet 中数量
                if( bet > 5000 )                   // 总量 5000 以上可以得到全额奖金
                    percent = 100;
                else
                    percent = bet * 100 / 5000;
                if( percent < 1 )
                    percent = 1;                    // 得出百分比
                bingo = jackpot / 100 * percent;    // 最终奖金(coin)
                message_vision( HIY"          $N"HIY"获得了 "+HIR+percent+"%"HIY" 的彩金："
                    +MONEY_D->money_str( bingo )+"！\n"NOR, ob);
                addn("balance", bingo, ob);//支付
                log_info[ "total_pay" ] += bingo;   // 记录
            }
        }
    }
    // 将 log 记录换成 gold 单位以防止溢出的问题。
    if( log_info["total_bet"] >= 10000 )
    {
        log_info["total_bet_g"] += log_info["total_bet"] / 10000;
        log_info["total_bet"] %= 10000;
    }
    if( log_info["total_pay"] >= 10000 )
    {
        log_info["total_pay_g"] += log_info["total_pay"] / 10000;
        log_info["total_pay"] %= 10000;
    }
}

// 获得系统现在赢钱的数量
int query_system_win()
{
    return log_info["system_reward_g"]
        + (log_info["total_bet_g"] - log_info["total_pay_g"] - log_info["system_eat_g"]);
}

protected void new_game()
{
    times_flag ++;
    GameStat = 0;
    bet_info = ([ ]);
    bet_info_jp = ([ ]);
    df_player = ({ });
    jackpot = 0;
    // 本局总押注额要抽一部分作系统吃掉的。
    if( SYSTEM_EAT_P > 0 )
    {
        int tmp;
        tmp = this_bet / 1000 * SYSTEM_EAT_P;       // 这是一个千分率。
        if( tmp < 1 )
            tmp = 1;
        log_info["system_eat"] += tmp;
        if( log_info["system_eat"] >= 10000 )
        {
            log_info["system_eat_g"] += log_info["system_eat"] / 10000;
            log_info["system_eat"] %= 10000;
        }
    }
    this_bet = 0;
    tell_room( this_object(), query_now_long2() );
    set( "long", query_now_long() );
    save();
}
string random_color()
{
    return ({ HIR, HIM, HIB, HIC, HIG, })[ random(5) ];
}
protected void game_start( int stat )
{
    remove_call_out( "game_start" );
    GameStat = 2;
    if( !stat )
    {
        int win = query_system_win();
        int t = 1;
        tell_room( this_object(), HIW"第 "+times_flag+" 局赌局开宝，买定离手！\n"NOR );
        // 系统赢了一定数量，就会开启彩金奖励。或者会以较低概率开启小奖彩金。
        if( (JACKPOT_ON && !random( JACKPOT_RANDOM ) && win > JACKPOT_LIMIT)
         || (JACKPOT_ON && !random(JACKPOT_RANDOM*10))
        )
        {
            jp_bingo = 0;
            // 彩金额是 win 额的 1/20
            jackpot = 1 + random( win/20 );
            // 最多
            if( jackpot > JACKPOT_MAX )
                jackpot = JACKPOT_MAX - random(JACKPOT_MAX/20);
            // 最少
            if( jackpot < JACKPOT_MIN )
                jackpot = JACKPOT_MIN + random(JACKPOT_MIN/20);
            jackpot *= 10000;       // 换成 coin
            if( win > JACKPOT_LIMIT*3 )
                jp_num = 6 + random( 10 );      // 这个相对容易中一些。
            else
                jp_num = 3 + random(16);
            tell_room( this_object(),
                sprintf( "\n                 %s★%s☆%s★ %s幸%s运  "HIY"%d  %s彩%s金 %s★%s☆%s★\n"
                    +HIW"         本局若开出 "HIR"%d"HIW" 点，则所有买中的玩家都有机会获得奖金！\n\n"NOR,
                        random_color(), random_color(), random_color(),
                        random_color(), random_color(),
                        jackpot,
                        random_color(), random_color(),
                        random_color(), random_color(), random_color(),
                        jp_num,
                )
            );
            t = 5;
        }
        call_out( "game_start", t, 1 );     // t 秒后继续
        return;
    }
    if( stat == 1 )
    {
        string msg;
        t1 = 1 + random( 6 );
        t2 = 1 + random( 6 );
        t3 = 1 + random( 6 );
        total = t1 + t2 + t3;
        msg = "第 "+times_flag+" 局赌局开出："
            + chinese_number( t1 ) + "、"
            + chinese_number( t2 ) + "、"
            + chinese_number( t3 ) + "，";
        if( t1 == t2 && t1 == t3 )
        {
            msg += BAOZI_STR+ HIW"，通吃“大小单双”！";
            game_info[ "opened1" ] = "baozi";       // 设置一个就行
            game_info[ "opened2" ] = "-----";       //
        }
        else
        {
            msg += chinese_number( total )+"点  "
                + (total < 11 ? SMALL_STR : BIG_STR) + HIW "  "
                +"，报  "+(total % 2 ? SINGLE_STR : DOUBLE_STR )+ HIW"  数！";
            if( total < 11 )
                game_info[ "opened1" ] = "xiao";
            else
                game_info[ "opened1" ] = "da";
            if( total % 2 )
                game_info[ "opened2" ] = "dan";
            else
                game_info[ "opened2" ] = "shuang";
        }
        tell_room( this_object(), HIW"\n" + msg + "\n\n"NOR );
        game_info[ "last_opened_msg" ] = msg;   // 把信息记录下来。
        call_out( "game_start", 1, 2 );         // 1秒后继续
        return;
    }
    else
    {
        if( total == jp_num )
            jp_bingo = 1;
        finish_bingo_check();      // 支付奖金。

        // 计算新的赔率。如果是豹子，则保持赔率。
        if( game_info[ "opened1" ] != "baozi" )
        {
            // 大小连开(或者连续通杀)
            if( game_info[ "last_opened1" ] == game_info[ "opened1" ] )
            {
                game_info[ "percent_" + game_info[ "opened1" ] ] += ADD_PERCENT;
                game_info[ "percent_" + type_opp[game_info[ "opened1" ]] ] -= LOST_PERCENT;
                game_info[ "comp_" + game_info[ "opened1" ] ] ++;
                game_info[ "comp_" +  type_opp[game_info[ "opened1" ]] ] = 0;
            }
            else        // 否则恢复。
            {
                game_info[ "percent_da" ] = DEF_PERCENT;
                game_info[ "percent_xiao" ] = DEF_PERCENT;
                game_info[ "comp_" + game_info[ "opened1" ] ] = 1;
                game_info[ "comp_" + type_opp[game_info[ "opened1" ]] ] = 0;

            }
            // 单双连开
            if( game_info[ "last_opened2" ] == game_info[ "opened2" ] )
            {
                game_info[ "percent_" + game_info[ "opened2" ] ] += ADD_PERCENT;
                game_info[ "percent_" + type_opp[game_info[ "opened2" ]] ] -= LOST_PERCENT;
                game_info[ "comp_" + game_info[ "opened2" ] ] ++;
                game_info[ "comp_" + type_opp[game_info[ "opened2" ]] ] = 0;
            }
            else
            {
                game_info[ "percent_dan" ] = DEF_PERCENT;
                game_info[ "percent_shuang" ] = DEF_PERCENT;
                game_info[ "comp_" + game_info[ "opened2" ] ] = 1;
                game_info[ "comp_" + type_opp[game_info[ "opened2" ]] ] = 0;
            }
            game_info[ "last_opened1" ] = game_info[ "opened1" ];
            game_info[ "last_opened2" ] = game_info[ "opened2" ];
            // 记录上盘的信息。
        }
        // 记录总共开的次数。
        if( !game_info[ "total_opened_" + game_info[ "opened1" ]]  )
            game_info["total_opened_" + game_info[ "opened1" ]] = 1;
        else
            game_info["total_opened_" + game_info[ "opened1" ]] ++;
        if( !game_info[ "total_opened_" + game_info[ "opened2" ]]  )
            game_info["total_opened_" + game_info[ "opened2" ]] = 1;
        else
            game_info["total_opened_" + game_info[ "opened2" ]] ++;
        if( 1 )     // 搞走势图
        {
            string t;
            // dx
            if( game_info["opened1"] == "baozi" )
                t = "* ";
            if( game_info["opened1"] == "da" )
                t = "- ";
            else if( game_info["opened1"] == "xiao" )
                t = "_ ";
            else
                t = "* ";
            if( strlen(game_info["last_msg_dx"]) >= 20 )
                game_info["last_msg_dx"] = game_info["last_msg_dx"][2..19];
            game_info["last_msg_dx"] += t;
            // ds
            if( game_info["opened2"] == "baozi" )
                t = "* ";
            if( game_info["opened2"] == "dan" )
                t = "- ";
            else if( game_info["opened2"] == "shuang" )
                t = "_ ";
            else
                t = "* ";
            if( strlen(game_info["last_msg_ds"]) >= 20 )
                game_info["last_msg_ds"] = game_info["last_msg_ds"][2..19];
            game_info["last_msg_ds"] += t;
        }
        new_game();
    }
}

void create()
{
    restore();
    set("short","赌坊");
    //set("long", (: query_now_long :) );  yh lib 不支持这样 set long. 为了兼容，统一更改。
    set( "long", query_now_long() );       // 每局游戏结束后还要额外 set 一次，以改变 long().
    set("exits",([
        "east" : "/d/city/tree2",
    ]));
    set("item_desc", ([
        "bugao" : (: look_bugao :),
    ]));
    if( file_size( __DIR__"cadf_huoji.c" ) > 1 )
    {
        set( "objects", ([
            __DIR__"cadf_huoji" : 1,
        ]));
    }
    set("no_fight", 1 );
    set("no_steal", 1 );
    set("no_sleep_room", 1 );

    set("show_dir", "changan" );
    set("show_map_use", "changan2" );
    setup();
}

string query_now_long2()
{
    string msg = "";
    if( !BetOn )
        msg += HIR"                         【赌坊暂停营业】\n\n"NOR;
    if( game_info[ "last_opened_msg" ] )
        msg += BBLU + HIW"  上局：" + filter_color(game_info[ "last_opened_msg" ]) + "  \n"NOR;
    else
        msg += BBLU + HIW"  上局：                                                            \n"NOR;
    msg += "      "BCYN + HIW" A  目前赔率：    [大]  连开 "+game_info[ "comp_da" ]+" 局  赔率 "+(100+game_info[ "percent_da" ])+"%    \n"NOR;
    msg += "      "BCYN + HIW" B  目前赔率：    [小]  连开 "+game_info[ "comp_xiao" ]+" 局  赔率 "+(100+game_info[ "percent_xiao" ])+"%    \n"NOR;
    msg += "      "BCYN + HIW" C  目前赔率：    [单]  连开 "+game_info[ "comp_dan" ]+" 局  赔率 "+(100+game_info[ "percent_dan" ])+"%    \n"NOR;
    msg += "      "BCYN + HIW" D  目前赔率：    [双]  连开 "+game_info[ "comp_shuang" ]+" 局  赔率 "+(100+game_info[ "percent_shuang" ])+"%    \n"NOR;
    msg += BBLU+HIW"  大小：[ " + sprintf( "%-20s",game_info["last_msg_dx"]) + "]      单双：[ "+sprintf( "%-20s",game_info["last_msg_ds"])+"]  \n"NOR;
    msg += check_percent_str();
    return msg + "\n";
}

string query_now_long()
{
    string msg;

    msg ="这里是王者归来的一家小赌坊，别看它规模不大，却常常有许多千金富豪
来这里彻夜豪赌。对门的墙上帖着一张布告(bugao)。\n\n";
    msg += query_now_long2();
    return msg;
}

string look_bugao()
{
    object me = this_player();
    string msg;
    msg =
"**********************************************************
    赌坊游戏说明  "HIC+DUFANG_VERSION"  Naihe@神州 MUD"NOR"

    本赌坊直接使用钱庄转帐付款，设骰子赌局。

    三颗骰子，押注后 "+WAIT_TIME+" 秒开奖，押中即奖。
    可以押“大”、“小”、“单”、“双”、“豹子”共五项。

    4,6,8,10,12,14,16 为双，5,7,9,11,13,15,17 为单。
    4-10 为小，11-17 为大。
    三颗骰子都一样时为“豹子”，通吃大小单双——但赔出押
    中豹子的注金，赔率为固定的 "+(game_info["percent_baozi"]+100)+"%。

    其它赔率每局另报，投注范围 1 - 10000 两"HIW"白银"NOR"。

    "HIY"押注：   <bet 数量 to da|xiao|dan|shuang|baozi>"NOR"
             你也可以用  a|b|c|d|e  来简化输入上面的类型。
    查看：   <chk ID>
    即开：   <gogo>

    加入 "HIW"随机彩金"NOR" 设置！
    每位玩家一次可能获得 "+JACKPOT_MIN+" - "+JACKPOT_MAX+" 黄金！
**********************************************************\n";
    if( wizardp(me) )
        msg += "你是巫师，可以使用 <mewiz> 指令进行一些设置。\n";
    return msg;
}
void init()
{
    add_action( "do_bet", "bet" );
    add_action( "do_chk", "chk" );
    add_action( "do_gogo", "gogo" );
    if( wizardp(this_player()) )
        add_action( "do_mewiz", "mewiz" );
}

string system_info_msg()
{
    int t = query_system_win();
    return sprintf(
        "(系统现在 %s )  总收入：%d (额外奖励：%d)  总支出：%d (手续消耗：%d)  盈余：%s%d"NOR"  ("HIY"黄金"NOR")\n",
        (BetOn ? HIG"开放中"NOR : HIR"关闭中"NOR),
        log_info["total_bet_g"],
        log_info["system_reward_g"],
        log_info["total_pay_g"],
        log_info["system_eat_g"],
        (t > 0 ? HIG : HIR),
        t,
    );
}

// 巫师设置开放 / 停止 游戏；或设置当前总押注数量(更新后之前的记录没了，把它设置回来)。
// naihe 按：增加彩金设置之后，押注数量有相当大的影响，所以不能再随意更改了。取消了这个功能。
protected int do_mewiz( string arg )
{
    object me = this_player();
    int add, now, all, because;
    string msg, help_msg;

    if( !wizardp(me) )
        return 0;
    help_msg = "指令参数如下：\n"
        +"<mewiz reward 数字 原因>  -- 给赌坊系统加入额外奖励资金，单位 gold 。\n"
        +"                             也可以输入负数来撤消它。\n"
        +"<mewiz stat>              -- 开放 / 关闭赌坊\n";
    if( arg == "stat" )
    {
        if( BetOn )
            BetOn = 0;
        else
            BetOn = 1;
        if( LOG_ON )
        {
            log_file( DUFANG_LOG_FILE, sprintf( "[%s] %s(%s)更改开放状态，现在是：%d  。\n",
                ctime_format(),query("name", me),getuid(me),BetOn )
            );
        }
        msg = sprintf( HIG"【公告】%s(%s)将长安城%s%s了，现在：%s。\n"NOR,
            query("name", me),getuid(me),query("short"),(BetOn?"开放":"关闭"),
            (BetOn ? "正常营业" : "停止营业")
        );
        shout( msg );
        write( msg + "执行完毕，状态已自动储存。\n" );
        set( "long", query_now_long() );       // 每局游戏结束后还要额外 set 一次，以改变 long().
        save();
        return 1;
    }
    if( stringp(arg) && sscanf( arg, "reward %d %s", add, because ) == 2 )
    {
        if( strsrch( SYSTEM_WIZ_ID, "$" + getuid(me) + "$" ) == -1 )
            return notify_fail("对不起，这个指令只能由指定巫师执行。\n"
                "指定巫师："+ replace_string( SYSTEM_WIZ_ID, "$", " ") + "\n"
            );
        if( add < -10000 || add > 10000 )
            return notify_fail("增加量范围是 -10000 ~ 10000 之间。\n");
        now = log_info["system_reward_g"];
        all = now + add;
        if( all < 0 )
            return notify_fail("对不起，你不能将奖励资金减到 0 以下。\n"
                "现在有："+now+"  增加："+add+"  结果："+all+"\n"
            );
        if( LOG_ON )
        {
            log_file( DUFANG_LOG_FILE, sprintf( "[%s] %s(%s)因为(%s)注入额外奖励资金 %d ，原 %d -> %d 。\n",
                ctime_format(),query("name", me),getuid(me),because,add,now,all )
            );
        }
        msg = sprintf( HIG"【公告】%s(%s)给长安城%s注入了 %d 两黄金作额外奖励资金，原因：%s\n"NOR,
            query("name", me),getuid(me),query("short"),add,because,
        );
        log_info[ "system_reward_g" ] = all;
        shout( msg );
        write( msg + "执行完毕，状态已自动储存。\n" + system_info_msg() );
        save();
        return 1;
    }
    write( system_info_msg() + help_msg );
    return 1;
}

protected string check_percent_str()
{
    return sprintf( "%s：%d (%d%%)  %s：%d (%d%%)  %s：%d (%d%%)  %s：%d (%d%%)  %s：%d (%d.%d%%)\n",
            BIG_STR,    game_info["total_opened_da"],
                times_flag <= 1 ? 0 : game_info["total_opened_da"] * 100 / (times_flag-1),
            SMALL_STR,  game_info["total_opened_xiao"],
                times_flag <= 1 ? 0 : game_info["total_opened_xiao"] * 100 / (times_flag-1),
            SINGLE_STR, game_info["total_opened_dan"],
                times_flag <= 1 ? 0 : game_info["total_opened_dan"] * 100 / (times_flag-1),
            DOUBLE_STR, game_info["total_opened_shuang"],
                times_flag <= 1 ? 0 : game_info["total_opened_shuang"] * 100 / (times_flag-1),
            BAOZI_STR,  game_info["total_opened_baozi"],
                times_flag <= 1 ? 0 : (game_info["total_opened_baozi"] * 1000 / (times_flag-1)) / 10,
                times_flag <= 1 ? 0 : (game_info["total_opened_baozi"] * 1000 / (times_flag-1)) % 10,
    );
}

// 查询押注信息，玩家操作接口函数
protected int do_chk( string arg )
{
    string id, msg;
    if( !arg )
        id=query("id", this_player());
    else
        id = arg;
    if( (msg=check_beted_str(id)) == "" )
        return notify_fail( id + " 在本局未有任何押注。\n");
    write( msg );
    return 1;
}

// 押注，玩家操作接口函数
protected int do_bet( string arg )
{
    object me = this_player();
    string id, bet_key, type;
    int bet, beted;

    if( !BetOn )
        return notify_fail("对不起，本赌坊暂时停止营业。\n");
    if( GameStat == 2)
        return notify_fail("现在正在开出本局结果，请稍等下局再押。\n");
    id=query("id", me);
    if( !arg || sscanf( arg, "%d to %s", bet, type) != 2 )
    {
        write( check_beted_str( id ) );
        return notify_fail("押注格式： <bet 数量 to da|xiao|dan|shuang>\n");
    }
    // 可简化
    switch( type )
    {
        case "a":
        case "A": type = "da";   break;
        case "b":
        case "B": type = "xiao"; break;
        case "c":
        case "C": type = "dan";  break;
        case "d":
        case "D": type = "shuang";break;
        case "e":
        case "E": type = "baozi";break;
    }
    if( member_array( type , keys(type_str) ) == -1 )
        return notify_fail("押注格式： <bet 数量 to da|xiao|dan|shuang>\n");
    if( bet < 1 || bet > 10000 )
        return notify_fail("押注范围在 1 - 10000 两白银之间。\n");
    if( query("balance", me)<bet*100 )
        return notify_fail("你的存款不足 "+bet+" 两白银了。\n");
    // naihe add 人数限制 05-12-6 8:46
    if( member_array( id, df_player ) != -1 )
    {
        if( MAX_DF_PLAYER > 0 && sizeof(df_player) >= MAX_DF_PLAYER )
            return notify_fail("对不起，这局游戏押注的人已经太多了。\n");
        else
            df_player += ({ id });
    }
    bet_key = id + "-" + type;
    if( bet_info[ bet_key ] )
    {
        beted = bet_info[ bet_key ];
        if( beted + bet > 10000 )
            return notify_fail( "这局你已经押了 "+beted+" 两白银在 "
                +type_str[ type ]+" 上边了，合计本次超出了最大押注限制。\n"
            );
        bet_info[ bet_key ] = beted + bet;          // 修改该玩家当局的该项押注
        log_info[ "total_bet" ] += (bet*100);       // 总押注额记录
        this_bet += (bet*100);                      // 本局总押注额记录
        addn("balance", -(bet*100), me);
        message_vision( "$N拿过帐本大笔一挥，追加了 "+bet+" 两白银押  "+type_str[ type ]+ "。\n", me );
    }
    else
    {
        bet_info[ bet_key ] = bet;                  // 设置该玩家当局的该项押注
        log_info[ "total_bet" ] += (bet*100);       // 总押注额记录
        this_bet += (bet*100);                      // 本局总押注额记录
        addn("balance", -(bet*100), me);
        message_vision( "$N拿过帐本大笔一挥，把 "+bet+" 两白银押上了  "+type_str[ type ]+ "。\n", me );
    }
    write( check_beted_str( id ) );
    if( GameStat == 0 )
    {
        valid_gogo_time = time() + GOGO_WAIT_TIME;       // 过几秒才可以用 gogo 加速开奖。
        GameStat = 1;
        tell_room( this_object(), HIW"第 "+times_flag+" 局赌局将于 "+WAIT_TIME+" 秒后开始，要买的就快押啦！\n"NOR );
        remove_call_out( "game_start" );
        call_out( "game_start", WAIT_TIME, 0 );
    }
    //me->save();       // 不需要。玩家如果 quit 会 save()
    return 1;
}

// 加速开局，玩家接口函数
protected int do_gogo()
{
    if( GameStat != 1 )
        return notify_fail( "现在的状态不能开奖。可能是无人押注，或者是已在开奖中。\n");
    if( valid_gogo_time > time() )
        return notify_fail( "等等别人也押点再开吧！\n");
    message_vision( "$N大声叫道：快点开！立刻开！现在、马上、给我开！\n", this_player() );
    GameStat = 2;
    remove_call_out( "game_start" );
    call_out( "game_start", 1, 0 );
    return 1;
}