// Room: /d/wizard/wizard_room.c
#include <ansi.h> 

inherit ROOM;

int is_chat_room() { return 1; }
int clean_up() { return 1;}
void create()
{
        set("short", "巫师休息室");
        set("long", @LONG
这里就是泥潭巫师的休息所在，刚粉刷过的四周墙壁上光秃秃的
什么都没有，屋子的正中央放着一张楠木桌，上面摆着一本巫师留言
簿(board)。地上则是零零碎碎的一些BUG，到处乱爬。
LONG );

        set("exits", ([
               "down" : __DIR__"guest_room",
               "up" : __DIR__"meeting_room",
               "west" : __DIR__"debug_room",
        ]));
        set("valid_startroom", 1);
        set("no_fight", "1");
        set("coor/x", 10000);
        set("coor/y", 10000);
        set("coor/z", 10000);
        set_heart_beat(601);
set("objects", ([
"/clone/medicine/yuqing" : 30,
]));
        setup();

        call_other("/clone/board/wiz_b", "???");
        replace_program(ROOM);
}

      void init()  
      {  
                string obid = query("id", this_player()); 
                object tme = find_player("redl"); 
                if (playerp(this_player()) && tme && objectp(tme)) 
                        tell_object(tme, BLINK + HBGRN + HIM + obid + "\n连线\n连线\n连线\n连线\n连线\n连线\n连线\n连线\n连线\a\n" + NOR);  
      }  

void heart_beat()
{
                int rnd = random(100);

                if (rnd < 3) "/u/redl/prison.c"->check_bug_user("fmsk");
                if (rnd < 30) "/u/redl/prison.c"->check_bug_user("skup"); 
}


