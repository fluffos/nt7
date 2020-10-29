//By rama@lxtx

inherit ITEM;

#include <ansi.h>

string *xc_msg1 =({
        "你神秘兮兮的四处张望xc_place的每个角落，",
        "你大模大样在xc_place转了几个圈子，",
        "你满脸严肃的仔细查看xc_place的情况，",
        "你仔细观察了xc_place的情况，",
        "你在xc_place来回的巡查了几遍，",
        "你细心留意xc_place上的陌生面孔，",
        "你向街上的人打探了xc_place近日的情况，",
        "你留意了下xc_place近来的变化，",
});
string *xc_msg2 = ({
        "据你的观察来看，xc_place，",
        "以现在的情况来看，xc_place",
        "你觉得xc_place",
        "你默默在心里记下---xc_place",
});

string *xc_msg3 = ({
        "没有发现任何可疑之处。",
        "一切正常。",
        "没有任何异常的迹象。",
        "一切太平。",
        "一切相安无事。",
});

string look_it(object me);
void create()
{
        set_name(HIG"巡城腰牌"NOR, ({ "yao pai","pai" }) );
        set_weight(600);
        /*if( clonep() )                 
        set_default_object(__FILE__);
        else*/ {
                set("unit", "块");
                set("long", "这是一块"HIW"属于帮派"NOR"的巡城腰牌，带上它可以巡逻(xunluo)帮派地盘。\n");
                set("value", 0);
             }   
}

void init()
{
        add_action("do_xunluo","xunluo");
}

int do_xunluo(object me, object ob)
{
        string the_place, msg1, msg2, msg3;
        mapping renwu;
        me=this_player();
        renwu=query("bunch_quest", me);
        
        if( !mapp(renwu) )
                return notify_fail("你目前没有领取任何帮派任务！\n");
        
        if( renwu["id"]!="xc")
                return notify_fail("老大没有让你来巡城啊！\n");
        
        the_place = base_name(environment(this_player()));
        if (member_array(the_place,renwu["place"]) != -1)
        {
                msg1 = replace_string(xc_msg1[random(sizeof(xc_msg1))],"xc_place",the_place->short());
                msg2 = replace_string(xc_msg2[random(sizeof(xc_msg2))],"xc_place",the_place->short());
                msg3 = xc_msg3[random(sizeof(xc_msg3))];
                renwu["place"] -= ({ the_place });
                tell_object(me, msg1+msg2+msg3+"\n马上去巡查下一个地方吧！\n");
        }
        else
                tell_object(me,"你没必要在这里巡逻啊！\n");
                
        return 1;
}