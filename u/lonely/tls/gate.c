#include <ansi.h>
#include <wanted.h>
inherit ROOM;

void create()
{
        set("short", HIY"崇圣寺"NOR);
        set("long", @LONG
崇圣寺在大理城外点苍山中岳峰之北，因段氏历代祖先做皇帝的，往
往避位为僧，都是在这崇圣寺中出家，因此崇圣寺便是大理皇室的家庙，
于全国诸寺之中最是尊荣，所以又称之为天龙寺，大门气势恢弘，上挂一
巨幅匾额(biane)。这里背负苍山，面临洱水，极占形胜。
LONG);
        set("outdoors", "天龙寺");

        set("item_desc",([
	  "biane" : "\n
            ※※※※※※※※※※※※※※※※※※※※※※
            ※※※※　　　　　　　　　　　　　　※※※※       
            ※※※※     "HIY"崇      圣      寺"NOR"     ※※※※
            ※※※※　　　　　　　　　　　　　　※※※※
            ※※※※※※※※※※※※※※※※※※※※※※\n\n",
			  ]));	

        set("exits", ([             
               "enter" : __DIR__"road",
               "south" : __DIR__"shanlu",
        ]));

        set("coor/x",-350);
  set("coor/y",-360);
   set("coor/z",20);
   setup();
}

int valid_leave(object me, string dir)
{
	if (dir == "enter" && is_wanted(me))
		return 0;
	return ::valid_leave(me, dir);
}
