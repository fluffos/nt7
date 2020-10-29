// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <room.h>
inherit CREATE_CHAT_ROOM;

int is_chat_room() { return 1; }
int do_hy(string arg); 
int do_pick();

void create()
{
        set("short", NOR HIW "民工" HIK "棚" NOR);
        set("long", @LONG
这是没有建造工作室的巫师的临时住处，这里的设备非常简单，只有
一些常用物品。
LONG );

        set("exits", ([ /* sizeof() == 1 */
                "north" : "/u/redl/tianshenzoulang",
                "south" : "/d/wizard/wizard_room",
                "up" : __DIR__"check",
        ]));

          set("objects", ([ 
//          "/u/mud/charm.c":1,
      "/kungfu/class/misc/haigui":1,
          ]));
        set("valid_startroom", 1);
        //set("no_fight", "1");
        set("no_clean_up", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "north" && ! wizardp(me))
                return notify_fail("那里只有巫师才能进去。\n");

        return ::valid_leave(me, dir);
}

void init()
{
        add_action("do_hy","hy");
        add_action("do_pick","pick");
}
int do_hy(string arg)
{
        object obj;
        object me = this_player();
        if(! arg || arg == "")
            return notify_fail("请输入要还阳者的id？\n");
        obj = find_player(arg);
        if(!obj)
            return notify_fail("没有这个人。\n");

        obj->move("/d/death/gate");
        tell_object(me,obj->name()+"已经被送往白无常处复活！\n");

      return 1;
}
int do_pick()
{
        object ob;
        object me = this_player();
        if(!wizardp(me) && query("id",me)!="mud")
            return notify_fail("不要再别人家里乱翻东西！\n");
        ob = new("/u/mud/charm");
        ob->move(me);
        return 1;
}
