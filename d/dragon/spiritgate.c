#include <ansi.h>
inherit ROOM; 

int do_knock(string arg);

void create()
{
        set("short","忘忧园");
        set("long",
"你处在一个植满茶花的花园里，虽然还不是开花的时节，但是那些生\n"
"机勃勃的茶树，不禁让你感到心神清爽。草丛里有些小虫子正唧喁唧喁地\n"
"叫得正欢。\n");
        set("outdoors", "silu"); 
        set("exits",([ 
                "south"  : "/d/xingxiu/jiayuguan",
        ]));
        setup();
} 

void init()
{
        add_action("do_knock","knock");
}

int do_knock(string arg)
{ 
        object *member;
        int i;
        object env;
        string *ips;

        member = this_player()->query_team();
       
        if (!arg || arg != "spiritgate")
        {
                return notify_fail("你要敲什么？\n");
        }
        
        if( sizeof(member) != 4 )
                return notify_fail(HIG"如果队中成员数目不是正好为八之半，精灵之门不会开启。\n"NOR);

        if( ! this_player()->is_team_leader() )
                return notify_fail(HIG"队中成员中只有队长才能开启精灵之门。\n"NOR);

        env = environment(this_player());
        ips = ({ query_ip_number(this_player()) });
        for(i=0;i<sizeof(member);i++)
        {
                if (environment(member[i]) != env)
                        return notify_fail("你队中成员还有没有来齐的。\n");

                if( query("combat_exp", member[i])<2000000 )
                        return notify_fail("队中成员里有经验能力太低的,你们是进不了精灵界的。\n");
                        
                if( time()-query("boss/dragon", member[i])<3600 )
                        return notify_fail(HIG "队中成员里有离上次屠龙时间不足一个小时，精灵之门不会开启。\n" NOR);
        
                if (member_array(query_ip_number(member[i]), ips) == -1)
                        ips += ({ query_ip_number(member[i]) });
        }
/*
        if (sizeof(ips) < 4)
                return notify_fail(HIG"队中成员中只有 " + sizeof(ips) + " IP地址的人，精灵之门不会开启。\n"NOR);
*/

        for(i=0;i<sizeof(member);i++)
        {
                member[i]->move(__DIR__"spirit1"); 
                set("fighter", 0, member[i]);
                set("mark/diary", 0, member[i]);
                set("boss/dragon", time(), member[i]);
                set_temp("m_success/初级", 0, member[i]);
                set_temp("m_success/幻影", 0, member[i]);
                set_temp("m_success/孽龙", 0, member[i]);
                set_temp("m_success/琼草", 0, member[i]);
        }
        
        message_vision( HIG "$N在虚空中轻轻扣动几下，一阵优美的乐声中，$N被送到了一个奇异的地方！\n" NOR, this_player());
        message("channel:chat", HBMAG"【精灵神界】精灵之门开启，某小队进入了精灵神界，破解神龙的封印!\n"NOR, users());
        return 1;
}
