

inherit ROOM;

void  create  ()
{
        set("short",  "大院");
        set("long",  @LONG
你走进聚贤庄大院，院里栽着几丛老梅，枝干甚是虬劲。院角门内
小庭院内，少不了身在洛阳的标志：几盆挺名贵的牡丹。院子中停了不
少车马，每一匹牲口都是鞍辔鲜明。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "south"  :  __DIR__"changlang2",
                "north"  :  __DIR__"changlang1",
                "east"   :  __DIR__"damen",
                "west"   :  __DIR__"zhengting",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("coor/x", -600);
        set("coor/y", 10);
        set("coor/z", 0);
        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
