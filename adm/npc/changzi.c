// This program is a part of NITAN MudLIB 
// redl 2013/3
#include <ansi.h>

inherit NPC;

int get_reward()
{
                int amount;
        object me, obj;
        me = this_player();
        
        if( query("online_time", me) < 3600){
                tell_object(me,CYN + query("name") + "深情地看了你一眼说：你在线时间还没有超过一小时吧？\n"+ NOR); 
                return 1;
        }      
        amount = query("active", me);
        if( amount < 1){
                tell_object(me,CYN + query("name") + "面孔扭曲地说：你至少也要有1点活跃度才能来我这兑换呀！\n"+ NOR); 
                return 1;
        }
        if( time() - query("active_endtime", me) < 3600){
                tell_object(me,CYN + query("name") + "抠了抠鼻孔，慢悠悠地说：活跃度每小时兑换一次！\n"+ NOR); 
                return 1;
        }
        
        if (amount > 100) amount=100;
        addn("active", -amount, me);
        
                if( query("online_time", me) < 86400) obj = new(__DIR__"obj/xianghy");//一天以内的新玩家，可以抽到天赋丹和低级rune
                else obj = new(__DIR__"obj/xianghy2");//一天以上的老玩家可以抽到中高级rune
                
                obj->set_amount(amount);
        message_vision(YEL + query("name") + NOR + YEL+ "拿出"+chinese_number(amount)+"个箱子交给"+ NOR +"$N"+ NOR + YEL+"。\n" + NOR, me);        
        obj->move(me);
        set("active_endtime", time(), me);
        return 1;
}      

void create()
{
        set_name(NOR "小常子" NOR, ({ "xiao changzi", "xiao", "changzi" }));
         set("nickname", YEL "聊天室伙计" NOR);
        set("long", @LONG
泥潭捡大粪先行者，金盆洗手后在公共聊天室端茶递水。
LONG);
        set("gender", "男性" );
        set("age", 30);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("combat_exp", 1200000);

        set("inquiry", ([
                        "奖池" : (: call_other("/u/redl/obj/cigarette_c", "ask_pond", query("name") ) :) ,
                "宝箱" : (: get_reward :),
                "活跃度" : (: get_reward :),
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();

}


