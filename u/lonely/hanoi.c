// hanoi.c
// 汉诺塔是一种古老的数学游戏，有三个底座(base)，一开始
// 所有的盘子都按从小到大的顺序从上到下的放在第一个底座
// (base/A)里。其要求是把第一个底座中的盘子利用第二个底
// 座(base/B)全部移到第三个底座中。其中小的盘子只能放在
// 大的盘子上面，每次只能移动一个盘子。这个题目可以用递
// 归的方法求解(最少的完成步数 = 2 ^ 盘子数目 - 1)。

#include <ansi.h>
#define MAX my["max"] // 总共盘子数
#define START my["start"] // 开始游戏者
#define BASE my["base"] // 底座的状态
#define STEP my["step"] // 已走的步数

inherit ITEM;
inherit F_SAVE;
inherit F_AUTOLOAD;

int do_help(string arg);

int query_autoload() { return 1; }
string query_save_file() { return __DIR__ "hanoi/" + query("start"); }

void create()
{
        set_name(HIY "汉诺塔" NOR, ({ "hanoi" }));
        set_weight(100);

        set("long", "这是一套古老数学游戏汉诺塔的模型。\n");
        set("unit", "套");

        set("base", ([
                "A" : ({ }),
                "B" : ({ }),
                "C" : ({ }),
        ]));
}

// 提供指令
void init()
{
        add_action("do_new", "new");       // 新 游 戏
        add_action("do_stop", "stop");     // 结束游戏
        add_action("do_record", "record"); // 保存游戏
        add_action("do_load", "load");     // 载入游戏
        add_action("do_move", "move");     // 移动盘子
        add_action("do_help", "help");     // 帮助信息
}

// 显示目前状态
string long()
{
        mapping my = query_entire_dbase();
        mapping info;
        string *msg, line, base, long;
        int i, j, max;

        if( !START )
                return my["long"];

        info = ([ ]);
        max = MAX * 2 + 4;
        foreach( base in keys(BASE) ) {
                msg = ({ });
                BASE[base] = sort_array(BASE[base], 1);
                for( i = 0; i < MAX; i++ ) {
                        j = i - (MAX - sizeof(BASE[base]));

                        if( j < 0 )
                                line = repeat_string(" ", (max - 2) / 2) + WHT "│" NOR +
                                repeat_string(" ", (max - 2) / 2);
                        else {
                                line =  repeat_string(" ", (max - BASE[base][j] * 2) / 2) +
                                        CYN + repeat_string("--", BASE[base][j]) + NOR +
                                        repeat_string(" ", (max - BASE[base][j]* 2) / 2);
                        }

                        msg += ({ line });
                }
                info[base] = msg;
        }
        set("info", info);
        long = WHT "现在" + ((! STEP) ? "第一步还没走"
                : "已经走了 " + STEP + " 步") + "。\n\n" + NOR;

        for (i = 0; i < MAX; i++)
        {
                long += sprintf("%s%s%s\n", info["A"][i], info["B"][i], info["C"][i]);
        }
        return long;
}

int do_new(string arg)
{
        object me = this_player();
        mapping my = query_entire_dbase();
        int i, max;

        if (stringp(START))
                return notify_fail("游戏已经开始了，你得先停止它。\n");

        if (! arg) max = 3;
        else if (! sscanf(arg, "%d", max) || max > 9)
                return notify_fail("输入的格式错误。\n");

        START=query("id", me);
        MAX = max;
        STEP = 0;
        for (i = 0; i < max; i++)
        {
                BASE["A"] += ({ i + 1, });
        }

        write("游戏创建完毕，输入(help here)可以获得帮助。\n");
        write(long());
        return 1;
}

void end_game()
{
        delete("max");
        delete("start");
        delete("base");
        delete("step");
        set("base", ([
                "A" : ({ }),
                "B" : ({ }),
                "C" : ({ }),
        ]));
}

int do_move(string arg)
{
        object me = this_player();
        mapping my;
        string from, to;

        if (! arg || sscanf(arg, "%s to %s", from, to) != 2)
                return do_help("move");

        if (from == to)
                return notify_fail("你脑潮了？\n");

        my = query_entire_dbase();

        if( query("id", me) != START )
                return notify_fail("你可别乱动。\n");

        if (member_array(from, keys(BASE)) == -1 ||
            member_array(to, keys(BASE)) == -1)
                return notify_fail("底座只可能是" + implode(keys(BASE), "、") + "其中之一。\n");

        if (! sizeof(BASE[from]))
                return notify_fail("底座" + from + "那里可没有盘子呀。\n");

        BASE[from] = sort_array(BASE[from], 1);
        BASE[to] = sort_array(BASE[to], 1);

        if (sizeof(BASE[to]) && sizeof(BASE[from]) && BASE[to][0] < BASE[from][0])
                return notify_fail("大的盘子不能放在小的盘子上面。\n");

        tell_object(me, WHT "你把底座" + from + "的" + chinese_number(BASE[from][0])+ "号盘子移动到了底座" + to + "上。\n" NOR);

        BASE[to] = ({ BASE[from][0] }) + BASE[to];
        BASE[from] -= ({ BASE[from][0] });
        STEP++;
        write(long());

        if (sizeof(BASE["C"]) == MAX)
        {
                write(WHT "\n恭喜你完成了游戏。\n" NOR);
                end_game();
        }

        return 1;
}

int do_stop(string arg)
{
        object me = this_player();
        mapping my;

        my = query_entire_dbase();

        if (! stringp(START))
                return notify_fail("还没开始呢，结束个啥？\n");

        if( query("id", me) != START )
                return notify_fail("只有游戏进行者才能结束这个游戏。\n");

        end_game();
        write(WHT "你结束了当前的游戏。\n" NOR);
        return 1;
}

int do_record(string arg)
{
        object me = this_player();
        mapping my;

        my = query_entire_dbase();

        if (! stringp(START))
                return notify_fail("还没开始呢，保存个啥？\n");

        if( query("id", me) != START )
                return notify_fail("只有游戏进行者才能保存游戏。\n");

        save();
        write(WHT "当前游戏保存完毕。\n" NOR);
        return 1;
}

int do_load(string arg)
{
        object me = this_player();
        mapping my;

        my = query_entire_dbase();

        if (stringp(START))
                return notify_fail("游戏已经开始了，你还是先把它停止吧。\n");

        if( file_size(__DIR__"hanoi/"+query("id", me)+".o") <= 0 )
                return notify_fail("你并没有保存过游戏呀。\n");

        START=query("id", me);
        restore();
        write(WHT "上一次的游戏载入完毕。\n" NOR);
        write(long());
        return 1;
}

int do_help(string arg)
{
switch (arg)
{
case "here":
        write(@HELP
在这里你可以使用以下这些和汉诺塔相关的命令：
new 开始一局新游戏
stop 结束这局游戏
record 保存当前的游戏
load 载入保存的游戏
move 移动一个盘子
HELP );
        break;

case "new":
        write(@HELP_NEW
指令格式 : new [盘子数目]

此指令让你开始一局新的汉诺塔游戏，当这套汉诺塔已经开始了游戏
时，你必须先把这个游戏关闭(stop)。建议你在关闭前保存(record)。
你可以指定游戏中初始盘子的数目，但最多不得超过 9个，一开始盘
子会全部被放到底座 A中，你需要把它们全部一个个移(move)到底座
C 中就是赢得胜利。注意：大的盘子不得放在小的盘子上面。

相关指令：stop, record, move
HELP_NEW );
        break;

case "stop":
        write(@HELP_STOP
指令格式 : stop

停止这局游戏，你必须是这局游戏的进行者才能这么做。

HELP_STOP );
        break;

case "record":
        write(@HELP_RECORD
指令格式 : record

此指令让你保存现在正在进行的游戏以备下次继续玩，你必须是这局
游戏的进行者才能这么做。保存以后可以用(load)在没有游戏正在进
行的情况下调入。注意：假如你这个 ID 以前已经保存过游戏，那么
会把以前的游戏档案覆盖掉。

相关指令：load
HELP_RECORD );
        break;

case "load":
        write(@HELP_LOAD
指令格式 : load

载入一个你上次玩的游戏，得先停止(stop)目前的游戏再说。

相关指令：record, stop
HELP_LOAD);
        break;

case "move":
        write(@HELP_MOVE
指令格式 : move A to B

把底座 A、B、C 中最上面的一个盘子移动到另一个底座中去，大的
盘子不得放在小的盘子上面。当你把底座 A 的所有盘子都移到了底
座 C 中，就会获胜并结束这局游戏。
HELP_MOVE );
        break;

default:
        return notify_fail("你要查看什么帮助？\n");
}

return 1;
}
