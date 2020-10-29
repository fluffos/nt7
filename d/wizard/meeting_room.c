// meeting_room.c

#include <ansi.h>
#include <command.h>
inherit ROOM;

#define SAY_CMD         "/cmds/std/say"

int do_start(string arg);
int do_say(string msg);
int do_over();
int do_not();

void create()
{
        set("short", "巫师会议室");
        set("long", @LONG
这里就是泥潭巫师的会议室所在。刚粉刷过的四周墙壁上挂着泥
潭㈠ 巫师画像，分别有：高处不胜寒(lonely)、择明(ken)、安全中
心(sinb)；泥潭㈡巫师画像：高处不胜寒(lonely)、一人两角(yezh)；
泥潭㈢ 巫师画像：高处不胜寒(lonely)、风飞(wind)。 屋子的正中
央放着一张楠木桌椅，是泥潭巫师组用来开会用的。
LONG );

        set("exits", ([ 
                "down" : __DIR__"wizard_room",
        ]));

        set("valid_startroom", 1);
        set("no_fight", 1);
        set("no_steal", 1);
        set("no_clean_up", 0);

        set("coor/x", 10000);
        set("coor/y", 10000);
        set("coor/z", 10010);
        setup();

        call_other("/clone/board/meet_b", "???");
}

void init()
{
        add_action("do_say", "say");
        add_action("do_say", "'");
        add_action("do_start", "start");
        add_action("do_over", "over");
        add_action("do_not", "tell");
        add_action("do_not", "replay");
        add_action("do_not", "whisper");
        add_action("do_not", "kickout");
        add_action("do_not", "goto");
        add_action("do_not", "call");
        add_action("do_not", "flyto");
        add_action("do_not", "home");
        add_action("do_not", "dual");  
        add_action("do_not", "dest"); 
        add_action("do_not", "quit");      
}


int do_start(string arg)
{
        object me;

        me = this_player();

        if (wiz_level(me) < wiz_level("(arch)"))
                return notify_fail("对不起，您无权召开巫师会议。\n");

        if ((int)query("meeting_trigger") != 0)
                return notify_fail("会议正在进行中。\n");

        set("meeting_trigger", 1);

        foreach (object player in users())
        {
                if (! wizardp(player))
                        continue;
                        
                if (player == me)
                        continue;

                tell_object(player, sprintf(GRN "%s(%s)告诉你：巫师会议现在召开，请到巫师会议室开会。\n" NOR, 
                                            query("name", me),query("id", me)));
                                            
                player->move("/d/wizard/meeting_room.c");
                message_vision("$N准时到达了会场。\n", player);       
                set_temp("disable_type", HIW"<会议中>"NOR, player);
        }

        set_temp("keeper", 1, me);
        
        message_vision(HIW "\n$N大声宣布：“会议现在开始。”\n" NOR, me);

        log_file("meeting.log", sprintf("%s(%s) start the meeting on %s.\n", 
                                        me->name(1), geteuid(me),
                                        ctime(time())));     
        return 1;
}

int do_say(string msg)
{
        if (! msg) return 0;

        SAY_CMD->main(this_player(), msg);
        
        if ((int)query("meeting_trigger") == 1)        
                log_file("meeting.log", sprintf(CYN "%s(%s)说道：" + msg + "\n" NOR,
                                                this_player()->name(1), 
                                                query("id", this_player())));
        return 1;
}

int do_over()
{
        object /**ob,*/ me;
//      int i;
//      string wiz_status;
        me = this_player();
        
        if (! wizardp(me) || wiz_level(me) < wiz_level("(arch)"))
                return notify_fail("你没有权力终止会议。\n");
                
        if ((int)query("meeting_trigger") == 0)
                return notify_fail("现在没有进行任何会议。\n");
        
        delete("meeting_trigger");
 
        foreach (object player in users())
        {
                if (! wizardp(player))
                        continue;
                        
                if( query_temp("disable_type", player) == HIW"<会议中>"NOR )
                        delete_temp("disable_type", player);
        }
        
        message_vision(HIW "\n$N大声宣布：“会议现在结束。”\n" NOR, me);
        log_file("meeting.log", sprintf("%s(%s) over the meeting on %s.\n", 
                                        me->name(1), geteuid(me), 
                                        ctime(time())));
        return 1;
}

int do_not()
{
       if (query("meeting_trigger"))
       {
               write("请专心开会！\n");
               return 1;
       }
       return 0;
}

int valid_leave(object me, string dir)
{
        if (query("meeting_trigger"))
                return notify_fail("现在正在开会呢，你最好哪里也不要去。\n");
                
        return ::valid_leave(me, dir);
}