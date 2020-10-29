// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include <room.h>

// inherit HARBOR;
inherit ROOM;

void create()
{
        set("short", "海滩");
        set("long", @LONG
这里就是名震江湖的桃花岛了。你放眼望去，除了海天交际处几点海
鸥的影子若隐若现，四周见不到一个人影，不由得心里一阵发慌。北面是
一片灿若云霞的桃林，繁花似锦，五色缤纷，但静悄悄的，似乎透着古怪。
桃林前立了一块石碑(shibei)，上面似乎有些字迹，旁边有一块大石(sto
ne)，海边泊着一艘大船(chuan)。
LONG );

        set("exits", ([
                "north" : __DIR__"thzhen1",
        ]));

        set("item_desc",([
                "shibei" : "
先天......伏羲......占其地利......
......后天......文王......得其天时......\n",

                "stone" : "大石上方有一块凹痕，象是一个扭曲的八卦形状。\n",
                "chuan" : "这是桃花岛对外联系的大船。岛上的客人或弟子只要\n"
                          "上船(enter)就可以回中原。\n",
        ]));

        set("outdoors", "taohua");

        set("island", "桃花岛");
        set("shape", "有一股夹着扑鼻花香的海风吹来。");
        set("navigate/locx", 30);
        set("navigate/locy", -180);

        set("coor/x", 9000);
        set("coor/y", -2000);
        set("coor/z", 0);
        setup();

}

void init()
{

        add_action("do_put", "put");
        add_action("do_pozhen", "pozhen");
        add_action("do_enter", "enter");
        add_action("do_pozhen","破阵");
}

int do_put(string arg)
{
        object me;
        string item, target;

        me = this_player();

        if (! arg || sscanf(arg, "%s in %s", item, target) != 2)
                return notify_fail("什麽？\n");

        if (! present("tie bagua", me))
                return notify_fail("什麽？\n");

        if (item != "tie bagua")
                return notify_fail("什麽？\n");

        if (target != "stone")
                return notify_fail("什麽？\n");

        message_vision("$N把铁八卦放入大石凹痕里\n", me);
        message_vision(HIW "只听得轧轧数声响，桃林向左右两边分开，一条小路出现在$N面前\n"
                       "$N连忙收起铁八卦，走入桃林。桃林在$N身后又恢复了原状。\n\n" NOR, me);

        me->move("/d/taohua/xiaojing");

        return 1;

}

int do_pozhen()
{
        object me;

        me = this_player();

        if (me->query_skill("qimen-wuxing", 1) < 120) 
        {
                me->receive_damage("jing", 50);
                me->receive_damage("qi", 50);
                message_vision("$N冥思苦想半晌不得其解，神困力疲，如同着了魔一样，居然一步步走向桃林\n", me);
                me->move("/d/taohua/thzhen1");
    
        } else 
        {

                message_vision(HIW "$N凝思片刻，桃林的种种生克变化已全盘了然于胸，\n"
                               "仰天一声长笑，袍袖一拂，掠入桃林，左一弯，右一转，已影踪不见\n" NOR, me);

        me->move("/d/taohua/xiaojing");
        }
        return 1;

}
int do_enter ( string arg )
{
        object ob ;
        string dir;
        if( !arg || arg !="chuan" ) 
        {
                tell_object(this_player() , "你要 enter 哪儿？\n" ) ;
                return 1 ;
        }
        ob = this_player () ;
        message_vision("船夫一见有人上船，忙叫了一声：开船喽！\n", ob);
        message_vision("船夫升起帆，船就向西方航行。\n", ob);
        ob ->move("/d/taohua/dahai") ;
        tell_object(ob, BLU "你在海上航行了很久很久.......\n" NOR ) ;
        call_out("rtaohua", 10 , ob );
        return 1 ;
}
void rtaohua( object ob )
{
        if (base_name(environment(ob)) != "/d/taohua/dahai")
                return;

        tell_object(ob , "大船终于抵达了中原的一个繁华城市。你走下船来。\n" ) ;
        ob->move ("/d/jiaxing/jiaxinggang") ;
}