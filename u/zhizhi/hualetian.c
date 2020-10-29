// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <room.h>
inherit CREATE_CHAT_ROOM;

int is_chat_room() { return 1; }

void create()
{
      set("short","化乐天");
        set("long", @LONG
许君八千岁，念我八百年，自是一昼夜，乐变化五天。
LONG );

        set("exits", ([ /* sizeof() == 1 */
              "菩提":"/u/zhizhi/workroom",
        ]));

        set("valid_startroom", 1);
        set("no_fight", "1");
        set("no_clean_up", 0);
        setup();
     call_other("/clone/board/stone_b","???");
         replace_program(ROOM);
}

