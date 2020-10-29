//                标准描述长度示例                                   |
// 幻境内物品  其他类型（包括补充HP的物品）
// by naihe  2002-10-25  于茂名

#include <ansi.h>

inherit ITEM;


string *names=({
    "无名果",
    "仙人果",
    "淘气之果",
    "毒龙果",
    "野生果实",
    ""HIR"红色宝石"NOR"",
    ""HIG"绿色宝石"NOR"",
    ""HIB"蓝色宝石"NOR"",
    ""YEL"试炼之果"NOR"",
});

string *ids=({
    "wm guo",
    "xr guo",
    "tq guo",
    "dl guo",
    "ys guo",
    "red baoshi",
    "green baoshi",
    "blue baoshi",
    "sl guo",
});

string *heal_hps=({
    "yes",
    "yes",
    "yes",
    "yes",
    "yes",
    "no",
    "no",
    "no",
    "yes",
});

string *longs=({
    "这是一枚很小的不知名的果实，你可以把它吃下(chixia)。\n",
    "这是一枚小小的果子，名叫“仙人果”，相传是仙人们吃了增加道行的东西。\n你可以把它吃下(chixia)。\n",
    "这枚果子怪模怪样的，但却有补血活气的功效。你可以把它吃下(chixia)。\n",
    "这是一枚毒龙果，相传是远古毒龙曾用于疗伤的果品。\n人类吃下(chixia)了可不知道会发生什么事。\n",
    "这是一枚野生果实，在林子里随处可见。你可以把它吃下(chixia)。\n",
    "这是一颗红色的宝石，散发着迷人的幽幽光芒。\n",
    "这是一颗绿色的宝石，散发着迷人的幽幽光芒。\n",
    "这是一颗蓝色的宝石，散发着迷人的幽幽光芒。\n",
    "这是一枚“试炼之果”，似有特别神奇的功效。你可以把它吃下(chixia)试试看。\n",
});


void setme( int iii )
{
    if( iii == 99 ) iii = random( sizeof(names) );
    set("iii", iii );

    if( iii < 5 ||  iii == 8)
        set_name(names[ iii ], ({ids[ iii ],"guo"}));
    else set_name(names[ iii ], ({ids[ iii ] , "baoshi", "bao shi", "bs" }));

    set_weight(100);

    if (clonep())
        set_default_object(__FILE__);

    set("long", longs[ iii ]);
    set("heal_hp",heal_hps[ iii ]);
    set("unit", "枚");
    set("value", 0);  // 该物扔下后将消失
    //set("no_refresh", 1); // 此类允许被MUD刷掉

    set("hj_game/obj","other");
}


void create()
{
    setme( 99 );
    setup();
}

void init()
{
    if( query("heal_hp") == "yes") add_action("do_chixia","chixia");
}

int do_chixia(string arg)
{
    object ob,me;
    int temp,temp1,temp_add;

    if( !query("room_mark", environment(this_player())) && !wizardp(this_player()) )
        return 0;

    me=this_player();
    ob=this_object();

    if( !arg || query_temp("huanjing", me) != "start" || query_temp("hj_hp", me)<1 )
        return 0;

    if( !query_temp("hj_hp_max", me))return 0;
    if( !query_temp("hj_game_mepower", me))return 0;

    if( query("heal_hp") != "yes" || !arg || !id(arg) )
        return 0;
    //if(me->is_busy()) return notify_fail("你还忙着呢，小心吃了噎着。\n");
    // 不限制忙时，否则果品没什么大用处。

    if( query("id", ob) == "slguo" )
    {
        if( !random(3) )
        {
            if( random(3) )
            {
                message_vision(CYN"$N"NOR+CYN"吞下一"+query("unit", ob)+query("name", ob)+""NOR+CYN"，顿时觉得精神一振，似乎力量增强了一点！\n"NOR,me);
                addn_temp("hj_game_mepower", 1, me);
            }
            else
            {
                message_vision(CYN"$N"NOR+CYN"吞下一"+query("unit", ob)+query("name", ob)+""NOR+CYN"，顿时觉得精神一振，似有无穷内息涌涌而来！\n"NOR,me);
                addn_temp("hj_hp_max", 10+random(11), me);
            }
        }
        else
        {
            message_vision(CYN"$N"NOR+CYN"吞下一"+query("unit", ob)+query("name", ob)+""NOR+CYN"，但觉腹中绞痛，看来是吃下了有毒的东西！\n"NOR,me);
            addn_temp("hj_hp", -(20+random(31)), me);
        }

        destruct(ob);
        return 1;
    }

// 无论是否饱和都能吃，但最多也就加到 MAX HP 。
// 若是饱和状态下吃，将会增加忙时！
// 否则无忙时。

    temp=query_temp("hj_hp", me);

    if( temp >= query_temp("hj_hp_max", me) )
    {
        me->start_busy(2);
        tell_object(me,"你吃得饱饱的，差点给噎住了。\n");
    }

    switch(query("id", ob) )
    {
        case "wm guo":temp_add=10+random(11);break;   //  10-20
        case "tq guo":if(random(2)) temp_add=1;  //  1 or 30
            else temp_add=30;break;
        case "xr guo":temp_add=30+random(21);break;   //  30-50
        case "dl guo":temp_add=100-random(150);break; //  -50  -  100
        case "ys guo":temp_add=10;break;              //  10
    }
    temp_add *= 3;  // 加强效力

    temp1 = 1 + temp_add + temp;

    if( temp1>query_temp("hj_hp_max", me) )
        temp1=query_temp("hj_hp_max", me);

    set_temp("hj_hp", temp1, me);
    if( temp_add>=0 )
    message_vision(CYN"$N"NOR+CYN"吞下一"+query("unit", ob)+query("name", ob)+""NOR+CYN"，顿时觉得精神一振。\n"NOR,me);
    else 
    message_vision(CYN"$N"NOR+CYN"吞下一"+query("unit", ob)+query("name", ob)+""NOR+CYN"，只觉得腹如绞痛，看来是吃下了有毒的东西！\n"NOR,me);

    destruct(ob);
    return 1;
}