#include <ansi.h>

inherit ROOM;

#define PLACE "xy"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "无极帮总舵");
        set("long", @LONG
这里是无极帮的大厅，只见代表无极帮威望的那块横匾高高的悬
 挂着。那只是上好松木做成的横匾，黑漆金字，写着无极帮三个大字。
 木匾下面的署名，包括了少林、武当、华山掌门人，慕容世家主人、
 丐帮帮主，五个江湖上最具权势的人物。也正因为有了这块横匾，近
 年来无极帮声势大盛，许多江湖儿女纷纷慕名而来，无极帮俨然一派
 武林第一帮的气势。墙上挂着一个任务牌（paizi）。 
LONG );

        set("objects", ([
               __DIR__"npc/boss-jin"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "south" : __DIR__"wjb_damen",
        ]));

        set("coor/x", -7780);
	set("coor/y", -720);
	set("coor/z", 0);
	setup();
}
#include <bang_good.h>