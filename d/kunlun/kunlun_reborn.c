// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "昆仑之巅");
        set("long", @LONG
四下无声，只有风吹松涛，幽韵天成，仰视苍天，注视群山，令
人不觉怆然而发思古之幽情！往前看，只见一块很大的冰壁，下临绝
崖，大冰壁表面极其光滑，如同镜子一般，散发出奇异的光芒，往下
看，峭壁如刀削，云卷雾涌，深不见底。
LONG );
        set("exits", ([
                "down" : __DIR__"kunlun5",
        ]));

        set("outdoors", "kunlun");
        setup();
}

void init()
{
        add_action("do_throw", "throw");
        add_action("do_enter", "enter");
}

int do_throw(string arg)
{
        object me, ob;
        
        me = this_player();
        if( !objectp( ob = present("contract", me) ) ||
            query("owner", ob) != query("id", me) )
                return 0;
        
        if( !query("reborn_offer", me) || query("reborn_offer", me) != "finish" )
                return 0;
                         
        if( !arg || arg != "contract" ) 
                return notify_fail("你要用什么掷向那冰壁？\n");      
                    
        message_vision( HIW "$N" HIW "将泛紫光的阎王契(Contract)掷向那冰壁，阎王契没入其中、竟尔消失不见。\n"
                        HIW "只见本就平滑的大冰壁愈见光洁、而后渐渐透明，渐渐化作了水银镜般的模样，\n"
                        HIW "原来这正是通往地狱的通道：" HIR "「昆仑镜」" HIW "(enter mirror)。\n" NOR, me );
        set_temp("throw_contract", 1, me);
        destruct(ob);
        return 1; 
}

int do_enter(string arg)
{
        object me, *inv;
        int i;
        
        me = this_player();
        if( !query_temp("throw_contract", me) )
                return 0;
                
        if( !arg || arg != "mirror" ) 
                return notify_fail("你想要去那里？\n");      
        
        inv = deep_inventory(me);
        for( i=sizeof(inv)-1; i>=0; i-- ) {
                if( objectp(inv[i]) && inv[i]->is_character() ) {
                        tell_object(me, "你不可以将其他玩家或者NPC(包括宠物)背进昆仑镜中。\n");
                        return 0;
                }
        }
        
        message_vision( HIW "$N" HIW "谨慎举步，缓缓走入了昆仑镜中。\n" NOR, me );
        tell_object(me, HIM "只见四周俱是五彩瑰丽景象，如临仙境，好半晌后你才回过神、走出隧道，来到幽冥界。\n" NOR);
        delete_temp("throw_contract", me);
        me->move("/d/death/youmingjie");
        set("startroom", "/d/death/youmingjie", me);
        message("vision",HBRED"【转世重生】地府："+query("name", me)+"("+query("id", me)+")"
                HBRED "进入幽冥界，欲挑战幽冥地府考验，换取转世奇缘！\n" NOR, users());
        return 1;
}
