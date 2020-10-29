//Room: /d/suzhou/hong-damen.c
// by llm 99/06/12

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "红娘庄大门");
        set("long", @LONG
眼前是一座气势雄伟的大庄庭，门廊高大、朱墙黄瓦，竟有些与
皇宫相似的味道，只是大门两边立的不是麒麟、狮兽，而是笑眯眯的
喜财童子童女，而且大门敞开，任人随意进入，正中上面一块巨大的
乌木匾牌
            红    娘    庄

LONG );
        set("exits", ([
                "west" : "/d/suzhou/canlangting",
                "east" : "/d/suzhou/hong-zoulang",
   ]) );


   set("objects", ([
//           "/d/suzhou/npc/meipo" : 1,
      ]) );
   set("coor/x", 210);
        set("coor/y", -200);
        set("coor/z", 0);
        setup();
   replace_program(ROOM);
}

