// /d/gaoli/yingbinguan.c
// Room in 高丽
inherit ROOM;

string look_sign(object me);

void create()        
{
        set("short", "迎宾馆");
        set("long", @LONG
你现在正站在高丽的迎宾馆里，迎宾馆不仅招待使节，还招待各路
客商，来自中原的旅人都喜欢聚集在这里交换旅途上的见闻，你也可以
在这里打听到许多有趣的消息。靠近门口的地方有一块乌木雕成的招牌
(sign)。
LONG
        );
set("valid_startroom", 1);
set("item_desc", ([
                "sign": (: look_sign :),
                ]));
set("exits", ([
                "north":__DIR__"yudao8",
                "up":__DIR__"kefang",
        ]));
       setup();
        
        
set("objects", ([
        __DIR__"npc/xiaoer" : 1, 
]));

        setup();
        }


string look_sign(object me)
{
        if( wizardp(me) )
    return "招牌写著：猛鬼客栈。\n";
        else
        return "招牌写著：内设雅房，每夜五两白银。\n";
}
int valid_leave(object me, string dir)
{

        if ( !me->query_temp("rent_paid") && dir == "up"&&me->query("family/family_name")!="弈剑派" )
                return notify_fail("怎么着，想白住啊！\n");

        if ( me->query_temp("rent_paid") && dir == "north" )
                return notify_fail("客官已经付了银子，怎么不住店就走了呢！旁人还以为小店伺候不周呢！\n");

        return ::valid_leave(me, dir);
}
