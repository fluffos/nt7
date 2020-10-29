// This program is a part of NT MudLIB

inherit  ROOM;

void create()
{
        set("short",  "演武场");
        set("long",  @LONG
游氏双雄身为一方豪富，却不失武林中人的本色，宅邸之中的演武场
修葺得尤为广阔，场中旌旗蔽空，樯帆林立，场边的兵器架上摆放着
刀、枪、剑、戟、锤等十八般兵器，被家丁们擦拭得寒光闪闪。游氏
双雄嗜武成痴，时常邀请武林中的前辈耆宿、后起之秀来庄中比试切
磋。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west"  :  __DIR__"neitang",
                "east"  :  __DIR__"huayuan",
                "south" :  __DIR__"changlang4",
                "north" :  __DIR__"changlang3",
        ]));
        /*
        set("objects",([
                __DIR__"npc/haojie" : 1,
                __DIR__"npc/sengren" : 1,
                __DIR__"npc/qigai"  : 1,
        ]));
        */
        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
