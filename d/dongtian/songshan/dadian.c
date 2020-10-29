// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h> 
inherit __DIR__"normal.c"; 

#define YXNUM 3000

void create()
{
        set("short", __DIR__"guangchang.c"->load_name() + "大殿");
        set("long", 
"走过前庭，正前方便是大殿所在，青山含翠，殿宇雄阔，大殿坐落峰顶\n"
"云气缭绕，时有仙鹤几只，长鸣飞过，在空中盘旋不去，如仙家灵境，令人\n"
"心生敬仰。顺桥继续前行，此时虹桥不再上升，在空中做个拱形，落在殿前\n"
"一湾碧水寒谭边。于此同时，大殿里隐隐传出仙乐歌诀，一派仙家气势。潭\n"
"水边，一条宽敞石阶，从水潭边向上直通殿门。潭水碧清，如镜，人影山影\n"
"清晰可见。走过高高石阶，远远便看到大殿门扉大开，里面光线充足，供奉\n"
"着盘古，女娲之神位，气度庄严。神位之前，大殿之上。站着数十余人，有\n"
"道有俗，看来都是门徒，个个神光内敛，面目和善，看来都是有道的修行者。\n"
);
                //set("outdoors", "yangzhou");
                set("exits",([ /* sizeof() == 1 */
                        "south" : __DIR__"qianting",
                        "north" : __DIR__"houdian",
                ]));

        set("no_steal",1);
        set("no_beg",1);         
                set("no_rideto", 1);
                set("no_flyto", 1);
        set("no_drift", 1);
        set("no_sleep_room", 1); //睡觉不雅观
        set("no_kill",1);
        //set("no_fight",1);

        set("owner_level", 1);
        set("max_carry_user" ,6);
        set("dongtianfudi", YXNUM);
        
        setup();
}

int discmdkill() 
{ 
        tell_object(this_player(), "你不能在这里毛手毛脚。\n");  
        return -1;  
} 

void init()
{
        object ob, me = this_player();
        if (playerp(me) && wiz_level(me) < 6) me->start_busy(2);
        if (query_temp("dongtian/user_cant_die", me)) {
                delete_temp("dongtian/user_cant_die", me);
                me->start_busy(60);//失败复活的代价
        }
        if ((playerp(me)||me->is_baby()) && !query_temp("dongtian/invite/armor", me)) {
                ob = new(__DIR__"armor");
                ob->reborn(me);
                if (ob->move(me)) {
                        set_temp("dongtian/invite/armor", ob, me);
                        tell_object(me, NOR YEL "金光一闪，傀儡侍卫扑向你身上...\n" NOR);
                } else {
                        destruct(ob);
                }
        } else if ( playerp(me) && objectp(ob = query_temp("dongtian/invite/armor", me)) ) {
                ob->fill();
                if( !query("consistence", ob) || query("consistence", ob) < 100 ) {
                        set("consistence", 100, ob);
                        tell_object(me, NOR CYN "灵气汹涌，你身上的洞天甲焕然一新。\n" NOR);
                }
        }
        if ((playerp(me)||me->is_baby()) && (query("dongtian/invite_item/charm_time", me)!=time()/86400)) {
                set("dongtian/invite_item/charm_time", time()/86400, me);
                ob = new(__DIR__"charm");
                ob->reborn(me);
                if (ob->move(me)) {
                        tell_object(me, NOR CYN "你听到飘渺的声音说道：赐下今日的气运符在身，\n  它对你在洞天内各场所的行动大有益处，赶快抓紧时间利用好吧。\n" NOR);
                        me->command("wear qiyun fu");
                } else {
                        destruct(ob);
                }
        }
        add_action("discmdkill", "kill"); 
        set("max_carry_user", 6 + 2 * query("zhen_type", get_object(__DIR__"guangchang")));
        set("dongtianfudi", YXNUM + query("apply/num_yanxi", get_object(__DIR__"guangchang")));
        ::init();
}

