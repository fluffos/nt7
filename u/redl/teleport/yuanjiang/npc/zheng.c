// This program is a part of NITAN MudLIB 
// redl 2015/10
#include <ansi.h>
inherit NPC;

int get_help()
{
        write( CYN + query("name") + CYN + "说道：金船里遗留有广成子当年所练的金丹，有几率提高智慧和修为。\n"+ NOR); 
        return 1;
}

int get_help2()
{
        write( CYN + query("name") + CYN + "说道：金蛛乃太古异种，力大无比。如果你有金蛛给我，可以单独和你合作。\n"+ NOR); 
        return 1;
}

int get_help3()
{
        write( CYN + query("name") + CYN + "说道：天字舱分为“癸壬辛庚己戊丁丙乙甲”十个，持续touch舱门可以从癸推动到甲，舱门前不会自动PK，可以考虑合力加快。\n"+ NOR); 
        return 1;
}

int get_help4()
{
        write( CYN + query("name") + CYN + "说道：金船地图巨大，用maphere -m比单纯的maphere要望得远些，有特殊出口处必定是舱门所在。\n"+ NOR); 
        return 1;
}

int get_help5()
{
        write( CYN + query("name") + CYN + "说道：元磁力是修炼元磁道术的必需材料，在金船里使用xi指令可以获得元磁力，在天字十个舱里尤其丰富。\n"+ NOR); 
        return 1;
}

int get_help6()
{
        write( CYN + query("name") + CYN + "说道：元磁道术是各种能激发在taoism上的特殊道家武学。比如玄离刀罡可以使你用绝招时多出两招，小心晓月禅师擅长此道。\n"+ NOR); 
        return 1;
}

int get_help7()
{
        write( CYN + query("name") + CYN + "说道：铁箱里的小元磁力爆炸是单独计算的，能清零你受到的金船大元磁力累积伤害，打开它是件好事。\n"+ NOR); 
        return 1;
}

int get_help8()
{
        write( CYN + query("name") + CYN + "说道：仙隐符叶让别的玩家和水鬼，都很难发现有你存在的踪迹，但小心跌倒哦。\n"+ NOR); 
        return 1;
}

int get_reward()
{
                int amount;
        object room, me, obj, *inv;
        me = this_player();
        
        if(me->is_busy()) {
                        write(NOR "你正忙着呢。\n" NOR);
                        return 1;
        }
        me->start_busy(1);

        if( query("online_time", me) < 86400 * 7){
                tell_object(me,CYN + query("name") + CYN + "说道：你在线年龄都没有超过一周，是小号吧？\n"+ NOR); 
                return 1;
        }      
        
        amount = query("combat_exp", me);
        if( amount < 1000000000){
                tell_object(me,CYN + query("name") + CYN + "说道：你这点点经验进去能干什么？\n"+ NOR); 
                return 1;
        }
        
        if( objectp(query_temp("is_riding", me)) ){//飞行法阵已经限制了背玩家进来，以及很多意外的情况
                tell_object(me,CYN + query("name") + CYN + "说道：下马先？\n"+ NOR); 
                return 1;
        }      
        
        if( query("weiwang", me) < 1000000){
                tell_object(me,CYN + query("name") + CYN + "说道：你的威望太低了，我只和成名人物合作。\n"+ NOR); 
                return 1;
        }
    
        room = environment(this_object());
        if (query("blv", room) < 9){
                tell_object(me,CYN + query("name") + CYN + "说道：你来得太晚了，打捞已经开始。\n"+ NOR); 
                return 1;
        }
        
      if( query("gcjinchuan_time", me) >= query("gcjinchuan_time", room) ) 
        {
                tell_object(me,CYN + query("name") + "说道：你进出地过于频繁了！\n"+ NOR); 
                return 1;
       }
        //DEBUG_CHANNEL("player gcjinchuan_time：" + (string)query("gcjinchuan_time", me));
        //DEBUG_CHANNEL("room gcjinchuan_time：" + (string)query("gcjinchuan_time", room));
        
                addn("weiwang", -30000, me);
                tell_object(me, NOR "你被扣除三万点江湖威望。\n"+ NOR); 
                message_vision(append_color(NOR + CYN + query("name") + CYN + "一挥衣袖，$N" + NOR + CYN + "奋起跳上了元江宝船。\n" + NOR, CYN), me);
                set("gcjinchuan_time", query("gcjinchuan_time", room), me);
                me->move(get_object("/u/redl/teleport/yuanjiang/jiaban"));
                CHANNEL_D->channel_broadcast("rumor", "听说" + query("name", me) + "已经赶赴元江的广成金船夺宝。\n");
        return 1;
}      

void create()
{
        set_name( "郑颠仙" , ({ "zheng dianxian", "zheng" }));
        set("long", @LONG
此乃大熊岭苦竹庵主人，元江夺宝的倡议者。
LONG);
        set("gender", "女性" );
        set("title", NOR HIC "大颠上人" NOR);
        set("age", 45);
        set("level", 200);
        set("attitude", "friendly");
        set("max_jing", 500000000);
        set("max_qi", 500000000);
        set("max_jingli", 500000000);
        set("jingli", 500000000);
        set("max_neili", 500000000);
        set("neili", 500000000);
        set("jiali", 5000000);
        set("str", 200);
        set("int", 200);
        set("con", 200);
        set("dex", 200);
        set("combat_exp", 120000000000);

        set("inquiry", ([
                "广成金丹" : (: get_help :),
                "广成金船" : (: get_reward :),
                "boat" : (: get_reward :),
                "金蛛" : (: get_help2 :),
                "天字舱" : (: get_help3 :),
                "地图" : (: get_help4 :),
                "元磁力" : (: get_help5 :),
                "元磁道术" : (: get_help6 :),
                "铁箱" : (: get_help7 :),
                "box" : (: get_help7 :),
                "仙隐符叶" : (: get_help8 :),
                "leaf" : (: get_help8 :),
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();

}


int push_down(object me)
{
        if (!me) return 1;
        if (!environment(me)) return 1;
        if (environment(me)!=environment(this_object())) return 1;
        
        message_vision(append_color(NOR + CYN + query("name") + CYN + "一挥衣袖，$N" + NOR + CYN + "狼狈地往外面退去。\n" + NOR, CYN), me);
        me->move(query("exits/out", environment(this_object())));
        return 1;
}

void init()
{
        object me = this_player();
        
        //remove_call_out("push_down");
        //call_out("push_down", 60, me);
}


int accept_object(object me, object obj)
{
        object room;
        int *t;
        
        if (me->is_busy())
        {
                tell_object(me, NOR BUSY_MESSAGE NOR); 
                return 0;
        }
        else 
                me->start_busy(2);
                
        if (!query("is jin zhu", obj)){
                tell_object(me, NOR CYN + query("name") + CYN + "摇头对你说道：我只需要金蛛。\n" NOR); 
                return 0;
    }

/*        if( query("online_time", me) < 86400 * 2){
                tell_object(me,CYN + query("name") + CYN + "说道：你在线年龄都没有超过两天，是小号吧？\n"+ NOR); 
                return 0;
        }      */
        
       t = TIME_D->analyse_time(TIME_D->query_real_time());
       if (t[1]>=19 && t[1]<21)
        {
                tell_object(me, NOR CYN + query("name") + "摇头道：１９～２１点之间不允许私人打捞。\n"+ NOR); 
                return 0;
       }

        room = environment(this_object());
        if (query("blv", room)){
                tell_object(me, NOR CYN + query("name") + CYN + "说道：你来得太晚了，打捞已经开始。\n"+ NOR); 
                return 0;
        }
        
      if( query("gcjinchuan_time", room) && //等于重启后第一次用金蛛进去的玩家不受这个CD限制
        query("gcjinchuan_time", me) >= query("gcjinchuan_time", room) ) 
        {
                tell_object(me, NOR CYN + query("name") + "说道：你进出地过于频繁了！\n"+ NOR); 
                return 0;
       }
       
        tell_object(me, NOR CYN + query("name") + CYN + "点头对你说道：请稍带片刻。\n" NOR); 

                message_vision(append_color(NOR + CYN + query("name") + CYN + "一挥衣袖，$N" + NOR + CYN + "奋起跳上了元江宝船。\n" + NOR, CYN), me);
                set("gcjinchuan_time", query("gcjinchuan_time", room), me);
                me->move(get_object("/u/redl/teleport/yuanjiang/jiaban"));
        
        room->cdeploy(me);
        return 1;
}



