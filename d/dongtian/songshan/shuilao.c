// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h> 
inherit ROOM; 

int clean_up() { return 1;}

int do_cantsave()
{
        object me = this_player();
                tell_object(me, NOR "这是牢里，你老实点吧。\n" NOR);
                return -1;
}

int do_action(string arg)
{
        string action = query_verb();
        object me = this_player();
        
        if (me->is_busy() && action!="stat") {
                tell_object(me, NOR "你还是忙完手头上的事情再说吧。\n" NOR);
                return -1;
        }

        if (query("dongtian/prison/time", me) > query("online_time", me) && action!="tell" && action!="reply" && action!="look" && action!="say" && action!="stat") {
                me->start_busy(2);
                if (action=="chat" || action=="rumor" || action=="ask1") tell_object(me, NOR "你张口欲喊，墙壁上射出几股臭水喷了你一脸。\n" NOR);
                        else tell_object(me, NOR "你胡乱扭摆身体，陷在齐腰深的水里却动不了。\n" NOR);
                return -1;
        }
        
        if (action=="tell" || action=="reply") {
                me->start_busy(60);//远处说话避免持续骚扰
        }
        
        return 0;
}

int throwing(object me, int i)
{
        int c, p = query("dongtian/prison/num", me);
        
        if (undefinedp(p) || !p) p = 0;
        
        c = (60 * i) * (10 + p) / 10;
        if (c > 86400) c = 86400;
        set("dongtian/prison/ti", i, me);
        set("dongtian/prison/time", query("online_time", me) + c , me);
        set("dongtian/prison/num", p + 1, me);
        
        message_vision(append_color(NOR + YEL + "虚空中穿过来一只大如山岳的巨掌，对着$N" + NOR + YEL + "拦腰一捞，再缩回去就此不见了。\n" + NOR, YEL), me);
        me->move(this_object());
        return 1;
}

int delay_msg(string msg, object me)
{
        message_vision(msg, me);
        return 1;
}

void init()
{
        object *prisoners, me = this_player();
        string cti;
        
        add_action("do_cantsave", ({
                "push", "save", "get", "uget", "drop", "quit", 
                "home", "exit", "recall", "team", "chatroom", 
                "rideto", "array", "battle", "accept"}));

        if ( wiz_level(me) > 6 ) {
                //add_action("do_free", "fr");
                return; 
        }
        if (query("dongtian/prison/time", me)) {
        set("dtname", __DIR__"guangchang.c"->load_name());
        set("short", query("dtname") + "水牢");
                me->start_busy(30);
                prisoners = query("prisonerlist");
                if (undefinedp(prisoners) || !prisoners || !sizeof(prisoners))
                        set("prisonerlist",  ({me}));
                else if (member_array(me, prisoners) < 0)
                        set("prisonerlist",  prisoners + ({me}));
                cti = chinese_number(abs((query("dongtian/prison/time", me)-query("online_time", me))) / 60) + "分钟";
                if (query("startroom", me)!=base_name(this_object())) {
                        CHANNEL_D->channel_broadcast("rumor", NOR + MAG + "听说" + filter_color(query("name", me), 1) + "被抓进" + query("dtname") + "禁闭" + cti + "。\n" + NOR);
                }
                call_out("delay_msg", 2, append_color(NOR + YEL + "$N" + NOR + YEL + "像只死狗样被扔了进来，一个阴森的声音说道：" +  cti + "后自己滚出去。\n" + NOR, YEL), me);
                set("startroom", base_name(this_object()), me);
                set("in_prison", base_name(this_object()), me);
                me->save();
        }
        if (playerp(me) && !__DIR__"guangchang.c"->owner_level(me))  {  
                add_action("do_action", "");
        }
        
}

void create()
{
        set("dtname", __DIR__"guangchang.c"->load_name());
        set("short", query("dtname") + "水牢");
        set("long", 
"这是洞天里黑幽幽的水牢，一米多深的水浸满了整个房间，臭不可闻。\n"
);
                //set("outdoors", "dongtian");
                set("exits",([ /* sizeof() == 1 */
                        "north" : __DIR__"zoulang21",
                ]));

        set("no_dazuo",1);
        set("no_kill",1);
        set("no_fight",1);
        set("no_steal",1);
        set("no_beg",1);         
                set("no_rideto", 1);
                set("no_flyto", 1);
        set("no_drift", 1);
                set("no_magic", 1); 
        set("no_sleep_room", 1); 
        set("valid_startroom", 1);
        
        set("owner_level", 1);  //不能成为外来者避风港
        
        set_heart_beat(15);

        setup();
}

int valid_leave(object me, string dir)
{
        if (query("dongtian/prison/time", me) && dir == "north") {
                message_vision(append_color(NOR YEL "$N" NOR YEL "仿佛想起什么提示，狼狈不堪地逃出了水牢。\n" NOR, YEL), me);
                delete("dongtian/prison/time", me);
                me->start_busy(3);
                me->move(__DIR__"teleport");
                message_vision(append_color(NOR YEL "$N" NOR YEL "狼狈不堪地从" + query("dtname") +  NOR YEL "水牢逃了出来。\n" NOR, YEL), me);
                set("startroom", "/d/city/wumiao", me);
                delete("in_prison", me);
                me->save();
                return -1;
        }
        return ::valid_leave(me, dir);
}

void heart_beat()
{
                object prisoner, *prisoners, where;
                int ti;
                
                prisoners = query("prisonerlist");
                if (!undefinedp(prisoners) && prisoners && sizeof(prisoners)) {
                        foreach (prisoner in prisoners) {
                                if (!prisoner || !objectp(where=environment(prisoner)) || !query("dongtian/prison/time", prisoner)) {
                                                prisoners -= ({prisoner});
                                                continue;
                                }
                                if (this_object() != where) {
                                        ti = query("dongtian/prison/ti", prisoner);
                                        if (ti < 1) ti = 1;
                                        throwing(prisoner, ti);
                                }
                        }
                        set("prisonerlist",  prisoners);
                }
}






