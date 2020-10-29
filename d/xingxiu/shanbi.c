// Room: /d/xingxiu/shanbi.c
// Last Modified by Lonely on Apr. 25 2001

inherit ROOM;

void create()
{
        set("short", "山壁");
        set("long", @LONG
一条草草在山壁上人工开凿出来崎岖的小路，几个星宿弟子正在埋
头苦干。这里，寒风凛冽，西面是望浩浩百里方圆的星宿海。东边山壁
上，尽是星宿弟子用力砸出的坑凹(ao)。
LONG
        );
        set("exits", ([
                "southdown" : __DIR__"xiaolu",
        ]));
        set ("item_desc", ([
                "ao" : "是人用棍杖撞击(za)山壁(bi)留下的痕迹。\n"
        ])) ;
        set("objects", ([
                __DIR__"npc/gushou"  : 1,
        ]));
        set("outdoors", "xingxiu");
        set("coor/x", -49900);
        set("coor/y", 20300);
        set("coor/z", 100);
        setup();
}

void init()
{
        add_action("do_za", "za");
}

int do_za(string arg)
{
        object  weapon, me = this_player();
        int ging_cost, qi_cost, jingli_cost;
        weapon=query_temp("weapon", me);
        ging_cost=150/query("int", me);
        qi_cost=200/query("con", me);
 
        if (!living(me)) return 0;
        if ( arg != "bi" ) return notify_fail("你要撞击什麽？\n");
        if (!weapon) return notify_fail("你用什么砸山壁来练功？\n");  
        if( query("skill_type", weapon) == "staff" )
                if ((int)me->query_skill("staff", 1) >= 120) 
                        return notify_fail("你已经不用再在这里费功夫了。\n");  
        if( query("skill_type", weapon) == "hammer" )
                if ((int)me->query_skill("hammer", 1) >= 120) 
                        return notify_fail("你已经不用再在这里费功夫了。\n");  
        if( random(query("kar", me))<3 )
        {
                message_vision("$N一不小心砸到自己脚上，痛得晕了过去。\n",me);
                me->unconcious();
                return 1;
        }
        if( (query("jing", me)<ging_cost) || (query("qi", me)<qi_cost) )
        {
                message_vision("$N猛地砸在山壁上，结果用力过度！\n", me);
                me->unconcious();
                return 1;
        }
        message_vision("$N使劲撞击山壁，在山壁上砸出一个坑凹。\n", me);
        if( query("skill_type", weapon) == "staff" )
                me->improve_skill("staff", me->query_skill("staff", 1));
        else if( query("skill_type", weapon) == "hammer" )
        me->improve_skill("hammer", me->query_skill("hammer", 1));
        me->receive_damage("jing", ging_cost );
        me->receive_damage("qi", qi_cost );
        return 1;     
}