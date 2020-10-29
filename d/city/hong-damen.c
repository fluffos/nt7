//Room: /d/ruzhou/hong-damen.c
// by llm 99/06/12

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "红娘庄大门");
   set("long",
"眼前是一座气势雄伟的大庄庭，门廊高大、朱墙黄瓦，竟有些与皇宫\n"
"相似的味道，只是大门两边立的不是麒麟、狮兽，而是笑眯眯的喜财童子\n"
"童女，而且大门敞开，任人随意进入，正中上面一块巨大的乌木匾牌\n"
HIR"            红    娘    庄\n"NOR
"\n");
        set("exits", ([
                "west" : __DIR__"beimen",
                "east" : __DIR__"hong-zoulang",
   ]) );


   set("objects", ([
//           __DIR__"npc/meipo" : 1,
      ]) );
	set("coor/x", 10);
	set("coor/y", 30);
	set("coor/z", 0);
	setup();
   replace_program(ROOM);
}