// Room: /city/kedian4.c
// SMALLFISH 1995/12/04

#include <ansi.h>
#include <room.h>

inherit ROOM;

int is_chat_room() { return 1; }

void create() 
{
        set("short", "天龙殿");
        set("long", @LONG
[1；33m   永  黑  长  巨  他  古  它  古  它  遥  它  遥   永  
眼  成  龙  们  老  的  老  的  远  的  远   远  睛  以  脚 
 全  的  名  的  名  的  名  的   远  黑  后  底  都  东  字
  东  字  东  字  东   是  头  是  下  是  方  就  方  就  方
  就  方   龙  发  龙  我  龙  有  叫  有  叫  有  叫  有   
的  黄  的  成  的  一  中  一  黄  一  长  一   传  皮  传 
 长  传  群  国  条  河  条  江  条   人  肤  人      人  人
      龙      河      江[2；37；0m
LONG );

        set("no_fight", 1);
        set("no_steal", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);

        set("exits", ([
                "up"   : "/d/city/kedian",
        ]));

        setup();

        "/clone/board/kedian_b"->foo();
}