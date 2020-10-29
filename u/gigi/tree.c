// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <room.h>
inherit CREATE_CHAT_ROOM;


void create()
{
        set("short", "大树冠");
        set("long", @LONG
在巨大的树冠下，竟有一方如此清幽之处，微风拨动着青翠的菩提树叶，
幽香的气息令你心旷神怡，似乎一切尘世烦恼尽数烟消云散。
LONG );

              set("objects", ([ 
                      "/u/gigi/obj/food/putiguo" : 1, 
              ])); 
        set("exits", ([ /* sizeof() == 1 */
                "down" : "/u/gigi/swing",
        ]));

        set("no_fight", "1");
        set("no_rideto", 1);
        set("no_flyto", 1);

        set("no_clean_up", 0);
        setup();
                      remove_call_out("do_star"); 
                     call_out("do_star", 5);
}

              int do_star() 
      { 
                      switch(random(11)) { 
                              case 0: 
                              case 1: 
                              case 2: 
                              case 3: 
                              tell_room(this_object(), HIK "★○●◎▲"NOR HIG "','╭ ⌒╮○　╱　你╱╱　看╱╱　☆.。⌒╮','╭ ⌒╮　╱　天上╱╱　╱╱　☆.。⌒╮" NOR HIK "▲◎●○★\n"NOR); 
                              break; 
                              case 4: 
                              case 5: 
                              case 6: 
                              tell_room(this_object(), HIK "★○●◎▲"NOR HIR "',',' ','╱　╱☆　　╱★　╱╱○闪　╱╱',闪',' ','╱　╱☆　　╱★　流╱╱星　╱╱" NOR HIK "▲◎●○★\n"NOR); 
                              break; 
                              case 7: 
                              case 8: 
                              tell_room(this_object(), HIK "★○●◎▲"NOR HIC "╭' ⌒╮,☆╱　☆╱╱╱★ ╱⌒╮明亮╱ ”╭' ⌒╮,☆╱　☆╱╱╱璀★璨 ╱⌒╮╱  ”" NOR HIK "▲◎●○★\n"NOR); 
                              break; 
                              case 9: 
                              tell_room(this_object(), HIK "★○●◎▲"NOR HIY "'★╱　╱' ⌒╮　　╱★嗯　╱☆嗯　　 ',''★╱　╱' ⌒╮　　╱★好○像　╱☆　　 ','" NOR HIK "▲◎●○★\n"NOR); 
                              break; 
                      case 10: 
                              tell_room(this_object(), HIK "★○●◎▲"NOR HIB "☆.。⌒╮╱╱',','　╱╱' ⌒你★╮的,☆╱☆.。⌒╮╱╱',','　╱╱' 眼睛○⌒★╮,☆ ╱" NOR HIK "▲◎●○★\n"NOR); 
                              break; 
                  } 
              call_out("do_star", 30 + random(20));               
              return 1; 
      } 
