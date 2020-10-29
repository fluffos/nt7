#include <room.h>
#include <ansi.h>
#include <getconfig.h>
inherit ROOM;

int do_look(string arg);

void create()
{
    set("short", HIY"休息室"NOR);
        set("long", @LONG
这是一个装饰豪华，色调温暖的小房间，到处摆放着各种珍奇古
玩。宽大的真皮沙发柔软舒适，大款们来到这里都会坐下来，讨论一
下泥巴商业运作情况。休息室大门通向金色走廊，另一面墙壁有一道
小门，平常紧闭着，只有在每两月一次的泥巴黑店拍卖时，巫师才会
将之打开。一块小小的牌子 (paizi)挂在东面墙上，这是巫师宣布黑
店拍卖底价用的。
LONG );

    set("no_fight",1);
    set("no_beg",1);
    set("no_steal",1);

    set("exits", ([
        "south"  : "/d/city/pm_road8",
    ]));

    set("no_clean_up", 0);
    setup();
}

void init()
{
    add_action("do_look","look");
    if (wiz_level(this_player()) > 2)
    {
        add_action("do_open","open");
        add_action("do_close","close");
    }
}

int do_open()
{
    if (query("exits/north"))
        return notify_fail("门已经是开着的了。\n");
    set("exits/north","/clone/SHOP/pmc");
    message_vision(HIY"$N轻轻一推，将通向拍卖大厅的小门开启了。\n"NOR,this_player());
    shout(HIY + this_player()->name() +  "开启了拍卖休息室里那扇通往拍卖大厅的金色小门！\n" NOR);
    write(HIY + "你开启了拍卖休息室里那扇通往拍卖大厅的金色小门！\n" NOR);
    return 1;
}

int do_close()
{
    if (!query("exits/north"))
        return notify_fail("门已经是关着的了。\n");
    delete("exits/north");
    message_vision(HIY"$N顺手一带，将通向拍卖大厅的小门关闭了。\n"NOR,this_player());
    return 1;
}

int do_look(string arg)
{
    int i;
    string msg;
    mapping *SHOP_record;

    if (arg != "paizi") return 0;
    if (!query("exits/north"))
    {
        write("现在尚未到拍卖黑店的时间。\n");
        return 1;
    }

    SHOP_record = SHOP_D->query_SHOP();
    msg = HIC +LOCAL_MUD_NAME()+ HIY "黑店" HIC " 拍卖底价表：\n"NOR;
    msg += HIC "-------------------------------------------------------------------------\n" NOR;
    msg += sprintf(HIW"%-20s%-20s%-20s\n"NOR,"黑店ID","黑店名字","拍卖底价");
    for (i = 0;i < sizeof(SHOP_record);i++)
        msg += sprintf(HIY"%-20s%-20s%-20d\n"NOR,
            SHOP_record[i]["id"],
            SHOP_record[i]["name"],
            SHOP_record[i]["price"]
            );
    msg += HIC "-------------------------------------------------------------------------\n" NOR;
    msg += HIC "一共 " HIR + chinese_number(sizeof(SHOP_record)) + HIC " 家黑店\n";
    write(msg);
    return 1;
}